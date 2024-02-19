//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tile.hpp"
#include "my_ui.hpp"

void gfx_init_32x32(void)
{
  std::initializer_list< std::string > tiles = {
      // clang-format off
      "dungeon_entrance",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "dungeon_floor.1",
      "dungeon_floor.2",
      "dungeon_floor.3",
      "dungeon_floor.4",
      "",
      "",
      "",
      "",
      "",
      "",
      // ##############################################################################
      "dungeon_exit.0",
      "dungeon_exit.1",
      "dungeon_exit.2",
      "dungeon_exit.3",
      "dungeon_exit.4",
      "dungeon_exit.5",
      "dungeon_exit.6",
      "dungeon_exit.7",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      "",
      // ##############################################################################
  };
  const std::vector< std::string > arr(tiles);
  tile_load_arr("data/gfx/tiles_32x32.tga", "tiles_32x32", 32, 32, arr);
}
