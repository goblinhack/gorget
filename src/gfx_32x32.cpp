//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tile.hpp"
#include "my_ui.hpp"

void gfx_init_32x32(void)
{
  {
    const char *tiles[] = {
        /* clang-format off */
        // ##############################################################################
        "exit.0",
        "exit.1",
        "exit.2",
        "exit.3",
        "exit.4",
        "exit.5",
        "exit.6",
        "exit.7",
        // ##############################################################################
        /* clang-format on */
    };
    tile_load_arr("data/gfx/tiles_32x32.tga", "tiles_32x32", 32, 32, ARRAY_SIZE(tiles), tiles);
  }
}
