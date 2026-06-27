/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef POPUP_ADD_PRESET_POPUP_H
#define POPUP_ADD_PRESET_POPUP_H
#include "base_pop_window.h"

struct Add_preset_popup;
typedef void (*Add_preset_popup_render_func)(Add_preset_popup& win);

struct Add_preset_popup {

    Gopro_master_popup_window base;

    Add_preset_popup_render_func render;

    char preset_name[64];

};

void add_preset_popup_render(Add_preset_popup& win);
void add_preset_popup_savepreset(Add_preset_popup& win);

#endif