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

using json = nlohmann::json;

struct AppData
{
    std::queue<std::string> command_queue;
    GoProMaster master;
    GlobalState global_state;
    json gui;
    json servers;
    json presets;

    CameraListWindow camera_list_win;
    InspectorWindow inspector_win;
    WebsocketWindow websocket_win;
    StyleSetting style_setting_win;
    BaseWindow windows_array[4];

    AddCameraPopup add_camera_popwin;
    ScanCameraPopup scan_camera_popwin;
    StartWebcamPopup start_webcam_popwin;
    PreviewPopup preview_popwin;
    AddPresetPopup add_preset_popwin;
    PresetManagerPopup preset_manager_popwin;
    MediaBrowserPopup media_browser_popwin;
    BasePopWindow pop_windows_array[7];

    ExecutionType execution_type = ExecutionType::SetAll;
    std::unordered_map<std::string, std::string> execution_logs = std::unordered_map<std::string, std::string>();
};


#endif
