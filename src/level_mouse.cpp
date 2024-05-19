//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_dmap.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_point.hpp"
#include "my_sdl_event.hpp"
#include "my_tp.hpp"

#include <string.h>
#include <vector>

//
// Get the mouse position, so when displaying tiles we can work out where the cursor is now.
//
void level_mouse_position_get(Levelp l)
{
  TRACE_AND_INDENT();

  //
  // Get the visible map bounds
  //
  int visible_map_tl_x;
  int visible_map_tl_y;
  int visible_map_br_x;
  int visible_map_br_y;
  int visible_map_mouse_x;
  int visible_map_mouse_y;
  game_visible_map_get(game, &visible_map_tl_x, &visible_map_tl_y, &visible_map_br_x, &visible_map_br_y);

  //
  // Find out what pixel on the map the mouse is over
  //
  visible_map_mouse_x = sdl.mouse_x - visible_map_tl_x;
  visible_map_mouse_y = sdl.mouse_y;
  float scale_x       = (float) game_pix_width_get(game) / (float) game_window_pix_width_get(game);
  float scale_y       = (float) game_pix_height_get(game) / (float) game_window_pix_height_get(game);
  visible_map_mouse_x = (int) ((float) visible_map_mouse_x * scale_x);
  visible_map_mouse_y = (int) ((float) visible_map_mouse_y * scale_y);

  //
  // Now we wait for level_display to find the cursor
  //
  game_visible_map_mouse_set(game, visible_map_mouse_x, visible_map_mouse_y);
}
