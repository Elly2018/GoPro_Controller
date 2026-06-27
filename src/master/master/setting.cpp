/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_master.h"
#include "../data/server_connection.h"
#include "../data/app.h"

void gopro_master_preset_switch(AppData& data, const std::string server, const std::string target, int32_t mode) {
    for (Server_connection& s : data.master.servers) {
        if (!s.vaild) continue;
        if (!s.connected) continue;
        if (server.size() > 0 && server != s.ip) continue;
        json get_status = json::object();
        get_status["key"] = "preset";
        get_status["value"] = json::object();
        get_status["value"]["name"] = "load";
        get_status["value"]["mode"] = mode;
        get_status["value"]["target"] = target;
        s.client.send(get_status.dump());
    }
}

void gopro_master_locate(AppData& data, const std::string server, const std::string target) {
    data.master.locates.server = server;
    data.master.locates.ip = target;
    data.master.locates.vaild = true;
}

void gopro_master_apply(AppData& data, const std::string& ip, const std::string& target, const int32_t id, const int32_t value) {
    for (Server_connection& s : data.master.servers) {
        if (!s.vaild) continue;
        if (!s.connected) continue;
        json get_status = json::object();
        get_status["key"] = "query";
        get_status["value"] = json::object();
        get_status["value"]["name"] = "set";
        get_status["value"]["source"] = ip;
        get_status["value"]["target"] = target;
        get_status["value"]["id"] = id;
        get_status["value"]["value"] =  std::to_string(value);
        s.client.send(get_status.dump());
    }
}

void gopro_master_apply(AppData& data, const std::string& ip, const json& res) {
    for (Server_connection& s : data.master.servers) {
        if (!s.vaild) continue;
        if (!s.connected) continue;
        json get_status = json::object();
        get_status["key"] = "query";
        get_status["value"] = json::object();
        get_status["value"]["source"] = ip;
        get_status["value"]["name"] = "setall";
        get_status["value"]["value"] = res;
        s.client.send(get_status.dump());
    }
}

void gopro_master_quick_apply(AppData& data, const CameraInfo& target) {
    int32_t model = InspectorWindow::_get_current_model(target.hw);
    json root = json::object();
    json _set = json::object();
    json _status = json::object();
    
    if(!gopro_master_get_settings_from_camera(data, target, _set) || !gopro_master_get_status_from_camera(data, target, _status)) {
        return;
    }

    int32_t p = _status[std::to_string(PRESET_ID)].get<int32_t>();
    root["model"] = model;
    root["preset"] = p;
    root["setting"] = _set;
    std::cout << "trying apply all, preset: " << p << std::endl;
    applyAll(target.ip, root);
}

void gopro_master_stop_apply(AppData& data, const CameraInfo& target) {
    for (Server_connection& s : data.master.servers) {
        if (!s.vaild) continue;
        if (!s.connected) continue;
        json get_status = json::object();
        get_status["key"] = "query";
        get_status["value"] = json::object();
        get_status["value"]["name"] = "setall_cancel";
        s.client.send(get_status.dump());
    }
}

bool gopro_master_directory_exists(const std::string& path) {
    return fs::exists(path) && fs::is_directory(path);
}

int32_t gopro_master_add_preset(AppData& data, const std::string name, json data) {
    if(!(*preset_ptr)["data"].is_array()) {
        (*preset_ptr)["data"] = json::array();
    }else{
        for(int32_t i = 0; i < (*preset_ptr)["data"].size(); i++){
            json item = (*preset_ptr)["data"].at(i);
            if(item["name"].is_string()){
                if(item["name"].get<std::string>() == name){
                    // Name repeat
                    return 2;
                }
            }
        }
    }
    (*preset_ptr)["data"].push_back(data);
    return 0;
}

bool gopro_master_get_preset(AppData& data, const std::string name, json& data) {
    if(!(*preset_ptr)["data"].is_array()) {
        (*preset_ptr)["data"] = json::array();
        return false;
    }
    for(int32_t i = 0; i < (*preset_ptr)["data"].size(); i++){
        json item = (*preset_ptr)["data"].at(i);
        if(item["name"].is_string()){
            if(item["name"].get<std::string>() == name){
                data = item;
                return true;
            }
        }
    }
    return false;
}

bool gopro_master_remove_preset(AppData& data, const std::string name) {
    if(!(*preset_ptr)["data"].is_array()) {
        (*preset_ptr)["data"] = json::array();
        return false;
    }else{
        for(int32_t i = 0; i < (*preset_ptr)["data"].size(); i++){
            json item = (*preset_ptr)["data"].at(i);
            if(item["name"].is_string()){
                if(item["name"].get<std::string>() == name){
                    (*preset_ptr)["data"].erase((*preset_ptr)["data"].begin() + i);
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<std::string> gopro_master_get_preset_names(AppData& data) {
    if(!(*preset_ptr)["data"].is_array()) {
        (*preset_ptr)["data"] = json::array();
        return std::vector<std::string>();
    }
    std::vector<std::string> a = std::vector<std::string>();
    for(int32_t i = 0; i < (*preset_ptr)["data"].size(); i++){
        json item = (*preset_ptr)["data"].at(i);
        if(item["name"].is_string()){
            a.push_back(item["name"].get<std::string>());
        }
    }
    return a;
}
