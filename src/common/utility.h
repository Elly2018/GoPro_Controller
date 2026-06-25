/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef GCG_UTILITY_H
#define GCG_UTILITY_H
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

inline std::string Get_packet(std::string key, json data) {
    json response = json::object();
    response["key"] = key;
    response["value"] = data;
    return response.dump();
};

#endif