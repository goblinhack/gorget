//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_tile.hpp"

bool is_oob(LevelData *data, point p)
{
  TRACE_NO_INDENT();
  if (p.x < 0) {
    return true;
  }
  if (p.y < 0) {
    return true;
  }
  if (p.x >= MAP_WIDTH) {
    return true;
  }
  if (p.y >= MAP_HEIGHT) {
    return true;
  }
  return false;
}

bool Level::is_oob(point p)
{
  TRACE_NO_INDENT();
  if (p.x < 0) {
    return true;
  }
  if (p.y < 0) {
    return true;
  }
  if (p.x >= MAP_WIDTH) {
    return true;
  }
  if (p.y >= MAP_HEIGHT) {
    return true;
  }
  return false;
}

bool Level::set_id(point p, uint8_t slot, Id id)
{
  TRACE_NO_INDENT();
  if (is_oob(p)) {
    return false;
  }
  data->obj[ p.x ][ p.y ][ slot ].id = id;
  return true;
}

void Level::set_id_no_check(point p, uint8_t slot, Id id) { data->obj[ p.x ][ p.y ][ slot ].id = id; }

Id Level::get_id(point p, uint8_t slot)
{
  TRACE_NO_INDENT();
  if (is_oob(p)) {
    return 0;
  }
  return data->obj[ p.x ][ p.y ][ slot ].id;
}

Id Level::get_id_no_check(point p, uint8_t slot) { return data->obj[ p.x ][ p.y ][ slot ].id; }

bool Level::set_tile(point p, uint8_t slot, Tilep tile)
{
  TRACE_NO_INDENT();
  if (is_oob(p)) {
    return false;
  }
  if (tile) {
    data->obj[ p.x ][ p.y ][ slot ].tile = tile->global_index;
  } else {
    data->obj[ p.x ][ p.y ][ slot ].tile = 0;
  }
  return true;
}

void Level::set_tile_no_check(point p, uint8_t slot, Tilep tile)
{
  data->obj[ p.x ][ p.y ][ slot ].tile = tile->global_index;
}

Tilep Level::get_tile(point p, uint8_t slot)
{
  TRACE_NO_INDENT();
  if (is_oob(p)) {
    return nullptr;
  }
  return tile_index_to_tile(data->obj[ p.x ][ p.y ][ slot ].tile);
}

Tilep Level::get_tile_no_check(point p, uint8_t slot)
{
  return tile_index_to_tile(data->obj[ p.x ][ p.y ][ slot ].tile);
}
