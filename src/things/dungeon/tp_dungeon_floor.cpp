//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "../../my_level_data.hpp"
#include "../../my_main.hpp"
#include "../../my_tp.hpp"
#include "../../my_tps.hpp"

bool tp_load_dungeon_floor(void)
{
  TRACE_NO_INDENT();

  auto tp = tp_load("dungeon_floor");
  // begin sort marker1 {
  tp->z_depth_set(MAP_DEPTH_FLOOR);
  tp->is_dungeon_floor  = true;
  tp->is_blit_on_ground = true;
  // end sort marker1 }

  tp->tiles.push_back(tile_find_mand("dungeon_floor.1"));
  tp->tiles.push_back(tile_find_mand("dungeon_floor.2"));
  tp->tiles.push_back(tile_find_mand("dungeon_floor.3"));
  tp->tiles.push_back(tile_find_mand("dungeon_floor.4"));

  return true;
}
