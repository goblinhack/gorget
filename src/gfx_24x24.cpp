//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tile.hpp"
#include "my_ui.hpp"

void gfx_init_24x24(void)
{
  {
    const char *tiles[] = {
        /* clang-format off */
        // ##############################################################################
        "wall1.IS_JOIN_TL2",
        "wall1.IS_JOIN_T_3",
        "wall1.IS_JOIN_TR2",
        "wall1.IS_JOIN_TOP",
        "wall1.IS_JOIN_X4_180",
        "wall1.IS_JOIN_X4_270",
        "wall1.IS_JOIN_X2_270",
        "wall1.IS_JOIN_X2",
        "wall1.IS_JOIN_X1_180",
        "wall1.IS_JOIN_X1",
        "wall1.IS_JOIN_X",
        "",
        // ##############################################################################
        "wall1.IS_JOIN_T270_3",
        "wall1.IS_JOIN_BLOCK",
        "wall1.IS_JOIN_T90_3",
        "wall1.IS_JOIN_VERT",
        "wall1.IS_JOIN_X4_90",
        "wall1.IS_JOIN_X4",
        "wall1.IS_JOIN_X2_180",
        "wall1.IS_JOIN_X2_90",
        "wall1.IS_JOIN_X1_90",
        "wall1.IS_JOIN_X1_270",
        "wall1.IS_JOIN_X3_180",
        "wall1.IS_JOIN_X3",
        // ##############################################################################
        "wall1.IS_JOIN_BL2",
        "wall1.IS_JOIN_T180_3",
        "wall1.IS_JOIN_BR2",
        "wall1.IS_JOIN_BOT",
        "wall1.IS_JOIN_T_1",
        "wall1.IS_JOIN_T_2",
        "wall1.IS_JOIN_T270_2",
        "wall1.IS_JOIN_T90_1",
        "wall1.IS_JOIN_T",
        "wall1.IS_JOIN_T90",
        "wall1.IS_JOIN_TL",
        "wall1.IS_JOIN_TR",
        // ##############################################################################
        "wall1.IS_JOIN_LEFT",
        "wall1.IS_JOIN_HORIZ",
        "wall1.IS_JOIN_RIGHT",
        "wall1.IS_JOIN_NODE",
        "wall1.IS_JOIN_T180_2",
        "wall1.IS_JOIN_T180_1",
        "wall1.IS_JOIN_T270_1",
        "wall1.IS_JOIN_T90_2",
        "wall1.IS_JOIN_T270",
        "wall1.IS_JOIN_T180",
        "wall1.IS_JOIN_BL",
        "wall1.IS_JOIN_BR",
        // ##############################################################################
        "wall1.IS_JOIN_TL2.shadow",
        "wall1.IS_JOIN_T_3.shadow",
        "wall1.IS_JOIN_TR2.shadow",
        "wall1.IS_JOIN_TOP.shadow",
        "wall1.IS_JOIN_X4_180.shadow",
        "wall1.IS_JOIN_X4_270.shadow",
        "wall1.IS_JOIN_X2_270.shadow",
        "wall1.IS_JOIN_X2.shadow",
        "wall1.IS_JOIN_X1_180.shadow",
        "wall1.IS_JOIN_X1.shadow",
        "wall1.IS_JOIN_X.shadow",
        "",
        // ##############################################################################
        "wall1.IS_JOIN_T270_3.shadow",
        "wall1.IS_JOIN_BLOCK.shadow",
        "wall1.IS_JOIN_T90_3.shadow",
        "wall1.IS_JOIN_VERT.shadow",
        "wall1.IS_JOIN_X4_90.shadow",
        "wall1.IS_JOIN_X4.shadow",
        "wall1.IS_JOIN_X2_180.shadow",
        "wall1.IS_JOIN_X2_90.shadow",
        "wall1.IS_JOIN_X1_90.shadow",
        "wall1.IS_JOIN_X1_270.shadow",
        "wall1.IS_JOIN_X3_180.shadow",
        "wall1.IS_JOIN_X3.shadow",
        // ##############################################################################
        "wall1.IS_JOIN_BL2.shadow",
        "wall1.IS_JOIN_T180_3.shadow",
        "wall1.IS_JOIN_BR2.shadow",
        "wall1.IS_JOIN_BOT.shadow",
        "wall1.IS_JOIN_T_1.shadow",
        "wall1.IS_JOIN_T_2.shadow",
        "wall1.IS_JOIN_T270_2.shadow",
        "wall1.IS_JOIN_T90_1.shadow",
        "wall1.IS_JOIN_T.shadow",
        "wall1.IS_JOIN_T90.shadow",
        "wall1.IS_JOIN_TL.shadow",
        "wall1.IS_JOIN_TR.shadow",
        // ##############################################################################
        "wall1.IS_JOIN_LEFT.shadow",
        "wall1.IS_JOIN_HORIZ.shadow",
        "wall1.IS_JOIN_RIGHT.shadow",
        "wall1.IS_JOIN_NODE.shadow",
        "wall1.IS_JOIN_T180_2.shadow",
        "wall1.IS_JOIN_T180_1.shadow",
        "wall1.IS_JOIN_T270_1.shadow",
        "wall1.IS_JOIN_T90_2.shadow",
        "wall1.IS_JOIN_T270.shadow",
        "wall1.IS_JOIN_T180.shadow",
        "wall1.IS_JOIN_BL.shadow",
        "wall1.IS_JOIN_BR.shadow",
        // ##############################################################################
        "door.IS_JOIN_TL2",
        "door.IS_JOIN_T_3",
        "door.IS_JOIN_TR2",
        "door.IS_JOIN_TOP",
        "door.IS_JOIN_X4_180",
        "door.IS_JOIN_X4_270",
        "door.IS_JOIN_X2_270",
        "door.IS_JOIN_X2",
        "door.IS_JOIN_X1_180",
        "door.IS_JOIN_X1",
        "door.IS_JOIN_X",
        "",
        // ##############################################################################
        "door.IS_JOIN_T270_3",
        "door.IS_JOIN_BLOCK",
        "door.IS_JOIN_T90_3",
        "door.IS_JOIN_VERT",
        "door.IS_JOIN_X4_90",
        "door.IS_JOIN_X4",
        "door.IS_JOIN_X2_180",
        "door.IS_JOIN_X2_90",
        "door.IS_JOIN_X1_90",
        "door.IS_JOIN_X1_270",
        "door.IS_JOIN_X3_180",
        "door.IS_JOIN_X3",
        // ##############################################################################
        "door.IS_JOIN_BL2",
        "door.IS_JOIN_T180_3",
        "door.IS_JOIN_BR2",
        "door.IS_JOIN_BOT",
        "door.IS_JOIN_T_1",
        "door.IS_JOIN_T_2",
        "door.IS_JOIN_T270_2",
        "door.IS_JOIN_T90_1",
        "door.IS_JOIN_T",
        "door.IS_JOIN_T90",
        "door.IS_JOIN_TL",
        "door.IS_JOIN_TR",
        // ##############################################################################
        "door.IS_JOIN_LEFT",
        "door.IS_JOIN_HORIZ",
        "door.IS_JOIN_RIGHT",
        "door.IS_JOIN_NODE",
        "door.IS_JOIN_T180_2",
        "door.IS_JOIN_T180_1",
        "door.IS_JOIN_T270_1",
        "door.IS_JOIN_T90_2",
        "door.IS_JOIN_T270",
        "door.IS_JOIN_T180",
        "door.IS_JOIN_BL",
        "door.IS_JOIN_BR",
        // ##############################################################################
        "door1.IS_JOIN_TL2.shadow",
        "door1.IS_JOIN_T_3.shadow",
        "door1.IS_JOIN_TR2.shadow",
        "door1.IS_JOIN_TOP.shadow",
        "door1.IS_JOIN_X4_180.shadow",
        "door1.IS_JOIN_X4_270.shadow",
        "door1.IS_JOIN_X2_270.shadow",
        "door1.IS_JOIN_X2.shadow",
        "door1.IS_JOIN_X1_180.shadow",
        "door1.IS_JOIN_X1.shadow",
        "door1.IS_JOIN_X.shadow",
        "",
        // ##############################################################################
        "door1.IS_JOIN_T270_3.shadow",
        "door1.IS_JOIN_BLOCK.shadow",
        "door1.IS_JOIN_T90_3.shadow",
        "door1.IS_JOIN_VERT.shadow",
        "door1.IS_JOIN_X4_90.shadow",
        "door1.IS_JOIN_X4.shadow",
        "door1.IS_JOIN_X2_180.shadow",
        "door1.IS_JOIN_X2_90.shadow",
        "door1.IS_JOIN_X1_90.shadow",
        "door1.IS_JOIN_X1_270.shadow",
        "door1.IS_JOIN_X3_180.shadow",
        "door1.IS_JOIN_X3.shadow",
        // ##############################################################################
        "door1.IS_JOIN_BL2.shadow",
        "door1.IS_JOIN_T180_3.shadow",
        "door1.IS_JOIN_BR2.shadow",
        "door1.IS_JOIN_BOT.shadow",
        "door1.IS_JOIN_T_1.shadow",
        "door1.IS_JOIN_T_2.shadow",
        "door1.IS_JOIN_T270_2.shadow",
        "door1.IS_JOIN_T90_1.shadow",
        "door1.IS_JOIN_T.shadow",
        "door1.IS_JOIN_T90.shadow",
        "door1.IS_JOIN_TL.shadow",
        "door1.IS_JOIN_TR.shadow",
        // ##############################################################################
        "door1.IS_JOIN_LEFT.shadow",
        "door1.IS_JOIN_HORIZ.shadow",
        "door1.IS_JOIN_RIGHT.shadow",
        "door1.IS_JOIN_NODE.shadow",
        "door1.IS_JOIN_T180_2.shadow",
        "door1.IS_JOIN_T180_1.shadow",
        "door1.IS_JOIN_T270_1.shadow",
        "door1.IS_JOIN_T90_2.shadow",
        "door1.IS_JOIN_T270.shadow",
        "door1.IS_JOIN_T180.shadow",
        "door1.IS_JOIN_BL.shadow",
        "door1.IS_JOIN_BR.shadow",
        // ##############################################################################
        /* clang-format on */
    };
    tile_load_arr("data/gfx/tiles_24x24.tga", "tiles_24x24", 24, 24, ARRAY_SIZE(tiles), tiles);
  }
}
