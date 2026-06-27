/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../gopro_master.h"
#include "../data/server_connection.h"
#include "../data/app.h"
#include <imgui.h>

void gopro_master_clean_cameras_from_server(AppData& data, const std::string server) {
    std::vector<Camera_info>::iterator iter = std::find_if(
        data.master.cameras.begin(),
        data.master.cameras.end(),
        [=](const Camera_info& s) {
            return s.server == server;
        }
    );

    while(iter != data.master.cameras.end()) {
        data.master.cameras.erase(iter);
        iter = std::find_if(
            data.master.cameras.begin(),
            data.master.cameras.end(),
            [=](const Camera_info& s) {
                return s.server == server;
            }
        );
    }
}

void gopro_master_replace_camera_from_server(AppData& data, const std::string server, const std::vector<std::string> ips) {
    std::vector<Camera_info>::iterator it = std::remove_if(
        data.master.cameras.begin(), 
        data.master.cameras.end(), 
        [=](const Camera_info& c) {
            if(c.server == server){
                return std::find(
                    ips.begin(),
                    ips.end(),
                    c.ip
                ) == ips.end();
            }
            return false;
        }
    );

    data.master.cameras.erase(it, data.master.cameras.end());

    for (const std::string& new_ip : ips) {
        bool exists = false;
        for(const Camera_info& existing_cam : data.master.cameras) {
            if (existing_cam && existing_cam.ip == new_ip && existing_cam.server == server) {
                exists = true;
                break;
            }
        }

        if(exists) continue;

        Camera_info new_cam = Camera_info();
        new_cam.server = server;
        new_cam.ip = new_ip;
        cameras.push_back(new_cam);
        {
            ImGuiToast toast(ImGuiToastType_Success, 3000);
            toast.set_title("New IP Detected");
            toast.set_content("Detected ip: %s, from server: %s", new_ip.c_str(), server.c_str());
            ImGui::InsertNotification(toast);
        }
    }
}
