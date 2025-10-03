//
// Copyright goblinhack@gmail.com
//

#include "my_tile.hpp"

void gfx_init_chasm(void)
{
  const char *tiles[] = {
      /* clang-format off */
        // ##############################################################################
        "chasm.IS_JOIN_TL2",
        "chasm.IS_JOIN_T_3",
        "chasm.IS_JOIN_TR2",
        "chasm.IS_JOIN_TOP",
        "chasm.IS_JOIN_X4_180",
        "chasm.IS_JOIN_X4_270",
        "chasm.IS_JOIN_X2_270",
        "chasm.IS_JOIN_X2",
        "chasm.IS_JOIN_X1_180",
        "chasm.IS_JOIN_X1",
        "chasm.IS_JOIN_X",
        "",
        // ##############################################################################
        "chasm.IS_JOIN_T270_3",
        "chasm.IS_JOIN_BLOCK",
        "chasm.IS_JOIN_T90_3",
        "chasm.IS_JOIN_VERT",
        "chasm.IS_JOIN_X4_90",
        "chasm.IS_JOIN_X4",
        "chasm.IS_JOIN_X2_180",
        "chasm.IS_JOIN_X2_90",
        "chasm.IS_JOIN_X1_90",
        "chasm.IS_JOIN_X1_270",
        "chasm.IS_JOIN_X3_180",
        "chasm.IS_JOIN_X3",
        // ##############################################################################
        "chasm.IS_JOIN_BL2",
        "chasm.IS_JOIN_T180_3",
        "chasm.IS_JOIN_BR2",
        "chasm.IS_JOIN_BOT",
        "chasm.IS_JOIN_T_1",
        "chasm.IS_JOIN_T_2",
        "chasm.IS_JOIN_T270_2",
        "chasm.IS_JOIN_T90_1",
        "chasm.IS_JOIN_T",
        "chasm.IS_JOIN_T90",
        "chasm.IS_JOIN_TL",
        "chasm.IS_JOIN_TR",
        // ##############################################################################
        "chasm.IS_JOIN_LEFT",
        "chasm.IS_JOIN_HORIZ",
        "chasm.IS_JOIN_RIGHT",
        "chasm.IS_JOIN_NODE",
        "chasm.IS_JOIN_T180_2",
        "chasm.IS_JOIN_T180_1",
        "chasm.IS_JOIN_T270_1",
        "chasm.IS_JOIN_T90_2",
        "chasm.IS_JOIN_T270",
        "chasm.IS_JOIN_T180",
        "chasm.IS_JOIN_BL",
        "chasm.IS_JOIN_BR",
        // ##############################################################################
      /* clang-format on */
  };
  tile_load_arr_sprites("data/gfx/tiles_chasm.tga", "tiles_chasm", INNER_TILE_WIDTH, INNER_TILE_HEIGHT,
                        ARRAY_SIZE(tiles), tiles);
}
