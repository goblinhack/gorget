//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_thing_inlines.hpp"
#include "my_tile.hpp"
#include "my_ui.hpp"

#include <cmath>

#include <array>
#include <cstring>

//
// Something blocking the fov?
//
auto level_light_blocker_at(Gamep g, Levelsp v, Levelp l, const spoint &pov) -> Thingp
{
  FOR_ALL_THINGS_AT_UNSAFE(g, v, l, it, pov)
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
      if (compiler_unused) {
        THING_LOG(it, "block");
      }
      return it;
    }
  }

  return nullptr;

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

//
// Something blocking the fov?
//
auto level_light_blocker_at_cached(Gamep g, Levelsp v, Levelp l, const spoint &p) -> bool
{
  return l->is_light_blocker_cache[ p.x ][ p.y ] != 0;
}

//
// Update all light blockers. This is done per tick to avoid having to redo this
// check for every monster during vision checks.
//
void level_light_blocker_update(Gamep g, Levelsp v, Levelp l)
{
  TRACE();

  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      if (level_light_blocker_at(g, v, l, spoint(x, y)) != nullptr) {
        l->is_light_blocker_cache[ x ][ y ] = 1U;
      } else {
        l->is_light_blocker_cache[ x ][ y ] = 0U;
      }
    }
  }
}
