/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_controller.h"
#include "../gopro_controller_local.h"
#include <string>
#include <thread>

void gopro_controller_setPreset(gopro_controller& controller, const std::string target, const int32_t mode) noexcept {
    if(target.size() > 0){
        _setPreset(target, mode);
    }else{
        std::vector<std::future<void>> calls = std::vector<std::future<void>>();
        std::vector<std::string> buffer = std::vector<std::string>(camera_alive_ips.size());
        {
            std::lock_guard<std::mutex> lock(ips_alive_mutex);
            std::copy(std::begin(camera_alive_ips), std::end(camera_alive_ips), std::begin(buffer));
        }
        for(std::string ip : buffer){
            calls.push_back(std::async(std::launch::async, [this, ip, mode]() {
                this->_setPreset(ip, mode);
            }));
        }

        for(auto& call : calls){
            call.get();
        }
    }
}

void GoProController::reboot(std::string target){
    if(target.size() > 0) _reboot(target); 
    else {
        std::vector<std::string> buffer = std::vector<std::string>(camera_alive_ips.size());
        {
            std::lock_guard<std::mutex> lock(ips_alive_mutex);
            std::copy(std::begin(camera_alive_ips), std::end(camera_alive_ips), std::begin(buffer));
        }
        _rebootAll(buffer);
    }
}

void GoProController::shutdown(std::string target){
    if(target.size() > 0) _shutdown(target); 
    else {
        std::vector<std::string> buffer = std::vector<std::string>(camera_alive_ips.size());
        {
            std::lock_guard<std::mutex> lock(ips_alive_mutex);
            std::copy(std::begin(camera_alive_ips), std::end(camera_alive_ips), std::begin(buffer));
        }
        _shutdownAll(buffer);
    }
}

void GoProController::keep_alive(std::string target){
    if(target.size() > 0) _keepAlive(target); 
    else {
        std::vector<std::string> buffer = std::vector<std::string>(camera_alive_ips.size());
        {
            std::lock_guard<std::mutex> lock(ips_alive_mutex);
            std::copy(std::begin(camera_alive_ips), std::end(camera_alive_ips), std::begin(buffer));
        }
        _keepAliveAll(buffer);
    }
}

void GoProController::usb(std::string target, bool ison){
    if(target.size() > 0) _usb(target, ison); 
    else {
        std::vector<std::string> buffer = std::vector<std::string>(camera_alive_ips.size());
        {
            std::lock_guard<std::mutex> lock(ips_alive_mutex);
            std::copy(std::begin(camera_alive_ips), std::end(camera_alive_ips), std::begin(buffer));
        }
        _usbAll(buffer, ison);
    }
}

void GoProController::datetime(std::string target){
    if(target.size() > 0) _datetime(target);
    else {
        std::vector<std::string> buffer = std::vector<std::string>(camera_alive_ips.size());
        {
            std::lock_guard<std::mutex> lock(ips_alive_mutex);
            std::copy(std::begin(camera_alive_ips), std::end(camera_alive_ips), std::begin(buffer));
        }
        _datetimeAll(buffer);
    }
}

void GoProController::zoom(std::string target, int32_t value){
    if(target.size() > 0) _zoom(target, value); 
    else {
        std::vector<std::string> buffer = std::vector<std::string>(camera_alive_ips.size());
        {
            std::lock_guard<std::mutex> lock(ips_alive_mutex);
            std::copy(std::begin(camera_alive_ips), std::end(camera_alive_ips), std::begin(buffer));
        }
        _zoomAll(buffer, value);
    }
}

void GoProController::shutter(std::string target, bool isstart){
    if(target.size() > 0) _shutter(target, isstart); 
    else {
        std::vector<std::string> buffer = std::vector<std::string>(camera_alive_ips.size());
        {
            std::lock_guard<std::mutex> lock(ips_alive_mutex);
            std::copy(std::begin(camera_alive_ips), std::end(camera_alive_ips), std::begin(buffer));
        }
        _shutterAll(buffer, isstart);
    }
}
void GoProController::locate(std::string target, bool ison){
    if(target.size() > 0) _locate(target, ison); 
}

std::string GoProController::getAllIP(){
    json result = json::array();
    std::vector<std::string> buffer = std::vector<std::string>(camera_ips.size());
    {
        std::lock_guard<std::mutex> lock(ips_mutex);
        std::copy(std::begin(camera_ips), std::end(camera_ips), std::begin(buffer));
    }
    for(std::string target : buffer){
        if(camera_name.count(target)){
            result.push_back(target + " " + camera_name.at(target));
        }else{
            result.push_back(target);
        }
    }
    return result.dump();
}