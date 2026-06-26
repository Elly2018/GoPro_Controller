/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef WINDOWS_WEBSOCKET_SERVER_H
#define WINDOWS_WEBSOCKET_SERVER_H
#include "base_window.h"

struct Websocket_window;
typedef void (*Websocket_window_render_func)(Websocket_window& win);

struct Websocket_window {
    Gopro_master_window base;

    Websocket_window_render_func render;

    char server_ip_buf[32];
};

void websocket_window_render(Websocket_window& win);

#endif