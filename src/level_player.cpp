//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"

void Level::player_map_center()
{
  TRACE_NO_INDENT();

  if (! data->player) {
    return;
  }

  auto t = thing_find(data->player);
  if (! t) {
    return;
  }

  data->pixel_map_at_x = t->pix_x;
  data->pixel_map_at_y = t->pix_y;
  data->pixel_map_at_x -= game->config.map_pix_width / 2;
  data->pixel_map_at_y -= game->config.map_pix_height / 2;
}

void Level::player_move(int8_t dx, int8_t dy)
{
  TRACE_NO_INDENT();

  if (! data->player) {
    return;
  }

  auto t = thing_find(data->player);
  if (! t) {
    return;
  }

  t->dx += dx;
  t->dy += dy;
}

void Level::player_move_left()
{
  TRACE_NO_INDENT();
  player_move(-1, 0);
}

void Level::player_move_right()
{
  TRACE_NO_INDENT();
  player_move(1, 0);
}

void Level::player_move_up()
{
  TRACE_NO_INDENT();
  player_move(0, -1);
}

void Level::player_move_down()
{
  TRACE_NO_INDENT();
  player_move(0, 1);
}
