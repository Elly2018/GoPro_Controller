#include "media_browser_popwin.h"
#include <SDL3/SDL.h>

static void draw_header(const CameraInfo& c){
    bool is_enable = c.ip.size() > 0;
    bool have_select = selected.size() > 0;
    ImGui::Dummy(ImVec2(10, 10));
    ImGui::Dummy(ImVec2(10, 10));
    ImGui::SameLine();

    if(ImGui::Button("Cancel")){
        trigger(false);
    }
    ImGui::SameLine();
    ImGui::BeginDisabled(!have_select);
    if(ImGui::Button("Copy URL")){
        
    }
    ImGui::SameLine();
    if(ImGui::Button("Download")){

    }
    ImGui::SameLine();
    if(ImGui::Button("Download To")){
        
    }
    ImGui::EndDisabled();
    ImGui::SameLine();
    if(ImGui::Button("Download All To")){
        
    }
    ImGui::SameLine();
    ImGui::BeginDisabled(!have_select);
    if(ImGui::Button("Delete")){
        
    }
    ImGui::EndDisabled();
    ImGui::SameLine();
    if(ImGui::Button("Delete All")){
        
    }

    ImGui::Dummy(ImVec2(10, 10));

    ImGui::Dummy(ImVec2(10, 10));
    ImGui::SameLine();
    ImGui::Text("Camera: %s", c.name.c_str());
}

static void draw_body(const CameraInfo& c){
    if(c.ip.size() == 0) return;
    std::lock_guard<std::mutex> lock(state->media_list_mtx);
    std::vector<MediaInfo> media_list = state->current_media_list;
    for(int i = 0; i < media_list.size(); i++){
        const MediaInfo& mi = media_list.at(i);
        if(draw_item(mi)){
            selected = mi.filename;
        }
    }
}

static bool draw_item(const MediaInfo& mi){
    return ImGui::Selectable(mi.filename.c_str(), selected == mi.filename);
}

static void open_dialog_for_download_all_folder_selection(){
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
            MediaBrowserPopup* self = static_cast<MediaBrowserPopup*>(userdata); 
            self->download_all_folder_callback(path);
        }
    }, this, win, NULL, false);
}

static void open_dialog_for_download_file_selection(){

}

static void download_all_folder_callback(const std::string folder){
    int32_t s = master->findCamera(state->current_camera_server, state->current_camera_item);
    if(s >= 0) {
        const CameraInfo ci = master->getCamera_Clone(s);
        master->download_all_media(ci.server, ci.ip, folder, state->current_media_list);
    }
}

static void download_file_callback(const std::string fullpath){
    int32_t s = master->findCamera(state->current_camera_server, state->current_camera_item);
    if(s >= 0) {
        const CameraInfo ci = master->getCamera_Clone(s);

        for(int32_t i = 0; i < state->current_media_list.size(); i++){
            const MediaInfo& mi = state->current_media_list.at(i);
            if(mi.filename == selected){
                master->download_single_media(ci.server, ci.ip, fullpath, mi);
                break;
            }
        }
    }
}

static void add_thumbnail(const std::string filename, const std::vector<u_char> rawData, const std::pair<int32_t, int32_t> resolution){
    thumbnail_rawData.insert_or_assign(filename, std::make_pair(rawData, resolution));
}

static void convert_rawData_to_texture(){
    for(auto& i : thumbnail_rawData){
        const std::string& filename = i.first;
        const std::vector<u_char>& rawData = i.second.first;
        const std::pair<int32_t, int32_t>& resolution = i.second.second;

        SDL_Texture* texture = SDL_CreateTexture(state->m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, resolution.first, resolution.second);
        if (texture) {
            // 2. Upload the raw pixel data
            // Pitch is the number of bytes in a row (width * 4 bytes for RGBA)
            SDL_UpdateTexture(texture, nullptr, rawData.data(), resolution.first * 4);
            // 3. Set filtering (Scaling mode)
            // SDL_SCALEMODE_LINEAR is the equivalent to GL_LINEAR
            SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_LINEAR);

            // 4. Store in your map
            // In SDL3 + Dear ImGui, ImTextureID is typically just the SDL_Texture pointer
            thumbnail_textures.insert_or_assign(filename, (ImTextureID)texture);
        }
    }
    thumbnail_rawData.clear();
}

static void clean_thumbnail(){
    thumbnail_rawData.clear();
}

static clean_textures(){
    for(auto& i : thumbnail_textures){
        ImTextureID textureID = i.second;
        SDL_DestroyTexture((SDL_Texture*)textureID);
    }
    thumbnail_textures.clear();
}

void MediaBrowserPopup::render(){
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec2 display_size = io.DisplaySize;
    ImVec2 unit = ImVec2(display_size.x / 12.0f, display_size.y / 12.0f);
    float unit_width;
    float unit_height;

    ImGui::SetNextWindowPos(ImVec2(unit.x * 1.0F, unit.y * 1.0F), wp_cond);
    ImGui::SetNextWindowSize(ImVec2(unit.x * 10.0F, unit.y * 10.0F), wp_cond);
    
    unit_width = (unit.x * 10.0F) / 2.0F - style.ItemSpacing.x;
    unit_height = unit.y * 9.0F;

    if(ImGui::BeginPopupModal(title.c_str(), NULL, wp_flag)){
        {
            int32_t s = master->findCamera(state->current_camera_server, state->current_camera_item);
            if(s >= 0) {
                const CameraInfo ci = master->getCamera_Clone(s);
                ImGui::BeginChild("Body##Media_Browser_ChildWin_Body", ImVec2(unit.x * 10.0F - (style.ItemSpacing.x * 2), unit.y * 7.5F));
                {
                    draw_body(ci);
                }
                ImGui::EndChild();
                ImGui::BeginChild("Header##Media_Browser_ChildWin_Header", ImVec2(unit.x * 10.0F - (style.ItemSpacing.x * 2), unit.y * 1.6F));
                {
                    draw_header(ci);
                }
                ImGui::EndChild();
            }
        }    
        ImGui::EndPopup();
    }
}
