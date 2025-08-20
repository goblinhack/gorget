//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tp_callbacks.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

bool tp_load_explosion(void)
{
  TRACE_NO_INDENT();

  auto tp   = tp_load("explosion"); // keep as string for scripts
  auto name = tp_name(tp);

  // begin sort marker1 {
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_explosion);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_teleport_blocked);
  tp_flag_set(tp, is_wait_on_anim_when_dead);
  tp_temperature_initial_set(tp, 1000); // celsius
  tp_weight_set(tp, WEIGHT_NONE);       // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  auto delay = 50;

  for (auto frame = 0; frame < 6; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);

    if (frame == 5) {
      tile_is_cleanup_on_end_of_anim_set(tile);
    }
  }

  return true;
}
