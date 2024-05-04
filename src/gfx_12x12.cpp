//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tile.hpp"
#include "my_ui.hpp"

void gfx_init_12x12(void)
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
        /* clang-format on */
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
        "floor.1",
        "floor.2",
        "floor.3",
        "floor.4",
        "floor.5",
        "floor.6",
    };
    tile_load_arr("data/gfx/tiles_12x12.tga", "tiles_12x12", 12, 12, ARRAY_SIZE(tiles), tiles);
  }
}
