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

json gopro_controller_query_status(gopro_controller& controller, const std::string target){
    json arr = json::array();
    if(target.size() > 0){
        SingleResponse status_result = gopro_controller_local_query_status(controller, target);
        SingleResponse hw_result = gopro_controller_local_query_HW(controller, target);
        json buff = json::object();
        buff["ip"] = status_result.first;
        buff["status"] = status_result.second;
        buff["hw"] = hw_result.second;
        gopro_controller_local_element_set_HW(controller, status_result.first, hw_result.second);
        arr.push_back(buff);
    }
    else{
        std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
        std::vector<SingleResponse> status_result = gopro_controller_local_query_status(controller, buffer);
        std::vector<SingleResponse> hw_result = gopro_controller_local_query_HW(controller, buffer);
        for(int32_t i = 0; i < status_result.size(); i++){
            json buff = json::object();
            buff["ip"] = status_result.at(i).first;
            buff["status"] = status_result.at(i).second;
            buff["hw"] = hw_result.at(i).second;
            gopro_controller_local_element_set_HW(controller, status_result.at(i).first, hw_result.at(i).second);
            arr.push_back(buff);
        }
    }
    return arr;
}

json gopro_controller_set_setting(gopro_controller& controller, const std::string target, const int32_t ID, const std::string value) {
    json arr = json::array();
    if(target.size() > 0){
        SingleResponse result = gopro_controller_local_set_setting(controller, target, ID, value);
        json buff = json::object();
        buff["ip"] = result.first;
        buff["status"] = result.second;
        arr.push_back(buff);
    }else{
        std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
        std::vector<SingleResponse> results = gopro_controller_local_set_setting(controller, buffer, ID, value);
        for(int32_t i = 0; i < results.size(); i++){
            json buff = json::object();
            buff["ip"] = results[i].first;
            buff["status"] = results[i].second;
            arr.push_back(buff);
        }
    }
    return arr;
}

json gopro_controller_set_setting_preset(gopro_controller& controller, const std::string source, const std::string target, const int32_t preset, const json value) {
    json arr = json::array();
    controller.applying_cancel = false;
    if(target.size() > 0){ 
        std::vector<SingleResponse> results = gopro_controller_local_set_setting_preset(controller, target, preset, value);
        for(int32_t i = 0; i < results.size(); i++){
            if(controller.applying_cancel) continue;
            json buff = json::object();
            buff["ip"] = results[i].first;
            buff["status"] = results[i].second;
            arr.push_back(buff);
        }
    }else{
        std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
        std::vector<SingleResponse> results = gopro_controller_local_set_setting_preset(controller, buffer, preset, value);
        std::cout << "[LOG] next step of setSettingAll" << std::endl;
        for(int32_t i = 0; i < results.size(); i++){
            if(controller.applying_cancel) continue;
            json buff = json::object();
            buff["ip"] = results[i].first;
            buff["status"] = results[i].second;
            arr.push_back(buff);
        }
    }
    return arr;
}

void gopro_controller_set_setting_cancel(gopro_controller& controller) {
    controller.applying_cancel = true;
}