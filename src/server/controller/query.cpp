/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_controller.h"
#include "../gopro_controller_local.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

json gopro_controller_query_status(gopro_controller& controller, const std::string target) noexcept{
    json arr = json::array();
    json res = json::object();
    json hw = json::object();
    if(target.size() > 0){
        SingleResponse status_result = gopro_controller_local_query_status(target);
        SingleResponse hw_result = gopro_controller_local_query_hw(target);
        json i = json::object();
        i["ip"] = status_result.first;
        i["status"] = status_result.second;
        i["hw"] = hw_result.second;
        gopro_controller_local_element_set_hw(controller, status_result.first, hw_result.second);
        arr.push_back(i);
    }
    else{
        std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
        std::vector<SingleResponse> status_result = gopro_controller_local_query_status(buffer);
        std::vector<SingleResponse> hw_result = gopro_controller_local_query_hw(buffer);
        for(int32_t i = 0; i < status_result.size(); i++){
            json j = json::object();
            j["ip"] = status_result[i].first;
            j["status"] = status_result[i].second;
            j["hw"] = hw_result[i].second;
            gopro_controller_local_element_set_hw(controller, status_result.first, hw_result.second);
            arr.push_back(j);
        }
    }
    return arr;
}

json gopro_controller_set_setting(gopro_controller& controller, const std::string target, const int32_t ID, const std::string value) noexcept {
    json arr = json::array();
    json res = json::object();
    std::string address = "";
    if(target.size() > 0){
        SingleResponse result = _setSetting(target, ID, value);
        address = result.first;
        bool vaild = json::accept(result.second);
        if(vaild){
            res = json::parse(result.second);
        }else{
            res = json::object();
            std::cerr << "[ERROR] setSetting: res parser error" << std::endl;
        }
        json i = json::object();
        i["ip"] = target;
        i["status"] = res;
        arr.push_back(i);
    }else{
        std::vector<std::string> buffer = std::vector<std::string>(camera_alive_ips.size());
        {
            std::lock_guard<std::mutex> lock(ips_alive_mutex);
            std::copy(std::begin(camera_alive_ips), std::end(camera_alive_ips), std::begin(buffer));
        }
        std::vector<SingleResponse> results = _setAllSetting(buffer, ID, value);
        for(int32_t i = 0; i < results.size(); i++){
            address = results[i].first;
            bool vaild = json::accept(results[i].second);
            if(vaild){
                res = json::parse(results[i].second);
            }else{
                res = json::object();
                std::cerr << "[ERROR] setSetting: res parser error" << std::endl;
            }
            json j = json::object();
            j["ip"] = address;
            j["status"] = res;
            arr.push_back(j);
        }
    }
    return arr.dump();
}

json gopro_controller_set_setting(gopro_controller& controller, const std::string source, const std::string target, const int32_t preset, const json value) noexcept {
    json arr = json::array();
    json res = json::object();
    applying_cancel = false;
    std::string address = "";
    if(target.size() > 0){ // Apply to single target
        std::vector<SingleResponse> results = _setSetting(target, preset, value);
        for(int32_t i = 0; i < results.size(); i++){
            if(applying_cancel) continue;
            address = results[i].first;
            bool vaild = json::accept(results[i].second);
            if(vaild){
                res = json::parse(results[i].second);
            }else{
                res = json::object();
                std::cerr << "[ERROR] setSettingAll: res parser error" << std::endl;
            }
            json j = json::object();
            j["ip"] = address;
            j["status"] = res;
            arr.push_back(j);
        }
    }else{ // Apply to all
        std::vector<std::string> buffer = std::vector<std::string>();
        {
            std::lock_guard<std::mutex> lock(ips_alive_mutex);
            for(int32_t i = 0; i < camera_alive_ips.size(); i++){
                if(camera_alive_ips[i] != source) buffer.push_back(camera_alive_ips[i]);
            }
        }
        std::vector<SingleResponse> results = _setAllSetting(buffer, preset, value);
        std::cout << "[LOG] next step of setSettingAll" << std::endl;
        for(int32_t i = 0; i < results.size(); i++){
            if(applying_cancel) continue;
            address = results[i].first;
            bool vaild = json::accept(results[i].second);
            if(vaild){
                res = json::parse(results[i].second);
            }else{
                res = json::object();
                std::cerr << "[ERROR] setSettingAll: res parser error" << std::endl;
            }
            json j = json::object();
            j["ip"] = address;
            j["status"] = res;
            arr.push_back(j);
        }
    }
    std::cout << "[LOG] before response with arr.dump()" << std::endl;
    return arr.dump();
}

void gopro_controller_set_setting_cancel(gopro_controller& controller) noexcept {
    controller.applying_cancel = true;
}