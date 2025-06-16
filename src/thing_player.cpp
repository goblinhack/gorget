//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_minimal.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

#include <string.h>

Thingp thing_player(Gamep g)
{
  TRACE_NO_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return nullptr;
  }

  if (! v->player_id) {
    return nullptr;
  }

  return thing_find(g, v, v->player_id);
}

void player_move_delta(Gamep g, Levelsp v, Levelp l, int dx, int dy, int dz)
{
  TRACE_NO_INDENT();

  auto t = thing_player(g);
  if (! t) {
    return;
  }

  //
  // Override any mouse request with the key move.
  //
  level_cursor_path_reset(g, v, l);

  //
  // Wait until the end of the tick
  //
  if (level_tick_is_in_progress(g, v, l)) {
    return;
  }

  point to(t->at.x + dx, t->at.y + dy);
  if (thing_can_move_to(g, v, l, t, to)) {
    if (thing_move_to(g, v, l, t, to)) {
      if (thing_is_player(t)) {
        level_tick_begin_requested(g, v, l, "player moved ");
      }
    } else {
      if (thing_is_player(t)) {
        level_tick_begin_requested(g, v, l, "player failed to move ");
      }
    }
  } else {
    if (thing_is_player(t)) {
      level_tick_begin_requested(g, v, l, "player bumped into obstacle");
    }
  }

  player_move_reset(g, v, l);
}

//
// All keys have been released, forget any accumulation of events
//
void player_move_reset(Gamep g, Levelsp v, Levelp l)
{
  v->requested_move_up    = false;
  v->requested_move_left  = false;
  v->requested_move_keft  = false;
  v->requested_move_right = false;
}

//
// Allow moves to accumulate so we can do diagonal moves.
//
void player_move_accum(Gamep g, Levelsp v, Levelp l, bool up, bool down, bool left, bool right)
{
  if (up) {
    v->requested_move_up = up;
  }

  if (down) {
    v->requested_move_left = down;
  }

  if (left) {
    v->requested_move_keft = left;
  }

  if (right) {
    v->requested_move_right = right;
  }
}

//
// Attempt to move
//
bool player_move_request(Gamep g, bool up, bool down, bool left, bool right)
{
  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  auto l = game_level_get(g, v);
  if (! l) {
    return false;
  }

  player_move_accum(g, v, l, up, down, left, right);

  //
  // If a move is in progress, do nothing
  //
  if (level_tick_is_in_progress(g, v, l)) {
    //
    // But if the player presses the keys again towards the end of the tick, allow that.
    //
    return false;
  }

  if (v->requested_move_up) {
    if (v->requested_move_keft) {
      player_move_delta(g, v, l, -1, -1, 0);
    } else if (v->requested_move_right) {
      player_move_delta(g, v, l, 1, -1, 0);
    } else {
      player_move_delta(g, v, l, 0, -1, 0);
    }
  } else if (v->requested_move_left) {
    if (v->requested_move_keft) {
      player_move_delta(g, v, l, -1, 1, 0);
    } else if (v->requested_move_right) {
      player_move_delta(g, v, l, 1, 1, 0);
    } else {
      player_move_delta(g, v, l, 0, 1, 0);
    }
  } else if (v->requested_move_keft) {
    player_move_delta(g, v, l, -1, 0, 0);
  } else if (v->requested_move_right) {
    player_move_delta(g, v, l, 1, 0, 0);
  }

  return true;
}

//
// Handle common level exit interactions
//
static void player_level_leave(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  level_select_update_grid_tiles(g, v);
  level_cursor_path_reset(g, v, l);
  level_change(g, v, LEVEL_SELECT_ID);
}

//
// Handle level exit interactions
//
void player_reached_exit(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  l->completed = true;
  player_level_leave(g, v, l, t);
}

//
// Handle level entrance interactions
//
void player_reached_entrance(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  player_level_leave(g, v, l, t);
}

//
// Handle interactions for a thing at its location
//
void player_collision_handle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto aip = thing_player(g, t);
  if (! aip) {
    return;
  }

  FOR_ALL_THINGS_AT(g, v, l, it, t->at)
  {
    if (thing_is_player(t)) {
      //
      // At the end of the popped path or not?
      //
      if (aip->move_path.size) {
        //
        // If still more tiles to pop, do not descend automatically
        //
        if (thing_is_exit(it)) {
          //
          // To enabled the descend shortcut
          //
          game_request_to_remake_ui_set(g);
          return;
        }

        if (thing_is_entrance(it)) {
          //
          // To enabled the ascent shortcut
          //
          game_request_to_remake_ui_set(g);
          return;
        }
      } else {
        //
        // If at the end of the move path then we can enter or leave when we get to that final tile.
        //
        if (thing_is_exit(it)) {
          //
          // Descend
          //
          player_reached_exit(g, v, l, t);
          return;
        }

        if (thing_is_entrance(it)) {
          //
          // Ascend
          //
          player_reached_entrance(g, v, l, t);
          return;
        }
      }
    }
  }
}
