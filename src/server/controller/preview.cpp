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

void gopro_controller_preview_on(gopro_controller& controller, const std::string target, const int32_t port) {
    if(target.size() > 0) {
        gopro_controller_local_preview_on(controller, target, port); 
        return;
    }
    std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
    gopro_controller_local_preview_on(controller, buffer, port);
}

void gopro_controller_preview_off(gopro_controller& controller, const std::string target) {
    if(target.size() > 0) {
        gopro_controller_local_preview_off(controller, target); 
        return;
    }
    std::vector<std::string> buffer = gopro_controller_local_element_alives(controller);
    gopro_controller_local_preview_off(controller, buffer);
}
