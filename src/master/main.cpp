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

void assign_log(std::string key, std::string value){
    if(execution_logs.count(key)){
        std::string b = execution_logs.at(key);
        execution_logs.insert_or_assign(key, b + "\n" + value);
    }else{
        execution_logs.insert_or_assign(key, value);
    }
}

void setting_getter_feedback(std::string ip, json setting){
    if(global_state->current_camera_item == ip){
        global_state->current_setting_items = setting;
        global_state->current_setting_items_bind = true;
    }
}

void status_getter_feedback(std::string ip, json status){
    if(global_state->current_camera_item == ip){
        global_state->current_status_items = status;
        global_state->current_status_items_bind = true;
    }
}

void HW_getter_feedback(std::string ip, json hw){
    if(global_state->current_camera_item == ip){
        global_state->current_hw_items = hw;
        global_state->current_hw_items_bind = true;
    }
}

void apply_feedbacks(){
    global_state->applying_all_count++;
    if(global_state->applying_all_count >= master->getServerCount()){
        global_state->applying_all = false;
    }
}

void update_media_list(std::vector<MediaInfo> data){
    std::lock_guard<std::mutex> lock(global_state->media_list_mtx);
    global_state->current_media_list = data;
}

int main(int, char**) {
    AppData data = AppData();
    
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    
    SDL_Window* window;
    SDL_GLContext gl_context;

    const char* glsl_version;
    {
        std::tuple<SDL_Window*, const char*> sdl_ctx;
        begin_sdl(sdl_ctx);
        
        window = std::get<0>(sdl_ctx);
        glsl_version = std::get<1>(sdl_ctx);

        gl_context = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, gl_context);
    }
    
    data.global_state.m_renderer = SDL_CreateRenderer(window, NULL);

    init(data);
    setup_imgui();
    init_state_setup(data);
    begin_imgui(window, gl_context, glsl_version);

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    while (!data.should_quit)
    {
        int focus = -1;
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                data.should_quit = true;
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window))
                data.should_quit = true;
            
            // Hotkeys
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

        for(auto& w : windows_array){
            if(w && w->is_enable()){
                w->update();
            }
        }
        for(auto& w : pop_windows_array){
            if(w && w->is_open()){
                w->update();
            }
        }

        // Start the Dear ImGui frame
        begin_loop();

        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("Windows")) {
            bool update_menu = false;
            if(ImGui::MenuItem("Websocket Dashboard (Q)", NULL, websocket_win->is_enable())){
                websocket_win->trigger(!websocket_win->is_enable());
                update_menu = true;
            }
            if(ImGui::MenuItem("Camera List (E)", NULL, camera_list_win->is_enable())){
                camera_list_win->trigger(!camera_list_win->is_enable());
                update_menu = true;
            }
            if(ImGui::MenuItem("Inspector (R)", NULL, inspector_win->is_enable())){
                inspector_win->trigger(!inspector_win->is_enable());
                update_menu = true;
            }
            if(ImGui::MenuItem("Style (T)", NULL, style_setting_win->is_enable())){
                style_setting_win->trigger(!style_setting_win->is_enable());
                update_menu = true;
            }
            ImGui::Separator();
            //update_menu = update_menu || ImGui::MenuItem("System Style", NULL, &system_style_win);
            ImGui::EndMenu();
            if(update_menu){
                updateGUIList();
            }
        }
        ImGui::EndMainMenuBar();

        int counter = 0;
        for(auto& w : windows_array){
            if(focus != -1 && focus == counter){
                ImGui::SetNextWindowFocus();
            }
            if(w && w->is_enable()){
                w->render();
                if(w->is_close()){
                    w->trigger(false);
                    updateGUIList();
                }
            }
            counter++;
        }

        for(auto& w : pop_windows_array){
            if(w){
                w->detect();
            }
        }

        for(auto& w : pop_windows_array){
            if(w){
                w->render();
            }
        }

        // Render toasts on top of everything, at the end of your code!
        // You should push style vars here
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
        ImGui::RenderNotifications();
        ImGui::PopStyleVar(1); // Don't forget to Pop()

        // Rendering
        ImGui::Render();
        end_loop(window, io);
    }

    master->setdone();
    master->disconnectAll();
    if(bg_thread.joinable()){
        bg_thread.join();
    }
    // Cleanup
    end_imgui();
    SDL_GL_DestroyContext(gl_context);
    end_sdl(window);
}

