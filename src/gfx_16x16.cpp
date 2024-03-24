//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tile.hpp"
#include "my_ui.hpp"

void gfx_init_16x16(void)
{
  std::initializer_list< std::string > tiles = {
      // clang-format off
      // ##############################################################################
      "floor.1",
      "floor.2",
      "floor.3",
      "floor.4",
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
      "",
      "",
      // ##############################################################################
      "player1.idle.0",
      "player2.idle.0",
      "player3.idle.0",
      "player4.idle.0",
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
      "",
      "",
      // ##############################################################################
  };
  const std::vector< std::string > arr(tiles);
  // If you need outlines
  // tile_load_arr_sprites("data/gfx/tiles_16x16.tga", "tiles_16x16", 16, 16, arr);
  tile_load_arr("data/gfx/tiles_16x16.tga", "tiles_16x16", 16, 16, arr);
}
