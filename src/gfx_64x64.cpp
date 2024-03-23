//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tile.hpp"
#include "my_ui.hpp"

void gfx_init_64x64(void)
{
  {
    std::initializer_list< std::string > tiles = {
        /* clang-format off */
        // ##############################################################################
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        // ##############################################################################
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        // ##############################################################################
        /* clang-format on */
    };
    const std::vector< std::string > arr(tiles);
    tile_load_arr("data/gfx/tiles_64x64.tga", "tiles_64x64", 64, 64, arr);
  }
}
