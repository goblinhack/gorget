//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

float    thing_thing_dt_get(Thingp t) { return t->thing_dt; }
int16_t  thing_pix_x_get(Thingp t) { return t->pix_x; }
int16_t  thing_pix_y_get(Thingp t) { return t->pix_y; }
int16_t  thing_speed_get(Thingp t) { return t->speed; }
int8_t   thing_old_x_get(Thingp t) { return t->old_x; }
int8_t   thing_old_y_get(Thingp t) { return t->old_y; }
int8_t   thing_x_get(Thingp t) { return t->x; }
int8_t   thing_y_get(Thingp t) { return t->y; }
ThingId  thing_id_get(Thingp t) { return t->id; }
uint16_t thing_tick_get(Thingp t) { return t->tick; }
uint16_t thing_tp_id_get(Thingp t) { return t->tp_id; }
void     thing_id_set(Thingp t, ThingId id) { t->id = id; }
void     thing_old_x_set(Thingp t, int8_t old_x) { t->old_x = old_x; }
void     thing_old_y_set(Thingp t, int8_t old_y) { t->old_y = old_y; }
void     thing_pix_x_set(Thingp t, int16_t pix_x) { t->pix_x = pix_x; }
void     thing_pix_y_set(Thingp t, int16_t pix_y) { t->pix_y = pix_y; }
void     thing_speed_set(Thingp t, int16_t speed) { t->speed = speed; }
void     thing_thing_dt_set(Thingp t, float thing_dt) { t->thing_dt = thing_dt; }
void     thing_tick_set(Thingp t, uint16_t tick) { t->tick = tick; }
void     thing_tp_id_set(Thingp t, uint16_t tp_id) { t->tp_id = tp_id; }
void     thing_x_set(Thingp t, int8_t x) { t->x = x; }
void     thing_y_set(Thingp t, int8_t y) { t->y = y; }

Thingp level_thing_init(Levelp l, Tpp tp, int x, int y)
{
  TRACE_NO_INDENT();

  auto t = level_thing_new(l, tp, x, y);
  if (! t) {
    return nullptr;
  }

  t->x     = x;
  t->y     = y;
  t->old_x = t->x;
  t->old_y = t->y;
  t->pix_x = t->x * TILE_WIDTH;
  t->pix_y = t->y * TILE_HEIGHT;

  level_thing_update(l, t);

  return t;
}

void level_thing_update(Level *l, Thingp t)
{
  TRACE_NO_INDENT();

  auto tp = level_thing_tp(l, t);

  t->speed = tp_speed_get(tp);
}

Tpp level_thing_tp(Level *l, Thingp t)
{
  TRACE_NO_INDENT();
  return tp_find(t->tp_id);
}
