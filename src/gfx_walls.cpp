//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tile.hpp"
#include "my_ui.hpp"

void gfx_init_walls(void)
{
  std::initializer_list< std::string > tiles = {
      // clang-format off
      "wall.tl.0.0",   "wall.top.0.0", "wall.tr.0.0",     "wall.tl.1.0",   "wall.top.1.0", "wall.tr.1.0",     "wall.tl.2.0",   "wall.top.2.0", "wall.tr.2.0",     "wall.tl.3.0",   "wall.top.3.0", "wall.tr.3.0",    "wall.tl.4.0",   "wall.top.4.0", "wall.tr.4.0",     "wall.tl.5.0",   "wall.top.5.0", "wall.tr.5.0",
      "wall.left.0.0", "wall.0.0",     "wall.right.0.0",  "wall.left.1.0", "wall.1.0",     "wall.right.1.0",  "wall.left.2.0", "wall.2.0",     "wall.right.2.0",  "wall.left.3.0", "wall.3.0",     "wall.right.3.0", "wall.left.4.0", "wall.4.0",     "wall.right.4.0",  "wall.left.5.0", "wall.5.0",     "wall.right.5.0",
      "wall.bl.0.0",   "wall.bot.0.0", "wall.br.0.0",     "wall.bl.1.0",   "wall.bot.1.0", "wall.br.1.0",     "wall.bl.2.0",   "wall.bot.2.0", "wall.br.2.0",     "wall.bl.3.0",   "wall.bot.3.0", "wall.br.3.0",    "wall.bl.4.0",   "wall.bot.4.0", "wall.br.4.0",     "wall.bl.5.0",   "wall.bot.5.0", "wall.br.5.0",

      "wall.tl.0.1",   "wall.top.0.1", "wall.tr.0.1",     "wall.tl.1.1",   "wall.top.1.1", "wall.tr.1.1",     "wall.tl.2.1",   "wall.top.2.1", "wall.tr.2.1",     "wall.tl.3.1",   "wall.top.3.1", "wall.tr.3.1",    "wall.tl.4.1",   "wall.top.4.1", "wall.tr.4.1",     "wall.tl.5.1",   "wall.top.5.1", "wall.tr.5.1",
      "wall.left.0.1", "wall.0.1",     "wall.right.0.1",  "wall.left.1.1", "wall.1.1",     "wall.right.1.1",  "wall.left.2.1", "wall.2.1",     "wall.right.2.1",  "wall.left.3.1", "wall.3.1",     "wall.right.3.1", "wall.left.4.1", "wall.4.1",     "wall.right.4.1",  "wall.left.5.1", "wall.5.1",     "wall.right.5.1",
      "wall.bl.0.1",   "wall.bot.0.1", "wall.br.0.1",     "wall.bl.1.1",   "wall.bot.1.1", "wall.br.1.1",     "wall.bl.2.1",   "wall.bot.2.1", "wall.br.2.1",     "wall.bl.3.1",   "wall.bot.3.1", "wall.br.3.1",    "wall.bl.4.1",   "wall.bot.4.1", "wall.br.4.1",     "wall.bl.5.1",   "wall.bot.5.1", "wall.br.5.1",

      "wall.tl.0.2",   "wall.top.0.2", "wall.tr.0.2",     "wall.tl.1.2",   "wall.top.1.2", "wall.tr.1.2",     "wall.tl.2.2",   "wall.top.2.2", "wall.tr.2.2",     "wall.tl.3.2",   "wall.top.3.2", "wall.tr.3.2",    "wall.tl.4.2",   "wall.top.4.2", "wall.tr.4.2",     "wall.tl.5.2",   "wall.top.5.2", "wall.tr.5.2",
      "wall.left.0.2", "wall.0.2",     "wall.right.0.2",  "wall.left.1.2", "wall.1.2",     "wall.right.1.2",  "wall.left.2.2", "wall.2.2",     "wall.right.2.2",  "wall.left.3.2", "wall.3.2",     "wall.right.3.2", "wall.left.4.2", "wall.4.2",     "wall.right.4.2",  "wall.left.5.2", "wall.5.2",     "wall.right.5.2",
      "wall.bl.0.2",   "wall.bot.0.2", "wall.br.0.2",     "wall.bl.1.2",   "wall.bot.1.2", "wall.br.1.2",     "wall.bl.2.2",   "wall.bot.2.2", "wall.br.2.2",     "wall.bl.3.2",   "wall.bot.3.2", "wall.br.3.2",    "wall.bl.4.2",   "wall.bot.4.2", "wall.br.4.2",     "wall.bl.5.2",   "wall.bot.5.2", "wall.br.5.2",

      "wall.tl.0.3",   "wall.top.0.3", "wall.tr.0.3",     "wall.tl.1.3",   "wall.top.1.3", "wall.tr.1.3",     "wall.tl.2.3",   "wall.top.2.3", "wall.tr.2.3",     "wall.tl.3.3",   "wall.top.3.3", "wall.tr.3.3",    "wall.tl.4.3",   "wall.top.4.3", "wall.tr.4.3",     "wall.tl.5.3",   "wall.top.5.3", "wall.tr.5.3",
      "wall.left.0.3", "wall.0.3",     "wall.right.0.3",  "wall.left.1.3", "wall.1.3",     "wall.right.1.3",  "wall.left.2.3", "wall.2.3",     "wall.right.2.3",  "wall.left.3.3", "wall.3.3",     "wall.right.3.3", "wall.left.4.3", "wall.4.3",     "wall.right.4.3",  "wall.left.5.3", "wall.5.3",     "wall.right.5.3",
      "wall.bl.0.3",   "wall.bot.0.3", "wall.br.0.3",     "wall.bl.1.3",   "wall.bot.1.3", "wall.br.1.3",     "wall.bl.2.3",   "wall.bot.2.3", "wall.br.2.3",     "wall.bl.3.3",   "wall.bot.3.3", "wall.br.3.3",    "wall.bl.4.3",   "wall.bot.4.3", "wall.br.4.3",     "wall.bl.5.3",   "wall.bot.5.3", "wall.br.5.3",

      "wall.tl.0.4",   "wall.top.0.4", "wall.tr.0.4",     "wall.tl.1.4",   "wall.top.1.4", "wall.tr.1.4",     "wall.tl.2.4",   "wall.top.2.4", "wall.tr.2.4",     "wall.tl.3.4",   "wall.top.3.4", "wall.tr.3.4",    "wall.tl.4.4",   "wall.top.4.4", "wall.tr.4.4",     "wall.tl.5.4",   "wall.top.5.4", "wall.tr.5.4",
      "wall.left.0.4", "wall.0.4",     "wall.right.0.4",  "wall.left.1.4", "wall.1.4",     "wall.right.1.4",  "wall.left.2.4", "wall.2.4",     "wall.right.2.4",  "wall.left.3.4", "wall.3.4",     "wall.right.3.4", "wall.left.4.4", "wall.4.4",     "wall.right.4.4",  "wall.left.5.4", "wall.5.4",     "wall.right.5.4",
      "wall.bl.0.4",   "wall.bot.0.4", "wall.br.0.4",     "wall.bl.1.4",   "wall.bot.1.4", "wall.br.1.4",     "wall.bl.2.4",   "wall.bot.2.4", "wall.br.2.4",     "wall.bl.3.4",   "wall.bot.3.4", "wall.br.3.4",    "wall.bl.4.4",   "wall.bot.4.4", "wall.br.4.4",     "wall.bl.5.4",   "wall.bot.5.4", "wall.br.5.4",

      "wall.tl.0.5",   "wall.top.0.5", "wall.tr.0.5",     "wall.tl.1.5",   "wall.top.1.5", "wall.tr.1.5",     "wall.tl.2.5",   "wall.top.2.5", "wall.tr.2.5",     "wall.tl.3.5",   "wall.top.3.5", "wall.tr.3.5",    "wall.tl.4.5",   "wall.top.4.5", "wall.tr.4.5",     "wall.tl.5.5",   "wall.top.5.5", "wall.tr.5.5",
      "wall.left.0.5", "wall.0.5",     "wall.right.0.5",  "wall.left.1.5", "wall.1.5",     "wall.right.1.5",  "wall.left.2.5", "wall.2.5",     "wall.right.2.5",  "wall.left.3.5", "wall.3.5",     "wall.right.3.5", "wall.left.4.5", "wall.4.5",     "wall.right.4.5",  "wall.left.5.5", "wall.5.5",     "wall.right.5.5",
      "wall.bl.0.5",   "wall.bot.0.5", "wall.br.0.5",     "wall.bl.1.5",   "wall.bot.1.5", "wall.br.1.5",     "wall.bl.2.5",   "wall.bot.2.5", "wall.br.2.5",     "wall.bl.3.5",   "wall.bot.3.5", "wall.br.3.5",    "wall.bl.4.5",   "wall.bot.4.5", "wall.br.4.5",     "wall.bl.5.5",   "wall.bot.5.5", "wall.br.5.5",
      // clang-format on
  };
  const std::vector< std::string > arr(tiles);
  tile_load_arr_sprites("data/gfx/walls.tga", "walls", 16, 16, arr);
}
