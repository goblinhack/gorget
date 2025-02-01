//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "../../my_minimal.hpp"
#include "../../my_tile.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_player(void)
{
  for (auto player = 1; player <= 4; player++) {
    auto name = "player" + std::to_string(player);
    auto tp   = tp_load(name.c_str());

    // begin sort marker1 {
    tp_flag_set(tp, is_animated_can_hflip, true);
    tp_flag_set(tp, is_blit_on_ground, true);
    tp_flag_set(tp, is_player, true);
    tp_flag_set(tp, is_tickable, true);
    tp_speed_set(tp, 100);
    tp_z_prio_set(tp, MAP_Z_PRIO_INFRONT);
    // end sort marker1 }

    auto delay = 100;

    for (auto frame = 0; frame < 1; frame++) {
      auto tile = tile_find_mand(name + ".idle." + std::to_string(frame));
      tile_delay_ms_set(tile, delay);
      tp_tiles_push_back(tp, tile);
    }
  }

  return true;
}
