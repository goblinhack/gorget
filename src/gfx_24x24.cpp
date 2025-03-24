//
// Copyright goblinhack@gmail.com
//

#include "my_tile.hpp"
#include "my_ui.hpp"

void gfx_init_24x24(void)
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
        "floor.1",
        "floor.2",
        "floor.3",
        "floor.4",
        "floor.5",
        "floor.6",
        "floor.7",
        "floor.8",
        "floor.9",
        "floor.10",
        "floor.11",
        "floor.12",
        // ##############################################################################
        "player.idle.0",
        "cursor_path",
        "cursor_at",
        "exit.0",
        "door.0",
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
  tile_load_arr("data/gfx/tiles_24x24.tga", "tiles_24x24", TILE_WIDTH, TILE_HEIGHT, ARRAY_SIZE(tiles), tiles);
}
