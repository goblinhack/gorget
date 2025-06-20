//
// Copyright goblinhack@gmail.com
//

#include "my_minimal.hpp"

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tp.hpp"

void thing_temperature_handle(Gamep g, Levelsp v, Levelp l, Thingp it, Thingp me, int n)
{
  TRACE_NO_INDENT();

  auto tp = thing_tp(me);

  if (n > tp_temperature_damage_at_get(tp)) {
    // TODO damage
    thing_dead(g, v, l, it, me, "by burning");
  }

  if (n > tp_temperature_burns_at_get(tp)) {
    // TODO damage
  }

  thing_temperature_set(g, v, l, me, n);
}

