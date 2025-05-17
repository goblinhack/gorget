//
// Copyright goblinhack@gmail.com
//

#include "my_minimal.hpp"

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tp.hpp"
#include "my_wids.hpp"

static void level_tick_begin(Gamep, Levelsp, Levelp);
static void level_tick_body(Gamep, Levelsp, Levelp, float dt);
static void level_tick_end(Gamep, Levelsp, Levelp);
static void level_tick_idle(Gamep, Levelsp, Levelp);
static void level_tick_time_step(Gamep, Levelsp, Levelp);

void level_tick(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  v->last_time_step = v->time_step;
  if (v->tick_in_progress) {
    //
    // A tick is running
    //
    level_tick_time_step(g, v, l);
  } else if (v->tick_begin_requested) {
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
  // Move things
  //
  if (v->tick_in_progress) {
    level_tick_body(g, v, l, v->time_step - v->last_time_step);
  }

  //
  // End of tick?
  //
  if (v->tick_end_requested) {
    level_tick_end(g, v, l);
  }
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
      v->time_step          = 1.0;
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

  const int player_speed = p->speed;

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
    if (! t->is_moving) {
      continue;
    }

    t->thing_dt += dt * ((float) t->speed / (float) player_speed);

    if (t->thing_dt >= 1.0) {
      t->thing_dt = 1.0;
    }

    thing_interpolate(g, t, t->thing_dt);

    //
    // If the thing tick has completed, finish its move.
    //
    if (t->thing_dt >= 0.99) { // dt increments can end up very close to 1
      t->thing_dt = 0.0;
      thing_move_finish(g, v, l, t);
    }
  }
}

static void level_tick_begin(Gamep g, Levelsp v, Levelp l)
{
  v->tick++;
  v->tick_begin_requested  = false;
  v->frame_begin           = v->frame;
  v->time_step             = 0.0;
  v->tick_in_progress      = true;
  v->requested_auto_scroll = true;

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
  auto p = thing_player(g);
  if (! p) {
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

  v->tick_begin_requested = true;

  v->requested_move_up    = false;
  v->requested_move_left  = false;
  v->requested_move_keft  = false;
  v->requested_move_right = false;
}

static void level_tick_end(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  v->tick_in_progress   = false;
  v->tick_end_requested = false;
  v->time_step          = 0;

  auto p = thing_player(g);
  if (! p) {
    return;
  }

  //
  // Only save once a tick is complete and before the next move is popped below
  //
  if (game_request_to_save_game_get(g)) {
    game_request_to_save_game_set(g, false);
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
}

bool level_tick_is_in_progress(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  return v->tick_in_progress;
}
