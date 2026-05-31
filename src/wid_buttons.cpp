//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game_defs.hpp"
#include "my_time.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wids.hpp"
#include <algorithm>
#include <cstdint>
#include <string>

void wid_gray_out_button(Gamep /*g*/, Widp w)
{
  TRACE();

  wid_set_mode(w, WID_MODE_OVER);
  wid_set_style(w, UI_WID_STYLE_SOLID_WHITE);
  wid_set_color(w, WID_COLOR_BG, GRAY50);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  wid_set_mode(w, WID_MODE_NORMAL);
  wid_set_style(w, UI_WID_STYLE_SOLID_WHITE);
  wid_set_color(w, WID_COLOR_BG, GRAY40);
}

[[nodiscard]] auto wid_new_back_button(Gamep g, Widp parent, const std::string &name) -> Widp
{
  TRACE();

  auto *w = wid_new_square_button(g, parent, name);
  wid_set_text(w, "BACK");
  wid_set_mode(w, WID_MODE_OVER);
  wid_set_style(w, UI_WID_STYLE_SOLID_WHITE);
  wid_set_color(w, WID_COLOR_BG, RED);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  wid_set_mode(w, WID_MODE_NORMAL);
  return w;
}

[[nodiscard]] auto wid_new_close_button(Gamep g, Widp parent, const std::string &name) -> Widp
{
  TRACE();

  auto *w = wid_new_square_button(g, parent, name);
  wid_set_text(w, "CLOSE");
  wid_set_mode(w, WID_MODE_OVER);
  wid_set_style(w, UI_WID_STYLE_SOLID_WHITE);
  wid_set_color(w, WID_COLOR_BG, RED);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  wid_set_mode(w, WID_MODE_NORMAL);
  return w;
}

static void wid_button_pulse(Gamep /*g*/, Widp w)
{
  TRACE();

  auto        pulse = THING_IS_HOT_PULSE_ANIM_MS; // ms
  float const mid   = pulse / 2;
  auto const  n     = static_cast< float >(time_ms_cached() % pulse);
  float       i     = 0;

  uint8_t a = 0;

  if (n == mid) {
    a = 255;
  } else if (n > mid) {
    i = (n - mid) / mid;
    i *= 100;
    i = 255 - i;
  } else {
    i = n / mid;
    i *= 100;
    i = 155 + i;
  }

  i = std::max< float >(i, 0);
  i = std::min< float >(i, 255);

  a = static_cast< uint8_t >(i);

  color c = wid_get_color(w, WID_COLOR_BG);
  c.a     = a;
  wid_set_color(w, WID_COLOR_BG, c);
}

[[nodiscard]] auto wid_new_continue_button(Gamep g, Widp parent, const std::string &name) -> Widp
{
  TRACE();

  auto *w = wid_new_square_button(g, parent, name);
  wid_set_text(w, "CONTINUE");
  wid_set_mode(w, WID_MODE_OVER);
  wid_set_style(w, UI_WID_STYLE_SOLID_WHITE);
  wid_set_color(w, WID_COLOR_BG, GREEN);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  wid_set_mode(w, WID_MODE_NORMAL);
  wid_set_style(w, UI_WID_STYLE_SOLID_WHITE);
  wid_set_color(w, WID_COLOR_BG, GREEN2);
  wid_set_on_tick(w, wid_button_pulse);
  return w;
}

[[nodiscard]] auto wid_new_menu_button(Gamep g, Widp parent, const std::string &name) -> Widp
{
  TRACE();

  auto *w = wid_new_square_button(g, parent, name);
  wid_set_mode(w, WID_MODE_OVER);
  wid_set_style(w, UI_WID_STYLE_SOLID_WHITE);
  wid_set_color(w, WID_COLOR_BG, GREEN);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  wid_set_mode(w, WID_MODE_NORMAL);
  return w;
}

[[nodiscard]] auto wid_new_button(Gamep g, Widp parent, const std::string &name) -> Widp
{
  TRACE();

  auto *w = wid_new_square_button(g, parent, name);
  wid_set_mode(w, WID_MODE_OVER);
  wid_set_style(w, UI_WID_STYLE_SOLID_WHITE);
  wid_set_color(w, WID_COLOR_BG, GREEN);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  wid_set_mode(w, WID_MODE_NORMAL);
  wid_set_style(w, UI_WID_STYLE_SOLID_WHITE);
  wid_set_color(w, WID_COLOR_BG, GRAY20);
  return w;
}

[[nodiscard]] auto wid_new_green_button(Gamep g, Widp parent, const std::string &name) -> Widp
{
  TRACE();

  auto *w = wid_new_square_button(g, parent, name);
  wid_set_mode(w, WID_MODE_OVER);
  wid_set_style(w, UI_WID_STYLE_SOLID_WHITE);
  wid_set_color(w, WID_COLOR_BG, GREEN);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  wid_set_mode(w, WID_MODE_NORMAL);
  wid_set_style(w, UI_WID_STYLE_GREEN);
  return w;
}

[[nodiscard]] auto wid_new_red_button(Gamep g, Widp parent, const std::string &name) -> Widp
{
  TRACE();

  auto *w = wid_new_square_button(g, parent, name);
  wid_set_mode(w, WID_MODE_OVER);
  wid_set_style(w, UI_WID_STYLE_SOLID_WHITE);
  wid_set_color(w, WID_COLOR_BG, RED);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  wid_set_mode(w, WID_MODE_NORMAL);
  wid_set_style(w, UI_WID_STYLE_RED);
  return w;
}

[[nodiscard]] auto wid_new_save_button(Gamep g, Widp parent, const std::string &name) -> Widp
{
  TRACE();

  return wid_new_green_button(g, parent, name);
}

[[nodiscard]] auto wid_new_cancel_button(Gamep g, Widp parent, const std::string &name) -> Widp
{
  TRACE();

  return wid_new_red_button(g, parent, name);
}
