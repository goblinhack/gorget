//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tile.hpp"

//
// Soft scroll to the player/
//
void level_scroll_to_player(Gamep g, Levelsp v)
{
  TRACE_NO_INDENT();

  auto player = thing_player(g);
  if (! player) {
    return;
  }

  //
  // If the player is scrolling the map via the mouse, do not auto scroll.
  //
  if (! v->requested_auto_scroll) {
    return;
  }

  //
  // Get the size of the on screen map.
  //
  int w, h;
  fbo_get_size(g, FBO_MAP, w, h);

  //
  // Where are we as a percentage on that map.
  //
  float x = (player->pix_at.x - v->pixel_map_at.x) / (float) w;
  float y = (player->pix_at.y - v->pixel_map_at.y) / (float) h;

  const auto scroll_border = MAP_SCROLL_BORDER;
  const auto scroll_speed  = MAP_SCROLL_SPEED;

  //
  // If too close to the edges, scroll.
  //
  if (x > 1.0 - scroll_border) {
    v->pixel_map_at.x += (x - scroll_border) * scroll_speed;
  }
  if (x < scroll_border) {
    v->pixel_map_at.x -= (scroll_border - x) * scroll_speed;
  }
  if (y > 1.0 - scroll_border) {
    v->pixel_map_at.y += (y - scroll_border) * scroll_speed;
  }
  if (y < scroll_border) {
    v->pixel_map_at.y -= (scroll_border - y) * scroll_speed;
  }

  level_bounds_set(g, v);
}

//
// Scroll the map e.g. via mouse
//
void level_scroll_delta(Gamep g, Levelsp v, point delta)
{
  TRACE_NO_INDENT();

  v->pixel_map_at += delta;
  v->requested_auto_scroll = false;

  level_bounds_set(g, v);
}

//
// Jump to the player immediately.
//
void level_scroll_warp_to_player(Gamep g, Levelsp v)
{
  TRACE_NO_INDENT();

  auto t = thing_player(g);
  if (! t) {
    return;
  }

  v->pixel_map_at = t->pix_at;
  v->pixel_map_at.x -= game_map_pix_width_get(g) / 2;
  v->pixel_map_at.y -= game_map_pix_height_get(g) / 2;

  level_bounds_set(g, v);
}
