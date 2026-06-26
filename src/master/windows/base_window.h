/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef WINDOWS_BASE_WINDOW_H
#define WINDOWS_BASE_WINDOW_H
#include <nlohmann/json.hpp>
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

using json = nlohmann::json;

static constexpr uint32_t w_flag = ImGuiWindowFlags_NoCollapse;

typedef struct Global_state;
typedef struct Gopro_master;

struct Gopro_master_window {
    json& setting;
    Global_state& state;
    Gopro_master& master;
    char title[64];
    bool enable;
    bool enable_last;
};

#endif