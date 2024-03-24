//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <SDL_mixer.h>

#include "my_ascii.hpp"
#include "my_game.hpp"

void Config::fini(void) { TRACE_AND_INDENT(); }

void Config::reset(void)
{
  TRACE_AND_INDENT();
  config_pix_height      = {};
  config_pix_width       = {};
  debug_mode             = false;
  fps_counter            = false;
  game_pix_height        = {};
  game_pix_width         = {};
  map_pix_height         = {};
  map_pix_width          = {};
  game_pix_scale_height  = {};
  game_pix_scale_width   = {};
  gfx_allow_highdpi      = false;
  gfx_borderless         = true;
  gfx_fullscreen_desktop = true;
  gfx_fullscreen         = false;
  gfx_vsync_enable       = true;
  gfx_vsync_locked       = false;
  mouse_wheel_lr_negated = false;
  mouse_wheel_ud_negated = false;
  ui_gfx_term_height     = {TERM_GFX_HEIGHT_DEF};
  ui_gfx_term_width      = {TERM_GFX_WIDTH_DEF};
  ui_pix_height          = {};
  ui_pix_width           = {};
  version                = "" MYVER "";
  aspect_ratio           = {};
  window_pix_height      = {};
  window_pix_width       = {};

  key_action0.sym    = SDLK_0;
  key_action1.sym    = SDLK_1;
  key_action2.sym    = SDLK_2;
  key_action3.sym    = SDLK_3;
  key_action4.sym    = SDLK_4;
  key_action5.sym    = SDLK_5;
  key_action6.sym    = SDLK_6;
  key_action7.sym    = SDLK_7;
  key_action8.sym    = SDLK_8;
  key_action9.sym    = SDLK_9;
  key_attack.sym     = SDLK_SPACE;
  key_help.sym       = SDLK_h;
  key_load.sym       = SDLK_F11;
  key_move_down.sym  = SDLK_s;
  key_move_left.sym  = SDLK_a;
  key_move_right.sym = SDLK_d;
  key_move_up.sym    = SDLK_w;
  key_quit.sym       = SDLK_q;
  key_quit.mod       = KMOD_SHIFT;
  key_save.sym       = SDLK_F12;
  key_screenshot.sym = SDLK_F10;
  key_console.sym    = SDLK_TAB;
  key_console.mod    = KMOD_SHIFT;
  music_volume       = {MIX_MAX_VOLUME / 3};
  sdl_delay          = 1;
  sound_volume       = {MIX_MAX_VOLUME / 2};

  // key_unused1.sym  = SDLK_TAB;
  // key_unused1.mod  = KMOD_NUM;
  // key_unused2.sym  = SDLK_TAB;
  // key_unused2.mod  = KMOD_NUM;
  // key_unused3.sym  = SDLK_TAB;
  // key_unused3.mod  = KMOD_NUM;
  // key_unused4.sym  = SDLK_TAB;
  // key_unused4.mod  = KMOD_NUM;
  // key_unused5.sym  = SDLK_TAB;
  // key_unused5.mod  = KMOD_NUM;
  // key_unused6.sym  = SDLK_TAB;
  // key_unused6.mod  = KMOD_NUM;
  // key_unused7.sym  = SDLK_TAB;
  // key_unused7.mod  = KMOD_NUM;
  // key_unused8.sym  = SDLK_TAB;
  // key_unused8.mod  = KMOD_NUM;
  // key_unused9.sym  = SDLK_TAB;
  // key_unused9.mod  = KMOD_NUM;
  // key_unused10.sym  = SDLK_TAB;
  // key_unused10.mod  = KMOD_NUM;
  // key_unused11.sym  = SDLK_TAB;
  // key_unused11.mod  = KMOD_NUM;
  // key_unused12.sym  = SDLK_TAB;
  // key_unused12.mod  = KMOD_NUM;
  // key_unused13.sym  = SDLK_TAB;
  // key_unused13.mod  = KMOD_NUM;
  // key_unused14.sym  = SDLK_TAB;
  // key_unused14.mod  = KMOD_NUM;
  // key_unused15.sym  = SDLK_TAB;
  // key_unused15.mod  = KMOD_NUM;
  // key_unused16.sym  = SDLK_TAB;
  // key_unused16.mod  = KMOD_NUM;
  // key_unused17.sym  = SDLK_TAB;
  // key_unused17.mod  = KMOD_NUM;
  // key_unused18.sym  = SDLK_TAB;
  // key_unused18.mod  = KMOD_NUM;
  // key_unused19.sym  = SDLK_TAB;
  // key_unused19.mod  = KMOD_NUM;
  // key_unused20.sym  = SDLK_TAB;
  // key_unused20.mod  = KMOD_NUM;
  //
}
