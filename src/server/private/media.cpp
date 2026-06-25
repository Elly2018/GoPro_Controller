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

std::vector<SingleResponse> gopro_controller_local_get_media_list(gopro_controller& controller, const std::vector<std::string> targets){
    return gopro_controller_local_get_responses(controller, targets, "/gopro/media/list");
}

SingleResponse gopro_controller_local_get_media_list(gopro_controller& controller, const std::string target){
    return gopro_controller_local_get_response(controller, target, "/gopro/media/list");
}

std::vector<SingleResponse> gopro_controller_local_get_last_media(gopro_controller& controller, const std::vector<std::string> targets){
    return gopro_controller_local_get_responses(controller, targets, "/gopro/media/last_captured");
}

SingleResponse gopro_controller_local_get_last_media(gopro_controller& controller, const std::string target){
    return gopro_controller_local_get_response(controller, target, "/gopro/media/last_captured");
}
