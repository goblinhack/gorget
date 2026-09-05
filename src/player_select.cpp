//
// Copyright goblinhack@gmail.com
//

#include "my_bpoint.hpp"
#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_game.hpp"
#include "my_game_defs.hpp"
#include "my_game_inlines.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_sound.hpp"
#include "my_thing.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"
#include "my_wids.hpp"

#include <cmath>
#include <cstdint>
#include <cstring>
#include <string>

//
// If in player select mode, enter the chosen level
//
auto player_select_mouse_down(Gamep g) -> bool
{
  TRACE();

  auto *v = game_levels_get(g);
  if (v == nullptr) [[unlikely]] {
    (void) sound_play(g, "error");
    return false;
  }

  Levelp l = thing_player_level(g);
  if (l == nullptr) [[unlikely]] {
    (void) sound_play(g, "error");
    return false;
  }

  topcon("TODO");

  return true;
}

//
// If in player select mode, enter the chosen level
//
auto player_select_mouse_down(Gamep g, Levelsp v, Levelp l) -> bool
{
  TRACE();

  if (! level_is_player_select(g, v, l)) {
    (void) sound_play(g, "error");
    return false;
  }

  topcon("TODO");

  return true;
}
