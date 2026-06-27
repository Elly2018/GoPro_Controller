/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef POPUP_PRESET_MANAGER_POPWIN_H
#define POPUP_PRESET_MANAGER_POPWIN_H
#include "base_pop_window.h"

struct Preset_manager_popup;
typedef void (*Preset_manager_popup_render_func)(Preset_manager_popup& win);

struct Preset_manager_popup {
    
    Gopro_master_popup_window base;

    Preset_manager_popup_render_func render;

    char preset_select[64];
    bool applying = false;
};

void preset_manager_popup_render(Preset_manager_popup& win);

#endif