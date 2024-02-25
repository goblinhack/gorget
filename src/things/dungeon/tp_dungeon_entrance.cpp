//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "../../my_depth.hpp"
#include "../../my_main.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_dungeon_entrance(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("dungeon_entrance");
  // begin sort marker1 {
  tp->z_depth_set(MAP_DEPTH_OBJ1);
  tp->is_dungeon_entrance = true;
  tp->is_blit_on_ground   = true;
  // end sort marker1 }

  tp->tiles.push_back(tile_find("dungeon_entrance"));

  return true;
}
