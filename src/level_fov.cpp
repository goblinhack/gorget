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
#include "my_fov_map_inlines.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_thing_inlines.hpp"

#include <algorithm>
#include <cmath>
#include <cstring>

// Octant transformation matrixes.
// {xx, xy, yx, yy}
static const int matrix_table[ 8 ][ 4 ] = {
    {1, 0, 0, 1}, {0, 1, 1, 0}, {0, -1, 1, 0}, {-1, 0, 0, 1}, {-1, 0, 0, -1}, {0, -1, -1, 0}, {0, 1, -1, 0}, {1, 0, 0, -1},
};

//
// Cast visiblity using shadowcasting.
//
static void level_fov_do(const short       distance_from_origin, // Polar distance_from_origin from POV.
                         float             view_slope_high,      //
                         float             view_slope_low,       //
                         const short       octant,               //
                         const FovContext &ctx)
{
  const short xx             = matrix_table[ octant ][ 0 ];
  const short xy             = matrix_table[ octant ][ 1 ];
  const short yx             = matrix_table[ octant ][ 2 ];
  const short yy             = matrix_table[ octant ][ 3 ];
  const short radius_squared = ctx.max_radius * ctx.max_radius;

  if (view_slope_high < view_slope_low) {
    return; // View is invalid.
  }

  if (distance_from_origin > ctx.max_radius) {
    return; // Distance is out-of-range.
  }

  if (is_oob(ctx.pov.x + (distance_from_origin * xy), ctx.pov.y + (distance_from_origin * yy))) [[unlikely]] {
    return; // Distance is out-of-bounds.
  }

  bool prev_tile_blocked = false;

  for (short angle = distance_from_origin; angle >= 0; --angle) { // Polar angle coordinates from high to low.
    const float tile_slope_high     = (angle + 0.5F) / (distance_from_origin - 0.5F);
    const float tile_slope_low      = (angle - 0.5F) / (distance_from_origin + 0.5F);
    const float prev_tile_slope_low = (angle + 0.5F) / (distance_from_origin + 0.5F);

    if (tile_slope_low > view_slope_high) {
      continue; // Tile is not in the view yet.
    }

    if (tile_slope_high < view_slope_low) {
      break; // Tiles will no longer be in view.
    }

    // Current tile is in view.
    const spoint p(ctx.pov.x + (angle * xx) + (distance_from_origin * xy), ctx.pov.y + (angle * yx) + (distance_from_origin * yy));

    if (is_oob(p)) [[unlikely]] {
      continue; // Angle is out-of-bounds.
    }

    //
    // Treat player and monster blocking differently so the player can use cover
    //
    auto light_blocker = level_light_blocker_at_cached(ctx.g, ctx.v, ctx.l, p);

    if ((angle * angle) + (distance_from_origin * distance_from_origin) <= radius_squared && (ctx.light_walls || ! light_blocker)) {

      if (ctx.fov_can_see_tile != nullptr) {
        //
        // Can see tile. If not seen already, light it
        //
        if (! fov_map_get(ctx.fov_can_see_tile, p.x, p.y)) {
          fov_map_set(ctx.fov_can_see_tile, p.x, p.y, 1u);

          //
          // Per tile can see callback check
          //
          if (ctx.can_see_callback != nullptr) {
            (ctx.can_see_callback)(ctx, p);
          }
        }
      } else {
        //
        // Can see tile. Could be a repeat of this tile.
        //
        if (ctx.can_see_callback != nullptr) {
          (ctx.can_see_callback)(ctx, p);
        }
      }

      if (ctx.fov_has_seen_tile != nullptr) {
        //
        // Has seen this tile
        //
        fov_map_set(ctx.fov_has_seen_tile, p.x, p.y, 1u);
      }
    }

    if (prev_tile_blocked && ! light_blocker) { // Wall -> floor.
      view_slope_high = prev_tile_slope_low;    // Reduce the view size.
    }

    if (! prev_tile_blocked && light_blocker) { // Floor -> wall.
      //
      // Get the last sequence of floors as a view and recurse into them.
      //
      level_fov_do(distance_from_origin + 1, // newline
                   view_slope_high,          // newline
                   tile_slope_high,          // newline
                   octant,                   // newline
                   ctx);
    }

    prev_tile_blocked = light_blocker;
  }

  if (! prev_tile_blocked) {
    //
    // Tail-recurse into the current view.
    //
    level_fov_do(distance_from_origin + 1, // newline
                 view_slope_high,          // newline
                 view_slope_low,           // newline
                 octant,                   // newline
                 ctx);
  }
}

void level_fov(const FovContext &ctx)
{
  TRACE();

  if (ctx.fov_can_see_tile != nullptr) {
    *ctx.fov_can_see_tile = {};
  }

  // recursive shadow casting
  for (int octant = 0; octant < 8; ++octant) {
    level_fov_do(1, 1.0, 0.0, octant, ctx);
  }

  if (ctx.fov_can_see_tile != nullptr) {
    //
    // If not seen already, light it
    //
    if (! fov_map_get(ctx.fov_can_see_tile, ctx.pov.x, ctx.pov.y)) {
      fov_map_set(ctx.fov_can_see_tile, ctx.pov.x, ctx.pov.y, 1u);

      //
      // Per tile can see callback check
      //
      if (ctx.can_see_callback != nullptr) {
        (ctx.can_see_callback)(ctx, ctx.pov);
      }
    }
  }

  if (ctx.fov_has_seen_tile != nullptr) {
    fov_map_set(ctx.fov_has_seen_tile, ctx.pov.x, ctx.pov.y, 1u);
  }
}
