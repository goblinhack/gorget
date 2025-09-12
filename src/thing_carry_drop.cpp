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
// Add an item to the things inventory
//
bool thing_carry_item(Gamep g, Levelsp v, Levelp l, Thingp player_or_monst, Thingp it)
{
  TRACE_NO_INDENT();

  if (! thing_is_item(it)) {
    return false;
  }

  if (! thing_is_able_to_collect_items(player_or_monst)) {
    return false;
  }

  return thing_is_carried_try_set(g, v, l, it, player_or_monst);
}
