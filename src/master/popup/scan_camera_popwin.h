/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef POPUP_SCAN_CAMERA_POPWIN_H
#define POPUP_SCAN_CAMERA_POPWIN_H
#include "base_pop_window.h"

struct Scan_camera_popup;
typedef void (*Scan_camera_popup_render_func)(Scan_camera_popup& win);

struct Scan_camera_popup {

    Gopro_master_popup_window base;

    Scan_camera_popup_func render;

    char server_ip_buf[64];
    char error[64];
};

void scan_camera_popup_render(Scan_camera_popup& win);

#endif