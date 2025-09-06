//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tp_callbacks.hpp"

void thing_fini(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (0) {
    THING_DBG(t, "fini");
  }

  thing_free(g, v, l, t);
}
