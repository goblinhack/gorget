//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp" // NOLINT
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_spoint.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_text_box.hpp"
#include "my_wids.hpp"

#include <SDL_keyboard.h>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <string>

static WidPopup *wid_player_select_window;

void wid_player_select_destroy()
{
  if (wid_player_select_window == nullptr) {
    return;
  }

  log("Player select menu: destroy");
  TRACE();

  delete wid_player_select_window;
  wid_player_select_window = nullptr;
}

[[nodiscard]] static auto wid_player_select_continue(Gamep g)
{
  log("Player select menu: continue");
  TRACE();

  auto *v = game_levels_get(g);
  if (v == nullptr) [[unlikely]] {
    (void) sound_play(g, "error");
    return false;
  }

  Levelp l = thing_player_level(g);
  if (l == nullptr) [[unlikely]] {
    (void) sound_play(g, "error");
    return false;
  }

  wid_player_select_destroy();
  (void) level_change(g, v, LEVEL_ARR_IDX_LEVEL_SELECT);

  return true;
}

[[nodiscard]] static auto wid_player_select_mouse_down(Gamep g, Widp w, int x, int y, uint32_t button) -> bool
{
  log("Player select menu: mouse down");
  TRACE();

  return wid_player_select_continue(g);
}

[[nodiscard]] static auto wid_player_select_key_down(Gamep g, Widp w, const struct SDL_Keysym *key) -> bool
{
  TRACE();

  if (sdlk_eq(*key, game_key_console_get(g))) {
    (void) sound_play(g, "keypress");
    return false;
  }

  auto s = to_string(*key);

  if (s == "<Return>" || s == "<Space>" || s == "<Escape>" || s == "n" || s == "N") {
    TRACE();
    (void) sound_play(g, "keypress");

    return wid_player_select_continue(g);
  }

  return false;
}
void wid_player_select(Gamep g, Levelsp v)
{
  log("Player select menu: select");
  TRACE();

  if (wid_player_select_window != nullptr) {
    wid_player_select_destroy();
  } else if (! v->tick) {
    topcon("Choose one major and one major sacrifice to continue.");
  }

  auto         width = UI_RIGHTBAR_WIDTH;
  spoint const tl(TERM_WIDTH - width, 0);
  spoint const br(TERM_WIDTH - 1, TERM_HEIGHT - 1);
  auto         menu_width  = br.x - tl.x;
  auto         menu_height = br.y - tl.y;

  wid_player_select_window = new WidPopup(g, "player_select", tl, br, nullptr, "", false, false);

  wid_set_on_key_down(wid_player_select_window->wid_popup_container, wid_player_select_key_down);

  {
    TRACE();
    auto *p = wid_player_select_window->wid_text_area->wid_text_area;
    auto *w = wid_new_continue_button(g, p, "continue");

    spoint const button_tl((menu_width / 2) - 5, menu_height - 6);
    spoint const button_br((menu_width / 2) + 4, menu_height - 4);

    wid_set_on_mouse_down(w, wid_player_select_mouse_down);
    wid_set_pos(w, button_tl, button_br);
  }

  wid_update(g, wid_player_select_window->wid_text_area->wid_text_area);
}
