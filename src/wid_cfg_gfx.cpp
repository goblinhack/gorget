//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_color_defs.hpp"
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
  TRACE_NO_INDENT();
  delete wid_cfg_gfx_window;
  wid_cfg_gfx_window = nullptr;
}

static bool wid_cfg_gfx_save(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();

  CON("Save config for gfx");
  game_save_config(g);

  wid_cfg_gfx_destroy(g);

  g_need_restart = true;
  wid_main_menu_destroy(g);

  return true;
}

static bool wid_cfg_gfx_cancel(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  CON("Reload config");
  wid_cfg_gfx_destroy(g);
  wid_options_menu_select(g);
  return true;
}

static bool wid_cfg_gfx_back(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_cfg_gfx_destroy(g);
  wid_options_menu_select(g);
  return true;
}

static bool wid_cfg_gfx_vsync_enable_toggle(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  CON("Toggle vsync");
  if (game_gfx_vsync_enable_get(g)) {
    game_gfx_vsync_enable_unset(g);
  } else {
    game_gfx_vsync_enable_set(g);
  }
  config_gfx_vsync_update(g);

  wid_cfg_gfx_save(g, nullptr, 0, 0, 0);
  return true;
}

static bool wid_cfg_gfx_fullscreen_toggle(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  CON("Toggle gfx fullscreen");
  if (game_gfx_fullscreen_get(g)) {
    game_gfx_fullscreen_unset(g);
  } else {
    game_gfx_fullscreen_set(g);
  }

  if (game_gfx_fullscreen_get(g)) {
    game_gfx_fullscreen_desktop_unset(g);
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
  TRACE_NO_INDENT();
  CON("Toggle gfx fullscreen desktop");

  if (game_gfx_fullscreen_desktop_get(g)) {
    game_gfx_fullscreen_desktop_unset(g);
  } else {
    game_gfx_fullscreen_desktop_set(g);
  }

  if (game_gfx_fullscreen_desktop_get(g)) {
    game_gfx_fullscreen_unset(g);
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
  TRACE_NO_INDENT();
  CON("Toggle gfx allow highdpi");

  if (game_gfx_allow_highdpi_get(g)) {
    game_gfx_allow_highdpi_unset(g);
  } else {
    game_gfx_allow_highdpi_set(g);
  }

  wid_cfg_gfx_save(g, nullptr, 0, 0, 0);
  return true;
}

static bool wid_cfg_gfx_borderless_toggle(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  CON("Toggle gfx borderless");

  if (game_gfx_borderless_get(g)) {
    game_gfx_borderless_unset(g);
  } else {
    game_gfx_borderless_set(g);
  }

  SDL_SetWindowBordered(sdl.window, game_gfx_borderless_get(g) ? SDL_TRUE : SDL_FALSE);

  wid_cfg_gfx_save(g, nullptr, 0, 0, 0);
  return true;
}

static bool wid_cfg_other_fps_counter_toggle(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  CON("Toggle fps counter");

  if (game_fps_counter_get(g)) {
    game_fps_counter_unset(g);

  } else {
    game_fps_counter_set(g);
  }

  wid_cfg_gfx_save(g, nullptr, 0, 0, 0);
  return true;
}

static bool wid_cfg_gfx_resolution_apply(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();

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
  TRACE_NO_INDENT();
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
  TRACE_NO_INDENT();
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

static bool wid_cfg_gfx_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
{
  TRACE_NO_INDENT();

  if (sdlk_eq(*key, game_key_console_get(g))) {
    sound_play(g, "keypress");
    return false;
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        default :
          {
            TRACE_NO_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case 'c' :
              case 'C' :
                sound_play(g, "keypress");
                wid_cfg_gfx_cancel(g, nullptr, 0, 0, 0);
                return true;
              case 's' :
              case 'S' :
                sound_play(g, "keypress");
                wid_cfg_gfx_save(g, nullptr, 0, 0, 0);
                return true;
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE :
                sound_play(g, "keypress");
                wid_cfg_gfx_cancel(g, nullptr, 0, 0, 0);
                return true;
            }
          }
      }
  }

  return false;
}

void wid_cfg_gfx_select(Gamep g)
{
  TRACE_NO_INDENT();
  if (wid_cfg_gfx_window) {
    wid_cfg_gfx_destroy(g);
  }

  auto m = TERM_WIDTH / 2;

  spoint outer_tl(m - 20, TERM_HEIGHT / 2 - 15);
  spoint outer_br(m + 20, TERM_HEIGHT / 2 + 15);

  auto width = outer_br.x - outer_tl.x - 2;

  wid_cfg_gfx_window = new WidPopup(g, "Gfx select", outer_tl, outer_br, nullptr, "", false, false);
  {
    TRACE_NO_INDENT();
    Widp w = wid_cfg_gfx_window->wid_popup_container;
    wid_set_on_key_down(g, w, wid_cfg_gfx_key_down);
  }

  int y_at = 0;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "configuration");

    spoint tl(1, y_at);
    spoint br(width, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Configuration");
  }

  y_at = 3;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_back_button(g, p, "BACK");

    spoint tl(1, y_at);
    spoint br(6, y_at + 2);
    wid_set_on_mouse_up(g, w, wid_cfg_gfx_back);
    wid_set_pos(w, tl, br);
  }

  if (pending_mode_set) {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_menu_button(g, p, "Apply");

    spoint tl(10, y_at);
    spoint br(16, y_at + 2);
    wid_set_on_mouse_up(g, w, wid_cfg_gfx_resolution_apply);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "Apply");
  }

  /////////////////////////////////////////////////////////////////////////
  // resolution
  /////////////////////////////////////////////////////////////////////////
  y_at += 4;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Resolution");

    spoint tl(1, y_at);
    spoint br(width / 2, y_at);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Resolution");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Resolution value");

    spoint tl(width / 2, y_at);
    spoint br(width / 2 + 10, y_at + 2);
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
      TRACE_NO_INDENT();
      auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
      auto w = wid_menu_button(g, p, "Resolution value +");

      spoint tl(width / 2 + 12, y_at);
      spoint br(width / 2 + 14, y_at + 2);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_up(g, w, wid_cfg_gfx_resolution_incr);
      wid_set_text(w, "+");
    }
    {
      TRACE_NO_INDENT();
      auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
      auto w = wid_menu_button(g, p, "Resolution value -");

      spoint tl(width / 2 + 16, y_at);
      spoint br(width / 2 + 18, y_at + 2);
      wid_set_pos(w, tl, br);
      wid_set_on_mouse_up(g, w, wid_cfg_gfx_resolution_decr);
      wid_set_text(w, "-");
    }
  }
  y_at += 2;

  /////////////////////////////////////////////////////////////////////////
  // Terminal
  /////////////////////////////////////////////////////////////////////////
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Terminal");

    spoint tl(1, y_at);
    spoint br(width / 2, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Terminal");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Terminal value");

    spoint tl(width / 2, y_at);
    spoint br(width / 2 + 12, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);

    auto res = std::to_string(TERM_WIDTH) + "x" + std::to_string(TERM_HEIGHT);
    wid_set_text(w, res);
    wid_set_text_lhs(w, true);
  }
  y_at += 1;

  /////////////////////////////////////////////////////////////////////////
  // ascii font
  /////////////////////////////////////////////////////////////////////////
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Font size");

    spoint tl(1, y_at);
    spoint br(width / 2, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Font size");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Font size value");

    spoint tl(width / 2, y_at);
    spoint br(width / 2 + 12, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);

    auto fw  = game_ascii_pix_width_get(g);
    auto fh  = game_ascii_pix_height_get(g);
    auto res = std::to_string(fw) + "x" + std::to_string(fh);
    wid_set_text(w, res);
    wid_set_text_lhs(w, true);
  }
  y_at += 2;

  /////////////////////////////////////////////////////////////////////////
  // Fullscreen desktop
  /////////////////////////////////////////////////////////////////////////
  y_at++;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Full desktop");

    spoint tl(1, y_at);
    spoint br(width / 2, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Full desktop");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_menu_button(g, p, "Fullscreen value");

    spoint tl(23, y_at);
    spoint br(37, y_at + 2);
    wid_set_pos(w, tl, br);
    wid_set_on_mouse_up(g, w, wid_cfg_gfx_fullscreen_desktop_toggle);

    if (game_gfx_fullscreen_desktop_get(g)) {
      wid_set_text(w, "True");
    } else {
      wid_set_text(w, "False");
    }
  }

  if (game_gfx_fullscreen_desktop_get(g)) {
    y_at += 4;
    {
      TRACE_NO_INDENT();
      auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(g, p, "Notice");

      spoint tl(1, y_at);
      spoint br(width - 2, y_at);
      wid_set_shape_none(w);
      wid_set_pos(w, tl, br);
      wid_set_text(w, "^^ Disable to change resolution ^^");
      wid_set_text_lhs(w, true);
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // Fullscreen
  /////////////////////////////////////////////////////////////////////////
  y_at += 3;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Fullscreen");

    spoint tl(1, y_at);
    spoint br(width / 2, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Fullscreen");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_menu_button(g, p, "Fullscreen value");

    spoint tl(23, y_at);
    spoint br(37, y_at + 2);
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
      TRACE_NO_INDENT();
      auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
      auto w = wid_new_square_button(g, p, "High DPI res");

      spoint tl(1, y_at);
      spoint br(width / 2, y_at + 2);
      wid_set_shape_none(w);
      wid_set_pos(w, tl, br);
      wid_set_text_lhs(w, true);
      wid_set_text(w, "High DPI resolution");
    }
    {
      TRACE_NO_INDENT();
      auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
      auto w = wid_menu_button(g, p, "High DPI value");

      spoint tl(23, y_at);
      spoint br(37, y_at + 2);
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
  y_at += 3;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Borderless");

    spoint tl(1, y_at);
    spoint br(width / 2, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Borderless window");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_menu_button(g, p, "Borderless");

    spoint tl(23, y_at);
    spoint br(37, y_at + 2);
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
  y_at += 3;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "Vertical sync");

    spoint tl(1, y_at);
    spoint br(width / 2, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "Vertical sync");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_menu_button(g, p, "Vertical sync value");

    spoint tl(23, y_at);
    spoint br(37, y_at + 2);
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
  y_at += 3;
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(g, p, "FPS counter");

    spoint tl(1, y_at);
    spoint br(width / 2, y_at + 2);
    wid_set_shape_none(w);
    wid_set_pos(w, tl, br);
    wid_set_text_lhs(w, true);
    wid_set_text(w, "FPS counter");
  }
  {
    TRACE_NO_INDENT();
    auto p = wid_cfg_gfx_window->wid_text_area->wid_text_area;
    auto w = wid_menu_button(g, p, "FPS counter value");

    spoint tl(23, y_at);
    spoint br(37, y_at + 2);
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
