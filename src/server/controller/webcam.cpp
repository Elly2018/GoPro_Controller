/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../GoProController.h"
#include <vector>
#include <string>
#include <thread>
#include <future>

void gopro_controller_webcam_mode(gopro_controller& controller, const std::string target) noexcept {
    if(target.size() > 0) _webcamMode(target); 
    else {
        std::lock_guard<std::mutex> lock(ips_mutex);
        _webcamAllMode(camera_ips);
    }
}

void gopro_controller_webcam_mode_off(gopro_controller& controller, const std::string target) noexcept {
    if(target.size() > 0) _webcamUnMode(target); 
    else {
        std::lock_guard<std::mutex> lock(ips_mutex);
        _webcamAllUnMode(camera_ips);
    }
}

void gopro_controller_webcam_on(gopro_controller& controller, const std::string target, const int32_t startPort, const int32_t res, const int32_t fov, const bool TS) noexcept {
    if(target.size() > 0) _webcamOn(target, startPort, res, fov, TS); 
    else {
        std::lock_guard<std::mutex> lock(ips_mutex);
        _webcamAllOn(camera_ips, startPort, res, fov, TS);
    }
}

void gopro_controller_webcam_off(gopro_controller& controller, const std::string target) noexcept {
    if(target.size() > 0) _webcamOff(target); 
    else {
        std::lock_guard<std::mutex> lock(ips_mutex);
        _webcamAllOff(camera_ips);
    }
}

json gopro_controller_webcam_status(gopro_controller& controller, const std::string target) noexcept {
    json res;
    std::string address;
    json arr = json::array();
    if(target.size() > 0){
        json res;
        try{
            SingleResponse result = _webcamStatus(target);
            address = result.first;
            res = json::parse(result.second);
        }catch(const std::exception& ex){
            res = json::object();
        }
        json i;
        i["ip"] = address;
        i["status"] = res;
        arr.push_back(i);
    }else{
        std::vector<std::future<SingleResponse>> calls = std::vector<std::future<SingleResponse>>();
        std::vector<std::string> buffer = std::vector<std::string>(camera_alive_ips.size());
        {
            std::lock_guard<std::mutex> lock(ips_alive_mutex);
            std::copy(std::begin(camera_alive_ips), std::end(camera_alive_ips), std::begin(buffer));
        }
        for(std::string ip : buffer){
            calls.push_back(std::async(std::launch::async, [this, ip]() {
                return _webcamStatus(ip);
            }));
        }

        for(auto& call : calls){
            try{
                SingleResponse result = call.get();
                address = result.first;
                res = json::parse(result.second);
            }catch(const std::exception& ex){
                res = json::object();
            }
            json i;
            i["ip"] = address;
            i["status"] = res;
            arr.push_back(i);
        }
    }
    return arr.dump();
}

json gopro_controller_webcam_version(gopro_controller& controller, const std::string target) noexcept {
    json res;
    std::string address;
    json arr = json::array();
    if(target.size() > 0){
        json res;
        try{
            SingleResponse result = _webcamVersion(target);
            address = result.first;
            res = json::parse(result.second);
        }catch(const std::exception& ex){
            res = json::object();
        }
        json i;
        i["ip"] = address;
        i["status"] = res;
        arr.push_back(i);
    }else{
        std::vector<std::future<SingleResponse>> calls = std::vector<std::future<SingleResponse>>();
        std::vector<std::string> buffer = std::vector<std::string>(camera_alive_ips.size());
        {
            std::lock_guard<std::mutex> lock(ips_alive_mutex);
            std::copy(std::begin(camera_alive_ips), std::end(camera_alive_ips), std::begin(buffer));
        }
        for(std::string ip : buffer){
            calls.push_back(std::async(std::launch::async, [this, ip]() {
                return _webcamVersion(ip);
            }));
        }

        for(auto& call : calls){
            try{
                SingleResponse result = call.get();
                address = result.first;
                res = json::parse(result.second);
            }catch(const std::exception& ex){
                res = json::object();
            }
            json i;
            i["ip"] = address;
            i["status"] = res;
            arr.push_back(i);
        }
    }
    return arr.dump();
}
