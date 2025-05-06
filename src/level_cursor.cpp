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
#include "my_tp.hpp"

#include <string.h>
#include <vector>

static std::vector< point > cursor_path;

void level_cursor_set(Gamep g, Levelsp v, point p)
{
  TRACE_AND_INDENT();

  if (! is_oob(p)) {
    v->cursor_at = p;
  }
}

//
// Create the cursor path, avoiding things like lava
//
// For the first pass, restrict to tiles we have walked on
// For the first pass, any tiles will do
//
static std::vector< point > level_cursor_path_draw_line_attempt(Gamep g, Levelsp v, Levelp l, Thingp player,
                                                                point start, point end, int attempt)
{
  TRACE_AND_INDENT();

  static std::vector< point > empty;

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

  auto border = game_tiles_visible_across_get(g);
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
  if (level_is_cursor_path_hazard(g, v, l, player->at)) {
    //
    // Just map the shortest path outta here
    //
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        if (level_is_cursor_path_blocker(g, v, l, point(x, y))) {
          d.val[ x ][ y ] = DMAP_IS_WALL;
        } else {
          d.val[ x ][ y ] = DMAP_IS_PASSABLE;
        }
      }
    }
  } else if (level_is_cursor_path_hazard(g, v, l, v->cursor_at)) {
    bool                               got_one = false;
    std::initializer_list< ThingFlag > init    = {is_lava, is_chasm};

    for (auto i : init) {
      if (level_flag(g, v, l, i, point(v->cursor_at.x, v->cursor_at.y))) {
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
            point p(x, y);

            if (level_is_cursor_path_hazard(g, v, l, p)) {
              if (! level_flag(g, v, l, i, p)) {
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
          point p(x, y);

          if (level_is_cursor_path_blocker(g, v, l, p) || level_is_cursor_path_hazard(g, v, l, p)) {
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
        point p(x, y);

        if (level_is_cursor_path_blocker(g, v, l, p) || level_is_cursor_path_hazard(g, v, l, p)) {
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
        point p(x, y);

        if (! l->is_walked[ x ][ y ]) {
          d.val[ x ][ y ] = DMAP_IS_WALL;
        }

        //
        // Probably best to not use tiles where there is a monster
        //
        if (level_is_monst(g, v, l, p)) {
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
static std::vector< point > level_cursor_path_draw_line(Gamep g, Levelsp v, Levelp l, point start, point end)
{
  static std::vector< point > empty;

  auto player = thing_player(g);
  if (! player) {
    return empty;
  }

  //
  // Choose the shortest path of each attempt.
  //
  // The first path prefers visited tiles.
  //
  auto attempt1 = level_cursor_path_draw_line_attempt(g, v, l, player, start, end, 1);
  auto attempt2 = level_cursor_path_draw_line_attempt(g, v, l, player, start, end, 2);

  std::vector< point > best;

  best = attempt1;

  if (! best.size()) {
    best = attempt2;
  } else if (attempt2.size() && (attempt2.size() < best.size())) {
    best = attempt2;
  }

  return best;
}

//
// Stop following the current path
//
void level_cursor_path_reset(Gamep g, Levelsp v, Levelp l)
{
  auto t = thing_player(g);
  if (! t) {
    //
    // If no player, clear the cursor
    //
    memset(v->cursor, 0, SIZEOF(v->cursor));
    return;
  }

  auto aip = thing_player(g, t);
  if (! aip) {
    //
    // If no player, clear the cursor
    //
    memset(v->cursor, 0, SIZEOF(v->cursor));
    return;
  }

  v->player_pressed_button_and_waiting_for_a_path = false;
  v->player_currently_following_a_path            = false;
  aip->move_path.size                             = 0;
}

//
// Copy the mouse path to the thing
//
static void level_cursor_path_apply(Gamep g, Levelsp v, Levelp l, std::vector< point > &move_path)
{
  auto t = thing_player(g);
  if (! t) {
    //
    // If no player, clear the cursor
    //
    memset(v->cursor, 0, SIZEOF(v->cursor));
    return;
  }

  auto aip = thing_player(g, t);
  if (! aip) {
    //
    // If no player, clear the cursor
    //
    memset(v->cursor, 0, SIZEOF(v->cursor));
    return;
  }

  if (v->player_pressed_button_and_waiting_for_a_path) {
    //
    // Player wants to start following or replace the current path.
    //
    v->player_pressed_button_and_waiting_for_a_path = false;
    v->player_currently_following_a_path            = true;
  } else if (v->player_currently_following_a_path) {
    //
    // Already following a path, stick to it until completion.
    //
    return;
  }

  //
  // Copy the latest mouse path to the player
  //
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

//
// Recreate the mouse path
//
static void level_cursor_path_create(Gamep g, Levelsp v, Levelp l)
{
  auto player = thing_player(g);
  if (! player) {
    //
    // If no player, clear the cursor
    //
    memset(v->cursor, 0, SIZEOF(v->cursor));
    return;
  }

  //
  // Only create the cursor path if the player is on this level. The level
  // select level for example, has no player.
  //
  if (player->level_num != l->level_num) {
    memset(v->cursor, 0, SIZEOF(v->cursor));
    return;
  }

  //
  // Has something changed?
  //
  if ((player->at == player->old_at) && (v->cursor_at == v->old_cursor_at)) {
    return;
  }

  //
  // Clear the path.
  //
  memset(v->cursor, 0, SIZEOF(v->cursor));

  //
  // Draw the path
  //
  cursor_path = level_cursor_path_draw_line(g, v, l, player->at, v->cursor_at);
  for (auto p : cursor_path) {
    v->cursor[ p.x ][ p.y ] = CURSOR_PATH;
  }
  v->cursor[ v->cursor_at.x ][ v->cursor_at.y ] = CURSOR_AT;

  v->old_cursor_at = v->cursor_at;
}

//
// Recreate and possibly apply the mouse path to the player
//
void level_cursor_update(Gamep g, Levelsp v, Levelp l)
{
  //
  // Recreate the mouse path
  //
  level_cursor_path_create(g, v, l);

  //
  // Update the player with the path.
  //
  level_cursor_path_apply(g, v, l, cursor_path);
}
