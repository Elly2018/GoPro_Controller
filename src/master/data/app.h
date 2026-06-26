/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef DATA_APP_H
#define DATA_APP_H
#include <string>
#include <nlohmann/json.hpp>
#include "state.h"
#include "state_action.h"
#include "windows/wins.h"
#include "popup/popwins.h"

using json = nlohmann::json;

struct AppData
{
    std::queue<std::string> command_queue;
    Gopro_master master;
    Global_state global_state;
    json gui;
    json servers;
    json presets;

    union {
        Websocket_window websocket_window;
        Gopro_master_window websocket_window_base;
    };
    union {
        Camera_list_window camera_list_window;
        Gopro_master_window camera_list_window_base;
    };
    union {
        Inspector_window inspector_window;
        Gopro_master_window inspector_window_base;
    };
    union {
        Style_window style_window;
        Gopro_master_window style_window_base;
    };
    Gopro_master_window* windows_array[4];

    union {
        Add_camera_popup add_camera_popup_window;
        Gopro_master_popup_window add_camera_popup_window_base;
    };
    union {
        Scan_camera_popup scan_camera_popup_window;
        Gopro_master_popup_window scan_camera_popup_window_base;
    };
    union {
        Start_webcam_popup start_webcam_popup_window;
        Gopro_master_popup_window start_webcam_popup_window_base;
    };
    union {
        Preview_popup preview_popup_window;
        Gopro_master_popup_window preview_popup_window_base;
    };
    union {
        Add_preset_popup add_preset_popup_window;
        Gopro_master_popup_window add_preset_popup_window_base;
    };
    union {
        Preset_manager_popup preset_manager_popup_window;
        Gopro_master_popup_window preset_manager_popup_window_base;
    };
    union {
        Media_browser_popup media_browser_popup_window;
        Gopro_master_popup_window media_browser_popup_window_base;
    };
    Gopro_master_popup_window* pop_windows_array[7];

    ExecutionType execution_type = ExecutionType::SetAll;
    std::unordered_map<std::string, std::string> execution_logs = std::unordered_map<std::string, std::string>();
};


#endif
