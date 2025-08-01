
// Copyright goblinhack@gmail.com
//

#include "my_tile.hpp"

void gfx_init_lava(void)
{
  const char *lava_tiles[] = {
      /* clang-format off */
        // ##############################################################################
        "lava.IS_JOIN_TL2.0",
        "lava.IS_JOIN_T_3.0",
        "lava.IS_JOIN_TR2.0",
        "lava.IS_JOIN_TOP.0",
        "lava.IS_JOIN_X4_180.0",
        "lava.IS_JOIN_X4_270.0",
        "lava.IS_JOIN_X2_270.0",
        "lava.IS_JOIN_X2.0",
        "lava.IS_JOIN_X1_180.0",
        "lava.IS_JOIN_X1.0",
        "lava.IS_JOIN_X.0",
        "",
        // ##############################################################################
        "lava.IS_JOIN_T270_3.0",
        "lava.IS_JOIN_BLOCK.0",
        "lava.IS_JOIN_T90_3.0",
        "lava.IS_JOIN_VERT.0",
        "lava.IS_JOIN_X4_90.0",
        "lava.IS_JOIN_X4.0",
        "lava.IS_JOIN_X2_180.0",
        "lava.IS_JOIN_X2_90.0",
        "lava.IS_JOIN_X1_90.0",
        "lava.IS_JOIN_X1_270.0",
        "lava.IS_JOIN_X3_180.0",
        "lava.IS_JOIN_X3.0",
        // ##############################################################################
        "lava.IS_JOIN_BL2.0",
        "lava.IS_JOIN_T180_3.0",
        "lava.IS_JOIN_BR2.0",
        "lava.IS_JOIN_BOT.0",
        "lava.IS_JOIN_T_1.0",
        "lava.IS_JOIN_T_2.0",
        "lava.IS_JOIN_T270_2.0",
        "lava.IS_JOIN_T90_1.0",
        "lava.IS_JOIN_T.0",
        "lava.IS_JOIN_T90.0",
        "lava.IS_JOIN_TL.0",
        "lava.IS_JOIN_TR.0",
        // ##############################################################################
        "lava.IS_JOIN_LEFT.0",
        "lava.IS_JOIN_HORIZ.0",
        "lava.IS_JOIN_RIGHT.0",
        "lava.IS_JOIN_NODE.0",
        "lava.IS_JOIN_T180_2.0",
        "lava.IS_JOIN_T180_1.0",
        "lava.IS_JOIN_T270_1.0",
        "lava.IS_JOIN_T90_2.0",
        "lava.IS_JOIN_T270.0",
        "lava.IS_JOIN_T180.0",
        "lava.IS_JOIN_BL.0",
        "lava.IS_JOIN_BR.0",
        // ##############################################################################
        "lava.IS_JOIN_TL2.1",
        "lava.IS_JOIN_T_3.1",
        "lava.IS_JOIN_TR2.1",
        "lava.IS_JOIN_TOP.1",
        "lava.IS_JOIN_X4_180.1",
        "lava.IS_JOIN_X4_270.1",
        "lava.IS_JOIN_X2_270.1",
        "lava.IS_JOIN_X2.1",
        "lava.IS_JOIN_X1_180.1",
        "lava.IS_JOIN_X1.1",
        "lava.IS_JOIN_X.1",
        "",
        // ##############################################################################
        "lava.IS_JOIN_T270_3.1",
        "lava.IS_JOIN_BLOCK.1",
        "lava.IS_JOIN_T90_3.1",
        "lava.IS_JOIN_VERT.1",
        "lava.IS_JOIN_X4_90.1",
        "lava.IS_JOIN_X4.1",
        "lava.IS_JOIN_X2_180.1",
        "lava.IS_JOIN_X2_90.1",
        "lava.IS_JOIN_X1_90.1",
        "lava.IS_JOIN_X1_270.1",
        "lava.IS_JOIN_X3_180.1",
        "lava.IS_JOIN_X3.1",
        // ##############################################################################
        "lava.IS_JOIN_BL2.1",
        "lava.IS_JOIN_T180_3.1",
        "lava.IS_JOIN_BR2.1",
        "lava.IS_JOIN_BOT.1",
        "lava.IS_JOIN_T_1.1",
        "lava.IS_JOIN_T_2.1",
        "lava.IS_JOIN_T270_2.1",
        "lava.IS_JOIN_T90_1.1",
        "lava.IS_JOIN_T.1",
        "lava.IS_JOIN_T90.1",
        "lava.IS_JOIN_TL.1",
        "lava.IS_JOIN_TR.1",
        // ##############################################################################
        "lava.IS_JOIN_LEFT.1",
        "lava.IS_JOIN_HORIZ.1",
        "lava.IS_JOIN_RIGHT.1",
        "lava.IS_JOIN_NODE.1",
        "lava.IS_JOIN_T180_2.1",
        "lava.IS_JOIN_T180_1.1",
        "lava.IS_JOIN_T270_1.1",
        "lava.IS_JOIN_T90_2.1",
        "lava.IS_JOIN_T270.1",
        "lava.IS_JOIN_T180.1",
        "lava.IS_JOIN_BL.1",
        "lava.IS_JOIN_BR.1",
        // ##############################################################################
        "lava.IS_JOIN_TL2.2",
        "lava.IS_JOIN_T_3.2",
        "lava.IS_JOIN_TR2.2",
        "lava.IS_JOIN_TOP.2",
        "lava.IS_JOIN_X4_180.2",
        "lava.IS_JOIN_X4_270.2",
        "lava.IS_JOIN_X2_270.2",
        "lava.IS_JOIN_X2.2",
        "lava.IS_JOIN_X1_180.2",
        "lava.IS_JOIN_X1.2",
        "lava.IS_JOIN_X.2",
        "",
        // ##############################################################################
        "lava.IS_JOIN_T270_3.2",
        "lava.IS_JOIN_BLOCK.2",
        "lava.IS_JOIN_T90_3.2",
        "lava.IS_JOIN_VERT.2",
        "lava.IS_JOIN_X4_90.2",
        "lava.IS_JOIN_X4.2",
        "lava.IS_JOIN_X2_180.2",
        "lava.IS_JOIN_X2_90.2",
        "lava.IS_JOIN_X1_90.2",
        "lava.IS_JOIN_X1_270.2",
        "lava.IS_JOIN_X3_180.2",
        "lava.IS_JOIN_X3.2",
        // ##############################################################################
        "lava.IS_JOIN_BL2.2",
        "lava.IS_JOIN_T180_3.2",
        "lava.IS_JOIN_BR2.2",
        "lava.IS_JOIN_BOT.2",
        "lava.IS_JOIN_T_1.2",
        "lava.IS_JOIN_T_2.2",
        "lava.IS_JOIN_T270_2.2",
        "lava.IS_JOIN_T90_1.2",
        "lava.IS_JOIN_T.2",
        "lava.IS_JOIN_T90.2",
        "lava.IS_JOIN_TL.2",
        "lava.IS_JOIN_TR.2",
        // ##############################################################################
        "lava.IS_JOIN_LEFT.2",
        "lava.IS_JOIN_HORIZ.2",
        "lava.IS_JOIN_RIGHT.2",
        "lava.IS_JOIN_NODE.2",
        "lava.IS_JOIN_T180_2.2",
        "lava.IS_JOIN_T180_1.2",
        "lava.IS_JOIN_T270_1.2",
        "lava.IS_JOIN_T90_2.2",
        "lava.IS_JOIN_T270.2",
        "lava.IS_JOIN_T180.2",
        "lava.IS_JOIN_BL.2",
        "lava.IS_JOIN_BR.2",
        // ##############################################################################
        "lava.IS_JOIN_TL2.3",
        "lava.IS_JOIN_T_3.3",
        "lava.IS_JOIN_TR2.3",
        "lava.IS_JOIN_TOP.3",
        "lava.IS_JOIN_X4_180.3",
        "lava.IS_JOIN_X4_270.3",
        "lava.IS_JOIN_X2_270.3",
        "lava.IS_JOIN_X2.3",
        "lava.IS_JOIN_X1_180.3",
        "lava.IS_JOIN_X1.3",
        "lava.IS_JOIN_X.3",
        "",
        // ##############################################################################
        "lava.IS_JOIN_T270_3.3",
        "lava.IS_JOIN_BLOCK.3",
        "lava.IS_JOIN_T90_3.3",
        "lava.IS_JOIN_VERT.3",
        "lava.IS_JOIN_X4_90.3",
        "lava.IS_JOIN_X4.3",
        "lava.IS_JOIN_X2_180.3",
        "lava.IS_JOIN_X2_90.3",
        "lava.IS_JOIN_X1_90.3",
        "lava.IS_JOIN_X1_270.3",
        "lava.IS_JOIN_X3_180.3",
        "lava.IS_JOIN_X3.3",
        // ##############################################################################
        "lava.IS_JOIN_BL2.3",
        "lava.IS_JOIN_T180_3.3",
        "lava.IS_JOIN_BR2.3",
        "lava.IS_JOIN_BOT.3",
        "lava.IS_JOIN_T_1.3",
        "lava.IS_JOIN_T_2.3",
        "lava.IS_JOIN_T270_2.3",
        "lava.IS_JOIN_T90_1.3",
        "lava.IS_JOIN_T.3",
        "lava.IS_JOIN_T90.3",
        "lava.IS_JOIN_TL.3",
        "lava.IS_JOIN_TR.3",
        // ##############################################################################
        "lava.IS_JOIN_LEFT.3",
        "lava.IS_JOIN_HORIZ.3",
        "lava.IS_JOIN_RIGHT.3",
        "lava.IS_JOIN_NODE.3",
        "lava.IS_JOIN_T180_2.3",
        "lava.IS_JOIN_T180_1.3",
        "lava.IS_JOIN_T270_1.3",
        "lava.IS_JOIN_T90_2.3",
        "lava.IS_JOIN_T270.3",
        "lava.IS_JOIN_T180.3",
        "lava.IS_JOIN_BL.3",
        "lava.IS_JOIN_BR.3",
        // ##############################################################################
        "lava.IS_JOIN_TL2.4",
        "lava.IS_JOIN_T_3.4",
        "lava.IS_JOIN_TR2.4",
        "lava.IS_JOIN_TOP.4",
        "lava.IS_JOIN_X4_180.4",
        "lava.IS_JOIN_X4_270.4",
        "lava.IS_JOIN_X2_270.4",
        "lava.IS_JOIN_X2.4",
        "lava.IS_JOIN_X1_180.4",
        "lava.IS_JOIN_X1.4",
        "lava.IS_JOIN_X.4",
        "",
        // ##############################################################################
        "lava.IS_JOIN_T270_3.4",
        "lava.IS_JOIN_BLOCK.4",
        "lava.IS_JOIN_T90_3.4",
        "lava.IS_JOIN_VERT.4",
        "lava.IS_JOIN_X4_90.4",
        "lava.IS_JOIN_X4.4",
        "lava.IS_JOIN_X2_180.4",
        "lava.IS_JOIN_X2_90.4",
        "lava.IS_JOIN_X1_90.4",
        "lava.IS_JOIN_X1_270.4",
        "lava.IS_JOIN_X3_180.4",
        "lava.IS_JOIN_X3.4",
        // ##############################################################################
        "lava.IS_JOIN_BL2.4",
        "lava.IS_JOIN_T180_3.4",
        "lava.IS_JOIN_BR2.4",
        "lava.IS_JOIN_BOT.4",
        "lava.IS_JOIN_T_1.4",
        "lava.IS_JOIN_T_2.4",
        "lava.IS_JOIN_T270_2.4",
        "lava.IS_JOIN_T90_1.4",
        "lava.IS_JOIN_T.4",
        "lava.IS_JOIN_T90.4",
        "lava.IS_JOIN_TL.4",
        "lava.IS_JOIN_TR.4",
        // ##############################################################################
        "lava.IS_JOIN_LEFT.4",
        "lava.IS_JOIN_HORIZ.4",
        "lava.IS_JOIN_RIGHT.4",
        "lava.IS_JOIN_NODE.4",
        "lava.IS_JOIN_T180_2.4",
        "lava.IS_JOIN_T180_1.4",
        "lava.IS_JOIN_T270_1.4",
        "lava.IS_JOIN_T90_2.4",
        "lava.IS_JOIN_T270.4",
        "lava.IS_JOIN_T180.4",
        "lava.IS_JOIN_BL.4",
        "lava.IS_JOIN_BR.4",
        // ##############################################################################
        "lava.IS_JOIN_TL2.5",
        "lava.IS_JOIN_T_3.5",
        "lava.IS_JOIN_TR2.5",
        "lava.IS_JOIN_TOP.5",
        "lava.IS_JOIN_X4_180.5",
        "lava.IS_JOIN_X4_270.5",
        "lava.IS_JOIN_X2_270.5",
        "lava.IS_JOIN_X2.5",
        "lava.IS_JOIN_X1_180.5",
        "lava.IS_JOIN_X1.5",
        "lava.IS_JOIN_X.5",
        "",
        // ##############################################################################
        "lava.IS_JOIN_T270_3.5",
        "lava.IS_JOIN_BLOCK.5",
        "lava.IS_JOIN_T90_3.5",
        "lava.IS_JOIN_VERT.5",
        "lava.IS_JOIN_X4_90.5",
        "lava.IS_JOIN_X4.5",
        "lava.IS_JOIN_X2_180.5",
        "lava.IS_JOIN_X2_90.5",
        "lava.IS_JOIN_X1_90.5",
        "lava.IS_JOIN_X1_270.5",
        "lava.IS_JOIN_X3_180.5",
        "lava.IS_JOIN_X3.5",
        // ##############################################################################
        "lava.IS_JOIN_BL2.5",
        "lava.IS_JOIN_T180_3.5",
        "lava.IS_JOIN_BR2.5",
        "lava.IS_JOIN_BOT.5",
        "lava.IS_JOIN_T_1.5",
        "lava.IS_JOIN_T_2.5",
        "lava.IS_JOIN_T270_2.5",
        "lava.IS_JOIN_T90_1.5",
        "lava.IS_JOIN_T.5",
        "lava.IS_JOIN_T90.5",
        "lava.IS_JOIN_TL.5",
        "lava.IS_JOIN_TR.5",
        // ##############################################################################
        "lava.IS_JOIN_LEFT.5",
        "lava.IS_JOIN_HORIZ.5",
        "lava.IS_JOIN_RIGHT.5",
        "lava.IS_JOIN_NODE.5",
        "lava.IS_JOIN_T180_2.5",
        "lava.IS_JOIN_T180_1.5",
        "lava.IS_JOIN_T270_1.5",
        "lava.IS_JOIN_T90_2.5",
        "lava.IS_JOIN_T270.5",
        "lava.IS_JOIN_T180.5",
        "lava.IS_JOIN_BL.5",
        "lava.IS_JOIN_BR.5",
        // ##############################################################################
        "lava.IS_JOIN_TL2.6",
        "lava.IS_JOIN_T_3.6",
        "lava.IS_JOIN_TR2.6",
        "lava.IS_JOIN_TOP.6",
        "lava.IS_JOIN_X4_180.6",
        "lava.IS_JOIN_X4_270.6",
        "lava.IS_JOIN_X2_270.6",
        "lava.IS_JOIN_X2.6",
        "lava.IS_JOIN_X1_180.6",
        "lava.IS_JOIN_X1.6",
        "lava.IS_JOIN_X.6",
        "",
        // ##############################################################################
        "lava.IS_JOIN_T270_3.6",
        "lava.IS_JOIN_BLOCK.6",
        "lava.IS_JOIN_T90_3.6",
        "lava.IS_JOIN_VERT.6",
        "lava.IS_JOIN_X4_90.6",
        "lava.IS_JOIN_X4.6",
        "lava.IS_JOIN_X2_180.6",
        "lava.IS_JOIN_X2_90.6",
        "lava.IS_JOIN_X1_90.6",
        "lava.IS_JOIN_X1_270.6",
        "lava.IS_JOIN_X3_180.6",
        "lava.IS_JOIN_X3.6",
        // ##############################################################################
        "lava.IS_JOIN_BL2.6",
        "lava.IS_JOIN_T180_3.6",
        "lava.IS_JOIN_BR2.6",
        "lava.IS_JOIN_BOT.6",
        "lava.IS_JOIN_T_1.6",
        "lava.IS_JOIN_T_2.6",
        "lava.IS_JOIN_T270_2.6",
        "lava.IS_JOIN_T90_1.6",
        "lava.IS_JOIN_T.6",
        "lava.IS_JOIN_T90.6",
        "lava.IS_JOIN_TL.6",
        "lava.IS_JOIN_TR.6",
        // ##############################################################################
        "lava.IS_JOIN_LEFT.6",
        "lava.IS_JOIN_HORIZ.6",
        "lava.IS_JOIN_RIGHT.6",
        "lava.IS_JOIN_NODE.6",
        "lava.IS_JOIN_T180_2.6",
        "lava.IS_JOIN_T180_1.6",
        "lava.IS_JOIN_T270_1.6",
        "lava.IS_JOIN_T90_2.6",
        "lava.IS_JOIN_T270.6",
        "lava.IS_JOIN_T180.6",
        "lava.IS_JOIN_BL.6",
        "lava.IS_JOIN_BR.6",
        // ##############################################################################
        "lava.IS_JOIN_TL2.7",
        "lava.IS_JOIN_T_3.7",
        "lava.IS_JOIN_TR2.7",
        "lava.IS_JOIN_TOP.7",
        "lava.IS_JOIN_X4_180.7",
        "lava.IS_JOIN_X4_270.7",
        "lava.IS_JOIN_X2_270.7",
        "lava.IS_JOIN_X2.7",
        "lava.IS_JOIN_X1_180.7",
        "lava.IS_JOIN_X1.7",
        "lava.IS_JOIN_X.7",
        "",
        // ##############################################################################
        "lava.IS_JOIN_T270_3.7",
        "lava.IS_JOIN_BLOCK.7",
        "lava.IS_JOIN_T90_3.7",
        "lava.IS_JOIN_VERT.7",
        "lava.IS_JOIN_X4_90.7",
        "lava.IS_JOIN_X4.7",
        "lava.IS_JOIN_X2_180.7",
        "lava.IS_JOIN_X2_90.7",
        "lava.IS_JOIN_X1_90.7",
        "lava.IS_JOIN_X1_270.7",
        "lava.IS_JOIN_X3_180.7",
        "lava.IS_JOIN_X3.7",
        // ##############################################################################
        "lava.IS_JOIN_BL2.7",
        "lava.IS_JOIN_T180_3.7",
        "lava.IS_JOIN_BR2.7",
        "lava.IS_JOIN_BOT.7",
        "lava.IS_JOIN_T_1.7",
        "lava.IS_JOIN_T_2.7",
        "lava.IS_JOIN_T270_2.7",
        "lava.IS_JOIN_T90_1.7",
        "lava.IS_JOIN_T.7",
        "lava.IS_JOIN_T90.7",
        "lava.IS_JOIN_TL.7",
        "lava.IS_JOIN_TR.7",
        // ##############################################################################
        "lava.IS_JOIN_LEFT.7",
        "lava.IS_JOIN_HORIZ.7",
        "lava.IS_JOIN_RIGHT.7",
        "lava.IS_JOIN_NODE.7",
        "lava.IS_JOIN_T180_2.7",
        "lava.IS_JOIN_T180_1.7",
        "lava.IS_JOIN_T270_1.7",
        "lava.IS_JOIN_T90_2.7",
        "lava.IS_JOIN_T270.7",
        "lava.IS_JOIN_T180.7",
        "lava.IS_JOIN_BL.7",
        "lava.IS_JOIN_BR.7",
        // ##############################################################################
      /* clang-format on */
  };
  tile_load_arr("data/gfx/tiles_lava.tga", "tiles_lava", INNER_TILE_WIDTH, INNER_TILE_HEIGHT, ARRAY_SIZE(lava_tiles),
                lava_tiles);
}
