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
static auto thing_attack(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp it) -> bool
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

  thing_damage(g, v, l, it, e);

  thing_is_hit_set(g, v, l, it, MAX_HIT_TIME_MS);

  return true;
}

//
// We're trying to attack at this tile. What do we hit first?
//
auto thing_attack_at(Gamep g, Levelsp v, Levelp l, Thingp me, const spoint &attack_at) -> bool
{
  TRACE();

  if (compiler_unused) {
    THING_DBG(me, "thing_attack_at");
  }

  //
  // Only allow attacks on immediately adjacent tiles
  //
  if (! adjacent(thing_at(me), attack_at)) {
    return false;
  }

  std::vector< Thingp > cands;

  FOR_ALL_THINGS_AT_UNSAFE(g, v, l, o, attack_at)
  {
    if (o == me) {
      continue;
    }

    if (thing_is_monst(me)) {
      if (thing_is_attackable_by_monst(o)) {
        cands.push_back(o);
      }
    } else if (thing_is_player(me)) {
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

    if (thing_attack(g, v, l, me, cand)) {
      return true;
    }
  }
  return false;
}
