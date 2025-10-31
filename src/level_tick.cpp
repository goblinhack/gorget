//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_game_popups.hpp"
// REMOVED #include "my_gl.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_wids.hpp"

static void level_tick_begin(Gamep, Levelsp, Levelp);
static void level_tick_body(Gamep, Levelsp, Levelp, float dt);
static void level_tick_end(Gamep, Levelsp, Levelp);
static void level_tick_idle(Gamep, Levelsp, Levelp);
static void level_tick_time_step(Gamep, Levelsp, Levelp);

//
// Called at the end of the tick and then whenever needed, like at the end of an animation.
//
static void level_cleanup_things(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  if (! game_request_to_cleanup_things_get(g)) {
    return;
  }
  game_request_to_cleanup_things_unset(g);

  //
  // This can pop the next player move
  //
  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t)
  {
    if (thing_is_scheduled_for_cleanup(t)) {
      thing_fini(g, v, l, t);
    }
  }
}

//
// Check if it is ok to end the tick
// e.g. something fell in lava and now needs to delay the end of the tick whilst its animation finishes
//
static void level_tick_ok_to_end_check(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  v->tick_wait_on_things = false;
  v->tick_wait_on_anim   = false;

  //
  // The player has died and the dead menu has been closed
  //
  if (game_request_to_end_game_get(g)) {
    v->tick_end_requested = true;
    return;
  }

  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t)
  {
    //
    // We need to wait for things to complete moving into lava for example before we can
    // run temperature checks. Else it looks odd that it catches fire before it reaches
    // the lava.
    //
    if (thing_is_moving(t) || thing_is_jumping(t) || thing_is_falling(t)) {
      v->tick_wait_on_things = true;
    }

    //
    // Some things like explosions, we want to wait for the explosion to finish before
    // moving to the next tick. Except it adds delays and is currently disabled.
    //
    if (g_opt_tests) {
      if (thing_is_dead(t)) {
        if (! thing_is_scheduled_for_cleanup(t)) {
          if (thing_is_wait_on_dead_anim(t)) {
            v->tick_wait_on_anim = true;
          }
        }
      }
    }
  }
}

//
// Called per frame
//
void level_tick(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  verify(MTYPE_LEVELS, game_levels_get(g));

  v->last_time_step = v->time_step;

  //
  // First time tick for this level?
  //
  if (! l->is_active_level) {
    l->is_active_level = true;

    //
    // First lighting update
    //
    level_light_fov_all(g, v, l);

    //
    // Update minimaps
    //
    level_minimaps_update(g, v, l);
  }

  if (v->tick_in_progress) {
    //
    // A tick is running
    //
    level_tick_time_step(g, v, l);

    //
    // Need to update while moving as raycasting can change
    //
    level_light_fov_all(g, v, l);
  } else if (v->tick_begin_requested) {
    //
    // Allow temperatures to settle prior to starting
    //
    level_tick_begin_temperature(g, v, l);

    //
    // Start the tick
    //
    level_tick_begin(g, v, l);
  } else {
    //
    // Idle state
    //
    level_tick_idle(g, v, l);
  }

  //
  // Update any tiles that are needed
  //
  level_tile_update(g, v, l);

  //
  // Move things. Interpolated per frame.
  //
  if (v->tick_in_progress) {
    level_tick_body(g, v, l, v->time_step - v->last_time_step);
  }

  //
  // Animate things Per frame.
  //
  level_anim(g, v, l);

  //
  // Check if something fell in lava and now needs to delay the end of the tick
  //
  level_tick_ok_to_end_check(g, v, l);

  //
  // If things are no longer moving and we have requested the end of the tick, then we can check
  // for temperature interactions.
  //
  if (v->tick_end_requested && (v->tick != v->tick_temperature) && ! v->tick_wait_on_things) {
    //
    // Only do this once per tick
    //
    v->tick_temperature = v->tick;

    //
    // Need to do the temperature checks after things have moved an also need to give time for death
    // animations to end
    //
    level_tick_end_temperature(g, v, l);

    do {
      l->is_tick_delay_on_spawn = false;

      //
      // Handle things interacting with explosions
      //
      level_tick_explosion(g, v, l);

      //
      // Handle things interacting with water
      //
      level_tick_water(g, v, l);

      //
      // Handle things interacting with teleports
      //
      level_tick_teleport(g, v, l);

      //
      // Handle things interacting with chasms
      //
      level_tick_chasm(g, v, l);

      //
      // Check if something reacted with lava and is now needing to delay the end of tick
      //
      level_tick_ok_to_end_check(g, v, l);

      //
      // A chasm or explosion or some other event has occurred that we need to handle immediately
      // and delay ending the tick
      //
    } while (l->is_tick_delay_on_spawn);
  }

  //
  // Are we done with all checks and ok to end the tick which will trigger thing cleanup.
  //
  if (v->tick_end_requested && ! v->tick_wait_on_things && ! v->tick_wait_on_anim) {
    level_tick_end(g, v, l);

    //
    // Final lighting update now we've stopped moving
    //
    level_light_fov_all(g, v, l);

    //
    // Update minimaps
    //
    level_minimaps_update(g, v, l);
  }

  //
  // Remove things scheduled for cleanup
  //
  level_cleanup_things(g, v, l);

  //
  // Remove old popups
  //
  game_popups_age(g);
}

static void level_tick_time_step(Gamep g, Levelsp v, Levelp l)
{
  if (! v->frame_begin) {
    //
    // First tick
    //
    v->frame_begin = v->frame;
    v->time_step   = 0.0;
  } else {
    //
    // Continue the tick
    //
    v->time_step = ((float) (v->frame - v->frame_begin)) / (float) TICK_DURATION_MS;
    if (v->time_step >= 1.0) {
      //
      // Tick has surpassed its time
      //
      v->time_step = 1.0;

      if (! v->tick_end_requested) {
        LOG("Tick %u end requested", v->tick);
      }

      v->tick_end_requested = true;
    }
  }
}

static void level_tick_body(Gamep g, Levelsp v, Levelp l, float dt)
{
  TRACE_NO_INDENT();

  auto p = thing_player(g);
  if (! p) {
    return;
  }

  const int player_speed = thing_speed(p);

  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t)
  {
    //                   Tick 1              Tick 2
    //            =================== ===================
    //            0.00 0.25 0.50 1.00 0.00 0.25 0.50 1.00
    // --------------------------------------------------------
    // speed 400  tick tick tick tick tick tick tick tick
    // speed 200  tick      tick      tick      tick
    // speed 100  tick           tick
    // speed 50   tick
    //
    if (! thing_is_moving(t) && ! thing_is_jumping(t)) {
      continue;
    }

    float t_speed = thing_speed(t);

    t->thing_dt += dt * (t_speed / (float) player_speed);

    if (t->thing_dt >= 1.0) {
      t->thing_dt = 1.0;
    }

    if (0) {
      if (thing_is_player(t)) {
        THING_LOG(t, "dt %f thing_dt %f speed %d v %d", dt, t->thing_dt, thing_speed(t), player_speed);
      }
    }

    thing_interpolate(g, t, t->thing_dt);

    //
    // If the thing tick has completed, finish its move.
    //
    if (t->thing_dt >= 0.99) { // dt increments can end up very close to 1
      t->thing_dt = 0.0;
      thing_move_or_jump_finish(g, v, l, t);

      //
      // Handle interactions for a thing at its new location
      //
      thing_collision_handle(g, v, l, t);
    }
  }
}

static void level_tick_begin(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  v->tick++;
  LOG("Tick %u begin", v->tick);

  v->tick_begin_requested = false;
  v->frame_begin          = v->frame;
  v->time_step            = 0.0;
  v->tick_in_progress     = true;

  auto p = thing_player(g);
  if (! p) {
    return;
  }

  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t)
  {
    if (thing_is_tickable(t)) {
      thing_tick_begin(g, v, l, t);
    }
  }
}

static void level_tick_idle(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  auto p = thing_player(g);
  if (! p) {
    TOPCON("noplayer");
    return;
  }

  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t)
  {
    if (thing_is_tickable(t)) {
      thing_tick_idle(g, v, l, t);
    }
  }
}

void level_tick_begin_requested(Gamep g, Levelsp v, Levelp l, const char *why)
{
  TRACE_NO_INDENT();

  LOG("Tick requested: %s", why);

  v->tick_begin_requested = true;

  v->requested_move_up    = false;
  v->requested_move_left  = false;
  v->requested_move_keft  = false;
  v->requested_move_right = false;
}

static void level_tick_end(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  LOG("Tick %u ending", v->tick);

  v->tick_end_requested = false;
  v->tick_in_progress   = false;
  v->time_step          = 0;

  auto p = thing_player(g);
  if (! p) {
    return;
  }

  //
  // Only save once a tick is complete and before the next move is popped below
  //
  if (game_request_to_save_game_get(g)) {
    game_request_to_save_game_unset(g);
    wid_save_select(g);
  }

  //
  // This can pop the next player move
  //
  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t)
  {
    if (thing_is_tickable(t)) {
      thing_tick_end(g, v, l, t);
    }
  }

  LOG("Tick %u end", v->tick);
  LOG("-");
}

bool level_tick_is_in_progress(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  return v->tick_in_progress;
}
