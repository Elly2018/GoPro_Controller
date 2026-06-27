/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "scan_camera_popwin.h"
#include "../gopro_master.h"

void scan_camera_popup_render(Scan_camera_popup& win) {
    if(ImGui::BeginPopupModal(win.base.base.title, NULL, wp_flag)){
        bool updated = false;
        updated = ImGui::InputText("Server IP", &win.server_ip_buf, sizeof(win.server_ip_buf));
        ImGui::Text("You can leave it empty for broadcast to all websocket server");
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", error.c_str());
        if(updated){
            error.clear();
        }
        if (ImGui::Button("Confirm")) {
            bool pass = true;
            int32_t fs = gopro_master_find_server(win.base.base.state.appdata, std::string(win.server_ip_buf));
            if(fs == -1 && strlen(win.server_ip_buf) == 0){
                win.error = "Server does not exist.";
                pass = false;
            }

            if(pass){
                if(strlen(win.server_ip_buf) == 0){
                    master->command_only("scan");
                }else{
                    master->command_only(std::string(win.server_ip_buf), "scan", "");
                }
            }
        }
        ImGui::SameLine();
        if(ImGui::Button("Cancel")){
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();               
    }
}