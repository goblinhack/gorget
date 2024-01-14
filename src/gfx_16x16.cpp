//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_tile.hpp"
#include "my_ui.hpp"

void gfx_init_16x16(void)
{
  std::initializer_list< std::string > tiles = {
      // clang-format off
      "ladder.0",      "block.0",       "rock_gold.0",   "spike.0",      "snake.0",      "snake.1",      "snake.2",    "snake.3",      "", "",
      "ladder.1",      "block.1",       "rock_gold.1",   "spike.1",      "",             "",             "",           "",             "", "",
      "ladder.2",      "block.2",       "rock_gold.2",   "spike.2",      "",             "",             "",           "",             "", "",
      "ladder.3",      "block.3",       "rock_gold.3",   "spike.3",      "",             "",             "",           "",             "", "",
      "ladder.4",      "block.4",       "rock_gold.4",   "spike.4",      "",             "",             "",           "",             "", "",
      "key0",          "",              "",              "",             "",             "",             "",           "",             "", "",
      "crystal0",      "crystal1",      "crystal2",      "crystal3",     "crystal4",     "crystal5",     "crystal6",   "",             "", "",
      "player.idle.0", "player.idle.1", "",              "",             "",             "",             "",           "",             "", "",
      "player.up.0",   "player.up.1",   "",              "",             "",             "",             "",           "",             "", "",
      "player.walk.0", "player.walk.1", "",              "",             "",             "",             "",           "",             "", "",
      "player.run.0",  "player.run.1",  "player.run.2",  "player.run.3", "player.run.4", "player.run.5", "",           "",             "", "",
      // clang-format on
  };
  const std::vector< std::string > arr(tiles);
  tile_load_arr_sprites("data/gfx/tiles_16x16.tga", "tiles_16x16", 16, 16, arr);
}
