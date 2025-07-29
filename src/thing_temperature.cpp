//
// Copyright goblinhack@gmail.com
//


#include "my_callstack.hpp"
#include "my_level.hpp"

static void thing_temperature_damage_handle(Gamep g, Levelsp v, Levelp l, Thingp source, Thingp me, int n)
{
  TRACE_NO_INDENT();

  auto event_type = THING_EVENT_HEAT_DAMAGE;
  auto damage     = n;
  auto max_damage = 0;

  if (source) {
    //
    // Limit damage to the type of thing, e.g. lava/fire
    //
    max_damage = tp_damage(thing_tp(source), event_type);
  } else {
    //
    // Give the thing a chance and don't kill it immediately
    //
    max_damage = thing_health(me) / 2;
  }

  if (max_damage < 1) {
    max_damage = 1;
  }

  if (damage > max_damage) {
    damage = max_damage;
  }

  ThingEvent e {
      .reason     = "by heat damage", //
      .event_type = event_type,       //
      .damage     = damage,           //
      .source     = source,           //
  };

  thing_damage(g, v, l, me, e);
}

void thing_temperature_handle(Gamep g, Levelsp v, Levelp l, Thingp source, Thingp me, int n)
{
  TRACE_NO_INDENT();

  auto tp = thing_tp(me);

  //
  // Pre burning heat damage
  //
  auto t1 = tp_temperature_damage_at_get(tp);
  if (t1 && (n > t1)) {
    thing_temperature_damage_handle(g, v, l, source, me, n);
    if (thing_is_dead(me)) {
      return;
    }
  }

  //
  // If not burnt already, burn it if over the threshold temperature.
  //
  auto t2 = tp_temperature_burns_at_get(tp);
  if (t2 && (n > t2)) {
    if (! level_is_fire(g, v, l, me->at)) {
      thing_spawn(g, v, l, tp_random(is_fire), me->at);
    }
    thing_is_burnt_set(g, v, l, me);
  }

  thing_temperature_set(g, v, l, me, n);
}
