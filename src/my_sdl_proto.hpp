//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_SDL_PROTO_HPP_
#define _MY_SDL_PROTO_HPP_

#include "my_minimal.hpp"

#include <SDL.h>
#include <string>
#include <vector>

bool sdlk_eq(const SDL_Keysym &a, const SDL_Keysym &b);

int sdl_filter_events(void *userdata, SDL_Event *event);
int sdl_get_mouse(void);

SDL_Keysym   sdlk_normalize(SDL_Keysym k);
SDL_Scancode sdlk_to_scancode(const SDL_Keysym &k);

std::string to_string(const SDL_Keysym &k);
std::string to_string_ignoring_mods(const SDL_Keysym &k);

std::vector< uint8_t > sdl_fbo_save(Gamep, int fbo);

uint8_t config_errored(Gamep, class Tokens *, void *context);
uint8_t config_fps_counter_set(Gamep, class Tokens *, void *context);
uint8_t config_debug_set(Gamep, class Tokens *, void *context);
uint8_t config_gfx_vsync_enable(Gamep, class Tokens *, void *context);
uint8_t sdl_init(void);

class Tokens;
uint8_t sdl_user_exit(Gamep, class Tokens *tokens, void *context);

void    config_game_gfx_update(Gamep);
void    config_gfx_vsync_update(Gamep);
void    sdl_config_update_all(Gamep);
uint8_t sdl_display_init(Gamep);
void    sdl_display(Gamep);
void    sdl_display_reset(Gamep);
void    sdl_event(Gamep, SDL_Event *event, bool &processed_mouse_motion_event);
void    sdl_prepare_to_exit(Gamep);
void    sdl_fbo_dump(Gamep, int fbo, const std::string &name);
void    sdl_fbo_load(Gamep, int fbo, const std::vector< uint8_t > &pixels);
void    sdl_fini(Gamep);
void    sdl_video_fini(Gamep);
void    sdl_flush_display(Gamep, bool force = false);
void    sdl_joy_rumble(float strength, uint32_t ms);
void    sdl_key_repeat_events(Gamep);
void    sdl_loop(Gamep);
void    sdl_mouse_center(Gamep);
void    sdl_mouse_warp(Gamep, int x, int y);
void    sdl_screenshot_do(Gamep);
void    sdl_screenshot(Gamep);
void    sdl_tick(Gamep);

#endif
