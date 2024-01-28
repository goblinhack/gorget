//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tile.hpp"
#include "my_ui.hpp"

void gfx_init_48x48(void)
{
  std::initializer_list< std::string > tiles = {
      // clang-format off
      "world_mountains.0",
      "world_forest.0",
      "",
      "",
      "",
      "",
      "",
      "",
      // clang-format on
  };
  const std::vector< std::string > arr(tiles);
  tile_load_arr("data/gfx/tiles_48x48.tga", "tiles_48x48", 48, 48, arr);
}
