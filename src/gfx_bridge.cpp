//
// Copyright goblinhack@gmail.com
//

#include "my_tile.hpp"

void gfx_init_bridge(void)
{
  const char *tiles[] = {
      /* clang-format off */
        // ##############################################################################
        "bridge.IS_JOIN_TL2",
        "bridge.IS_JOIN_T_3",
        "bridge.IS_JOIN_TR2",
        "bridge.IS_JOIN_TOP",
        "bridge.IS_JOIN_X4_180",
        "bridge.IS_JOIN_X4_270",
        "bridge.IS_JOIN_X2_270",
        "bridge.IS_JOIN_X2",
        "bridge.IS_JOIN_X1_180",
        "bridge.IS_JOIN_X1",
        "bridge.IS_JOIN_X",
        "",
        // ##############################################################################
        "bridge.IS_JOIN_T270_3",
        "bridge.IS_JOIN_BLOCK",
        "bridge.IS_JOIN_T90_3",
        "bridge.IS_JOIN_VERT",
        "bridge.IS_JOIN_X4_90",
        "bridge.IS_JOIN_X4",
        "bridge.IS_JOIN_X2_180",
        "bridge.IS_JOIN_X2_90",
        "bridge.IS_JOIN_X1_90",
        "bridge.IS_JOIN_X1_270",
        "bridge.IS_JOIN_X3_180",
        "bridge.IS_JOIN_X3",
        // ##############################################################################
        "bridge.IS_JOIN_BL2",
        "bridge.IS_JOIN_T180_3",
        "bridge.IS_JOIN_BR2",
        "bridge.IS_JOIN_BOT",
        "bridge.IS_JOIN_T_1",
        "bridge.IS_JOIN_T_2",
        "bridge.IS_JOIN_T270_2",
        "bridge.IS_JOIN_T90_1",
        "bridge.IS_JOIN_T",
        "bridge.IS_JOIN_T90",
        "bridge.IS_JOIN_TL",
        "bridge.IS_JOIN_TR",
        // ##############################################################################
        "bridge.IS_JOIN_LEFT",
        "bridge.IS_JOIN_HORIZ",
        "bridge.IS_JOIN_RIGHT",
        "bridge.IS_JOIN_NODE",
        "bridge.IS_JOIN_T180_2",
        "bridge.IS_JOIN_T180_1",
        "bridge.IS_JOIN_T270_1",
        "bridge.IS_JOIN_T90_2",
        "bridge.IS_JOIN_T270",
        "bridge.IS_JOIN_T180",
        "bridge.IS_JOIN_BL",
        "bridge.IS_JOIN_BR",
        // ##############################################################################
      /* clang-format on */
  };
  tile_load_arr_sprites("data/gfx/tiles_bridge.tga", "tiles_bridge", INNER_TILE_WIDTH, INNER_TILE_HEIGHT,
                        ARRAY_SIZE(tiles), tiles);
}
