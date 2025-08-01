//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tp_callbacks.hpp"

void thing_chasm_handle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // Begin falling
  //
  if (! thing_is_falling(t)) {
    thing_is_falling_set(g, v, l, t, 1);
  }

  tp_on_over_chasm(g, v, l, t);
}
