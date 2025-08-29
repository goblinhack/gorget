//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"

//
// Create all levels
//
void levels_init(Gamep g)
{
  TRACE_NO_INDENT();

  levels_test(g);
  levels_fixed(g);
}
