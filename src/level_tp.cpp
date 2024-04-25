//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"

#include <string.h>

void tp_set(LevelData *data, int x, int y, Tpp tp)
{
  TRACE_NO_INDENT();

  auto o = &data->obj[ x ][ y ][ tp_z_depth_get(tp) ];
  memset(o, 0, sizeof(*o));
  o->id = tp_id_get(tp);
}

void Level::tp_set(int x, int y, Tpp tp)
{
  TRACE_NO_INDENT();
  return ::tp_set(data, x, y, tp);
}

void tp_unset(LevelData *data, int x, int y, Tpp tp)
{
  TRACE_NO_INDENT();

  auto o = &data->obj[ x ][ y ][ tp_z_depth_get(tp) ];
  memset(o, 0, sizeof(*o));
  o->id = tp_id_get(tp);
}

void Level::tp_unset(int x, int y, Tpp tp)
{
  TRACE_NO_INDENT();
  return ::tp_unset(data, x, y, tp);
}

Tpp tp_get(LevelData *data, int x, int y, uint8_t slot)
{
  TRACE_NO_INDENT();

  Id id = data->obj[ x ][ y ][ slot ].id;
  if (! id) {
    return nullptr;
  }

  if (id >= THING_ID_BASE) {
    return nullptr;
  }

  return tp_find(id);
}

Tpp Level::tp_get(int x, int y, uint8_t slot)
{
  TRACE_NO_INDENT();
  return ::tp_get(data, x, y, slot);
}
