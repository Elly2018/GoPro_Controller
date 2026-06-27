/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#ifndef POPUP_MEDIA_BROWSER_POPUP_H
#define POPUP_MEDIA_BROWSER_POPUP_H
#include "base_pop_window.h"
#include <unordered_map>
#include <imgui.h>

struct Media_browser_popup {

};

class MediaBrowserPopup : public BasePopWindow {
public:
    MediaBrowserPopup(
        std::shared_ptr<json> _setting, 
        std::shared_ptr<GlobalState> _state, 
        std::shared_ptr<GoProMaster> _master);
    ~MediaBrowserPopup();

    virtual void trigger(bool value) override;
    virtual void render() override;
protected:
    virtual void draw_header(const CameraInfo& c);
    virtual void draw_body(const CameraInfo& c);

    virtual bool draw_item(const MediaInfo& mi);
    virtual void open_dialog_for_download_all_folder_selection();
    virtual void open_dialog_for_download_file_selection();
    virtual void download_all_folder_callback(const std::string folder);
    virtual void download_file_callback(const std::string fullpath);

    virtual void add_thumbnail(const std::string filename, const std::vector<u_char> rawData, const std::pair<int32_t, int32_t> resolution);
    virtual void convert_rawData_to_texture();
    virtual void clean_thumbnail();
    virtual void clean_textures();
private:
    std::string selected = "";
    std::unordered_map<std::string, std::pair<std::vector<u_char>, std::pair<int32_t, int32_t>>> thumbnail_rawData;
    std::unordered_map<std::string, ImTextureID> thumbnail_textures;
};

#endif