//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_ui.hpp"
#include "my_wids.hpp"

Widp wid_back_button(Gamep g, Widp parent, const std::string name)
{
  TRACE_NO_INDENT();

  auto w = wid_new_square_button(g, parent, name);
  wid_set_text(w, "BACK");
  wid_set_mode(g, w, WID_MODE_OVER);
  wid_set_style(w, UI_WID_STYLE_SOLID_GRAY);
  wid_set_color(w, WID_COLOR_BG, RED);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  wid_set_mode(g, w, WID_MODE_NORMAL);
  return w;
}

Widp wid_menu_button(Gamep g, Widp parent, const std::string name)
{
  TRACE_NO_INDENT();

  auto w = wid_new_square_button(g, parent, name);
  wid_set_mode(g, w, WID_MODE_OVER);
  wid_set_style(w, UI_WID_STYLE_SOLID_GRAY);
  wid_set_color(w, WID_COLOR_BG, GREEN);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  wid_set_mode(g, w, WID_MODE_NORMAL);
  return w;
}

Widp wid_solid_button(Gamep g, Widp parent, const std::string name)
{
  TRACE_NO_INDENT();

  auto w = wid_new_square_button(g, parent, name);
  wid_set_mode(g, w, WID_MODE_OVER);
  wid_set_style(w, UI_WID_STYLE_SOLID_GRAY);
  wid_set_color(w, WID_COLOR_BG, GREEN);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  wid_set_mode(g, w, WID_MODE_NORMAL);
  wid_set_style(w, UI_WID_STYLE_SOLID_GRAY);
  wid_set_color(w, WID_COLOR_BG, GRAY20);
  return w;
}

Widp wid_save_button(Gamep g, Widp parent, const std::string name)
{
  TRACE_NO_INDENT();

  return wid_green_button(g, parent, name);
}

Widp wid_cancel_button(Gamep g, Widp parent, const std::string name)
{
  TRACE_NO_INDENT();

  return wid_red_button(g, parent, name);
}

Widp wid_green_button(Gamep g, Widp parent, const std::string name)
{
  TRACE_NO_INDENT();

  auto w = wid_new_square_button(g, parent, name);
  wid_set_mode(g, w, WID_MODE_OVER);
  wid_set_style(w, UI_WID_STYLE_SOLID_GRAY);
  wid_set_color(w, WID_COLOR_BG, GREEN);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  wid_set_mode(g, w, WID_MODE_NORMAL);
  wid_set_style(w, UI_WID_STYLE_GREEN);
  return w;
}

Widp wid_red_button(Gamep g, Widp parent, const std::string name)
{
  TRACE_NO_INDENT();

  auto w = wid_new_square_button(g, parent, name);
  wid_set_mode(g, w, WID_MODE_OVER);
  wid_set_style(w, UI_WID_STYLE_SOLID_GRAY);
  wid_set_color(w, WID_COLOR_BG, RED);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  wid_set_mode(g, w, WID_MODE_NORMAL);
  wid_set_style(w, UI_WID_STYLE_RED);
  return w;
}
