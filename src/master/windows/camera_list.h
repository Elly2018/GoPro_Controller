/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef WINDOWS_CAMERA_LIST
#define WINDOWS_CAMERA_LIST
#include "base_window.h"

enum class FilterType {
    None, Connect, Server
};

enum class SortType {
    None, Name, IP
};

struct Camera_list_window {
    Gopro_master_window base;

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

virtual void draw_line(const CameraInfo& c);
virtual void draw_group_state(const CameraInfo& c);
virtual void draw_group_header(const CameraInfo& c);
virtual void item_event(const CameraInfo& c);
void onClick(const CameraInfo& c);

ImVec2 camera_list_window_get_rect_size();
std::vector<CameraInfo> get_filtering_result();
std::string get_filter_string(FilterType type);
std::string get_sort_string(SortType type);
std::string toTimeCode(int32_t timer);
std::string bytesToGbString(long bytes);

#endif