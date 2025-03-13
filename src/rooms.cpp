//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"

//
// Create all rooms
//
void rooms_init(Gamep g)
{
  TRACE_NO_INDENT();

  /* clang-format off */

  rooms_start(g);
  rooms_exit(g);
  rooms_prefab(g);

  /* clang-format on */
}
