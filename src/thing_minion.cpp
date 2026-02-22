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

#include <cstring>
#include <utility>

//
// Is this minion attached to a mob?
//
auto thing_minion_mob_get(Gamep g, Levelsp v, Levelp l, Thingp me) -> Thingp
{
  if (me == nullptr) {
    return nullptr;
  }

  if (! thing_is_minion(me)) {
    return nullptr;
  }

  if (me->mob_id == 0U) {
    return nullptr;
  }

  return thing_find(g, v, me->mob_id);
}

//
// Get the dmap associated with the mob
//
auto thing_minion_get_mob_dmap(Gamep g, Levelsp v, Levelp l, Thingp me) -> Dmap *
{
  TRACE_NO_INDENT();

  auto *mob = thing_minion_mob_get(g, v, l, me);
  if (mob == nullptr) {
    return nullptr; // can be normal if detached
  }

  auto *mob_ext = thing_ext_struct(g, mob);
  if (mob_ext == nullptr) {
    THING_ERR(me, "mob has no ext memory");
    return nullptr;
  }

  return &mob_ext->dmap;
}

//
// Detach a minion from its mob
//
auto thing_minion_detach_me_from_mob(Gamep g, Levelsp v, Levelp l, Thingp me) -> bool
{
  TRACE_NO_INDENT();

  if (me == nullptr) {
    return false;
  }

  if (! thing_is_minion(me)) {
    THING_ERR(me, "non minion trying to detach itself");
    return false;
  }

  auto *mob = thing_minion_mob_get(g, v, l, me);
  if (mob == nullptr) {
    return false; // can be normal if detached
  }

  THING_LOG(me, "detach me from mob");

  return thing_mob_detach_minion(g, v, l, mob, me);
}

//
// Collect all possible points we could wander to in the given dmap.
// The points are arranged in a radius around the dmap goal, which was
// what was presumably used to create the dmap.
//
[[nodiscard]] static auto thing_minion_get_mob_dmap_target_cand(Gamep g, Levelsp v, Levelp l, Thingp me,
                                                                spoint dmap_goal, Dmap *dmap, int radius,
                                                                spoint &target) -> bool
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

  if (target == dmap_goal) {
    return false;
  }

  if (target == thing_at(me)) {
    return false;
  }

  if (std::cmp_greater_equal(dmap->val[ target.x ][ target.y ], radius)) {
    return false;
  }

  if (! thing_can_move_to_ai(g, v, l, me, target)) {
    return false;
  }

  return true;
}

//
// Given a mob, choose somewhere to wander, near the mob.
//
auto thing_minion_choose_target_near_mob(Gamep g, Levelsp v, Levelp l, Thingp me) -> bool
{
  TRACE_NO_INDENT();

  auto *mob = thing_minion_mob_get(g, v, l, me);
  if (mob == nullptr) {
    THING_DBG(me, "choose target: no mob");
    return false; // can be normal if detached
  }

  auto *dmap = thing_minion_get_mob_dmap(g, v, l, me);
  if (dmap == nullptr) {
    THING_DBG(me, "choose target: no mob dmap");
    return false;
  }

  auto minion_at = thing_at(me);
  auto mob_at    = thing_at(mob);

  //
  // How far to look for a target?
  //
  auto radius = thing_distance_minion_from_mob_max(me);
  if (radius == 0) {
    THING_ERR(me, "unexpected value for radius");
    return false;
  }

  //
  // Keep trying to find a target
  //
  spoint target;
  int    tries = (radius * radius) / 2;
  while (tries-- > 0) {
    if (! thing_minion_get_mob_dmap_target_cand(g, v, l, me, mob_at, dmap, radius, target)) {
      continue;
    }

    auto p = astar_solve(g, v, l, me, minion_at, target);
    if (p.empty()) {
      continue;
    }

    if (thing_move_path_apply(g, v, l, me, p)) {
      thing_target_set(g, v, l, me, target);
      THING_DBG(me, "choose target: wander around mob");
      return true;
    }
  }

  return false;
}
