//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_thing_inlines.hpp"
#include "my_tile.hpp"
#include "my_ui.hpp"

#include <array>
#include <cmath>
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

    //
    // Submerged foliage does not block light
    //
    if (thing_submerged_pct(it) != 0) {
      continue;
    }

    if (thing_is_obs_to_vision(it)) {
      if (compiler_unused) {
        THING_DBG(it, "block");
      }
      return it;
    }
  }

  return nullptr;
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
