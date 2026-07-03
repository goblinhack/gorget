//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_types.hpp"

void thing_fini(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE();

  if (compiler_unused) {
    THING_DBG(g, v, l, t, "fini");
  }

  if (thing_is_mob(t)) {
    (void) thing_mob_detach_all_minions(g, v, l, t);
  }

  thing_free(g, v, l, t);
}
