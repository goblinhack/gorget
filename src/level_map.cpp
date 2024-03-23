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

  auto tp_wall  = tp_random_wall();
  auto tp_door  = tp_find("door");
  auto tp_floor = tp_find("floor");
  auto tp_exit  = tp_find("exit");

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      auto offset = (row_len * y) + x;
      auto c      = in[ offset ];
      Tpp  tp     = nullptr;

      switch (c) {
        case CHARMAP_WALL :
          tp = tp_floor;
          ::tp_set(data, point(x, y), tp);
          tp = tp_wall;
          break;
        case CHARMAP_DOOR :
          tp = tp_floor;
          ::tp_set(data, point(x, y), tp);
          tp = tp_door;
          break;
        case CHARMAP_TREASURE : break;
        case CHARMAP_MONST1 : break;
        case CHARMAP_PLAYER1 :
          tp = tp_floor;
          ::tp_set(data, point(x, y), tp);
          break;
        case CHARMAP_PLAYER2 :
          tp = tp_floor;
          ::tp_set(data, point(x, y), tp);
          break;
        case CHARMAP_PLAYER3 :
          tp = tp_floor;
          ::tp_set(data, point(x, y), tp);
          break;
        case CHARMAP_PLAYER4 :
          tp = tp_floor;
          ::tp_set(data, point(x, y), tp);
          break;
        case CHARMAP_EXIT :
          tp = tp_floor;
          ::tp_set(data, point(x, y), tp);
          tp = tp_exit;
          break;
        case CHARMAP_KEY : break;
        case CHARMAP_EMPTY : tp = tp_find("floor"); break;
        default : DIE("unexpected map char '%c'", c);
      }

      if (! tp) {
        continue;
      }

      ::tp_set(data, point(x, y), tp);
    }
  }
}
