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

static Widp wid_choose_seed;

static void selected(Gamep g, Widp w, const std::string &text)
{
  TRACE_NO_INDENT();

  wid_destroy(g, &wid_choose_seed);
  game_seed_set(g, text.c_str());
  CON("Save config");
  game_save_config(g);
  wid_cfg_select(g);
}

static void cancelled(Gamep g, Widp w, const std::string &text)
{
  TRACE_NO_INDENT();

  wid_destroy(g, &wid_choose_seed);
  wid_cfg_select(g);
}

void wid_seed_select(Gamep g)
{
  TRACE_AND_INDENT();

  CON("Choose seed menu");

  const char *seed = game_seed_name_get(g);
  wid_choose_seed  = wid_keyboard(g, std::string(seed),
                                  "Enter a name or number for the dungeon seed, max "
                                      + std::to_string(UI_MAX_SEED_NAME_LEN) + " characters",
                                  selected, cancelled, UI_MAX_SEED_NAME_LEN);
}
