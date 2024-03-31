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

  t->x     = p.x;
  t->y     = p.y;
  t->old_x = t->x;
  t->old_y = t->y;
  t->pix_x = t->x * TILE_WIDTH;
  t->pix_y = t->y * TILE_HEIGHT;

  thing_update(data, t);

  return t;
}

Thingp Level::thing_init(Tpp tp, point p)
{
  TRACE_NO_INDENT();
  return ::thing_init(data, tp, p);
}
