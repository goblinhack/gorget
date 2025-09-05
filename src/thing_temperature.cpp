//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"

//
// First step is to mark things as burning and change temperatures
//
void thing_temperature_handle(Gamep g, Levelsp v, Levelp l, Thingp source, Thingp t, int n)
{
  TRACE_NO_INDENT();

  auto tp = thing_tp(t);

  //
  // If not burnt already, burn it if over the threshold temperature.
  //
  auto T = tp_temperature_burns_at_get(tp);
  if (T && (n > T)) {
    if (! level_is_fire(g, v, l, t->at)) {
      thing_spawn(g, v, l, tp_random(is_fire), t->at);
    }
    thing_is_burning_set(g, v, l, t);
  }

  thing_temperature_set(g, v, l, t, n);
}

static void thing_temperature_damage_apply(Gamep g, Levelsp v, Levelp l, Thingp source, Thingp t, int n)
{
  TRACE_NO_INDENT();

  auto event_type = THING_EVENT_HEAT_DAMAGE;
  auto damage     = n;

  ThingEvent e {
      .reason     = "by heat damage", //
      .event_type = event_type,       //
      .damage     = damage,           //
      .source     = source,           //
  };

  thing_damage(g, v, l, t, e);
}

//
// Next step is to apply burning damage
//
void thing_temperature_damage_handle(Gamep g, Levelsp v, Levelp l, Thingp source, Thingp t, int n)
{
  TRACE_NO_INDENT();

  auto tp = thing_tp(t);

  //
  // Pre burning heat damage
  //
  auto T = tp_temperature_damage_at_get(tp);
  if (T && (n > T)) {
    thing_temperature_damage_apply(g, v, l, source, t, n);
    if (thing_is_dead(t)) {
      return;
    }
  }
}
