//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_string.hpp"
#include "my_ui.hpp"
#include "my_wid_popup.hpp"

static WidPopup *wid_hiscore_window;

static void wid_hiscore_destroy(void)
{
  TRACE_AND_INDENT();
  delete wid_hiscore_window;
  wid_hiscore_window = nullptr;
  game->wid_main_menu_select();
}

static bool wid_hiscore_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
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
              case '\n' :
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE :
                {
                  TRACE_AND_INDENT();
                  wid_hiscore_destroy();
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

static bool wid_hiscore_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

static bool wid_hiscore_mouse_up(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_hiscore_destroy();
  return true;
}

void Game::wid_hiscores_show(void)
{
  TRACE_AND_INDENT();
  if (wid_hiscore_window) {
    wid_hiscore_destroy();
  }

  int   menu_height  = 26;
  int   menu_width   = UI_WID_POPUP_WIDTH_NORMAL * 2;
  point tl           = make_point(TERM_WIDTH / 2 - (menu_width / 2), TERM_HEIGHT / 2 - (menu_height / 2));
  point br           = make_point(TERM_WIDTH / 2 + (menu_width / 2), TERM_HEIGHT / 2 + (menu_height / 2));
  wid_hiscore_window = new WidPopup("hiscores", tl, br, nullptr, "", false, false);

  {
    TRACE_AND_INDENT();
    Widp w = wid_hiscore_window->wid_popup_container;
    wid_set_on_key_up(w, wid_hiscore_key_up);
    wid_set_on_key_down(w, wid_hiscore_key_down);
  }

  auto h     = game->config.hiscores.hiscores.begin();
  bool first = true;
  auto index = 0;

  const char *colors[ HiScore::max_displayed ] = {
      "green", "yellow", "yellow", "yellow", "gold", "gold", "gold", "white", "white", "white",
  };

  while (h != game->config.hiscores.hiscores.end()) {

    if (index >= (int) ARRAY_SIZE(colors)) {
      break;
    }

    char tmp[ 200 ];

    int name_field_len = 8;
    int when_field_len = 10;

    if (first) {
      first = false;

      auto color = "red";
      auto name  = "Name";
      auto when  = "When";

      snprintf(tmp, sizeof(tmp) - 1, "%%%%fg=%s$%7s  %-*s %-*s %-5s", color, "Score", name_field_len,
               capitalise(name).c_str(), when_field_len, when, "Lvl");

      wid_hiscore_window->log(tmp);
    }

    std::string name = h->name.c_str();
    if ((int) name.length() > name_field_len) {
      name[ name_field_len ] = '\0';
    }

    std::string when = h->when.c_str();
    if ((int) when.length() > when_field_len) {
      when[ when_field_len ] = '\0';
    }

    auto color = colors[ index++ ];
    snprintf(tmp, sizeof(tmp) - 1, "%%%%fg=%s$%07u  %-*s %-*s %-5u", color, h->score, name_field_len, name.c_str(),
             when_field_len, when.c_str(), h->level_reached);

    wid_hiscore_window->log(UI_LOGGING_EMPTY_LINE);
    wid_hiscore_window->log(tmp);
    h++;
  }

  {
    TRACE_AND_INDENT();
    auto p = wid_hiscore_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "hiscore");

    point tl = make_point(menu_width / 2 - 4, menu_height - 4);
    point br = make_point(menu_width / 2 + 3, menu_height - 2);

    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(w, wid_hiscore_mouse_up);

    wid_set_pos(w, tl, br);
    wid_set_text(w, "BACK");
  }

  wid_update(wid_hiscore_window->wid_text_area->wid_text_area);
}
