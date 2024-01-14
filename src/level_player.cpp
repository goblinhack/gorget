//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_level.hpp"
#include "my_level_data.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Level::place_create_and_place()
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

        if (! tp->is_entrance) {
          continue;
        }

        auto player_tp = tp_random_player();
        auto t         = thing_new(player_tp, x, y);
        thing_push(t);
        data->player = t->id;
        return;
      }
    }
  }
}

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

  data->pixel_map_at_x = t->pix_x / PIX_SCALE;
  data->pixel_map_at_y = t->pix_y / PIX_SCALE;
  data->pixel_map_at_x -= game->config.game_pix_width / 2;
  data->pixel_map_at_y -= game->config.game_pix_height / 2;
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
  player_move(-2, 0);
}

void Level::player_move_right()
{
  TRACE_NO_INDENT();
  player_move(2, 0);
}

void Level::player_move_up()
{
  TRACE_NO_INDENT();
  player_move(0, -2);
}

void Level::player_move_down()
{
  TRACE_NO_INDENT();
  player_move(0, 2);
}
