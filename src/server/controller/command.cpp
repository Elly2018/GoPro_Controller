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

void gopro_controller_set_preset(gopro_controller& controller, const std::string target, const int32_t mode) noexcept {
    if(target.size() > 0){
        gopro_controller_local_set_sreset(controller, target, mode);
        return;
    }
    std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
    gopro_controller_local_set_preset(controller, buffer, mode);
}

void gopro_controller_reboot(gopro_controller& controller, const std::string target) noexcept {
    if(target.size() > 0) {
        gopro_controller_local_reboot(controller, target); 
        return;
    }
    std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
    gopro_controller_local_reboot(controller, buffer);
}

void gopro_controller_shutdown(gopro_controller& controller, const std::string target) noexcept {
    if(target.size() > 0) {
        gopro_controller_local_shutdown(controller, target);
        return;
    }
    std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
    gopro_controller_local_shutdown(controller, buffer);
}

void gopro_controller_keep_alive(gopro_controller& controller, const std::string target) noexcept {
    if(target.size() > 0) {
        gopro_controller_local_keep_alive(controller, target);
        return;
    }
    std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
    gopro_controller_local_keep_alive(controller, buffer);
}

void gopro_controller_usb(gopro_controller& controller, const std::string target, const bool is_on) noexcept {
    if(target.size() > 0) {
        gopro_controller_local_usb(controller, target, is_on);
        return;
    }
    std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
    gopro_controller_local_usb(controller, buffer, is_on);
}

void gopro_controller_datetime(gopro_controller& controller, const std::string target) noexcept {
    if(target.size() > 0) {
        gopro_controller_local_datetime(controller, target);
        return;
    }
    std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
    gopro_controller_local_datetime(controller, buffer);
}

void gopro_controller_zoom(gopro_controller& controller, const std::string target, const int32_t value) noexcept {
    if(target.size() > 0) {
        gopro_controller_local_zoom(controller, target, value);
        return;
    }
    std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
    gopro_controller_local_zoom(controller, buffer, value);
}

void gopro_controller_shutter(gopro_controller& controller, const std::string target, const bool is_start) noexcept {
    if(target.size() > 0) {
        gopro_controller_local_shutter(controller, target, is_start);
        return;
    }
    std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
    gopro_controller_local_shutter(controller, buffer, is_start);
}

void gopro_controller_locate(gopro_controller& controller, const std::string target, const bool is_on) noexcept {
    if(target.size() > 0) {
        gopro_controller_local_locate(target, is_on); 
    }
}

json gopro_controller_get_IPs(gopro_controller& controller) noexcept {
    json result = json::array();
    for(int32_t i = 0; i < controller.client_limit; i++){
        const gopro_element &e = controller.camera_elements.at(i);
        if(!e.exist) continue;
        if(strlen(e.name) > 0){
            result.push_back(std::string(e.ip) + " " + std::string(e.name));
        }else{
            result.push_back(std::string(e.ip));
        }
    }
    return result;
}