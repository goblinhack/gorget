//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_enums.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_minimal.hpp"
#include "my_random.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

#include <map>
#include <string>

ENUM_DEF_C(THING_FLAG_ENUM, ThingFlag)

Tpp thing_tp(Thingp t)
{
  if (t->tp_id) {
    return tp_find(t->tp_id);
  }

  return nullptr;
}

Thingp thing_init(Levelp l, Tpp tp, int x, int y, int z)
{
  TRACE_NO_INDENT();

  auto t = thing_new(l, tp, x, y, z);
  if (! t) {
    return nullptr;
  }

  t->x = x;
  t->y = y;
  t->z = z;

  t->old_x = x;
  t->old_y = y;
  t->old_z = z;

  t->pix_x = t->x * TILE_WIDTH;
  t->pix_y = t->y * TILE_HEIGHT;

  //
  // Assign an initial tile
  //
  auto index = pcg_rand() % tp_tiles_size(tp);
  auto tile  = tp_tiles_get(tp, index);
  if (tile) {
    t->tile_index = tile_index(tile);
    auto i        = pcg_random_range_inclusive(0, tp_tiles_size(tp) - 1);
    t->anim_index = i;
  }

  //
  // Assign the player
  //
  if (tp_is_player(tp)) {
    if (tp_player_index_get(tp) == l->player_index) {
      l->player = t->id;
    }
  }

  thing_update(l, t);

  return t;
}

void thing_update(Level *l, Thingp t)
{
  TRACE_NO_INDENT();

  auto tp = thing_tp(l, t);

  t->speed = tp_speed_get(tp);
}

Tpp thing_tp(Level *l, Thingp t)
{
  TRACE_NO_INDENT();
  return tp_find(t->tp_id);
}
