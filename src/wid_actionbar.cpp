//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sdl_proto.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wids.hpp"

static Widp      wid_actionbar {};
static WidPopup *wid_over_save {};
static WidPopup *wid_over_load {};
static WidPopup *wid_over_wait {};
static WidPopup *wid_over_ascend {};
static WidPopup *wid_over_descend {};
static WidPopup *wid_over_quit {};
static WidPopup *wid_actionbar_popup {};

static ts_t wid_last_wait;
static ts_t wid_last_wait_repeat;

static bool wid_actionbar_save(Gamep g, Widp w, int x, int y, uint32_t button)
{
  LOG("Actionbar save");
  TRACE_AND_INDENT();
  return game_event_save(g);
}

static void wid_actionbar_save_over_begin(Gamep g, Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 10;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;

  bry -= 1;
  tly -= 0;

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_save = new WidPopup(g, "Load game", tl, br, nullptr, "", false, false);
  wid_over_save->log(g, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Load game");
  wid_over_save->log_empty_line(g);
  wid_over_save->log(g, "Select this to load an old game");
  wid_over_save->compress(g);
}

static void wid_actionbar_save_over_end(Gamep g, Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_save;
  wid_over_save = nullptr;
}

static bool wid_actionbar_load(Gamep g, Widp w, int x, int y, uint32_t button)
{
  LOG("Actionbar load");
  TRACE_AND_INDENT();
  return game_event_load(g);
}

static void wid_actionbar_load_over_begin(Gamep g, Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 10;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;

  bry -= 1;
  tly -= 0;

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_load = new WidPopup(g, "Save game", tl, br, nullptr, "", false, false);
  wid_over_load->log(g, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Save game");
  wid_over_load->log_empty_line(g);
  wid_over_load->log(g, "Select this to load your current progress");
  wid_over_load->compress(g);
}

static void wid_actionbar_load_over_end(Gamep g, Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_load;
  wid_over_load = nullptr;
}

static bool wid_actionbar_wait(Gamep g, Widp w, int x, int y, uint32_t button)
{
  LOG("Actionbar wait");
  TRACE_AND_INDENT();

  wid_last_wait = time_ms_cached();

  return game_event_wait(g);
}

static bool wid_actionbar_repeat_wait(Gamep g, Widp w, int x, int y, uint32_t button)
{
  LOG("Actionbar wait");
  TRACE_AND_INDENT();

  if (! time_have_x_tenths_passed_since(1, wid_last_wait)) {
    return true;
  }

  if (! time_have_x_tenths_passed_since(1, wid_last_wait_repeat)) {
    return true;
  }

  wid_last_wait_repeat = time_ms_cached();
  return game_event_wait(g);
}

static void wid_actionbar_wait_over_begin(Gamep g, Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 13;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;

  bry -= 1;
  tly += 1;

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_wait = new WidPopup(g, "Wait/rest", tl, br, nullptr, "", false, false);
  wid_over_wait->log(g, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Wait/rest");
  wid_over_wait->log_empty_line(g);
  wid_over_wait->log(g, "Select this to waste one turn of your existence waiting.");
  wid_over_wait->log_empty_line(g);
  wid_over_wait->log(g, "Hold down to pass multiple turns.");
  wid_over_wait->compress(g);
}

static void wid_actionbar_wait_over_end(Gamep g, Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_wait;
  wid_over_wait = nullptr;
}

static bool wid_actionbar_ascend(Gamep g, Widp w, int x, int y, uint32_t button)
{
  LOG("Actionbar ascend");
  TRACE_AND_INDENT();

  return game_event_ascend(g);
}

static void wid_actionbar_ascend_over_begin(Gamep g, Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 13;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;

  bry -= 1;
  tly += 1;

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_ascend = new WidPopup(g, "Descend", tl, br, nullptr, "", false, false);
  wid_over_ascend->log(g, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Ascend");
  wid_over_ascend->log_empty_line(g);
  wid_over_ascend->log(g, "Select this return to level selection.");
  wid_over_ascend->compress(g);
}

static void wid_actionbar_ascend_over_end(Gamep g, Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_ascend;
  wid_over_ascend = nullptr;
}

static bool wid_actionbar_descend(Gamep g, Widp w, int x, int y, uint32_t button)
{
  LOG("Actionbar descend");
  TRACE_AND_INDENT();

  return game_event_descend(g);
}

static void wid_actionbar_descend_over_begin(Gamep g, Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 13;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;

  bry -= 1;
  tly += 1;

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_descend = new WidPopup(g, "Wait/rest", tl, br, nullptr, "", false, false);
  wid_over_descend->log(g, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Descend");
  wid_over_descend->log_empty_line(g);
  wid_over_descend->log(g, "Select this to descend further into the dungeon.");
  wid_over_descend->compress(g);
}

static void wid_actionbar_descend_over_end(Gamep g, Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_descend;
  wid_over_descend = nullptr;
}

static bool wid_actionbar_quit(Gamep g, Widp w, int x, int y, uint32_t button)
{
  LOG("Actionbar quit");
  TRACE_AND_INDENT();

  return game_event_quit(g);
}

static void wid_actionbar_quit_over_begin(Gamep g, Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  int tlx;
  int tly;
  int brx;
  int bry;
  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int width  = 32;
  int height = 6;

  tlx -= width / 2;
  brx += width / 2;
  tly -= height;
  bry -= 1;
  tly -= 0;

  point tl(tlx, tly);
  point br(brx, bry);

  wid_over_quit = new WidPopup(g, "Quit", tl, br, nullptr, "", false, false);
  wid_over_quit->log(g, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Quit game");
  wid_over_quit->log_empty_line(g);
  wid_over_quit->log(g, "Select this to abandon all hope.");
  wid_over_quit->compress(g);
}

static void wid_actionbar_quit_over_end(Gamep g, Widp w)
{
  TRACE_NO_INDENT();

  delete wid_over_quit;
  wid_over_quit = nullptr;
}

bool wid_actionbar_create_window(Gamep g)
{
  TRACE_NO_INDENT();

  wid_actionbar_fini(g);

  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  auto l = game_level_get(g, v);
  if (! l) {
    return false;
  }

  auto player = thing_player(g);
  if (! player) {
    return false;
  }

  if (player->is_dead) {
    return false;
  }

  auto box_style           = UI_WID_STYLE_HORIZ_DARK;
  auto box_highlight_style = UI_WID_STYLE_HORIZ_LIGHT;

  int  option_width = 10;
  int  options      = 2;
  bool opt_load     = false;
  bool opt_save     = false;
  bool opt_descend  = level_is_exit(g, v, l, player->at);
  bool opt_ascend   = level_is_entrance(g, v, l, player->at);

  if (g_opt_debug1 || (l->level_num == LEVEL_SELECT_ID)) {
    opt_save = true;
    opt_load = true;
  }

  if (opt_save) {
    options++;
  }

  if (opt_load) {
    options++;
  }

  int width      = options * (option_width + 1);
  int left_half  = width / 2;
  int right_half = width - left_half;

  {
    point tl = make_point(TERM_WIDTH / 2 - left_half, TERM_HEIGHT - 2);
    point br = make_point(TERM_WIDTH / 2 + right_half - 1, TERM_HEIGHT - 2);

    wid_actionbar = wid_new_square_window(g, "wid actionbar");
    wid_set_ignore_scroll_events(wid_actionbar, true);
    wid_set_pos(wid_actionbar, tl, br);
    wid_set_shape_none(wid_actionbar);
    wid_set_shape_none(wid_actionbar);
    wid_lower(g, wid_actionbar);
  }

  int x_at = 0;

  if (opt_descend) {
    auto  w  = wid_new_square_button(g, wid_actionbar, "wid actionbar descend");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, 0);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_down(g, w, wid_actionbar_descend);
    wid_set_on_mouse_over_begin(g, w, wid_actionbar_descend_over_begin);
    wid_set_on_mouse_over_end(g, w, wid_actionbar_descend_over_end);
    wid_set_text(w, "%%fg=" UI_TEXT_SHORTCUT_COLOR_STR "$" + ::to_string(game_key_descend_get(g))
                        + "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$" + " Wait");
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    x_at += option_width + 1;
  }

  if (opt_ascend) {
    auto  w  = wid_new_square_button(g, wid_actionbar, "wid actionbar ascend");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, 0);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_down(g, w, wid_actionbar_ascend);
    wid_set_on_mouse_over_begin(g, w, wid_actionbar_ascend_over_begin);
    wid_set_on_mouse_over_end(g, w, wid_actionbar_ascend_over_end);
    wid_set_text(w, "%%fg=" UI_TEXT_SHORTCUT_COLOR_STR "$" + ::to_string(game_key_ascend_get(g))
                        + "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$" + " Wait");
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    x_at += option_width + 1;
  }

  {
    auto  w  = wid_new_square_button(g, wid_actionbar, "wid actionbar wait");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, 0);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_down(g, w, wid_actionbar_wait);
    wid_set_on_mouse_held(g, w, wid_actionbar_repeat_wait);
    wid_set_on_mouse_over_begin(g, w, wid_actionbar_wait_over_begin);
    wid_set_on_mouse_over_end(g, w, wid_actionbar_wait_over_end);
    wid_set_text(w, "%%fg=" UI_TEXT_SHORTCUT_COLOR_STR "$" + ::to_string(game_key_wait_get(g))
                        + "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$" + " Wait");
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    x_at += option_width + 1;
  }

  if (opt_load) {
    auto  w  = wid_new_square_button(g, wid_actionbar, "wid actionbar load");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, 0);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(g, w, wid_actionbar_load);
    wid_set_on_mouse_over_begin(g, w, wid_actionbar_load_over_begin);
    wid_set_on_mouse_over_end(g, w, wid_actionbar_load_over_end);
    wid_set_text(w, "%%fg=" UI_TEXT_SHORTCUT_COLOR_STR "$" + ::to_string(game_key_load_get(g))
                        + "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$" + " Load");
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    x_at += option_width + 1;
  }

  if (opt_save) {
    auto  w  = wid_new_square_button(g, wid_actionbar, "wid actionbar save");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, 0);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(g, w, wid_actionbar_save);
    wid_set_on_mouse_over_begin(g, w, wid_actionbar_save_over_begin);
    wid_set_on_mouse_over_end(g, w, wid_actionbar_save_over_end);
    wid_set_text(w, "%%fg=" UI_TEXT_SHORTCUT_COLOR_STR "$" + ::to_string(game_key_save_get(g))
                        + "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$" + " Save");
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    x_at += option_width + 1;
  }

  {
    auto  w  = wid_new_square_button(g, wid_actionbar, "wid actionbar quit");
    point tl = make_point(x_at, 0);
    point br = make_point(x_at + option_width - 1, 0);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(g, w, wid_actionbar_quit);
    wid_set_on_mouse_over_begin(g, w, wid_actionbar_quit_over_begin);
    wid_set_on_mouse_over_end(g, w, wid_actionbar_quit_over_end);
    wid_set_text(w, "%%fg=" UI_TEXT_SHORTCUT_COLOR_STR "$" + ::to_string(game_key_quit_get(g))
                        + "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$" + " Quit");
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    x_at += option_width + 1;
  }

  wid_update(g, wid_actionbar);

  return true;
}

void wid_actionbar_fini(Gamep g)
{
  TRACE_NO_INDENT();
  wid_destroy(g, &wid_actionbar);

  delete wid_actionbar_popup;
  wid_actionbar_popup = nullptr;
}

bool wid_actionbar_init(Gamep g)
{
  TRACE_NO_INDENT();
  return wid_actionbar_create_window(g);
}

bool wid_actionbar_create(Gamep g)
{
  wid_actionbar_fini(g);

  auto level = game_levels_get(g);
  if (! level) {
    return false;
  }

  return wid_actionbar_create_window(g);
}
