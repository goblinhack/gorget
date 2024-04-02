//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_level.hpp"
#include "my_tile.hpp"

//
// Soft scroll to the player/
//
void Level::scroll_to_player(void)
{
  TRACE_NO_INDENT();

  auto player = thing_player();
  if (! player) {
    return;
  }

  //
  // If the player is scrolling the map via the mouse, do not auto scroll.
  //
  if (! data->requested_auto_scroll) {
    return;
  }

  //
  // Get the size of the on screen map.
  //
  int w, h;
  fbo_get_size(FBO_MAP, w, h);

  //
  // Where are we as a percentage on that map.
  //
  float x = (player->pix_x - data->pixel_map_at_x) / (float) w;
  float y = (player->pix_y - data->pixel_map_at_y) / (float) h;

  const auto scroll_border = MAP_SCROLL_BORDER;
  const auto scroll_speed  = MAP_SCROLL_SPEED;

  //
  // If too close to the edges, scroll.
  //
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

  bounds_set();
}

//
// Scroll the map e.g. via mouse
//
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

//
// Jump to the player immediately.
//
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
