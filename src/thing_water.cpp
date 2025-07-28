//
// Copyright goblinhack@gmail.com
//

// REMOVED #include "my_types.hpp"

#include "my_callstack.hpp"
// REMOVED #include "my_dice.hpp"
// REMOVED #include "my_game.hpp"
#include "my_level.hpp"
// REMOVED #include "my_main.hpp"
// REMOVED #include "my_tp.hpp"

void thing_water_handle(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();

  auto   p = me->at;
  Thingp source;
  if (level_is_deep_water(g, v, l, p)) {
    source = level_first_deep_water(g, v, l, p);
  } else {
    source = level_first_water(g, v, l, p);
  }

  auto event_type = THING_EVENT_WATER_DAMAGE;
  auto damage     = tp_damage(thing_tp(source), event_type);

  //
  // Give the thing a chance and don't kill it immediately
  //
  auto max_damage = thing_health(me) / 2;

  if (max_damage < 1) {
    max_damage = 1;
  }

  if (damage > max_damage) {
    damage = max_damage;
  }

  ThingEvent e {
      .reason     = "by water damage", //
      .event_type = event_type,        //
      .damage     = damage,            //
      .source     = source,            //
  };

  thing_damage(g, v, l, me, e);
}
