//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_string.hpp"
#include "my_ui.hpp"
#include "my_wids.hpp"

//
// Do actions upon burning
//
void thing_is_burning_handle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (thing_is_burning(t)) {
    if (thing_is_player(t)) {
      TOPCON(UI_IMPORTANT_FMT_STR "You are burning!" UI_RESET_FMT);
    }
  }
}

void thing_continue_to_burn_check(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto tp = thing_tp(t);

  if (! thing_is_burning(t)) {
    return;
  }

  //
  // Over water?
  //
  if (level_is_water(g, v, l, t->at)) {
    thing_is_burning_unset(g, v, l, t);

    if (thing_is_player(t)) {
      TOPCON(UI_GOOD_FMT_STR "You extinguish the flames!" UI_RESET_FMT);
    }

    if (! level_is_steam(g, v, l, t->at)) {
      thing_spawn(g, v, l, tp_random(is_steam), t->at);
    }
    return;
  }

  //
  // Good luck
  //
  if (tp_chance_success(tp, THING_CHANCE_CONTINUE_TO_BURN)) {
    //
    // Poor thing
    //
    thing_is_burning_unset(g, v, l, t);

    if (thing_is_player(t)) {
      TOPCON(UI_GOOD_FMT_STR "You stop burning!" UI_RESET_FMT);
    }
    return;
  }

  //
  // Bad luck
  //
  if (tp_chance_fail(tp, THING_CHANCE_CONTINUE_TO_BURN)) {
    //
    // Spawn more flames?
    //
    if (thing_is_combustible(t)) {
      if (level_count_is_fire(g, v, l, t->at) < 2) {
        THING_LOG(t, "spawn additional flames");
        thing_spawn(g, v, l, tp_random(is_fire), t->at);

        if (thing_is_player(t)) {
          TOPCON(UI_IMPORTANT_FMT_STR "The flames intensify!" UI_RESET_FMT);
        }
      }
    }

    //
    // Don't let the fire age out.
    //
    auto f = level_first_is_fire(g, v, l, t->at);
    if (f) {
      THING_DBG(t, "keep the fire burning");
      thing_lifespan_incr(g, v, l, f, 2);
    }
  }

  //
  // Continue to burn
  //
  if (! level_is_fire(g, v, l, t->at)) {
    THING_LOG(t, "spawn flames");
    thing_spawn(g, v, l, tp_random(is_fire), t->at);
  }

  if (! level_is_smoke(g, v, l, t->at)) {
    THING_LOG(t, "spawn smoke");
    thing_spawn(g, v, l, tp_random(is_smoke), t->at);
  }
}
