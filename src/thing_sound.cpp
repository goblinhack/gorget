//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_file.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_sound.hpp"
#include "my_thing.hpp"

bool thing_sound_play(Gamep g, Levelsp v, Levelp l, Thingp t, const std::string &alias)
{
  TRACE_NO_INDENT();

  if (g_opt_tests) {
    return false;
  }

  auto player = thing_player(g);
  if (! player) {
    return false;
  }

  float scale = 1.0;

  if (! thing_vision_can_see_tile(g, v, l, player, t->at)) {
    scale /= 5;
  }

  if (! thing_vision_player_has_seen_tile(g, v, l, t->at)) {
    scale /= 5;
  }

  if (scale <= 0) {
    return false;
  }

  return sound_play(g, alias, scale);
}
