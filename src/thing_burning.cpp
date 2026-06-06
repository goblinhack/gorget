//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"

//
// Do actions upon burning
//
void thing_is_burning_handle(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE();

  if (thing_is_burning(me)) {
    if (thing_is_player(me)) {
      if (thing_is_immune_to(g, v, l, me, THING_EVENT_FIRE_DAMAGE)) {
        topcon(UI_IMPORTANT_FMT_STR "You are burning and bask in the flames!" UI_RESET_FMT);
      } else {
        topcon(UI_IMPORTANT_FMT_STR "You are burning!" UI_RESET_FMT);
      }
    }
  }
}

void thing_continue_to_burn_check(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE();

  auto *tp = thing_tp(me);

  if (! thing_is_burning(me)) {
    return;
  }

  //
  // Over water?
  //
  if (level_is_water(g, v, l, thing_at(me)) != nullptr) {
    thing_is_burning_unset(g, v, l, me);

    if (thing_is_player(me)) {
      topcon(UI_GOOD_FMT_STR "You extinguish the flames in the cool water!" UI_RESET_FMT);
    }

    if (level_is_steam(g, v, l, thing_at(me)) == nullptr) {
      (void) thing_spawn(g, v, l, tp_first(is_steam), me);
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
    thing_is_burning_unset(g, v, l, me);

    if (thing_is_player(me)) {
      topcon(UI_GOOD_FMT_STR "You stop burning!" UI_RESET_FMT);
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
    if (thing_is_flying(me) || thing_is_combustible(me)) {
      if (level_count_is_fire(g, v, l, thing_at(me)) < 2) {
        THING_DBG(me, "spawn additional flames");
        TRACE_INDENT();
        (void) thing_spawn(g, v, l, tp_first(is_fire), me);

        if (thing_is_player(me)) {
          topcon(UI_IMPORTANT_FMT_STR "The flames intensify!" UI_RESET_FMT);
        }
      }
    }

    //
    // Don't let the fire age out.
    //
    auto *f = level_is_fire(g, v, l, thing_at(me));
    if (f != nullptr) {
      THING_DBG(me, "keep the fire burning");
      (void) thing_lifespan_incr(g, v, l, f, 2);
    }
  }

  //
  // Continue to burn
  //
  if (level_is_fire(g, v, l, thing_at(me)) == nullptr) {
    THING_DBG(me, "spawn flames");
    (void) thing_spawn(g, v, l, tp_first(is_fire), me);
  }

  if (level_is_smoke(g, v, l, thing_at(me)) == nullptr) {
    THING_DBG(me, "spawn smoke");
    (void) thing_spawn(g, v, l, tp_first(is_smoke), me);
  }
}
