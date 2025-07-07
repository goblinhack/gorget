//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_sdl_proto.hpp"
#include "my_wids.hpp"

static WidPopup *wid_cfg_mouse_window;
static bool      local_g_config_changed;

static void wid_cfg_mouse_destroy(Gamep g)
{
  TRACE_AND_INDENT();
  delete wid_cfg_mouse_window;
  wid_cfg_mouse_window   = nullptr;
  local_g_config_changed = false;
}

static bool wid_cfg_mouse_cancel(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("Reload config");
  if (local_g_config_changed) {
    local_g_config_changed = false;
    game_load_config(g);
    sdl_config_update_all(g);
  }
  wid_cfg_mouse_destroy(g);
  wid_cfg_select(g);
  return true;
}

static bool wid_cfg_mouse_save(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("Save config");
  game_save_config(g);
  wid_cfg_mouse_destroy(g);
  wid_cfg_select(g);
  return true;
}

static bool wid_cfg_mouse_back(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_cfg_mouse_destroy(g);
  wid_cfg_select(g);
  return true;
}

static bool wid_cfg_mouse_wheel_lr_negated(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  local_g_config_changed = true;
  CON("Toggle wheel mouse lr");
  game_mouse_wheel_lr_negated_set(g, ! game_mouse_wheel_lr_negated_get(g));
  wid_cfg_mouse_select(g);
  return true;
}

static bool wid_cfg_mouse_wheel_ud_negated(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  local_g_config_changed = true;
  CON("Toggle wheel mouse ud");
  game_mouse_wheel_ud_negated_set(g, ! game_mouse_wheel_ud_negated_get(g));
  wid_cfg_mouse_select(g);
  return true;
}

static bool wid_cfg_mouse_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game_key_console_get(g))) {
    return false;
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        default :
          {
            TRACE_AND_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case 'c' :
              case 'C' :         wid_cfg_mouse_cancel(g, nullptr, 0, 0, 0); return true;
              case 's' :
              case 'S' :         wid_cfg_mouse_save(g, nullptr, 0, 0, 0); return true;
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE : wid_cfg_mouse_cancel(g, nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

void wid_cfg_mouse_select(Gamep g)
{
  TRACE_AND_INDENT();
  if (wid_cfg_mouse_window) {
    wid_cfg_mouse_destroy(g);
  }

  auto box_style           = UI_WID_STYLE_HORIZ_DARK;
  auto box_highlight_style = UI_WID_STYLE_HORIZ_LIGHT;

  int    menu_height = 20;
  int    menu_width  = UI_WID_POPUP_WIDTH_NORMAL * 2;
  spoint outer_tl(TERM_WIDTH / 2 - (menu_width / 2), TERM_HEIGHT / 2 - (menu_height / 2));
  spoint outer_br(TERM_WIDTH / 2 + (menu_width / 2), TERM_HEIGHT / 2 + (menu_height / 2));
  wid_cfg_mouse_window = new WidPopup(g, "Mouse", outer_tl, outer_br, nullptr, "", false, false);

  auto button_width = outer_br.x - outer_tl.x - 2;

  {
    TRACE_AND_INDENT();
    Widp w = wid_cfg_mouse_window->wid_popup_container;
    wid_set_on_key_down(g, w, wid_cfg_mouse_key_down);
  }

  int y_at = 0;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_mouse_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "configuration");

    spoint tl(1, y_at);
    spoint br(button_width, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Configuration");
  }

  y_at = 3;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_mouse_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Back");

    spoint tl(1, y_at);
    spoint br(6, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(g, w, wid_cfg_mouse_back);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "B" UI_RESET_FMT "ack");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_mouse_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Save");

    spoint tl(button_width - 15, y_at);
    spoint br(button_width - 10, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_GREEN);
    wid_set_on_mouse_up(g, w, wid_cfg_mouse_save);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "S" UI_RESET_FMT "ave");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_mouse_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Cancel");

    spoint tl(button_width - 8, y_at);
    spoint br(button_width - 1, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_up(g, w, wid_cfg_mouse_cancel);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "C" UI_RESET_FMT "ancel");
  }

  y_at = 6;

  /////////////////////////////////////////////////////////////////////////
  // Inverted mouse scrolling
  /////////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_mouse_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Mouse scroll lr invert lr");

    spoint tl(1, y_at);
    spoint br(button_width, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Mouse invert left/right");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_mouse_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Mouse scroll lr invert");

    spoint tl(28, y_at);
    spoint br(34, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(g, w, wid_cfg_mouse_wheel_lr_negated);

    if (game_mouse_wheel_lr_negated_get(g)) {
      wid_set_text(w, "True");
    } else {
      wid_set_text(w, "False");
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // Inverted mouse scrolling
  /////////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_mouse_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Mouse scroll ud invert");

    spoint tl(1, y_at);
    spoint br(button_width, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Mouse invert up/down");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_mouse_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Mouse scroll ud invert value");

    spoint tl(28, y_at);
    spoint br(34, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(g, w, wid_cfg_mouse_wheel_ud_negated);

    if (game_mouse_wheel_ud_negated_get(g)) {
      wid_set_text(w, "True");
    } else {
      wid_set_text(w, "False");
    }
  }

  wid_update(g, wid_cfg_mouse_window->wid_text_area->wid_text_area);
}
