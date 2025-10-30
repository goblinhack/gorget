//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"

//
// Add an item to the things inventory
//
bool thing_carry_item(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp player_or_monst)
{
  TRACE_NO_INDENT();

  if (! thing_is_item(item)) {
    return false;
  }

  if (! thing_is_able_to_collect_items(player_or_monst)) {
    return false;
  }

  if (! thing_is_player(player_or_monst) && ! thing_is_monst(player_or_monst)) {
    THING_ERR(player_or_monst, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  auto s = to_string(g, item);
  THING_LOG(player_or_monst, "carry: %s", s.c_str());

  if (! thing_is_carried_try_set(g, v, l, item, player_or_monst)) {
    THING_LOG(player_or_monst, "carry: %s (failed)", s.c_str());

    if (thing_is_player(player_or_monst)) {
      auto the_thing = thing_the_long_name(g, v, l, item);
      TOPCON("You fail to carry %s.", the_thing.c_str());
    }
    return false;
  }

  thing_pop(g, v, item);

  thing_inventory_dump(g, v, l, player_or_monst);

  if (thing_is_player(player_or_monst)) {
    auto the_thing = thing_the_long_name(g, v, l, item);
    TOPCON("You carry %s.", the_thing.c_str());
  }

  return true;
}

//
// Drop an item from the things inventory
//
bool thing_drop_item(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp player_or_monst)
{
  TRACE_NO_INDENT();

  if (! thing_is_item(item)) {
    return false;
  }

  if (! thing_is_carried(item)) {
    return false;
  }

  if (! thing_is_player(player_or_monst) && ! thing_is_monst(player_or_monst)) {
    THING_ERR(player_or_monst, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  auto s = to_string(g, item);
  THING_LOG(player_or_monst, "drop: %s", s.c_str());

  if (! thing_is_carried_try_unset(g, v, l, item, player_or_monst)) {
    THING_LOG(player_or_monst, "drop: %s (failed)", s.c_str());

    if (thing_is_player(player_or_monst)) {
      auto the_thing = thing_the_long_name(g, v, l, item);
      TOPCON("You fail to drop %s.", the_thing.c_str());
    }
    return false;
  }

  thing_warp_to(g, v, l, item, player_or_monst->at);

  if (thing_is_player(player_or_monst)) {
    auto the_thing = thing_the_long_name(g, v, l, item);
    TOPCON("You drop %s.", the_thing.c_str());
  }

  return true;
}
