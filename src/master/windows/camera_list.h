/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef WINDOWS_CAMERA_LIST_H
#define WINDOWS_CAMERA_LIST_H
#include "base_window.h"

struct Camera_list_window;
typedef void (*Camera_list_window_render_func)(Camera_list_window& win);

enum class FilterType {
    None, Connect, Server
};

enum class SortType {
    None, Name, IP
};

struct Camera_list_window {
    Gopro_master_window base;

    Camera_list_window_render_func render;

    int32_t size = 1;
    FilterType filter = FilterType::None;
    SortType sort = SortType::None;

    char search[128];
    char filter_ip[128];
    bool filter_connect = false;
};

json camera_list_window_get_window_data(Camera_list_window& win);
void camera_list_window_set_window_data(Camera_list_window& win, const json& data);
void camera_list_window_render(Camera_list_window& win);

void camera_list_window_draw_line(Camera_list_window& win, const CameraInfo& c);
void camera_list_window_item_event(Camera_list_window& win, const CameraInfo& c);
void camera_list_window_on_click(Camera_list_window& win, const CameraInfo& c);

ImVec2 camera_list_window_get_rect_size(Camera_list_window& win);
std::vector<CameraInfo> camera_list_window_get_filtering_result(Camera_list_window& win);
std::string camera_list_window_get_filter_string(const FilterType type);
std::string camera_list_window_get_sort_string(const SortType type);
std::string camera_list_window_toTimeCode(const int32_t timer);
std::string camera_list_window_bytesToGbString(const long bytes);

void camera_list_window_draw_group_state(Camera_list_window& win, const CameraInfo& c);
void camera_list_window_draw_group_header(Camera_list_window& win, const CameraInfo& c);

#endif