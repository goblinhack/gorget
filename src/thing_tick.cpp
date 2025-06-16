//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_minimal.hpp"
#include "my_random.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

#include <cinttypes>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <string.h>
#include <string>

//
// Called at the beginning of each tick
//
void thing_tick_begin(Gamep g, Levelsp v, Levelp l, Thingp t) { TRACE_NO_INDENT(); }

//
// Called when the level is idle
//
void thing_tick_idle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // If asked to follow the mouse path, start walking
  //
  if (thing_is_player(t)) {
    thing_move_to_next(g, v, l, t);
  }
}

//
// Called at the end of each tick
//
void thing_tick_end(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // Mark the tick as completed
  //
  if (t->tick == v->tick) {
    return;
  }
  t->tick = v->tick;

  //
  // If following the mouse path, keep going
  //
  if (thing_is_player(t)) {
    thing_move_to_next(g, v, l, t);
  }
}
