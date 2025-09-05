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
void thing_open(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  thing_is_open_set(g, v, l, t);
}
