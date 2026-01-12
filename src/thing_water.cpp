//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
// REMOVED #include "my_level.hpp"
#include "my_thing_inlines.hpp"

void thing_water_handle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto   at = thing_at(t);
  Thingp source;
  if (level_is_deep_water(g, v, l, at)) {
    source = level_is_deep_water(g, v, l, at);
  } else {
    source = level_is_water(g, v, l, at);
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
