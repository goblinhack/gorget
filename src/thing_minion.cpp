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
Thingp thing_minion_mob_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  if (! t) {
    return nullptr;
  }

  if (! thing_is_minion(t)) {
    return nullptr;
  }

  if (! t->mob_id) {
    return nullptr;
  }

  return thing_find(g, v, t->mob_id);
}

//
// Get the dmap associated with the mob
//
Dmap *thing_minion_get_mob_dmap(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // Acceptable to fail when the minion is detached
  //
  auto mob = thing_minion_mob_get(g, v, l, t);
  if (! mob) {
    return nullptr;
  }

  auto mob_ext = thing_ext_struct(g, mob);
  if (! mob_ext) {
    THING_ERR(t, "mob has no ext memory");
    return nullptr;
  }

  return &mob_ext->dmap;
}

//
// Detach a minion from its mob
//
bool thing_minion_detach_me_from_mob(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (! t) {
    return false;
  }

  if (! thing_is_minion(t)) {
    THING_ERR(t, "non minion trying to detach itself");
    return false;
  }

  auto mob = thing_minion_mob_get(g, v, l, t);
  if (! mob) {
    return false;
  }

  THING_LOG(t, "detach me from mob");

  return thing_mob_detach_minion(g, v, l, mob, t);
}

//
// Collect all possible points we could wander to in the given dmap.
// The points are arranged in a radius around the dmap goal, which was
// what was presumably used to create the dmap.
//
[[nodiscard]] static std::vector< spoint > thing_minion_get_mob_dmap_target_cands(Gamep g, Levelsp v, Levelp l,
                                                                                  Thingp t, spoint dmap_goal,
                                                                                  Dmap *dmap, int radius)
{
  TRACE_NO_INDENT();

  std::vector< spoint > cands;
  auto                  at = thing_at(t);

  //
  // Look at tiles surrounding the mob for somewhere to wander to
  //
  for (int x = -radius; x <= radius; x++) {
    for (int y = -radius; y <= radius; y++) {
      spoint p(x + dmap_goal.x, y + dmap_goal.y);
      if (is_oob(p)) {
        continue;
      }

      if (p == at) {
        continue;
      }

      if (p == dmap_goal) {
        continue;
      }

      if (level_is_obs_to_movement(g, v, l, p)) {
        continue;
      }

      if (level_is_monst(g, v, l, p)) {
        continue;
      }

      if (dmap->val[ p.x ][ p.y ] >= radius) {
        continue;
      }

      cands.push_back(p);
    }
  }
  return cands;
}

//
// Given a mob, choose somewhere to wander, near the mob.
//
bool thing_minion_choose_target_near_mob(Gamep g, Levelsp v, Levelp l, Thingp t, spoint &target)
{
  TRACE_NO_INDENT();

  auto mob = thing_minion_mob_get(g, v, l, t);
  if (! mob) {
    return false;
  }

  auto dmap = thing_minion_get_mob_dmap(g, v, l, t);
  if (! dmap) {
    return false;
  }

  auto minion_at = thing_at(t);
  auto mob_at    = thing_at(mob);
  auto radius    = thing_distance_minion_from_mob_max(t);
  auto cands     = thing_minion_get_mob_dmap_target_cands(g, v, l, t, mob_at, dmap, radius);
  auto tries     = cands.size();

  while (tries-- > 0) {
    target = pcg_rand_one_of(cands);

    auto p = thing_astar_solve(g, v, l, t, minion_at, target);
    if (! p.size()) {
      continue;
    }

    thing_monst_apply_path(g, v, l, t, p);
    break;
  }

  if (tries <= 0) {
    return false;
  }

  return true;
}
