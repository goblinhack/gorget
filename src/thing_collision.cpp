//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_minimal.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

#include <string.h>

//
// Handle interactions for a thing at its location
//
void thing_collision_handle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (thing_is_player(t)) {
    thing_player_collision_handle(g, v, l, t);
  }

  //
  // Common collision handling for player and anything else
  //
  FOR_ALL_THINGS_AND_TPS_AT(g, v, l, it, it_tp, t->at)
  {
    //
    // TODO
    //
  }
}
