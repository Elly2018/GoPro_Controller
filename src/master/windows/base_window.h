/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#include <chrono>
#include <mutex>
#include <thread>
#include <nlohmann/json.hpp>
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "misc/cpp/imgui_stdlib.h"
#include "../GoProMaster.h"
#include "../data/state.h"

using json = nlohmann::json;

#define w_flag ImGuiWindowFlags_NoCollapse

struct gopro_master_window {
    bool enable = false;
    std::shared_ptr<json> setting;
    std::shared_ptr<GlobalState> state;
    std::shared_ptr<GoProMaster> master;
    std::string title = "";
};

gopro_master_window_init();
gopro_master_window_dispose();

class BaseWindow {
public:
    BaseWindow(
        std::shared_ptr<json> _setting, 
        std::shared_ptr<GlobalState> _state, 
        std::shared_ptr<GoProMaster> _master);
    ~BaseWindow();

    /**
     * Current window visibility
     */
    std::string get_title();
    bool is_enable();

    /**
     * Is enable being triiger right now
     */
    virtual json get_window_data();
    virtual void set_window_data(json data);
    virtual void trigger(bool value);
    virtual void update();
    virtual void render();
    virtual bool is_close();
    virtual void save_setting();
protected:
    bool enable = false;
    std::shared_ptr<json> setting;
    std::shared_ptr<GlobalState> state;
    std::shared_ptr<GoProMaster> master;
    std::string title = "";
};