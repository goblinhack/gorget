//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_hiscore.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_string.hpp"
#include "my_wids.hpp"

static WidPopup *wid_hiscore_window;

static void wid_hiscore_destroy(Gamep g)
{
  TRACE_NO_INDENT();
  delete wid_hiscore_window;
  wid_hiscore_window = nullptr;
  wid_main_menu_select(g);
}

static bool wid_hiscore_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
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
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE :
                {
                  TRACE_NO_INDENT();
                  sound_play(g, "keypress");
                  wid_hiscore_destroy(g);
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

static bool wid_hiscore_mouse_up(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_hiscore_destroy(g);
  return true;
}

void wid_hiscores_show(Gamep g)
{
  TRACE_NO_INDENT();

  if (wid_hiscore_window) {
    wid_hiscore_destroy(g);
  }

  int menu_height = 26;
  int menu_width  = 100;

  auto name           = "Name";
  int  name_field_len = UI_MAX_PLAYER_NAME_LEN + 1;

  auto when           = "Date of Demise";
  int  when_field_len = 25;

  auto completed           = "Completed";
  int  completed_field_len = 9;

  auto reason           = "Reason of Unfair Demise";
  int  reason_field_len = 28;

  spoint outer_tl(TERM_WIDTH / 2 - (menu_width / 2), TERM_HEIGHT / 2 - (menu_height / 2));
  spoint outer_br(TERM_WIDTH / 2 + (menu_width / 2), TERM_HEIGHT / 2 + (menu_height / 2));
  wid_hiscore_window = new WidPopup(g, "hiscores", outer_tl, outer_br, nullptr, "", false, false);

  {
    TRACE_NO_INDENT();
    Widp w = wid_hiscore_window->wid_popup_container;
    wid_set_on_key_down(g, w, wid_hiscore_key_down);
  }

  auto hiscores = game_hiscores_get(g);
  auto h        = hiscores->hiscores.begin();
  bool first    = true;
  auto index    = 0;

  const char *colors[ HiScore::max_displayed ] = {
      "green", "yellow", "yellow", "yellow", "gray50", "gray50", "gray60", "gray60", "gray70", "gray70",
  };

  while (h != hiscores->hiscores.end()) {

    if (index >= (int) ARRAY_SIZE(colors)) {
      break;
    }

    char tmp[ 200 ];

    if (first) {
      first = false;

      auto color = "red";

      snprintf(tmp, SIZEOF(tmp) - 1, "%%%%fg=%s$%7s %-*s %-*s %-*s %*s", //
               color, "Score",                                           //
               name_field_len, capitalize(name).c_str(),                 //
               when_field_len, when,                                     //
               completed_field_len, completed,                           //
               reason_field_len, reason);

      wid_hiscore_window->log(g, tmp);
    }

    std::string when_val = h->when.c_str();
    if ((int) when_val.length() > when_field_len) {
      when_val[ when_field_len ] = '\0';
    }

    if (when_val == "") {
      when_val = "-";
    }

    std::string reason_val = capitalize_first(h->reason).c_str();
    if ((int) reason_val.length() > reason_field_len) {
      reason_val[ reason_field_len ] = '\0';
    }

    if (reason_val == "") {
      reason_val = "-";
    }

    auto color = colors[ index++ ];
    snprintf(tmp, SIZEOF(tmp) - 1, "%%%%fg=%s$%07u %-*s %-*s %-*u %*s", //
             color, h->score,                                           //
             name_field_len, h->name.c_str(),                           //
             when_field_len, when_val.c_str(),                          //
             completed_field_len, h->levels_completed,                  //
             reason_field_len, reason_val.c_str());

    wid_hiscore_window->log_empty_line(g);
    wid_hiscore_window->log(g, tmp);
    h++;
  }

  {
    TRACE_NO_INDENT();
    auto p = wid_hiscore_window->wid_text_area->wid_text_area;
    auto w = wid_back_button(g, p, "hiscore");

    spoint tl(menu_width / 2 - 4, menu_height - 4);
    spoint br(menu_width / 2 + 3, menu_height - 2);

    wid_set_on_mouse_up(g, w, wid_hiscore_mouse_up);
    wid_set_pos(w, tl, br);
  }

  wid_update(g, wid_hiscore_window->wid_text_area->wid_text_area);
}
