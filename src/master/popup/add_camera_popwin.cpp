/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "add_camera_popwin.h"

void add_camera_popup_render(Add_camera_popup& win) {
    if(ImGui::BeginPopupModal(&win.base.base.title, NULL, wp_flag)){
        const std::vector<ServerConnection> all_servers = master->getServers_Clone();
        bool updated = false;
        if(ImGui::BeginCombo("Server IP", server_ip_buf.c_str())){
            for (int n = 0; n < all_servers.size(); n++)
            {
                std::string option = all_servers.at(n).ip;
                bool is_selected = all_servers.at(n).ip == server_ip_buf;
                option += "##PopupServerOption"; 
                ImGui::BeginDisabled(!all_servers.at(n).connected);
                if (ImGui::Selectable(option.c_str(), is_selected))
                {
                    server_ip_buf = all_servers.at(n).ip;
                }
                ImGui::EndDisabled();
                if (is_selected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }
        updated = ImGui::InputText("Camera Serial", &camera_serial_buf);
        if(ImGui::IsItemHovered()){
            ImGui::SetItemTooltip("Enter the camera last 3 serial number\nIt will automatically generate ip address for you.");
        }
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", error.c_str());
        if(updated){
            error.clear();
        }

        if (ImGui::Button("Confirm")) {
            bool pass = true;
            int32_t index = master->findServer(server_ip_buf);
            if(index == -1){
                error = "Server does not exist.";
                pass = false;
            }
            if(!all_servers.at(index).connected){
                error = "Server is disconnected.";
                pass = false;
            }
            if(master->findCamera(server_ip_buf, GetRemoteIPBySerial(camera_serial_buf)) != -1){
                error = "Camera already added.";
                pass = false;
            }
            if(camera_serial_buf.size() != 3){
                error = "Serial must be 3 number";
                pass = false;
            }

            if(pass){
                master->command_only(server_ip_buf, "add", std::string(camera_serial_buf));
                trigger(false);
            }
        }
        ImGui::SameLine();
        if(ImGui::Button("Cancel")){
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}