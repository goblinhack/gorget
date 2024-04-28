//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"

Tpp level_thing_tp(Level *l, Thingp t)
{
  TRACE_NO_INDENT();
  return tp_find(t->tp_id);
}
