//
// Copyright Neil McGill, goblinhack@gmail.com
//

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
        point p(x, y);
        auto  tp = tp_get(p, slot);
        if (! tp) {
          continue;
        }

        if (! tp->is_player) {
          continue;
        }

        auto t = thing_init(tp, p);

        thing_push(t);

        if (tp->player_index == data->player_index) {
          data->player = t->id;
        }

        tp_unset(p, tp);
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

void Level::thing_player_map_center()
{
  TRACE_NO_INDENT();

  auto t = thing_player();
  if (! t) {
    return;
  }

  data->pixel_map_at_x = t->pix_x;
  data->pixel_map_at_y = t->pix_y;
  data->pixel_map_at_x -= game->config.map_pix_width / 2;
  data->pixel_map_at_y -= game->config.map_pix_height / 2;
}

void Level::thing_player_move(int8_t dx, int8_t dy)
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

  thing_update_map_pos(t, t->x + dx, t->y + dy);

  tick_begin_requested("player moved");

  data->request_player_move_up    = false;
  data->request_player_move_down  = false;
  data->request_player_move_left  = false;
  data->request_player_move_right = false;
}

void Level::thing_player_move_request(bool up, bool down, bool left, bool right)
{
  //
  // If a move is in progress, do nothing
  //
  if (tick_is_in_progress()) {
    //
    // But if the player presses the keys again towards the end of the tick, allow that.
    //
    if (data->time_step < 0.5) {
      return;
    }
  }

  if (up) {
    data->request_player_move_up = up;
  }

  if (down) {
    data->request_player_move_down = down;
  }

  if (left) {
    data->request_player_move_left = left;
  }

  if (right) {
    data->request_player_move_right = right;
  }

  if (data->request_player_move_up) {
    if (data->request_player_move_left) {
      thing_player_move(-1, -1);
    } else if (data->request_player_move_right) {
      thing_player_move(1, -1);
    } else {
      thing_player_move(0, -1);
    }
  } else if (data->request_player_move_down) {
    if (data->request_player_move_left) {
      thing_player_move(-1, 1);
    } else if (data->request_player_move_right) {
      thing_player_move(1, 1);
    } else {
      thing_player_move(0, 1);
    }
  } else if (data->request_player_move_left) {
    thing_player_move(-1, 0);
  } else if (data->request_player_move_right) {
    thing_player_move(1, 0);
  }

  CON("%d %d %d %d", data->request_player_move_up, data->request_player_move_down, data->request_player_move_left,
      data->request_player_move_right);
}
