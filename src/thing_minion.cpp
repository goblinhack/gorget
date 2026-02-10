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

  auto mob = thing_minion_mob_get(g, v, l, t);
  if (! mob) {
    return nullptr; // can be normal if detached
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
    return false; // can be normal if detached
  }

  THING_LOG(t, "detach me from mob");

  return thing_mob_detach_minion(g, v, l, mob, t);
}

//
// Collect all possible points we could wander to in the given dmap.
// The points are arranged in a radius around the dmap goal, which was
// what was presumably used to create the dmap.
//
[[nodiscard]] static bool thing_minion_get_mob_dmap_target_cand(Gamep g, Levelsp v, Levelp l, Thingp t,
                                                                spoint dmap_goal, Dmap *dmap, int radius,
                                                                spoint &target)
{
  TRACE_NO_INDENT();

  //
  // Look at tiles surrounding the mob for somewhere to wander to
  //
  target.x = dmap_goal.x - radius + pcg_random_range(0, radius * 2);
  target.y = dmap_goal.y - radius + pcg_random_range(0, radius * 2);

  if (is_oob(target)) {
    return false;
  }

  if (target == thing_at(t)) {
    return false;
  }

  if (target == dmap_goal) {
    return false;
  }

  if (level_is_obs_to_movement(g, v, l, target)) {
    return false;
  }

  if (level_is_monst(g, v, l, target)) {
    return false;
  }

  if (dmap->val[ target.x ][ target.y ] >= radius) {
    return false;
  }

  return true;
}

//
// Given a mob, choose somewhere to wander, near the mob.
//
bool thing_minion_choose_target_near_mob(Gamep g, Levelsp v, Levelp l, Thingp t, spoint &target)
{
  TRACE_NO_INDENT();

  auto mob = thing_minion_mob_get(g, v, l, t);
  if (! mob) {
    return false; // can be normal if detached
  }

  auto dmap = thing_minion_get_mob_dmap(g, v, l, t);
  if (! dmap) {
    THING_ERR(t, "attached minion has no mob");
    return false;
  }

  auto minion_at = thing_at(t);
  auto mob_at    = thing_at(mob);

  //
  // How far to look for a target?
  //
  auto radius = thing_distance_minion_from_mob_max(t);
  if (! radius) {
    THING_ERR(t, "unexpected value for radius");
    return false;
  }

  //
  // Keep trying to find a target
  //
  int tries = (radius * radius) / 2;
  while (tries-- > 0) {
    if (! thing_minion_get_mob_dmap_target_cand(g, v, l, t, mob_at, dmap, radius, target)) {
      continue;
    }

    auto p = thing_astar_solve(g, v, l, t, minion_at, target);
    if (! p.size()) {
      continue;
    }

    if (! thing_monst_apply_path(g, v, l, t, p)) {
      continue;
    }
    return true;
  }

  return false;
}
