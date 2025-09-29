//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_wids.hpp"

static WidPopup *wid_item_menu_window;

static void wid_item_menu_destroy(Gamep g)
{
  TRACE_NO_INDENT();
  delete wid_item_menu_window;
  wid_item_menu_window = nullptr;
}

static bool wid_item_menu_drop(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_item_menu_destroy(g);
  TOPCON("TODO drop");
  return true;
}

static bool wid_item_menu_equip(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_item_menu_destroy(g);
  TOPCON("TODO equip");
  return true;
}

static bool wid_item_menu_back(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_item_menu_destroy(g);
  wid_main_menu_select(g);
  return true;
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

void wid_item_menu_select(Gamep g, Levelsp v, Thingp it)
{
  TRACE_NO_INDENT();
  LOG("Item menu");

  if (wid_item_menu_window) {
    wid_item_menu_destroy(g);
  }

  auto box_height = 2;
  auto box_step   = 3;

  int menu_height = 8;

  if (thing_is_item_droppable(it)) {
    menu_height += box_step;
  }

  if (thing_is_item_equipable(it)) {
    menu_height += box_step;
  }

  int    menu_width = UI_WID_POPUP_WIDTH_NORMAL;
  spoint outer_tl(TERM_WIDTH / 2 - (menu_width / 2), TERM_HEIGHT / 2 - (menu_height / 2));
  spoint outer_br(TERM_WIDTH / 2 + (menu_width / 2), TERM_HEIGHT / 2 + (menu_height / 2));
  wid_item_menu_window = new WidPopup(g, "Item menu", outer_tl, outer_br, nullptr, "nothing", false, false);

  auto button_width = outer_br.x - outer_tl.x - 2;

  {
    TRACE_NO_INDENT();
    Widp w = wid_item_menu_window->wid_popup_container;
    wid_set_on_key_down(g, w, wid_item_menu_key_down);
  }

  int y_at = 0;

  y_at += box_step;
  if (thing_is_item_droppable(it)) {
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

  if (thing_is_item_equipable(it)) {
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
