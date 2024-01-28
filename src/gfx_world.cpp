//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tile.hpp"
#include "my_ui.hpp"

void gfx_init_world(void)
{
  std::initializer_list< std::string > tiles = {
      // clang-format off
      // ###############################################################################
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      // ###############################################################################
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      // ###############################################################################
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      // ###############################################################################
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      // ###############################################################################
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      // ###############################################################################
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      "", "", "",
      // ###############################################################################
      "world_grassland.tl.0",   "world_grassland.top.0", "world_grassland.tr.0",
      "world_grassland.tl.1",   "world_grassland.top.1", "world_grassland.tr.1",
      "world_grassland.tl.2",   "world_grassland.top.2", "world_grassland.tr.2",
      "world_grassland.tl.3",   "world_grassland.top.3", "world_grassland.tr.3",
      "world_grassland.tl.4",   "world_grassland.top.4", "world_grassland.tr.4",
      "world_grassland.tl.5",   "world_grassland.top.5", "world_grassland.tr.5",
      // ###############################################################################
      "world_grassland.left.0", "world_grassland.0",     "world_grassland.right.0",
      "world_grassland.left.1", "world_grassland.1",     "world_grassland.right.1",
      "world_grassland.left.2", "world_grassland.2",     "world_grassland.right.2",
      "world_grassland.left.3", "world_grassland.3",     "world_grassland.right.3",
      "world_grassland.left.4", "world_grassland.4",     "world_grassland.right.4",
      "world_grassland.left.5", "world_grassland.5",     "world_grassland.right.5",
      // ###############################################################################
      "world_grassland.bl.0",   "world_grassland.bot.0", "world_grassland.br.0",
      "world_grassland.bl.1",   "world_grassland.bot.1", "world_grassland.br.1",
      "world_grassland.bl.2",   "world_grassland.bot.2", "world_grassland.br.2",
      "world_grassland.bl.3",   "world_grassland.bot.3", "world_grassland.br.3",
      "world_grassland.bl.4",   "world_grassland.bot.4", "world_grassland.br.4",
      "world_grassland.bl.5",   "world_grassland.bot.5", "world_grassland.br.5",
      // ###############################################################################
      "world_marsh.tl.0",   "world_marsh.top.0", "world_marsh.tr.0",
      "world_marsh.tl.1",   "world_marsh.top.1", "world_marsh.tr.1",
      "world_marsh.tl.2",   "world_marsh.top.2", "world_marsh.tr.2",
      "world_marsh.tl.3",   "world_marsh.top.3", "world_marsh.tr.3",
      "world_marsh.tl.4",   "world_marsh.top.4", "world_marsh.tr.4",
      "world_marsh.tl.5",   "world_marsh.top.5", "world_marsh.tr.5",
      // ###############################################################################
      "world_marsh.left.0", "world_marsh.0",     "world_marsh.right.0",
      "world_marsh.left.1", "world_marsh.1",     "world_marsh.right.1",
      "world_marsh.left.2", "world_marsh.2",     "world_marsh.right.2",
      "world_marsh.left.3", "world_marsh.3",     "world_marsh.right.3",
      "world_marsh.left.4", "world_marsh.4",     "world_marsh.right.4",
      "world_marsh.left.5", "world_marsh.5",     "world_marsh.right.5",
      // ###############################################################################
      "world_marsh.bl.0",   "world_marsh.bot.0", "world_marsh.br.0",
      "world_marsh.bl.1",   "world_marsh.bot.1", "world_marsh.br.1",
      "world_marsh.bl.2",   "world_marsh.bot.2", "world_marsh.br.2",
      "world_marsh.bl.3",   "world_marsh.bot.3", "world_marsh.br.3",
      "world_marsh.bl.4",   "world_marsh.bot.4", "world_marsh.br.4",
      "world_marsh.bl.5",   "world_marsh.bot.5", "world_marsh.br.5",
      // ###############################################################################
      "world_desert.tl.0",   "world_desert.top.0", "world_desert.tr.0",
      "world_desert.tl.1",   "world_desert.top.1", "world_desert.tr.1",
      "world_desert.tl.2",   "world_desert.top.2", "world_desert.tr.2",
      "world_desert.tl.3",   "world_desert.top.3", "world_desert.tr.3",
      "world_desert.tl.4",   "world_desert.top.4", "world_desert.tr.4",
      "world_desert.tl.5",   "world_desert.top.5", "world_desert.tr.5",
      // ###############################################################################
      "world_desert.left.0", "world_desert.0",     "world_desert.right.0",
      "world_desert.left.1", "world_desert.1",     "world_desert.right.1",
      "world_desert.left.2", "world_desert.2",     "world_desert.right.2",
      "world_desert.left.3", "world_desert.3",     "world_desert.right.3",
      "world_desert.left.4", "world_desert.4",     "world_desert.right.4",
      "world_desert.left.5", "world_desert.5",     "world_desert.right.5",
      // ###############################################################################
      "world_desert.bl.0",   "world_desert.bot.0", "world_desert.br.0",
      "world_desert.bl.1",   "world_desert.bot.1", "world_desert.br.1",
      "world_desert.bl.2",   "world_desert.bot.2", "world_desert.br.2",
      "world_desert.bl.3",   "world_desert.bot.3", "world_desert.br.3",
      "world_desert.bl.4",   "world_desert.bot.4", "world_desert.br.4",
      "world_desert.bl.5",   "world_desert.bot.5", "world_desert.br.5",
      // ###############################################################################
      "world_sea.tl.0",   "world_sea.top.0", "world_sea.tr.0",
      "world_sea.tl.1",   "world_sea.top.1", "world_sea.tr.1",
      "world_sea.tl.2",   "world_sea.top.2", "world_sea.tr.2",
      "world_sea.tl.3",   "world_sea.top.3", "world_sea.tr.3",
      "world_sea.tl.4",   "world_sea.top.4", "world_sea.tr.4",
      "world_sea.tl.5",   "world_sea.top.5", "world_sea.tr.5",
      // ###############################################################################
      "world_sea.left.0", "world_sea.0",     "world_sea.right.0",
      "world_sea.left.1", "world_sea.1",     "world_sea.right.1",
      "world_sea.left.2", "world_sea.2",     "world_sea.right.2",
      "world_sea.left.3", "world_sea.3",     "world_sea.right.3",
      "world_sea.left.4", "world_sea.4",     "world_sea.right.4",
      "world_sea.left.5", "world_sea.5",     "world_sea.right.5",
      // ###############################################################################
      "world_sea.bl.0",   "world_sea.bot.0", "world_sea.br.0",
      "world_sea.bl.1",   "world_sea.bot.1", "world_sea.br.1",
      "world_sea.bl.2",   "world_sea.bot.2", "world_sea.br.2",
      "world_sea.bl.3",   "world_sea.bot.3", "world_sea.br.3",
      "world_sea.bl.4",   "world_sea.bot.4", "world_sea.br.4",
      "world_sea.bl.5",   "world_sea.bot.5", "world_sea.br.5",
      // ###############################################################################
      "world_deep_sea.tl.0",   "world_deep_sea.top.0", "world_deep_sea.tr.0",
      "world_deep_sea.tl.1",   "world_deep_sea.top.1", "world_deep_sea.tr.1",
      "world_deep_sea.tl.2",   "world_deep_sea.top.2", "world_deep_sea.tr.2",
      "world_deep_sea.tl.3",   "world_deep_sea.top.3", "world_deep_sea.tr.3",
      "world_deep_sea.tl.4",   "world_deep_sea.top.4", "world_deep_sea.tr.4",
      "world_deep_sea.tl.5",   "world_deep_sea.top.5", "world_deep_sea.tr.5",
      // ###############################################################################
      "world_deep_sea.left.0", "world_deep_sea.0",     "world_deep_sea.right.0",
      "world_deep_sea.left.1", "world_deep_sea.1",     "world_deep_sea.right.1",
      "world_deep_sea.left.2", "world_deep_sea.2",     "world_deep_sea.right.2",
      "world_deep_sea.left.3", "world_deep_sea.3",     "world_deep_sea.right.3",
      "world_deep_sea.left.4", "world_deep_sea.4",     "world_deep_sea.right.4",
      "world_deep_sea.left.5", "world_deep_sea.5",     "world_deep_sea.right.5",
      // ###############################################################################
      "world_deep_sea.bl.0",   "world_deep_sea.bot.0", "world_deep_sea.br.0",
      "world_deep_sea.bl.1",   "world_deep_sea.bot.1", "world_deep_sea.br.1",
      "world_deep_sea.bl.2",   "world_deep_sea.bot.2", "world_deep_sea.br.2",
      "world_deep_sea.bl.3",   "world_deep_sea.bot.3", "world_deep_sea.br.3",
      "world_deep_sea.bl.4",   "world_deep_sea.bot.4", "world_deep_sea.br.4",
      "world_deep_sea.bl.5",   "world_deep_sea.bot.5", "world_deep_sea.br.5",
      // clang-format on
  };
  const std::vector< std::string > arr(tiles);
  tile_load_arr_sprites("data/gfx/world.tga", "world", 16, 16, arr);
}
