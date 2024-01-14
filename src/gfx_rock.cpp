//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tile.hpp"
#include "my_ui.hpp"

void gfx_init_rocks(void)
{
  std::initializer_list< std::string > tiles = {
      // clang-format off
      "rock.tl.0.0",   "rock.top.0.0", "rock.tr.0.0",     "rock.tl.1.0",   "rock.top.1.0", "rock.tr.1.0",     "rock.tl.2.0",   "rock.top.2.0", "rock.tr.2.0",     "rock.tl.3.0",   "rock.top.3.0", "rock.tr.3.0",    "rock.tl.4.0",   "rock.top.4.0", "rock.tr.4.0",     "rock.tl.5.0",   "rock.top.5.0", "rock.tr.5.0",
      "rock.left.0.0", "rock.0.0",     "rock.right.0.0",  "rock.left.1.0", "rock.1.0",     "rock.right.1.0",  "rock.left.2.0", "rock.2.0",     "rock.right.2.0",  "rock.left.3.0", "rock.3.0",     "rock.right.3.0", "rock.left.4.0", "rock.4.0",     "rock.right.4.0",  "rock.left.5.0", "rock.5.0",     "rock.right.5.0",
      "rock.bl.0.0",   "rock.bot.0.0", "rock.br.0.0",     "rock.bl.1.0",   "rock.bot.1.0", "rock.br.1.0",     "rock.bl.2.0",   "rock.bot.2.0", "rock.br.2.0",     "rock.bl.3.0",   "rock.bot.3.0", "rock.br.3.0",    "rock.bl.4.0",   "rock.bot.4.0", "rock.br.4.0",     "rock.bl.5.0",   "rock.bot.5.0", "rock.br.5.0",

      "rock.tl.0.1",   "rock.top.0.1", "rock.tr.0.1",     "rock.tl.1.1",   "rock.top.1.1", "rock.tr.1.1",     "rock.tl.2.1",   "rock.top.2.1", "rock.tr.2.1",     "rock.tl.3.1",   "rock.top.3.1", "rock.tr.3.1",    "rock.tl.4.1",   "rock.top.4.1", "rock.tr.4.1",     "rock.tl.5.1",   "rock.top.5.1", "rock.tr.5.1",
      "rock.left.0.1", "rock.0.1",     "rock.right.0.1",  "rock.left.1.1", "rock.1.1",     "rock.right.1.1",  "rock.left.2.1", "rock.2.1",     "rock.right.2.1",  "rock.left.3.1", "rock.3.1",     "rock.right.3.1", "rock.left.4.1", "rock.4.1",     "rock.right.4.1",  "rock.left.5.1", "rock.5.1",     "rock.right.5.1",
      "rock.bl.0.1",   "rock.bot.0.1", "rock.br.0.1",     "rock.bl.1.1",   "rock.bot.1.1", "rock.br.1.1",     "rock.bl.2.1",   "rock.bot.2.1", "rock.br.2.1",     "rock.bl.3.1",   "rock.bot.3.1", "rock.br.3.1",    "rock.bl.4.1",   "rock.bot.4.1", "rock.br.4.1",     "rock.bl.5.1",   "rock.bot.5.1", "rock.br.5.1",

      "rock.tl.0.2",   "rock.top.0.2", "rock.tr.0.2",     "rock.tl.1.2",   "rock.top.1.2", "rock.tr.1.2",     "rock.tl.2.2",   "rock.top.2.2", "rock.tr.2.2",     "rock.tl.3.2",   "rock.top.3.2", "rock.tr.3.2",    "rock.tl.4.2",   "rock.top.4.2", "rock.tr.4.2",     "rock.tl.5.2",   "rock.top.5.2", "rock.tr.5.2",
      "rock.left.0.2", "rock.0.2",     "rock.right.0.2",  "rock.left.1.2", "rock.1.2",     "rock.right.1.2",  "rock.left.2.2", "rock.2.2",     "rock.right.2.2",  "rock.left.3.2", "rock.3.2",     "rock.right.3.2", "rock.left.4.2", "rock.4.2",     "rock.right.4.2",  "rock.left.5.2", "rock.5.2",     "rock.right.5.2",
      "rock.bl.0.2",   "rock.bot.0.2", "rock.br.0.2",     "rock.bl.1.2",   "rock.bot.1.2", "rock.br.1.2",     "rock.bl.2.2",   "rock.bot.2.2", "rock.br.2.2",     "rock.bl.3.2",   "rock.bot.3.2", "rock.br.3.2",    "rock.bl.4.2",   "rock.bot.4.2", "rock.br.4.2",     "rock.bl.5.2",   "rock.bot.5.2", "rock.br.5.2",

      "rock.tl.0.3",   "rock.top.0.3", "rock.tr.0.3",     "rock.tl.1.3",   "rock.top.1.3", "rock.tr.1.3",     "rock.tl.2.3",   "rock.top.2.3", "rock.tr.2.3",     "rock.tl.3.3",   "rock.top.3.3", "rock.tr.3.3",    "rock.tl.4.3",   "rock.top.4.3", "rock.tr.4.3",     "rock.tl.5.3",   "rock.top.5.3", "rock.tr.5.3",
      "rock.left.0.3", "rock.0.3",     "rock.right.0.3",  "rock.left.1.3", "rock.1.3",     "rock.right.1.3",  "rock.left.2.3", "rock.2.3",     "rock.right.2.3",  "rock.left.3.3", "rock.3.3",     "rock.right.3.3", "rock.left.4.3", "rock.4.3",     "rock.right.4.3",  "rock.left.5.3", "rock.5.3",     "rock.right.5.3",
      "rock.bl.0.3",   "rock.bot.0.3", "rock.br.0.3",     "rock.bl.1.3",   "rock.bot.1.3", "rock.br.1.3",     "rock.bl.2.3",   "rock.bot.2.3", "rock.br.2.3",     "rock.bl.3.3",   "rock.bot.3.3", "rock.br.3.3",    "rock.bl.4.3",   "rock.bot.4.3", "rock.br.4.3",     "rock.bl.5.3",   "rock.bot.5.3", "rock.br.5.3",

      "rock.tl.0.4",   "rock.top.0.4", "rock.tr.0.4",     "rock.tl.1.4",   "rock.top.1.4", "rock.tr.1.4",     "rock.tl.2.4",   "rock.top.2.4", "rock.tr.2.4",     "rock.tl.3.4",   "rock.top.3.4", "rock.tr.3.4",    "rock.tl.4.4",   "rock.top.4.4", "rock.tr.4.4",     "rock.tl.5.4",   "rock.top.5.4", "rock.tr.5.4",
      "rock.left.0.4", "rock.0.4",     "rock.right.0.4",  "rock.left.1.4", "rock.1.4",     "rock.right.1.4",  "rock.left.2.4", "rock.2.4",     "rock.right.2.4",  "rock.left.3.4", "rock.3.4",     "rock.right.3.4", "rock.left.4.4", "rock.4.4",     "rock.right.4.4",  "rock.left.5.4", "rock.5.4",     "rock.right.5.4",
      "rock.bl.0.4",   "rock.bot.0.4", "rock.br.0.4",     "rock.bl.1.4",   "rock.bot.1.4", "rock.br.1.4",     "rock.bl.2.4",   "rock.bot.2.4", "rock.br.2.4",     "rock.bl.3.4",   "rock.bot.3.4", "rock.br.3.4",    "rock.bl.4.4",   "rock.bot.4.4", "rock.br.4.4",     "rock.bl.5.4",   "rock.bot.5.4", "rock.br.5.4",

      "rock.tl.0.5",   "rock.top.0.5", "rock.tr.0.5",     "rock.tl.1.5",   "rock.top.1.5", "rock.tr.1.5",     "rock.tl.2.5",   "rock.top.2.5", "rock.tr.2.5",     "rock.tl.3.5",   "rock.top.3.5", "rock.tr.3.5",    "rock.tl.4.5",   "rock.top.4.5", "rock.tr.4.5",     "rock.tl.5.5",   "rock.top.5.5", "rock.tr.5.5",
      "rock.left.0.5", "rock.0.5",     "rock.right.0.5",  "rock.left.1.5", "rock.1.5",     "rock.right.1.5",  "rock.left.2.5", "rock.2.5",     "rock.right.2.5",  "rock.left.3.5", "rock.3.5",     "rock.right.3.5", "rock.left.4.5", "rock.4.5",     "rock.right.4.5",  "rock.left.5.5", "rock.5.5",     "rock.right.5.5",
      "rock.bl.0.5",   "rock.bot.0.5", "rock.br.0.5",     "rock.bl.1.5",   "rock.bot.1.5", "rock.br.1.5",     "rock.bl.2.5",   "rock.bot.2.5", "rock.br.2.5",     "rock.bl.3.5",   "rock.bot.3.5", "rock.br.3.5",    "rock.bl.4.5",   "rock.bot.4.5", "rock.br.4.5",     "rock.bl.5.5",   "rock.bot.5.5", "rock.br.5.5",

      // clang-format on
  };
  const std::vector< std::string > arr(tiles);
  tile_load_arr_sprites("data/gfx/rocks.tga", "rocks", 16, 16, arr);
}
