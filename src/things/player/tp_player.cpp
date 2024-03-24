//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "../../my_depth.hpp"
#include "../../my_main.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_player(void)
{
  TRACE_NO_INDENT();

  for (auto player = 1; player <= 4; player++) {
    auto name = "player" + std::to_string(player);
    auto tp   = tp_load(name);

    // begin sort marker1 {
    tp->z_depth_set(MAP_DEPTH_PLAYER);
    tp->is_player         = true;
    tp->player_index   = player - 1;
    tp->is_blit_on_ground = true;
    // end sort marker1 }

    auto delay = 100;

    for (auto frame = 0; frame < 1; frame++) {
      auto tile      = tile_find_mand(name + ".idle." + std::to_string(frame));
      tile->delay_ms = delay;
      tp->tiles.push_back(tile);
    }
  }

  return true;
}
