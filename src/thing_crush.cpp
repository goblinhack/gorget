//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"

//
// Add a key to the things inventory
//
// "me" here could be a barrel
//
bool thing_crush(Gamep g, Levelsp v, Levelp l, Thingp it, Thingp me)
{
  TRACE_NO_INDENT();

  if (! thing_is_crushable(it)) {
    return false;
  }

  //
  // Crush grass?
  //
  if (thing_is_grass(it)) {
    if (! thing_is_able_to_crush_grass(me)) {
      return false;
    }
  }

  //
  // Crush it
  //
  ThingEvent e {
      .reason     = "by crushing",     //
      .event_type = THING_EVENT_CRUSH, //
      .source     = me                 //
  };
  thing_dead(g, v, l, it, e);
  return true;
}
