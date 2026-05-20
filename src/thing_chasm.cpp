//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing.hpp"
#include "my_types.hpp"

void thing_chasm_handle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE();

  thing_fall(g, v, l, t);
}
