//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tile.hpp"
#include "my_ui.hpp"

void gfx_init_16x16(void)
{
  const char *tiles[] = {
      // clang-format off
      // ##############################################################################
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
      "",
      "",
      "",
      "",
      // ##############################################################################
      "player.idle.0",
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
      // clang-format on
  };
  // If you need outlines
  // tile_load_arr_sprites("data/gfx/tiles_16x16.tga", "tiles_16x16", 16, 16, arr);
  tile_load_arr("data/gfx/tiles_16x16.tga", "tiles_16x16", 16, 16, ARRAY_SIZE(tiles), tiles);
}
