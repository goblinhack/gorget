//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_string.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_keyboard.hpp"
#include "my_wids.hpp"

static Widp wid_choose_seed;

static void selected(Gamep g, Widp w, const std::string &text)
{
  TRACE_NO_INDENT();

  wid_destroy(g, &wid_choose_seed);
  game_seed_name_set(g, text.c_str());
  game_save_config(g);
  wid_main_menu_select(g);
}

static void cancelled(Gamep g, Widp w, const std::string &text)
{
  TRACE_NO_INDENT();

  wid_destroy(g, &wid_choose_seed);
  wid_main_menu_select(g);
}

void wid_choose_seed_select(Gamep g)
{
  TRACE_AND_INDENT();

  CON("INF: Choose maybe_seed menu");

  const char *seed = game_seed_name_get(g);
  wid_choose_seed  = wid_keyboard(g, std::string(seed), "Enter a name or number for the dungeon seed", selected,
                                  cancelled, MAX_SEED_NAME_LEN);
}
