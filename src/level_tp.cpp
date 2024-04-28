//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"

#include <string.h>

void level_tp_set(Level *l, int x, int y, Tpp tp)
{
  TRACE_NO_INDENT();

  auto o = &l->obj[ x ][ y ][ tp_z_depth_get(tp) ];
  memset(o, 0, sizeof(*o));
  o->id = tp_id_get(tp);
}

void level_tp_unset(Level *l, int x, int y, Tpp tp)
{
  TRACE_NO_INDENT();

  auto o = &l->obj[ x ][ y ][ tp_z_depth_get(tp) ];
  memset(o, 0, sizeof(*o));
  o->id = tp_id_get(tp);
}

Tpp level_tp_get(Level *l, int x, int y, uint8_t slot)
{
  TRACE_NO_INDENT();

  Id id = l->obj[ x ][ y ][ slot ].id;
  if (! id) {
    return nullptr;
  }

  if (id >= THING_ID_BASE) {
    return nullptr;
  }

  return tp_find(id);
}
