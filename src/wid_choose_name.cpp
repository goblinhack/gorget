//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_string.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_keyboard.hpp"
#include "my_wids.hpp"

static Widp wid_choose_player_name;

static void selected(Gamep g, Widp w, const std::string &text)
{
  TRACE_NO_INDENT();

  wid_destroy(g, &wid_choose_player_name);
  game_player_name_set(g, text.c_str());
  CON("Save config");
  game_save_config(g);
  wid_main_menu_select(g);
}

static void cancelled(Gamep g, Widp w, const std::string &text)
{
  TRACE_NO_INDENT();

  wid_destroy(g, &wid_choose_player_name);
  wid_main_menu_select(g);
}

void wid_player_name_select(Gamep g)
{
  TRACE_AND_INDENT();

  CON("Choose player name menu");

  const char *player_name = game_player_name_get(g);
  wid_choose_player_name
      = wid_keyboard(g, std::string(player_name),
                     "Enter a name for the player, max " + std::to_string(UI_MAX_PLAYER_NAME_LEN) + " characters",
                     selected, cancelled, UI_MAX_PLAYER_NAME_LEN);
}
