//
// Copyright Neil McGill, goblinhack@gmail.com
//

// REMOVED #include <iostream>
// REMOVED #include <sstream>
#include <string.h>

#include "my_level.hpp"
// REMOVED #include "my_level_data.hpp"
// REMOVED #include "my_main.hpp"
// REMOVED #include "my_thing.hpp"
// REMOVED #include "my_thing_id.hpp"
#include "my_tp.hpp"

void tp_set(LevelData *data, point p, Tpp tp)
{
  TRACE_NO_INDENT();

  auto o = &data->obj[ p.x ][ p.y ][ tp->z_depth ];
  memset(o, 0, sizeof(*o));
  o->id = tp->id;
}

void Level::tp_set(point p, Tpp tp)
{
  TRACE_NO_INDENT();
  return ::tp_set(data, p, tp);
}

Tpp tp_get(LevelData *data, point p, uint8_t slot)
{
  TRACE_NO_INDENT();

  Id id = data->obj[ p.x ][ p.y ][ slot ].id;
  if (! id) {
    return nullptr;
  }

  if (id >= THING_ID_BASE) {
    return nullptr;
  }

  return tp_find(id);
}

Tpp Level::tp_get(point p, uint8_t slot)
{
  TRACE_NO_INDENT();
  return ::tp_get(data, p, slot);
}
