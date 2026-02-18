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

bool wid_actionbar_init(Gamep g);
bool wid_leftbar_init(Gamep g);
bool wid_rightbar_init(Gamep g);
void wid_actionbar_fini(Gamep g);
void wid_cfg_gfx_select(Gamep g);
void wid_cfg_help_select(Gamep g);
void wid_cfg_mouse_select(Gamep g);
void wid_options_menu_select(Gamep);
void wid_cfg_sound_select(Gamep g);
void wid_credits_select(Gamep g);
void wid_dead_fini(Gamep g);
void wid_dead_select(Gamep g, std::string reason);
void wid_hiscores_show(Gamep g);
void wid_inventory_show(Gamep g, Levelsp v, Levelp l, Thingp /*player*/);
void wid_leftbar_fini(Gamep g);
void wid_load_destroy(Gamep);
void wid_load_select(Gamep);
void wid_main_menu_destroy(Gamep g);
void wid_main_menu_select(Gamep g);
void wid_more_select(Gamep g);
void wid_item_menu_select(Gamep, Levelsp, Thingp it);
void wid_new_game(Gamep g);
void wid_player_name_select(Gamep g);
void wid_quit_destroy(Gamep g);
void wid_quit_select(Gamep g);
void wid_rightbar_fini(Gamep g);
void wid_save_destroy(Gamep);
void wid_save_select(Gamep);
void wid_seed_select(Gamep g);
void wid_gray_out_button(Gamep g, Widp w);
Widp wid_new_back_button(Gamep g, Widp parent, std::string name);
Widp wid_new_menu_button(Gamep g, Widp parent, std::string name);
Widp wid_new_save_button(Gamep g, Widp parent, std::string name);
Widp wid_new_cancel_button(Gamep g, Widp parent, std::string name);
Widp wid_new_green_button(Gamep g, Widp parent, std::string name);
Widp wid_new_red_button(Gamep g, Widp parent, std::string name);
Widp wid_new_button(Gamep g, Widp parent, std::string name);

#endif
