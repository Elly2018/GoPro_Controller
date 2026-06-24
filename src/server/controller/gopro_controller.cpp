/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../GoProController.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <future>
#include "icmplib.h"

void gopro_controller_init(gopro_controller& controller) noexcept {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    _loadRecord();
}

void gopro_controller_dispose(gopro_controller& controller) noexcept {

}

void gopro_controller_update(gopro_controller& controller) noexcept {
    std::vector<std::string> fine = std::vector<std::string>();
    std::vector<std::string> buffer = std::vector<std::string>();
    {
        std::lock_guard lock(ips_mutex);
        buffer = std::vector<std::string>(camera_ips.begin(), camera_ips.end());
    }
    
    for(int32_t i = 0; i < buffer.size(); i++){
        auto ping = icmplib::Ping(icmplib::IPAddress(buffer.at(i)), ICMPLIB_TIMEOUT_1S);
        bool connected = ping.delay != ICMPLIB_TIMEOUT_1S || ping.response == icmplib::PingResponseType::Success || ping.response == icmplib::PingResponseType::Unreachable; 
        if(connected){
            fine.push_back(buffer.at(i));
        }
    }

    {
        std::lock_guard lock(ips_alive_mutex);
        camera_alive_ips = fine;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(ICMPLIB_TIMEOUT_1S));
}
