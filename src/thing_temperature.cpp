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
      .reason      = "by heat damage",  //
      .damage_type = THING_DAMAGE_HEAT, //
      .damage      = damage,            //
      .source      = source,            //
  };
  thing_damage(g, v, l, me, e);
}

void thing_temperature_handle(Gamep g, Levelsp v, Levelp l, Thingp source, Thingp me, int n)
{
  TRACE_NO_INDENT();

  auto tp = thing_tp(me);

  if (n > tp_temperature_damage_at_get(tp)) {
    thing_temperature_damage_handle(g, v, l, source, me, n);
  }

  if (n > tp_temperature_burns_at_get(tp)) {
    // TODO damage
  }

  thing_temperature_set(g, v, l, me, n);
}
