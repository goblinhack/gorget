//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"

void Level::thing_player_create_and_place()
{
  TRACE_NO_INDENT();

  if (data->player) {
    return;
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      for (auto x = 0; x < MAP_WIDTH; x++) {
        auto tp = tp_get(x, y, slot);
        if (! tp) {
          continue;
        }

        if (! tp_is_player_get(tp)) {
          continue;
        }

        auto t = thing_init(tp, x, y);

        thing_push(t);

        if (tp_player_index_get(tp) == data->player_index) {
          data->player = t->id;
        }

        tp_unset(x, y, tp);
      }
    }
  }
}

Thingp Level::thing_player()
{
  TRACE_NO_INDENT();

  if (! data->player) {
    return NULL;
  }

  return thing_find(data->player);
}

void Level::thing_player_move_delta(int dx, int dy)
{
  TRACE_NO_INDENT();

  //
  // Wait until the end of the tick
  //
  if (tick_is_in_progress()) {
    return;
  }

  auto t = thing_player();
  if (! t) {
    return;
  }

  if (1 || thing_can_move(t, t->x + dx, t->y + dy)) {
    thing_move(t, t->x + dx, t->y + dy);

    tick_begin_requested("player moved");
  }

  thing_player_move_reset();
}

//
// All keys have been released, forget any accumulation of events
//
void Level::thing_player_move_reset(void)
{
  data->requested_move_up    = false;
  data->requested_move_left  = false;
  data->requested_move_keft  = false;
  data->requested_move_right = false;
}

//
// Allow moves to accumulate so we can do diagonal moves.
//
void Level::thing_player_move_accum(bool up, bool down, bool left, bool right)
{
  if (up) {
    data->requested_move_up = up;
  }

  if (down) {
    data->requested_move_left = down;
  }

  if (left) {
    data->requested_move_keft = left;
  }

  if (right) {
    data->requested_move_right = right;
  }
}

//
// Attempt to move
//
bool Level::thing_player_move_request(bool up, bool down, bool left, bool right)
{
  thing_player_move_accum(up, down, left, right);

  //
  // If a move is in progress, do nothing
  //
  if (tick_is_in_progress()) {
    //
    // But if the player presses the keys again towards the end of the tick, allow that.
    //
    return false;
  }

  if (data->requested_move_up) {
    if (data->requested_move_keft) {
      thing_player_move_delta(-1, -1);
    } else if (data->requested_move_right) {
      thing_player_move_delta(1, -1);
    } else {
      thing_player_move_delta(0, -1);
    }
  } else if (data->requested_move_left) {
    if (data->requested_move_keft) {
      thing_player_move_delta(-1, 1);
    } else if (data->requested_move_right) {
      thing_player_move_delta(1, 1);
    } else {
      thing_player_move_delta(0, 1);
    }
  } else if (data->requested_move_keft) {
    thing_player_move_delta(-1, 0);
  } else if (data->requested_move_right) {
    thing_player_move_delta(1, 0);
  }

  return true;
}
