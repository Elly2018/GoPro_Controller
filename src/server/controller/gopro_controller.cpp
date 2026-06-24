/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_controller.h"
#include "../gopro_controller_local.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <future>
#include "icmplib.h"

void gopro_controller_init(gopro_controller& controller) noexcept {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    controller.ping_thread = std::thread(gopro_controller_ping, controller)
    controller.ping_thread_state = Thread_state::PROCESSING;
    gopro_controller_local_loadRecord(controller);
}

void gopro_controller_dispose(gopro_controller& controller) noexcept {
    controller.shutdown = true;
    if(controller.ping_thread.joinable()){
        controller.ping_thread.join();
    }
}

void gopro_controller_update(gopro_controller& controller) noexcept {
    
}

void gopro_controller_ping(gopro_controller& controller) noexcept {
    while(!controller.shutdown) {
        for(int32_t i = 0; i < controller.client_limit; i++){
            const gopro_element &e = controller.camera_elements.at(i);
            if(!e.exist) continue;
            auto ping = icmplib::Ping(icmplib::IPAddress(e.ip), ICMPLIB_TIMEOUT_1S);
            bool connected = ping.delay != ICMPLIB_TIMEOUT_1S || ping.response == icmplib::PingResponseType::Success || ping.response == icmplib::PingResponseType::Unreachable; 
            e.alive = connected;
        }
    }
}
