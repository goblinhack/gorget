//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <iostream>
#include <sstream>
#include <string.h>

#include "my_level.hpp"
#include "my_level_data.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_thing_id.hpp"
#include "my_tp.hpp"

void thing_push(LevelData *data, Thingp t)
{
  TRACE_NO_INDENT();

  int16_t x = t->pix_x / TILE_WIDTH;
  int16_t y = t->pix_y / TILE_HEIGHT;
  point   p(x, y);

  if (is_oob(data, p)) {
    return;
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o = &data->obj[ x ][ y ][ slot ];
    if (o->id == t->id) {
      return;
    }
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o = &data->obj[ x ][ y ][ slot ];
    if (! o->id) {
      o->id     = t->id;
      auto tp   = tp_find(t->tp_id);
      auto tile = tp_first_tile(tp);
      if (tile) {
        o->tile = tile->global_index;
      }
      return;
    }
  }

  ERR("out of thing slots");
}

void Level::thing_push(Thingp t)
{
  TRACE_NO_INDENT();
  return ::thing_push(data, t);
}

void thing_pop(LevelData *data, Thingp t)
{
  TRACE_NO_INDENT();

  uint8_t x = t->pix_x / TILE_WIDTH;
  uint8_t y = t->pix_y / TILE_HEIGHT;
  point   p(x, y);

  if (is_oob(data, p)) {
    return;
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o = &data->obj[ x ][ y ][ slot ];
    if (o->id == t->id) {
      memset(o, 0, sizeof(*o));
      return;
    }
  }
}

void Level::thing_pop(Thingp t)
{
  TRACE_NO_INDENT();
  return ::thing_pop(data, t);
}

void thing_update_pos(LevelData *data, Thingp t)
{
  if (! t->dx && ! t->dy) {
    return;
  }

  int16_t cur_pix_x = t->pix_x;
  int16_t cur_pix_y = t->pix_y;
  int16_t new_pix_x = cur_pix_x + t->dx;
  int16_t new_pix_y = cur_pix_y + t->dy;

  int16_t cur_tile_x = cur_pix_x / TILE_WIDTH;
  int16_t cur_tile_y = cur_pix_y / TILE_HEIGHT;
  int16_t new_tile_x = new_pix_x / TILE_WIDTH;
  int16_t new_tile_y = new_pix_y / TILE_HEIGHT;

  if ((cur_tile_x == new_tile_x) && (cur_tile_y == new_tile_y)) {
    t->pix_x = new_pix_x;
    t->pix_y = new_pix_y;
    return;
  }

  ThingOrTp saved {};

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o = &data->obj[ cur_tile_x ][ cur_tile_y ][ slot ];
    if (o->id == t->id) {
      memcpy(&saved, o, sizeof(*o));
      break;
    }
  }

  thing_pop(data, t);
  t->pix_x = new_pix_x;
  t->pix_y = new_pix_y;
  thing_push(data, t);

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o = &data->obj[ new_tile_x ][ new_tile_y ][ slot ];
    if (o->id == t->id) {
      memcpy(o, &saved, sizeof(*o));
      break;
    }
  }
}

void Level::thing_update_pos(Thingp t)
{
  TRACE_NO_INDENT();
  return ::thing_update_pos(data, t);
}
