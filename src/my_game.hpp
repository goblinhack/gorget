//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GAME_HPP_
#define _MY_GAME_HPP_

#include <SDL.h>

#include "my_game_defs.hpp"
#include "my_hiscore.hpp"
#include "my_minimal.hpp"

using Config = class Config_
{
public:
  std::string version = "" MYVER "";

  uint32_t serialized_size = {};
  //
  // Keep flags int size so the header size will change on a new flag.
  // It does not always for new bools.
  //
  int16_t game_pix_scale_height = {};
  int16_t game_pix_scale_width  = {};
  float   aspect_ratio          = {};

  uint32_t ui_gfx_term_height = {};
  uint32_t ui_gfx_term_width  = {};

  bool debug_mode             = {};
  bool fps_counter            = {};
  bool gfx_allow_highdpi      = {};
  bool gfx_borderless         = {};
  bool gfx_fullscreen         = {};
  bool gfx_fullscreen_desktop = {};
  bool gfx_vsync_enable       = {};

  bool mouse_wheel_lr_negated = {};
  bool mouse_wheel_ud_negated = {};

  int16_t config_pix_height = {};
  int16_t config_pix_width  = {};
  //
  // The pixel perfect screen
  //
  int16_t game_pix_height = {};
  int16_t game_pix_width  = {};
  //
  // This is the size of the game map within the game FBO
  //
  int16_t map_pix_height = {};
  int16_t map_pix_width  = {};
  //
  // The user interface that can be higher res than the game
  //
  int16_t ui_pix_height = {};
  int16_t ui_pix_width  = {};
  //
  // The actual display res
  //
  int16_t window_pix_height = {};
  int16_t window_pix_width  = {};

  uint16_t ascii_gl_height = {};
  uint16_t ascii_gl_width  = {};
  uint32_t music_volume    = {};
  uint32_t sdl_delay       = {};
  uint32_t sound_volume    = {};

  // begin sort marker1 {
  SDL_Keysym key_action0    = {};
  SDL_Keysym key_action1    = {};
  SDL_Keysym key_action2    = {};
  SDL_Keysym key_action3    = {};
  SDL_Keysym key_action4    = {};
  SDL_Keysym key_action5    = {};
  SDL_Keysym key_action6    = {};
  SDL_Keysym key_action7    = {};
  SDL_Keysym key_action8    = {};
  SDL_Keysym key_action9    = {};
  SDL_Keysym key_attack     = {};
  SDL_Keysym key_console    = {};
  SDL_Keysym key_help       = {};
  SDL_Keysym key_load       = {};
  SDL_Keysym key_move_down  = {};
  SDL_Keysym key_move_left  = {};
  SDL_Keysym key_move_right = {};
  SDL_Keysym key_move_up    = {};
  SDL_Keysym key_quit       = {};
  SDL_Keysym key_save       = {};
  SDL_Keysym key_screenshot = {};
  SDL_Keysym key_unused1    = {};
  SDL_Keysym key_unused10   = {};
  SDL_Keysym key_unused11   = {};
  SDL_Keysym key_unused12   = {};
  SDL_Keysym key_unused13   = {};
  SDL_Keysym key_unused14   = {};
  SDL_Keysym key_unused15   = {};
  SDL_Keysym key_unused16   = {};
  SDL_Keysym key_unused17   = {};
  SDL_Keysym key_unused18   = {};
  SDL_Keysym key_unused19   = {};
  SDL_Keysym key_unused2    = {};
  SDL_Keysym key_unused20   = {};
  SDL_Keysym key_unused3    = {};
  SDL_Keysym key_unused4    = {};
  SDL_Keysym key_unused5    = {};
  SDL_Keysym key_unused6    = {};
  SDL_Keysym key_unused7    = {};
  SDL_Keysym key_unused8    = {};
  SDL_Keysym key_unused9    = {};
  // end sort marker1 }

  //
  // Ok, not really config...
  //
  HiScores hiscores;

  void fini(void);
  void reset(void);
};

class Game
{
public:
  //
  // Save file name, contains the date and other useful save slot info
  //
  std::string version = "" MYVER "";

  //
  // Current level
  //
  Levelp level {};

  //
  // Used to check for changes in the size of this struct.
  //
  uint32_t serialized_size {};

  //
  // If this was a saved game, which slot does it use.
  //
  uint8_t save_slot {};

  //
  // Title and seed name.
  //
  std::string save_meta;

  //
  // Saved file for this game.
  //
  std::string save_file;

  //
  // Appdata dir for saving logs.
  //
  std::string appdata;

  //
  // Save dir for saving games.
  //
  std::string saved_dir;

  //
  // User configuration.
  //
  Config config;

  //
  // All randomness jumps off of this.
  //
  uint32_t seed {};

  //
  // Human readable version of the above seed.
  //
  std::string seed_name {};

  //
  // Seed has been manually set, so stick with it
  //
  bool seed_manually_set {};

  //
  // Current fram-erate
  //
  uint32_t fps_value = {};

  /////////////////////////////////////////////////////////////////////////
  // not worth saving
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////

  //
  // Game is ending and levels are being destroyed.
  //
  bool is_being_destroyed {};

  //
  // Temporary. Global states
  //
  enum {
    STATE_MAIN_MENU,
    STATE_PLAYING,
    STATE_KEYBOARD_MENU, // Setting keys
    STATE_LOAD_MENU,     // Loading a game
    STATE_SAVE_MENU,     // Saving a game
    STATE_QUIT_MENU,     // Pondering quitting
  };
  uint8_t state {STATE_MAIN_MENU};

  //
  // Temporary. Dampens mouse clicks
  //
  uint32_t last_mouse_down {};
  uint32_t last_pause {};

  /////////////////////////////////////////////////////////////////////////
  // not worth saving
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  /////////////////////////////////////////////////////////////////////////

  Game(std::string appdata);
  Game(void) = default;

  std::string load_config(void);

  bool load(std::string save_file, class Game &target);
  bool save(std::string save_file);

  // begin sort marker2 {
  void create_level(void);
  void display(void);
  void fini(void);
  void init(void);
  void load_snapshot(void);
  void load(uint8_t slot);
  void load(void);
  void new_game(void);
  void save_config(void);
  void save_snapshot_check();
  void save_snapshot(void);
  void save(uint8_t slot);
  void save(void);
  void set_currently_saving_snapshot(void);
  void set_seed(void);
  void start(void);
  void state_change(uint8_t state, const std::string &);
  void state_reset(const std::string &);
  void unset_currently_saving_snapshot(void);
  void unset_request_reset_state_change(void);
  void unset_request_to_save_snapshot(void);
  void unset_request_to_update_same_level(void);
  void wid_cfg_gfx_select(void);
  void wid_cfg_keyboard_select(void);
  void wid_cfg_mouse_select(void);
  void wid_cfg_sound_select(void);
  void wid_cfg_top_menu(void);
  void wid_credits_select(void);
  void wid_help_select(void);
  void wid_hiscores_show(void);
  void wid_load_select(void);
  void wid_main_menu_select(void);
  void wid_quit_select(void);
  void wid_save_select(void);
  // end sort marker2 }
};

extern uint8_t game_mouse_down(int x, int y, uint32_t button);
extern uint8_t game_mouse_up(int x, int y, uint32_t button);
extern uint8_t game_mouse_motion(int x, int y, int relx, int rely, int wheelx, int wheely);
extern uint8_t game_input(const SDL_Keysym *key);

extern void wid_main_menu_hide(void);
extern void wid_main_menu_destroy(void);

extern std::string gama_state_to_string(int state);

extern class Game *game;

#endif
