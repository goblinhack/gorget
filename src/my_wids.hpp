//
// Copyright goblinhack@gmail.com
//

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
void wid_options_menu_select(Gamep g);
void wid_cfg_sound_select(Gamep g);
void wid_credits_select(Gamep g);
void wid_dead_fini(Gamep g);
void wid_dead_select(Gamep g, const std::string &reason);
void wid_hiscores_show(Gamep g);
void wid_inventory_show(Gamep g, Levelsp v, Levelp l, Thingp player);
void wid_leftbar_fini(Gamep g);
void wid_load_destroy(Gamep g);
void wid_load_select(Gamep g);
void wid_main_menu_destroy(Gamep g);
void wid_main_menu_select(Gamep g);
void wid_more_select(Gamep g);
void wid_item_menu_select(Gamep g, Levelsp v, Thingp it);
void wid_new_game(Gamep g);
void wid_player_name_select(Gamep g);
void wid_quit_destroy(Gamep g);
void wid_quit_select(Gamep g);
void wid_rightbar_fini(Gamep g);
void wid_save_destroy(Gamep g);
void wid_save_select(Gamep g);
void wid_seed_select(Gamep g);
void wid_gray_out_button(Gamep g, Widp w);
Widp wid_new_back_button(Gamep g, Widp parent, const std::string &name);
Widp wid_new_menu_button(Gamep g, Widp parent, const std::string &name);
Widp wid_new_save_button(Gamep g, Widp parent, const std::string &name);
Widp wid_new_cancel_button(Gamep g, Widp parent, const std::string &name);
Widp wid_new_green_button(Gamep g, Widp parent, const std::string &name);
Widp wid_new_red_button(Gamep g, Widp parent, const std::string &name);
Widp wid_new_button(Gamep g, Widp parent, const std::string &name);
void wid_botcon_fini(Gamep g);
bool wid_botcon_init(Gamep g);
void wid_botcon_log(const std::string &s);
void wid_botcon_flush(Gamep g);
void wid_topcon_fini(Gamep g);
bool wid_topcon_init(Gamep g);
void wid_topcon_log(const std::string &s);
void wid_topcon_flush(Gamep g);
void wid_notice(const std::string &notice);
void wid_notice_destroy();
void wid_console_fini(Gamep g);
bool wid_console_init(Gamep g);
void wid_console_log(const std::string &s);
void wid_console_raise(Gamep g);
void wid_console_flush(Gamep g);
void wid_progress_bar(Gamep, const std::string &title, float pct);
void wid_progress_bar_destroy(Gamep);
bool wid_console_receive_input(Gamep g, Widp w, const SDL_Keysym *key);
void wid_console_deserialize(const std::vector< std::string > &r);

std::vector< std::string > wid_console_serialize();

extern Widp wid_topcon_input_line;
extern Widp wid_topcon_window;
extern Widp wid_topcon_container;

extern Widp wid_botcon_input_line;
extern Widp wid_botcon_window;
extern Widp wid_botcon_container;

extern Widp wid_console_input_line;
extern Widp wid_console_window;
extern Widp wid_console_container;

#endif
