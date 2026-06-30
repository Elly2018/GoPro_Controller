/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef WINDOWS_INSPECTOR_H
#define WINDOWS_INSPECTOR_H
#include "base_window.h"

struct Inspector_window;
typedef void (*Inspector_window_render_func)(Inspector_window& win);

struct Inspector_window {
    Gopro_master_window base;

    Inspector_window_render_func render;

    int32_t system_list_ordered;
    
    int32_t video_setting_list_ordered;
    int32_t video_protune_list_ordered;
    int32_t photo_setting_list_ordered;
    int32_t photo_protune_list_ordered;
    int32_t burst_setting_list_ordered;
    int32_t burst_protune_list_ordered;
    
    int32_t status_software_list_ordered;
    int32_t status_hardware_list_ordered;
    int32_t status_encode_list_ordered;
    int32_t status_network_list_ordered;
    int32_t status_media_list_ordered;

    bool create_date_folder;
    bool put_finish;
    bool should_disabled;
    bool applying_all_last;
    
    int32_t media_name_rule_type;
    int32_t media_name_character_count;
};

void inspector_window_render(Inspector_window& win);

json inspector_window_get_window_data(Inspector_window& win) override;
void inspector_window_set_window_data(const json& data) override;

void inspector_window_draw_header(Inspector_window& win);
void inspector_window_draw_system(Inspector_window& win);
void inspector_window_draw_setting(Inspector_window& win);
void inspector_window_draw_protune(Inspector_window& win);
void inspector_window_global_draw_setting(Inspector_window& win, Global_state& state, Gopro_master& master, const CameraInfo& c);
void inspector_window_global_draw_protune(Inspector_window& win, Global_state& state, Gopro_master& master, const CameraInfo& c);
void inspector_window_draw_status(Inspector_window& win);
void inspector_window_draw_hardware(Inspector_window& win);
void inspector_window_draw_network(Inspector_window& win);
void inspector_window_draw_encode(Inspector_window& win);
void inspector_window_draw_media_status(Inspector_window& win);
void inspector_window_draw_media_global(Inspector_window& win);
void inspector_window_draw_media_local(Inspector_window& win);
void inspector_window_draw_command_local(Inspector_window& win);
void inspector_window_draw_command_global(Inspector_window& win);

void inspector_window_reset_setting_order(Inspector_window& win);
void inspector_window_reset_status_order(Inspector_window& win);

void inspector_window_draw_setting(Inspector_window& win, std::vector<int32_t>& ordered);
void inspector_window_draw_status(Inspector_window& win, std::vector<int32_t>& ordered);
void inspector_window_open_dialog_for_folder_selection(Inspector_window& win);

void inspector_window_static_global_draw_setting(std::shared_ptr<GlobalState>& state, std::shared_ptr<GoProMaster>& master, const CameraInfo& c, std::vector<int32_t>& ordered);
bool inspector_window_static_global_draw_setting_item(int32_t i, std::shared_ptr<GlobalState>& state, std::shared_ptr<GoProMaster>& master, const CameraInfo& c, std::vector<int32_t>& ordered);
bool inspector_window_static_conditional_filter(const std::shared_ptr<GlobalState>& state, int32_t mymodel, int32_t setting_id);
bool inspector_window_static_conditional_filter_option(const std::shared_ptr<GlobalState>& state, int32_t mymodel, int32_t setting_id, int32_t value_index);

#endif