//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_sdl_event.hpp"
#include "my_tp.hpp"

#include <string.h>

void level_cursor_set(Level *l, int x, int y, int cursor)
{
  TRACE_NO_INDENT();

  l->cursor[ x ][ y ] = cursor;
}

void level_cursor_unset(Level *l, int x, int y, int cursor)
{
  TRACE_NO_INDENT();

  l->cursor[ x ][ y ] = CURSOR_NONE;
}

int level_cursor_get(Level *l, int x, int y)
{
  TRACE_NO_INDENT();

  return l->cursor[ x ][ y ];
}

//
// Clear all cursors and get the mouse position, so when displaying tiles
// we can work out where the cursor is now.
//
void level_cursor_reset(Levelp l)
{
  TRACE_NO_INDENT();

  memset(l->cursor, 0, sizeof(l->cursor));

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
