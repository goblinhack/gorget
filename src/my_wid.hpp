//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_WID_HPP_
#define _MY_WID_HPP_

#include "my_color.hpp"
#include "my_spoint.hpp"
#include "my_time.hpp"
#include "my_types.hpp"

typedef enum {
  WID_COLOR_BG,
  WID_COLOR_TEXT_FG,
  WID_COLOR_TEXT_BG,
  WID_COLOR_MAX,
} wid_color;

typedef enum {
  WID_MODE_NORMAL,
  WID_MODE_OVER,
  WID_MODE_FOCUS,
  WID_MODE_ACTIVE,
  WID_MODE_LAST,
} wid_mode;

#define WID_MODE_FIRST WID_MODE_NORMAL

char wid_event_to_char(const struct SDL_Keysym *evt);

color wid_get_color(Widp, wid_color which);

int wid_get_br_x(Widp);
int wid_get_br_y(Widp);
int wid_get_height(Widp);
int wid_get_style(Widp);
int wid_get_tl_x(Widp);
int wid_get_tl_y(Widp);
int wid_get_width(Widp);

std::string to_string(Widp);
std::string wid_get_name(Widp);
std::string wid_name(Widp);

std::string wid_get_text(Widp);
std::string wid_get_tooltip(Widp);

Widp wid_find_at(int x, int y);
Widp wid_find(const std::string &name);
Widp wid_find_under_mouse(void);
Widp wid_find_under_mouse_when_scrolling(Gamep);
Widp wid_find(Widp, const std::string &name);
Widp wid_get_current_focus(void);
Widp wid_get_focus(Widp);
Widp wid_get_head(Widp);
Widp wid_get_next(Widp);
Widp wid_get_parent(Widp);
Widp wid_get_prev(Widp);
Widp wid_get_scrollbar_horiz(Widp);
Widp wid_get_scrollbar_vert(Widp);
Widp wid_get_tail(Widp);
Widp wid_get_top_parent(Widp);
Widp wid_new_container(Gamep, Widp, std::string name);
Widp wid_new_horiz_scroll_bar(Gamep, Widp parent, std::string name, Widp scrollbar_owner);
Widp wid_new_plain(Gamep, Widp parent, std::string name);
Widp wid_new_square_button(Gamep, Widp parent, std::string name);
Widp wid_new_window(Gamep, std::string name);
Widp wid_new_vert_scroll_bar(Gamep, Widp parent, std::string name, Widp scrollbar_owner);
typedef bool (*on_joy_button_t)(Gamep, Widp, int x, int y);
typedef bool (*on_key_down_t)(Gamep, Widp, const struct SDL_Keysym *);
typedef bool (*on_key_up_t)(Gamep, Widp, const struct SDL_Keysym *);
typedef bool (*on_mouse_down_t)(Gamep, Widp, int x, int y, uint32_t button);
typedef bool (*on_mouse_held_t)(Gamep, Widp, int x, int y, uint32_t button);
typedef bool (*on_mouse_motion_t)(Gamep, Widp, int x, int y, int relx, int rely, int wx, int wy);
typedef bool (*on_mouse_up_t)(Gamep, Widp, int x, int y, uint32_t button);

typedef void (*on_destroy_begin_t)(Gamep, Widp);
typedef void (*on_destroy_t)(Gamep, Widp);
typedef void (*on_mouse_focus_begin_t)(Gamep, Widp);
typedef void (*on_mouse_focus_end_t)(Gamep, Widp);
typedef void (*on_mouse_over_begin_t)(Gamep, Widp, int relx, int rely, int wheelx, int wheely);
typedef void (*on_mouse_over_end_t)(Gamep, Widp);
typedef void (*on_tick_t)(Gamep, Widp);
typedef void (*on_display_t)(Gamep, Widp, spoint tl, spoint br);

int         wid_count(Widp w, int depth);
int         wid_get_int_context(Widp);
std::string wid_get_string_context(Widp);
void        wid_set_int_context(Widp w, int);
void       *wid_get_void_context(Widp);
void        wid_set_string_context(Widp w, std::string);
void        wid_set_void_context(Widp w, void *);

bool wid_get_do_not_lower(Widp);
bool wid_get_do_not_raise(Widp);
bool wid_get_focusable(Widp);
bool wid_get_mode_top(Widp);
bool wid_get_moveable_bounded(Widp);
bool wid_get_moveable_horiz(Widp);
bool wid_get_moveable_no_user_scroll(Widp);
bool wid_get_moveable_vert(Widp);
bool wid_get_moveable(Widp);
bool wid_get_received_input(Widp);
bool wid_get_show_cursor(Widp);
bool wid_get_text_bot(Widp);
bool wid_get_text_centerx(Widp);
bool wid_get_text_centery(Widp);
bool wid_get_text_lhs(Widp);
bool wid_get_text_pos(Widp, int *x, int *y);
bool wid_get_text_rhs(Widp);
bool wid_get_text_top(Widp);
bool wid_ignore_being_destroyed(Widp);
bool wid_ignore_events_only(Widp);
bool wid_ignore_events(Widp);
bool wid_ignore_for_focus(Widp);
bool wid_ignore_scroll_events(Widp);
bool wid_init(void);
bool wid_is_always_hidden(const Widp);
bool wid_is_hidden(Widp);
bool wid_is_visible(const Widp);
bool wid_receive_input(Gamep, Widp, const SDL_Keysym *key);
bool wid_scroll_trough_mouse_down(Gamep, Widp w, int x, int y, uint32_t button);
bool wid_scroll_trough_mouse_motion(Gamep, Widp w, int x, int y, int relx, int rely, int wheelx, int wheely);
bool wid_some_recent_event_occurred(void);
void wid_destroy_in(Gamep, Widp w, uint32_t ms);
void wid_destroy_nodelay(Gamep, Widp *);
void wid_destroy_ptr_in(Gamep, Widp *w, uint32_t ms);
void wid_destroy(Gamep, Widp *);
void wid_display_all(Gamep);
void wid_dump(Widp w, int depth);
void wid_fake_joy_button(Gamep, int x, int y);
void wid_set_first_focus(Gamep);
void wid_set_top_focus(Gamep);
void wid_fini(Gamep);
void wid_focus_lock(Gamep, Widp);
void wid_gc_all_force(Gamep);
void wid_gc_all(Gamep);
void wid_sanity_check(Gamep);
void wid_get_abs_coords_unclipped(Widp w, int *tlx, int *tly, int *brx, int *bry);
void wid_get_abs_coords(Widp w, int *tlx, int *tly, int *brx, int *bry);
void wid_get_abs(Widp w, int *x, int *y);
void wid_get_children_size(Widp, int *width, int *height);
void wid_get_pct(Widp w, float *x, float *y);
void wid_get_tl_x_tl_y_br_x_br_y(Widp w, int *tl_x, int *tl_y, int *br_x, int *br_y);
void wid_hide(Gamep, Widp);
void wid_ignore_events_briefly(Gamep);
void wid_joy_button(Gamep, int x, int y);
void wid_key_down(Gamep, const struct SDL_Keysym *, int x, int y);
void wid_key_up(Gamep, const struct SDL_Keysym *, int x, int y);
void wid_lower(Gamep, Widp);
void wid_mouse_down(Gamep, uint32_t button, int x, int y);
void wid_mouse_focus_begin(Gamep, Widp);
void wid_mouse_focus_end(Gamep);
void wid_mouse_held(Gamep, uint32_t button, int x, int y);
void wid_mouse_hide(Gamep, int);
void wid_mouse_motion_begin(Gamep, Widp, int x, int y);
void wid_mouse_motion(Gamep, int x, int y, int relx, int rely, int wheelx, int wheely);
void wid_mouse_motion_end(Gamep);
void wid_mouse_move(Gamep, Widp);
void wid_mouse_over_end(Gamep);
void wid_mouse_up(Gamep, uint32_t button, int x, int y);
void wid_mouse_warp(Gamep, Widp);
void wid_move_delta_pct(Gamep, Widp, float dx, float dy);
void wid_move_delta(Gamep, Widp, int dx, int dy);
void wid_move_end(Gamep, Widp);
void wid_move_to_abs_centered(Gamep, Widp, int dx, int dy);
void wid_move_to_abs(Gamep, Widp, int dx, int dy);
void wid_move_to_bottom(Gamep, Widp);
void wid_move_to_horiz_pct(Gamep, Widp w, float pct);
void wid_move_to_left(Gamep, Widp);
void wid_move_to_pct_centered(Gamep, Widp, float dx, float dy);
void wid_move_to_pct(Gamep, Widp, float dx, float dy);
void wid_move_to_right(Gamep, Widp);
void wid_move_to_top(Gamep, Widp);
void wid_move_to_vert_pct(Gamep, Widp w, float pct);
void wid_move_to(Gamep, Widp w, int x, int y);
void wid_move_to_y_off(Gamep, Widp w, int off);
void wid_raise(Gamep, Widp);
void wid_resize(Gamep, Widp w, int width, int height);
void wid_scroll_text(Widp);
void wid_scroll_with_input(Gamep, Widp, std::string str);
void wid_set_active(Gamep, Widp);
void wid_set_color(Widp, wid_color col, color val);
void wid_set_cursor(Widp, uint32_t val);
void wid_set_debug(Widp, uint8_t);
void wid_set_do_not_lower(Widp, uint8_t val);
void wid_set_do_not_raise(Widp, uint8_t val);
void wid_set_focusable(Widp, uint8_t val);
void wid_set_focus(Gamep, Widp);
void wid_set_ignore_events(Widp, uint8_t);
void wid_set_ignore_for_mouse_down(Widp, uint8_t);
void wid_set_ignore_scroll_events(Widp, uint8_t);
void wid_set_mode(Widp, wid_mode mode);
void wid_set_moveable_bounded(Gamep, Widp, uint8_t val);
void wid_set_moveable_horiz(Gamep, Widp, uint8_t val);
void wid_set_moveable_no_user_scroll(Gamep, Widp, uint8_t val);
void wid_set_moveable_vert(Gamep, Widp, uint8_t val);
void wid_set_moveable(Gamep, Widp, uint8_t val);
void wid_set_name(Widp, std::string);
void wid_set_on_destroy_begin(Widp, on_destroy_begin_t fn);
void wid_set_on_destroy(Widp, on_destroy_t fn);
void wid_set_on_display(Widp, on_display_t fn);
void wid_set_on_joy_button(Widp, on_joy_button_t fn);
void wid_set_on_key_down(Widp, on_key_down_t fn);
void wid_set_on_key_up(Widp, on_key_up_t fn);
void wid_set_on_mouse_down(Widp, on_mouse_down_t fn);
void wid_set_on_mouse_focus_begin(Widp, on_mouse_focus_begin_t fn);
void wid_set_on_mouse_focus_end(Widp, on_mouse_focus_end_t fn);
void wid_set_on_mouse_held(Widp, on_mouse_down_t fn);
void wid_set_on_mouse_motion(Widp, on_mouse_motion_t fn);
void wid_set_on_mouse_over_begin(Widp, on_mouse_over_begin_t fn);
void wid_set_on_mouse_over_end(Widp, on_mouse_over_end_t fn);
void wid_set_on_mouse_up(Widp, on_mouse_up_t fn);
void wid_set_on_tick(Widp, on_tick_t fn);
void wid_set_pos(Widp, spoint tl, spoint br);
void wid_set_prev(Widp w, Widp);
void wid_set_received_input(Widp, uint8_t val);
void wid_set_shape_none(Widp);
void wid_set_shape_square(Widp);
void wid_set_show_cursor(Widp, uint8_t val);
void wid_set_style(Widp w, int style);
void wid_set_text_bot(Widp, uint8_t val);
void wid_set_text_centerx(Widp, uint8_t val);
void wid_set_text_centery(Widp, uint8_t val);
void wid_set_text_lhs(Widp, uint8_t val);
void wid_set_text_max_len(Widp, size_t);
void wid_set_text_pos(Widp, uint8_t val, int x, int y);
void wid_set_text_rhs(Widp, uint8_t val);
void wid_set_text_top(Widp, uint8_t val);
void wid_set_text(Widp, int);
void wid_set_text(Widp, std::string);
void wid_set_tile(int depth, Widp w, Tilep tile);
void wid_set_tilename(int depth, Widp, std::string name);
void wid_set_top(Gamep, Widp, uint8_t val);
void wid_toggle_hidden(Gamep, Widp);
void wid_unset_focus(Gamep);
void wid_unset_focus_lock(void);
void wid_update_mouse(Gamep);
void wid_update(Gamep, Widp);
void wid_visible(Gamep, Widp);

wid_mode wid_get_mode(Widp);

extern bool      wid_exiting;
extern bool      wid_init_done;
extern bool      wid_mouse_two_clicks;
extern const int wid_destroy_delay_ms;
extern int       wid_mouse_visible;

extern ts_t wid_ignore_events_briefly_ts;
extern ts_t wid_last_mouse_motion;
extern ts_t wid_last_over_event;

extern Widp wid_focus;
extern Widp wid_over;
extern Widp wid_focus_locked;

#endif
