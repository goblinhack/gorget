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
        /* clang-format on */
        // ##############################################################################
        "door.IS_JOIN_TL2.shadow",
        "door.IS_JOIN_T_3.shadow",
        "door.IS_JOIN_TR2.shadow",
        "door.IS_JOIN_TOP.shadow",
        "door.IS_JOIN_X4_180.shadow",
        "door.IS_JOIN_X4_270.shadow",
        "door.IS_JOIN_X2_270.shadow",
        "door.IS_JOIN_X2.shadow",
        "door.IS_JOIN_X1_180.shadow",
        "door.IS_JOIN_X1.shadow",
        "door.IS_JOIN_X.shadow",
        "",
        // ##############################################################################
        "door.IS_JOIN_T270_3.shadow",
        "door.IS_JOIN_BLOCK.shadow",
        "door.IS_JOIN_T90_3.shadow",
        "door.IS_JOIN_VERT.shadow",
        "door.IS_JOIN_X4_90.shadow",
        "door.IS_JOIN_X4.shadow",
        "door.IS_JOIN_X2_180.shadow",
        "door.IS_JOIN_X2_90.shadow",
        "door.IS_JOIN_X1_90.shadow",
        "door.IS_JOIN_X1_270.shadow",
        "door.IS_JOIN_X3_180.shadow",
        "door.IS_JOIN_X3.shadow",
        // ##############################################################################
        "door.IS_JOIN_BL2.shadow",
        "door.IS_JOIN_T180_3.shadow",
        "door.IS_JOIN_BR2.shadow",
        "door.IS_JOIN_BOT.shadow",
        "door.IS_JOIN_T_1.shadow",
        "door.IS_JOIN_T_2.shadow",
        "door.IS_JOIN_T270_2.shadow",
        "door.IS_JOIN_T90_1.shadow",
        "door.IS_JOIN_T.shadow",
        "door.IS_JOIN_T90.shadow",
        "door.IS_JOIN_TL.shadow",
        "door.IS_JOIN_TR.shadow",
        // ##############################################################################
        "door.IS_JOIN_LEFT.shadow",
        "door.IS_JOIN_HORIZ.shadow",
        "door.IS_JOIN_RIGHT.shadow",
        "door.IS_JOIN_NODE.shadow",
        "door.IS_JOIN_T180_2.shadow",
        "door.IS_JOIN_T180_1.shadow",
        "door.IS_JOIN_T270_1.shadow",
        "door.IS_JOIN_T90_2.shadow",
        "door.IS_JOIN_T270.shadow",
        "door.IS_JOIN_T180.shadow",
        "door.IS_JOIN_BL.shadow",
        "door.IS_JOIN_BR.shadow",
    };
    tile_load_arr("data/gfx/tiles_24x24.tga", "tiles_24x24", 24, 24, ARRAY_SIZE(tiles), tiles);
  }
}
