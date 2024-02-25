//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_charmap.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"

void Level::map_set(LevelDatap data, const char *in)
{
  TRACE_NO_INDENT();
  const auto row_len      = MAP_WIDTH;
  auto       expected_len = row_len * MAP_HEIGHT;

  if ((int) strlen(in) != expected_len) {
    DIE("bad map size, expected %d, got %d", (int) strlen(in), (int) expected_len);
  }

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      auto offset = (row_len * y) + x;
      auto c      = in[ offset ];
      Tpp  tp     = nullptr;

      switch (c) {
        case CHARMAP_WILDCARD : break;
        case CHARMAP_DUNGEON_WALL :
          tp = tp_find("dungeon_floor");
          ::tp_set(data, point(x, y), tp);
          tp = tp_find("dungeon_wall");
          break;
        case CHARMAP_DUNGEON_DOOR :
          tp = tp_find("dungeon_floor");
          ::tp_set(data, point(x, y), tp);
          tp = tp_find("dungeon_door");
          break;
          break;
        case CHARMAP_TREASURE : break;
        case CHARMAP_MONST1 : break;
        case CHARMAP_DUNGEON_ENTRANCE : break;
        case CHARMAP_DUNGEON_EXIT : break;
        case CHARMAP_LOCK : break;
        case CHARMAP_KEY : break;
        case CHARMAP_SECRET_DOOR : break;
        case CHARMAP_EMPTY : tp = tp_find("dungeon_floor"); break;
        default : DIE("unexpected map char '%c'", c);
      }

      if (! tp) {
        continue;
      }

      ::tp_set(data, point(x, y), tp);
    }
  }
}
