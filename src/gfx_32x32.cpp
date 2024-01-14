//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tile.hpp"
#include "my_ui.hpp"

void gfx_init_32x32(void)
{
  std::initializer_list< std::string > tiles = {
      // clang-format off
      "entrance", "",       "",       "",       "",       "",       "",       "",
      "exit.0",   "exit.1", "exit.2", "exit.3", "exit.4", "exit.5", "exit.6", "exit.7",
      // clang-format on
  };
  const std::vector< std::string > arr(tiles);
  tile_load_arr("data/gfx/tiles_32x32.tga", "tiles_32x32", 32, 32, arr);
}
