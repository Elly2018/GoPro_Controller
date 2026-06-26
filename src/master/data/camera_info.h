/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Camera_info {
    char name[64];
    char last_media[128];
    char serial[64];
    char ip[32];
    char server[32];
    bool connected;
    json state;
    json hw;
};