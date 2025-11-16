//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_thing_callbacks.hpp"

Thingp thing_spawn(Gamep g, Levelsp v, Levelp l, Tpp tp, spoint at)
{
  TRACE_NO_INDENT();

  auto t = thing_init(g, v, l, tp, at);
  if (! t) {
    TP_ERR(tp, "failed to init thing");
    return nullptr;
  }

  if (! thing_push(g, v, l, t)) {
    THING_ERR(t, "failed to push");
    return nullptr;
  }

  THING_DBG(t, "spawned");

  //
  // This is reset each tick
  //
  if (thing_is_tick_delay_on_spawn(t)) {
    l->is_tick_delay_on_spawn = true;
  }

  //
  // Callback upon spawning
  //
  thing_on_spawn(g, v, l, t);

  return t;
}
