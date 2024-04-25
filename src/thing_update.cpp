//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"

void thing_update(LevelData *data, Thingp t)
{
  TRACE_NO_INDENT();

  auto tp = thing_tp(data, t);

  t->speed = tp_speed_get(tp);
}

void Level::thing_update(Thingp t)
{
  TRACE_NO_INDENT();
  ::thing_update(data, t);
}
