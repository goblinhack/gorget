//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_tile.hpp"
#include "my_time.hpp"
#include "my_tp.hpp"

//
// Assign an initial tile
//
void thing_anim_init(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  Tpp tp = thing_tp(t);

  auto ntiles = tp_tiles_size(tp, t->anim_type);
  if (ntiles) {
    auto index = pcg_rand() % ntiles;
    auto tile  = tp_tiles_get(tp, t->anim_type, index);
    if (tile) {
      t->tile_index = tile_global_index(tile);

      if (tp_is_animated_same_first_tile(tp)) {
        //
        // Same first tile e.g. level select tiles, we want to flash in sync and not out of order
        //
        t->anim_index = 0;
      } else if (tp_is_animated(tp)) {
        //
        // Choose a random first tile
        //
        auto i        = pcg_random_range_inclusive(0, ntiles - 1);
        t->anim_index = i;
      }
    }
  }
}

//
// Reset back to the first frame
//
void thing_anim_reset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  t->anim_index        = 0;
  t->anim_ms_remaining = 0;
}

//
// Animation time step
//
void thing_anim_step(Gamep g, Levelsp v, Levelp l, Thingp t, int time_step)
{
  TRACE_NO_INDENT();

  Tpp tp = thing_tp(t);

  if (! tp_is_animated(tp)) {
    return;
  }

  auto tile_index = t->tile_index;
  if (! tile_index) {
    return;
  }

  auto tile = tile_index_to_tile(tile_index);
  if (! tile) {
    return;
  }

  if (! tile_delay_ms(tile)) {
    return;
  }

  //
  // Decrement the remaining time
  //
  if (t->anim_ms_remaining > 0) {
    t->anim_ms_remaining -= time_step;
    if (t->anim_ms_remaining > 0) {
      return;
    }
  }

  if (0) {
    if (thing_is_mob(t)) {
      THING_LOG(t, "anim %s", tile_name_get(tile).c_str());
    }
  }

  //
  // If this is the final tile in an animation, we may want to remove the thing
  //
  if (tile_is_cleanup_on_end_of_anim(tile)) {
    if (! thing_is_scheduled_for_cleanup(t)) {
      //
      // Schedule for removal from the map and freeing
      //
      thing_is_scheduled_for_cleanup_set(g, v, l, t);
      return;
    }
  }

  t->anim_index++;
  if (t->anim_index >= tp_tiles_size(tp, t->anim_type)) {
    t->anim_index = 0;
  }

  tile          = tp_tiles_get(tp, t->anim_type, t->anim_index);
  t->tile_index = tile_global_index(tile);

  t->anim_ms_remaining += tile_delay_ms(tile);
  if (t->anim_ms_remaining < 0) {
    t->anim_ms_remaining = tile_delay_ms(tile);
  }
}
