/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../inspector.h"
#include <iostream>
#include <string>

void InspectorWindow::draw_command_local(){
    ImGui::Text("Single Camera Control");

    int32_t current_camera = master->findCamera(state->current_camera_server, state->current_camera_item);
    bool should_disabled = state->current_camera_item.size() < 10 || current_camera == -1;
    ImGui::BeginDisabled(should_disabled);

    ImGuiStyle& style = ImGui::GetStyle();
    ImVec2 size = ImGui::GetWindowSize();
    ImVec2 button_2size = ImVec2(size.x / 2.0F - style.ItemSpacing.x, 0);
    ImVec2 button_4size = ImVec2(size.x / 4.0F - style.ItemSpacing.x, 0);
    ImVec2 full_button_size = ImVec2(size.x - style.ItemSpacing.x, 0);

    if(current_camera != -1) {
        CameraInfo info = master->getCamera_Clone(current_camera);

        if(ImGui::Button("Record", button_2size)) master->command_only(info.server, "shutter_on", info.ip); ImGui::SameLine();
        if(ImGui::Button("Stop", button_2size)) master->command_only(info.server, "shutter_off", info.ip);

        if(ImGui::Button("Connect", button_4size)) master->command_only(info.server, "usb_on", info.ip); ImGui::SameLine();
        if(ImGui::Button("Disconnect", button_4size)) master->command_only(info.server, "usb_off", info.ip); ImGui::SameLine();
        if(ImGui::Button("Shutdown", button_4size)) master->command_only(info.server, "shutdown", info.ip); ImGui::SameLine();
        int32_t lo = master->haslocate(info.server, info.ip);
        if(lo == -1){
            if(ImGui::Button("Locate", button_4size)) master->locate(info.server, info.ip);
        }else{
            if(ImGui::Button("UnLocate", button_4size)) master->locate(info.server, info.ip);
        }

        ImGui::Dummy(ImVec2(0, 20));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0, 20));

        if(state->current_status_items[std::to_string(PRESET_ID)].is_number_integer()){

            int32_t cuccrent_select = state->current_status_items[std::to_string(PRESET_ID)].get<int32_t>();
            int32_t index = -1;
            for(int32_t i = 0; i < GOPRO_MODE_SIZE; i++){
                if(GOPRO_MODE_VALUE[i] == cuccrent_select){
                    index = i;
                    break;
                }
            }

            std::string display_mode = GOPRO_MODE_STRING[index];
            
            if(ImGui::BeginCombo("Mode##SCC", display_mode.c_str())){
                for (int n = 0; n < GOPRO_MODE_SIZE; n++)
                {
                    std::string curr = GOPRO_MODE_STRING[n];
                    std::string curr_b = curr + "##SCC_Option";
                    bool is_selected = (state->current_mode_item_string == curr); // You can store your selection however you want, outside or inside your objects
                    if (ImGui::Selectable(curr_b.c_str(), is_selected)){
                        master->presetSwitch("", info.ip, GOPRO_MODE_VALUE[n]);
                        state->current_mode_item_string = curr;
                        state->current_mode_item = n;
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
                }
                ImGui::EndCombo();
            }
        }
        
        if(ImGui::Button("Setting Apply All By ID", full_button_size)) {
            int32_t v = state->current_setting_items[std::to_string(state->apply_all_item)].get<int32_t>();
            master->apply(info.ip, "", state->apply_all_item, GET_SETTING_VALUE_BY_ID(state->apply_all_item)[v]);
        }

        if(ImGui::BeginCombo("ID", state->apply_all_item_string.c_str())){
            for (int n = 0; n < GOPRO_SETTING_SIZE; n++)
            {
                int32_t id = GOPRO_SETTING_IDS[n];
                std::string curr = GET_SETTING_NAME_BY_ID(id);
                bool is_selected = (state->current_mode_item_string == curr); // You can store your selection however you want, outside or inside your objects
                std::string curr_b = curr + "##Setting_ID_Option";
                if (ImGui::Selectable(curr_b.c_str(), is_selected)){
                    state->apply_all_item_string = curr;
                    state->apply_all_item = GOPRO_SETTING_IDS[n];
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
            }
            ImGui::EndCombo();
        }

        json buffer_c = json::object();
        std::string try_apply = "";
        if(master->getSettingsFromCamera(info, buffer_c)){
            if(buffer_c[std::to_string(state->apply_all_item)].is_number_integer()){
                int32_t v = buffer_c[std::to_string(state->apply_all_item)].get<int32_t>();
                try_apply = GET_SETTING_STRING_BY_ID(state->apply_all_item)[v];
                ImGui::Text("Trying Apply Value: %s", try_apply.c_str());
            }
        }

        if (ImGui::BeginTable("Local_Apply", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            ImGui::TableSetupColumn("Server Address##Local_Apply_header");
            ImGui::TableSetupColumn("IP Address##Local_Apply_header");
            ImGui::TableSetupColumn("Value##Local_Apply_header");
            ImGui::TableSetupColumn("OK##Local_Apply_header");
            ImGui::TableHeadersRow();

            for(auto& camera: master->getCameras()){
                json buffer = json::object();
                if(master->getSettingsFromCamera(*camera, buffer)){
                    if(buffer[std::to_string(state->apply_all_item)].is_number_integer()){
                        int32_t v = buffer[std::to_string(state->apply_all_item)].get<int32_t>();
                        std::string c_v = GET_SETTING_STRING_BY_ID(state->apply_all_item)[v];
                        bool eq = c_v == try_apply;
                        std::string ok = "";
                        if(eq) ok = "O";
                        else ok = "X";
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0);
                        ImGui::Text("%s", camera->server.c_str());
                        ImGui::TableSetColumnIndex(1);
                        ImGui::Text("%s", camera->ip.c_str());
                        ImGui::TableSetColumnIndex(2);
                        ImGui::Text("%s", c_v.c_str());   
                        ImGui::TableSetColumnIndex(3);
                        ImGui::Text("%s", ok.c_str());
                    }
                }
            }
            ImGui::EndTable();
        }
    }
    ImGui::EndDisabled();
}

void InspectorWindow::draw_command_global(){
    ImGui::Text("Global Controls");
    ImGui::Text("Commands applied to all connected cameras");

    ImGuiStyle& style = ImGui::GetStyle();
    ImVec2 size = ImGui::GetWindowSize();
    ImVec2 button_size = ImVec2(size.x / 2.0F - style.ItemSpacing.x, 0);
    ImVec2 full_button_size = ImVec2(size.x - style.ItemSpacing.x, 0);
    
    if(ImGui::Button("Scan All", button_size)) master->command_only("scan"); ImGui::SameLine();
    if(ImGui::IsItemHovered()) ImGui::SetTooltip("Scan all websocket server for cameras");
    if(ImGui::Button("Scan Server", button_size)) state->command_sender("scan_server");
    if(ImGui::IsItemHovered()) ImGui::SetTooltip("Scan one websocket server for cameras\nThis will popup a window for you to enter websocket server address to targeting");

    if(ImGui::Button("Add Camera", button_size)) state->command_sender("add_camera"); ImGui::SameLine();
    if(ImGui::IsItemHovered()) ImGui::SetTooltip("Menually add camera address to one websocket server list");
    if(ImGui::Button("Clean Camera", button_size)) master->command_only("clean");
    if(ImGui::IsItemHovered()) ImGui::SetTooltip("Clean all websocket server camera record");

    if(ImGui::Button("Connect All", button_size)) master->command_only("usb_on"); ImGui::SameLine();
    if(ImGui::IsItemHovered()) ImGui::SetTooltip("Tells all cameras usb control on");
    if(ImGui::Button("Disconnect All", button_size)) master->command_only("usb_off");
    if(ImGui::IsItemHovered()) ImGui::SetTooltip("Tells all cameras usb control off");

    if(ImGui::Button("Reboot All", button_size)) master->command_only("reboot"); ImGui::SameLine();
    if(ImGui::IsItemHovered()) ImGui::SetTooltip("Tells all cameras reboot right now");
    if(ImGui::Button("Shutdown All", button_size)) master->command_only("shutdown");
    if(ImGui::IsItemHovered()) ImGui::SetTooltip("Tells all cameras shutdown right now");

    if(ImGui::Button("Record All", button_size)) master->command_only("shutter_on"); ImGui::SameLine();
    if(ImGui::Button("Stop All", button_size)) master->command_only("shutter_off");

    if(ImGui::Button("Enter Webcam", button_size)) master->webcam_only("preview"); ImGui::SameLine();
    if(ImGui::Button("Exit Webcam", button_size)) master->webcam_only("exit");

    if(ImGui::Button("Start Webcam", button_size)) state->command_sender("start_webcam"); ImGui::SameLine();
    if(ImGui::Button("Sync Time", button_size)) master->command_only("datetime");

    if(ImGui::Button("Last Media", button_size)) master->media_only("lastmedia"); ImGui::SameLine();
    if(ImGui::Button("Close Preview", button_size)) master->preview_end("", "");
}
