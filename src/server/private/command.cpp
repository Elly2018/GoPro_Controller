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
#ifdef _WIN32
    #include <windows.h>
#endif
#include "../../common/timezone.h"

void GoProController::_setAllPreset(std::vector<std::string> targets, int32_t mode){
    _getAllResponse(targets, "/gopro/camera/presets/load?id=" + std::to_string(mode));
}

void GoProController::_setPreset(std::string target, int32_t mode){
    _getSingleResponse(target, "/gopro/camera/presets/load?id=" + std::to_string(mode));
}

void gopro_controller_local_reboot(gopro_controller& controller, const std::vector<std::string> targets) {
    _getAllResponse(targets, "/gp/gpControl/command/system/reset");
}

void gopro_controller_local_reboot(gopro_controller& controller, const std::string target){
    _getSingleResponse(target, "/gp/gpControl/command/system/reset");
}

void GoProController::_shutdownAll(std::vector<std::string> targets){
    _getAllResponse(targets, "/gp/gpControl/command/system/shutdown");
}

void GoProController::_shutdown(std::string target){
    _getSingleResponse(target, "/gp/gpControl/command/system/shutdown");
}

void GoProController::_keepAliveAll(std::vector<std::string> targets){
    _getAllResponse(targets, "/gopro/camera/keep_alive");
}

void GoProController::_keepAlive(std::string target){
    _getSingleResponse(target, "/gopro/camera/keep_alive");
}

void GoProController::_usbAll(std::vector<std::string> targets, bool ison){
    std::string url = "/gopro/camera/control/wired_usb?p=";
    if(ison) url += "1";
    else url += "0";
    _getAllResponse(targets, url);
}

void GoProController::_usb(std::string target, bool ison){
    std::string url = "/gopro/camera/control/wired_usb?p=";
    if(ison) url += "1";
    else url += "0";
    _getSingleResponse(target, url);
}

void GoProController::_datetimeAll(std::vector<std::string> targets){
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
    _getAllResponse(targets, url);
}

void GoProController::_datetime(std::string target){
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
    _getSingleResponse(target, url);
}

void GoProController::_zoomAll(std::vector<std::string> targets, int32_t value){
    std::string url = "/gopro/camera/digital_zoom?percent=";
    url += std::to_string(value);
    _getAllResponse(targets, url);
}

void GoProController::_zoom(std::string target, int32_t value){
    std::string url = "/gopro/camera/digital_zoom?percent=";
    url += std::to_string(value);
    _getSingleResponse(target, url);
}

void GoProController::_shutterAll(std::vector<std::string> targets, bool ison){
    std::string url = "/gopro/camera/shutter/";
    if(ison) url += "start";
    else url += "stop";
    _getAllResponse(targets, url);
}

void GoProController::_shutter(std::string target, bool ison){
    std::string url = "/gopro/camera/shutter/";
    if(ison) url += "start";
    else url += "stop";
    _getSingleResponse(target, url);
}

void GoProController::_locate(std::string target, bool ison){
    std::string url = "/gp/gpControl/command/system/locate?p=";
    if(ison) url += "1";
    else url += "0";
    _getSingleResponse(target, url);
}
