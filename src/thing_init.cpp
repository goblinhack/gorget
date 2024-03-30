//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_tp.hpp"

Thingp thing_init(LevelData *data, Tpp tp, point p)
{
  TRACE_NO_INDENT();

  auto t = thing_new(data, tp, p);
  if (! t) {
    return nullptr;
  }

  thing_update(data, t);
  return t;
}

Thingp Level::thing_init(Tpp tp, point p)
{
  TRACE_NO_INDENT();
  return ::thing_init(data, tp, p);
}
