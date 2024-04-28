//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"

bool level_is_same_type(Levelp l, int x, int y, Tpp tp)
{
  TRACE_NO_INDENT();

  if (! l) {
    return false;
  }

  if (level_is_oob(l, x, y)) {
    return false;
  }

  auto id = l->obj[ x ][ y ][ tp_z_depth_get(tp) ].id;
  if (! id) {
    return false;
  }

  return id == tp_id_get(tp);
}
