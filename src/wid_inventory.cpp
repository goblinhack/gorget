//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_wids.hpp"

static Widp wid_inventory_window;

static void wid_inventory_destroy(Gamep g)
{
  TRACE_NO_INDENT();
  wid_destroy(g, &wid_inventory_window);

  game_state_change(g, STATE_PLAYING, "close inventory");
}

static bool wid_inventory_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
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
              case '\n' :
              case SDLK_ESCAPE :
                {
                  TRACE_NO_INDENT();
                  sound_play(g, "keypress");
                  wid_inventory_destroy(g);
                  return true;
                }
            }
          }
      }
  }

  //
  // So screenshots can work
  //
  return false;
}

static bool wid_inventory_mouse_up(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_inventory_destroy(g);
  return true;
}

void wid_inventory_show(Gamep g, Levelsp v, Levelp l, Thingp player)
{
  TRACE_NO_INDENT();

  if (wid_inventory_window) {
    wid_inventory_destroy(g);
  }

  if (thing_is_dead(player)) {
    return;
  }

  auto ai_struct = thing_ai_struct(g, player);
  if (! ai_struct) {
    return;
  }

#if 0
  auto box_style           = UI_WID_STYLE_HORIZ_DARK;
  auto box_highlight_style = UI_WID_STYLE_HORIZ_LIGHT;
#endif

  static int inventory_width  = UI_INVENTORY_WIDTH;
  static int inventory_height = UI_INVENTORY_HEIGHT;

  int left_half  = inventory_width / 2;
  int right_half = inventory_width - left_half;
  int top_half   = inventory_height / 2;
  int bot_half   = inventory_height - top_half;

  {
    TRACE_NO_INDENT();
    spoint tl(TERM_WIDTH / 2 - left_half, TERM_HEIGHT / 2 - top_half);
    spoint br(TERM_WIDTH / 2 + right_half - 1, TERM_HEIGHT / 2 + bot_half - 1);

    wid_inventory_window = wid_new_square_window(g, "wid inventory");
    wid_set_pos(wid_inventory_window, tl, br);
    wid_set_style(wid_inventory_window, UI_WID_STYLE_NORMAL);
    wid_set_on_key_down(g, wid_inventory_window, wid_inventory_key_down);
    wid_set_text(wid_inventory_window, "Inventory");
    wid_set_text_top(wid_inventory_window, true);
    wid_raise(g, wid_inventory_window);
  }

  FOR_ALL_INVENTORY_SLOTS(g, v, l, player, slot, item)
  { //
    if (! item) {
      THING_LOG(player, "slot %d: -", _n_);
      continue;
    }

    auto s = to_string(g, item);
    if (slot->count) {
      THING_LOG(player, "slot %d: %s, count %d", _n_, s.c_str(), slot->count);
    } else {
      THING_LOG(player, "slot %d: %s", _n_, s.c_str());
    }
  }

  {
    TRACE_NO_INDENT();
    auto w = wid_new_square_button(g, wid_inventory_window, "BACK");

    spoint tl(inventory_width / 2 - 4, inventory_height - 4);
    spoint br(inventory_width / 2 + 3, inventory_height - 2);

    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(g, w, wid_inventory_mouse_up);

    wid_set_pos(w, tl, br);
    wid_set_text(w, "BACK");
  }

  wid_update(g, wid_inventory_window);

  game_state_change(g, STATE_INVENTORY, "inventory");
}
