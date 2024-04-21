//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"

void Level::anim(void)
{
  TRACE_NO_INDENT();

  auto            ts = time_ms();
  static uint32_t last_ts;

  if (! last_ts) {
    last_ts = ts;
    return;
  }

  auto time_step = ts - last_ts;
  last_ts        = ts;

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        Tpp tp;
        thing_get(x, y, slot, &tp);
        if (! tp) {
          continue;
        }

        auto obj        = &data->obj[ x ][ y ][ slot ];
        auto tile_index = obj->tile;
        if (! tile_index) {
          continue;
        }

        auto tile = tile_index_to_tile(tile_index);
        if (! tile) {
          continue;
        }

        if (! tile->delay_ms) {
          continue;
        }

        //
        // Decrement the remaining time
        //
        if (obj->anim_ms_remaining > 0) {
          obj->anim_ms_remaining -= time_step;
          if (obj->anim_ms_remaining > 0) {
            continue;
          }
        }

        obj->anim_index++;
        if (obj->anim_index >= tp->tiles.size()) {
          obj->anim_index = 0;
        }

        tile      = tp->tiles[ obj->anim_index ];
        obj->tile = tile->global_index;

        obj->anim_ms_remaining += tile->delay_ms;
        if (obj->anim_ms_remaining < 0) {
          obj->anim_ms_remaining = tile->delay_ms;
        }
      }
    }
  }
}
