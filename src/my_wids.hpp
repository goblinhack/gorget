//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_WIDS_HPP_
#define _MY_WIDS_HPP_

#include "my_color_defs.hpp"
#include "my_thing.hpp"
#include "my_wid.hpp"
#include "my_wid_popup.hpp"

#include <string>

bool wid_actionbar_init(Gamep);
bool wid_leftbar_init(Gamep);
bool wid_rightbar_init(Gamep);
void wid_actionbar_fini(Gamep);
void wid_cfg_gfx_select(Gamep);
void wid_cfg_keyboard_select(Gamep);
void wid_cfg_mouse_select(Gamep);
void wid_options_menu_select(Gamep);
void wid_cfg_sound_select(Gamep);
void wid_credits_select(Gamep);
void wid_dead_fini(Gamep);
void wid_dead_select(Gamep, std::string reason);
void wid_hiscores_show(Gamep);
void wid_inventory_show(Gamep, Levelsp, Levelp, Thingp);
void wid_leftbar_fini(Gamep);
void wid_load_destroy(Gamep);
void wid_load_select(Gamep);
void wid_main_menu_destroy(Gamep);
void wid_main_menu_select(Gamep);
void wid_more_select(Gamep);
void wid_item_menu_select(Gamep, Levelsp, Thingp it);
void wid_new_game(Gamep);
void wid_player_name_select(Gamep);
void wid_quit_destroy(Gamep);
void wid_quit_select(Gamep);
void wid_rightbar_fini(Gamep);
void wid_save_destroy(Gamep);
void wid_save_select(Gamep);
void wid_seed_select(Gamep);
Widp wid_back_button(Gamep, Widp parent, const std::string name);
Widp wid_menu_button(Gamep, Widp parent, const std::string name);
Widp wid_save_button(Gamep, Widp parent, const std::string name);
Widp wid_cancel_button(Gamep, Widp parent, const std::string name);
Widp wid_green_button(Gamep, Widp parent, const std::string name);
Widp wid_red_button(Gamep, Widp parent, const std::string name);
Widp wid_solid_button(Gamep, Widp parent, const std::string name);

#endif
