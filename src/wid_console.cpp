//
// Copyright goblinhack@gmail.com
//

#include <algorithm>
#include <map>

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_command.hpp"
#include "my_sdl_proto.hpp"
#include "my_wid_console.hpp"

static int wid_console_inited;
static int wid_console_commands_inited;
static int wid_console_exiting;

static void wid_console_wid_create(Gamep);

Widp wid_console_container {};
Widp wid_console_vert_scroll {};
Widp wid_console_horiz_scroll {};
Widp wid_console_input_line {};
Widp wid_console_window {};

static std::map< unsigned int, std::string > wid_console_lines;

void wid_console_fini(Gamep g)
{
  TRACE_NO_INDENT();
  wid_console_exiting = true;

  if (wid_console_inited) {
    wid_console_inited = false;
  }

  wid_destroy(g, &wid_console_container);
  wid_destroy(g, &wid_console_vert_scroll);
  wid_destroy(g, &wid_console_horiz_scroll);
  wid_destroy(g, &wid_console_input_line);
  wid_destroy(g, &wid_console_window);
}

bool wid_console_init(Gamep g)
{
  TRACE_NO_INDENT();

  if (! wid_console_commands_inited) {
    command_add(g, config_debug_set, "set debug [0123]", "set debug level");
    command_add(g, config_fps_counter_set, "set fps [01]", "enable frames per sec counter");
    command_add(g, config_gfx_vsync_enable, "set vsync [01]", "enable vertical sync enable");
    command_add(g, config_errored, "clear errored", "used to clear a previous error");
    command_add(g, sdl_user_exit, "quit", "exit game");
    wid_console_commands_inited = true;
  }

  wid_console_inited = true;

  wid_console_wid_create(g);

  wid_console_lines.clear();

  wid_console_exiting = false;

  return true;
}

//
// Scroll back to the bottom of the screen.
//
static void wid_console_reset_scroll(Gamep g)
{
  TRACE_NO_INDENT();
  if (! wid_console_vert_scroll) {
    return;
  }

  wid_move_to_bottom(g, wid_console_vert_scroll);
}

//
// Log a message to the console
//
static void wid_console_log_(Gamep g, std::string s)
{
  TRACE_NO_INDENT();
  static int log_wid_console_buffered_lines;

  if (wid_console_exiting) {
    return;
  }

  wid_console_reset_scroll(g);

  //
  // Before the console is ready, we buffer the logs.
  //
  if (! wid_console_input_line) {
    auto result = wid_console_lines.insert(std::make_pair(log_wid_console_buffered_lines++, s));

    if (! result.second) {
      DIE("Wid console lines insert name [%s] failed", s.c_str());
    }

    return;
  }

  //
  // Flush the logs now the console exists.
  //
  auto iter = wid_console_lines.begin();

  while (iter != wid_console_lines.end()) {
    wid_scroll_with_input(g, wid_console_input_line, iter->second);
    iter = wid_console_lines.erase(iter);
  }

  wid_scroll_with_input(g, wid_console_input_line, s);
}

//
// Log a message to the console
//
void wid_console_log(std::string s)
{
  TRACE_NO_INDENT();

  extern Gamep game;
  auto         g = game;

  int chars_per_line = UI_CONSOLE_WIDTH;
  if (chars_per_line <= 0) {
    chars_per_line = 80;
  }

  auto d = split(s, chars_per_line);

  for (const auto &c : d) {
    wid_console_log_(g, c);
  }
}

//
// Key down etc...
//
bool wid_console_receive_input(Gamep g, Widp w, const SDL_Keysym *key)
{
  TRACE_NO_INDENT();

  wid_console_reset_scroll(g);

  switch (key->sym) {
    case SDLK_RETURN :
      {
        break;
      }

    default : break;
  }

  //
  // Feed to the general input handler
  //
  return (wid_receive_input(g, w, key));
}

//
// Create the console
//
static void wid_console_wid_create(Gamep g)
{
  TRACE_NO_INDENT();

  spoint outer_tl(0, 0);
  spoint outer_br(TERM_WIDTH - 1, TERM_HEIGHT - 1);
  int    w = outer_br.x - outer_tl.x;
  int    h = outer_br.y - outer_tl.y;

  wid_console_window = wid_new_square_window(g, "wid console");
  wid_set_pos(wid_console_window, outer_tl, outer_br);
  wid_set_color(wid_console_window, WID_COLOR_BG, WHITE);
  wid_set_color(wid_console_window, WID_COLOR_TEXT_FG, WHITE);

  {
    spoint tl(0, 0);
    spoint br(w - 1, h);

    wid_console_container = wid_new_container(g, wid_console_window, "wid console inner area");
    wid_set_pos(wid_console_container, tl, br);
    wid_set_style(wid_console_container, UI_WID_STYLE_CONSOLE);
  }

  {
    int row;
    int row_bottom = UI_CONSOLE_HEIGHT - 1;

    Widp child {};
    Widp prev {};

    for (row = 0; row < UI_CONSOLE_HEIGHT; row++) {
      row_bottom--;

      spoint tl(0, row_bottom);
      spoint br(UI_CONSOLE_WIDTH, row_bottom);

      child = wid_new_container(g, wid_console_container, "console line");

      wid_set_shape_none(child);
      wid_set_pos(child, tl, br);
      wid_set_text_lhs(child, true);

      wid_set_prev(g, child, prev);
      prev = child;

      if (row == 0) {
        wid_set_on_key_down(g, child, wid_console_receive_input);

        wid_set_show_cursor(child, true);
        wid_set_name(child, "console input");
        wid_set_focusable(child, 1);
        wid_move_delta(g, child, 1, 0);
        wid_console_input_line = child;

        Widp prefix = wid_new_container(g, wid_console_container, "console final line");
        wid_set_pos(prefix, tl, br);
        wid_set_text_lhs(prefix, true);
        wid_set_shape_none(prefix);
        wid_set_text(prefix, ">");
        wid_set_color(child, WID_COLOR_BG, COLOR_NONE);
        wid_set_color(child, WID_COLOR_TEXT_FG, UI_CONSOLE_INPUT_COLOR);
      } else {
        wid_set_color(child, WID_COLOR_BG, COLOR_NONE);
        wid_set_color(child, WID_COLOR_TEXT_FG, UI_CONSOLE_TEXT_COLOR);
        wid_set_name(child, "console output");
      }
    }

    wid_raise(g, wid_console_input_line);
  }

  wid_console_vert_scroll  = wid_new_vert_scroll_bar(g, wid_console_window, "", wid_console_container);
  wid_console_horiz_scroll = wid_new_horiz_scroll_bar(g, wid_console_window, "", wid_console_container);

  wid_visible(g, wid_get_parent(wid_console_vert_scroll));
  wid_hide(g, wid_get_parent(wid_console_horiz_scroll));
  wid_hide(g, wid_console_window);

  wid_set_ignore_scroll_events(wid_console_window, true);

  wid_update(g, wid_console_window);
}

std::vector< std::string > wid_console_serialize(void)
{
  TRACE_NO_INDENT();
  std::vector< std::string > r;
  auto                       tmp = wid_get_head(wid_console_input_line);
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

void wid_console_deserialize(std::vector< std::string > r)
{
  TRACE_NO_INDENT();
  DBG2("Start of replaying old logs");
  DBG2("Vvvvvvvvvvvvvvvvvvvvvvvvvvv");
  for (auto s : r) {
    if (s.size()) {
      wid_console_log(s);
    }
  }
  DBG2("^^^^^^^^^^^^^^^^^^^^^^^^^^^");
  DBG2("End of replaying of old log");
}
