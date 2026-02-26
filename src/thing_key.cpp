//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_inlines.hpp"

//
// Add a key to the things inventory
//
auto thing_collect_key(Gamep g, Levelsp v, Levelp l, Thingp it, Thingp player_or_monst) -> bool
{
  TRACE();

  if (! thing_is_key(it)) {
    return false;
  }

  if (! thing_is_able_to_collect_keys(player_or_monst)) {
    return false;
  }

  if (! thing_is_player(player_or_monst) && ! thing_is_monst(player_or_monst)) {
    THING_ERR(player_or_monst, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  ThingEvent e {
      .reason     = "by carrying",       //
      .event_type = THING_EVENT_CARRIED, //
      .source     = player_or_monst      //
  };

  thing_dead(g, v, l, it, e);

  (void) thing_keys_carried_incr(g, v, l, player_or_monst, 1);

  return true;
}
