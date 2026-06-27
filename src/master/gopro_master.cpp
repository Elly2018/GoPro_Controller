/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "gopro_master.h"
#include <iostream>
#include <filesystem>
#include "hv/requests.h"
#include "windows/inspector.h"
#include "src/imgui_notify.h"
#include "data/app.h"

namespace fs = std::filesystem;

extern std::shared_ptr<GlobalState> global_state;

void GoProMaster::get_media_info(const std::string server, const std::string ip, const std::string path){
    json data = json::object();
    data["key"] = "media";
    data["value"] = json::object();
    data["value"]["name"] = "info";
    data["value"]["path"] = path;
    data["value"]["target"] = ip;

    for(auto s : servers){
        if(s->ip != server) continue;
        bool islocal = s->ip == "127.0.0.1";
        data["value"]["local"] = islocal;
        if((s->ip == server || server.size() == 0) && s->connected){
            s->client->send(data.dump());
            break;
        }
    }
}

void GoProMaster::get_media_list(const std::string server, const std::string ip){
    json data = json::object();
    data["key"] = "media";
    data["value"] = json::object();
    data["value"]["name"] = "list";
    data["value"]["target"] = ip;

    for(auto s : servers){
        if(s->ip != server) continue;
        bool islocal = s->ip == "127.0.0.1";
        data["value"]["local"] = islocal;
        if((s->ip == server || server.size() == 0) && s->connected){
            s->client->send(data.dump());
            break;
        }
    }
}

void GoProMaster::presetSwitch(const std::string server, const std::string target, int32_t mode) {
    std::thread([=](){
        for (auto& s : servers) {
            if (!s->connected) continue;
            if (server.size() > 0 && server != s->ip) continue;
            json get_status = json::object();
            get_status["key"] = "preset";
            get_status["value"] = json::object();
            get_status["value"]["name"] = "load";
            get_status["value"]["mode"] = mode;
            get_status["value"]["target"] = target;
            s->client->send(get_status.dump());
        }
    }).detach();
}

void GoProMaster::locate(const std::string server, const std::string target){
    int32_t index = haslocate(server, target);
    if(index == -1){
        locates.push_back(std::pair<std::string, std::string>(server, target));
    }else{
        locates.erase(locates.begin() + index);
    }
}

int32_t GoProMaster::haslocate(const std::string server, const std::string target){
    for(int32_t i = 0; i < locates.size(); i++){
        auto& s = locates.at(i);
        if(s.first == server && s.second == target) return i;
    }
    return -1;
}

void GoProMaster::apply(const std::string& ip, const std::string& target, const int32_t id, const int32_t value){
    std::thread([=](){    
        for (auto& s : servers) {
            if (!s->connected) continue;
            json get_status = json::object();
            get_status["key"] = "query";
            get_status["value"] = json::object();
            get_status["value"]["name"] = "set";
            get_status["value"]["source"] = ip;
            get_status["value"]["target"] = target;
            get_status["value"]["id"] = id;
            get_status["value"]["value"] =  std::to_string(value);
            s->client->send(get_status.dump());
        }
    }).detach();
}

void GoProMaster::applyAll(const std::string& ip, const json& res){
    std::thread([=](){    
        for (auto& s : servers) {
            if (!s->connected) continue;
            json get_status = json::object();
            get_status["key"] = "query";
            get_status["value"] = json::object();
            get_status["value"]["source"] = ip;
            get_status["value"]["name"] = "setall";
            get_status["value"]["value"] = res;
            s->client->send(get_status.dump());
        }
    }).detach();
}

void GoProMaster::quickApplyAll(const CameraInfo& target){
    int32_t model = InspectorWindow::_get_current_model(target.hw);
    json root = json::object();
    json _set = json::object();
    json _status = json::object();
    if(getSettingsFromCamera(target, _set) && getStatusFromCamera(target, _status)){
        // Execute the apply logic here
        int32_t p = _status[std::to_string(PRESET_ID)].get<int32_t>();
        root["model"] = model; // Added a model field for mark it's supported
        root["preset"] = p;
        root["setting"] = _set;
        std::cout << "trying apply all, preset: " << p << std::endl;
        applyAll(target.ip, root);
    }
}

void GoProMaster::stopApplyAll(const CameraInfo& target){
    std::thread([=](){    
        for (auto& s : servers) {
            if (!s->connected) continue;
            json get_status = json::object();
            get_status["key"] = "query";
            get_status["value"] = json::object();
            get_status["value"]["name"] = "setall_cancel";
            s->client->send(get_status.dump());
        }
    }).detach();
}

bool GoProMaster::directoryExists(const std::string& path) {
    if (fs::exists(path) && fs::is_directory(path)) {
        return true;
    }
    return false;
}

void GoProMaster::registerCameraMediaListFeedback(camera_media_list_feedback v){
    _camera_media_list_feedback = v;
}

void GoProMaster::registerCameraSettingFeedback(camera_setting_feedback v){
    _camera_setting_feedback = v;
}

void GoProMaster::registerCameraStatusFeedback(camera_status_feedback v){
    _camera_status_feedback = v;
}

void GoProMaster::registerCameraHWFeedback(camera_hw_feedback v){
    _camera_hw_feedback = v;
}

void GoProMaster::registerCameraLogFeedback(camera_log_feedback v){
    _camera_log_feedback = v;
}

void GoProMaster::registerApplyAllFeedback(camera_apply_all_feedback v){
    _camera_apply_all_feedback = v;
}

void GoProMaster::registerSavePreset(camera_preset_save v){
    _camera_preset_save = v;
}

void GoProMaster::set_preset_data(std::shared_ptr<json> _preset){
    preset_ptr = _preset;
}

int32_t GoProMaster::add_preset(const std::string name, json data){
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

bool GoProMaster::get_preset(const std::string name, json& data){
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

bool GoProMaster::remove_preset(const std::string name){
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

std::vector<std::string> GoProMaster::get_preset_names(){
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