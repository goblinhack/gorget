//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tile.hpp"
#include "my_ui.hpp"

void gfx_init_background(void)
{
  std::initializer_list< std::string > tiles = {
      // clang-format off
      "background1",
      // clang-format on
  };
  const std::vector< std::string > arr(tiles);
  tile_load_arr("data/gfx/background1.tga", "background1", (MAP_WIDTH * TILE_WIDTH), (MAP_HEIGHT * TILE_HEIGHT), arr);
}
