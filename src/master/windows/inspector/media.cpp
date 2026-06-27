/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "../inspector.h"
#include <cstdlib>      // For std::getenv
#include <filesystem>
#include <stdexcept>
#include <SDL3/SDL.h>

namespace fs = std::filesystem;

std::filesystem::path get_home_directory() {
    const char* home_dir = nullptr;

#if defined(_WIN32) || defined(_WIN64)
    // Windows: Check USERPROFILE or HOMEDRIVE/HOMEPATH
    home_dir = std::getenv("USERPROFILE");
    if (!home_dir) {
        const char* drive = std::getenv("HOMEDRIVE");
        const char* path = std::getenv("HOMEPATH");
        if (drive && path) {
            return std::filesystem::path(drive) / path;
        }
    }
#else
    // Unix-like systems (Linux, macOS, etc.): Check HOME
    home_dir = std::getenv("HOME");
#endif

    if (home_dir) {
        return std::filesystem::path(home_dir);
    } else {
        // Fallback or throw an error if the home directory cannot be found
        throw std::runtime_error("Could not find home directory");
    }
}

void InspectorWindow::draw_media_global(){
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec2 size = ImGui::GetWindowSize();
    ImVec2 button_size = ImVec2(size.x / 2.0F - style.ItemSpacing.x, 0);
    ImVec2 button3_size = ImVec2(size.x / 3.0F - style.ItemSpacing.x, 0);

    DownloadMediaParameters params;
    params.dir = state->current_download_location;
    params.put_finish = put_finish;
    params.type = media_name_rule_type;
    params.c_count = media_name_character_count;

    int32_t camera_ip = master->findCamera(state->current_camera_server, state->current_camera_item);
    if(ImGui::InputText("Media Download", &state->current_download_location)){
        state->update_server();
    }
    if(ImGui::Button("All Download", button3_size)){
        std::string buffer = state->current_download_location;
        while(buffer.size() > 0 && buffer.at(buffer.size() - 1) == '/'){
            buffer.pop_back();
        }
        if(master->directoryExists(buffer)){
            if(create_date_folder){
                std::string date = getCurrentDateTimeString();
                buffer.append("/" + date);
            }
            fs::create_directories(buffer);
            params.dir = buffer;
            master->download_last_media("", params);
        }
    }
    if(ImGui::IsItemHovered()) ImGui::SetTooltip("Download all exist camera instances");
    ImGui::SameLine();
    if(ImGui::Button("Single Download", button3_size)){
        std::string buffer = state->current_download_location;
        while(buffer.size() > 0 && buffer.at(buffer.size() - 1) == '/'){
            buffer.pop_back();
        }
        if(master->directoryExists(buffer)){
            if(create_date_folder){
                std::string date = getCurrentDateTimeString();
                buffer.append("/" + date);
            }
            fs::create_directories(buffer);
            params.dir = buffer;
            master->download_last_media(state->current_camera_item, params);
        }
    }
    ImGui::SameLine();
    if(ImGui::Button("Media Browser", button3_size)){
        state->command_sender("media_browser");
    }
    if(ImGui::IsItemHovered()) ImGui::SetTooltip("Download current select camera instance");

    if(ImGui::Button("Open Home", button3_size)){
        std::system((std::string("open \"") + get_home_directory().string() + std::string("\"")).c_str());
    }
    if(ImGui::IsItemHovered()) ImGui::SetTooltip("Open file explorer for home directory");
    ImGui::SameLine();
    if(ImGui::Button("Open Select Path", button3_size)){
        std::system((std::string("open \"") + state->current_download_location + std::string("\"")).c_str());
    }
    ImGui::SameLine();
    if(ImGui::Button("Pick Path", button3_size)){
        open_dialog_for_folder_selection();
    }

    if(ImGui::Checkbox("Create Date Folder", &create_date_folder)){
        state->update_server();
    }
    if(ImGui::Checkbox("Added Finish File", &put_finish)){
        state->update_server();
    }

    const char* selection = MEDIA_DOWNLOAD_TYPE_STRING[media_name_rule_type];
    if(ImGui::BeginCombo("Media Name Rule", selection)){
        for(int32_t i = 0; i < MEDIA_DOWNLOAD_TYPE_SIZE; i++){
            bool selected = (media_name_rule_type == i);
            if(ImGui::Selectable(MEDIA_DOWNLOAD_TYPE_STRING[i], selected)){
                media_name_rule_type = i;
                state->update_server();
            }
            if(selected){
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    if(media_name_rule_type > 0){
        if(ImGui::InputInt("Character Count", &media_name_character_count, 1, 5)){
            if(media_name_character_count < 1) media_name_character_count = 1;
            state->update_server();
        }
    }

    if(ImGui::IsItemHovered()) ImGui::SetTooltip("Open file explorer for path select directory");
    if(camera_ip >= 0){
        std::shared_ptr<CameraInfo> t = master->getCameras()[camera_ip];
        ImGui::LabelText("Server", "%s", t->server.c_str());
        ImGui::LabelText("Last Media", "%s", t->last_media.c_str());
    }
}

void InspectorWindow::draw_media_local(){

}

void InspectorWindow::open_dialog_for_folder_selection(){
    SDL_Window* win = SDL_GL_GetCurrentWindow();
    SDL_ShowOpenFolderDialog([](void* userdata, const char* const* filelist, int filter){
        if (!filelist) {
            SDL_Log("Error opening file dialog: %s", SDL_GetError());
        } else if (!*filelist) {
            SDL_Log("User canceled the dialog.");
        } else {
            std::string path = "";
            while (*filelist) {
                SDL_Log("Selected file: %s", *filelist);
                path = *filelist;
                filelist++;
            }
            InspectorWindow* self = static_cast<InspectorWindow*>(userdata); 
            self->state->current_download_location = path;
            self->state->update_server();
        }
    }, this, win, NULL, false);
}
