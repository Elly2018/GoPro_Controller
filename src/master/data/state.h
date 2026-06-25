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

typedef void(*CommandSenderFunc)(const char* cmd);
typedef void(*ActionFunc)();

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
    bool done;
    int32_t applying_all_count = 0;
    bool applying_all;
    // Selection
    std::string websocket_server_selection;
    std::string camera_selection;
    std::string current_mode_item_string;
    int32_t current_mode_item;
    // Current select camera setting
    std::string current_camera_name = "";
    std::string current_download_location = "";
    std::mutex media_list_mtx;
    std::vector<MediaInfo> current_media_list = std::vector<MediaInfo>();
    json current_setting_items;
    bool current_setting_items_bind = false;
    json current_status_items;
    bool current_status_items_bind = false;
    json current_hw_items;
    bool current_hw_items_bind = false;
    std::string current_camera_item = "";
    std::string current_camera_server = "";

    // Apply state
    std::string apply_all_item_string = "Video Resolution";
    int32_t apply_all_item = 2;
    // Preview
    std::string preview_server;
    std::string preview_ip;
    // Caller
    CommandSenderFunc command_sender = NULL; 
    ActionFunc update_server = NULL;
    ActionFunc update_preset = NULL;
    // Inspector
    InspectorObjectType iot = InspectorObjectType::Camera;

    /**
     * This will trying to fetch data from current_setting_items variable
     * If it fetch fail, it will return -1
     */
    int32_t try_get_setting_int32_by_id(int32_t id){
        if(current_setting_items[std::to_string(id)].is_number()){
            return current_setting_items[std::to_string(id)].get<int32_t>();
        }
        return -1;
    }

    /**
     * This will trying to fetch data from current_status_items variable
     * If it fetch fail, it will return -1
     */
    int32_t try_get_status_int32_by_id(int32_t id){
        if(current_status_items[std::to_string(id)].is_number()){
            return current_status_items[std::to_string(id)].get<int32_t>();
        }
        return -1;
    }
    
};

