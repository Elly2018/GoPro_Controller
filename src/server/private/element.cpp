/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_controller_local.h"
#include "../gopro_controller.h"
#include <string>

bool gopro_controller_local_element_exist(gopro_controller& controller, const std::string ip, bool should_be_alive) {
    for(int32_t i = 0; i < controller.client_limit; i++){
        const gopro_element &e = controller.camera_elements.at(i);
        if(!e.exist) continue;
        if(should_be_alive && !e.alive) continue;
        if(e.ip == ip) return true;
    }
    return false;
}

int32_t gopro_controller_local_element_add(gopro_controller& controller, const std::string ip) {
    for(int32_t i = 0; i < controller.client_limit; i++){
        gopro_element &e = controller.camera_elements.at(i);
        if(e.exist) continue;

        uint64_t len = ip.copy(e.ip, sizeof(e.ip) - 1);
        e.ip[len] = '\0';

        e.alive = false;
        return i;
    }
    return -1;
}

bool gopro_controller_local_element_remove(gopro_controller& controller, const std::string ip) {
    for(int32_t i = 0; i < controller.client_limit; i++){
        gopro_element &e = controller.camera_elements.at(i);
        if(!e.exist) continue;
        if(e.ip == ip) {
            e.alive = false;
            e.exist = false;
            return true;
        }
    }
    return false;
}

bool gopro_controller_local_element_clean(gopro_controller& controller) {
    for(int32_t i = 0; i < controller.client_limit; i++){
        gopro_element &e = controller.camera_elements.at(i);
        e.exist = false;
    }
    return true;
}

int32_t gopro_controller_local_element_have_slot(gopro_controller& controller) {
    for(int32_t i = 0; i < controller.client_limit; i++){
        const gopro_element &e = controller.camera_elements.at(i);
        if(!e.exist) return i;
    }
    return -1;
}

int32_t gopro_controller_local_element_find(gopro_controller& controller, const std::string ip) {
    for(int32_t i = 0; i < controller.client_limit; i++){
        const gopro_element &e = controller.camera_elements.at(i);
        if(!e.exist) continue;
        if(e.ip == ip) return i;
    }
    return -1;
}

std::vector<std::string> gopro_controller_local_element_alives(gopro_controller& controller) {
    std::vector<std::string> buffer;
    for(int32_t i = 0; i < controller.client_limit; i++){
        const gopro_element &e = controller.camera_elements.at(i);
        if(!e.exist || !e.alive) continue;
        buffer.push_back(e.ip);
    }
    return buffer;
}

void gopro_controller_local_element_set_hw(gopro_controller& controller, const std::string ip, json value) {
    int32_t index = gopro_controller_local_element_find(controller, ip);
    if(index == -1) return;

    gopro_element &e = controller.camera_elements.at(index);

    std::string dumped = value.dump();

    uint64_t len = dumped.copy(e.hw, sizeof(e.hw) - 1);
    e.hw[len] = '\0';
}

json gopro_controller_local_element_get_hw(gopro_controller& controller, const std::string ip) {
    int32_t index = gopro_controller_local_element_find(controller, ip);
    if(index == -1) return json::object();

    const gopro_element &e = controller.camera_elements.at(index);
    const std::string_view buff = std::string(e.hw);
    if(!json::accept(buff)) {
        return json::object();
    }

    return json::parse(buff);
}