//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_wids.hpp"

static Widp wid_inventory_window;

static void wid_inventory_destroy(Gamep g)
{
  TRACE_NO_INDENT();

  if (wid_inventory_window) {
    wid_destroy(g, &wid_inventory_window);

    game_state_change(g, STATE_PLAYING, "close inventory");
  }
}

static void wid_inventory_mouse_over_begin(Gamep g, Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return;
  }

  auto t = wid_get_thing_context(g, v, w, 0);
  if (! t) {
    return;
  }

  level_cursor_describe_add(g, v, t);
}

static void wid_inventory_mouse_over_end(Gamep g, Widp w)
{
  TRACE_NO_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return;
  }

  auto t = wid_get_thing_context(g, v, w, 0);
  if (! t) {
    return;
  }

  level_cursor_describe_remove(g, v, t);
}

static bool wid_inventory_mouse_up(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  auto t = wid_get_thing_context(g, v, w, 0);
  if (! t) {
    return false;
  }

  wid_inventory_destroy(g);
  wid_item_menu_select(g, v, t);

  return true;
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

static bool wid_inventory_back(Gamep g, Widp w, int x, int y, uint32_t button)
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

  const int inventory_width  = UI_INVENTORY_WIDTH;
  const int inventory_height = UI_INVENTORY_HEIGHT;

  const auto button_width  = inventory_width - 4;
  const auto button_height = 0;
  const auto button_step   = 1;
  const auto button_style  = UI_WID_STYLE_SPARSE_NONE;

  auto y_at = 2;

  const int left_half  = inventory_width / 2;
  const int right_half = inventory_width - left_half;
  const int top_half   = inventory_height / 2;
  const int bot_half   = inventory_height - top_half;

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

  {
    TRACE_NO_INDENT();
    auto   w = wid_new_square_button(g, wid_inventory_window, "text");
    spoint tl(0, y_at);
    spoint br(inventory_width, y_at);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_FMT_STR "Mouse select an item or press key a-z");
    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_shape_none(w);
    wid_set_text_centerx(w, true);
    y_at += 2;
  }

  FOR_ALL_INVENTORY_SLOTS(g, v, l, player, slot, item)
  {
    auto tp = item ? thing_tp(item) : nullptr;

    //
    // Item icon
    //
    if (tp) {
      Tilep tile = tp_tiles_get(tp, THING_ANIM_IDLE, 0);
      if (tile) {
        TRACE_NO_INDENT();
        auto   w = wid_new_square_button(g, wid_inventory_window, "Icon");
        spoint tl(1, y_at);
        spoint br(2, y_at + button_height);
        wid_set_tile(TILE_LAYER_BG_0, w, tile);
        wid_set_style(w, button_style);
        wid_set_pos(w, tl, br);

        if (item) {
          wid_set_thing_context(g, v, w, item);
          wid_set_on_mouse_over_begin(g, w, wid_inventory_mouse_over_begin);
          wid_set_on_mouse_over_end(g, w, wid_inventory_mouse_over_end);
          wid_set_on_mouse_up(g, w, wid_inventory_mouse_up);
        }
      }
    }

    //
    // Key shortcut
    //
    {
      TRACE_NO_INDENT();
      auto w = wid_new_square_button(g, wid_inventory_window, "Key");

      std::string s;
      s += (char) ('a' + _n_);
      s += ')';

      spoint tl(3, y_at);
      spoint br(6, y_at + button_height);
      wid_set_text_lhs(w, true);

      wid_set_mode(g, w, WID_MODE_NORMAL);
      wid_set_color(w, WID_COLOR_TEXT_FG, GRAY50);
      wid_set_style(w, button_style);
      wid_set_pos(w, tl, br);
      wid_set_text(w, s);

      if (item) {
        wid_set_thing_context(g, v, w, item);
        wid_set_on_mouse_over_begin(g, w, wid_inventory_mouse_over_begin);
        wid_set_on_mouse_over_end(g, w, wid_inventory_mouse_over_end);
        wid_set_on_mouse_up(g, w, wid_inventory_mouse_up);
      }
    }

    //
    // Item name
    //
    {
      std::string s;

      if (item) {
        s = tp_long_name(tp);
      } else {
        s = "-";
      }

      if (slot->count) {
        s += " x";
        s += std::to_string(slot->count);
      }

      {
        TRACE_NO_INDENT();
        auto w = wid_solid_button(g, wid_inventory_window, "Item");

        spoint tl(6, y_at);
        spoint br(button_width, y_at + button_height);
        wid_set_text_lhs(w, true);
        wid_set_pos(w, tl, br);
        wid_set_text(w, s);

        if (item) {
          wid_set_thing_context(g, v, w, item);
          wid_set_on_mouse_over_begin(g, w, wid_inventory_mouse_over_begin);
          wid_set_on_mouse_over_end(g, w, wid_inventory_mouse_over_end);
          wid_set_on_mouse_up(g, w, wid_inventory_mouse_up);
        }
      }
    }

    y_at += button_step;
  }

  {
    TRACE_NO_INDENT();
    auto w = wid_back_button(g, wid_inventory_window, "BACK");

    spoint tl(inventory_width / 2 - 4, inventory_height - 4);
    spoint br(inventory_width / 2 + 3, inventory_height - 2);
    wid_set_on_mouse_up(g, w, wid_inventory_back);
    wid_set_pos(w, tl, br);
  }

  wid_update(g, wid_inventory_window);

  game_state_change(g, STATE_INVENTORY, "inventory");
}
