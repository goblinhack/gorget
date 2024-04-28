//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"

void level_thing_update(Level *l, Thingp t)
{
  TRACE_NO_INDENT();

  auto tp = level_thing_tp(l, t);

  t->speed = tp_speed_get(tp);
}
