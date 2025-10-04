//
// Copyright goblinhack@gmail.com
//

#include <format>

#include "my_charmap.hpp"
#include "my_level.hpp"
#include "my_test.hpp"
#include "my_ui.hpp"
#include "my_wids.hpp"

void level_debug_stats(Gamep g)
{
  TRACE_NO_INDENT();

  auto v = game_levels_get(g);
  if (! v) {
    return;
  }

  LOG("Level stats:");
  LOG("- Total memory:         %" PRI_SIZE_T " Mb", sizeof(Levels) / (1024 * 1024));
  LOG("- Per level memory:     %" PRI_SIZE_T " Kb", sizeof(Level) / (1024));
  LOG("- Levels:               %" PRI_SIZE_T " Mb", sizeof(v->level) / (1024 * 1024));
  LOG("- Max things:           %u", 1 << THING_INDEX_BITS);

  thing_stats_dump(g, v);
}

void level_debug(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  LOG("Level         : %d", l->level_num);
  LOG("Seed          : %u", l->info.seed_num);

  if (l->info.room_count) {
    LOG("Room count        : %d", l->info.room_count);
    LOG("Fragment count    : %d", l->info.fragment_count);
    LOG("Treasure count    : %d", l->info.treasure_count);
    LOG("Monst count       : %d (mob:%d easy:%d hard:%d)", l->info.monst_count, l->info.monst_group_mob_count,
        l->info.monst_group_easy_count, l->info.monst_group_hard_count);
    LOG("Teleport count    : %d", l->info.teleport_count);
    LOG("Locked door count : %d", l->info.door_locked_count);
    LOG("Key count         : %d", l->info.key_count);
  }

  for (int y = 0; y < MAP_HEIGHT; y++) {
    std::string tmp;
    for (int x = 0; x < MAP_WIDTH; x++) {
      auto c = l->debug[ x ][ y ];
      if (c) {
        tmp += l->debug[ x ][ y ];
      }
    }

    if (! tmp.empty()) {
      LOG("[%s]", tmp.c_str());
    }
  }

  LOG("-");
}
