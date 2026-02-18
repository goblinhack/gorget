//
// Copyright goblinhack@gmail.com
//

#ifndef _MY_SDL_PROTO_HPP_
#define _MY_SDL_PROTO_HPP_

#include "my_gl.hpp"
#include "my_types.hpp"

#include <SDL.h>
#include <string>
#include <vector>

bool sdlk_eq(const SDL_Keysym &a, const SDL_Keysym &b);

int sdl_filter_events(void *userdata, SDL_Event *event);
int sdl_get_mouse();

SDL_Keysym   sdlk_normalize(SDL_Keysym k);
SDL_Scancode sdlk_to_scancode(const SDL_Keysym &k);

std::string to_string(const SDL_Keysym &k);
std::string to_string_ignoring_mods(const SDL_Keysym &k);

std::vector< uint8_t > sdl_fbo_save(Gamep, FboEnum fbo);

uint8_t config_errored_clear(Gamep g, class Tokens * /*tokens*/, void *context);
uint8_t show_error(Gamep g, class Tokens * /*tokens*/, void *context);
uint8_t config_fps_counter_set(Gamep g, class Tokens * /*tokens*/, void *context);
uint8_t config_debug_set(Gamep g, class Tokens * /*tokens*/, void *context);
uint8_t config_gfx_vsync_enable(Gamep g, class Tokens * /*tokens*/, void *context);
bool    sdl_init();

class Tokens;
uint8_t sdl_user_exit(Gamep g, class Tokens *tokens, void *context);

void config_game_gfx_update(Gamep g);
void config_gfx_vsync_update(Gamep g);
void sdl_config_update_all(Gamep g);
bool sdl_display_init(Gamep g);
void sdl_display(Gamep g);
void sdl_display_reset(Gamep g);
void sdl_event(Gamep g, SDL_Event *event, bool &processed_mouse_motion_event);
void sdl_prepare_to_exit(Gamep g);
void sdl_fbo_dump(Gamep, FboEnum fbo, const std::string &name);
void sdl_fbo_load(Gamep, FboEnum fbo, const std::vector< uint8_t > &pixels);
void sdl_fini(Gamep g);
void sdl_display_fini(Gamep g);
void sdl_flush_display(Gamep g, bool force = false);
void sdl_joy_rumble(float strength, uint32_t ms);
void sdl_key_repeat_events(Gamep g);
void sdl_loop(Gamep g);
void sdl_mouse_center(Gamep g);
void sdl_mouse_warp(Gamep g, int x, int y);
void sdl_screenshot_do(Gamep);
void sdl_screenshot(Gamep);
void sdl_tick(Gamep g);

#endif
