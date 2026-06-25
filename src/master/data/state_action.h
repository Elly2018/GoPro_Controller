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

using json = nlohmann::json;

struct GlobalState;
struct GoProMaster;
struct BaseWindow;
struct BasePopWindow;

extern "C" void init_state_setup(
    std::shared_ptr<json> servers,
    std::shared_ptr<json> gui,
    std::shared_ptr<struct GlobalState> global_state,
    std::shared_ptr<struct GoProMaster> master,
    std::shared_ptr<struct BaseWindow> windows[],
    std::shared_ptr<struct BasePopWindow> popwins[]
);
extern "C" json get_global_state_data(struct GlobalState& data);
extern "C" void set_global_state_data(struct GlobalState& data, json refs);

#endif