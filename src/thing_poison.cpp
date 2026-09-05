//
// Copyright goblinhack@gmail.com
//

#include "my_bpoint.hpp"
#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game_popups.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp" // NOLINT
#include "my_main.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"

#include <algorithm>
#include <vector>

//
// Poison tbe poor thing
//
auto thing_attack_poison(Gamep g, Levelsp v, Levelp l, Thingp it) -> bool
{
  TRACE();

  auto event_type = THING_EVENT_POISON_DAMAGE;
  auto damage     = 1;

  ThingEvent e {
      .reason     = "poison",   //
      .event_type = event_type, //
      .damage     = damage,     //
  };

  thing_damage_apply(g, v, l, it, e);

  return true;
}
