//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_tile.hpp"

bool is_oob(Level *l, int x, int y)
{
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

bool level_is_oob(Levelp l, int x, int y)
{
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

bool level_set_id(Levelp l, int x, int y, uint8_t slot, Id id)
{
  if (level_is_oob(l, x, y)) {
    return false;
  }
  l->obj[ x ][ y ][ slot ].id = id;
  return true;
}

void level_set_id_no_check(Levelp l, int x, int y, uint8_t slot, Id id) { l->obj[ x ][ y ][ slot ].id = id; }

Id level_get_id(Levelp l, int x, int y, uint8_t slot)
{
  if (level_is_oob(l, x, y)) {
    return 0;
  }
  return l->obj[ x ][ y ][ slot ].id;
}

Id level_get_id_no_check(Levelp l, int x, int y, uint8_t slot) { return l->obj[ x ][ y ][ slot ].id; }

bool level_set_tile(Levelp l, int x, int y, uint8_t slot, Tilep tile)
{
  if (level_is_oob(l, x, y)) {
    return false;
  }
  if (tile) {
    l->obj[ x ][ y ][ slot ].tile = tile_global_index(tile);
  } else {
    l->obj[ x ][ y ][ slot ].tile = 0;
  }
  return true;
}

void level_set_tile_no_check(Levelp l, int x, int y, uint8_t slot, Tilep tile)
{
  l->obj[ x ][ y ][ slot ].tile = tile_global_index(tile);
}

Tilep level_get_tile(Levelp l, int x, int y, uint8_t slot)
{
  if (level_is_oob(l, x, y)) {
    return nullptr;
  }
  return tile_index_to_tile(l->obj[ x ][ y ][ slot ].tile);
}

Tilep level_get_tile_no_check(Levelp l, int x, int y, uint8_t slot)
{
  return tile_index_to_tile(l->obj[ x ][ y ][ slot ].tile);
}
