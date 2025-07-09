//
// Copyright goblinhack@gmail.com
//

#include "my_types.hpp"

#include "my_callstack.hpp"
#include "my_dice.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tp.hpp"

static void thing_temperature_damage_handle(Gamep g, Levelsp v, Levelp l, Thingp source, Thingp me, int n)
{
  TRACE_NO_INDENT();

  auto damage = n;
  if (damage > 20) {
    damage = 20;
  }

  ThingEvent e {
      .reason     = "by heat damage", //
      .event_type = THING_EVENT_HEAT, //
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
