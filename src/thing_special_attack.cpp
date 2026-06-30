//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_dice_class.hpp"
#include "my_dice_rolls.hpp"
#include "my_game_defs.hpp"
#include "my_game_popups.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_tp_class.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"

#include <algorithm>
#include <limits>
#include <string>

bool thing_special_attack_get_random(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp it, TpSpecialAttack &out)
{
  TRACE();

  if (me == nullptr) [[unlikely]] {
    ERR("no thing pointer");
    return false;
  }

  auto tp = thing_tp(me);

  if (tp->damage_type.empty()) {
    return false;
  }

  auto dice_roll = d100();

  std::vector< TpSpecialAttack > filtered;

  //
  // Check for things mathing the dice roll first.
  //
  for (auto d : tp->damage_type) {
    auto val = d.second;

    if (val.when_adjacent) {
      auto target = thing_at(it);
      if (! adjacent(thing_at(me), target)) {
        continue;
      }
    }

    if (val.when_distant) {
      auto target = thing_at(it);
      if (distance(thing_at(me), target) <= 1) {
        continue;
      }
    }

    filtered.push_back(val);
  }

  //
  // Check for things mathing the dice roll first.
  //
  for (auto d : filtered) {
    if (! d.d100) {
      continue;
    }

    if (dice_roll < d.d100) {
      out = d;
      return true;
    }
  }

  //
  // Fallback to any valid default attack
  //
  for (auto d : filtered) {
    if (d.d100) {
      continue;
    }

    out = d;
    return true;
  }

  return false;
}
