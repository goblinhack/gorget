//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_dmap.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"

//
// Get the dmap associated with the thing
//
Dmap *thing_get_dmap(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();

  auto ext = thing_ext_struct(g, me);
  if (! ext) {
    THING_ERR(me, "mob has no ext memory");
    return nullptr;
  }

  return &ext->dmap;
}

//
// Create a dmap for a player, mob, monst etc... with the thing itself being the target.
// This serves as a way for monsters to reach the player, mob etc...
//
void thing_dmap(Gamep g, Levelsp v, Levelp l, Thingp me, bool reverse)
{
  TRACE_AND_INDENT();

  if (! thing_is_dmap(me)) {
    return;
  }

  uint8_t minx = 0;
  uint8_t miny = 0;
  uint8_t maxx = MAP_WIDTH - 1;
  uint8_t maxy = MAP_HEIGHT - 1;

  auto ext = thing_ext_struct(g, me);
  if (! ext) {
    return;
  }

  memset(&ext->dmap.val, DMAP_IS_PASSABLE, sizeof(ext->dmap));

  for (auto y = miny; y < maxy; y++) {
    for (auto x = minx; x < maxx; x++) {
      spoint p(x, y);

      if (! thing_can_move_to_check_only(g, v, l, me, p)) {
        ext->dmap.val[ x ][ y ] = DMAP_IS_WALL;
      }
    }
  }

  auto target = thing_at(me);
  if (reverse) {
    ext->dmap.val[ target.x ][ target.y ] = DMAP_IS_GOAL_REVERSE;
  } else {
    ext->dmap.val[ target.x ][ target.y ] = DMAP_IS_GOAL;
  }

  auto dmap_start = spoint(minx, miny);
  auto dmap_end   = spoint(maxx, maxy);

  if (0) {
    dmap_print(&ext->dmap, target, dmap_start, dmap_end);
  }

  if (reverse) {
    dmap_process_reverse(&ext->dmap, dmap_start, dmap_end);
  } else {
    dmap_process(&ext->dmap, dmap_start, dmap_end);
  }

  if (0) {
    THING_LOG(me, "thing dmap");
    dmap_print(&ext->dmap, target, dmap_start, dmap_end);
  }
}
