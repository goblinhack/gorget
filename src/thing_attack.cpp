//
// Copyright goblinhack@gmail.com
//

#include "my_bpoint.hpp"
#include "my_callstack.hpp"
#include "my_game_defs.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp" // NOLINT
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

#include <algorithm>
#include <vector>

//
// We're trying to attack at this tile. What do we hit first?
//
static auto thing_attack(Gamep g, Levelsp v, Levelp l, Thingp attacker, Thingp it, ThingEvent *e_in = nullptr) -> bool
{
  TRACE();

  auto *source     = attacker;
  auto  event_type = THING_EVENT_MELEE_DAMAGE;
  auto  damage     = tp_damage(thing_tp(source), event_type);

  ThingEvent e {
      .reason     = "melee",    //
      .event_type = event_type, //
      .damage     = damage,     //
      .source     = source,     //
  };

  if (e_in != nullptr) {
    e = *e_in;
  }

  //
  // Check not too many attacks
  //
  if (thing_is_monst(attacker) || thing_is_player(attacker)) {
    //
    // NOTE: door slam attack and anything else I've not thought of, bypasses this
    //
    if (thing_attack_count_per_tick_incr(g, v, l, attacker) > tp_attack_count_max_per_tick_get(thing_tp(attacker))) {
      THING_DBG(attacker, "exceeded attack count, ignore");
      return false;
    }
  }

  //
  // Keep track of who attacked us
  //
  if (thing_is_monst(attacker)) {
    if (thing_is_player(it)) {
      auto *p = thing_player_struct(g);
      if (p != nullptr) {
        p->attacked_by[ tp_id_get(thing_tp(attacker)) ]++;
      }
    }
  }

  //
  // Thing callback
  //
  if (! thing_on_attacking(g, v, l, attacker, it, e)) {
    return false;
  }

  thing_damage(g, v, l, it, e);

  thing_is_hit_set(g, v, l, it, THING_HIT_FLASH_ANIM_MS);

  return true;
}

//
// We're trying to attack at this tile. What do we hit first?
//
[[nodiscard]] auto thing_attack_at(Gamep g, Levelsp v, Levelp l, Thingp attacker, const bpoint &attack_at, ThingEvent *e) -> bool
{
  THING_DBG(attacker, "%s", __FUNCTION__);
  TRACE_INDENT();

  //
  // Only allow attacks on immediately adjacent tiles. Unless you can fire weapons.
  //
  if (thing_is_able_to_fire_weapons(attacker)) {
    //
    // Firing tiles do not need to be adjacent
    //
  } else {
    if (thing_at(attacker) == attack_at) {
      //
      // Allow door slam attack on same tile
      //
    } else if (! adjacent(thing_at(attacker), attack_at)) {
      //
      // Adjacent tile attack
      //
      return false;
    }
  }

  std::vector< Thingp > cands;

  FOR_ALL_THINGS_AT_UNSAFE(g, v, l, o, attack_at)
  {
    if (o == attacker) {
      continue;
    }

    if (thing_is_monst(attacker) || ((e != nullptr) && (e->source != nullptr) && thing_is_monst(e->source))) {
      if (thing_is_attackable_by_monst(o)) {
        cands.push_back(o);
      }
    } else if (thing_is_player(attacker) || ((e != nullptr) && (e->source != nullptr) && thing_is_player(e->source))) {
      if (thing_is_attackable_by_player(o)) {
        cands.push_back(o);
      }
    } else {
      continue;
    }
  }

  if (cands.empty()) {
    return false;
  }

  //
  // Sort by priority
  //
  std::ranges::sort(cands, [](Thingp a, Thingp b) -> bool { return thing_priority(a) < thing_priority(b); });

  if (compiler_unused) {
    for (auto *cand : cands) {
      THING_DBG(cand, "prio %u", thing_priority(cand));
    }
  }

  for (auto *cand : cands) {

    if (thing_is_dead(cand)) {
      if (! thing_is_hit_when_dead(cand)) {
        continue;
      }
    }

    if (thing_attack(g, v, l, attacker, cand, e)) {
      return true;
    }
  }
  return false;
}

[[nodiscard]] auto thing_attack_count_per_tick(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_attack_count_per_tick;
}

[[nodiscard]] auto thing_attack_count_per_tick_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_attack_count_per_tick = val;
}

[[nodiscard]] auto thing_attack_count_per_tick_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_attack_count_per_tick += val;
}

[[nodiscard]] auto thing_attack_count_per_tick_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_attack_count_per_tick) - val <= 0) {
    return t->_attack_count_per_tick = 0;
  }
  return t->_attack_count_per_tick -= val;
}

[[nodiscard]] auto thing_is_attackable_by_player(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_attackable_by_player) != 0;
}

[[nodiscard]] auto thing_is_attackable_by_monst(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_attackable_by_monst) != 0;
}
