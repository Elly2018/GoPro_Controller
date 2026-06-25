/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_controller_local.h"
#include "../gopro_controller.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include <future>
#include <ctime>
#include "../../common/timezone.h"

void gopro_controller_local_set_preset(gopro_controller& controller, const std::vector<std::string> targets, const int32_t mode) {
    gopro_controller_local_get_responses(controller, targets, "/gp/gpControl/command/system/reset");
}

void gopro_controller_local_set_preset(gopro_controller& controller, const std::string target, const int32_t mode) {
    gopro_controller_local_get_response(controller, target, "/gopro/camera/presets/load?id=" + std::to_string(mode));
}

void gopro_controller_local_reboot(gopro_controller& controller, const std::vector<std::string> targets) {
    gopro_controller_local_get_responses(controller, targets, "/gp/gpControl/command/system/reset");
}

void gopro_controller_local_reboot(gopro_controller& controller, const std::string target) {
    gopro_controller_local_get_response(controller, target, "/gp/gpControl/command/system/reset");
}

void gopro_controller_local_shutdown(gopro_controller& controller, const std::vector<std::string> targets){
    gopro_controller_local_get_responses(controller, targets, "/gp/gpControl/command/system/shutdown");
}

void gopro_controller_local_shutdown(gopro_controller& controller, const std::string target){
    gopro_controller_local_get_response(controller, target, "/gp/gpControl/command/system/shutdown");
}

void gopro_controller_local_keep_alive(gopro_controller& controller, const std::vector<std::string> targets){
    gopro_controller_local_get_responses(controller, targets, "/gopro/camera/keep_alive");
}

void gopro_controller_local_keep_alive(gopro_controller& controller, const std::string target){
    gopro_controller_local_get_response(controller, target, "/gopro/camera/keep_alive");
}

void gopro_controller_local_usb(gopro_controller& controller, const std::vector<std::string> targets, const bool ison){
    std::string url = "/gopro/camera/control/wired_usb?p=";
    if(ison) url += "1";
    else url += "0";
    gopro_controller_local_get_responses(controller, targets, url);
}

void gopro_controller_local_usb(gopro_controller& controller, const std::string target, const bool ison){
    std::string url = "/gopro/camera/control/wired_usb?p=";
    if(ison) url += "1";
    else url += "0";
    gopro_controller_local_get_response(controller, target, url);
}

void gopro_controller_local_datetime(gopro_controller& controller, const std::vector<std::string> targets){
    const auto now = std::chrono::system_clock::now();
    const std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);

    std::ostringstream date;
    std::ostringstream time;
    date << std::put_time(&tm, "%Y_%m_%d");
    time << std::put_time(&tm, "%H_%M_%S");
    int32_t minutes = get_timezone_offset_minutes();

    std::string url = "/gopro/camera/set_date_time?date=";
    url += date.str();
    url += "&time=";
    url += time.str();
    url += "&tzone=";
    url += std::to_string(minutes);
    url += "&dst=0";
    gopro_controller_local_get_responses(controller, targets, url);
}

void gopro_controller_local_datetime(gopro_controller& controller, const std::string target){
    const auto now = std::chrono::system_clock::now();
    const std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);

    std::ostringstream date;
    std::ostringstream time;
    date << std::put_time(&tm, "%Y_%m_%d");
    time << std::put_time(&tm, "%H_%M_%S");
    int32_t minutes = get_timezone_offset_minutes();

    std::string url = "/gopro/camera/set_date_time?date=";
    url += date.str();
    url += "&time=";
    url += time.str();
    url += "&tzone=";
    url += std::to_string(minutes);
    url += "&dst=0";
    gopro_controller_local_get_response(controller, target, url);
}

void gopro_controller_local_zoom(gopro_controller& controller, const std::vector<std::string> targets, const int32_t value){
    std::string url = "/gopro/camera/digital_zoom?percent=";
    url += std::to_string(value);
    gopro_controller_local_get_responses(controller, targets, url);
}

void gopro_controller_local_zoom(gopro_controller& controller, const std::string target, int32_t value){
    std::string url = "/gopro/camera/digital_zoom?percent=";
    url += std::to_string(value);
    gopro_controller_local_get_response(controller, target, url);
}

void gopro_controller_local_shutter(gopro_controller& controller, const std::vector<std::string> targets, const bool is_start){
    std::string url = "/gopro/camera/shutter/";
    if(is_start) url += "start";
    else url += "stop";
    gopro_controller_local_get_responses(controller, targets, url);
}

void gopro_controller_local_shutter(gopro_controller& controller, const std::string target, const bool is_start){
    std::string url = "/gopro/camera/shutter/";
    if(is_start) url += "start";
    else url += "stop";
    gopro_controller_local_get_response(controller, target, url);
}

void gopro_controller_local_locate(gopro_controller& controller, std::string target, bool ison){
    std::string url = "/gp/gpControl/command/system/locate?p=";
    if(ison) url += "1";
    else url += "0";
    gopro_controller_local_get_response(controller, target, url);
}
