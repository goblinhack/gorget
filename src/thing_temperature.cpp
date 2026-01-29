//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_dice_rolls.hpp"
#include "my_thing_inlines.hpp"

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
  auto Tb = tp_temperature_burns_at_get(tp);
  if (Tb && (n > Tb)) {
    if (thing_is_steam(source) || thing_is_water(source)) {
      //
      // You don't continue to burn with steam
      //
    } else if (! level_is_fire(g, v, l, t)) {
      THING_DBG(t, "set on fire");
      (void) thing_spawn(g, v, l, tp_random(is_fire), t);
      thing_is_burning_set(g, v, l, t);
    } else {
      thing_is_burning_set(g, v, l, t);
    }
  }

  //
  // If not meltt already, melt it if over the threshold temperature.
  //
  auto Tm = tp_temperature_melts_at_get(tp);
  if (Tm && (n > Tm)) {
    THING_DBG(t, "melt");
    thing_melt(g, v, l, t);
  }

  thing_temperature_set(g, v, l, t, n);
}

static void thing_temperature_damage_apply(Gamep g, Levelsp v, Levelp l, Thingp source, Thingp t, int n)
{
  TRACE_NO_INDENT();

  auto tp        = thing_tp(t);
  int  damage    = d6();
  int  damage_at = tp_temperature_damage_at_get(tp);

  if (n > damage_at * 2) {
    damage *= 2;
  }

  if (thing_is_combustible(t)) {
    damage *= 2;
  }

  if (level_is_lava(g, v, l, t)) {
    damage *= 2;
  }

  ThingEvent e {
      .reason = {},     //
      .damage = damage, //
      .source = source, //
  };

  if (thing_is_steam(source)) {
    e.event_type = THING_EVENT_HEAT_DAMAGE;
    e.reason     = "by steam";
  } else if (level_is_lava(g, v, l, t)) {
    e.event_type = THING_EVENT_FIRE_DAMAGE;
    e.reason     = "by lava";
  } else if (level_is_fire(g, v, l, t)) {
    e.event_type = THING_EVENT_FIRE_DAMAGE;
    e.reason     = "by fire";
  } else {
    e.event_type = THING_EVENT_HEAT_DAMAGE;
    e.reason     = "by heat damage";
  }

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
