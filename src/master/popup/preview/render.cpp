/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../preview_popwin.h"
#include "src/imgui_notify.h"

void preview_popup_render(Preview_popup& win) {
    Global_state& state = win.base.base.state;
    Gopro_master& master = win.base.base.master;
    AppData& appdata = state.appdata;
    
    cv::Mat frame = get_latest_frame();
    ConvertTexture(frame);

    ImGuiIO& io = ImGui::GetIO();
    ImVec2 display_size = io.DisplaySize;
    ImVec2 unit = ImVec2(display_size.x / 12.0f, display_size.y / 12.0f);
    float left_width;
    float top_width;
    float img_width;

    ImGui::SetNextWindowPos(ImVec2(unit.x * 0.5F, unit.y * 0.5F), wp_cond);
    ImGui::SetNextWindowSize(ImVec2(unit.x * 11.0F, unit.y * 11.0F), wp_cond);

    /**
     * The resolution we actually want to display on the screen
     * The image is already rotate during ConvertTexture stage
     * So we just have to figure out the display vector
     */
    int32_t target_w, target_h;
    if(dir == 0 || dir == 2){
        // 0° or 180° - width/height unchanged
        target_w = texture_width;
        target_h = texture_height;
    } else {
        // 90° or 270° - width/height swapped
        target_w = texture_height;
        target_h = texture_width;
    }

    if(ImGui::BeginPopupModal(title.c_str(), NULL, wp_flag)){
        if(gl_texture != 0){ // We have frame to display
            ImVec2 image_pos = ImGui::GetCursorScreenPos();
            ImVec2 window_size = ImGui::GetWindowSize();

            // Image drawing
            {
                float ratio = (float)target_w / (float)target_h;
                ImVec2 size;
                // First we adjust the ratio
                if(ratio >= 1.0f){ // Normal aspect, w > h
                    size = ImVec2((unit.y * 6.0f) * ratio, unit.y * 6.0f);
                }else{ // h > w
                    size = ImVec2(unit.x * 6.0f, (unit.x * 6.0f) / ratio);
                }
                // Even if we adjust the ratio, the resolution might still out of screen
                if(size.x > (unit.x * 8.0f)){
                    float diff = (unit.x * 8.0f) / size.x;
                    size *= diff;
                }else if(size.y > (unit.y * 8.0f)){
                    float diff = (unit.y * 8.0f) / size.y;
                    size *= diff;
                }
                if(remap){
                    std::cout << "Window size: " << display_size.x << ", " << display_size.y << std::endl;
                    std::cout << "unit size: " << unit.x << ", " << unit.y << std::endl;
                    std::cout << "Image size: " << target_w << ", " << target_h << std::endl;
                    std::cout << "Rescale size: " << size.x << ", " << size.y << std::endl;
                    remap = false;
                }
                
                left_width = ( (unit.x * 11.0f) - size.x) / 2.0f;
                top_width = ( (unit.y * 9.0f) - size.y) / 2.0f;
                img_width = size.x;
                ImGui::Dummy(ImVec2(0.0f, top_width));
                ImGui::Dummy(ImVec2(left_width, 0.0f));
                ImGui::SameLine();
                ImGui::Image((ImTextureID)(intptr_t)gl_texture, size);
            }
            ImGui::SetCursorScreenPos(image_pos);
            // Go Different camera
            { // Left side of the panel
                ImGui::BeginChild("Detail##Preview_Camera_Inspector", ImVec2(left_width, 0));
                _draw_rotation_button();
                _draw_camera_selection();
                _draw_bottom_button();
                ImGui::EndChild();
            }
            ImGui::SameLine();
            ImGui::Dummy(ImVec2(img_width, 0.0f));
            ImGui::SameLine();
            { // Right side of the panel
                ImGui::BeginChild("Detail##Preview_Camera_Inspector2", ImVec2(left_width, 0));
                _draw_setting();
                ImGui::EndChild();
            }

        } else { // No frame QAQ
            ImGui::Dummy(ImVec2(800, 280));
            float win_width = ImGui::GetContentRegionAvail().x;
            std::string msg = "Waiting for video stream...";
            float text_width = ImGui::CalcTextSize(msg.c_str()).x;
            ImGui::SetCursorPosX((win_width - text_width) * 0.5f);
            ImGui::Text("%s", msg.c_str());
            // Animated dots
            static int dots = 0;
            static auto last = std::chrono::steady_clock::now();
            auto now = std::chrono::steady_clock::now();
            if(std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count() > 500){
                dots = (dots + 1) % 4;
                last = now;
            }
            std::string dot_str(dots, '.');
            ImGui::SameLine();
            ImGui::Text("%s", dot_str.c_str());

            _draw_bottom_button();
        }
        ImGui::EndPopup();

        if(state->applying_all != applying_all_last){
            applying_all_last = state->applying_all;
            if(state->applying_all){
                ImGuiToast toast(ImGuiToastType_Success, 3000);
                toast.set_title("Trying to applying...");
                ImGui::InsertNotification(toast);
            }else{
                ImGuiToast toast(ImGuiToastType_Success, 3000);
                toast.set_title("Applying Finish");
                ImGui::InsertNotification(toast);
            }
        }
    }
}