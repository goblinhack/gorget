//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_tp.hpp"

Tpp thing_tp(LevelData *data, Thingp t)
{
  TRACE_NO_INDENT();
  return tp_find(t->tp_id);
}

Tpp Level::thing_tp(Thingp t)
{
  TRACE_NO_INDENT();
  return ::thing_tp(data, t);
}
