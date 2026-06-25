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

void gopro_controller_local_webcam_mode(gopro_controller& controller, const std::vector<std::string> targets){
    gopro_controller_local_get_responses(controller, targets, "/gopro/webcam/preview");
}

void gopro_controller_local_webcam_mode(gopro_controller& controller, const std::string target){
    gopro_controller_local_get_response(controller, target, "/gopro/webcam/preview");
}

void gopro_controller_local_webcam_mode_off(gopro_controller& controller, const std::vector<std::string> targets){
    gopro_controller_local_get_responses(controller, targets, "/gopro/webcam/exit");
}

void gopro_controller_local_webcam_mode_off(gopro_controller& controller, const std::string target){
    gopro_controller_local_get_response(controller, target, "/gopro/webcam/exit");
}

void gopro_controller_local_webcam_on(gopro_controller& controller, const std::vector<std::string> targets, const int32_t startPort, const int32_t res, const int32_t fov, const bool TS){
    std::string url = "/gopro/webcam/start?res=";
    url += std::to_string(res);
    url += "&fov=";
    url += std::to_string(fov);
    url += "&port=";
    url += std::to_string(startPort);
    if(TS){
        url += "&protocol=TS";
    }else{
        url += "&protocol=RTSP";
    }
    gopro_controller_local_get_responses(controller, targets, url);
}

void gopro_controller_local_webcam_on(gopro_controller& controller, const std::string target, const int32_t startPort, const int32_t res, const int32_t fov, const bool TS){
    std::string url = "/gopro/webcam/start?res=";
    url += std::to_string(res);
    url += "&fov=";
    url += std::to_string(fov);
    url += "&port=";
    url += std::to_string(startPort);
    if(TS){
        url += "&protocol=TS";
    }else{
        url += "&protocol=RTSP";
    }
    gopro_controller_local_get_response(controller, target, url);
}

void gopro_controller_local_webcam_off(gopro_controller& controller, const std::vector<std::string> targets){
    gopro_controller_local_get_responses(controller, targets, "/gopro/webcam/stop");
}

void gopro_controller_local_webcam_off(gopro_controller& controller, const std::string target){
    gopro_controller_local_get_response(controller, target, "/gopro/webcam/stop");
}

SingleResponse gopro_controller_local_webcam_status(gopro_controller& controller, const std::string target){
    return gopro_controller_local_get_response(controller, target, "/gopro/webcam/status");
}

SingleResponse gopro_controller_local_webcam_version(gopro_controller& controller, const std::string target){
    return gopro_controller_local_get_response(controller, target, "/gopro/webcam/version");
}
