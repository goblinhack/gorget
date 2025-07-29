//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_tile.hpp"

//
// Assign an initial tile
//
// Or reset back to the first frame
//
void thing_anim_init(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  Tpp tp = thing_tp(t);

  t->anim_index        = 0;
  t->anim_ms_remaining = 0;

  auto ntiles = tp_tiles_size(tp, t->anim_type);
  if (ntiles) {
    auto index = pcg_rand() % ntiles;
    auto tile  = tp_tiles_get(tp, t->anim_type, index);
    if (tile) {
      switch (t->anim_type) {
        case THING_ANIM_JOIN_BL :
        case THING_ANIM_JOIN_BL2 :
        case THING_ANIM_JOIN_BLOCK :
        case THING_ANIM_JOIN_BOT :
        case THING_ANIM_JOIN_BR :
        case THING_ANIM_JOIN_BR2 :
        case THING_ANIM_JOIN_HORIZ :
        case THING_ANIM_JOIN_HORIZ2 :
        case THING_ANIM_JOIN_LEFT :
        case THING_ANIM_JOIN_NODE :
        case THING_ANIM_JOIN_RIGHT :
        case THING_ANIM_JOIN_T_1 :
        case THING_ANIM_JOIN_T_2 :
        case THING_ANIM_JOIN_T_3 :
        case THING_ANIM_JOIN_T :
        case THING_ANIM_JOIN_T180_1 :
        case THING_ANIM_JOIN_T180_2 :
        case THING_ANIM_JOIN_T180_3 :
        case THING_ANIM_JOIN_T180 :
        case THING_ANIM_JOIN_T270_1 :
        case THING_ANIM_JOIN_T270_2 :
        case THING_ANIM_JOIN_T270_3 :
        case THING_ANIM_JOIN_T270 :
        case THING_ANIM_JOIN_T90_1 :
        case THING_ANIM_JOIN_T90_2 :
        case THING_ANIM_JOIN_T90_3 :
        case THING_ANIM_JOIN_T90 :
        case THING_ANIM_JOIN_TL :
        case THING_ANIM_JOIN_TL2 :
        case THING_ANIM_JOIN_TOP :
        case THING_ANIM_JOIN_TR :
        case THING_ANIM_JOIN_TR2 :
        case THING_ANIM_JOIN_VERT :
        case THING_ANIM_JOIN_VERT2 :
        case THING_ANIM_JOIN_X :
        case THING_ANIM_JOIN_X1_180 :
        case THING_ANIM_JOIN_X1_270 :
        case THING_ANIM_JOIN_X1_90 :
        case THING_ANIM_JOIN_X1 :
        case THING_ANIM_JOIN_X2_180 :
        case THING_ANIM_JOIN_X2_270 :
        case THING_ANIM_JOIN_X2_90 :
        case THING_ANIM_JOIN_X2 :
        case THING_ANIM_JOIN_X3_180 :
        case THING_ANIM_JOIN_X3 :
        case THING_ANIM_JOIN_X4_180 :
        case THING_ANIM_JOIN_X4_270 :
        case THING_ANIM_JOIN_X4_90 :
        case THING_ANIM_JOIN_X4 :
        case THING_ANIM_IDLE :
          if (tp_is_animated_sync_first(tp)) {
            //
            // Same first tile e.g. level select tiles, we want to flash in sync and not out of order
            //
            t->anim_index = 0;
          } else {
            //
            // Choose a random first tile. Cannot use animated check here, as things like grass
            // want different tiles, but are not animated.
            //
            auto i        = pcg_random_range_inclusive(0, ntiles - 1);
            t->anim_index = i;
          }
          break;
        case THING_ANIM_OPEN :
        case THING_ANIM_DEAD :
        case THING_ANIM_BURNT :
          //
          // If changing to a non idle state, we want to usually start at tile 0, e.g. for dead animations
          //
          t->anim_index = 0;
          break;
        case THING_ANIM_ENUM_MAX : ERR("unexpected enum"); break;
      }

      tile          = tp_tiles_get(tp, t->anim_type, t->anim_index);
      t->tile_index = tile_global_index(tile);
    }
  }
}

//
// Animation time step
//
void thing_anim_time_step(Gamep g, Levelsp v, Levelp l, Thingp t, int time_step)
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

  if (0) {
    if (thing_is_mob(t)) {
      THING_LOG(t, "anim %s index %d", tile_name_get(tile).c_str(), t->anim_index);
    }
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

  //
  // If this is the final tile in an animation, we may want to remove the thing
  //
  if (tile_is_cleanup_on_end_of_anim(tile)) {
    //
    // Schedule for removal from the map and freeing
    //
    thing_is_scheduled_for_cleanup_set(g, v, l, t);
    return;
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
