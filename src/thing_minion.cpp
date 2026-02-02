//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_inlines.hpp"

#include <string.h>

//
// Is this minion attached to a mob?
//
Thingp thing_minion_mob_get(Gamep g, Levelsp v, Levelp l, Thingp minion)
{
  if (! minion) {
    return nullptr;
  }

  if (! thing_is_minion(minion)) {
    return nullptr;
  }

  if (! minion->mob_id) {
    return nullptr;
  }

  return thing_find(g, v, minion->mob_id);
}

//
// Detach a minion from its mob
//
bool thing_minion_detach_me_from_mob(Gamep g, Levelsp v, Levelp l, Thingp minion)
{
  TRACE_NO_INDENT();

  if (! minion) {
    return false;
  }

  if (! thing_is_minion(minion)) {
    THING_ERR(minion, "non minion trying to detach itself");
    return false;
  }

  auto mob = thing_minion_mob_get(g, v, l, minion);
  if (! mob) {
    return false;
  }

  THING_LOG(minion, "detach me from mob");

  return thing_mob_detach_minion(g, v, l, mob, minion);
}
