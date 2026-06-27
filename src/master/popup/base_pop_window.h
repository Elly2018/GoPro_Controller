/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef POPUP_BASE_POP_WINDOW_H
#define POPUP_BASE_POP_WINDOW_H
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include "../windows/base_window.h"

static constexpr uint32_t wp_flag = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize;

#ifdef _WIN32
    static constexpr uint32_t wp_cond = ImGuiCond_FirstUseEver;
#else
    static constexpr uint32_t wp_cond = ImGuiCond_Always;
#endif

struct Gopro_master_popup_window {
    Gopro_master_window base;
    bool isopen;
};

#endif