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

#if 0
//
// Create the cursor path, avoiding things like lava
//
// For the first pass, restrict to tiles we have walked on
// For the first pass, any tiles will do
//
std::vector< point > cursor_path_draw_line_attempt(Levelp l, Thingp player, point start, point end, int attempt)
{
  static std::vector< point > empty;

  TRACE_AND_INDENT();

  Dmap  d {};
  point dmap_start = start;
  point dmap_end   = end;

  int minx, miny, maxx, maxy;
  if (dmap_start.x < dmap_end.x) {
    minx = dmap_start.x;
    maxx = dmap_end.x;
  } else {
    minx = dmap_end.x;
    maxx = dmap_start.x;
  }
  if (dmap_start.y < dmap_end.y) {
    miny = dmap_start.y;
    maxy = dmap_end.y;
  } else {
    miny = dmap_end.y;
    maxy = dmap_start.y;
  }

  auto border = game_tiles_visible_across_get(game);
  minx -= border;
  miny -= border;
  maxx += border;
  maxy += border;

  if (minx < 0) {
    minx = 0;
  }
  if (miny < 0) {
    miny = 0;
  }
  if (maxx >= MAP_WIDTH) {
    maxx = MAP_WIDTH - 1;
  }
  if (maxy >= MAP_HEIGHT) {
    maxy = MAP_HEIGHT - 1;
  }

  //
  // If clicking on a wall, don't walk into it.
  //
  if (cursor && is_cursor_path_blocker(it, cursor->curr_at.x, cursor->curr_at.y)) {
    return empty;
  }

  //
  // If standing on a hazard, then plot a course that allows travel over hazards.
  //
  if (is_cursor_path_hazard(player->curr_at.x, player->curr_at.y)) {
    //
    // Just map the shortest path outta here
    //
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        if (is_cursor_path_blocker(it, x, y)) {
          set(d.val, x, y, DMAP_IS_WALL);
        } else {
          set(d.val, x, y, DMAP_IS_PASSABLE);
        }
      }
    }
  } else if (cursor && is_cursor_path_hazard(cursor->curr_at.x, cursor->curr_at.y)) {
    if (is_lava(cursor->curr_at.x, cursor->curr_at.y)) {
      //
      // If the cursor is on a hazard then allow creating a path via hazards.
      //
      // However, be careful. If we click on lava, and the shortest path
      // to that lava is via a chasm, then we do not want to jump into the
      // chasm.
      //
      for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
          if (is_cursor_path_hazard(x, y)) {
            if (! is_lava(x, y)) {
              set(d.val, x, y, DMAP_IS_WALL);
              continue;
            }
          }
          if (is_cursor_path_blocker(it, x, y)) {
            set(d.val, x, y, DMAP_IS_WALL);
          } else {
            set(d.val, x, y, DMAP_IS_PASSABLE);
          }
        }
      }
    } else if (is_ooze(cursor->curr_at.x, cursor->curr_at.y)) {
      //
      // If the cursor is on a hazard then allow creating a path via hazards.
      //
      // However, be careful. If we click on ooze, and the shortest path
      // to that ooze is via a chasm, then we do not want to jump into the
      // chasm.
      //
      for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
          if (is_cursor_path_hazard(x, y)) {
            if (! is_ooze(x, y)) {
              set(d.val, x, y, DMAP_IS_WALL);
              continue;
            }
          }
          if (is_cursor_path_blocker(it, x, y)) {
            set(d.val, x, y, DMAP_IS_WALL);
          } else {
            set(d.val, x, y, DMAP_IS_PASSABLE);
          }
        }
      }
    } else if (is_chasm(cursor->curr_at.x, cursor->curr_at.y)) {
      //
      // If the cursor is on a hazard then allow creating a path via hazards.
      //
      // However, be careful. If we click on chasm, and the shortest path
      // to that chasm is through lava, then we do not want to walk through
      // the lava!
      //
      for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
          if (is_cursor_path_hazard(x, y)) {
            if (! is_chasm(x, y)) {
              set(d.val, x, y, DMAP_IS_WALL);
              continue;
            }
          }
          if (is_cursor_path_blocker(it, x, y)) {
            set(d.val, x, y, DMAP_IS_WALL);
          } else {
            set(d.val, x, y, DMAP_IS_PASSABLE);
          }
        }
      }
    } else {
      //
      // Plough through all hazards? This is probably not good. Let's play safe.
      //
      for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
          if (is_cursor_path_blocker(it, x, y) || is_cursor_path_hazard(x, y)) {
            set(d.val, x, y, DMAP_IS_WALL);
          } else {
            set(d.val, x, y, DMAP_IS_PASSABLE);
          }
        }
      }
    }
  } else {
    //
    // Normal path. Avoid hazards.
    //
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        if (is_cursor_path_blocker(it, x, y) || is_cursor_path_hazard(x, y)) {
          set(d.val, x, y, DMAP_IS_WALL);
        } else {
          set(d.val, x, y, DMAP_IS_PASSABLE);
        }
      }
    }
  }

  //
  // Limit to previously walked tiles
  //
  if (attempt == 1) {
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        if (! is_walked(x, y)) {
          set(d.val, x, y, DMAP_IS_WALL);
        }

        //
        // Probably best to not use tiles where there is a monster
        //
        if (is_monst(x, y)) {
          set(d.val, x, y, DMAP_IS_WALL);
        }
      }
    }
  }

  dmap_start = point(minx, miny);
  dmap_end   = point(maxx, maxy);

  set(d.val, end.x, end.y, DMAP_IS_GOAL);
  set(d.val, start.x, start.y, DMAP_IS_PASSABLE);

  dbg2("Make cursor path %d,%d to @%d,%d", start.x, start.y, end.x, end.y);

  // dmap_print(&d, start, dmap_start, dmap_end);
  dmap_process_allow_diagonals(&d, dmap_start, dmap_end, true);
  // dmap_print(&d, start, dmap_start, dmap_end);

  auto p         = dmap_solve(&d, start);
  auto path_size = p.size();
  if (! path_size) {
    dbg2("No path");
    return empty;
  }

  //
  // If we could not reach the target, then the path will just plot the distance from the start, which is not what
  // we want.
  //
  if (p[ path_size - 1 ] != end) {
    dbg2("Could not reach");
    return empty;
  }
  dbg2("Created attempt %d cursor path len %d", attempt, (int) p.size());

  return p;
}

bool Level::cursor_path_draw_line(Thingp it, point start, point end)
{
  auto player = level_thing_player(l);
  if (! player) {
    return;
  }

  //
  // Choose the shortest path of each attempt.
  //
  // The first path prefers visited tiles.
  //
  auto attempt1 = cursor_path_draw_line_attempt(it, start, end, 1);
  auto attempt2 = cursor_path_draw_line_attempt(it, start, end, 2);

  std::vector< point > best;

  best = attempt1;

  if (! best.size()) {
    best = attempt2;
  } else if (attempt2.size() && (attempt2.size() < best.size())) {
    best = attempt2;
  }

  dbg2("Best cursor path len %d", (int) best.size());

  if (! best.size()) {
    return false;
  }

  game->cursor_move_path = best;
  game->cursor_move_end  = end;
  game->cursor_moved     = true;

  dbg2("Created cursor path len %d", (int) best.size());

  for (auto &c : best) {
    if (cursor && cursor->is_visible()) {
      if ((c.x == cursor_at.x) && (c.y == cursor_at.y)) {
        continue;
      }
    }

    //
    // Create the cursor
    //
    cursor_path_thing_new(c);
  }

  return true;
}
#endif
