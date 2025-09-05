//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"

void thing_water_handle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto   p = t->at;
  Thingp source;
  if (level_is_deep_water(g, v, l, p)) {
    source = level_first_is_deep_water(g, v, l, p);
  } else {
    source = level_first_is_water(g, v, l, p);
  }

  auto event_type = THING_EVENT_WATER_DAMAGE;
  auto damage     = tp_damage(thing_tp(source), event_type);

  ThingEvent e {
      .reason     = "by water damage", //
      .event_type = event_type,        //
      .damage     = damage,            //
      .source     = source,            //
  };

  thing_damage(g, v, l, t, e);
}
