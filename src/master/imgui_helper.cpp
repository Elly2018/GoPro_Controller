/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#include "imgui_helper.h"
#include <memory>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <tuple>
#include <filesystem>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#pragma comment(lib, "setupapi.lib") 
#pragma comment(lib, "version.lib") 
#pragma comment(lib, "Wtsapi32.lib")
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "Gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "imm32.lib") 
#pragma comment(lib, "OleAut32.lib") 
#pragma comment(lib, "Iphlpapi.lib")

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "vfw32.lib")
#pragma comment(lib, "msvfw32.lib")

#endif
#include <SDL3/SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL3/SDL_opengles2.h>
#else
#include <SDL3/SDL_opengl.h>
#endif
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include "windows/base_window.h"

#include "src/imgui_notify.h"
#include "tahoma.h"

namespace fs = std::filesystem;

void setup_imgui(){
    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
#ifdef _WIN32
    io.Fonts->AddFontFromFileTTF("SourceHanSans-Medium.otf", 0.0f, NULL, io.Fonts->GetGlyphRangesDefault());
    io.Fonts->AddFontFromFileTTF("SourceHanSansK-Medium.otf", 0.0f, NULL, io.Fonts->GetGlyphRangesKorean());
    io.Fonts->AddFontFromFileTTF("SourceHanSansTC-Medium.otf", 0.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
#else
    if(fs::exists("SourceHanSans-Medium.otf")) io.Fonts->AddFontFromFileTTF("SourceHanSans-Medium.otf", 0.0f, NULL, io.Fonts->GetGlyphRangesDefault());
    else io.Fonts->AddFontFromFileTTF("/usr/share/fonts/truetype/SourceHanSans-Medium.otf", 0.0f, NULL, io.Fonts->GetGlyphRangesDefault());
    
    if(fs::exists("SourceHanSansK-Medium.otf")) io.Fonts->AddFontFromFileTTF("SourceHanSansK-Medium.otf", 0.0f, NULL, io.Fonts->GetGlyphRangesDefault());
    else io.Fonts->AddFontFromFileTTF("/usr/share/fonts/truetype/SourceHanSansK-Medium.otf", 0.0f, NULL, io.Fonts->GetGlyphRangesDefault());

    if(fs::exists("SourceHanSansTC-Medium.otf")) io.Fonts->AddFontFromFileTTF("SourceHanSansTC-Medium.otf", 0.0f, NULL, io.Fonts->GetGlyphRangesDefault());
    else io.Fonts->AddFontFromFileTTF("/usr/share/fonts/truetype/SourceHanSansTC-Medium.otf", 0.0f, NULL, io.Fonts->GetGlyphRangesDefault());

    {
        ImFontConfig font_cfg;
        font_cfg.FontDataOwnedByAtlas = false;
        io.Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), 17.f, &font_cfg);

        // Initialize notify
        ImGui::MergeIconsWithLatestFont(16.f, false);
    }
#endif
    
    io.FontGlobalScale = 1.0f;
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    io.ConfigErrorRecovery = true;
    io.ConfigErrorRecoveryEnableAssert = true;
    io.ConfigErrorRecoveryEnableDebugLog = true;
    io.ConfigErrorRecoveryEnableTooltip = true;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
#ifdef _WIN32
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
#endif
    io.ConfigDockingAlwaysTabBar = true;
    io.ConfigDpiScaleFonts = true;
    io.ConfigDpiScaleViewports = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);
}
/**
 * Setup build-in theme
 */
void setup_catppuccin_mocha_theme() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Catppuccin Mocha Palette
    // --------------------------------------------------------
    const ImVec4 base       = ImVec4(0.117f, 0.117f, 0.172f, 1.0f); // #1e1e2e
    const ImVec4 mantle     = ImVec4(0.109f, 0.109f, 0.156f, 1.0f); // #181825
    const ImVec4 surface0   = ImVec4(0.200f, 0.207f, 0.286f, 1.0f); // #313244
    const ImVec4 surface1   = ImVec4(0.247f, 0.254f, 0.337f, 1.0f); // #3f4056
    const ImVec4 surface2   = ImVec4(0.290f, 0.301f, 0.388f, 1.0f); // #4a4d63
    const ImVec4 overlay0   = ImVec4(0.396f, 0.403f, 0.486f, 1.0f); // #65677c
    const ImVec4 overlay2   = ImVec4(0.576f, 0.584f, 0.654f, 1.0f); // #9399b2
    const ImVec4 text       = ImVec4(0.803f, 0.815f, 0.878f, 1.0f); // #cdd6f4
    const ImVec4 subtext0   = ImVec4(0.639f, 0.658f, 0.764f, 1.0f); // #a3a8c3
    const ImVec4 mauve      = ImVec4(0.796f, 0.698f, 0.972f, 1.0f); // #cba6f7
    const ImVec4 peach      = ImVec4(0.980f, 0.709f, 0.572f, 1.0f); // #fab387
    const ImVec4 yellow     = ImVec4(0.980f, 0.913f, 0.596f, 1.0f); // #f9e2af
    const ImVec4 green      = ImVec4(0.650f, 0.890f, 0.631f, 1.0f); // #a6e3a1
    const ImVec4 teal       = ImVec4(0.580f, 0.886f, 0.819f, 1.0f); // #94e2d5
    const ImVec4 sapphire   = ImVec4(0.458f, 0.784f, 0.878f, 1.0f); // #74c7ec
    const ImVec4 blue       = ImVec4(0.533f, 0.698f, 0.976f, 1.0f); // #89b4fa
    const ImVec4 lavender   = ImVec4(0.709f, 0.764f, 0.980f, 1.0f); // #b4befe

    // Main window and backgrounds
    colors[ImGuiCol_WindowBg]             = base;
    colors[ImGuiCol_ChildBg]              = base;
    colors[ImGuiCol_PopupBg]              = surface0;
    colors[ImGuiCol_Border]               = surface1;
    colors[ImGuiCol_BorderShadow]         = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    colors[ImGuiCol_FrameBg]              = surface0;
    colors[ImGuiCol_FrameBgHovered]       = surface1;
    colors[ImGuiCol_FrameBgActive]        = surface2;
    colors[ImGuiCol_TitleBg]              = mantle;
    colors[ImGuiCol_TitleBgActive]        = surface0;
    colors[ImGuiCol_TitleBgCollapsed]     = mantle;
    colors[ImGuiCol_MenuBarBg]            = mantle;
    colors[ImGuiCol_ScrollbarBg]          = surface0;
    colors[ImGuiCol_ScrollbarGrab]        = surface2;
    colors[ImGuiCol_ScrollbarGrabHovered] = overlay0;
    colors[ImGuiCol_ScrollbarGrabActive]  = overlay2;
    colors[ImGuiCol_CheckMark]            = green;
    colors[ImGuiCol_SliderGrab]           = sapphire;
    colors[ImGuiCol_SliderGrabActive]     = blue;
    colors[ImGuiCol_Button]               = surface0;
    colors[ImGuiCol_ButtonHovered]        = surface1;
    colors[ImGuiCol_ButtonActive]         = surface2;
    colors[ImGuiCol_Header]               = surface0;
    colors[ImGuiCol_HeaderHovered]        = surface1;
    colors[ImGuiCol_HeaderActive]         = surface2;
    colors[ImGuiCol_Separator]            = surface1;
    colors[ImGuiCol_SeparatorHovered]     = mauve;
    colors[ImGuiCol_SeparatorActive]      = mauve;
    colors[ImGuiCol_ResizeGrip]           = surface2;
    colors[ImGuiCol_ResizeGripHovered]    = mauve;
    colors[ImGuiCol_ResizeGripActive]     = mauve;
    colors[ImGuiCol_Tab]                  = surface0;
    colors[ImGuiCol_TabHovered]           = surface2;
    colors[ImGuiCol_TabActive]            = surface1;
    colors[ImGuiCol_TabUnfocused]         = surface0;
    colors[ImGuiCol_TabUnfocusedActive]   = surface1;
    colors[ImGuiCol_DockingPreview]       = sapphire;
    colors[ImGuiCol_DockingEmptyBg]       = base;
    colors[ImGuiCol_PlotLines]            = blue;
    colors[ImGuiCol_PlotLinesHovered]     = peach;
    colors[ImGuiCol_PlotHistogram]        = teal;
    colors[ImGuiCol_PlotHistogramHovered] = green;
    colors[ImGuiCol_TableHeaderBg]        = surface0;
    colors[ImGuiCol_TableBorderStrong]    = surface1;
    colors[ImGuiCol_TableBorderLight]     = surface0;
    colors[ImGuiCol_TableRowBg]           = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    colors[ImGuiCol_TableRowBgAlt]        = ImVec4(1.0f, 1.0f, 1.0f, 0.06f);
    colors[ImGuiCol_TextSelectedBg]       = surface2;
    colors[ImGuiCol_DragDropTarget]       = yellow;
    colors[ImGuiCol_NavHighlight]         = lavender;
    colors[ImGuiCol_NavWindowingHighlight]= ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
    colors[ImGuiCol_NavWindowingDimBg]    = ImVec4(0.8f, 0.8f, 0.8f, 0.2f);
    colors[ImGuiCol_ModalWindowDimBg]     = ImVec4(0.0f, 0.0f, 0.0f, 0.35f);
    colors[ImGuiCol_Text]                 = text;
    colors[ImGuiCol_TextDisabled]         = subtext0;

    // Rounded corners
    style.WindowRounding    = 6.0f;
    style.ChildRounding     = 6.0f;
    style.FrameRounding     = 4.0f;
    style.PopupRounding     = 4.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabRounding      = 4.0f;
    style.TabRounding       = 4.0f;

    // Padding and spacing
    style.WindowPadding     = ImVec2(8.0f, 8.0f);
    style.FramePadding      = ImVec2(16.0f, 5.0f);
    style.ItemSpacing       = ImVec2(8.0f, 4.0f);
    style.ItemInnerSpacing  = ImVec2(4.0f, 4.0f);
    style.IndentSpacing     = 21.0f;
    style.ScrollbarSize     = 20.0f;
    style.GrabMinSize       = 10.0f;

    // Borders
    style.WindowBorderSize  = 1.0f;
    style.ChildBorderSize   = 1.0f;
    style.PopupBorderSize   = 1.0f;
    style.FrameBorderSize   = 1.0f;
    style.TabBorderSize     = 0.0f;
    style.TabRounding       = 12.0f;
}
/**
 * Create the imgui context, use it in the begining and out of the loop
 */
void begin_imgui(struct SDL_Window *window, void *sdl_gl_context, const char *glsl_version){
    ImGui_ImplSDL3_InitForOpenGL(window, sdl_gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);
}
/**
 * Destory the imgui context, use it in the end and out of the loop
 */
void end_imgui(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}
/**
 * Create the SDL context
 */
void begin_sdl(std::tuple<struct SDL_Window*, const char*>& r){
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        printf("Error: SDL_Init(): %s\n", SDL_GetError());
        exit(1);
    }
#ifdef _WIN32
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
#endif

    const char* video_driver = SDL_GetCurrentVideoDriver();
    std::cout << "SDL Video Driver: " << video_driver << std::endl;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100 (WebGL 1.0)
    const char* glsl_version = "#version 100";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(IMGUI_IMPL_OPENGL_ES3)
    // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
    const char* glsl_version = "#version 300 es";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    const char* glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif
    // Create window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    SDL_WindowFlags window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
    SDL_Window* window = SDL_CreateWindow("GoPro Controller Master", (int)(1280 * main_scale), (int)(800 * main_scale), window_flags);
    if (window == nullptr)
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        exit(1);
    }
    SDL_GL_SetSwapInterval(1); // Enable vsync
    SDL_ShowWindow(window);
    r = {window, glsl_version};
}
/**
 * Destory the SDL context
 */
void end_sdl(struct SDL_Window *window){
    SDL_DestroyWindow(window);
    SDL_Quit();
}
/**
 * Loop begin
 */
void begin_loop(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport();
}
/**
 * Loop end
 * Clear color and swap the chain and stuff
 */
void end_loop(struct SDL_Window* window, struct ImGuiIO &io){
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    }

    SDL_GL_SwapWindow(window);
}

