//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

bool thing_is_immune_to(Thingp t, ThingEventType val)
{
  TRACE_NO_INDENT();

  auto tp = thing_tp(t);

  return tp_is_immune_to(tp, val);
}
