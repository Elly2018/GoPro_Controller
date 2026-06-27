/*
 * Copyright (c) [2026] [Elly/Funique]
 *
 * This software is licensed under the [MIT License].
 * See the LICENSE file in the project root for more information.
*/
#pragma once
#include <utility>

struct SDL_Window;
struct ImGuiIO;

#ifdef __cplusplus
extern "C" {
#endif

void setup_imgui();
void setup_catppuccin_mocha_theme();
void begin_imgui(struct SDL_Window *window, void *sdl_gl_context, const char *glsl_version);
void end_imgui();
void begin_sdl(std::tuple<struct SDL_Window*, const char*>& r);
void end_sdl(struct SDL_Window *window);
void begin_loop();
void end_loop(struct SDL_Window* window, struct ImGuiIO &io);

#ifdef __cplusplus
}
#endif

