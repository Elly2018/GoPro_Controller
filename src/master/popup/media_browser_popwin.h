/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef POPUP_MEDIA_BROWSER_POPUP_H
#define POPUP_MEDIA_BROWSER_POPUP_H
#include "base_pop_window.h"
#include <unordered_map>

struct Add_preset_popup;
typedef void (*Add_preset_popup_render_func)(Add_preset_popup& win);

struct Media_browser_popup {

    Gopro_master_popup_window base;

    Add_camera_popup_render_func render;

    char selected[64];
    std::unordered_map<std::string, std::pair<std::vector<u_char>, std::pair<int32_t, int32_t>>> thumbnail_rawData;
    std::unordered_map<std::string, ImTextureID> thumbnail_textures;

};

#endif