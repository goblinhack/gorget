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
extern bool wid_rightbar_ascii_create(class Game *);

extern WidPopup *wid_load;
extern WidPopup *wid_save;
extern WidPopup *wid_quit_window;

//
// Global widgets.
//
extern Widp wid_rightbar_window;
extern Widp wid_map_mini;
extern Widp wid_rightbar;

extern bool is_mouse_over_rightbar(void);

#endif
