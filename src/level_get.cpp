//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_tp.hpp"

bool Level::is_same_type(int x, int y, Tpp tp)
{
  TRACE_NO_INDENT();
  if (is_oob(x, y)) {
    return false;
  }

  if (! data) {
    return false;
  }

  auto id = data->obj[ x ][ y ][ tp->z_depth ].id;
  if (! id) {
    return false;
  }

  return id == tp->id;
}
