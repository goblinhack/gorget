//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tp_callbacks.hpp"

//
// Called at the beginning of each tick
//
void thing_tick_begin(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // Per thing callback
  //
  tp_on_tick_begin(g, v, l, t);

  //
  // Lifespan tick
  //
  if (thing_lifespan(t)) {
    if (! thing_lifespan_decr(g, v, l, t)) {
      ThingEvent e {
          .reason     = "ran out of life",            //
          .event_type = THING_EVENT_LIFESPAN_EXPIRED, //
      };
      thing_dead(g, v, l, t, e);
    }
  }

  thing_age_incr(g, v, l, t);

  thing_continue_to_burn_check(g, v, l, t);
}

//
// Called when the level is idle. i.e. multiple times per tick
//
void thing_tick_idle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // Per thing callback
  //
  tp_on_tick_idle(g, v, l, t);
}

//
// Called at the end of each tick
//
void thing_tick_end(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // Per thing callback
  //
  tp_on_tick_end(g, v, l, t);

  //
  // Mark the tick as completed
  //
  if (t->tick == v->tick) {
    return;
  }
  t->tick = v->tick;
}
