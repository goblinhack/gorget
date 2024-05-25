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

void level_cursor_set(Level *l, int x, int y)
{
  TRACE_AND_INDENT();

  l->cursor_x = x;
  l->cursor_y = y;
}

//
// Create the cursor path, avoiding things like lava
//
// For the first pass, restrict to tiles we have walked on
// For the first pass, any tiles will do
//
static std::vector< point > level_cursor_path_draw_line_attempt(Levelp l, Thingp player, point start, point end,
                                                                int attempt)
{
  TRACE_AND_INDENT();

  static std::vector< point > empty;

  int z = player->z;

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
  // If standing on a hazard, then plot a course that allows travel over hazards.
  //
  if (level_is_cursor_path_hazard(l, player->x, player->y, z)) {
    //
    // Just map the shortest path outta here
    //
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        if (level_is_cursor_path_blocker(l, x, y, z)) {
          d.val[ x ][ y ] = DMAP_IS_WALL;
        } else {
          d.val[ x ][ y ] = DMAP_IS_PASSABLE;
        }
      }
    }
  } else if (level_is_cursor_path_hazard(l, l->cursor_x, l->cursor_y, z)) {
    bool                               got_one = false;
    std::initializer_list< ThingFlag > init    = {is_lava, is_chasm};

    for (auto i : init) {
      if (level_flag(l, i, l->cursor_x, l->cursor_y, z)) {
        got_one = true;

        //
        // If the cursor is on a hazard then allow creating a path via hazards.
        //
        // However, be careful. If we click on lava, and the shortest path
        // to that lava is via a chasm, then we do not want to jump into the
        // chasm.
        //
        for (auto y = miny; y < maxy; y++) {
          for (auto x = minx; x < maxx; x++) {

            if (level_is_cursor_path_hazard(l, x, y, z)) {
              if (! level_flag(l, i, x, y, z)) {
                d.val[ x ][ y ] = DMAP_IS_WALL;
                continue;
              }
              d.val[ x ][ y ] = DMAP_IS_PASSABLE;
              continue;
            }
            d.val[ x ][ y ] = DMAP_IS_PASSABLE;
          }
        }
      }
    }

    if (! got_one) {
      //
      // Plough through all hazards? This is probably not good. Let's play safe.
      //
      for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
          if (level_is_cursor_path_blocker(l, x, y, z) || level_is_cursor_path_hazard(l, x, y, z)) {
            d.val[ x ][ y ] = DMAP_IS_WALL;
          } else {
            d.val[ x ][ y ] = DMAP_IS_PASSABLE;
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
        if (level_is_cursor_path_blocker(l, x, y, z) || level_is_cursor_path_hazard(l, x, y, z)) {
          d.val[ x ][ y ] = DMAP_IS_WALL;
        } else {
          d.val[ x ][ y ] = DMAP_IS_PASSABLE;
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
        if (! l->is_walked[ x ][ y ][ z ]) {
          d.val[ x ][ y ] = DMAP_IS_WALL;
        }

        //
        // Probably best to not use tiles where there is a monster
        //
        if (level_is_monst(l, x, y, z)) {
          d.val[ x ][ y ] = DMAP_IS_WALL;
        }
      }
    }
  }

  dmap_start = point(minx, miny);
  dmap_end   = point(maxx, maxy);

  d.val[ end.x ][ end.y ]     = DMAP_IS_GOAL;
  d.val[ start.x ][ start.y ] = DMAP_IS_PASSABLE;

  // dmap_print(&d, start, dmap_start, dmap_end);
  dmap_process_allow_diagonals(&d, dmap_start, dmap_end, true);
  // dmap_print(&d, start, dmap_start, dmap_end);

  auto p         = dmap_solve(&d, start);
  auto path_size = p.size();
  if (! path_size) {
    return empty;
  }

  //
  // If we could not reach the target, then the path will just plot the distance from the start, which is not what
  // we want.
  //
  if (p[ path_size - 1 ] != end) {
    return empty;
  }

  return p;
}

//
// Create a cursor path between the two points
//
// Returns true on success
//
static std::vector< point > level_cursor_path_draw_line(Levelp l, point start, point end)
{
  static std::vector< point > empty;

  auto player = thing_player(l);
  if (! player) {
    return empty;
  }

  //
  // Choose the shortest path of each attempt.
  //
  // The first path prefers visited tiles.
  //
  auto attempt1 = level_cursor_path_draw_line_attempt(l, player, start, end, 1);
  auto attempt2 = level_cursor_path_draw_line_attempt(l, player, start, end, 2);

  std::vector< point > best;

  best = attempt1;

  if (! best.size()) {
    best = attempt2;
  } else if (attempt2.size() && (attempt2.size() < best.size())) {
    best = attempt2;
  }

  return best;
}

static void level_cursor_player_move_path_update(Levelp l, Thingp t, std::vector< point > &move_path)
{
  auto aip = thing_ai(l, t);
  if (! aip) {
    return;
  }

  int index           = 0;
  aip->move_path.size = 0;

  for (auto p : move_path) {
    aip->move_path.points[ index ].x = p.x;
    aip->move_path.points[ index ].y = p.y;
    aip->move_path.size              = ++index;
    if (index >= ARRAY_SIZE(aip->move_path.points)) {
      break;
    }
  }
}

void level_cursor_update(Levelp l)
{
  if ((l->cursor_x == l->old_cursor_x) && (l->cursor_y == l->old_cursor_y)) {
    return;
  }

  //
  // Clear the path if there is no player or we're about to remake it.
  //
  memset(l->cursor, 0, SIZEOF(l->cursor));

  auto player = thing_player(l);
  if (! player) {
    return;
  }

  //
  // Draw the path
  //
  auto cursor_path = level_cursor_path_draw_line(l, point(player->x, player->y), point(l->cursor_x, l->cursor_y));
  for (auto p : cursor_path) {
    l->cursor[ p.x ][ p.y ] = CURSOR_PATH;
  }
  l->cursor[ l->cursor_x ][ l->cursor_y ] = CURSOR_AT;

  l->old_cursor_x = l->cursor_x;
  l->old_cursor_y = l->cursor_y;

  level_cursor_player_move_path_update(l, player, cursor_path);
}
