//
// Copyright goblinhack@gmail.com
//

#include "my_age_map_inlines.hpp"
#include "my_callstack.hpp"
#include "my_cpp_template.hpp"
#include "my_fov_map_inlines.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp"
#include "my_line.hpp"
#include "my_main.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_wid_warning.hpp"

//
// Can we chase the player?
//
static auto thing_monst_choose_target_player(Gamep g, Levelsp v, Levelp l, Thingp me) -> bool
{
  TRACE();

  auto *player = thing_player(g);
  if (player == nullptr) [[unlikely]] {
    return false;
  }

  auto *player_level = game_level_get(g, v, player->level_num);
  auto *monst_level  = game_level_get(g, v, me->level_num);
  if (player_level != monst_level) {
    THING_DBG(me, "choose target: different level from player");
    return false;
  }

  auto target = thing_at(player);
  if (! thing_vision_can_see_tile(g, v, l, me, target)) {
    THING_DBG(me, "choose target: cannot see player");
    return false;
  }

  auto monst_at = thing_at(me);
  auto dist     = distance(monst_at, target);
  auto v_dist   = thing_distance_vision(me);
  if (v_dist == 0) {
    thing_err(me, "choose target: monst has no vision distance");
    return false;
  }

  if (dist > v_dist) {
    THING_DBG(me, "choose target: player is too far (player %f) (vision %d)", dist, v_dist);
    return false;
  }

  auto p = astar_solve(g, v, l, me, monst_at, target);
  if (p.empty()) {
    THING_DBG(me, "choose target: no path to player at %d,%d", target.x, target.y);
    return false;
  }

  if (thing_move_path_apply(g, v, l, me, p)) {
    thing_target_set(g, v, l, me, target);
    THING_DBG(me, "choose target: found path to player");
    return true;
  }

  THING_DBG(me, "choose target: failed to apply path to player");
  return false;
}

//
// Choose somewhere random that we can see
//
static auto thing_minion_choose_target_can_see(Gamep g, Levelsp v, Levelp l, Thingp me) -> bool
{
  TRACE();

  auto at = thing_at(me);

  auto *ext = thing_ext_struct(g, me);
  if (ext == nullptr) {
    thing_err(me, "no ext pointer");
    return false;
  }

  auto *mob = thing_minion_mob_get(g, v, l, me);

  //
  // How far to look for a target? We want to look beyond normal vision
  // when wandering as we want to explore uncharted areas
  //
  int radius = 0;
  if (mob == nullptr) {
    radius = thing_distance_vision(me) * 2;
  } else {
    radius = thing_distance_minion_from_mob_max(me);
  }

  if (radius == 0) {
    thing_err(me, "unexpected value for radius");
    return false;
  }

  auto radius_sq = radius * radius;
  auto tries     = 0;
  auto max_tries = 100;

  int  best_lowest_score = 999999;
  bool found_path        = false;

  //
  // Keep trying to find a target
  //
  while (tries++ < max_tries) {
    uint8_t x = 0;
    uint8_t y = 0;

    //
    // Get a valid tile.
    //
    do {
      x = at.x - radius + PCG_RANDOM_RANGE(0, radius_sq);
      y = at.y - radius + PCG_RANDOM_RANGE(0, radius_sq);
    } while (is_oob_or_border(x, y));

    spoint const target(x, y);

    //
    // Check this is a tile we want to potentially walk to.
    // Just because we can see it, doesn't mean it's somewhere we want to go.
    //
    if (! thing_can_move_to_ai(g, v, l, me, target)) {
      continue;
    }

    //
    // If we get here for a minion, make sure the minion stays close to the mob
    //
    if (mob != nullptr) {
      if (distance(target, thing_at(mob)) >= thing_distance_minion_from_mob_max(me)) {
        continue;
      }
    }

    //
    // Prefer older tiles, so the monster explores more
    //
    int score = age_map_get(&ext->has_seen, x, y) * 100;

    //
    // Prefer further away tiles for exploration
    //
    score += 100 - static_cast< int >(distance(target, at));

    if (score >= best_lowest_score) {
      continue;
    }

    auto p = astar_solve(g, v, l, me, at, target);
    if (p.empty()) {
      continue;
    }

    if (! thing_move_path_apply(g, v, l, me, p)) {
      continue;
    }

    if (compiler_unused) {
      THING_DBG(me, "best %d,%d score %d", x, y, score);
    }

    thing_target_set(g, v, l, me, target);
    best_lowest_score = score;
    found_path        = true;
  }

  return found_path;
}

//
// Return true on a successful move (or a popup asking more info)
//
[[nodiscard]] static auto thing_monst_move_try(Gamep g, Levelsp v, Levelp l, Thingp me, spoint to) -> bool
{
  THING_DBG(me, "move try");

  if (thing_can_move_to_attempt(g, v, l, me, to)) {
    return true;
  }

  if (thing_can_move_to_attempt_by_shoving(g, v, l, me, to)) {
    //
    // Can we shove it out of the way to move?
    //
    THING_DBG(me, "move try: can move to by shoving");

    if (thing_shove_to(g, v, l, me, to)) {
      //
      // Do not step onto the thing we just shoved.
      //
      return level_is_dead_on_shoving(g, v, l, to) == nullptr;
    }
  }

  if (thing_can_move_to_attempt_by_opening(g, v, l, me, to)) {
    //
    // Can we open it allow movement?
    //
    THING_DBG(me, "move try: can move to by opening");

    if (thing_move_to(g, v, l, me, to)) {
      return true;
    }
  }

  //
  // Bumped into obstacle
  //
  return false;
}

//
// Move to the next path on the popped path if it exits.
//
[[nodiscard]] static auto thing_monst_move_to_next(Gamep g, Levelsp v, Levelp l, Thingp me) -> bool
{
  TRACE();
  THING_DBG(me, "move to next");

  //
  // If already moving, do not pop the next path tile
  //
  if (thing_is_moving(me)) {
    THING_DBG(me, "move to next: already moving");
    return false;
  }

  //
  // Get the next tile to move to
  //
  spoint move_next = {};
  if (! thing_move_path_pop(g, v, l, me, move_next)) {
    //
    // If could not pop, then no path is left
    //
    THING_DBG(me, "move to next: no move path to pop");
    return false;
  }

  spoint move_destination = {};
  if (thing_move_path_target(g, v, l, me, move_destination)) {
    if (! thing_can_move_to_possible(g, v, l, me, move_next)) {
      if (thing_jump_to(g, v, l, me, move_destination)) {
        //
        // If could jump, then abort the path walk
        //
        THING_DBG(me, "move to next: jump");
        return false;
      }

      //
      // Something was in the way of jumping. Best to stop rather than accidentally
      // walk into a chasm.
      //
      (void) thing_lunge(g, v, l, me, move_next);
      THING_DBG(me, "move to next: something in the way");
      return false;
    }
  }

  if (! thing_monst_move_try(g, v, l, me, move_next)) {
    //
    // If could not move, then abort the path walk
    //
    THING_DBG(me, "move to next: could not move");
    return false;
  }

  return thing_move_to(g, v, l, me, move_next);
}

[[nodiscard]] static auto thing_monst_choose_target(Gamep g, Levelsp v, Levelp l, Thingp me) -> bool
{
  TRACE();

  if (compiler_unused) {
    thing_can_see_dump(g, v, l, me);
  }

  if (thing_monst_choose_target_player(g, v, l, me)) {
    monst_state_change(g, v, l, me, MONST_STATE_CHASING);
    return true;
  }

  if (thing_is_minion(me)) {
    if (thing_minion_choose_target_near_mob(g, v, l, me)) {
      monst_state_change(g, v, l, me, MONST_STATE_WANDER);
      return true;
    }
  }

  if (thing_minion_choose_target_can_see(g, v, l, me)) {
    monst_state_change(g, v, l, me, MONST_STATE_WANDER);
    return true;
  }

  THING_DBG(me, "choose target: none");

  return false;
}

//
// Called per tick
//
void thing_monst_event_loop(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE();

  //
  // Early state check
  //
  switch (monst_state(g, v, l, me)) {
    case MONST_STATE_INIT : //
      monst_state_change(g, v, l, me, MONST_STATE_NORMAL);
      [[fallthrough]];
    case MONST_STATE_NORMAL : //
      (void) thing_monst_choose_target(g, v, l, me);
      break;
    case MONST_STATE_DEAD :
      //
      break;
    case MONST_STATE_CHASING :
      //
      // Might need to rething the target if it has moved. If we can no longer
      // see the player, keep going as it might have moved and we could be able
      // to see them again.
      //
      if (! thing_monst_choose_target_player(g, v, l, me)) {
        THING_DBG(me, "lost target, but keep going");
      }
      break;
    case MONST_STATE_WANDER :
      //
      // While wandering, if we see the player, change direction, but keep wandering
      // to the original target if we can't reach them
      //
      if (thing_monst_choose_target_player(g, v, l, me)) {
        THING_DBG(me, "sighted player");
        monst_state_change(g, v, l, me, MONST_STATE_CHASING);
      }
      break;
    case MONST_STATE_ENUM_MAX : break;
  }

  //
  // Post thinking state check
  //
  switch (monst_state(g, v, l, me)) {
    case MONST_STATE_INIT : //
      break;
    case MONST_STATE_NORMAL : //
      break;
    case MONST_STATE_DEAD :
      //
      break;
    case MONST_STATE_CHASING : [[fallthrough]];
    case MONST_STATE_WANDER :
      //
      // If we are unable to move, or we reach the target, move back
      // to normal state so we can decide what to do.
      //
      if (! thing_monst_move_to_next(g, v, l, me)) {
        THING_DBG(me, "end of move");
        monst_state_change(g, v, l, me, MONST_STATE_NORMAL);

        //
        // To avoid one move of sitting idle, can we choose a new target and
        // keep on moving?
        //
        if (thing_monst_choose_target(g, v, l, me)) {
          (void) thing_monst_move_to_next(g, v, l, me);
        }
      }
      break;
    case MONST_STATE_ENUM_MAX : break;
  }
}

auto monst_state_to_string(MonstState state) -> std::string
{
  TRACE();
  return MonstState_to_string(state);
}

auto monst_state(Gamep g, Levelsp v, Levelp l, Thingp me) -> MonstState
{
  TRACE();
  return me->_monst_state;
}

void monst_state_change(Gamep g, Levelsp v, Levelp l, Thingp me, MonstState new_state)
{
  TRACE();

  auto old_state = me->_monst_state;

  switch (old_state) {
    case MONST_STATE_INIT :
      //
      break;
    case MONST_STATE_DEAD :
      //
      return;
    case MONST_STATE_NORMAL :
      //
      break;
    case MONST_STATE_CHASING :
      //
      break;
    case MONST_STATE_WANDER :
      //
      break;
    case MONST_STATE_ENUM_MAX : break;
  }

  if (me->_monst_state == new_state) {
    return;
  }

  //
  // Set here to stop recursion.
  //
  me->_monst_state = new_state;

  //
  // Why oh why change state
  //
  IF_DEBUG { THING_DBG(me, "state change: %s -> %s", monst_state_to_string(old_state).c_str(), monst_state_to_string(new_state).c_str()); }

  switch (new_state) {
    case MONST_STATE_INIT :
      //
      break;
    case MONST_STATE_DEAD :
      //
      break;
    case MONST_STATE_NORMAL :
      //
      break;
    case MONST_STATE_CHASING :
      //
      break;
    case MONST_STATE_WANDER :
      //
      break;
    case MONST_STATE_ENUM_MAX : break;
  }

  (void) thing_move_remaining_set(g, v, l, me, 0);
}

//
// Called at the beginning of each tick and whenever the move_remaining
// count exceeds the players speed and there is still some level tick to go.
//
void thing_monst_tick(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE();

  if (thing_is_dead(me)) {
    return;
  }

  if (! thing_is_monst(me)) {
    return;
  }

  if (! level_is_player_level(g, v, l)) {
    return;
  }

  auto *player = thing_player(g);
  if (player == nullptr) [[unlikely]] {
    return;
  }

  const int player_speed = thing_speed(player);

  if (compiler_unused) {
    THING_DBG(me, "move_rem %d dt %f", thing_move_remaining(me), me->thing_dt);
  }

  //
  // Give the thing more ability to move
  //
  auto m = thing_move_remaining_incr(g, v, l, me, thing_speed(me));
  if (m >= player_speed) {
    (void) thing_move_remaining_decr(g, v, l, me, player_speed);

    thing_monst_event_loop(g, v, l, me);
  }
}
