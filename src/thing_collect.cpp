//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_string.hpp"
#include "my_tp_callbacks.hpp"
#include "my_ui.hpp"
#include "my_wids.hpp"

//
// Add a key to the things inventory
//
bool thing_collect_key(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp it)
{
  TRACE_NO_INDENT();

  if (! thing_is_key(it)) {
    return false;
  }

  if (! thing_is_able_to_collect_keys(me)) {
    return false;
  }

  ThingEvent e {
      .reason     = "by collecting",       //
      .event_type = THING_EVENT_COLLECTED, //
      .source     = me                     //
  };

  thing_dead(g, v, l, it, e);

  thing_keys_carried_incr(g, v, l, me, 1);

  return true;
}
