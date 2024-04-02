//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_level.hpp"
#include "my_tile.hpp"

void Level::scroll_to_player(void)
{
  TRACE_NO_INDENT();

  auto player = thing_player();
  if (! player) {
    return;
  }

  if (! data->requested_auto_scroll) {
    return;
  }

  int w, h;
  fbo_get_size(FBO_MAP, w, h);

  float x = (player->pix_x - data->pixel_map_at_x) / (float) w;
  float y = (player->pix_y - data->pixel_map_at_y) / (float) h;

  {
    const float scroll_border = 0.4;
    const float scroll_speed  = 5;

    if (x > 1.0 - scroll_border) {
      data->pixel_map_at_x += (x - scroll_border) * scroll_speed;
    }
    if (x < scroll_border) {
      data->pixel_map_at_x -= (scroll_border - x) * scroll_speed;
    }
    if (y > 1.0 - scroll_border) {
      data->pixel_map_at_y += (y - scroll_border) * scroll_speed;
    }
    if (y < scroll_border) {
      data->pixel_map_at_y -= (scroll_border - y) * scroll_speed;
    }
  }

  bounds_set();
}

void Level::scroll_delta(int x, int y)
{
  TRACE_NO_INDENT();

  auto level = game->level;

  if (! level) {
    return;
  }

  data->pixel_map_at_x += x;
  data->pixel_map_at_y -= y;
  data->requested_auto_scroll = false;

  bounds_set();
}

void Level::scroll_warp_to_player()
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

  bounds_set();
}
