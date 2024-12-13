//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_sdl_proto.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_topcon.hpp"

#include <algorithm>
#include <map>

static void wid_topcon_wid_create(void);

Widp wid_topcon_container {};
Widp wid_topcon_vert_scroll {};
Widp wid_topcon_input_line {};
Widp wid_topcon_window {};

static std::string last_msg;
static int         last_msg_count;

static std::map< unsigned int, std::string > wid_topcon_lines;

void wid_topcon_fini(void)
{
  TRACE_NO_INDENT();
  wid_destroy(&wid_topcon_container);
  wid_destroy(&wid_topcon_vert_scroll);
  wid_destroy(&wid_topcon_input_line);
  wid_destroy(&wid_topcon_window);
}

uint8_t wid_topcon_init(void)
{
  TRACE_NO_INDENT();
  wid_topcon_wid_create();

  last_msg       = "";
  last_msg_count = 0;

  return true;
}

//
// Scroll back to the bottom of the screen.
//
static void wid_topcon_reset_scroll(void)
{
  TRACE_NO_INDENT();
  if (! wid_topcon_vert_scroll) {
    return;
  }

  wid_move_to_bottom(wid_topcon_vert_scroll);
}

static void wid_topcon_scroll(Widp w, std::string str)
{
  TRACE_NO_INDENT();
  Widp tmp {};

  wid_scroll_text(w);

  //
  // Get the wid on the bottom of the list/screen.
  //
  tmp = wid_get_head(w);
  if (tmp) {
    wid_set_text(tmp, str);
  }
}

static void wid_topcon_replace(Widp w, std::string str)
{
  TRACE_NO_INDENT();
  Widp tmp {};

  //
  // Get the wid on the bottom of the list/screen.
  //
  tmp = wid_get_head(w);
  if (tmp) {
    wid_set_text(tmp, str);
  }
}

//
// Log a message to the topcon
//
static void wid_topcon_log_(std::string s)
{
  TRACE_NO_INDENT();
  static int log_wid_topcon_buffered_lines;

  if (! s.size()) {
    return;
  }

  wid_topcon_reset_scroll();

  //
  // Before the topcon is ready, we buffer the logs.
  //
  if (! wid_topcon_input_line) {
    auto result = wid_topcon_lines.insert(std::make_pair(log_wid_topcon_buffered_lines++, s));

    if (! result.second) {
      DIE("Wid topcon lines insert name [%s] failed", s.c_str());
    }

    return;
  }

  //
  // Flush the logs now the topcon exists.
  //
  wid_topcon_flush();

  auto curr_msg = wid_get_text(wid_get_head(wid_topcon_input_line));

  if (last_msg == s) {
    s = last_msg + " (x" + std::to_string(last_msg_count + 2) + ")";
    last_msg_count++;
    wid_topcon_replace(wid_topcon_input_line, s);
  } else if (! curr_msg.empty() && length_without_format(curr_msg) + length_without_format(s) + 1 < UI_TOPCON_WIDTH) {
    curr_msg = curr_msg + " " + s;
    wid_topcon_replace(wid_topcon_input_line, curr_msg);
    last_msg       = "";
    last_msg_count = 0;
  } else {
    last_msg       = s;
    last_msg_count = 0;
    wid_topcon_scroll(wid_topcon_input_line, s);
  }
}

void wid_topcon_flush(void)
{
  TRACE_NO_INDENT();
  auto iter = wid_topcon_lines.begin();

  while (iter != wid_topcon_lines.end()) {
    wid_topcon_scroll(wid_topcon_input_line, iter->second);
    iter = wid_topcon_lines.erase(iter);
  }

  wid_topcon_reset_scroll();
}

//
// Log a message to the topcon
//
void wid_topcon_log(std::string s)
{
  TRACE_NO_INDENT();
  int chars_per_line = UI_TOPCON_WIDTH;

  if (! TERM_WIDTH) {
    DIE("No TERM_WIDTH set");
  }

  auto d = split(s, chars_per_line);

  for (const auto &c : d) {
    wid_topcon_log_(c);
  }
}

//
// Create the topcon
//
static void wid_topcon_wid_create(void)
{
  TRACE_NO_INDENT();
  int h = UI_TOPCON_VIS_HEIGHT;

  if (wid_topcon_window) {
    wid_topcon_fini();
  }

  TRACE_NO_INDENT();
  {
    point tl = make_point(UI_LEFTBAR_WIDTH, 0);
    point br = make_point(UI_TOPCON_VIS_WIDTH - 1, h - 1);

    wid_topcon_window = wid_new_square_window("wid topcon");
    wid_set_name(wid_topcon_window, "wid topcon window");
    wid_set_pos(wid_topcon_window, tl, br);
    wid_set_shape_none(wid_topcon_window);
  }

  TRACE_NO_INDENT();
  {
    point tl = make_point(0, 0);
    point br = make_point(UI_TOPCON_VIS_WIDTH - 1, h - 1);

    wid_topcon_container = wid_new_container(wid_topcon_window, "wid topcon container");
    wid_set_pos(wid_topcon_container, tl, br);
    wid_set_shape_none(wid_topcon_container);
    wid_set_style(wid_topcon_container, UI_WID_STYLE_CONSOLE);
    color c = GRAY;
    c.a     = 150;
    wid_set_color(wid_topcon_container, WID_COLOR_BG, c);
  }

  TRACE_NO_INDENT();
  {
    int row;
    int row_bottom = h;

    Widp child {};
    Widp prev {};

    for (row = 0; row < UI_TOPCON_HEIGHT; row++) {
      row_bottom--;
      point tl = make_point(0, row_bottom);
      point br = make_point(UI_TOPCON_WIDTH - 1, row_bottom);

      TRACE_NO_INDENT();
      child = wid_new_container(wid_topcon_container, "");

      wid_set_shape_none(child);
      wid_set_pos(child, tl, br);
      wid_set_text_lhs(child, true);

      wid_set_prev(child, prev);
      prev = child;

      if (row == 0) {
        wid_topcon_input_line = child;
      }

      wid_set_color(child, WID_COLOR_TEXT_FG, UI_TOPCON_TEXT_COLOR);
      wid_set_color(child, WID_COLOR_BG, COLOR_NONE);
      wid_set_name(child, "topcon output");
    }
  }

  TRACE_NO_INDENT();
  wid_topcon_vert_scroll = wid_new_vert_scroll_bar(wid_topcon_window, "", wid_topcon_container);
  wid_visible(wid_get_parent(wid_topcon_vert_scroll));
  wid_update(wid_topcon_window);
}

std::vector< std::string > wid_topcon_serialize(void)
{
  TRACE_NO_INDENT();
  std::vector< std::string > r;
  auto                       tmp = wid_get_head(wid_topcon_input_line);
  while (tmp) {
    auto s = wid_get_text(tmp);
    if (s.size()) {
      r.push_back(wid_get_text(tmp));
    }
    tmp = wid_get_next(tmp);
  }
  std::reverse(r.begin(), r.end());
  return r;
}

void wid_topcon_deserialize(std::vector< std::string > r)
{
  TRACE_NO_INDENT();
  for (const auto &s : r) {
    auto tmp = s;
    if (tmp.size()) {
      TOPCON("%s", tmp.c_str());
    }
  }
}