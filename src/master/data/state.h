/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#include <string>
#include <mutex>
#include <SDL3/SDL.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

typedef struct AppData;

typedef void(*CommandSenderFunc)(AppData& data, const char* cmd);
typedef void(*ActionFunc)(AppData& data);

enum class InspectorObjectType {
    Camera
};

struct Media_info {
    std::string filename;
    uint32_t created;
    uint32_t modified;
    size_t size;
};

struct Global_state {
    SDL_Renderer* m_renderer;
    AppData* appdata;
    bool applying_all;
    int32_t applying_all_count;
    
    char websocket_server_selection[64];
    char camera_selection[64];
    char current_mode_item_string[64];
    int32_t current_mode_item;
    
    char current_camera_name[128];
    char current_download_location[128];
    std::mutex media_list_mtx;
    std::vector<MediaInfo> current_media_list;
    json current_setting_items;
    bool current_setting_items_bind;
    json current_status_items;
    bool current_status_items_bind;
    json current_hw_items;
    bool current_hw_items_bind;
    char current_camera_item[64];
    char current_camera_server[64];

    // Apply state
    char apply_all_item_string[64] = "Video Resolution";
    int32_t apply_all_item;
    // Preview
    std::string preview_server;
    std::string preview_ip;
    // Caller
    CommandSenderFunc command_sender; 
    ActionFunc update_event;
    ActionFunc update_server;
    ActionFunc update_preset;
    ActionFunc update_GUI;
    // Inspector
    InspectorObjectType iot = InspectorObjectType::Camera;
};


inline int32_t global_state_try_get_setting_int32_by_id(const json& setting, const int32_t id) {
    if(current_setting_items[std::to_string(id)].is_number()){
        return current_setting_items[std::to_string(id)].get<int32_t>();
    }
    return -1;
}

inline int32_t global_state_try_get_status_int32_by_id(const json& status, const int32_t id) {
    if(current_status_items[std::to_string(id)].is_number()){
        return current_status_items[std::to_string(id)].get<int32_t>();
    }
    return -1;
}