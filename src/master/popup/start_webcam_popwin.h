/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef POPUP_START_WEBCAM_POPWIN_H
#define POPUP_START_WEBCAM_POPWIN_H
#include "base_pop_window.h"

struct Start_webcam_popup;
typedef void (*Start_webcam_popup_render_func)(Start_webcam_popup& win);

struct Start_webcam_popup {
    
    Gopro_master_popup_window base;

    Start_webcam_popup_render_func render;

    char server_ip_buf[64] = "127.0.0.1";
    char port_buf[64] = "7000";
    char res_string_buf[64] = "480p";
    char fov_string_buf[64] = "Wide";
    char error[64] = "";

    int32_t res_buf = 0;
    bool ts_buf = true;
};

void start_webcam_popup_render(Start_webcam_popup& win);
