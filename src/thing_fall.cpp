//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_dice_rolls.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_ui.hpp"

//
// Ok to land on this spot?
//
static bool thing_ok_landing_spot(Gamep g, Levelsp v, Levelp l, Thingp t, spoint p)
{
  TRACE_NO_INDENT();

  if (is_oob(p)) {
    return false;
  }

  if (level_is_obs_to_falling_onto(g, v, l, p)) {
    return false;
  }

  return true;
}

//
// Try to find a spot clost to where we landed that is ok to exist in.
// i.e. no landing inside walls.
//
static spoint thing_choose_landing_spot(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  spoint p    = t->at;
  int    dist = 1;

  for (;;) {
    if (thing_ok_landing_spot(g, v, l, t, p)) {
      return p;
    }

    for (auto dx = -dist; dx <= dist; dx++) {
      for (auto dy = -dist; dy <= dist; dy++) {
        p.x = t->at.x + dx;
        p.y = t->at.y + dy;

        if (thing_ok_landing_spot(g, v, l, t, p)) {
          return p;
        }
      }
    }

    dist++;
  }

  return t->at;
}

//
// How much damage does the thing take on falling.
//
static int thing_fall_damage(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  int fall_dmg = 0;

  if (thing_is_player(t)) {
    fall_dmg = pcg_random_range(6, 30);
  } else if (thing_is_mob(t) || thing_is_monst(t)) {
    fall_dmg = pcg_random_range(6, thing_health(t) / 2);
  } else {
    fall_dmg = d4();
  }

  //
  // Landing in lava is bad
  //
  if (level_is_lava(g, v, l, t->at)) {
    if (! thing_is_immune_to(t, THING_EVENT_HEAT_DAMAGE)) {
      fall_dmg *= 4;
    }
  }

  //
  // Water dampens the fall
  //
  if (level_is_water(g, v, l, t->at)) {
    if (thing_is_immune_to(t, THING_EVENT_WATER_DAMAGE)) {
      fall_dmg /= 2;
    }
  }

  //
  // Deep water dampens it further
  //
  if (level_is_deep_water(g, v, l, t->at)) {
    if (thing_is_immune_to(t, THING_EVENT_WATER_DAMAGE)) {
      fall_dmg /= 2;
    }
  }

  //
  // Amplify or nullify due to weight
  //
  auto w = thing_weight(t);
  if (w <= WEIGHT_FEATHER) {
    fall_dmg = 0;
  } else if (w >= WEIGHT_HEAVY) {
    fall_dmg *= 2;
  }

  return fall_dmg;
}

//
// Complete the fall to the next level. If this is the player we also change level.
//
static void thing_fall_end(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto next_level = level_select_get_next_level_down(g, v, l);
  if (! next_level) {
    return;
  }

  //
  // Choose a new landing spot for the thing
  //
  auto new_location = thing_choose_landing_spot(g, v, next_level, t);

  //
  // Move the thing there
  //
  thing_warp_to(g, v, next_level, t, new_location);

  if (thing_is_player(t)) {
    level_scroll_warp_to_focus(g, v, l);
  }

  ThingEvent e {
      .reason     = "by falling",                  //
      .event_type = THING_EVENT_FALL,              //
      .damage     = thing_fall_damage(g, v, l, t), //
  };

  //
  // "You tumble into the vuid"
  //
  if (thing_is_player(t)) {
    player_fell(g, v, l, next_level, t);
  }

  //
  // "You take n damage from falling"
  //
  thing_damage(g, v, l, t, e);

  //
  // Falling can be good
  //
  if (thing_is_burning(t)) {
    thing_is_burning_unset(g, v, l, t);
    if (thing_is_player(t)) {
      TOPCON(UI_GOOD_FMT_STR "You extinguish the flames as you fall!" UI_RESET_FMT);
    }
  }
}

//
// Falling time step
//
void thing_fall_time_step(Gamep g, Levelsp v, Levelp l, Thingp t, int time_step)
{
  TRACE_NO_INDENT();

  if (thing_is_falling_incr(g, v, l, t, time_step) > MAX_FALL_TIME_MS) {
    thing_fall_end(g, v, l, t);
    thing_is_falling_set(g, v, l, t, false);
  }
}

//
// Begin falling
//
void thing_fall(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // Fall at the end of the move, or it just looks odd with things falling
  // through the floor before they get to the chasm
  //
  if (thing_is_moving(t)) {
    return;
  }

  if (! thing_is_able_to_fall(t)) {
    return;
  }

  thing_is_falling_set(g, v, l, t, true);

  if (! level_is_chasm(g, v, l, t->at)) {
    thing_spawn(g, v, l, tp_random(is_chasm), t->at);
  }
}
