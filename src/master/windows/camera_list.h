/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#include "base_window.h"

enum class FilterType {
    None, Connect, Server
};

enum class SortType {
    None, Name, IP
};

struct Camera_list_window {
    ImVec2 get_rect_size();
    std::vector<CameraInfo> get_filtering_result();
    std::string get_filter_string(FilterType type);
    std::string get_sort_string(SortType type);
    std::string toTimeCode(int32_t timer);
    std::string bytesToGbString(long bytes);

    int32_t size = 1;
    FilterType filter = FilterType::None;
    SortType sort = SortType::None;

    std::string search = "";
    std::string filter_ip = "";
    bool filter_connect = false;
};

/**
 * Display camera as a grid items or list items
 * Includes some filter and sort function
 * Use this window for camera selection
*/
class CameraListWindow : public BaseWindow {
public:
    CameraListWindow(
        std::shared_ptr<json> _setting, 
        std::shared_ptr<GlobalState> _state, 
        std::shared_ptr<GoProMaster> _master);
    virtual ~CameraListWindow();

    json get_window_data() override;
    void set_window_data(json data) override;
    virtual void render() override;

    virtual void draw_line(const CameraInfo& c);
    virtual void draw_group_state(const CameraInfo& c);
    virtual void draw_group_header(const CameraInfo& c);
    virtual void item_event(const CameraInfo& c);
    void onClick(const CameraInfo& c);

private:
    ImVec2 get_rect_size();
    std::vector<CameraInfo> get_filtering_result();
    std::string get_filter_string(FilterType type);
    std::string get_sort_string(SortType type);
    std::string toTimeCode(int32_t timer);
    std::string bytesToGbString(long bytes);

    int32_t size = 1;
    FilterType filter = FilterType::None;
    SortType sort = SortType::None;

    std::string search = "";
    std::string filter_ip = "";
    bool filter_connect = false;
};