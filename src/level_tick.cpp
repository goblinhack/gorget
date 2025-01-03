//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_minimal.hpp"

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tp.hpp"

static void level_tick_begin(Levelp);
static void level_tick_body(Levelp, float dt);
static void level_tick_end(Levelp);
static void level_tick_idle(Levelp);
static void level_tick_time_step(Levelp);

void level_tick(Levelp l)
{
  TRACE_NO_INDENT();

  l->last_time_step = l->time_step;
  if (l->tick_in_progress) {
    //
    // A tick is running
    //
    level_tick_time_step(l);
  } else if (l->tick_begin_requested) {
    //
    // Start the tick
    //
    level_tick_begin(l);
  } else {
    //
    // Idle state
    //
    level_tick_idle(l);
  }

  //
  // Move things
  //
  if (l->tick_in_progress) {
    level_tick_body(l, l->time_step - l->last_time_step);
  }

  //
  // End of tick?
  //
  if (l->tick_end_requested) {
    level_tick_end(l);
  }
}

static void level_tick_time_step(Levelp l)
{
  if (! l->frame_begin) {
    //
    // First tick
    //
    l->frame_begin = l->frame;
    l->time_step   = 0.0;
  } else {
    //
    // Continue the tick
    //
    l->time_step = ((float) (l->frame - l->frame_begin)) / (float) TICK_DURATION_MS;
    if (l->time_step >= 1.0) {
      //
      // Tick has surpassed its time
      //
      l->time_step          = 1.0;
      l->tick_end_requested = true;
    }
  }
}

static void level_tick_body(Levelp l, float dt)
{
  TRACE_NO_INDENT();

  auto p = thing_player(l);
  if (! p) {
    return;
  }

  int player_speed = p->speed;

  FOR_ALL_THINGS_Z_DEPTH(l, t, p->at.z)
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
    t->thing_dt += dt * ((float) t->speed / (float) player_speed);
    if (t->thing_dt >= 1.0) {
      t->thing_dt = 1.0;
    }

    thing_interpolate(l, t, t->thing_dt);

    //
    // If the thing tick has completed, finish its move.
    //
    if (t->thing_dt >= 1.0) {
      t->thing_dt = 0.0;
      thing_move_finish(l, t);
    }
  }
}

static void level_tick_begin(Levelp l)
{
  l->tick++;
  l->tick_begin_requested  = false;
  l->frame_begin           = l->frame;
  l->time_step             = 0.0;
  l->tick_in_progress      = true;
  l->requested_auto_scroll = true;

  auto p = thing_player(l);
  if (! p) {
    return;
  }

  FOR_ALL_THINGS_Z_DEPTH(l, t, p->at.z)
  {
    if (thing_is_tickable(t)) {
      thing_tick_begin(l, t);
    }
  }
}

static void level_tick_idle(Levelp l)
{
  auto p = thing_player(l);
  if (! p) {
    return;
  }

  FOR_ALL_THINGS_Z_DEPTH(l, t, p->at.z)
  {
    if (thing_is_tickable(t)) {
      thing_tick_idle(l, t);
    }
  }
}

void level_tick_begin_requested(Levelp l, const char *why)
{
  TRACE_NO_INDENT();

  l->tick_begin_requested = true;

  l->requested_move_up    = false;
  l->requested_move_left  = false;
  l->requested_move_keft  = false;
  l->requested_move_right = false;
}

static void level_tick_end(Levelp l)
{
  TRACE_NO_INDENT();

  l->tick_in_progress   = false;
  l->tick_end_requested = false;
  l->time_step          = 0;

  auto p = thing_player(l);
  if (! p) {
    return;
  }

  FOR_ALL_THINGS_Z_DEPTH(l, t, p->at.z)
  {
    if (thing_is_tickable(t)) {
      thing_tick_end(l, t);
    }
  }
}

bool level_tick_is_in_progress(Levelp l)
{
  TRACE_NO_INDENT();

  return l->tick_in_progress;
}
