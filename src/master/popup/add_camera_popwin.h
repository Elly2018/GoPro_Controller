/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef POPUP_ADD_CAMERA_POPUP_H
#define POPUP_ADD_CAMERA_POPUP_H
#include "base_pop_window.h"

struct Add_camera_popup;
typedef void (*Add_camera_popup_render_func)(Add_camera_popup& win);

struct Add_camera_popup {
    
    Gopro_master_popup_window base;

    Add_camera_popup_render_func render;

    std::string server_ip_buf = "127.0.0.1";
    std::string camera_serial_buf = "123";
    std::string error = "";
};

void add_camera_popup_render(Add_camera_popup& win);

#endif