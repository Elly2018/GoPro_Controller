/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <thread>
#include "GoProMaster.h"
#include "utility.h"
#include "data/app.h"
#include "../common/camera_code.h"
#include "windows/wins.h"
#include "popup/popwins.h"
#include "imgui_helper.h"
#include "src/imgui_notify.h"

static bool window_render_base (Gopro_master_window& target) {
    if(target.enable != target.enable_last){
        target.enable_last = target.enable;
        return true
    }
    return false;
}

static void popup_render_base (Gopro_master_popup_window& target) {
    if(target.base.enable != target.base.enable_last){
        if(!target.base.enable) {
            ImGui::CloseCurrentPopup();
        }else{
            ImGui::OpenPopup(&target.base.title);
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        }
        target.isopen = target.base.enable;
        target.base.enable_last = target.base.enable;
    }
}

static bool window_render (AppData& data, int32_t focus) {
    bool a = false;

    if(focus == 0) ImGui::SetNextWindowFocus();
    data.websocket_window.render(data.websocket_window);
    a = a || window_render_base(data.websocket_window_base);

    if(focus == 1) ImGui::SetNextWindowFocus();
    data.camera_list_window.render(data.camera_list_window);
    a = a || window_render_base(data.camera_list_window_base);

    if(focus == 2) ImGui::SetNextWindowFocus();
    data.inspector_window.render(data.inspector_window);
    a = a || window_render_base(data.inspector_window_base);

    if(focus == 3) ImGui::SetNextWindowFocus();
    data.style_window.render(data.style_window);
    a = a || window_render_base(data.style_window_base);

    return a;
}

static void popup_render (AppData& data) {
    data.add_camera_popup_window.render(data.add_camera_popup_window);
    popup_render_base(data.add_camera_popup_window_base);

    data.scan_camera_popup_window.render(data.scan_camera_popup_window);
    popup_render_base(data.scan_camera_popup_window_base);

    data.start_webcam_popup_window.render(data.start_webcam_popup_window);
    popup_render_base(data.start_webcam_popup_window_base);

    data.preview_popup_window.render(data.preview_popup_window);
    popup_render_base(data.preview_popup_window_base);

    data.add_preset_popup_window.render(data.add_preset_popup_window);
    popup_render_base(data.add_preset_popup_window_base);

    data.preset_manager_popup_window.render(data.preset_manager_popup_window);
    popup_render_base(data.preset_manager_popup_window_base);

    data.media_browser_popup_window.render(data.media_browser_popup_window);
    popup_render_base(data.media_browser_popup_window_base);
}

static void main_menubar(AppData& data) {
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("Windows")) {
        bool update_menu = false;
        if(ImGui::MenuItem("Websocket Dashboard (Q)", NULL, data.websocket_window_base.enable)){
            data.websocket_window_base = !data.websocket_window_base;
            update_menu = true;
        }
        if(ImGui::MenuItem("Camera List (E)", NULL, data.camera_list_window_base.enable)){
            data.camera_list_window_base.enable = !data.camera_list_window_base.enable;
            update_menu = true;
        }
        if(ImGui::MenuItem("Inspector (R)", NULL, data.inspector_window_base.enable)){
            data.inspector_window_base.enable = !data.inspector_window_base.enable;
            update_menu = true;
        }
        if(ImGui::MenuItem("Style (T)", NULL, data.style_window_base.enable)){
            data.style_window_base.enable = !data.style_window_base.enable;
            update_menu = true;
        }

        ImGui::Separator();
        
        ImGui::EndMenu();

        if(update_menu){
            data.global_state.update_GUI(data);
        }
    }
    ImGui::EndMainMenuBar();
}

static void event_poll(AppData& data, int32_t &focus) {
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL3_ProcessEvent(&event);

        if (event.type == SDL_EVENT_QUIT){
            data.should_quit = true;
        }
        if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window)){
            data.should_quit = true;
        }
        
        if (event.type == SDL_EVENT_KEY_DOWN) {
            if (event.key.key == SDLK_F2) {
                master->command_only("shutter_on");
                printf("Hotkey F2: Start Recording\n");
            }
            if (event.key.key == SDLK_F3) {
                master->command_only("shutter_off");
                printf("Hotkey F3: Stop Recording\n");
            }
            if (event.key.key == SDLK_F4 && (event.key.mod & SDL_KMOD_LSHIFT)) {
                master->presetSwitch("", "", 65538);
                printf("Hotkey F4 + Shift: Photo Burst Mode\n");
            }
            if (event.key.key == SDLK_F4 && !(event.key.mod & SDL_KMOD_LSHIFT)) {
                master->presetSwitch("", "", 65536);
                printf("Hotkey F4: Photo Mode\n");
            }
            if (event.key.key == SDLK_F5) {
                master->presetSwitch("", "", 0);
                printf("Hotkey F5: Video Mode\n");
            }

            bool textinput_current = io.WantTextInput;

            if (event.key.key == SDLK_F11) {
                uint32_t flag = SDL_GetWindowFlags(window);
                if ((flag & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN) {
                    SDL_SetWindowFullscreen(window, false);
                    printf("Window using exclusive (true) fullscreen mode\n");
                } else {
                    SDL_SetWindowFullscreen(window, true);
                    printf("Window in windowed mode\n");
                }
            }

            if(!textinput_current){
                if (event.key.key == SDLK_Q) {
                    if(event.key.mod & SDL_KMOD_LSHIFT){
                        focus = 0;
                    }else{
                        websocket_win->trigger(!websocket_win->is_enable());
                        updateGUIList();
                    }
                }
                if (event.key.key == SDLK_W) {
                    if(event.key.mod & SDL_KMOD_LSHIFT){
                        focus = 1;
                    }else{
                        camera_list_win->trigger(!camera_list_win->is_enable());
                        updateGUIList();
                    }
                }
                if (event.key.key == SDLK_E) {
                    if(event.key.mod & SDL_KMOD_LSHIFT){
                        focus = 2;
                    }else{
                        inspector_win->trigger(!inspector_win->is_enable());
                        updateGUIList();
                    }
                }
                if (event.key.key == SDLK_R) {
                    if(event.key.mod & SDL_KMOD_LSHIFT){
                        focus = 3;
                    }else{
                        style_setting_win->trigger(!style_setting_win->is_enable());
                        updateGUIList();
                    }
                }
            }
        }
    }
    
    data.global_state.update_event(data);
}

static void mainloop(AppData& data){
    int focus = -1;

    event_poll(data, focus);

    gopro_master_update(data);

    begin_loop();

    main_menubar(data);

    bool should_update_GUI = window_render(data, focus);

    if(should_update_GUI){
        data.global_state.update_GUI(data);
    }

    popup_render();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
    ImGui::RenderNotifications();
    ImGui::PopStyleVar(1);

    ImGui::Render();
    end_loop(window, io);
}

int main(int, char**) {
    AppData data = AppData();
    
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    
    SDL_Window* window;
    SDL_GLContext gl_context;

    const char* glsl_version;
    std::tuple<SDL_Window*, const char*> sdl_ctx;
    begin_sdl(sdl_ctx);

    window = std::get<0>(sdl_ctx);
    glsl_version = std::get<1>(sdl_ctx);
    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    
    data.global_state.m_renderer = SDL_CreateRenderer(window, NULL);

    init(data);
    setup_imgui();
    init_state_setup(data);
    begin_imgui(window, gl_context, glsl_version);

    while (!data.should_quit) {
        mainloop(data);
    }

    master->setdone();
    master->disconnectAll();
    if(bg_thread.joinable()){
        bg_thread.join();
    }
    
    end_imgui();
    SDL_GL_DestroyContext(gl_context);
    end_sdl(window);
}

