//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_tile.hpp"

//
// Soft scroll to the player/
//
void level_scroll_to_player(Levelp l)
{
  TRACE_NO_INDENT();

  auto player = level_thing_player(l);
  if (! player) {
    return;
  }

  //
  // If the player is scrolling the map via the mouse, do not auto scroll.
  //
  if (! l->requested_auto_scroll) {
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
  float x = (player->pix_x - l->pixel_map_at_x) / (float) w;
  float y = (player->pix_y - l->pixel_map_at_y) / (float) h;

  const auto scroll_border = MAP_SCROLL_BORDER;
  const auto scroll_speed  = MAP_SCROLL_SPEED;

  //
  // If too close to the edges, scroll.
  //
  if (x > 1.0 - scroll_border) {
    l->pixel_map_at_x += (x - scroll_border) * scroll_speed;
  }
  if (x < scroll_border) {
    l->pixel_map_at_x -= (scroll_border - x) * scroll_speed;
  }
  if (y > 1.0 - scroll_border) {
    l->pixel_map_at_y += (y - scroll_border) * scroll_speed;
  }
  if (y < scroll_border) {
    l->pixel_map_at_y -= (scroll_border - y) * scroll_speed;
  }

  level_bounds_set(l);
}

//
// Scroll the map e.g. via mouse
//
void level_scroll_delta(Levelp l, int x, int y)
{
  TRACE_NO_INDENT();

  l->pixel_map_at_x += x;
  l->pixel_map_at_y -= y;
  l->requested_auto_scroll = false;

  level_bounds_set(l);
}

//
// Jump to the player immediately.
//
void level_scroll_warp_to_player(Levelp l)
{
  TRACE_NO_INDENT();

  auto t = level_thing_player(l);
  if (! t) {
    return;
  }

  l->pixel_map_at_x = t->pix_x;
  l->pixel_map_at_y = t->pix_y;
  l->pixel_map_at_x -= game_map_pix_width_get(game) / 2;
  l->pixel_map_at_y -= game_map_pix_height_get(game) / 2;

  level_bounds_set(l);
}
