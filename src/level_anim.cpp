//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_tile.hpp"
#include "my_time.hpp"
#include "my_tp.hpp"

void level_anim(Levelp l)
{
  TRACE_NO_INDENT();

  //
  // What level is the player on?
  //
  auto player = thing_player(l);
  if (! player) {
    return;
  }
  int z = player->at.z;

  auto            ts = time_ms();
  static uint32_t last_ts;

  if (! last_ts) {
    last_ts = ts;
    return;
  }

  auto time_step = ts - last_ts;
  last_ts        = ts;

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    for (auto y = l->miny; y < l->maxy; y++) {
      for (auto x = l->minx; x < l->maxx; x++) {
        Tpp     tp;
        point3d p(x, y, z);
        Thingp  t = thing_and_tp_get(l, p, slot, &tp);
        if (! t) {
          continue;
        }

        auto tile_index = t->tile_index;
        if (! tile_index) {
          continue;
        }

        auto tile = tile_index_to_tile(tile_index);
        if (! tile) {
          continue;
        }

        if (! tile_delay_ms(tile)) {
          continue;
        }

        //
        // Decrement the remaining time
        //
        if (t->anim_ms_remaining > 0) {
          t->anim_ms_remaining -= time_step;
          if (t->anim_ms_remaining > 0) {
            continue;
          }
        }

        t->anim_index++;
        if (t->anim_index >= tp_tiles_size(tp)) {
          t->anim_index = 0;
        }

        tile          = tp_tiles_get(tp, t->anim_index);
        t->tile_index = tile_global_index(tile);

        t->anim_ms_remaining += tile_delay_ms(tile);
        if (t->anim_ms_remaining < 0) {
          t->anim_ms_remaining = tile_delay_ms(tile);
        }
      }
    }
  }
}
