/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef WINDOWS_STYLE_SETTING_H
#define WINDOWS_STYLE_SETTING_H
#include "base_window.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Style_window;
typedef void (*Style_window_render_func)(Style_window& win);

struct Style_window {
    Gopro_master_window base;

    Style_window_render_func render;
};

void style_window_render(Style_window& win);

json style_window_get_window_data(Style_window& win);
void style_window_set_window_data(Style_window& win, const json& data);

bool style_window_render_colors(Style_window& win);
bool style_window_render_fields(Style_window& win);
bool style_window_update_style(Style_window& win);

#endif