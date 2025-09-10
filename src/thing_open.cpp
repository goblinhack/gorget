//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_dice.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_ui.hpp"

//
// Open doors
//
bool thing_open(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp opener)
{
  TRACE_NO_INDENT();

  if (! thing_is_open_tryable(t)) {
    return false;
  }

  return thing_is_open_try_set(g, v, l, t, opener);
}
