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
auto thing_get_dmap(Gamep g, Levelsp v, Levelp l, Thingp me) -> Dmap *
{
  TRACE();

  auto *ext = thing_ext_struct(g, me);
  UNLIKELY if (ext == nullptr) {
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
  if (! thing_is_dmap(me)) {
    return;
  }

  TRACE();

  uint8_t const minx = 0;
  uint8_t const miny = 0;
  uint8_t const maxx = MAP_WIDTH - 1;
  uint8_t const maxy = MAP_HEIGHT - 1;

  auto *ext = thing_ext_struct(g, me);
  UNLIKELY if (ext == nullptr) {
    return;
  }

  memset(&ext->dmap.val, DMAP_IS_PASSABLE, sizeof(ext->dmap));

  for (auto y = miny; y < maxy; y++) {
    for (auto x = minx; x < maxx; x++) {
      spoint const p(x, y);

      if (! thing_can_move_to_ai(g, v, l, me, p)) {
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

  if (compiler_unused) {
    dmap_print(&ext->dmap, target, dmap_start, dmap_end);
  }

  if (reverse) {
    dmap_process_reverse(&ext->dmap, dmap_start, dmap_end);
  } else {
    dmap_process(&ext->dmap, dmap_start, dmap_end);
  }

  if (compiler_unused) {
    THING_LOG(me, "thing dmap");
    dmap_print(&ext->dmap, target, dmap_start, dmap_end);
  }
}
