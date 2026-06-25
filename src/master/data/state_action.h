/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef DATA_STATE_ACTION_H
#define DATA_STATE_ACTION_H
#include <nlohmann/json.hpp>
#include "app.h"

using json = nlohmann::json;

struct Global_state;
struct Gopro_master;

void init_state_setup(json servers, json gui, AppData& app);
json get_global_state_data(struct GlobalState& data);
void set_global_state_data(struct GlobalState& data, json refs);

#endif