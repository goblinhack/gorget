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

#include <algorithm>
#include <math.h>

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_thing.hpp"

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
    if (thing_is_open(it)) {
      continue;
    }

    if (thing_is_light_blocker(it)) {
      return true;
    }
  }

  return false;

#if 0
    if (me->is_monst()) {
      if (! light_blocker) {
        light_blocker = is_light_blocker_for_monst(p);
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
#ifdef OPT_DEV
  if (is_oob(pov)) {
    ERR("overflow");
    return;
  }
#endif

  m->can_see[ pov.x ][ pov.y ] = val;
}

// Cast visiblity using shadowcasting.
void level_fov_do(Gamep g, Levelsp v, Levelp l, Thingp me, //
                  FovMap      *fov_can_see_tile,           //
                  FovMap      *fov_has_ever_seen_tile,     //
                  const spoint pov,                        //
                  const int    distance_from_origin,       // Polar distance_from_origin from POV.
                  double       view_slope_high,            //
                  double       view_slope_low,             //
                  const int    max_radius,                 //
                  const int    octant,                     //
                  const bool   light_walls)
{
  const int xx             = matrix_table[ octant ][ 0 ];
  const int xy             = matrix_table[ octant ][ 1 ];
  const int yx             = matrix_table[ octant ][ 2 ];
  const int yy             = matrix_table[ octant ][ 3 ];
  const int radius_squared = max_radius * max_radius;

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

  for (int angle = distance_from_origin; angle >= 0; --angle) { // Polar angle coordinates from high to low.
    const double tile_slope_high     = (angle + 0.5) / (distance_from_origin - 0.5);
    const double tile_slope_low      = (angle - 0.5) / (distance_from_origin + 0.5);
    const double prev_tile_slope_low = (angle + 0.5) / (distance_from_origin + 0.5);

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
      level_fov_set(fov_can_see_tile, p, true);

      if (fov_has_ever_seen_tile) {
        level_fov_set(fov_has_ever_seen_tile, p, true);
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
      level_fov_do(g, v, l, me, fov_can_see_tile, fov_has_ever_seen_tile, pov, distance_from_origin + 1,
                   view_slope_high, tile_slope_high, max_radius, octant, light_walls);
    }

    prev_tile_blocked = light_blocker;
  }

  if (! prev_tile_blocked) {
    //
    // Tail-recurse into the current view.
    //
    level_fov_do(g, v, l, me, fov_can_see_tile, fov_has_ever_seen_tile, pov, distance_from_origin + 1,
                 view_slope_high, view_slope_low, max_radius, octant, light_walls);
  }
}

void level_fov(Gamep g, Levelsp v, Levelp l, Thingp me, FovMap *fov_can_see_tile, FovMap *fov_has_ever_seen_tile,
               spoint pov, int max_radius)
{
  TRACE_NO_INDENT();

  if (is_oob(pov)) {
    ERR("out of bounds");
    return;
  }

  const bool light_walls = thing_is_player(me);

  memset(fov_can_see_tile, 0, sizeof(*fov_can_see_tile));

  if (max_radius <= 0) {
    auto max_radius_x = std::max(MAP_WIDTH - (int) pov.x, (int) pov.x);
    auto max_radius_y = std::max(MAP_HEIGHT - (int) pov.y, (int) pov.y);
    max_radius        = (int) (sqrt(max_radius_x * max_radius_x + max_radius_y * max_radius_y)) + 1;
  }

  // recursive shadow casting
  for (int octant = 0; octant < 8; ++octant) {
    level_fov_do(g, v, l, me, fov_can_see_tile, fov_has_ever_seen_tile, pov, 1, 1.0, 0.0, max_radius, octant,
                 light_walls);
  }

  level_fov_set(fov_can_see_tile, pov, true);
  level_fov_set(fov_has_ever_seen_tile, pov, true);

  // me->can_see_you(point(pov_x, pov_y));
}
