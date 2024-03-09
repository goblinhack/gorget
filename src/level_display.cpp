//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_level.hpp"
#include "my_tile.hpp"

void Level::set_display_bounds(void)
{
  TRACE_NO_INDENT();

  auto dw = TILE_WIDTH / game->config.game_pix_zoom;
  auto dh = TILE_HEIGHT / game->config.game_pix_zoom;

  //
  // The number of tiles additionally to draw to avoid clipping
  //
  auto clipping_border = 2;

  //
  // Set the scroll bounds
  //
  if (data->pixel_map_at_x < 0) {
    data->pixel_map_at_x = 0;
  }
  if (data->pixel_map_at_y < 0) {
    data->pixel_map_at_y = 0;
  }

  //
  // Square map
  //
  auto max_pix_x = (MAP_WIDTH * dw) - game->config.game_pix_height;
  auto max_pix_y = (MAP_HEIGHT * dh) - game->config.game_pix_height;

  if (data->pixel_map_at_x > max_pix_x) {
    data->pixel_map_at_x = max_pix_x;
  }
  if (data->pixel_map_at_y > max_pix_y) {
    data->pixel_map_at_y = max_pix_y;
  }

  //
  // Set the tile bounds
  //
  int tmp_minx = data->pixel_map_at_x / dw;
  int tmp_miny = data->pixel_map_at_y / dh;
  tmp_minx -= clipping_border;
  tmp_minx -= clipping_border;

  if (tmp_minx < 0) {
    tmp_minx = 0;
  }
  if (tmp_miny < 0) {
    tmp_miny = 0;
  }

  int tmp_maxx = (data->pixel_map_at_x + game->config.map_pix_width) / dw;
  int tmp_maxy = (data->pixel_map_at_y + game->config.map_pix_height) / dh;

  tmp_maxx += clipping_border;
  tmp_maxy += clipping_border;

  if (tmp_maxx >= MAP_WIDTH) {
    tmp_maxx = MAP_WIDTH;
  }
  if (tmp_maxy >= MAP_HEIGHT) {
    tmp_maxy = MAP_HEIGHT;
  }

  minx = tmp_minx;
  miny = tmp_miny;
  maxx = tmp_maxx;
  maxy = tmp_maxy;

  if (game->config.game_pix_zoom != 1) {
    minx = 0;
    miny = 0;
    maxx = MAP_WIDTH;
    maxy = MAP_HEIGHT;
  }
}

void Level::display(void)
{
  TRACE_NO_INDENT();

  set_display_bounds();
  display_dungeon();
}
