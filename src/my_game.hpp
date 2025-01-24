//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GAME_HPP_
#define _MY_GAME_HPP_

#include "my_minimal.hpp"

#include <SDL.h>

enum {
  STATE_MAIN_MENU,
  STATE_PLAYING,
  STATE_QUITTING,
  STATE_KEYBOARD_MENU, // Setting keys
  STATE_LOAD_MENU,     // Loading a game
  STATE_SAVE_MENU,     // Saving a game
  STATE_QUIT_MENU,     // Pondering quitting
};

extern class Game *game;

class HiScores *game_hiscores_get(class Game *);

void game_visible_map_pix_get(class Game *, int *visible_map_tl_x, int *visible_map_tl_y, int *visible_map_br_x,
                              int *visible_map_br_y);
void game_visible_map_pix_set(class Game *, int visible_map_tl_x, int visible_map_tl_y, int visible_map_br_x,
                              int visible_map_br_y);

void game_visible_map_mouse_get(class Game *game, int *visible_map_mouse_x, int *visible_map_mouse_y);
void game_visible_map_mouse_set(class Game *game, int visible_map_mouse_x, int visible_map_mouse_y);

int  game_tiles_visible_across_get(class Game *);
void game_tiles_visible_across_set(class Game *, int val);

int  game_tiles_visible_down_get(class Game *);
void game_tiles_visible_down_set(class Game *, int val);

int  game_last_mouse_down_get(class Game *);
void game_last_mouse_down_set(class Game *, int);

int  game_last_pause_get(class Game *);
void game_last_pause_set(class Game *, int);

int  game_serialized_size_get(class Game *);
void game_serialized_size_set(class Game *, int);

float game_aspect_ratio_get(class Game *);
void  game_aspect_ratio_set(class Game *, float);

int  game_ui_term_height_get(class Game *);
void game_ui_term_height_set(class Game *, int);

int  game_ui_term_width_get(class Game *);
void game_ui_term_width_set(class Game *, int);

bool game_debug_mode_get(class Game *);
void game_debug_mode_set(class Game *, bool);

bool game_fps_counter_get(class Game *);
void game_fps_counter_set(class Game *, bool);

int  game_fps_value_get(class Game *);
void game_fps_value_set(class Game *, int);

bool game_gfx_allow_highdpi_get(class Game *);
void game_gfx_allow_highdpi_set(class Game *, bool);

bool game_gfx_borderless_get(class Game *);
void game_gfx_borderless_set(class Game *, bool);

bool game_gfx_fullscreen_get(class Game *);
void game_gfx_fullscreen_set(class Game *, bool);

bool game_gfx_fullscreen_desktop_get(class Game *);
void game_gfx_fullscreen_desktop_set(class Game *, bool);

bool game_gfx_vsync_enable_get(class Game *);
void game_gfx_vsync_enable_set(class Game *, bool);

bool game_mouse_wheel_lr_negated_get(class Game *);
void game_mouse_wheel_lr_negated_set(class Game *, bool);

bool game_mouse_wheel_ud_negated_get(class Game *);
void game_mouse_wheel_ud_negated_set(class Game *, bool);

int  game_config_pix_height_get(class Game *);
void game_config_pix_height_set(class Game *, int);

int  game_config_pix_width_get(class Game *);
void game_config_pix_width_set(class Game *, int);

int  game_pix_height_get(class Game *);
void game_pix_height_set(class Game *, int);

int  game_pix_width_get(class Game *);
void game_pix_width_set(class Game *, int);

int  game_map_pix_height_get(class Game *);
void game_map_pix_height_set(class Game *, int);

int  game_map_pix_width_get(class Game *);
void game_map_pix_width_set(class Game *, int);

int  game_window_pix_height_get(class Game *);
void game_window_pix_height_set(class Game *, int);

int  game_window_pix_width_get(class Game *);
void game_window_pix_width_set(class Game *, int);

int  game_ascii_pix_height_get(class Game *);
void game_ascii_pix_height_set(class Game *, int);

int  game_ascii_pix_width_get(class Game *);
void game_ascii_pix_width_set(class Game *, int);

int  game_music_volume_get(class Game *);
void game_music_volume_set(class Game *, int);

int  game_sdl_delay_get(class Game *);
void game_sdl_delay_set(class Game *, int);

int  game_sound_volume_get(class Game *);
void game_sound_volume_set(class Game *, int);

Levelp game_level_get(class Game *);
void   game_level_set(class Game *, Levelp);

const char *game_seed_name_get(class Game *);
void        game_seed_name_set(class Game *, const char *);

SDL_Keysym game_key_attack_get(class Game *);
void       game_key_attack_set(class Game *, SDL_Keysym);

SDL_Keysym game_key_console_get(class Game *);
void       game_key_console_set(class Game *, SDL_Keysym);

SDL_Keysym game_key_help_get(class Game *);
void       game_key_help_set(class Game *, SDL_Keysym);

SDL_Keysym game_key_load_get(class Game *);
void       game_key_load_set(class Game *, SDL_Keysym);

SDL_Keysym game_key_move_down_get(class Game *);
void       game_key_move_down_set(class Game *, SDL_Keysym);

SDL_Keysym game_key_move_left_get(class Game *);
void       game_key_move_left_set(class Game *, SDL_Keysym);

SDL_Keysym game_key_move_right_get(class Game *);
void       game_key_move_right_set(class Game *, SDL_Keysym);

SDL_Keysym game_key_move_up_get(class Game *);
void       game_key_move_up_set(class Game *, SDL_Keysym);

SDL_Keysym game_key_quit_get(class Game *);
void       game_key_quit_set(class Game *, SDL_Keysym);

SDL_Keysym game_key_save_get(class Game *);
void       game_key_save_set(class Game *, SDL_Keysym);

SDL_Keysym game_key_screenshot_get(class Game *);
void       game_key_screenshot_set(class Game *, SDL_Keysym);

SDL_Keysym game_key_unused1_get(class Game *);
void       game_key_unused1_set(class Game *, SDL_Keysym);

uint8_t game_input(class Game *, const SDL_Keysym *key);
uint8_t game_mouse_down(class Game *, int x, int y, uint32_t button);
uint8_t game_mouse_motion(class Game *, int x, int y, int relx, int rely, int wheelx, int wheely);
uint8_t game_mouse_up(class Game *, int x, int y, uint32_t button);

void game_config_reset(class Game *);
void game_create_level(class Game *);
void game_entered_level(class Game *);
void game_destroy_level(class Game *);
void game_display(class Game *);
void game_fini(class Game *);
void game_init(class Game *);
void game_load(class Game *);
void game_load(class Game *, int slot);
void game_load_config(class Game *game);
void game_load_last_config(const char *appdata);
void game_load_snapshot(class Game *);
void game_save(class Game *);
void game_save(class Game *, int slot);
void game_save_config(class Game *);
void game_save_snapshot_check(class Game *);
void game_save_snapshot(class Game *);
void game_set_currently_saving_snapshot(class Game *);
void game_set_seed(class Game *);
void game_state_change(class Game *, uint8_t state, const char *);
void game_state_reset(class Game *, const char *);
void game_unset_currently_saving_snapshot(class Game *);
void game_unset_request_reset_state_change(class Game *);
void game_unset_request_to_save_snapshot(class Game *);
void game_unset_request_to_update_same_level(class Game *);

#endif
