/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../preview_popwin.h"
#include <format>
#include <cstdlib>

static void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Move past the replaced section to avoid infinite loops
    }
}

json preview_popup_get_window_data(Preview_popup& win) {
    json data = json::object();
    data["dir"] = win.dir;
    return data;
}

void preview_popup_set_window_data(Preview_popup& win, const json& data) {
    if(data["dir"].is_number_integer()){
        win.dir = data["dir"].get<int32_t>();
    }
}

void PreviewPopup::register_setting_drawer(std::function<void(std::shared_ptr<GlobalState>& state, std::shared_ptr<GoProMaster>& master, const CameraInfo& c)> caller){
    setting_drawer = caller;
}

void PreviewPopup::register_protune_drawer(std::function<void(std::shared_ptr<GlobalState>& state, std::shared_ptr<GoProMaster>& master, const CameraInfo& c)> caller){
    protune_drawer = caller;
}

void PreviewPopup::trigger(bool value){
    BasePopWindow::trigger(value);
    if(value){
        reader = std::thread([&]() {
            update_decoder();
        });
    }else{
        _stop_thread();
        isopen = false;
        master->preview_end(state->preview_server, state->preview_ip);
    }
}

int32_t preview_popup_get_current_model(const json& target) {
    if(target["model_name"].is_string()){
        std::string model_name = target["model_name"].get<std::string>();
        if(model_name == "MAX 2") return MODEL_MAX2;
        else if(model_name == "HERO13 Black") return MODEL_13;
        else if(model_name == "HERO12 Black") return MODEL_12;
        else if(model_name == "HERO11 Black") return MODEL_11_BLACK;
        else if(model_name == "HERO11 Black Mini") return MODEL_11;
        else if(model_name == "HERO10 Black") return MODEL_10;
        else if(model_name == "HERO9 Black") return MODEL_9;
    }
    return 0;
}

void preview_popup_stop_thread(Preview_popup& win) {
    stream_open = false;
    if (cap.isOpened()) {
        cap.release();
    }
    if(reader.joinable()){
        reader.join();
    }
    if(gl_texture != 0){
        glDeleteTextures(1, &gl_texture);
        gl_texture = 0;
    }
    while(frame_queue.size() > 0) frame_queue.pop();
}

void preview_popup_draw_rotation_button(Preview_popup& win) {
    if(ImGui::Button("<== Rotate##preview_button")){
        DirChange(true); remap = true;
    }
    ImGui::SameLine();
    if(ImGui::Button("Rotate ==>##preview_button")){
        DirChange(false); remap = true;
    }
}

void preview_popup_draw_camera_selection(Preview_popup& win) {
    int32_t s = -1;
    std::lock_guard<std::mutex> lock(master->camera_mtx);
    s = master->findCamera(state->preview_server, state->preview_ip);
    if(s != -1){
        const std::shared_ptr<CameraInfo>& c = master->getCameras().at(s);
        std::string display_name = c->name;
        display_name += " ";
        display_name += c->ip;
        if(ImGui::BeginCombo("Camera##Preview_Camera_Selection", display_name.c_str())){
            for(auto& cam : master->getCameras()){
                if(!cam->connected) continue;
                std::string display_name2 = cam->name;
                display_name2 += " ";
                display_name2 += cam->ip;
                bool selected = display_name == display_name2;
                if(ImGui::Selectable(display_name2.c_str(), selected)){
                    _stop_thread();
                    master->preview_end(state->preview_server, state->preview_ip);
                    master->preview_start(cam->server, cam->ip);
                    state->preview_ip = cam->ip;
                    state->preview_server = cam->server;
                    reader = std::thread([&]() {
                        update_decoder();
                    });
                }
            }
            ImGui::EndCombo();
        }
    }
}

void preview_popup_draw_bottom_button(Preview_popup& win) {
    if(ImGui::Button("Cancel")){
        trigger(false);
    }
    ImGui::SameLine();
    if(!trying) {
        if(ImGui::Button("Retry")){
            _stop_thread();
            reader = std::thread([&]() {
                update_decoder();
            });
        }
    }
}

void preview_popup_draw_setting(Preview_popup& win) {
    if(setting_drawer != NULL){
        int32_t s = -1;
        s = master->findCamera(state->preview_server, state->preview_ip);
        if(s != -1){
            const CameraInfo c = master->getCamera_Clone(s);
            if(ImGui::Button("Quick Apply All##Preview_Popwin_Action")){
                state->applying_all = true;
                master->quickApplyAll(c);
            }
            if(ImGui::BeginTabBar("TabBar##Preview_Popwin")){
                if(ImGui::BeginTabItem("Setting##Preview_Popwin_Right")){
                    setting_drawer(state, master, c);
                    ImGui::EndTabItem();
                }
                if(ImGui::BeginTabItem("Protune##Preview_Popwin_Right")){
                    protune_drawer(state, master, c);
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
        }
    }
}

cv::Mat preview_popup_get_latest_frame(Preview_popup& win) {
    std::lock_guard<std::mutex> lock(win.queue_mutex);

    if (win.frame_queue.empty()) {
        return cv::Mat();
    }
    
    cv::Mat frame = win.frame_queue.front();
    win.frame_queue.pop();
    return frame;
}

void preview_popup_convert_texture(Preview_popup& win, cv::Mat& mat) {
    if(mat.empty()) return;

    if(win.texture_width != mat.cols || win.texture_height != mat.rows){
        win.texture_width = mat.cols;
        win.texture_height = mat.rows;
        glDeleteTextures(1, &win.gl_texture);
        win.gl_texture = 0;
    }

    cv::Mat rotated_frame;
    if(win.dir == 0){
        rotated_frame = mat;  // No rotation
    }
    else if(win.dir == 1){
        cv::rotate(mat, rotated_frame, cv::ROTATE_90_CLOCKWISE);
    }
    else if(win.dir == 2){
        cv::rotate(mat, rotated_frame, cv::ROTATE_180);
    }
    else if(win.dir == 3){
        cv::rotate(mat, rotated_frame, cv::ROTATE_90_COUNTERCLOCKWISE);
    }
    else {
        rotated_frame = mat;  // Invalid dir, no rotation
    }

    cv::Mat frame;
    int32_t target_w, target_h;
    if(dir == 0 || dir == 2){
        // 0° or 180° - width/height unchanged
        target_w = win.texture_width;
        target_h = win.texture_height;
    } else {
        // 90° or 270° - width/height swapped
        target_w = win.texture_height;
        target_h = win.texture_width;
    }

    if (rotated_frame.cols != target_w || rotated_frame.rows != target_h){
        cv::resize(rotated_frame, frame, cv::Size(target_w, target_h));
    } else {
        frame = rotated_frame;
    }

    cv::Mat rgb;
    cv::cvtColor(frame, rgb, cv::COLOR_BGR2RGB);

    if(win.gl_texture == 0){
        glGenTextures(1, &win.gl_texture);
        glBindTexture(GL_TEXTURE_2D, win.gl_texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
        // Allocate texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
            target_w, target_h,
            0, GL_RGB, GL_UNSIGNED_BYTE, rgb.data);
        glBindTexture(GL_TEXTURE_2D, 0);
        std::cout << "[Preview Decoder] Frame converted !\n";
    } else {
        // ✅ Update texture data (fast path)
        glBindTexture(GL_TEXTURE_2D, win.gl_texture);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,
            target_w, target_h,
            GL_RGB, GL_UNSIGNED_BYTE, rgb.data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void preview_popup_dir_change(Preview_popup& win, const bool increase) {
    if(increase){
        win.dir++;
        if(win.dir >= 4) win.dir = 0;
    }else{
        win.dir--;
        if(win.dir <= -1) win.dir = 3;
    }
    glDeleteTextures(1, &win.gl_texture);
    win.gl_texture = 0;
    win.base.
    state->update_server();
}
