//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_WIDS_HPP_
#define _MY_WIDS_HPP_

#include "my_wid.hpp"
#include "my_wid_popup.hpp"

extern void wid_load_destroy(class Game *);
extern void wid_save_destroy(class Game *);
extern void wid_quit_destroy(class Game *);
extern void wid_cfg_gfx_select(class Game *);
extern void wid_cfg_keyboard_select(class Game *);
extern void wid_cfg_mouse_select(class Game *);
extern void wid_cfg_sound_select(class Game *);
extern void wid_cfg_top_menu(class Game *);
extern void wid_credits_select(class Game *);
extern void wid_hiscores_show(class Game *);
extern void wid_load_select(class Game *);
extern void wid_main_menu_select(class Game *);
extern void wid_quit_select(class Game *);
extern void wid_main_menu_destroy(class Game *);
extern void wid_save_select(class Game *);
extern void wid_new_game(class Game *);
extern void wid_rightbar_fini(class Game *);
extern bool wid_rightbar_init(class Game *);
extern void wid_leftbar_fini(class Game *);
extern bool wid_leftbar_init(class Game *);

#endif
