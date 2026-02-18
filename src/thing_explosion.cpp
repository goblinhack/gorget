//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_inlines.hpp"

void thing_explosion_handle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (thing_is_ethereal(t)) {
    return;
  }

  auto at         = thing_at(t);
  auto *source     = level_is_explosion(g, v, l, at);
  auto event_type = THING_EVENT_EXPLOSION_DAMAGE;
  auto damage     = tp_damage(thing_tp(source), event_type);

  ThingEvent e {
      .reason     = "by explosion damage", //
      .event_type = event_type,            //
      .damage     = damage,                //
      .source     = source,                //
  };

  thing_damage(g, v, l, t, e);
}
