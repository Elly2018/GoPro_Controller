/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "utility.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "windows/base_window.h"
#include "popup/base_pop_window.h"
#include "imgui_helper.h"

static constexpr char* SERVER_LIST_PATH = "servers.json";
static constexpr char* GUI_PATH = "gui.json";
static constexpr char* PRESETS_PATH = "presets.json";

static void update_media_list(AppData& data, const std::vector<MediaInfo> data){
    std::lock_guard<std::mutex> lock(data.global_state->media_list_mtx);
    data.global_state.current_media_list = data;
}

static void setting_getter_feedback(AppData& data, const std::string ip, const json setting){
    if(data.global_state->current_camera_item == ip){
        data.global_state.current_setting_items = = setting;
        data.global_state.current_setting_items_bind = true;
    }
}

static void status_getter_feedback(AppData& data, const std::string ip, const json status){
    if(global_state->current_camera_item == ip){
        global_state->current_status_items = status;
        global_state->current_status_items_bind = true;
    }
}

static void HW_getter_feedback(AppData& data, const std::string ip, const json hw){
    if(global_state->current_camera_item == ip){
        global_state->current_hw_items = hw;
        global_state->current_hw_items_bind = true;
    }
}

static void assign_log(AppData& data, const std::string key, const std::string value){
    if(execution_logs.count(key)){
        std::string b = execution_logs.at(key);
        execution_logs.insert_or_assign(key, b + "\n" + value);
    }else{
        execution_logs.insert_or_assign(key, value);
    }
}

static void savePresetList(json data){
    std::ofstream file(PRESETS_PATH);
    if(file.is_open()){
        file << data.dump();
        file.close();
    }
}

static void apply_feedbacks(AppData& data){
    data.global_state.applying_all_count++;
    if(data.global_state.applying_all_count >= data.master->getServerCount()){
        data.global_state.applying_all = false;
    }
}

static void background_worker(AppData& data){
    while(!data.should_quit){
        while(!command_queue.empty()){
            std::string cmd = command_queue.front();
            command_queue.pop();
            if(cmd == "add_camera"){
                add_camera_popwin->trigger(true);
                std::cout << "Detect add_camera popup" << std::endl;
            }
            else if(cmd == "scan_camera"){
                scan_camera_popwin->trigger(true);
                std::cout << "Detect scan_camera popup" << std::endl;
            }
            else if(cmd == "start_webcam"){
                start_webcam_popwin->trigger(true);
                std::cout << "Detect start_webcam popup" << std::endl;
            }
            else if(cmd == "preview_start"){
                preview_popwin->trigger(true);
                std::cout << "Detect preview popup" << std::endl;
            }
            else if(cmd == "add_preset"){
                add_preset_popwin->trigger(true);
                std::cout << "Detect add_preset popup" << std::endl;
            }
            else if(cmd == "preset_manager"){
                preset_manager_popwin->trigger(true);
                std::cout << "Detect preset_manager popup" << std::endl;
            }
            else if(cmd == "media_browser"){
                media_browser_popwin->trigger(true);
                std::cout << "Detect media_browser popup" << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

static void push_command(AppData& data, const char* cmd){
    data.command_queue.push(cmd);
}

static void update_server_list(AppData& data){
    std::cout << "updateServerList" << std::endl;
    json data = json::object();
    data["data"] = json::array();
    for(const auto& s : master->getServers()){
        if(s){
            data["data"].push_back(s->ip);
        }
    }
    data["global"] = get_global_state_data(*global_state);
    data["window"] = json::object();
    data["window"]["camera_list_win"] = camera_list_win->get_window_data();
    data["window"]["inspector_win"] = inspector_win->get_window_data();
    data["window"]["websocket_win"] = websocket_win->get_window_data();
    data["window"]["style_setting_win"] = style_setting_win->get_window_data();
    data["popwin"]["preview_popwin"] = preview_popwin->get_window_data();
    saveServerList(data);
    servers->swap(data);
}

static void update_preset_list(AppData& data){
    savePresetList(*presets);
}

static void update_GUI_list(AppData& data){
    data.gui["websocket_server_window"] = websocket_win->is_enable();
    data.gui["camera_list_win"] = camera_list_win->is_enable();
    data.gui["inspector_win"] = inspector_win->is_enable();
    data.gui["style_setting_win"] = style_setting_win->is_enable();
    saveGUI(*gui);
    ImGui::SaveIniSettingsToDisk("imgui.ini");
}

void saveServerList(json data){
    std::ofstream file(SERVER_LIST_PATH);
    if(file.is_open()){
        file << data.dump();
        file.close();
    }
}

void saveGUI(json data){
    std::ofstream file(GUI_PATH);
    if(file.is_open()){
        file << data.dump();
        file.close();
    }
}

json loadServerList() {
    std::ifstream file(SERVER_LIST_PATH);
    if(!file.is_open()){
        std::cerr << "No server config found" << std::endl;
        return json::object();
    }

    std::stringstream buffer;
    std::string fileContents;

    buffer << file.rdbuf();
    fileContents = buffer.str();

    file.close();

    return json::parse(fileContents);
}

json loadGUI() {
    std::ifstream file(GUI_PATH);
    if(!file.is_open()){
        std::cerr << "No gui config found" << std::endl;
        return json::object();
    }

    std::stringstream buffer;
    std::string fileContents;

    buffer << file.rdbuf();
    fileContents = buffer.str();

    file.close();

    return json::parse(fileContents);
}

json loadPresetList(){
    std::ifstream file(PRESETS_PATH);
    if(!file.is_open()){
        std::cerr << "No presets config found" << std::endl;
        return json::object();
    }

    std::stringstream buffer;
    std::string fileContents;

    buffer << file.rdbuf();
    fileContents = buffer.str();

    file.close();

    return json::parse(fileContents);
}

void init(AppData& data){
    data.global_state.appdata = data;
    data.servers = loadServerList();
    data.gui = loadGUI();
    data.presets= loadPresetList();
    
    data.websocket_window_base = { data.servers, data.global_state, data.master, "Websocket" };
    data.camera_list_window_base = { data.servers, data.global_state, data.master, "Cameras" };
    data.inspector_window_base = { data.servers, data.global_state, data.master, "Inspector" };
    data.style_window_base = { data.servers, data.global_state, data.master, "Style" };

    data.websocket_window.render = websocket_window_render;
    data.camera_list_window.render = camera_list_window_render;
    data.inspector_window.render = inspector_window_render;
    data.style_window.render = style_window_render;

    data.windows_array[0] = &data.websocket_window_base;
    data.windows_array[1] = &data.camera_list_window_base;
    data.windows_array[2] = &data.inspector_window_base;
    data.windows_array[3] = &data.style_window_base;

    data.add_camera_popup_window_base = { data.servers, data.global_state, data.master, "Websocket" };
    data.scan_camera_popup_window_base = { data.servers, data.global_state, data.master, "Websocket" };
    data.start_webcam_popup_window_base = { data.servers, data.global_state, data.master, "Websocket" };
    data.preview_popup_window_base = { data.servers, data.global_state, data.master, "Websocket" };
    data.add_preset_popup_window_base = { data.servers, data.global_state, data.master, "Websocket" };
    data.preset_manager_popup_window_base = { data.servers, data.global_state, data.master, "Websocket" };
    data.media_browser_popup_window_base = { data.servers, data.global_state, data.master, "Websocket" };

    data.add_camera_popup_window_base.detect = gopro_master_popup_detect;
    data.scan_camera_popup_window_base = gopro_master_popup_detect;
    data.start_webcam_popup_window_base = gopro_master_popup_detect;
    data.preview_popup_window_base = gopro_master_popup_detect;
    data.add_preset_popup_window_base = gopro_master_popup_detect;
    data.preset_manager_popup_window_base = gopro_master_popup_detect;
    data.media_browser_popup_window_base = gopro_master_popup_detect;

    data.add_camera_popup_window.render = add_camera_popup_render;

    data.pop_windows_array[0] = &data.add_camera_popup_window_base;
    data.pop_windows_array[1] = &data.scan_camera_popup_window_base;
    data.pop_windows_array[2] = &data.start_webcam_popup_window_base;
    data.pop_windows_array[3] = &data.preview_popup_window_base;
    data.pop_windows_array[4] = &data.add_preset_popup_window_base;
    data.pop_windows_array[5] = &data.preset_manager_popup_window_base;
    data.pop_windows_array[6] = &data.media_browser_popup_window_base;
    
    data.master.feedback_camera_media_list = update_media_list;
    data.master.feedback_camera_setting = setting_getter_feedback;
    data.master.feedback_camera_status = status_getter_feedback;
    data.master.feedback_camera_hw = HW_getter_feedback;
    data.master.feedback_camera_log = assign_log;
    data.master.feedback_camera_preset_save = update_preset_list;
    data.master->set_preset_data(data.presets);
    data.master.feedback_camera_apply_all = apply_feedbacks;
    data.preview_popup_window.register_setting_drawer(InspectorWindow::global_draw_setting);
    data.preview_popup_window.register_protune_drawer(InspectorWindow::global_draw_protune);
    data.global_state.update_event = background_worker;
    data.global_state.update_server = update_server_list;
    data.global_state.update_preset = update_preset_list;
    data.global_state.update_GUI = update_GUI_list;
    data.global_state.command_sender = push_command;
}

void init_state_setup(AppData& data){
    if(data.servers["data"].is_array()){     
        for(int i = 0; i < data.servers["data"].size(); i++){
            if(data.servers["data"].at(i).is_string()){
                std::string buffer_ip = data.servers["data"].at(i).get<std::string>();
                std::string ip =  master->addServer(buffer_ip);
                data.master.
                master->reconnect(ip);
            }
        }
    }
    if(data.servers["global"].is_object()){
        set_global_state_data(*global_state, data.servers["global"]);
    }
    if(data.servers["window"].is_object()){
        json websocket_win_json = data.servers["window"]["websocket_win"];
        if(websocket_win_json.is_object()){
            windows[0]->set_window_data(websocket_win_json);
        }
        json camera_list_win_json = data.servers["window"]["camera_list_win"];
        if(camera_list_win_json.is_object()){
            windows[1]->set_window_data(camera_list_win_json);
        }
        json inspector_win_json = data.servers["window"]["inspector_win"];
        if(inspector_win_json.is_object()){
            windows[2]->set_window_data(inspector_win_json);
        }
        json style_setting_win_win_json = data.servers["window"]["style_setting_win"];
        if(style_setting_win_win_json["colors"].is_null() || style_setting_win_win_json["fields"].is_null()){
            std::cout << "Apply default theme" << std::endl;
            setup_catppuccin_mocha_theme();
        }else{
            std::cout << "Apply loaded theme" << std::endl;
            windows[3]->set_window_data(style_setting_win_win_json);
        }
    }else{
        std::cout << "Apply default theme" << std::endl;
        setup_catppuccin_mocha_theme();
    }
    if(data.servers["popwin"].is_object()){
        json preview_popwin_json = data.servers["popwin"]["preview_popwin"];
        if(preview_popwin_json.is_object()){
            popwins[3]->set_window_data(preview_popwin_json);
        }
    }

    if(data.gui["websocket_server_window"].is_boolean() && data.gui["websocket_server_window"].get<bool>()){
        windows[0]->trigger(true);
        std::cout << "Detect websocket_server_window gui is on" << std::endl;
    }
    if(data.gui["camera_list_win"].is_boolean() && data.gui["camera_list_win"].get<bool>()){
        windows[1]->trigger(true);
    }
    if(data.gui["inspector_win"].is_boolean() && data.gui["inspector_win"].get<bool>()){
        windows[2]->trigger(true);
    }
    if(data.gui["style_setting_win"].is_boolean() && data.gui["style_setting_win"].get<bool>()){
        windows[3]->trigger(true);
    }
}