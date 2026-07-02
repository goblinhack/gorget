//
// Copyright goblinhack@gmail.com
//

#include "my_age_map_inlines.hpp"
#include "my_bpoint.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_game_defs.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"
#include <string>

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

  if (compiler_unused) {
    thing_can_see_dump(g, v, l, me);
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
    if (thing_vision_can_hear_tile(g, v, l, me, thing_at(me))) {
      THING_DBG(me, "choose target: can hear player");
    } else {
      THING_DBG(me, "choose target: cannot hear player");
      return false;
    }
  }
  THING_DBG(me, "choose target: can see player");

  auto monst_at = thing_at(me);
  auto dist     = distance(monst_at, target);
  auto v_dist   = thing_distance_vision(g, v, l, me);
  if (v_dist == 0) {
    thing_err(me, "choose target: monst has no vision distance");
    return false;
  }

  if (dist > v_dist) {
    THING_DBG(me, "choose target: player is too far (player %f) (vision %d)", dist, v_dist);
    return false;
  }

  if (dist < thing_distance_avoid_target(me)) {
    THING_DBG(me, "choose target: player is too close (player %f) (vision %d)", dist, v_dist);

    //
    // Can we attack here?
    //
    if (dist <= 1) {
      if (level_is_attackable_by_monst(g, v, l, target) != nullptr) {
        if (thing_attack_at(g, v, l, me, target)) {
          THING_DBG(me, "close attack");
          monst_state_change(g, v, l, me, MONST_STATE_NORMAL);
        }
      }
    }

    return false;
  }

  THING_DBG(me, "astar thing_monst_choose_target_player");
  auto p = astar_solve(g, v, l, me, monst_at, target);
  if (p.empty()) {
    THING_DBG(me, "choose target: no path to player at (%d,%d)", target.x, target.y);
    return false;
  }

  //
  // Some monsters don't like to get too close
  //
  auto d = thing_distance_avoid_target(me);
  while (d-- > 0) {
    p.pop_back();
  }

  if (thing_move_path_apply(g, v, l, me, p)) {
    thing_monst_target_set(g, v, l, me, target);
    THING_DBG(me, "choose target: found path to player");
    return true;
  }

  THING_DBG(me, "choose target: failed to apply path to player");
  return false;
}

//
// Choose somewhere random that we can see
//
static auto thing_monst_choose_something_we_can_see(Gamep g, Levelsp v, Levelp l, Thingp me) -> bool
{
  THING_DBG(me, "choose target: can see");
  TRACE_INDENT();

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
    radius = thing_distance_vision(g, v, l, me) * 2;
  } else {
    radius = thing_distance_minion_from_mob_max(g, v, l, me);
  }

  THING_DBG(me, "choose target: radius: %d", radius);
  TRACE_INDENT();

  if (radius == 0) {
    thing_err(me, "unexpected value for radius");
    return false;
  }

  auto diameter  = radius * 2;
  auto tries     = 0;
  auto max_tries = 100;

  int  best_lowest_score = 999999;
  bool found_path        = false;

  //
  // Could avoid memsetting this by using uninitialized memory but
  // it means the tests are not deterministic
  //
  bool tried[ MAP_WIDTH ][ MAP_HEIGHT ] = {{0}};

  //
  // Keep trying to find a target
  //
  while (tries++ < max_tries) {
    bpoint target;

    //
    // Get a valid tile.
    //
    target.x = static_cast< int >(at.x) - radius + PCG_RANDOM_RANGE(0, diameter);
    target.y = static_cast< int >(at.y) - radius + PCG_RANDOM_RANGE(0, diameter);

    THING_DBG(me, "choose target: try: (%d,%d)", target.x, target.y);
    TRACE_INDENT();

    if (is_oob_or_border(target)) {
      continue;
    }

    if (tried[ target.x ][ target.y ]) {
      continue;
    }
    tried[ target.x ][ target.y ] = true;

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
      if (distance(target, thing_at(mob)) >= thing_distance_minion_from_mob_max(g, v, l, me)) {
        continue;
      }
    }

    //
    // Prefer older tiles, so the monster explores more
    //
    int score = age_map_get(&ext->has_seen, target.x, target.y) * 100;

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
      THING_DBG(me, "best %d,%d score %d", target.x, target.y, score);
    }

    thing_monst_target_set(g, v, l, me, target);
    best_lowest_score = score;
    found_path        = true;
    break;
  }

  return found_path;
}

//
// Return true on a successful move (or a popup asking more info)
//
[[nodiscard]] static auto thing_monst_move_try(Gamep g, Levelsp v, Levelp l, Thingp me, bpoint to) -> bool
{
  THING_DBG(me, "move try");

  auto at = thing_at(me);

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
  // Can it jump there?
  //
  if (! adjacent(at, to)) {
    if (thing_jump_to(g, v, l, me, to, false)) {
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

  auto target = thing_monst_target(me);
  THING_DBG(me, "move to next, target (%d,%d)", target.x, target.y);
  TRACE_INDENT();

  auto at = thing_at(me);

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
  bpoint nexthop = {};

  if (! thing_move_path_pop(g, v, l, me, nexthop)) {
    //
    // If could not pop, then no path is left
    //
    THING_DBG(me, "move to next: no move path to pop");
    return false;
  }

  THING_DBG(me, "move to next: nexthop (%d,%d)", nexthop.x, nexthop.y);
  TRACE_INDENT();

  //
  // If we have remaining moves and it is not possible to move to the next tile
  // then we pop moves off of the path to see if we can reach any of them
  //
  if (thing_move_path_size(g, v, l, me) != 0) {
    if (thing_can_move_to_ai(g, v, l, me, nexthop)) {
      THING_DBG(me, "nexthop allowed by ai");
    } else {
      THING_DBG(me, "nexthop blocked by ai (remaining path size %d)", thing_move_path_size(g, v, l, me));
      TRACE_INDENT();

      while (thing_move_path_pop(g, v, l, me, nexthop)) {
        THING_DBG(me, "pop nexthop (%d,%d)", nexthop.x, nexthop.y);
        TRACE_INDENT();

        //
        // Need to check the truncated path isn't something we don't like, like lava
        //
        if (thing_can_move_to_ai(g, v, l, me, nexthop)) {
          THING_DBG(me, "nexthop (%d,%d) allowed by ai", nexthop.x, nexthop.y);
          TRACE_INDENT();

          if (adjacent(at, nexthop)) {
            if (thing_move_to(g, v, l, me, nexthop)) {
              //
              // If could jump, then abort the path walk
              //
              THING_DBG(me, "moved to nexthop");
              return false;
            }
          } else {
            if (thing_jump_to(g, v, l, me, nexthop)) {
              //
              // If could jump, then abort the path walk
              //
              THING_DBG(me, "jumped to nexthop");
              return false;
            }
          }
        } else {
          THING_DBG(me, "nexthop (%d,%d) blocked by ai", nexthop.x, nexthop.y);
        }
      }

      //
      // Something was in the way of jumping. Best to stop rather than accidentally
      // walk into a chasm.
      //
      THING_DBG(me, "move to next: not possible, lunge");
      (void) thing_lunge(g, v, l, me, nexthop);
      return false;
    }
  }

  if (! thing_monst_move_try(g, v, l, me, nexthop)) {
    //
    // If could not move, then abort the path walk
    //
    THING_DBG(me, "move to next: could not move");
    return false;
  }

  if (! thing_is_floating(me)) {
    if (thing_is_able_to_throw_items(me)) {
      //
      // Jump over chasm?
      //
      if (level_is_chasm_bool(g, v, l, nexthop)) {
        return thing_jump_to(g, v, l, me, target);
      }

      //
      // Jump over lava or something else we hate?
      //
      switch (thing_assess_tile(g, v, l, nexthop, me)) {
        case THING_ENVIRON_HATES :    return thing_jump_to(g, v, l, me, target);
        case THING_ENVIRON_DISLIKES : break;
        case THING_ENVIRON_NEUTRAL :  break;
        case THING_ENVIRON_LIKES :    break;
        case THING_ENVIRON_ENUM_MAX : break;
      }
    }
  }

  return thing_move_to(g, v, l, me, nexthop);
}

[[nodiscard]] static auto thing_monst_choose_target(Gamep g, Levelsp v, Levelp l, Thingp me) -> bool
{
  THING_DBG(me, "choose target");
  TRACE_INDENT();

  if (thing_is_jumping(me)) {
    THING_DBG(me, "choose target: wait for jump to complete");
    return true;
  }

  if (thing_monst_choose_target_player(g, v, l, me)) {
    THING_DBG(me, "choose target: found player");
    monst_state_change(g, v, l, me, MONST_STATE_CHASING);
    return true;
  }

  if (thing_is_minion(me)) {
    THING_DBG(me, "choose target: one near mob?");
    TRACE_INDENT();
    if (thing_minion_choose_target_near_mob(g, v, l, me)) {
      THING_DBG(me, "choose target: minion found target near mob");
      monst_state_change(g, v, l, me, MONST_STATE_WANDER);
      return true;
    }
  }

  THING_DBG(me, "choose target: one we can see?");
  if (thing_monst_choose_something_we_can_see(g, v, l, me)) {
    TRACE_INDENT();
    THING_DBG(me, "choose target: monst found a target it can see");
    monst_state_change(g, v, l, me, MONST_STATE_WANDER);
    return true;
  }

  THING_DBG(me, "choose target: none");

  return false;
}

//
// Called multiple times per tick potentially. If the monster has enough
// move_remaining then it can move or attack again.
//
void thing_monst_event_loop(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  THING_DBG(me, "monst event loop, move_rem %d", thing_move_remaining(me));
  TRACE_INDENT();

  auto *player = thing_player(g);
  if (player == nullptr) {
    return;
  }

  const int player_speed = thing_speed(player);
  if (thing_move_remaining(me) < player_speed) {
    THING_DBG(me, "no more moves this tick, move_rem %d", thing_move_remaining(me));
    return;
  }

  (void) thing_move_remaining_decr(g, v, l, me, player_speed);
  THING_DBG(me, "move_rem %d", thing_move_remaining(me));

  if (compiler_unused) {
    thing_can_see_dump(g, v, l, me);
  }

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
  auto old_target = thing_monst_target(me);
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
      // If we are unable to move, or we reach the target, move back to normal state so we can decide what to do.
      //
      if (! thing_monst_move_to_next(g, v, l, me)) {
        THING_DBG(me, "end of move, old target (%d,%d)", old_target.x, old_target.y);

        monst_state_change(g, v, l, me, MONST_STATE_NORMAL);

        //
        // To avoid one move of sitting idle, can we choose a new target and keep on moving?
        //
        auto at = thing_at(me);
        if ((at == old_target) || adjacent(at, old_target)) {
          //
          // We're probably lunging at the player right now. No need to try to move again.
          //
          THING_DBG(me, "end of move: adjacent to target");

          //
          // Can we attack here?
          //
          if (level_is_attackable_by_monst(g, v, l, old_target) != nullptr) {
            if (thing_attack_at(g, v, l, me, old_target)) {
              THING_DBG(me, "end of move: attack");
              break;
            }
          }
          break;
        }

        //
        // Did we get a new target?
        //
        if (! thing_monst_choose_target(g, v, l, me)) {
          break;
        }

        auto new_target = thing_monst_target(me);
        if (old_target == new_target) {
          //
          // If it is the same target, do not try to fail to move to the same tile again.
          //
          monst_state_change(g, v, l, me, MONST_STATE_NORMAL);

          //
          // Can we attack here?
          //
          if (level_is_attackable_by_monst(g, v, l, new_target) != nullptr) {
            if (thing_attack_at(g, v, l, me, new_target)) {
              THING_DBG(me, "end of move: same target as before, attacked");
              break;
            }
          }

          THING_DBG(me, "end of move: same target as before, do not continue");
          break;
        }

        THING_DBG(me, "end of move: have a new target (%d,%d)", new_target.x, new_target.y);
        (void) thing_monst_move_to_next(g, v, l, me);
        THING_DBG(me, "end of move: done");
      }
      break;
    case MONST_STATE_ENUM_MAX : break;
  }
}

[[nodiscard]] auto monst_state_to_string(MonstState state) -> std::string
{
  TRACE();
  return MonstState_to_string(state);
}

[[nodiscard]] auto monst_state(Gamep g, Levelsp v, Levelp l, Thingp me) -> MonstState
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
    IF_DEBUG { THING_DBG(me, "same state: %s", monst_state_to_string(new_state).c_str()); }
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
}

//
// Called at the beginning of each tick
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

  //
  // Give the thing ability to move. This will be decremented each thing_monst_event_loop
  //
  (void) thing_move_remaining_incr(g, v, l, me, thing_speed(me));

  THING_DBG(me, "monst tick, move_rem %d dt %f", thing_move_remaining(me), (float) me->thing_dt);
  TRACE_INDENT();

  thing_monst_event_loop(g, v, l, me);
}

[[nodiscard]] auto thing_is_monst(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_monst) != 0;
}

[[nodiscard]] auto thing_is_monst1(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_monst1) != 0;
}

[[nodiscard]] auto thing_is_monst2(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_monst2) != 0;
}

[[nodiscard]] auto thing_monst_target(Thingp t) -> bpoint
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }

  return t->_monst_target;
}

void thing_monst_target_set(Gamep g, Levelsp v, Levelp l, Thingp t, const bpoint &val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }

  t->_monst_target = val;
}
