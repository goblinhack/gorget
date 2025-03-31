//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_cpp_template.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_wids.hpp"

static WidPopup *wid_cfg_gfx_window;

static SDL_DisplayMode pending_mode;
static bool            pending_mode_set;

static void wid_cfg_gfx_destroy(Gamep g)
{
  TRACE_AND_INDENT();
  delete wid_cfg_gfx_window;
  wid_cfg_gfx_window = nullptr;
}

static bool wid_cfg_gfx_save(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("Save config");
  game_save_config(g);

  wid_cfg_gfx_destroy(g);

  g_need_restart = true;
  wid_main_menu_destroy(g);

  return true;
}

static bool wid_cfg_gfx_cancel(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("Reload config");
  wid_cfg_gfx_destroy(g);
  wid_cfg_top_menu(g);
  return true;
}

static bool wid_cfg_gfx_back(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_cfg_gfx_destroy(g);
  wid_cfg_top_menu(g);
  return true;
}

static bool wid_cfg_gfx_vsync_enable_toggle(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("Toggle vsync");
  game_gfx_vsync_enable_set(g, ! game_gfx_vsync_enable_get(g));
  config_gfx_vsync_update(g);

  wid_cfg_gfx_save(g, nullptr, 0, 0, 0);
  return true;
}

static bool wid_cfg_gfx_fullscreen_toggle(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("Toggle gfx fullscreen");
  game_gfx_fullscreen_set(g, ! game_gfx_fullscreen_get(g));

  if (game_gfx_fullscreen_get(g)) {
    game_gfx_fullscreen_desktop_set(g, false);
  }

  if (game_gfx_fullscreen_get(g)) {
    SDL_SetWindowFullscreen(sdl.window, SDL_WINDOW_FULLSCREEN);
  } else if (game_gfx_fullscreen_desktop_get(g)) {
    SDL_SetWindowFullscreen(sdl.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  } else {
    SDL_SetWindowFullscreen(sdl.window, 0);
  }

  wid_cfg_gfx_save(g, nullptr, 0, 0, 0);
  return true;
}

static bool wid_cfg_gfx_fullscreen_desktop_toggle(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("Toggle gfx fullscreen desktop");
  game_gfx_fullscreen_desktop_set(g, ! game_gfx_fullscreen_desktop_get(g));

  if (game_gfx_fullscreen_desktop_get(g)) {
    game_gfx_fullscreen_set(g, false);
  }

  if (game_gfx_fullscreen_get(g)) {
    SDL_SetWindowFullscreen(sdl.window, SDL_WINDOW_FULLSCREEN);
  } else if (game_gfx_fullscreen_desktop_get(g)) {
    SDL_SetWindowFullscreen(sdl.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  } else {
    SDL_SetWindowFullscreen(sdl.window, 0);
  }

  wid_cfg_gfx_save(g, nullptr, 0, 0, 0);
  return true;
}

static bool wid_cfg_gfx_allow_highdpi_toggle(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("Toggle gfx allow highdpi");
  game_gfx_allow_highdpi_set(g, ! game_gfx_allow_highdpi_get(g));

  wid_cfg_gfx_save(g, nullptr, 0, 0, 0);
  return true;
}

static bool wid_cfg_gfx_borderless_toggle(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("Toggle gfx borderless");
  game_gfx_borderless_set(g, ! game_gfx_borderless_get(g));
  SDL_SetWindowBordered(sdl.window, game_gfx_borderless_get(g) ? SDL_TRUE : SDL_FALSE);

  wid_cfg_gfx_save(g, nullptr, 0, 0, 0);
  return true;
}

static bool wid_cfg_other_fps_counter_toggle(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  CON("Toggle fps counter");
  game_fps_counter_set(g, ! game_fps_counter_get(g));

  wid_cfg_gfx_save(g, nullptr, 0, 0, 0);
  return true;
}

static bool wid_cfg_gfx_resolution_apply(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();

  SDL_DisplayMode mode = pending_mode;
  pending_mode_set     = false;

  game_window_pix_width_set(g, mode.w);
  game_window_pix_height_set(g, mode.h);
  game_config_pix_width_set(g, mode.w);
  game_config_pix_height_set(g, mode.h);
  SDL_SetWindowSize(sdl.window, mode.w, mode.h);
  wid_cfg_gfx_save(g, nullptr, 0, 0, 0);

  return true;
}

static bool wid_cfg_gfx_resolution_incr(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  auto res = std::to_string(game_window_pix_width_get(g)) + "x" + std::to_string(game_window_pix_height_get(g));
  if (pending_mode_set) {
    res = std::to_string(pending_mode.w) + "x" + std::to_string(pending_mode.h);
    CON("Increment resolution (pending %s)", res.c_str());
  } else {
    CON("Increment resolution (current %s)", res.c_str());
  }

  auto                                     n = SDL_GetNumDisplayModes(0);
  std::string                              chosen;
  std::vector< std::string >               cands;
  std::map< std::string, SDL_DisplayMode > modes;
  for (int i = 0; i < n; ++i) {
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, i, &mode);
    auto cand = std::to_string(mode.w) + "x" + std::to_string(mode.h);
    push_back_if_unique(cands, cand);
    modes[ cand ] = mode;
  }
  for (int i = 0; i < (int) cands.size(); ++i) {
    auto cand = cands[ i ];
    if (res == cand) {
      if (i > 0) {
        chosen = cands[ i - 1 ];
        LOG(" - candidate: %s (current)", cand.c_str());
      } else {
        LOG(" - candidate: %s (at max)", cand.c_str());
      }
    } else {
      LOG(" - candidate: %s", cand.c_str());
    }
  }
  if (chosen != "") {
    SDL_DisplayMode mode = modes[ chosen ];
    LOG(" - chosen: %s", chosen.c_str());
    pending_mode_set = true;
    pending_mode     = mode;
    CON("Pending resolution %s", chosen.c_str());
    wid_cfg_gfx_select(g);
  } else {
    sound_play(g, "error");
    CON("At maximum resolution (current %s)", res.c_str());
  }

  return true;
}

static bool wid_cfg_gfx_resolution_decr(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  auto res = std::to_string(game_window_pix_width_get(g)) + "x" + std::to_string(game_window_pix_height_get(g));
  if (pending_mode_set) {
    res = std::to_string(pending_mode.w) + "x" + std::to_string(pending_mode.h);
    CON("Decrement resolution (pending %s)", res.c_str());
  } else {
    CON("Decrement resolution (current %s)", res.c_str());
  }

  auto                                     n = SDL_GetNumDisplayModes(0);
  std::string                              chosen;
  std::vector< std::string >               cands;
  std::map< std::string, SDL_DisplayMode > modes;
  for (int i = 0; i < n; ++i) {
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, i, &mode);
    auto cand = std::to_string(mode.w) + "x" + std::to_string(mode.h);
    push_back_if_unique(cands, cand);
    modes[ cand ] = mode;
  }
  for (int i = 0; i < (int) cands.size(); ++i) {
    auto cand = cands[ i ];
    if (res == cand) {
      if (i < (int) cands.size() - 1) {
        chosen = cands[ i + 1 ];
        LOG(" - candidate: %s (current)", cand.c_str());
      } else {
        LOG(" - candidate: %s (at max)", cand.c_str());
      }
    } else {
      LOG(" - candidate: %s", cand.c_str());
    }
  }
  if (chosen != "") {
    SDL_DisplayMode mode = modes[ chosen ];
    LOG(" - chosen: %s", chosen.c_str());
    pending_mode_set = true;
    pending_mode     = mode;
    CON("Pending resolution %s", chosen.c_str());
    wid_cfg_gfx_select(g);
  } else {
    sound_play(g, "error");
    CON("At minimm resolution (current %s)", res.c_str());
  }

  return true;
}

static bool wid_cfg_gfx_key_up(Gamep g, Widp w, const struct SDL_Keysym *key)
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
              case 'C' : wid_cfg_gfx_cancel(g, nullptr, 0, 0, 0); return true;
              case 's' :
              case 'S' : wid_cfg_gfx_save(g, nullptr, 0, 0, 0); return true;
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE : wid_cfg_gfx_cancel(g, nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static bool wid_cfg_gfx_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game_key_console_get(g))) {
    return false;
  }

  return true;
}

void wid_cfg_gfx_select(Gamep g)
{
  TRACE_AND_INDENT();
  if (wid_cfg_gfx_window) {
    wid_cfg_gfx_destroy(g);
  }

  auto box_style           = UI_WID_STYLE_HORIZ_DARK;
  auto box_highlight_style = UI_WID_STYLE_HORIZ_LIGHT;
  auto m                   = TERM_WIDTH / 2;

  point outer_tl(m - 20, TERM_HEIGHT / 2 - 10);
  point outer_br(m + 20, TERM_HEIGHT / 2 + 10);

  auto width = outer_br.x - outer_tl.x - 2;

  wid_cfg_gfx_window = new WidPopup(g, "Gfx select", outer_tl, outer_br, nullptr, "", false, false);
  {
    TRACE_AND_INDENT();
    Widp w = wid_cfg_gfx_window->wid_popup_container;
    wid_set_on_key_up(g, w, wid_cfg_gfx_key_up);
    wid_set_on_key_down(g, w, wid_cfg_gfx_key_down);
  }

  int y_at = 0;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
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
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Back");

    point tl(1, y_at);
    point br(6, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(g, w, wid_cfg_gfx_back);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=white$B%%fg=reset$ack");
  }

  if (pending_mode_set) {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Apply");

    point tl(10, y_at);
    point br(16, y_at + 2);
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(g, w, wid_cfg_gfx_resolution_apply);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Apply");
  }

  /////////////////////////////////////////////////////////////////////////
  // resolution
  /////////////////////////////////////////////////////////////////////////
  y_at += 4;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Resolution");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Resolution");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Resolution value");

    point tl(width / 2 + 4, y_at);
    point br(width / 2 + 12, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);

    auto res = std::to_string(game_window_pix_width_get(g)) + "x" + std::to_string(game_window_pix_height_get(g));
    if (pending_mode_set) {
      res = std::to_string(pending_mode.w) + "x" + std::to_string(pending_mode.h);
    }

    wid_set_text(w, res);
    wid_set_text_lhs(w, true);
  }

  if (! game_gfx_fullscreen_desktop_get(g)) {
    {
      TRACE_AND_INDENT();
      auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(g, p, "Resolution value +");

      point tl(width / 2 + 13, y_at);
      point br(width / 2 + 15, y_at);
      wid_set_mode(g, w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(g, w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_up(g, w, wid_cfg_gfx_resolution_incr);
      wid_set_text(w, "+");
    }
    {
      TRACE_AND_INDENT();
      auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(g, p, "Resolution value -");

      point tl(width / 2 + 16, y_at);
      point br(width / 2 + 18, y_at);
      wid_set_mode(g, w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(g, w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_up(g, w, wid_cfg_gfx_resolution_decr);
      wid_set_text(w, "-");
    }
  }
  y_at++;

  /////////////////////////////////////////////////////////////////////////
  // terminal
  /////////////////////////////////////////////////////////////////////////
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Terminal");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Terminal");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Terminal value");

    point tl(width / 2 + 4, y_at);
    point br(width / 2 + 12, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);

    auto res = std::to_string(TERM_WIDTH) + "x" + std::to_string(TERM_HEIGHT);
    wid_set_text(w, res);
    wid_set_text_lhs(w, true);
  }
  y_at++;

  /////////////////////////////////////////////////////////////////////////
  // ascii font
  /////////////////////////////////////////////////////////////////////////
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Font size");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Font size");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Font size value");

    point tl(width / 2 + 4, y_at);
    point br(width / 2 + 12, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);

    auto fw  = game_ascii_pix_width_get(g);
    auto fh  = game_ascii_pix_height_get(g);
    auto res = std::to_string(fw) + "x" + std::to_string(fh);
    wid_set_text(w, res);
    wid_set_text_lhs(w, true);
  }
  y_at++;

  /////////////////////////////////////////////////////////////////////////
  // Fullscreen desktop
  /////////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Full desktop");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Full desktop");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Fullscreen value");

    point tl(23, y_at);
    point br(37, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(g, w, wid_cfg_gfx_fullscreen_desktop_toggle);

    if (game_gfx_fullscreen_desktop_get(g)) {
      wid_set_text(w, "True");
    } else {
      wid_set_text(w, "False");
    }
  }

  if (game_gfx_fullscreen_desktop_get(g)) {
    y_at++;
    {
      TRACE_AND_INDENT();
      auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(g, p, "Notice");

      point tl(1, y_at);
      point br(width - 2, y_at);
      wid_set_shape_none(w);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "^^ Disable to change resolution ^^");
      wid_set_text_lhs(w, true);
    }
    y_at++;
  }

  /////////////////////////////////////////////////////////////////////////
  // Fullscreen
  /////////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Fullscreen");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Fullscreen");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Fullscreen value");

    point tl(23, y_at);
    point br(37, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(g, w, wid_cfg_gfx_fullscreen_toggle);

    if (game_gfx_fullscreen_get(g)) {
      wid_set_text(w, "True");
    } else {
      wid_set_text(w, "False");
    }
  }

  if (0) {
    /////////////////////////////////////////////////////////////////////////
    // High DPI
    //
    // Seems to have issues with mouse position, so disabled
    /////////////////////////////////////////////////////////////////////////
    y_at++;
    {
      TRACE_AND_INDENT();
      auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(g, p, "High DPI res");

      point tl(1, y_at);
      point br(width / 2, y_at);
      wid_set_shape_none(w);
      wid_set_pos(w, tl, br);
      wid_set_text_lhs(w, true);
      wid_set_text(w, "High DPI resolution");
    }
    {
      TRACE_AND_INDENT();
      auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(g, p, "High DPI value");

      point tl(23, y_at);
      point br(37, y_at);
      wid_set_mode(g, w, WID_MODE_OVER);
      wid_set_style(w, box_highlight_style);
      wid_set_mode(g, w, WID_MODE_NORMAL);
      wid_set_style(w, box_style);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_up(g, w, wid_cfg_gfx_allow_highdpi_toggle);

      if (game_gfx_allow_highdpi_get(g)) {
        wid_set_text(w, "True");
      } else {
        wid_set_text(w, "False");
      }
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // Borderless
  /////////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Borderless");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Borderless window");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Borderless");

    point tl(23, y_at);
    point br(37, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(g, w, wid_cfg_gfx_borderless_toggle);

    if (game_gfx_borderless_get(g)) {
      wid_set_text(w, "True");
    } else {
      wid_set_text(w, "False");
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // vsync
  /////////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Vertical sync");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Vertical sync");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Vertical sync value");

    point tl(23, y_at);
    point br(37, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(g, w, wid_cfg_gfx_vsync_enable_toggle);

    if (game_gfx_vsync_enable_get(g)) {
      wid_set_text(w, "True");
    } else {
      wid_set_text(w, "False");
    }
  }

  //////////////////////////////////////////////////////////////////////
  // fps
  //////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "FPS counter");

    point tl(1, y_at);
    point br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "FPS counter");
  }
  {
    TRACE_AND_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "FPS counter value");

    point tl(23, y_at);
    point br(37, y_at);
    wid_set_mode(g, w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(g, w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(g, w, wid_cfg_other_fps_counter_toggle);

    if (game_fps_counter_get(g)) {
      wid_set_text(w, "True");
    } else {
      wid_set_text(w, "False");
    }
  }

  wid_update(g, wid_cfg_gfx_window->wid_text_area->wid_text_area);
}
