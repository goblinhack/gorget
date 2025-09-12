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
bool thing_crush(Gamep g, Levelsp v, Levelp l, Thingp player_or_monst, Thingp it)
{
  TRACE_NO_INDENT();

  if (! thing_is_crushable(it)) {
    return false;
  }

  //
  // Crush grass?
  //
  if (thing_is_grass(it)) {
    if (! thing_is_able_to_crush_grass(player_or_monst)) {
      return false;
    }
  }

  //
  // Crush it
  //
  ThingEvent e {
      .reason     = "by crushing",     //
      .event_type = THING_EVENT_CRUSH, //
      .source     = player_or_monst    //
  };
  thing_dead(g, v, l, it, e);
  return true;
}
