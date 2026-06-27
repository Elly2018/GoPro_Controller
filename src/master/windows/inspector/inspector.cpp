/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../inspector.h"
#include "src/imgui_notify.h"

std::vector<int32_t> InspectorWindow::system_list_ordered = std::vector<int32_t>(GOPRO_SYSTEM_SETTING_SIZE);
std::vector<int32_t> InspectorWindow::video_setting_list_ordered = std::vector<int32_t>(GOPRO_VIDEO_SETTING_SIZE);
std::vector<int32_t> InspectorWindow::video_protune_list_ordered = std::vector<int32_t>(GOPRO_VIDEO_PROTUNE_SETTING_SIZE);
std::vector<int32_t> InspectorWindow::photo_setting_list_ordered = std::vector<int32_t>(GOPRO_PHOTO_SETTING_SIZE);
std::vector<int32_t> InspectorWindow::photo_protune_list_ordered = std::vector<int32_t>(GOPRO_PHOTO_PROTUNE_SETTING_SIZE);
std::vector<int32_t> InspectorWindow::burst_setting_list_ordered = std::vector<int32_t>(GOPRO_BURST_SETTING_SIZE);
std::vector<int32_t> InspectorWindow::burst_protune_list_ordered = std::vector<int32_t>(GOPRO_BURST_PROTUNE_SETTING_SIZE);

std::vector<int32_t> InspectorWindow::status_software_list_ordered = std::vector<int32_t>(GOPRO_SOFTWARE_STATUS_SIZE);
std::vector<int32_t> InspectorWindow::status_hardware_list_ordered = std::vector<int32_t>(GOPRO_HARDWARE_STATUS_SIZE);
std::vector<int32_t> InspectorWindow::status_encode_list_ordered = std::vector<int32_t>(GOPRO_ENCODE_STATUS_SIZE);
std::vector<int32_t> InspectorWindow::status_network_list_ordered = std::vector<int32_t>(GOPRO_NETWORK_STATUS_SIZE);
std::vector<int32_t> InspectorWindow::status_media_list_ordered = std::vector<int32_t>(GOPRO_MEDIA_STATUS_SIZE);

#define IO_DATA_GET(x, y) \
data[#x][#y] = json::array();\
for(int32_t i = 0; i < y.size(); i++){\
    data[#x][#y].push_back(y[i]);\
}\

#define IO_DATA_SET(x, y) \
if(data[#x][#y].is_array() && data[#x][#y].size() == y.size()){\
    for(int32_t i = 0; i < data[#x][#y].size(); i++){\
        if(data[#x][#y].at(i).is_number_integer()){\
            y[i] = data[#x][#y].at(i).get<int32_t>();\
        }\
    }\
}\

InspectorWindow::InspectorWindow(
    std::shared_ptr<json> _setting, 
    std::shared_ptr<GlobalState> _state, 
    std::shared_ptr<GoProMaster> _master
) 
    : BaseWindow(_setting, _state, _master) {
    title = "Inspector";
    reset_setting_order();
    reset_status_order();
}

InspectorWindow::~InspectorWindow(){
    
}

json InspectorWindow::get_window_data() {
    json data = json::object();
    data["put_finish"] = put_finish;
    data["create_date_folder"] = create_date_folder;
    data["media_name_rule_type"] = media_name_rule_type;
    data["media_name_character_count"] = media_name_character_count;
    data["current_download_location"] = state->current_download_location;
    data["setting_order"] = json::object();
    data["status_order"] = json::object();
    IO_DATA_GET(setting_order, system_list_ordered);
    IO_DATA_GET(setting_order, video_setting_list_ordered);
    IO_DATA_GET(setting_order, video_protune_list_ordered);
    IO_DATA_GET(setting_order, photo_setting_list_ordered);
    IO_DATA_GET(setting_order, photo_protune_list_ordered);
    IO_DATA_GET(setting_order, burst_setting_list_ordered);
    IO_DATA_GET(setting_order, burst_protune_list_ordered);
    IO_DATA_GET(status_order, status_software_list_ordered);
    IO_DATA_GET(status_order, status_hardware_list_ordered);
    IO_DATA_GET(status_order, status_encode_list_ordered);
    IO_DATA_GET(status_order, status_network_list_ordered);
    IO_DATA_GET(status_order, status_media_list_ordered);
    return data;
}

void InspectorWindow::set_window_data(json data) {
    if(data["put_finish"].is_boolean()){
        put_finish = data["put_finish"].get<bool>();
    }
    if(data["create_date_folder"].is_boolean()){
        create_date_folder = data["create_date_folder"].get<bool>();
    }
    if(data["media_name_rule_type"].is_number()){
        media_name_rule_type = data["media_name_rule_type"].get<int32_t>();
    }
    if(data["media_name_character_count"].is_number()){
        media_name_character_count = data["media_name_character_count"].get<int32_t>();
    }
    if(data["put_finish"].is_number()){
        put_finish = data["put_finish"].get<int32_t>();
    }
    if(data["current_download_location"].is_string()){
        state->current_download_location = data["current_download_location"].get<std::string>();
    }
    if(data["setting_order"].is_object()){
        IO_DATA_SET(setting_order, system_list_ordered);
        IO_DATA_SET(setting_order, video_setting_list_ordered);
        IO_DATA_SET(setting_order, video_protune_list_ordered);
        IO_DATA_SET(setting_order, photo_setting_list_ordered);
        IO_DATA_SET(setting_order, photo_protune_list_ordered);
        IO_DATA_SET(setting_order, burst_setting_list_ordered);
        IO_DATA_SET(setting_order, burst_protune_list_ordered);
    }
    if(data["status_order"].is_array() && data["status_order"].size() == GOPRO_STATUS_SIZE){
        IO_DATA_SET(status_order, status_software_list_ordered);
        IO_DATA_SET(status_order, status_hardware_list_ordered);
        IO_DATA_SET(status_order, status_encode_list_ordered);
        IO_DATA_SET(status_order, status_network_list_ordered);
        IO_DATA_SET(status_order, status_media_list_ordered);
    }
}

void InspectorWindow::render(){
    ImGui::Begin("Inspector", &enable, w_flag);
    {
        int32_t s = master->findCamera(state->current_camera_server, state->current_camera_item);
        if(s != -1){
            CameraInfo c = master->getCamera_Clone(s);
            should_disabled = !c.connected || state->current_camera_item.size() < 10 || s == -1 || !state->current_setting_items_bind;
        }
        draw_header();

        ImGui::Separator();

        if(ImGui::BeginTabBar("Inspector_Bar##Top")){
            if(ImGui::BeginTabItem("Command##Inspector_Bar_Item")){
                if(ImGui::BeginTabBar("Inspector_Bar##Command")){
                    if(ImGui::BeginTabItem("Global##Inspector_Bar_Item")){
                        draw_command_global();
                        ImGui::EndTabItem();
                    }
                    if(ImGui::BeginTabItem("Local##Inspector_Bar_Item")){
                        ImGui::BeginDisabled(should_disabled);
                        draw_command_local();
                        ImGui::EndDisabled();
                        ImGui::EndTabItem();
                    }
                    ImGui::EndTabBar();
                }
                ImGui::EndTabItem();
            }
            if(ImGui::BeginTabItem("Setting##Inspector_Bar_Item")){
                if(ImGui::Button("Reset Setting Order##Inspector_Bar_Item")){
                    reset_setting_order();
                    state->update_server();
                }

                ImGui::BeginDisabled(should_disabled);
                if(ImGui::Button("Save Preset##Inspector_Bar_Item")){
                    state->command_sender("add_preset");
                }
                ImGui::EndDisabled();

                ImGui::SameLine();
                ImGui::BeginDisabled(should_disabled);
                if(state->applying_all){
                    if(ImGui::Button("Stop Apply All##Inspector_Bar_Item")){
                        if(s != -1){
                            const CameraInfo c = master->getCamera_Clone(s);
                            master->stopApplyAll(c);
                        }
                    }
                }else{
                    if(ImGui::Button("Quick Apply All##Inspector_Bar_Item")){
                        if(s != -1){
                            const CameraInfo c = master->getCamera_Clone(s);
                            master->quickApplyAll(c);
                            state->applying_all = true;
                        }
                    }
                }
                ImGui::EndDisabled();

                ImGui::SameLine();

                ImGui::BeginDisabled(state->applying_all);
                if(ImGui::Button("Preset Manager##Inspector_Bar_Item")){
                    state->command_sender("preset_manager");
                }
                ImGui::EndDisabled();

                if(ImGui::BeginTabBar("Inspector_Bar##Second")){
                    if(ImGui::BeginTabItem("System##Inspector_Bar_Item")){
                        ImGui::BeginDisabled(should_disabled || state->applying_all);
                        draw_system();
                        ImGui::EndDisabled();
                        ImGui::EndTabItem();
                    }
                    if(ImGui::BeginTabItem("Setting##Inspector_Bar_Item")){
                        ImGui::BeginDisabled(should_disabled || state->applying_all);
                        draw_setting();
                        ImGui::EndDisabled();
                        ImGui::EndTabItem();
                    }
                    if(ImGui::BeginTabItem("Protune##Inspector_Bar_Item")){
                        ImGui::BeginDisabled(should_disabled || state->applying_all);
                        draw_protune();
                        ImGui::EndDisabled();
                        ImGui::EndTabItem();
                    }
                    ImGui::EndTabBar();
                }
                ImGui::EndTabItem();
            }
            if(ImGui::BeginTabItem("Status##Inspector_Bar_Item")){
                if(ImGui::Button("Reset Status Order")){
                    reset_status_order();
                    state->update_server();
                }
                if(ImGui::BeginTabBar("Inspector_Bar##Status")){
                    if(ImGui::BeginTabItem("Software##Inspector_Bar_Item")){
                        ImGui::BeginDisabled(should_disabled);
                        draw_status();
                        ImGui::EndDisabled();
                        ImGui::EndTabItem();
                    }
                    if(ImGui::BeginTabItem("Hardware##Inspector_Bar_Item")){
                        ImGui::BeginDisabled(should_disabled);
                        draw_hardware();
                        ImGui::EndDisabled();
                        ImGui::EndTabItem();
                    }
                    if(ImGui::BeginTabItem("Encode##Inspector_Bar_Item")){
                        ImGui::BeginDisabled(should_disabled);
                        draw_encode();
                        ImGui::EndDisabled();
                        ImGui::EndTabItem();
                    }
                    if(ImGui::BeginTabItem("Network##Inspector_Bar_Item")){
                        ImGui::BeginDisabled(should_disabled);
                        draw_network();
                        ImGui::EndDisabled();
                        ImGui::EndTabItem();
                    }
                    if(ImGui::BeginTabItem("Media##Inspector_Bar_Item")){
                        ImGui::BeginDisabled(should_disabled);
                        draw_media_status();
                        ImGui::EndDisabled();
                        ImGui::EndTabItem();
                    }
                    ImGui::EndTabBar();
                }
                ImGui::EndTabItem();
            }
            if(ImGui::BeginTabItem("Media##Inspector_Bar_Item")){
                if(ImGui::BeginTabBar("Inspector_Bar##Media")){
                    if(ImGui::BeginTabItem("Global##Inspector_Bar_Item_Media")){
                        draw_media_global();
                        ImGui::EndTabItem();
                    }
                    if(ImGui::BeginTabItem("Local##Inspector_Bar_Item_Media")){
                        ImGui::BeginDisabled(should_disabled);
                        draw_media_local();
                        ImGui::EndDisabled();
                        ImGui::EndTabItem();
                    }
                    ImGui::EndTabBar();
                }
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
    }
    ImGui::End();

    if(state->applying_all != applying_all_last){
        applying_all_last = state->applying_all;
        if(state->applying_all){
            ImGuiToast toast(ImGuiToastType_Success, 3000);
            toast.set_title("Trying to applying...");
            ImGui::InsertNotification(toast);
        }else{
            ImGuiToast toast(ImGuiToastType_Success, 3000);
            toast.set_title("Applying Finish");
            ImGui::InsertNotification(toast);
        }
    }
}

void InspectorWindow::draw_header(){
    ImGui::InputText("Camera Name", &state->current_camera_name);
    if(ImGui::Button("Rename Camera")){
        master->command_with_value("rename", state->current_camera_item, state->current_camera_name);
    }
    std::string serial = "";
    if(state->current_hw_items["serial_number"].is_string()){
        serial = state->current_hw_items["serial_number"].get<std::string>();
    }
    ImGui::Text("Name: %s, IP: %s, Serial: %s", 
        state->current_camera_name.c_str(), 
        state->current_camera_item.c_str(),
        serial.c_str());
}
