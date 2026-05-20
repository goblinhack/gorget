//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_types.hpp"

//
// Melt!
//
void thing_melt(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE();

  if (! thing_is_meltable(t)) {
    return;
  }

  thing_on_melt(g, v, l, t);
}
