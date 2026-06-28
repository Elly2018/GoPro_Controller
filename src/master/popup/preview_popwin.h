/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef POPUP_PREVIEW_POPWIN_H
#define POPUP_PREVIEW_POPWIN_H
#include <queue>
#include <mutex>
#include <thread>
#include <functional>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma comment(lib, "setupapi.lib") 
#pragma comment(lib, "version.lib") 
#pragma comment(lib, "Wtsapi32.lib")
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "Gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "imm32.lib") 
#pragma comment(lib, "OleAut32.lib") 
#pragma comment(lib, "Iphlpapi.lib")

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "vfw32.lib")
#pragma comment(lib, "msvfw32.lib")

#endif
#include <SDL3/SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL3/SDL_opengles2.h>
#else
#include <SDL3/SDL_opengl.h>
#endif
#include <opencv2/opencv.hpp>
#include "base_pop_window.h"

struct Preview_popup;
typedef void (*Preview_popup_render_func)(Preview_popup& win);
typedef void (*Preview_popup_drawer_func)(Global_state& state, Gopro_master& master, const Camera_info& c);

struct Preview_popup {
    constexpr uint64_t MAX_QUEUE_SIZE = 10UL;
    constexpr uint64_t MAX_REDECODE = 2UL;
    constexpr uint64_t MAX_ATTEMPT = 300UL;

    Gopro_master_popup_window base;

    Preview_popup_render_func render;

    Preview_popup_drawer_func setting_drawer;
    Preview_popup_drawer_func protune_drawer;

    cv::VideoCapture cap;
    std::string pipeline;
    std::queue<cv::Mat> frame_queue;
    std::mutex queue_mutex;
    std::thread reader;
    
    SDL_Renderer* renderer = NULL;
    GLuint gl_texture = 0;
    
    int32_t dir = 0;
    int32_t texture_width = 1920;
    int32_t texture_height = 1080;

    bool first = true;
    bool applying_all_last;
    bool trying = false;
    bool remap = false;
    bool stream_open = false;
};

void preview_popup_render(Preview_popup& win);
void preview_popup_update_decoder(Preview_popup& win);

json preview_popup_get_window_data(Preview_popup& win);
void preview_popup_set_window_data(Preview_popup& win, const json& data);

int32_t preview_popup_get_current_model(const json& target);
void preview_popup_stop_thread(Preview_popup& win);
void preview_popup_draw_rotation_button(Preview_popup& win);
void preview_popup_draw_camera_selection(Preview_popup& win);
void preview_popup_draw_bottom_button(Preview_popup& win);
void preview_popup_draw_setting(Preview_popup& win);

cv::Mat preview_popup_get_latest_frame(Preview_popup& win);
void preview_popup_convert_texture(Preview_popup& win, cv::Mat& mat);
void preview_popup_dir_change(Preview_popup& win, const bool increase);

#endif