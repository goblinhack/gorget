/*
 * Modified from libtcod, so here is their original license
 */

/* BSD 3-Clause License
 *
 * Copyright © 2008-2021, Jice and the libtcod contributors.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

//
// Changed by goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_thing.hpp"

#include <algorithm>
#include <math.h>
#include <string.h>

// Octant transformation matrixes.
// {xx, xy, yx, yy}
static const int matrix_table[ 8 ][ 4 ] = {
    {1, 0, 0, 1},   {0, 1, 1, 0},   {0, -1, 1, 0}, {-1, 0, 0, 1},
    {-1, 0, 0, -1}, {0, -1, -1, 0}, {0, 1, -1, 0}, {1, 0, 0, -1},
};

//
// Something blocking the light?
//
static bool level_fov_light_blocker_at(Gamep g, Levelsp v, Levelp l, Thingp me, spoint pov)
{
  FOR_ALL_THINGS_AT(g, v, l, it, pov)
  {
    //
    // Dead foliage should not block
    //
    if (thing_is_dead(it)) {
      continue;
    }

    //
    // Open doors should not block
    //
    if (thing_is_open(it)) {
      continue;
    }

    if (thing_is_obs_to_vision(it)) {
      return true;
    }
  }

  return false;

#if 0
    if (me->is_monst()) {
      if (! light_blocker) {
        light_blocker = is_obs_to_vision_for_monst(p);
      }

      if (! light_blocker) {
        if (! me->is_player()) {
          if (! me->is_able_to_see_in_magical_darkness()) {
            light_blocker = is_darkness(p);
          }
        }
      }
    }
#endif
}

static void level_fov_set(FovMap *m, spoint pov, bool val)
{
#ifdef DEBUG_BUILD
  if (is_oob(pov)) {
    ERR("overflow");
    return;
  }
#endif

  m->can_see[ pov.x ][ pov.y ] = val;
}

static bool level_fov(FovMap *m, spoint pov)
{
#ifdef DEBUG_BUILD
  if (is_oob(pov)) {
    ERR("overflow");
    return false;
  }
#endif

  return m->can_see[ pov.x ][ pov.y ];
}

// Cast visiblity using shadowcasting.
void level_fov_do(Gamep g, Levelsp v, Levelp l, Thingp me,           //
                  FovMap                      *fov_can_see_tile,     //
                  FovMap                      *fov_has_seen_tile,    //
                  const spoint                 pov,                  //
                  const short                  distance_from_origin, // Polar distance_from_origin from POV.
                  float                        view_slope_high,      //
                  float                        view_slope_low,       //
                  const short                  max_radius,           //
                  const short                  octant,               //
                  const bool                   light_walls,          //
                  level_fov_can_see_callback_t can_see_callback)
{
  const short xx             = matrix_table[ octant ][ 0 ];
  const short xy             = matrix_table[ octant ][ 1 ];
  const short yx             = matrix_table[ octant ][ 2 ];
  const short yy             = matrix_table[ octant ][ 3 ];
  const short radius_squared = max_radius * max_radius;

  if (view_slope_high < view_slope_low) {
    return; // View is invalid.
  }

  if (distance_from_origin > max_radius) {
    return; // Distance is out-of-range.
  }

  if (is_oob(pov.x + distance_from_origin * xy, pov.y + distance_from_origin * yy)) {
    return; // Distance is out-of-bounds.
  }

  bool prev_tile_blocked = false;

  for (short angle = distance_from_origin; angle >= 0; --angle) { // Polar angle coordinates from high to low.
    const float tile_slope_high     = (angle + 0.5f) / (distance_from_origin - 0.5f);
    const float tile_slope_low      = (angle - 0.5f) / (distance_from_origin + 0.5f);
    const float prev_tile_slope_low = (angle + 0.5f) / (distance_from_origin + 0.5f);

    if (tile_slope_low > view_slope_high) {
      continue; // Tile is not in the view yet.
    }
    if (tile_slope_high < view_slope_low) {
      break; // Tiles will no longer be in view.
    }

    // Current tile is in view.
    const spoint p(pov.x + angle * xx + distance_from_origin * xy, pov.y + angle * yx + distance_from_origin * yy);

    if (is_oob(p)) {
      continue; // Angle is out-of-bounds.
    }

    //
    // Treat player and monster blocking differently so the player can use cover
    //
    auto light_blocker = level_fov_light_blocker_at(g, v, l, me, p);

    if (angle * angle + distance_from_origin * distance_from_origin <= radius_squared
        && (light_walls || ! light_blocker)) {

      if (fov_can_see_tile) {
        //
        // If not seen already, light it
        //
        if (! level_fov(fov_can_see_tile, p)) {
          level_fov_set(fov_can_see_tile, p, true);

          //
          // Per tile can see callback check
          //
          if (can_see_callback) {
            (can_see_callback)(g, v, l, me, pov, p);
          }
        }
      }

      //
      // Monsters do not have this
      //
      if (fov_has_seen_tile) {
        level_fov_set(fov_has_seen_tile, p, true);
      }

#ifdef TODO
      //
      // Always call this, even for cells we can see, as a monster may have just walked onto
      // a cell that was empty that we have already seen.
      //
      // me->can_see_you(p);
#endif
    }

    if (prev_tile_blocked && ! light_blocker) { // Wall -> floor.
      view_slope_high = prev_tile_slope_low;    // Reduce the view size.
    }

    if (! prev_tile_blocked && light_blocker) { // Floor -> wall.
      //
      // Get the last sequence of floors as a view and recurse into them.
      //
      level_fov_do(g, v, l, me, fov_can_see_tile, fov_has_seen_tile, pov, distance_from_origin + 1, view_slope_high,
                   tile_slope_high, max_radius, octant, light_walls, can_see_callback);
    }

    prev_tile_blocked = light_blocker;
  }

  if (! prev_tile_blocked) {
    //
    // Tail-recurse into the current view.
    //
    level_fov_do(g, v, l, me, fov_can_see_tile, fov_has_seen_tile, pov, distance_from_origin + 1, view_slope_high,
                 view_slope_low, max_radius, octant, light_walls, can_see_callback);
  }
}

void level_fov(Gamep g, Levelsp v, Levelp l, Thingp me, FovMap *fov_can_see_tile, FovMap *fov_has_seen_tile,
               spoint pov, int max_radius, level_fov_can_see_callback_t can_see_callback)
{
  TRACE_NO_INDENT();

  const bool light_walls = true;

  if (fov_can_see_tile) {
    memset(fov_can_see_tile, 0, sizeof(*fov_can_see_tile));
  }

  // recursive shadow casting
  for (int octant = 0; octant < 8; ++octant) {
    level_fov_do(g, v, l, me, fov_can_see_tile, fov_has_seen_tile, pov, 1, 1.0, 0.0, max_radius, octant, light_walls,
                 can_see_callback);
  }

  if (fov_can_see_tile) {
    //
    // If not seen already, light it
    //
    if (! level_fov(fov_can_see_tile, pov)) {
      level_fov_set(fov_can_see_tile, pov, true);

      //
      // Per tile can see callback check
      //
      if (can_see_callback) {
        (can_see_callback)(g, v, l, me, pov, pov);
      }
    }
  }

  if (fov_has_seen_tile) {
    level_fov_set(fov_has_seen_tile, pov, true);
  }

  // me->can_see_you(point(pov_x, pov_y));
}
