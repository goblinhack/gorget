//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_wids.hpp"

static WidPopup *wid_item_menu_window;

//
// Used for keypresses, so we know which item to operate on
//
static Thingp g_item;

static bool wid_item_menu_destroy(Gamep g)
{
  TRACE_NO_INDENT();

  delete wid_item_menu_window;
  wid_item_menu_window = nullptr;

  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  auto l = game_level_get(g, v);
  if (! l) {
    return false;
  }

  auto player = thing_player(g);
  if (! player) {
    return false;
  }

  if (thing_inventory_is_empty(g, v, l, player)) {
    //
    // If empty, just go back to playing
    //
    game_state_change(g, STATE_PLAYING, "close inventory");
  } else {
    //
    // Re-open the inventory
    //
    wid_inventory_show(g, v, l, player);
  }

  return true;
}

static bool wid_item_menu_drop(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  auto l = game_level_get(g, v);
  if (! l) {
    return false;
  }

  auto player = thing_player(g);
  if (! player) {
    return false;
  }

  auto item = g_item;
  if (! item) {
    return false;
  }

  if (! thing_drop_item(g, v, l, item, player)) {
    sound_play(g, "error");
    return false;
  }

  return wid_item_menu_destroy(g);
}

static bool wid_item_menu_equip(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  TOPCON("TODO equip");
  return wid_item_menu_destroy(g);
}

static bool wid_item_menu_back(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  return wid_item_menu_destroy(g);
}

static bool wid_item_menu_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
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
              case 'd' :
              case 'D' :
                sound_play(g, "keypress");
                wid_item_menu_drop(g, nullptr, 0, 0, 0);
                return true;
              case 'e' :
              case 'E' :
                sound_play(g, "keypress");
                wid_item_menu_equip(g, nullptr, 0, 0, 0);
                return true;
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE :
                sound_play(g, "keypress");
                wid_item_menu_back(g, nullptr, 0, 0, 0);
                return true;
            }
          }
      }
  }

  return false;
}

void wid_item_menu_select(Gamep g, Levelsp v, Thingp item)
{
  TRACE_NO_INDENT();
  LOG("Item menu");

  g_item = item;

  if (wid_item_menu_window) {
    wid_item_menu_destroy(g);
  }

  auto box_height  = 2;
  auto box_step    = 3;
  auto menu_height = 2;

  if (thing_is_item_droppable(item)) {
    menu_height += box_step;
  }

  if (thing_is_item_equipable(item)) {
    menu_height += box_step;
  }

  //
  // Back menu
  //
  menu_height += box_step;

  int    menu_width = UI_WID_POPUP_WIDTH_NORMAL;
  spoint outer_tl(TERM_WIDTH / 2 - (menu_width / 2), TERM_HEIGHT / 2 - (menu_height / 2));
  spoint outer_br(TERM_WIDTH / 2 + (menu_width / 2), TERM_HEIGHT / 2 + (menu_height / 2) - 1);
  wid_item_menu_window = new WidPopup(g, "Item menu", outer_tl, outer_br, nullptr, "", false, false);

  auto button_width = outer_br.x - outer_tl.x - 2;

  {
    TRACE_NO_INDENT();
    Widp w = wid_item_menu_window->wid_popup_container;
    wid_set_on_key_down(g, w, wid_item_menu_key_down);
  }

  int y_at = 0;

  if (thing_is_item_droppable(item)) {
    TRACE_NO_INDENT();
    auto p = wid_item_menu_window->wid_text_area->wid_text_area;
    auto w = wid_menu_button(g, p, "Drop");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + box_height);
    wid_set_on_mouse_up(g, w, wid_item_menu_drop);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "D" UI_FMT_STR "rop");
    y_at += box_step;
  }

  if (thing_is_item_equipable(item)) {
    TRACE_NO_INDENT();
    auto p = wid_item_menu_window->wid_text_area->wid_text_area;
    auto w = wid_menu_button(g, p, "Equip");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + box_height);
    wid_set_on_mouse_up(g, w, wid_item_menu_equip);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "E" UI_FMT_STR "quip");
    y_at += box_step;
  }

  {
    TRACE_NO_INDENT();
    auto p = wid_item_menu_window->wid_text_area->wid_text_area;
    auto w = wid_back_button(g, p, "BACK");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + box_height);
    wid_set_on_mouse_up(g, w, wid_item_menu_back);
    wid_set_pos(w, tl, br);
  }

  wid_update(g, wid_item_menu_window->wid_text_area->wid_text_area);

  game_state_change(g, STATE_ITEM_MENU, "close inventory");
}
