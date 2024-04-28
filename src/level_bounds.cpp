//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_tile.hpp"

void level_bounds_set(Levelp l)
{
  TRACE_NO_INDENT();

  auto dw = TILE_WIDTH;
  auto dh = TILE_HEIGHT;

  //
  // The number of tiles additionally to draw to avoid clipping
  //
  auto clipping_border = 2;

  //
  // Set the scroll bounds
  //
  if (l->pixel_map_at_x < 0) {
    l->pixel_map_at_x = 0;
  }
  if (l->pixel_map_at_y < 0) {
    l->pixel_map_at_y = 0;
  }

  //
  // Square map
  //
  auto max_pix_x = (MAP_WIDTH * dw) - game_pix_height_get(game);
  auto max_pix_y = (MAP_HEIGHT * dh) - game_pix_height_get(game);

  if (l->pixel_map_at_x > max_pix_x) {
    l->pixel_map_at_x = max_pix_x;
  }
  if (l->pixel_map_at_y > max_pix_y) {
    l->pixel_map_at_y = max_pix_y;
  }

  //
  // Set the tile bounds
  //
  int tmp_minx = l->pixel_map_at_x / dw;
  int tmp_miny = l->pixel_map_at_y / dh;
  tmp_minx -= clipping_border;
  tmp_minx -= clipping_border;

  if (tmp_minx < 0) {
    tmp_minx = 0;
  }
  if (tmp_miny < 0) {
    tmp_miny = 0;
  }

  int tmp_maxx = (l->pixel_map_at_x + game_map_pix_width_get(game)) / dw;
  int tmp_maxy = (l->pixel_map_at_y + game_map_pix_height_get(game)) / dh;

  tmp_maxx += clipping_border;
  tmp_maxy += clipping_border;

  if (tmp_maxx >= MAP_WIDTH) {
    tmp_maxx = MAP_WIDTH;
  }
  if (tmp_maxy >= MAP_HEIGHT) {
    tmp_maxy = MAP_HEIGHT;
  }

  l->minx = tmp_minx;
  l->miny = tmp_miny;
  l->maxx = tmp_maxx;
  l->maxy = tmp_maxy;
}
