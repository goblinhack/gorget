//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_dmap.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"

//
// Create a dmap for a player, mob, monst etc... with the thing itself being the target.
// This serves as a way for monsters to reach the player, mob etc...
//
void thing_dmap(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_AND_INDENT();

  if (! thing_is_dmap(t)) {
    return;
  }

  uint8_t minx = 0;
  uint8_t miny = 0;
  uint8_t maxx = MAP_WIDTH - 1;
  uint8_t maxy = MAP_HEIGHT - 1;

  auto ext = thing_ext_struct(g, t);
  if (! ext) {
    return;
  }

  memset(&ext->dmap.val, DMAP_IS_PASSABLE, sizeof(ext->dmap));

  for (auto y = miny; y < maxy; y++) {
    for (auto x = minx; x < maxx; x++) {
      spoint p(x, y);
      if (level_is_obs_to_movement(g, v, l, p)) {
        ext->dmap.val[ x ][ y ] = DMAP_IS_WALL;
      }
    }
  }

  auto target                           = thing_at(t);
  ext->dmap.val[ target.x ][ target.y ] = DMAP_IS_GOAL;

  auto dmap_start = spoint(minx, miny);
  auto dmap_end   = spoint(maxx, maxy);

  if (0) {
    dmap_print(&ext->dmap, target, dmap_start, dmap_end);
  }
  dmap_process(&ext->dmap, dmap_start, dmap_end);
  if (0) {
    dmap_print(&ext->dmap, target, dmap_start, dmap_end);
  }
}
