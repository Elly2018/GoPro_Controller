/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#include <string>
#include "hv/WebSocketClient.h"

struct Server_connection {
    char ip [32];
    hv::WebSocketClient client;
    bool connected;
    bool vaild;
    bool query_ip;
    bool query_get_all;
    bool query_last_media;
};