//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_cpp_template.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_line.hpp"
#include "my_main.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_wid_warning.hpp"

#include <string.h>

//
// Is this minion attached to a mob?
//
Thingp thing_minion_mob_get(Gamep g, Levelsp v, Levelp l, Thingp minion)
{
  if (! minion) {
    return nullptr;
  }

  if (! thing_is_minion(minion)) {
    return nullptr;
  }

  if (! minion->mob_id) {
    return nullptr;
  }

  return thing_find(g, v, minion->mob_id);
}

//
// Detach a minion from its mob
//
bool thing_minion_detach_me_from_mob(Gamep g, Levelsp v, Levelp l, Thingp minion)
{
  TRACE_NO_INDENT();

  if (! minion) {
    return false;
  }

  if (! thing_is_minion(minion)) {
    THING_ERR(minion, "non minion trying to detach itself");
    return false;
  }

  auto mob = thing_minion_mob_get(g, v, l, minion);
  if (! mob) {
    return false;
  }

  THING_LOG(minion, "detach me from mob");

  return thing_mob_detach_minion(g, v, l, mob, minion);
}

bool thing_minion_choose_target_near_mob(Gamep g, Levelsp v, Levelp l, Thingp minion, spoint &target)
{
  TRACE_NO_INDENT();

  auto mob = thing_minion_mob_get(g, v, l, minion);
  if (! mob) {
    //
    // Acceptable when the minion is detached
    //
    return false;
  }

  auto mob_ext = thing_ext_struct(g, mob);
  if (! mob_ext) {
    THING_ERR(minion, "mob has no ext memory");
    return false;
  }

  auto                  minion_at = thing_at(minion);
  auto                  mob_at    = thing_at(mob);
  std::vector< spoint > cands;

  auto dmap = &mob_ext->dmap;

  if (0) {
    THING_LOG(mob, "mob");
    dmap_print(dmap, mob_at, spoint(0, 0), spoint(MAP_WIDTH - 1, MAP_HEIGHT - 1));
  }

  //
  // Look at tiles surrounding the mob, for somewhere to wander to
  //
  auto distance_minion_from_mob_max = thing_distance_minion_from_mob_max(minion);
  for (int x = -distance_minion_from_mob_max; x <= distance_minion_from_mob_max; x++) {
    for (int y = -distance_minion_from_mob_max; y <= distance_minion_from_mob_max; y++) {
      spoint p(x + mob_at.x, y + mob_at.y);
      if (is_oob(p)) {
        continue;
      }

      if (p == minion_at) {
        continue;
      }

      if (p == mob_at) {
        continue;
      }

      if (level_is_obs_to_movement(g, v, l, p)) {
        continue;
      }

      if (level_is_monst(g, v, l, p)) {
        continue;
      }

      if (dmap->val[ p.x ][ p.y ] >= distance_minion_from_mob_max) {
        continue;
      }

      cands.push_back(p);
    }
  }

  if (! cands.size()) {
    return false;
  }

  auto tries = cands.size();
  while (tries--) {
    target = pcg_rand_one_of(cands);

    thing_astar_solve(g, v, l, minion, minion_at, target);
#if 0
    auto p         = dmap_solve(g, v, l, minon, dmap, minion_at);
    auto path_size = p.size();
    if (! path_size) {
      return empty;
    }

    //
    // If we could not reach the target, then the path will just plot the distance from the start, which is not what
    // we want.
    //
    if (p[ path_size - 1 ] != end) {
      if (0) {
        LOG("did not reach %d,%d", end.x, end.y);
      }
      return empty;
    }
#endif
  }

  if (0) {
    THING_LOG(minion, "%s", __FUNCTION__);
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      std::string out;
      for (auto x = 0; x < MAP_WIDTH; x++) {
        char   c = {};
        spoint p(x, y);

        if (! c && (p == target)) {
          c = '*';
        }

        if (! c) {
          for (auto cand : cands) {
            if (p == cand) {
              c = '_';
              break;
            }
          }
        }

        if (! c && (p == minion_at)) {
          c = '@';
        }
        if (! c && (p == mob_at)) {
          c = 'G';
        }
        if (! c && level_is_obs_to_movement(g, v, l, p)) {
          c = 'X';
        }
        if (! c && level_is_monst(g, v, l, p)) {
          c = 'm';
        }
        if ((p == mob_at)) {
          c = 'G';
        }
        if (! c) {
          c = '.';
        }
        out += c;
      }
      THING_LOG(minion, "%s", out.c_str());
    }
  }

  return true;
}
