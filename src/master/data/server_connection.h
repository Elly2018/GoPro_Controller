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
    bool connected = false;
    hv::WebSocketClient client;
};