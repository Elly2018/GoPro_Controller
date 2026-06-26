/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#include "base_window.h"

struct Inspector_window {
    Gopro_master_window base;
    
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

class InspectorWindow : public BaseWindow {
public:
    InspectorWindow(
        std::shared_ptr<json> _setting, 
        std::shared_ptr<GlobalState> _state, 
        std::shared_ptr<GoProMaster> _master);
    virtual ~InspectorWindow();

    json get_window_data() override;
    void set_window_data(json data) override;
    virtual void render() override;

    virtual void draw_header();
    virtual void draw_system();
    virtual void draw_setting();
    virtual void draw_protune();
    static void global_draw_setting(std::shared_ptr<GlobalState>& state, std::shared_ptr<GoProMaster>& master, const CameraInfo& c);
    static void global_draw_protune(std::shared_ptr<GlobalState>& state, std::shared_ptr<GoProMaster>& master, const CameraInfo& c);
    virtual void draw_status();
    virtual void draw_hardware();
    virtual void draw_network();
    virtual void draw_encode();
    virtual void draw_media_status();
    virtual void draw_media_global();
    virtual void draw_media_local();
    virtual void draw_command_local();
    virtual void draw_command_global();

    void reset_setting_order();
    void reset_status_order();
    static int32_t _get_current_model(json hwinfo);
protected:
    virtual void _draw_setting(std::vector<int32_t>& ordered);
    virtual void _draw_status(std::vector<int32_t>& ordered);
    static void _global_draw_setting(std::shared_ptr<GlobalState>& state, std::shared_ptr<GoProMaster>& master, const CameraInfo& c, std::vector<int32_t>& ordered);
    static bool _global_draw_setting_item(int32_t i, std::shared_ptr<GlobalState>& state, std::shared_ptr<GoProMaster>& master, const CameraInfo& c, std::vector<int32_t>& ordered);
    static bool conditional_filter(const std::shared_ptr<GlobalState>& state, int32_t mymodel, int32_t setting_id);
    static bool conditional_filter_option(const std::shared_ptr<GlobalState>& state, int32_t mymodel, int32_t setting_id, int32_t value_index);

    void open_dialog_for_folder_selection();
private:
};
