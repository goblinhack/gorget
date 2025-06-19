//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GAME_HPP_
#define _MY_GAME_HPP_

#include "my_minimal.hpp"

#include <SDL.h>

typedef enum {
  STATE_MAIN_MENU,     // Main menu
  STATE_PLAYING,       // Actively playing in a level
  STATE_QUITTING,      // Shutting down
  STATE_KEYBOARD_MENU, // Setting keys
  STATE_LOAD_MENU,     // Loading a game
  STATE_LOADED,        // Loaded an old game
  STATE_SAVE_MENU,     // Saving a game
  STATE_QUIT_MENU,     // Pondering quitting
} GameState;

#define MAX_SEED_NAME_LEN 32

typedef enum {
  SEED_SOURCE_RANDOM,
  SEED_SOURCE_USER,
  SEED_SOURCE_COMMAND_LINE,
} SeedSource;

class HiScores *game_hiscores_get(Gamep);

void game_visible_map_pix_get(Gamep, int *visible_map_tl_x, int *visible_map_tl_y, int *visible_map_br_x,
                              int *visible_map_br_y);
void game_visible_map_pix_set(Gamep, int visible_map_tl_x, int visible_map_tl_y, int visible_map_br_x,
                              int visible_map_br_y);

int  game_tiles_visible_across_get(Gamep);
void game_tiles_visible_across_set(Gamep, int val);

int  game_tiles_visible_down_get(Gamep);
void game_tiles_visible_down_set(Gamep, int val);

int  game_last_mouse_down_get(Gamep);
void game_last_mouse_down_set(Gamep, int);

float game_aspect_ratio_get(Gamep);
void  game_aspect_ratio_set(Gamep, float);

int  game_ui_term_height_get(Gamep);
void game_ui_term_height_set(Gamep, int);

int  game_ui_term_width_get(Gamep);
void game_ui_term_width_set(Gamep, int);

bool game_debug_mode_get(Gamep);
void game_debug_mode_set(Gamep, bool);

bool game_fps_counter_get(Gamep);
void game_fps_counter_set(Gamep, bool);

int  game_fps_value_get(Gamep);
void game_fps_value_set(Gamep, int);

bool game_gfx_allow_highdpi_get(Gamep);
void game_gfx_allow_highdpi_set(Gamep, bool);

bool game_gfx_borderless_get(Gamep);
void game_gfx_borderless_set(Gamep, bool);

bool game_gfx_fullscreen_get(Gamep);
void game_gfx_fullscreen_set(Gamep, bool);

bool game_gfx_fullscreen_desktop_get(Gamep);
void game_gfx_fullscreen_desktop_set(Gamep, bool);

bool game_gfx_vsync_enable_get(Gamep);
void game_gfx_vsync_enable_set(Gamep, bool);

bool game_mouse_wheel_lr_negated_get(Gamep);
void game_mouse_wheel_lr_negated_set(Gamep, bool);

bool game_mouse_wheel_ud_negated_get(Gamep);
void game_mouse_wheel_ud_negated_set(Gamep, bool);

int  game_config_pix_height_get(Gamep);
void game_config_pix_height_set(Gamep, int);

int  game_config_pix_width_get(Gamep);
void game_config_pix_width_set(Gamep, int);

int  game_map_fbo_height_get(Gamep);
void game_map_fbo_height_set(Gamep, int);

int  game_map_fbo_width_get(Gamep);
void game_map_fbo_width_set(Gamep, int);

int  game_window_pix_height_get(Gamep);
void game_window_pix_height_set(Gamep, int);

int  game_window_pix_width_get(Gamep);
void game_window_pix_width_set(Gamep, int);

int  game_ascii_pix_height_get(Gamep);
void game_ascii_pix_height_set(Gamep, int);

int  game_ascii_pix_width_get(Gamep);
void game_ascii_pix_width_set(Gamep, int);

int  game_music_volume_get(Gamep);
void game_music_volume_set(Gamep, int);

int  game_sdl_delay_get(Gamep);
void game_sdl_delay_set(Gamep, int);

int  game_sound_volume_get(Gamep);
void game_sound_volume_set(Gamep, int);

Levelsp game_levels_get(Gamep);
Levelsp game_levels_set(Gamep, Levelsp);

Levelp game_level_get(Gamep g, Levelsp);
Levelp game_level_get(Gamep g, Levelsp, LevelNum level_num);
Levelp game_level_populate(Gamep g, Levelsp, LevelNum level_num);

const char *game_seed_name_get(Gamep);
SeedSource  game_seed_source_get(Gamep);
uint32_t    game_seed_num_get(Gamep);
void        game_seed_set(Gamep, const char *);
void        game_seed_set(Gamep, uint32_t);

SDL_Keysym game_key_wait_get(Gamep);
void       game_key_wait_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_console_get(Gamep);
void       game_key_console_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_help_get(Gamep);
void       game_key_help_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_load_get(Gamep);
void       game_key_load_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_move_down_get(Gamep);
void       game_key_move_down_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_move_left_get(Gamep);
void       game_key_move_left_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_move_right_get(Gamep);
void       game_key_move_right_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_move_up_get(Gamep);
void       game_key_move_up_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_quit_get(Gamep);
void       game_key_quit_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_save_get(Gamep);
void       game_key_save_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_screenshot_get(Gamep);
void       game_key_screenshot_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_unused1_get(Gamep);
void       game_key_unused1_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_unused2_get(Gamep);
void       game_key_unused2_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_unused3_get(Gamep);
void       game_key_unused3_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_unused4_get(Gamep);
void       game_key_unused4_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_unused5_get(Gamep);
void       game_key_unused5_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_unused6_get(Gamep);
void       game_key_unused6_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_unused7_get(Gamep);
void       game_key_unused7_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_unused8_get(Gamep);
void       game_key_unused8_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_unused9_get(Gamep);
void       game_key_unused9_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_unused10_get(Gamep);
void       game_key_unused10_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_unused11_get(Gamep);
void       game_key_unused11_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_unused12_get(Gamep);
void       game_key_unused12_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_unused13_get(Gamep);
void       game_key_unused13_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_unused14_get(Gamep);
void       game_key_unused14_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_unused15_get(Gamep);
void       game_key_unused15_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_unused16_get(Gamep);
void       game_key_unused16_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_unused17_get(Gamep);
void       game_key_unused17_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_ascend_get(Gamep);
void       game_key_ascend_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_descend_get(Gamep);
void       game_key_descend_set(Gamep, SDL_Keysym);

SDL_Keysym game_key_zoom_get(Gamep);
void       game_key_zoom_set(Gamep, SDL_Keysym);

bool game_request_to_remake_ui_get(Gamep);
void game_request_to_remake_ui_set(Gamep, bool = true);

bool game_request_to_save_game_get(Gamep);
void game_request_to_save_game_set(Gamep, bool = true);

bool     game_event_ascend(Gamep);
bool     game_event_descend(Gamep);
bool     game_event_help(Gamep);
bool     game_event_load(Gamep);
bool     game_event_quit(Gamep);
bool     game_event_save(Gamep);
bool     game_event_wait(Gamep);
int      game_map_single_pix_size_get(Gamep g);
int      game_map_zoom_def_get(Gamep g);
int      game_map_zoom_get(Gamep g);
Levelsp  game_test_init(Gamep, Levelp *, LevelNum, int w, int h, const char *contents);
uint8_t  game_input(Gamep, const SDL_Keysym *key);
uint8_t  game_mouse_down(Gamep, int x, int y, uint32_t button);
uint8_t  game_mouse_motion(Gamep, int x, int y, int relx, int rely, int wheelx, int wheely);
uint8_t  game_mouse_up(Gamep, int x, int y, uint32_t button);
uint8_t  game_state(Gamep);
void     game_config_reset(Gamep);
void     game_create_levels(Gamep);
void     game_destroy_levels(Gamep);
void     game_display(Gamep);
void     game_fini(Gamep);
void     game_init(Gamep);
void     game_load_config(Gamep game);
void     game_load_last_config(const char *appdata);
void     game_load_snapshot(Gamep);
void     game_load(Gamep, int slot);
void     game_load(Gamep);
void     game_map_single_pix_size_set(Gamep g, int val);
void     game_map_zoom_in(Gamep);
void     game_map_zoom_out(Gamep);
void     game_map_zoom_set(Gamep g, int val);
void     game_map_zoom_toggle(Gamep);
void     game_save_config(Gamep);
void     game_save_snapshot_check(Gamep);
void     game_save_snapshot(Gamep);
void     game_save(Gamep, int slot);
void     game_save(Gamep);
void     game_set_currently_saving_snapshot(Gamep);
void     game_start_playing(Gamep);
void     game_state_change(Gamep, GameState state, const char *);
void     game_state_reset(Gamep, const char *);
void     game_wait_for_tick_to_finish(Gamep, Levelsp, Levelp);
void     game_tick(Gamep);
uint32_t game_tick_get(Gamep, Levelsp);
void     game_unset_currently_saving_snapshot(Gamep);
void     game_unset_request_reset_state_change(Gamep);
void     game_unset_request_to_save_snapshot(Gamep);
void     game_unset_request_to_update_same_level(Gamep);

#endif
