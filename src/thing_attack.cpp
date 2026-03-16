//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level_inlines.hpp"
#include "my_main.hpp"
#include "my_thing_inlines.hpp"

#include <algorithm>
#include <cmath>

//
// We're trying to attack at this tile. What do we hit first?
//
bool thing_attack_at(Gamep g, Levelsp v, Levelp l, Thingp me, const spoint &attack_at)
{
  TRACE();

  if (compiler_unused) {
    THING_DBG(me, "thing_attack_at");
  }

  std::vector< Thingp > cands;

  FOR_ALL_THINGS_AT(g, v, l, o, attack_at)
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

  if (! cands.size()) {
    return false;
  }

  //
  // Sort by priority
  //
  std::ranges::sort(cands, [](Thingp a, Thingp b) -> bool {
    if (thing_priority(a) < thing_priority(b)) {
      return true;
    }
    return false;
  });

  if (compiler_unused) {
    for (auto cand : cands) {
      THING_DBG(cand, "prio %u", thing_priority(cand));
    }
  }

  for (auto cand : cands) {

    if (thing_is_dead(cand)) {
      if (! thing_is_hit_when_dead(cand)) {
        continue;
      }
    }

    thing_is_hit_set(g, v, l, cand, MAX_HIT_TIME_MS);

    return true;
  }
  return false;
}
