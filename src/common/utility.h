/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string Get_packet(std::string key, json data) {
    json response = json::object();
    response["key"] = key;
    response["value"] = data;
    return response.dump();
}