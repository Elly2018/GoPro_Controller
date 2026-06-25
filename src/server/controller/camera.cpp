/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_controller.h"
#include "../gopro_controller_local.h"
#include <string>
#include <thread>

void gopro_controller_scanCameras(gopro_controller& controller) {
    if(!controller.mdns_event_registered){
        controller.mdns_event_registered = true;

        auto a1 = [&controller](const std::string& log_msg) {
            const std::string keyword = std::string("gopro");
            const size_t pos = log_msg.find(keyword);
            if(pos != std::string::npos){
                const std::string p = std::string(log_msg.substr(0,13).c_str());
                std::cout << "[MDNS] gopro service found: " << p << "\n";
                const bool find = gopro_controller_local_element_exist(controller, p);
                if(gopro_controller_local_element_have_slot(controller) >= 0) {
                    gopro_controller_local_element_add(controller, p);
                    gopro_controller_local_updateRecord(controller);
                }
            }
        };

        mdns_cpp::Logger::setLoggerSink(a1);
    }

    if(controller.scan_thread_state == Thread_state::PROCESSING) return;
    controller.scan_thread_state = Thread_state::PROCESSING;
    controller.scan_thread = std::thread([&controller](){
        mdns.executeDiscovery();
        controller.scan_thread_state = Thread_state::FINISHED;
    });
}

void gopro_controller_cleanCameras(gopro_controller& controller){
    gopro_controller_local_element_clean(controller);
    gopro_controller_local_updateRecord(controller);
}

void gopro_controller_renameCameras(gopro_controller& controller, const std::string ip, const std::string name) {
    if (gopro_controller_local_element_have_slot(controller) >= 0) {
        int32_t index = gopro_controller_local_element_add(controller, ip);
        if(index >= 0){
            const gopro_element &e = controller.camera_elements.at(index);
            
            uint64_t len = name.copy(e.name, sizeof(e.name) -1);
            e.name[len] = '\0';

            gopro_controller_local_updateRecord(controller);
        }
    }
}

void gopro_controller_addCameras(gopro_controller& controller, const std::string serial) {
    if(serial.size() >= 3){
        const std::string p = GetRemoteIPBySerial(serial);
        if(!gopro_controller_local_element_exist(controller, p)){
            if(gopro_controller_local_element_have_slot(controller) >= 0) {
                gopro_controller_local_element_add(controller, p);
                gopro_controller_local_updateRecord(controller);
            }
        }
    }
}

void gopro_controller_deleteCameras(gopro_controller& controller, const std::string ip) {
    gopro_controller_local_element_remove(controller, ip);
}