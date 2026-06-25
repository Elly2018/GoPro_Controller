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
#include <thread>
#include <future>

void gopro_controller_webcam_mode(gopro_controller& controller, const std::string target) {
    if(target.size() > 0) {
        gopro_controller_local_webcam_mode(controller, target); 
        return;
    }
    std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
    gopro_controller_local_webcam_mode(controller, buffer); 
}

void gopro_controller_webcam_mode_off(gopro_controller& controller, const std::string target) {
    if(target.size() > 0) {
        gopro_controller_local_webcam_mode_off(controller, target); 
        return;
    }
    std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
    gopro_controller_local_webcam_mode_off(controller, buffer); 
}

void gopro_controller_webcam_on(gopro_controller& controller, const std::string target, const int32_t start_port, const int32_t res, const int32_t fov, const bool ts) {
    if(target.size() > 0) {
        gopro_controller_local_webcam_on(controller, target, start_port, res, fov, ts); 
        return;
    }
    std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
    gopro_controller_local_webcam_on(controller, buffer, start_port, res, fov, ts); 
}

void gopro_controller_webcam_off(gopro_controller& controller, const std::string target) {
    if(target.size() > 0) {
        gopro_controller_local_webcam_off(controller, target); 
        return;
    }
    std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
    gopro_controller_local_webcam_off(controller, buffer); 
}

json gopro_controller_webcam_status(gopro_controller& controller, const std::string target) {
    json arr = json::array();
    if(target.size() > 0){
        SingleResponse result = gopro_controller_local_webcam_status(controller, target);
        json buff;
        buff["ip"] = result.first;
        buff["status"] = result.second;
        arr.push_back(buff);
    }else{
        std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
        std::vector<SingleResponse> results = gopro_controller_local_webcam_status(controller, buffer);

        for(int32_t i = 0; i < results.size(); i++){
            json buff = json::object();
            buff["ip"] = results[i].first;
            buff["status"] = results[i].second;
            arr.push_back(buff);
        }
    }
    return arr;
}

json gopro_controller_webcam_version(gopro_controller& controller, const std::string target) {
    json res;
    std::string address;
    json arr = json::array();
    if(target.size() > 0){
        SingleResponse result = gopro_controller_local_webcam_version(controller, target);
        json buff;
        buff["ip"] = result.first;
        buff["status"] = result.second;
        arr.push_back(buff);
    }else{
        std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
        std::vector<SingleResponse> results = gopro_controller_local_webcam_version(controller, buffer);

        for(int32_t i = 0; i < results.size(); i++){
            json buff = json::object();
            buff["ip"] = results[i].first;
            buff["status"] = results[i].second;
            arr.push_back(buff);
        }
    }
    return arr;
}
