//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level_inlines.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_thing_inlines.hpp"

#include <algorithm>
#include <cmath>

//
// We're trying to attack at this tile. What do we hit first?
//
static auto thing_attack(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp it, ThingEvent *e_in = nullptr) -> bool
{
  TRACE();

  auto *source     = me;
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
  // Thing callback
  //
  if (! thing_on_attacking(g, v, l, me, it, e)) {
    return false;
  }

  thing_damage(g, v, l, it, e);

  thing_is_hit_set(g, v, l, it, THING_HIT_FLASH_ANIM_MS);

  return true;
}

//
// We're trying to attack at this tile. What do we hit first?
//
auto thing_attack_at(Gamep g, Levelsp v, Levelp l, Thingp me, const bpoint &attack_at, ThingEvent *e) -> bool
{
  THING_DBG(me, "%s", __FUNCTION__);
  TRACE_INDENT();

  //
  // Only allow attacks on immediately adjacent tiles. Unless you can fire weapons.
  //
  if (thing_is_able_to_fire_weapons(me)) {
    //
    // Firing tiles do not need to be adjacent
    //
  } else {
    if (thing_at(me) == attack_at) {
      //
      // Allow door slam attack on same tile
      //
    } else if (! adjacent(thing_at(me), attack_at)) {
      //
      // Adjacent tile attack
      //
      return false;
    }
  }

  std::vector< Thingp > cands;

  FOR_ALL_THINGS_AT_UNSAFE(g, v, l, o, attack_at)
  {
    if (o == me) {
      continue;
    }

    if (thing_is_monst(me) || ((e != nullptr) && (e->source != nullptr) && thing_is_monst(e->source))) {
      if (thing_is_attackable_by_monst(o)) {
        cands.push_back(o);
      }
    } else if (thing_is_player(me) || ((e != nullptr) && (e->source != nullptr) && thing_is_player(e->source))) {
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

    if (thing_attack(g, v, l, me, cand, e)) {
      return true;
    }
  }
  return false;
}
