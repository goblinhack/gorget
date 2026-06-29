//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_color.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_main.hpp" // NOLINT
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_spoint.hpp"
#include "my_tile.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_text_box.hpp"
#include "my_wids.hpp"

#include <SDL_keyboard.h>
#include <cstdint>

static WidPopup *wid_level_select_window;

void wid_level_select_destroy()
{
  if (wid_level_select_window == nullptr) {
    return;
  }

  con("Level select menu: destroy");
  TRACE();

  delete wid_level_select_window;
  wid_level_select_window = nullptr;
}

[[nodiscard]] static auto wid_level_select_key_down(Gamep g, Widp w, const struct SDL_Keysym *key) -> bool
{
  TRACE();

  if (sdlk_eq(*key, game_key_console_get(g))) {
    (void) sound_play(g, "keypress");
    return false;
  }

  auto s = to_string(*key);

  if (s == "<Return>" || s == "<Space>" || s == "<Escape>") {
    TRACE();
    (void) sound_play(g, "keypress");

    if (level_select_mouse_down(g)) {
      wid_level_select_destroy();
    }
    return true;
  }

  return false;
}

[[nodiscard]] static auto wid_level_select_mouse_up(Gamep g, Widp w, int x, int y, uint32_t button) -> bool
{
  con("Level select menu: start");
  TRACE();

  if (level_select_mouse_down(g)) {
    wid_level_select_destroy();
  }

  return true;
}

void wid_level_select(Gamep g)
{
  con("Level select menu: select");
  TRACE();

  if (wid_level_select_window != nullptr) {
    wid_level_select_destroy();
  }

  auto         width = UI_RIGHTBAR_WIDTH;
  spoint const tl(TERM_WIDTH - width, 0);
  spoint const br(TERM_WIDTH - 1, TERM_HEIGHT - 1);
  auto         menu_width  = br.x - tl.x;
  auto         menu_height = br.y - tl.y;

  wid_level_select_window = new WidPopup(g, "level_select", tl, br, nullptr, "", false, false);

  wid_set_on_key_down(wid_level_select_window->wid_popup_container, wid_level_select_key_down);

  wid_level_select_window->log_empty_line(g);
  wid_level_select_window->log(g, UI_GREEN_FMT_STR "Hello again, mortal.");
  wid_level_select_window->log_empty_line(g);
  wid_level_select_window->log_empty_line(g);
  wid_level_select_window->log(g, UI_INFO1_FMT_STR "Ready to enter the next level?", TEXT_FORMAT_LHS);
  wid_level_select_window->log_empty_line(g);

  {
    TRACE();
    auto *p = wid_level_select_window->wid_text_area->wid_text_area;
    auto *w = wid_new_continue_button(g, p, "continue");

    spoint const button_tl((menu_width / 2) - 5, menu_height - 6);
    spoint const button_br((menu_width / 2) + 4, menu_height - 4);

    wid_set_on_mouse_up(w, wid_level_select_mouse_up);
    wid_set_pos(w, button_tl, button_br);
  }

  wid_update(g, wid_level_select_window->wid_text_area->wid_text_area);
}
