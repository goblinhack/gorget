//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_level_ph1.hpp"
#include "my_level_ph2.hpp"
#include "my_level_ph3.hpp"
#include "my_level_ph4.hpp"
#include "my_tile.hpp"

bool is_oob(LevelData *data, int8_t x, int8_t y)
{
  TRACE_NO_INDENT();
  if (x < 0) {
    return true;
  }
  if (y < 0) {
    return true;
  }
  if (x >= MAP_WIDTH) {
    return true;
  }
  if (y >= MAP_HEIGHT) {
    return true;
  }
  return false;
}

bool Level::is_oob(int8_t x, int8_t y)
{
  TRACE_NO_INDENT();
  if (x < 0) {
    return true;
  }
  if (y < 0) {
    return true;
  }
  if (x >= MAP_WIDTH) {
    return true;
  }
  if (y >= MAP_HEIGHT) {
    return true;
  }
  return false;
}

bool Level::set_id(int8_t x, int8_t y, uint8_t slot, Id id)
{
  TRACE_NO_INDENT();
  if (is_oob(x, y)) {
    return false;
  }
  data->obj[ x ][ y ][ slot ].id = id;
  return true;
}

void Level::set_id_no_check(int8_t x, int8_t y, uint8_t slot, Id id) { data->obj[ x ][ y ][ slot ].id = id; }

Id Level::get_id(int8_t x, int8_t y, uint8_t slot)
{
  TRACE_NO_INDENT();
  if (is_oob(x, y)) {
    return 0;
  }
  return data->obj[ x ][ y ][ slot ].id;
}

Id Level::get_id_no_check(int8_t x, int8_t y, uint8_t slot) { return data->obj[ x ][ y ][ slot ].id; }

bool Level::set_tile(int8_t x, int8_t y, uint8_t slot, Tilep tile)
{
  TRACE_NO_INDENT();
  if (is_oob(x, y)) {
    return false;
  }
  if (tile) {
    data->obj[ x ][ y ][ slot ].tile = tile->global_index;
  } else {
    data->obj[ x ][ y ][ slot ].tile = 0;
  }
  return true;
}

void Level::set_tile_no_check(int8_t x, int8_t y, uint8_t slot, Tilep tile)
{
  data->obj[ x ][ y ][ slot ].tile = tile->global_index;
}

Tilep Level::get_tile(int8_t x, int8_t y, uint8_t slot)
{
  TRACE_NO_INDENT();
  if (is_oob(x, y)) {
    return nullptr;
  }
  return tile_index_to_tile(data->obj[ x ][ y ][ slot ].tile);
}

Tilep Level::get_tile_no_check(int8_t x, int8_t y, uint8_t slot)
{
  return tile_index_to_tile(data->obj[ x ][ y ][ slot ].tile);
}
