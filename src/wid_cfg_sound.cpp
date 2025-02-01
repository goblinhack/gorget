//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <SDL_mixer.h>

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_music.hpp"
#include "my_sdl_proto.hpp"
#include "my_wids.hpp"

static WidPopup *wid_cfg_sound_window;
static bool      local_g_config_changed;

static void wid_cfg_sound_destroy(Gamep g)
{
  TRACE_AND_INDENT();
  delete wid_cfg_sound_window;
  wid_cfg_sound_window   = nullptr;
  local_g_config_changed = false;
}

static bool wid_cfg_sound_cancel(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("INF: Reload config");
  if (local_g_config_changed) {
    local_g_config_changed = false;
    game_load_config(g);
    sdl_config_update_all(g);
  }
  wid_cfg_sound_destroy(g);
  wid_cfg_top_menu(g);
  return true;
}

static bool wid_cfg_sound_save(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("INF: Save config");
  game_save_config(g);
  wid_cfg_sound_destroy(g);
  wid_cfg_top_menu(g);
  return true;
}

static bool wid_cfg_sound_back(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_cfg_sound_destroy(g);
  wid_cfg_top_menu(g);
  return true;
}

static bool wid_cfg_sound_effects_volume_incr(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  local_g_config_changed = true;
  CON("INF: Increment sound volume");
  auto vol = game_sound_volume_get(g);
  game_sound_volume_set(g, vol + 1);
  if (game_sound_volume_get(g) > MIX_MAX_VOLUME) {
    game_sound_volume_set(g, MIX_MAX_VOLUME);
  }
  wid_cfg_sound_select(g);
  return true;
}

static bool wid_cfg_sound_effects_volume_decr(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  local_g_config_changed = true;
  CON("INF: Decrement sound volume");
  auto vol = game_sound_volume_get(g);
  game_sound_volume_set(g, vol - 1);
  if (game_sound_volume_get(g) < 0) {
    game_sound_volume_set(g, 0);
  }
  wid_cfg_sound_select(g);
  return true;
}

static bool wid_cfg_sound_music_volume_incr(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  local_g_config_changed = true;
  CON("INF: Increment music volume");
  auto vol = game_music_volume_get(g);
  game_music_volume_set(g, vol + 1);
  if (game_music_volume_get(g) > MIX_MAX_VOLUME) {
    game_music_volume_set(g, MIX_MAX_VOLUME);
  }
  wid_cfg_sound_select(g);
  music_update_volume(g);
  return true;
}

static bool wid_cfg_sound_music_volume_decr(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  local_g_config_changed = true;
  CON("INF: Decrement music volume");
  auto vol = game_music_volume_get(g);
  game_music_volume_set(g, vol - 1);
  if (game_music_volume_get(g) < 0) {
    game_music_volume_set(g, 0);
  }
  wid_cfg_sound_select(g);
  music_update_volume(g);
  return true;
}

static bool wid_cfg_sound_key_up(Gamep g, Widp w, const struct SDL_Keysym *key)
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
              case 'C' : wid_cfg_sound_cancel(g, nullptr, 0, 0, 0); return true;
              case 's' :
              case 'S' : wid_cfg_sound_save(g, nullptr, 0, 0, 0); return true;
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE : wid_cfg_sound_cancel(g, nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static bool wid_cfg_sound_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game_key_console_get(g))) {
    return false;
  }

  return true;
}

void wid_cfg_sound_select(Gamep g)
{
  TRACE_AND_INDENT();
  if (wid_cfg_sound_window) {
    wid_cfg_sound_destroy(g);
  }

  auto box_style           = UI_WID_STYLE_HORIZ_DARK;
  auto box_highlight_style = UI_WID_STYLE_HORIZ_LIGHT;
  auto m                   = TERM_WIDTH / 2;

  point outer_tl(m - 16, TERM_HEIGHT / 2 - 5);
  point outer_br(m + 16, TERM_HEIGHT / 2 + 6);

  auto width = outer_br.x - outer_tl.x - 2;

  wid_cfg_sound_window = new WidPopup(g, "Config sound select", outer_tl, outer_br, nullptr, "", false, false);

  {
    TRACE_AND_INDENT();
    Widp w = wid_cfg_sound_window->wid_popup_container;
    wid_set_on_key_up(g, w, wid_cfg_sound_key_up);
    wid_set_on_key_down(g, w, wid_cfg_sound_key_down);
  }

  int y_at = 0;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "configuration");

    point tl(1, y_at);
    point br(width, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Configuration");
  }

  y_at = 3;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Back");

    point tl(1, y_at);
    point br(6, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(g, w, wid_cfg_sound_back);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$B%%fg=reset$ack");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Save");

    point tl(width - 15, y_at);
    point br(width - 10, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_GREEN);
    wid_set_on_mouse_up(g, w, wid_cfg_sound_save);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$S%%fg=reset$ave");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Cancel");

    point tl(width - 8, y_at);
    point br(width - 1, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_up(g, w, wid_cfg_sound_cancel);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$C%%fg=reset$ancel");
  }

  y_at += 4;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Effects volume");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Effects");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Effects volume value");

    point tl(width / 2, y_at);
    point br(width / 2 + 8, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, std::to_string(game_sound_volume_get(g)));
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Effects value +");

    point tl(width / 2 + 9, y_at);
    point br(width / 2 + 11, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_down(g, w, wid_cfg_sound_effects_volume_incr);
    wid_set_on_mouse_held(g, w, wid_cfg_sound_effects_volume_incr);
    wid_set_text(w, "+");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Effects value -");

    point tl(width / 2 + 12, y_at);
    point br(width / 2 + 14, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_down(g, w, wid_cfg_sound_effects_volume_decr);
    wid_set_on_mouse_held(g, w, wid_cfg_sound_effects_volume_decr);
    wid_set_text(w, "-");
  }

  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Music volume");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Music");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Music volume value");

    point tl(width / 2, y_at);
    point br(width / 2 + 8, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_text(w, std::to_string(game_music_volume_get(g)));
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Music value +");

    point tl(width / 2 + 9, y_at);
    point br(width / 2 + 11, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_down(g, w, wid_cfg_sound_music_volume_incr);
    wid_set_on_mouse_held(g, w, wid_cfg_sound_music_volume_incr);
    wid_set_text(w, "+");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_sound_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Music value -");

    point tl(width / 2 + 12, y_at);
    point br(width / 2 + 14, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_down(g, w, wid_cfg_sound_music_volume_decr);
    wid_set_on_mouse_held(g, w, wid_cfg_sound_music_volume_decr);
    wid_set_text(w, "-");
  }

  wid_update(g, wid_cfg_sound_window->wid_text_area->wid_text_area);
}
