//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"

//
// We focus on the current level if on the level select screen.
// Failing that we focus on the player if playing a level.
//
Thingp level_scroll_target(Gamep g, Levelsp v)
{
  TRACE_NO_INDENT();

  //
  // If on the select level, do we have a current level?
  //
  auto l = game_level_get(g, v);
  if (level_is_level_select(g, v, l)) {
    Thingp target = thing_level_select(g);
    if (target) {
      return target;
    }
  }

  return thing_player(g);
}

//
// Soft scroll to the player/level.
//
void level_scroll_to_focus(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  //
  // We focus on the current level if on the level select screen.
  // Failing that we focus on the player if playing a level.
  //
  Thingp target = level_scroll_target(g, v);
  if (! target) {
    return;
  }

  //
  // Get the size of the on screen map.
  //
  int w, h;
  fbo_get_size(g, FBO_MAP_FG, w, h);

  //
  // Where are we as a percentage on that map.
  //
  int    zoom = game_map_zoom_get(g);
  spoint pix_at(thing_pix_at(target));
  float  x = ((pix_at.x * zoom) - v->pixel_map_at.x) / (float) w;
  float  y = ((pix_at.y * zoom) - v->pixel_map_at.y) / (float) h;

  const auto scroll_border = MAP_SCROLL_INNER_EDGE;
  const auto scroll_speed  = MAP_SCROLL_SPEED;

  if (v->requested_forced_auto_scroll) {
    //
    // For a time period e.g. post teleport, we want to ignore mouse moves until the player is
    // centered once more.
    //
  } else if (! v->requested_auto_scroll) {
    //
    // If the player is scrolling the map via the mouse, do not auto scroll.
    //
    if (level_is_level_select(g, v, l)) {
      //
      // Allow mouse scrolling always
      //
      return;
    } else if ((x < MAP_SCROLL_OUTER_EDGE) || (y < MAP_SCROLL_OUTER_EDGE) || (x > 1 - MAP_SCROLL_OUTER_EDGE)
               || (y > 1 - MAP_SCROLL_OUTER_EDGE)) {
      //
      // Unless the player has wandered off screen
      //
      switch (player_state(g, v)) {
        case PLAYER_STATE_INIT :
          //
          // Player not initialized yet
          // Ignore auto scroll
          //
          return;
        case PLAYER_STATE_DEAD :
          //
          // Player is dead.
          // Re-enable auto scroll
          //
          v->requested_auto_scroll = true;
          break;
        case PLAYER_STATE_NORMAL :
          //
          // Replace the mouse path
          // Ignore auto scroll
          //
          return;
        case PLAYER_STATE_PATH_REQUESTED :
          //
          // Player wants to start following or replace the current path.
          // Re-enable auto scroll
          //
          return;
        case PLAYER_STATE_MOVE_CONFIRM_REQUESTED :
          //
          // Wait for confirmation.
          // Re-enable auto scroll
          //
          return;
        case PLAYER_STATE_FOLLOWING_A_PATH :
          //
          // Already following a path, stick to it until completion.
          // Re-enable auto scroll
          //
          v->requested_auto_scroll = true;
          break;
        case PLAYER_STATE_ENUM_MAX : return;
      }
    } else {
      //
      // Ignore auto scroll
      //
      return;
    }
  }

  //
  // Did we scroll any pixels?
  //
  int dx = 0;
  int dy = 0;

  //
  // If too close to the edges, scroll.
  //
  if (x > 1.0 - scroll_border) {
    dx = (int) ((x - scroll_border) * scroll_speed);
    v->pixel_map_at.x += dx;
  }
  if (x < scroll_border) {
    dy = (int) ((scroll_border - x) * scroll_speed);
    v->pixel_map_at.x -= dy;
  }
  if (y > 1.0 - scroll_border) {
    dy = (int) ((y - scroll_border) * scroll_speed);
    v->pixel_map_at.y += dy;
  }
  if (y < scroll_border) {
    dx = (int) ((scroll_border - y) * scroll_speed);
    v->pixel_map_at.y -= dx;
  }

  //
  // Check for overflow
  //
  if (v->pixel_map_at.x > v->pixel_max.x) {
    dx                = 0;
    v->pixel_map_at.x = v->pixel_max.x;
  }

  if (v->pixel_map_at.y > v->pixel_max.y) {
    dy                = 0;
    v->pixel_map_at.y = v->pixel_max.y;
  }

  if (v->pixel_map_at.x < 0) {
    dx                = 0;
    v->pixel_map_at.x = 0;
  }

  if (v->pixel_map_at.y < 0) {
    dy                = 0;
    v->pixel_map_at.y = 0;
  }

  //
  // Have we finished scrolling?
  //
  if ((dx == 0) && (dy == 0)) {
    v->requested_forced_auto_scroll = false;
  }

  level_bounds_set(g, v, l);
}

//
// Scroll the map e.g. via mouse
//
void level_scroll_delta(Gamep g, Levelsp v, Levelp l, spoint delta)
{
  TRACE_NO_INDENT();

  v->pixel_map_at += delta;
  v->requested_auto_scroll = false;

  level_bounds_set(g, v, l);
}

//
// For a time period e.g. post teleport, we want to ignore mouse moves until the player is
// centered once more.
//
void level_forced_auto_scroll(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  v->requested_forced_auto_scroll = true;

  level_bounds_set(g, v, l);
}

//
// Jump to the target immediately.
//
void level_scroll_warp_to_focus(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  verify(MTYPE_LEVELS, v);

  //
  // We focus on the current level if on the level select screen.
  // Failing that we focus on the player if playing a level.
  //
  Thingp target = level_scroll_target(g, v);
  if (! target) {
    return;
  }

  int zoom = game_map_zoom_get(g);

  v->pixel_map_at = thing_pix_at(target);
  v->pixel_map_at.x *= zoom;
  v->pixel_map_at.y *= zoom;

  v->pixel_map_at.x -= game_map_fbo_width_get(g) / 2;
  v->pixel_map_at.y -= game_map_fbo_height_get(g) / 2;

  level_bounds_set(g, v, l);
}
