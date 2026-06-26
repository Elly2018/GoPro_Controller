/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef UTILITY_H
#define UTILITY_H
#include "data/app.h"
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void saveServerList(json data);
json loadServerList();

void savePresetList(json data);
json loadPresetList();

void saveGUI(json data);
json loadGUI();

void init(AppData& data);
void init_state_setup(AppData& data);

#endif