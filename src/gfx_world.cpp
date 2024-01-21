//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tile.hpp"
#include "my_ui.hpp"

void gfx_init_world(void)
{
  std::initializer_list< std::string > tiles = {
      // clang-format off
      "world_mountains.tl.0",   "world_mountains.top.0", "world_mountains.tr.0",
      "world_mountains.tl.1",   "world_mountains.top.1", "world_mountains.tr.1",
      "world_mountains.tl.2",   "world_mountains.top.2", "world_mountains.tr.2",
      "world_mountains.tl.3",   "world_mountains.top.3", "world_mountains.tr.3",
      "world_mountains.tl.4",   "world_mountains.top.4", "world_mountains.tr.4",
      "world_mountains.tl.5",   "world_mountains.top.5", "world_mountains.tr.5",
      // ###############################################################################
      "world_mountains.left.0", "world_mountains.0",     "world_mountains.right.0",
      "world_mountains.left.1", "world_mountains.1",     "world_mountains.right.1",
      "world_mountains.left.2", "world_mountains.2",     "world_mountains.right.2",
      "world_mountains.left.3", "world_mountains.3",     "world_mountains.right.3",
      "world_mountains.left.4", "world_mountains.4",     "world_mountains.right.4",
      "world_mountains.left.5", "world_mountains.5",     "world_mountains.right.5",
      // ###############################################################################
      "world_mountains.bl.0",   "world_mountains.bot.0", "world_mountains.br.0",
      "world_mountains.bl.1",   "world_mountains.bot.1", "world_mountains.br.1",
      "world_mountains.bl.2",   "world_mountains.bot.2", "world_mountains.br.2",
      "world_mountains.bl.3",   "world_mountains.bot.3", "world_mountains.br.3",
      "world_mountains.bl.4",   "world_mountains.bot.4", "world_mountains.br.4",
      "world_mountains.bl.5",   "world_mountains.bot.5", "world_mountains.br.5",
      // clang-format on
  };
  const std::vector< std::string > arr(tiles);
  tile_load_arr_sprites("data/gfx/world.tga", "world", 16, 16, arr);
}
