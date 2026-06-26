/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "websocket_server.h"

void websocket_window_render(Websocket_window& win) {
    ImGui::Begin("Websocket Dashboard", &enable, w_flag);
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec2 size = ImGui::GetWindowSize();
        ImVec2 button_2size = ImVec2(size.x / 2.0F - style.ItemSpacing.x, 0);
        ImVec2 button_3size = ImVec2(size.x / 3.0F - style.ItemSpacing.x, 0);
        ImVec2 full_button_size = ImVec2(size.x - style.ItemSpacing.x, 0);

        ImGui::Separator();

        ImGui::Text("Manual Control:");
        if (ImGui::Button("Start Rec (F2)", button_2size)) master->command_only("shutter_on"); ImGui::SameLine();
        if(ImGui::IsItemHovered()) ImGui::SetTooltip("Keyboard shortcut for broadcasting record signal to all connected cameras");
        if (ImGui::Button("Stop Rec (F3)", button_2size)) master->command_only("shutter_off");
        if(ImGui::IsItemHovered()) ImGui::SetTooltip("Keyboard shortcut for broadcasting stop signal to all connected cameras");
        if (ImGui::Button("Photo Mode (F4)", button_2size)) master->presetSwitch("", "", 65536);  ImGui::SameLine();
        if(ImGui::IsItemHovered()) ImGui::SetTooltip("Keyboard shortcut for broadcasting switch to photo mode signal to all connected cameras");
        if (ImGui::Button("Video Mode (F5)", button_2size)) master->presetSwitch("", "", 0);
        if(ImGui::IsItemHovered()) ImGui::SetTooltip("Keyboard shortcut for broadcasting switch to video mode signal to all connected cameras");

        ImGui::Separator();

        ImGui::Text("Server Connections:");
        ImGui::InputText("Server IP", &server_ip_buf);
        if(ImGui::IsItemHovered()) ImGui::SetTooltip("Enter the server ip address here, example will be 127.0.0.1 or 192.168.61.123");
        if (ImGui::Button("Add Server", button_3size)) {
            std::string ip = master->addServer(server_ip_buf);
            master->reconnect(ip);
            state->update_server();
        }
        if(ImGui::IsItemHovered()) ImGui::SetTooltip("Trying to connect server base on address you enter");

        ImGui::SameLine();
        if (ImGui::Button("Remove Server", button_3size)) {
            master->clean(std::string(server_ip_buf));
            state->update_server();
        }
        if(ImGui::IsItemHovered()) ImGui::SetTooltip("Trying to remove server base on address you enter, You must disconnect the server before hit remove by the way.");

        ImGui::SameLine();
        if (ImGui::Button("Disconnect Server", button_3size)) {
            master->disconnect(std::string(server_ip_buf));
        }
        if(ImGui::IsItemHovered()) ImGui::SetTooltip("Trying to disconnect server base on address you enter");

        if (ImGui::Button("Reconnect All", button_3size)) {
            master->reconnectAll();
        }
        ImGui::SameLine();
        if (ImGui::Button("Disconnect All", button_3size)) {
            master->disconnectAll();
        }
        ImGui::SameLine();
        if (ImGui::Button("Clean", button_3size)) {
            master->cleanAll();
            state->update_server();
        }

        // Server List Table
        if (ImGui::BeginTable("Servers", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            ImGui::TableSetupColumn("IP Address");
            ImGui::TableSetupColumn("Status");
            ImGui::TableSetupColumn("Last Message");
            ImGui::TableHeadersRow();

            for (const auto& s : master->getServers_Clone()) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", s.ip.c_str());
                ImGui::TableSetColumnIndex(1);
                if (s.connected) 
                    ImGui::TextColored(ImVec4(0,1,0,1), "Connected");
                else 
                    ImGui::TextColored(ImVec4(1,0,0,1), "Disconnected");
                ImGui::TableSetColumnIndex(2);
                ImGui::Text("%s", s.last_message.c_str());
            }
            ImGui::EndTable();
        }
    }
    ImGui::End();
}