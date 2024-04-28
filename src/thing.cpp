//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tile.hpp"

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

void     thing_id_set(Thingp t, ThingId id) { t->id = id; }
ThingId  thing_id_get(Thingp t) { return t->id; }
void     thing_tp_id_set(Thingp t, uint16_t tp_id) { t->tp_id = tp_id; }
uint16_t thing_tp_id_get(Thingp t) { return t->tp_id; }
void     thing_tick_set(Thingp t, uint16_t tick) { t->tick = tick; }
uint16_t thing_tick_get(Thingp t) { return t->tick; }
void     thing_x_set(Thingp t, int8_t x) { t->x = x; }
int8_t   thing_x_get(Thingp t) { return t->x; }
void     thing_y_set(Thingp t, int8_t y) { t->y = y; }
int8_t   thing_y_get(Thingp t) { return t->y; }
void     thing_old_x_set(Thingp t, int8_t old_x) { t->old_x = old_x; }
int8_t   thing_old_x_get(Thingp t) { return t->old_x; }
void     thing_old_y_set(Thingp t, int8_t old_y) { t->old_y = old_y; }
int8_t   thing_old_y_get(Thingp t) { return t->old_y; }
void     thing_speed_set(Thingp t, int16_t speed) { t->speed = speed; }
int16_t  thing_speed_get(Thingp t) { return t->speed; }
void     thing_thing_dt_set(Thingp t, float thing_dt) { t->thing_dt = thing_dt; }
float    thing_thing_dt_get(Thingp t) { return t->thing_dt; }
void     thing_pix_x_set(Thingp t, int16_t pix_x) { t->pix_x = pix_x; }
int16_t  thing_pix_x_get(Thingp t) { return t->pix_x; }
void     thing_pix_y_set(Thingp t, int16_t pix_y) { t->pix_y = pix_y; }
int16_t  thing_pix_y_get(Thingp t) { return t->pix_y; }
void     thing_dir_up_set(Thingp t, uint8_t dir_up) { t->dir_up = dir_up; }
uint8_t  thing_dir_up_get(Thingp t) { return t->dir_up; }
void     thing_dir_down_set(Thingp t, uint8_t dir_down) { t->dir_down = dir_down; }
uint8_t  thing_dir_down_get(Thingp t) { return t->dir_down; }
void     thing_dir_left_set(Thingp t, uint8_t dir_left) { t->dir_left = dir_left; }
uint8_t  thing_dir_left_get(Thingp t) { return t->dir_left; }
void     thing_dir_right_set(Thingp t, uint8_t dir_right) { t->dir_right = dir_right; }
uint8_t  thing_dir_right_get(Thingp t) { return t->dir_right; }

