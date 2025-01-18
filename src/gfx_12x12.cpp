//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_gl.hpp"
#include "my_tile.hpp"
#include "my_ui.hpp"

void gfx_init_12x12(void)
{
  const char *tiles[] = {
      /* clang-format off */
        // ##############################################################################
        "floor.1",
        "floor.2",
        "floor.3",
        "floor.4",
        "floor.5",
        "floor.6",
        "",
        "",
        "",
        "",
        "",
        "",
        // ##############################################################################
        "player1.idle.0",
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
        // ##############################################################################
        "exit.0",
        "cursor_path",
        "cursor_at",
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
      /* clang-format on */
  };
  tile_load_arr_sprites("data/gfx/tiles_12x12.tga", "tiles_12x12", 12, 12, ARRAY_SIZE(tiles), tiles, GL_LINEAR);
}
