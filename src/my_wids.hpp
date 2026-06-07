//
// Copyright goblinhack@gmail.com
//

#ifndef MY_WIDS_HPP
#define MY_WIDS_HPP

#include "my_color_defs.hpp"
#include "my_thing.hpp"
#include "my_wid.hpp"
#include "my_wid_popup.hpp"

#include <string>
#include <vector>

void wid_actionbar_fini(Gamep g);
void wid_botcon_fini(Gamep g);
void wid_botcon_flush(Gamep g);
void wid_botcon_log(const std::string &s);
void wid_cfg_gfx_select(Gamep g, bool menu_was_created_due_to_game_restarting = false);
void wid_cfg_help_select(Gamep g);
void wid_cfg_mouse_select(Gamep g);
void wid_cfg_sound_select(Gamep g);
void wid_console_deserialize(const std::vector< std::string > &r);
void wid_console_fini(Gamep g);
void wid_console_flush(Gamep g);
void wid_console_log(const std::string &s);
void wid_console_raise(Gamep g);
void wid_credits_select(Gamep g);
void wid_dead_fini(Gamep g);
void wid_dead_select(Gamep g, const std::string &reason);
void wid_error(Gamep g, const std::string &error);
void wid_game_over_select(Gamep g);
void wid_gray_out_button(Gamep g, Widp w);
void wid_hiscores_show(Gamep g);
void wid_intro_select(Gamep g);
void wid_inventory_mouse_over_begin(Gamep g, Widp w, int relx, int rely, int wheelx, int wheely);
void wid_inventory_mouse_over_end(Gamep g, Widp w);
void wid_inventory_show(Gamep g, Levelsp v, Levelp l, Thingp player);
void wid_collect_show(Gamep g, Levelsp v, Levelp l, Thingp player, std::vector< Thingp > /*items_in*/);
void wid_item_menu_select(Gamep g, Levelsp v, Thingp it, bool from_inventory);
void wid_leftbar_fini(Gamep g);
void wid_load_destroy(Gamep g);
void wid_options_menu_destroy(Gamep g);
void wid_load_select(Gamep g);
void wid_main_menu_destroy(Gamep g);
void wid_main_menu_select(Gamep g);
void wid_more_select(Gamep g);
void wid_new_game(Gamep g);
void wid_notice_destroy();
void wid_notice(const std::string &s);
void wid_options_menu_select(Gamep g);
void wid_player_name_select(Gamep g);
void wid_progress_bar_destroy(Gamep g);
void wid_progress_bar(Gamep g, const std::string &title, float pct);
void wid_quit_destroy(Gamep g);
void wid_quit_select(Gamep g);
void wid_rightbar_fini(Gamep g);
void wid_save_destroy(Gamep g);
void wid_save_select(Gamep g);
void wid_seed_select(Gamep g);
void wid_statistics_show(Gamep g, Levelsp v, Levelp l, Thingp player);
void wid_topcon_fini(Gamep g);
void wid_topcon_flush(Gamep g);
void wid_topcon_log(const std::string &s);

[[nodiscard]] auto wid_actionbar_init(Gamep g) -> bool;
[[nodiscard]] auto wid_botcon_init(Gamep g) -> bool;
[[nodiscard]] auto wid_console_init(Gamep g) -> bool;
[[nodiscard]] auto wid_console_receive_input(Gamep g, Widp w, const SDL_Keysym *key) -> bool;
[[nodiscard]] auto wid_console_serialize() -> std::vector< std::string >;
[[nodiscard]] auto wid_inventory_mouse_up(Gamep g, Widp w, int x, int y, uint32_t button) -> bool;
[[nodiscard]] auto wid_leftbar_init(Gamep g) -> bool;
[[nodiscard]] auto wid_new_back_button(Gamep g, Widp parent, const std::string &name) -> Widp;
[[nodiscard]] auto wid_new_button(Gamep g, Widp parent, const std::string &name) -> Widp;
[[nodiscard]] auto wid_new_cancel_button(Gamep g, Widp parent, const std::string &name) -> Widp;
[[nodiscard]] auto wid_new_close_button(Gamep g, Widp parent, const std::string &name) -> Widp;
[[nodiscard]] auto wid_new_continue_button(Gamep g, Widp parent, const std::string &name) -> Widp;
[[nodiscard]] auto wid_new_green_button(Gamep g, Widp parent, const std::string &name) -> Widp;
[[nodiscard]] auto wid_new_menu_button(Gamep g, Widp parent, const std::string &name) -> Widp;
[[nodiscard]] auto wid_new_red_button(Gamep g, Widp parent, const std::string &name) -> Widp;
[[nodiscard]] auto wid_new_save_button(Gamep g, Widp parent, const std::string &name) -> Widp;
[[nodiscard]] auto wid_rightbar_init(Gamep g) -> bool;
[[nodiscard]] auto wid_topcon_init(Gamep g) -> bool;

#endif
