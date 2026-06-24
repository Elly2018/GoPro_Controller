/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_controller_local.h"
#include "../gopro_controller.h"

bool gopro_controller_local_element_exist(gopro_controller& controller, const std::string ip, bool should_be_alive) noexcept {
    for(int32_t i = 0; i < controller.client_limit; i++){
        const gopro_element &e = controller.camera_elements.at(i);
        if(!e.exist) continue;
        if(should_be_alive && !e.alive) continue;
        if(e.ip == ip) return true;
    }
    return false;
}

int32_t gopro_controller_local_element_add(gopro_controller& controller, const std::string ip) noexcept {
    for(int32_t i = 0; i < controller.client_limit; i++){
        const gopro_element &e = controller.camera_elements.at(i);
        if(e.exist) continue;

        uint64_t len = ip.copy(e.ip, sizeof(e.ip) - 1);
        e.ip[len] = '\0';

        e.alive = false;
        return i;
    }
    return -1;
}

bool gopro_controller_local_element_remove(gopro_controller& controller, const std::string ip) noexcept {
    for(int32_t i = 0; i < controller.client_limit; i++){
        const gopro_element &e = controller.camera_elements.at(i);
        if(!e.exist) continue;
        if(e.ip == ip) {
            e.alive = false;
            e.exist = false;
            return true;
        }
    }
    return false;
}

bool gopro_controller_local_element_clean(gopro_controller& controller) noexcept {
    for(int32_t i = 0; i < controller.client_limit; i++){
        const gopro_element &e = controller.camera_elements.at(i);
        e.exist = false;
    }
    return true;
}

int32_t gopro_controller_local_element_have_slot(gopro_controller& controller) noexcept {
    for(int32_t i = 0; i < controller.client_limit; i++){
        const gopro_element &e = controller.camera_elements.at(i);
        if(!e.exist) return i;
    }
    return -1;
}

int32_t gopro_controller_local_element_find(gopro_controller& controller, const std::string ip) noexcept {
    for(int32_t i = 0; i < controller.client_limit; i++){
        const gopro_element &e = controller.camera_elements.at(i);
        if(!e.exist) continue;
        if(e.ip == ip) return i;
    }
    return -1;
}

#endif