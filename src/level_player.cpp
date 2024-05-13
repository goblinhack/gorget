//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"

Thingp level_thing_player(Levelp l)
{
  TRACE_NO_INDENT();

  if (! l) {
    return nullptr;
  }

  if (! l->player) {
    return nullptr;
  }

  return level_thing_find(l, l->player);
}

void level_thing_player_move_delta(Levelp l, int dx, int dy)
{
  TRACE_NO_INDENT();

  //
  // Wait until the end of the tick
  //
  if (level_tick_is_in_progress(l)) {
    return;
  }

  auto t = level_thing_player(l);
  if (! t) {
    return;
  }

  if (level_thing_can_move_to(l, t, t->x + dx, t->y + dy)) {
    level_thing_move(l, t, t->x + dx, t->y + dy);

    level_tick_begin_requested(l, "player moved");
  }

  level_thing_player_move_reset(l);
}

//
// All keys have been released, forget any accumulation of events
//
void level_thing_player_move_reset(Levelp l)
{
  l->requested_move_up    = false;
  l->requested_move_left  = false;
  l->requested_move_keft  = false;
  l->requested_move_right = false;
}

//
// Allow moves to accumulate so we can do diagonal moves.
//
void level_thing_player_move_accum(Levelp l, bool up, bool down, bool left, bool right)
{
  if (up) {
    l->requested_move_up = up;
  }

  if (down) {
    l->requested_move_left = down;
  }

  if (left) {
    l->requested_move_keft = left;
  }

  if (right) {
    l->requested_move_right = right;
  }
}

//
// Attempt to move
//
bool level_thing_player_move_request(Levelp l, bool up, bool down, bool left, bool right)
{
  level_thing_player_move_accum(l, up, down, left, right);

  //
  // If a move is in progress, do nothing
  //
  if (level_tick_is_in_progress(l)) {
    //
    // But if the player presses the keys again towards the end of the tick, allow that.
    //
    return false;
  }

  if (l->requested_move_up) {
    if (l->requested_move_keft) {
      level_thing_player_move_delta(l, -1, -1);
    } else if (l->requested_move_right) {
      level_thing_player_move_delta(l, 1, -1);
    } else {
      level_thing_player_move_delta(l, 0, -1);
    }
  } else if (l->requested_move_left) {
    if (l->requested_move_keft) {
      level_thing_player_move_delta(l, -1, 1);
    } else if (l->requested_move_right) {
      level_thing_player_move_delta(l, 1, 1);
    } else {
      level_thing_player_move_delta(l, 0, 1);
    }
  } else if (l->requested_move_keft) {
    level_thing_player_move_delta(l, -1, 0);
  } else if (l->requested_move_right) {
    level_thing_player_move_delta(l, 1, 0);
  }

  return true;
}
