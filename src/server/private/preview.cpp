/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_controller_local.h"
#include "../gopro_controller.h"
#include <vector>
#include <string>

void gopro_controller_local_preview_on(gopro_controller& controller, const std::vector<std::string> targets, const int32_t port){
    gopro_controller_local_get_responses(controller, targets, "/gopro/camera/stream/start?port=" + std::to_string(port));
}

void gopro_controller_local_preview_on(gopro_controller& controller, const std::string target, const int32_t port){
    gopro_controller_local_get_response(controller, target, "/gopro/camera/stream/start?port=" + std::to_string(port));
}

void gopro_controller_local_preview_off(gopro_controller& controller, const std::vector<std::string> targets){
    gopro_controller_local_get_responses(controller, targets, "/gopro/camera/stream/stop");
}

void gopro_controller_local_preview_off(gopro_controller& controller, const std::string target){
    gopro_controller_local_get_response(controller, target, "/gopro/camera/stream/stop");
}
