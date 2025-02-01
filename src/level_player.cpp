//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"

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

void thing_player_move_delta(Gamep g, Levelsp v, Levelp l, int dx, int dy, int dz)
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
    thing_move_to(g, v, l, t, to);
  }

  thing_player_move_reset(g, v, l);
}

//
// All keys have been released, forget any accumulation of events
//
void thing_player_move_reset(Gamep g, Levelsp v, Levelp l)
{
  v->requested_move_up    = false;
  v->requested_move_left  = false;
  v->requested_move_keft  = false;
  v->requested_move_right = false;
}

//
// Allow moves to accumulate so we can do diagonal moves.
//
void thing_player_move_accum(Gamep g, Levelsp v, Levelp l, bool up, bool down, bool left, bool right)
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
bool thing_player_move_request(Gamep g, bool up, bool down, bool left, bool right)
{
  auto v = game_levels_get(g);
  if (! v) {
    return false;
  }

  auto l = game_level_get(g, v);
  if (! l) {
    return false;
  }

  thing_player_move_accum(g, v, l, up, down, left, right);

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
      thing_player_move_delta(g, v, l, -1, -1, 0);
    } else if (v->requested_move_right) {
      thing_player_move_delta(g, v, l, 1, -1, 0);
    } else {
      thing_player_move_delta(g, v, l, 0, -1, 0);
    }
  } else if (v->requested_move_left) {
    if (v->requested_move_keft) {
      thing_player_move_delta(g, v, l, -1, 1, 0);
    } else if (v->requested_move_right) {
      thing_player_move_delta(g, v, l, 1, 1, 0);
    } else {
      thing_player_move_delta(g, v, l, 0, 1, 0);
    }
  } else if (v->requested_move_keft) {
    thing_player_move_delta(g, v, l, -1, 0, 0);
  } else if (v->requested_move_right) {
    thing_player_move_delta(g, v, l, 1, 0, 0);
  }

  return true;
}
