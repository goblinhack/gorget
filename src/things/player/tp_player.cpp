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

  auto tp = tp_load("player");
  // begin sort marker1 {
  tp->z_depth_set(MAP_DEPTH_PLAYER);
  tp->is_player               = true;
  tp->is_blit_on_ground       = true;
  tp->is_blit_square_outlined = true;
  tp->is_animated_can_hflip   = true;
  // end sort marker1 }

#if 0
  auto delay = 100;

  for (auto frame = 0; frame < 6; frame++) {
    auto tile      = tile_find_mand("player.run." + std::to_string(frame));
    tile->delay_ms = delay;
    tp->tiles.push_back(tile);
  }
#endif

  return true;
}
