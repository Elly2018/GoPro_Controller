/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../camera_list.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include "../../data/camera_info.h"
#include <algorithm>
#include <functional> 

json camera_list_window_get_window_data(Camera_list_window& win) {
    json buff = json::object();
    buff["size"] = win.size;
    buff["filter"] = (int32_t)win.filter;
    buff["sort"] = (int32_t)win.sort;
    buff["filter_ip"] = win.filter_ip;
    buff["filter_connect"] = win.filter_connect;
    return buff;
}

void camera_list_window_set_window_data(Camera_list_window& win, const json& data){
    if(data["size"].is_number()){
        win.size = data["size"].get<int32_t>();
    }
    if(data["filter"].is_number()){
        win.filter = (FilterType)data["filter"].get<int32_t>();
    }
    if(data["sort"].is_number()){
        win.sort = (SortType)data["sort"].get<int32_t>();
    }
    if(data["filter_connect"].is_boolean()){
        win.filter_connect = data["filter_connect"].get<bool>();
    }
    if(data["filter_ip"].is_string()){
        win.filter_ip = data["filter_ip"].get<std::string>();
    }
}

void camera_list_window_render(Camera_list_window& win){
    bool changed = false;
    ImGui::Begin(title.c_str(), &enable, w_flag);
    {
        ImVec2 window_size = ImGui::GetWindowSize();

        changed = ImGui::SliderInt("Item Size##Camera_List_Size", &size, 0, 15);
        changed = changed || ImGui::InputText("Search", &search);
        std::string filter_text = get_filter_string(filter);
        std::string sort_text = get_sort_string(sort);

        if(ImGui::BeginCombo("Sort##Camera_List_combo", sort_text.c_str())){
            for(int32_t i = 0; i < 3; i++){
                if(ImGui::Selectable((get_sort_string((SortType)i) + "##sort_option").c_str())){
                    sort = (SortType)i;
                    changed = true;
                }
            }
            ImGui::EndCombo();
        }
        if(ImGui::BeginCombo("Filter##Camera_List_combo", filter_text.c_str())){
            for(int32_t i = 0; i < 3; i++){
                if(ImGui::Selectable((get_filter_string((FilterType)i) + "##filter_option").c_str())){
                    filter = (FilterType)i;
                    if(filter == FilterType::Server && master->getServers().size() > 0){
                        filter_ip = master->getServers().at(0)->ip;
                    }
                    changed = true;
                }
            }
            ImGui::EndCombo();
        }

        if(filter == FilterType::Connect){
            ImGui::SameLine();
            if(ImGui::Checkbox("State##Camera_List_combo2", &filter_connect)){
                changed = true;
            }
        }else if(filter == FilterType::Server){
            if(ImGui::BeginCombo("Server##Camera_List_combo2", filter_ip.c_str())){
                for(auto& ser : master->getServers()){
                    if(ImGui::Selectable((ser->ip + "##filter_server_option").c_str())){
                        filter_ip = ser->ip;
                        changed = true;
                    }
                }
                ImGui::EndCombo();
            }
        }

        ImVec2 rect_size = get_rect_size(); // Single cell size
        float width = ImGui::GetWindowSize().x; // Total space size
        int32_t limit = static_cast<int32_t>((width / rect_size.x) - 0.5f);
        int32_t counter = 0;
        std::vector<CameraInfo> ciss = get_filtering_result();
        ImGui::Text("Cal: %f/%f, Total: %d, Line: %d", width, rect_size.x, size, limit);
        for(const auto& c : ciss){
            if(c.ip.size() > 0){
                try{
                    if(size == 0) draw_line(c);
                    else {
                        float s = ImGui::GetFontSize();
                        ImGui::UpdateCurrentFontSize(((float)size / 20.0f + 0.7f) * s);
                        draw_group_state(c);
                        ImGui::UpdateCurrentFontSize(s);
                        if(counter + 1 < limit){
                            ImGui::SameLine();
                            counter++;
                        }else{
                            counter = 0;
                        }
                    }
                }catch(const std::exception& ex){
                    std::cerr << ex.what() << std::endl;
                }
            }
        }
    }
    ImGui::End();
    if(changed){
        state->update_server();
        changed = false;
    }
}

void CameraListWindow::draw_line(const CameraInfo& c){
    bool selected = c.ip == state->current_camera_item && c.server == state->current_camera_server;
    std::string plusStatus = master->getBarInfo(c);
    std::string plusID = plusStatus + "##CameraList_" + c.ip;
    if(ImGui::Selectable(plusID.c_str(), selected)){
        // User select interaction
        onClick(c);
    }
    item_event(c);
}

void CameraListWindow::item_event(const CameraInfo& c){
    if(ImGui::IsItemClicked(ImGuiMouseButton_Left) && ImGui::IsItemHovered()){
        onClick(c);
    }
    if(ImGui::IsItemClicked(ImGuiMouseButton_Right) && ImGui::IsItemHovered()){
        ImGui::OpenPopupOnItemClick();
    }
    if(ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && ImGui::IsItemHovered() && c.connected){
        master->preview_start(c.server, c.ip);
        state->preview_ip = c.ip;
        state->preview_server = c.server;
        state->command_sender("preview_start");
    }

    if(ImGui::BeginPopupContextItem((title + "##Popup_Menu" + c.ip).c_str())){
        ImGui::BeginDisabled(!c.connected);
        if (ImGui::Selectable("Connect")){
            master->command_only(c.server, "usb_on", c.ip);
        }
        if (ImGui::Selectable("Disconnect")){
            master->command_only(c.server, "usb_off", c.ip);
        }
        ImGui::Separator();
        if (ImGui::Selectable("Reboot"))
        {
            master->command_only(c.server, "reboot", c.ip);
        }
        if (ImGui::Selectable("Shutdown"))
        {
            master->command_only(c.server, "shutdown", c.ip);
        }
        if (ImGui::Selectable("Preview"))
        {
            master->preview_start(c.server, c.ip);
            state->preview_ip = c.ip;
            state->preview_server = c.server;
            state->command_sender("preview_start");
        }
        ImGui::EndDisabled();
        if (ImGui::Selectable("Delete"))
        {
            master->command_only(c.server, "delete", c.ip);
        }
        ImGui::EndPopup();
    }
}

void CameraListWindow::onClick(const CameraInfo& c){
    state->current_setting_items_bind = false;
    state->current_camera_item = c.ip;
    state->current_camera_server = c.server;
    state->current_camera_name = c.name;
    std::cout << "Select camera: " << c.server << "  " << c.ip << std::endl;
    master->query_only(c.server, "get", c.ip);
    //current_setting_items_bind = master.getSettingsFromCamera(*c, current_setting_items);
}

ImVec2 CameraListWindow::get_rect_size(){
    return ImVec2(10 * (size + 10) + 20, 10 * (size + 10) + 20);
}

std::vector<CameraInfo> CameraListWindow::get_filtering_result(){
    auto buffer = master->getCameras_Clone();
    auto filtered = std::vector<CameraInfo>();

    for(auto& c : buffer){
        if(search.size() > 0){
            bool ip_contain = c.ip.find(search) != std::string::npos;
            bool name_contain = c.name.find(search) != std::string::npos;
            bool serial_contain = c.serial.find(search) != std::string::npos;
            if(!ip_contain && !name_contain && !serial_contain) continue;
        }

        if(filter == FilterType::Connect){
            if(c.connected == filter_connect){
                filtered.push_back(c);
            }
        }else if(filter == FilterType::Server){
            if(c.server == filter_ip){
                filtered.push_back(c);
            }
        }else {
            filtered.push_back(c);
        }
    }

    if (sort == SortType::Name){
        std::sort(filtered.begin(), filtered.end(), [](const CameraInfo& a, const CameraInfo& b){
            return a.name < b.name;
        });
    }else if (sort == SortType::IP){
        std::sort(filtered.begin(), filtered.end(), [](const CameraInfo& a, const CameraInfo& b){
            return a.ip < b.ip;
        });
    }
    
    return filtered;
}

std::string CameraListWindow::get_filter_string(FilterType type){
    switch(type){
        default:
        case FilterType::None: return "None";
        case FilterType::Server: return "Server";
        case FilterType::Connect: return "Connect";
    }
}

std::string CameraListWindow::get_sort_string(SortType type){
    switch(type){
        default:
        case SortType::None: return "None";
        case SortType::Name: return "Name";
        case SortType::IP: return "IP";
    }
}

std::string CameraListWindow::toTimeCode(int32_t timer){
    std::string result = "";
    int32_t mins = static_cast<int32_t>(((float)timer / 60.0f));
    int32_t hours = static_cast<int32_t>(((float)mins / 60.0f));
    mins = mins % 60;
    timer = timer % 60;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours;
    result += oss.str();
    result += ":";

    std::ostringstream oss2;
    oss2 << std::setfill('0') << std::setw(2) << mins;
    result += oss2.str();
    result += ":";

    std::ostringstream oss3;
    oss3 << std::setfill('0') << std::setw(2) << timer;
    result += oss3.str();

    return result;
}

std::string CameraListWindow::bytesToGbString(long bytes) {
    // Define the value of one gigabyte (1024 * 1024 * 1024 bytes)
    const long GIGABYTE = 1024L * 1024L * 1024L; 

    // Convert bytes to gigabytes as a double
    double gigabytes = static_cast<double>(bytes) / GIGABYTE;

    // Use std::stringstream to format the output with desired precision
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << gigabytes << " GB";

    // Return the formatted string
    return ss.str();
}
