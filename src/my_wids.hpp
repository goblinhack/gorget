//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_WIDS_HPP_
#define _MY_WIDS_HPP_

#include "my_wid.hpp"
#include "my_wid_popup.hpp"

#include <string>

extern void wid_load_destroy(Gamep);
extern void wid_save_destroy(Gamep);
extern void wid_quit_destroy(Gamep);
extern void wid_cfg_gfx_select(Gamep);
extern void wid_seed_select(Gamep);
extern void wid_cfg_keyboard_select(Gamep);
extern void wid_cfg_mouse_select(Gamep);
extern void wid_cfg_sound_select(Gamep);
extern void wid_cfg_top_menu(Gamep);
extern void wid_credits_select(Gamep);
extern void wid_hiscores_show(Gamep);
extern void wid_load_select(Gamep);
extern void wid_main_menu_select(Gamep);
extern void wid_quit_select(Gamep);
extern void wid_main_menu_destroy(Gamep);
extern void wid_save_select(Gamep);
extern void wid_new_game(Gamep);
extern void wid_rightbar_fini(Gamep);
extern bool wid_rightbar_init(Gamep);
extern void wid_actionbar_fini(Gamep);
extern bool wid_actionbar_init(Gamep);
extern void wid_leftbar_fini(Gamep);
extern bool wid_leftbar_init(Gamep);
extern void wid_dead_select(Gamep, std::string reason);

#endif
