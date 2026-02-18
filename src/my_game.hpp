//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GAME_HPP_
#define _MY_GAME_HPP_

#include "my_enum.hpp"
#include "my_spoint.hpp"
#include "my_types.hpp"

#include <SDL.h>
#include <string>

#define GAME_STATE_ENUM(list_macro)                                                                                  \
  clang_format_indent()                                    /* dummy line for clang indentation fixup */              \
      list_macro(STATE_INIT, "INIT"),                      /* newline */                                             \
      list_macro(STATE_MAIN_MENU, "MAIN-MENU"),            /* newline */                                             \
      list_macro(STATE_GENERATING, "GENERATING"),          /* newline */                                             \
      list_macro(STATE_GENERATED, "GENERATED"),            /* newline */                                             \
      list_macro(STATE_PLAYING, "PLAYING"),                /* newline */                                             \
      list_macro(STATE_MOVE_WARNING_MENU, "MOVE-WARNING"), /* newline */                                             \
      list_macro(STATE_QUITTING, "QUITTING"),              /* newline */                                             \
      list_macro(STATE_KEYBOARD_MENU, "KEYBOARD-MENU"),    /* newline */                                             \
      list_macro(STATE_LOAD_MENU, "LOAD-MENU"),            /* newline */                                             \
      list_macro(STATE_LOADED, "LOADED"),                  /* newline */                                             \
      list_macro(STATE_INVENTORY_MENU, "INVENTORY"),       /* newline */                                             \
      list_macro(STATE_ITEM_MENU, "ITEM-MENU"),            /* newline */                                             \
      list_macro(STATE_DEAD_MENU, "DEAD-MENU"),            /* newline */                                             \
      list_macro(STATE_SAVE_MENU, "SAVE-MENU"),            /* newline */                                             \
      list_macro(STATE_QUIT_MENU, "QUIT-MENU"),            /* newline */

ENUM_DEF_H(GAME_STATE_ENUM, GameState)

typedef enum {
  SEED_SOURCE_RANDOM,
  SEED_SOURCE_USER,
  SEED_SOURCE_TEST,
  SEED_SOURCE_COMMAND_LINE,
} SeedSource;

#define CONFIG_MAGIC_1 0xaabbccdd
#define CONFIG_MAGIC_2 0xddccbbaa
#define CONFIG_MAGIC_3 0x11223344
#define CONFIG_MAGIC_4 0x44332211
#define CONFIG_MAGIC_5 0xcafecafe
#define CONFIG_MAGIC_6 0xfeedface

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
void game_last_mouse_down_set(Gamep, int /*val*/);

float game_aspect_ratio_get(Gamep);
void  game_aspect_ratio_set(Gamep, float /*val*/);

int  game_ui_term_height_get(Gamep);
void game_ui_term_height_set(Gamep, int /*val*/);

int  game_ui_term_width_get(Gamep);
void game_ui_term_width_set(Gamep, int /*val*/);

bool game_debug_mode_get(Gamep);
void game_debug_mode_set(Gamep, bool /*val*/);

bool game_fps_counter_get(Gamep);
void game_fps_counter_set(Gamep);
void game_fps_counter_unset(Gamep);

int  game_fps_value_get(Gamep);
void game_fps_value_set(Gamep, int /*val*/);

bool game_gfx_borderless_get(Gamep);
void game_gfx_borderless_set(Gamep);
void game_gfx_borderless_unset(Gamep);

bool game_gfx_fullscreen_get(Gamep);
void game_gfx_fullscreen_set(Gamep);
void game_gfx_fullscreen_unset(Gamep);

bool game_gfx_fullscreen_desktop_get(Gamep);
void game_gfx_fullscreen_desktop_set(Gamep);
void game_gfx_fullscreen_desktop_unset(Gamep);

bool game_gfx_vsync_enable_get(Gamep);
void game_gfx_vsync_enable_set(Gamep);
void game_gfx_vsync_enable_unset(Gamep);

bool game_mouse_wheel_lr_negated_get(Gamep);
void game_mouse_wheel_lr_negated_set(Gamep);
void game_mouse_wheel_lr_negated_unset(Gamep);

bool game_mouse_wheel_ud_negated_get(Gamep);
void game_mouse_wheel_ud_negated_set(Gamep);
void game_mouse_wheel_ud_negated_unset(Gamep);

int  game_config_pix_height_get(Gamep);
void game_config_pix_height_set(Gamep, int /*val*/);

int  game_config_pix_width_get(Gamep);
void game_config_pix_width_set(Gamep, int /*val*/);

int  game_map_fbo_height_get(Gamep);
void game_map_fbo_height_set(Gamep, int /*val*/);

int  game_map_fbo_width_get(Gamep);
void game_map_fbo_width_set(Gamep, int /*val*/);

int  game_window_pix_height_get(Gamep);
void game_window_pix_height_set(Gamep, int /*val*/);

int  game_window_pix_width_get(Gamep);
void game_window_pix_width_set(Gamep, int /*val*/);

int  game_ascii_pix_height_get(Gamep);
void game_ascii_pix_height_set(Gamep, int /*val*/);

int  game_ascii_pix_width_get(Gamep);
void game_ascii_pix_width_set(Gamep, int /*val*/);

int  game_music_volume_get(Gamep);
void game_music_volume_set(Gamep, int /*val*/);

int  game_sdl_delay_get(Gamep);
void game_sdl_delay_set(Gamep, int /*val*/);

int  game_sound_volume_get(Gamep);
void game_sound_volume_set(Gamep, int /*val*/);

Levelsp game_levels_get(Gamep);
Levelsp game_levels_set(Gamep, Levelsp /*val*/);

Levelp game_level_get(Gamep, Levelsp);
Levelp game_level_get(Gamep, Levelsp, LevelNum level_num);
Levelp game_level_populate(Gamep, Levelsp, LevelNum level_num);

const char *game_seed_name_get(Gamep);
SeedSource  game_seed_source_get(Gamep);
uint32_t    game_seed_num_get(Gamep);
void        game_seed_set(Gamep, const char        */*maybe_seed*/);
void        game_seed_clear(Gamep);
void        game_seed_set(Gamep, uint32_t /*seed*/);

const char *game_player_name_get(Gamep);
void        game_player_name_set(Gamep, const char *player_name = nullptr);

SDL_Keysym game_key_wait_get(Gamep);
void       game_key_wait_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_console_get(Gamep);
void       game_key_console_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_help_get(Gamep);
void       game_key_help_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_load_get(Gamep);
void       game_key_load_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_move_down_get(Gamep);
void       game_key_move_down_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_move_left_get(Gamep);
void       game_key_move_left_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_move_right_get(Gamep);
void       game_key_move_right_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_move_up_get(Gamep);
void       game_key_move_up_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_quit_get(Gamep);
void       game_key_quit_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_save_get(Gamep);
void       game_key_save_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_screenshot_get(Gamep);
void       game_key_screenshot_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_unused1_get(Gamep);
void       game_key_unused1_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_unused2_get(Gamep);
void       game_key_unused2_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_unused3_get(Gamep);
void       game_key_unused3_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_unused4_get(Gamep);
void       game_key_unused4_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_unused5_get(Gamep);
void       game_key_unused5_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_unused6_get(Gamep);
void       game_key_unused6_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_unused7_get(Gamep);
void       game_key_unused7_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_unused8_get(Gamep);
void       game_key_unused8_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_unused9_get(Gamep);
void       game_key_unused9_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_unused10_get(Gamep);
void       game_key_unused10_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_unused11_get(Gamep);
void       game_key_unused11_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_unused12_get(Gamep);
void       game_key_unused12_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_unused13_get(Gamep);
void       game_key_unused13_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_unused14_get(Gamep);
void       game_key_unused14_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_fire_get(Gamep);
void       game_key_fire_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_inventory_get(Gamep);
void       game_key_inventory_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_jump_get(Gamep);
void       game_key_jump_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_ascend_get(Gamep);
void       game_key_ascend_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_descend_get(Gamep);
void       game_key_descend_set(Gamep, SDL_Keysym /*key*/);

SDL_Keysym game_key_zoom_get(Gamep);
void       game_key_zoom_set(Gamep, SDL_Keysym /*key*/);

bool game_request_to_remake_ui_get(Gamep);
void game_request_to_remake_ui_set(Gamep);
void game_request_to_remake_ui_unset(Gamep);

bool game_request_to_save_game_get(Gamep);
void game_request_to_save_game_set(Gamep);
void game_request_to_save_game_unset(Gamep);

bool game_request_to_update_cursor_get(Gamep);
void game_request_to_update_cursor_set(Gamep);
void game_request_to_update_cursor_unset(Gamep);

bool game_request_to_end_game_get(Gamep);
void game_request_to_end_game_set(Gamep);
void game_request_to_end_game_unset(Gamep);

std::string game_request_to_end_game_reason_get(Gamep);
void        game_request_to_end_game_reason_set(Gamep, const std::string        &/*val*/);

bool game_event_ascend(Gamep);
bool game_event_descend(Gamep);
bool game_event_help(Gamep);
bool game_event_load(Gamep);
bool game_event_quit(Gamep);
bool game_event_save(Gamep);
bool game_event_wait(Gamep);
bool game_event_inventory(Gamep);
bool game_load_config(Gamep game);
bool game_load_last_config(const char *appdata);
bool game_load_snapshot(Gamep);
bool game_load(Gamep, const std::string &name);
bool game_map_zoom_is_full_map_visible(Gamep);
bool game_save(Gamep, const std::string & /*file_to_save*/);

int game_map_single_pix_size_get(Gamep);
int game_map_zoom_def_get(Gamep);
int game_map_zoom_get(Gamep);

uint32_t game_tick_get(Gamep, Levelsp);

bool      game_input(Gamep, const SDL_Keysym *key);
bool      game_mouse_down(Gamep, int x, int y, uint32_t button);
bool      game_mouse_motion(Gamep, int x, int y, int relx, int rely, int wheelx, int wheely);
bool      game_mouse_up(Gamep, int x, int y, uint32_t button);
GameState game_state(Gamep);

void game_cleanup(Gamep);
void game_config_reset(Gamep);
void game_create_levels(Gamep);
void game_destroy_levels(Gamep);
void game_display(Gamep);
void game_fini(Gamep);
void game_init(Gamep);
void game_map_single_pix_size_set(Gamep, int val);
void game_map_zoom_in(Gamep);
void game_map_zoom_out(Gamep);
void game_map_zoom_set(Gamep, int val);
void game_map_zoom_toggle(Gamep);
void game_save_config(Gamep);
void game_set_currently_saving_snapshot(Gamep);
void game_start_playing(Gamep);
void game_state_change(Gamep, GameState state, const char * /*why*/);
void game_state_reset(Gamep, const char * /*why*/);
void game_tick(Gamep);
void game_unset_currently_saving_snapshot(Gamep);
void game_unset_request_reset_state_change(Gamep);
void game_unset_request_to_save_snapshot(Gamep);
void game_unset_request_to_update_same_level(Gamep);
bool game_wait_for_tick_to_finish(Gamep, Levelsp, Levelp);

void        game_add_new_hiscore(Gamep, int score, LevelNum /*level_num*/, const char *name, const char *reason);
bool        game_is_new_hiscore(Gamep, int score);
bool        game_is_new_highest_hiscore(Gamep, int score);
const char *game_place_str(Gamep, int score);

#endif
