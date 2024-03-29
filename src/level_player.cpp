//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"

void Level::player_create_and_place()
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

        auto t = thing_new(tp, p);
        thing_push(t);

        if (tp->player_index == data->player_index) {
          data->player = t->id;
        }

        tp_unset(p, tp);
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

  t->dx = dx;
  t->dy = dy;
}
