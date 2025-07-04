//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_topcon.hpp"
#include "my_wids.hpp"

#include <vector>

static WidPopup *wid_dead_window;

static void wid_dead_destroy(Gamep g)
{
  TRACE_AND_INDENT();

  delete wid_dead_window;
  wid_dead_window = nullptr;

  game_destroy_levels(g);

  game_state_reset(g, "close dead menu");
}

static bool wid_dead_key_up(Gamep g, Widp w, const struct SDL_Keysym *key)
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
              case 'q' :
              case SDLK_ESCAPE :
                {
                  TRACE_AND_INDENT();
                  wid_dead_destroy(g);
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static bool wid_dead_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game_key_console_get(g))) {
    return false;
  }

  return false;
}

static bool wid_dead_mouse_up(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();

  wid_dead_destroy(g);

  return true;
}

void wid_dead_select(Gamep g, std::string reason)
{
  TRACE_AND_INDENT();

  LOG("Open dead select: %s", reason.c_str());

  game_state_change(g, STATE_DEAD_MENU, "player is dead");

  if (wid_dead_window) {
    wid_dead_destroy(g);
  }

  auto   h = TERM_HEIGHT / 2;
  spoint tl(0, h + 1);
  spoint br(UI_LEFTBAR_WIDTH - 1, TERM_HEIGHT - 1);
  auto   width = br.x - tl.x - 1;

  wid_dead_window = new WidPopup(g, "Game dead", tl, br, nullptr, "", false, false);

  wid_set_on_key_up(g, wid_dead_window->wid_popup_container, wid_dead_key_up);
  wid_set_on_key_down(g, wid_dead_window->wid_popup_container, wid_dead_key_down);
  wid_raise(g, wid_dead_window->wid_popup_container);

  // Want console to be able to be on top
  // wid_set_do_not_lower(wid_dead_window->wid_popup_container, true);

  auto grave_text_width = 18;

  wid_dead_window->log_empty_line(g);
  wid_dead_window->log_empty_line(g);
  wid_dead_window->log_empty_line(g);
  wid_dead_window->log_empty_line(g);
  wid_dead_window->log_empty_line(g);
  wid_dead_window->log_empty_line(g);
  wid_dead_window->log(g, "   .------------.   ");
  wid_dead_window->log(g, "  /     Rest     \\  ");
  wid_dead_window->log(g, " /       In       \\ ");
  wid_dead_window->log(g, "/      Pieces      \\");
  wid_dead_window->log(g, "|                  |");
  wid_dead_window->log(g, "|                  |");
  wid_dead_window->log(g, "|                  |");

  //
  // Center the player name
  //
  {
    std::string text    = capitalise(game_player_name_get(g));
    int         pad     = grave_text_width - text.size();
    int         lhs_pad = pad / 2;
    int         rhs_pad = pad - lhs_pad;

    std::string grave_name = "|";
    while (lhs_pad--) {
      grave_name += " ";
    }
    grave_name += text;
    while (rhs_pad--) {
      grave_name += " ";
    }
    grave_name += "|";

    wid_dead_window->log(g, grave_name);
    CON("[%s]", grave_name.c_str());
    CON("[%s]", game_player_name_get(g));
  }

  wid_dead_window->log(g, "|                  |");
  wid_dead_window->log(g, "|      Killed      |");

  //
  // Center the death reason
  //
  {
    std::vector< std::string > d = split(capitalise(reason), grave_text_width);

    for (const auto &text : d) {
      int pad     = grave_text_width - text.size();
      int lhs_pad = pad / 2;
      int rhs_pad = pad - lhs_pad;

      std::string death_reason = " |";
      while (lhs_pad--) {
        death_reason += " ";
      }
      death_reason += text;
      while (rhs_pad--) {
        death_reason += " ";
      }
      death_reason += "|";

      wid_dead_window->log(g, death_reason);
    }
  }

  wid_dead_window->log(g, "|                  |");
  wid_dead_window->log(g, "|                  |");
  wid_dead_window->log(g, "|                  |");
  wid_dead_window->log(g, "|                  |");
  wid_dead_window->log(g, "|     " UI_YELLOW_FMT_STR "*" UI_RESET_FMT "            |");
  wid_dead_window->log(g, "|     " UI_GREEN_FMT_STR "|" UI_RESET_FMT "        " UI_YELLOW_FMT_STR "*" UI_RESET_FMT
                          "   |");
  wid_dead_window->log(g, UI_GREEN_FMT_STR ".,." UI_RESET_FMT "|" UI_GREEN_FMT_STR "'" UI_RESET_FMT
                                           "__" UI_GREEN_FMT_STR "'\"|" UI_RESET_FMT "___" UI_GREEN_FMT_STR
                                           "'\"'" UI_RESET_FMT "_" UI_GREEN_FMT_STR "\"|'" UI_RESET_FMT
                                           "__|" UI_GREEN_FMT_STR ",,." UI_RESET_FMT);
  wid_dead_window->log_empty_line(g);

  auto p = wid_dead_window->wid_text_area->wid_text_area;
  auto w = wid_new_square_button(g, p, "dead");

  {
    spoint tl2(9, h - 7);
    spoint br2(width - 11, h - 5);

    wid_set_pos(w, tl2, br2);

    wid_set_style(w, UI_WID_STYLE_RED);
    wid_set_on_mouse_up(g, w, wid_dead_mouse_up);
    wid_set_text(w, "Continue");
  }

  wid_update(g, wid_dead_window->wid_text_area->wid_text_area);
}
