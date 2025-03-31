//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_dmap.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_point.hpp"
#include "my_sdl_event.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

#include <string.h>
#include <vector>

//
// Get the mouse position, so when displaying tiles we can work out where the cursor is now.
//
void level_mouse_position_get(Gamep g, Levelsp v, Levelp l)
{
  TRACE_AND_INDENT();

  if (! v || ! l) {
    return;
  }

  //
  // Get the visible map bounds
  //
  int visible_map_tl_x;
  int visible_map_tl_y;
  int visible_map_br_x;
  int visible_map_br_y;
  game_visible_map_pix_get(g, &visible_map_tl_x, &visible_map_tl_y, &visible_map_br_x, &visible_map_br_y);

  //
  // Find out what pixel on the map the mouse is over
  //
  int rel_map_mouse_x = sdl.mouse_x - visible_map_tl_x;
  int rel_map_mouse_y = sdl.mouse_y - visible_map_tl_y;
  int map_pix_width   = visible_map_br_x - visible_map_tl_x;
  int map_pix_height  = visible_map_br_y - visible_map_tl_y;

  float scale_x             = (float) map_pix_width / (float) game_map_fbo_width_get(g);
  float scale_y             = (float) map_pix_height / (float) game_map_fbo_height_get(g);
  int   visible_map_mouse_x = (int) ((float) rel_map_mouse_x / scale_x);
  int   visible_map_mouse_y = (int) ((float) rel_map_mouse_y / scale_y);

  //
  // Compenstate for level scroll
  //
  visible_map_mouse_x += v->pixel_map_at.x;
  visible_map_mouse_y += v->pixel_map_at.y;

  //
  // Update teh cursor
  //
  point p(visible_map_mouse_x / TILE_WIDTH, visible_map_mouse_y / TILE_HEIGHT);
  level_cursor_set(g, v, p);
}
