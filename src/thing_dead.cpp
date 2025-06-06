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

//
// The poor thing is dead
//
void thing_dead(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp maybe_killer, const char *reason)
{
  TRACE_NO_INDENT();

  if (thing_is_dead(me)) {
    return;
  }
  thing_is_dead_set(me);

  if (reason) {
    THING_LOG(me, "dead, reason: %s", reason);
  } else {
    THING_LOG(me, "dead");
  }

  //
  // Stop it moving
  //
  thing_move_finish(g, v, l, me);
}
