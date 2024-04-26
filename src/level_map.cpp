//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tp.hpp"

void Level::map_set(LevelDatap data, const char *in)
{
  TRACE_NO_INDENT();
  const auto row_len      = MAP_WIDTH;
  auto       expected_len = row_len * MAP_HEIGHT;

  if ((int) strlen(in) != expected_len) {
    DIE("bad map size, expected %d, got %d", (int) strlen(in), (int) expected_len);
  }

  auto tp_wall    = tp_random_wall();
  auto tp_door    = tp_find("door");
  auto tp_floor   = tp_find("floor");
  auto tp_exit    = tp_find("exit");
  auto tp_player1 = tp_find("player1");
  auto tp_player2 = tp_find("player2");
  auto tp_player3 = tp_find("player3");
  auto tp_player4 = tp_find("player4");

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      auto offset = (row_len * y) + x;
      auto c      = in[ offset ];
      Tpp  tp     = nullptr;

      bool need_floor = false;

      switch (c) {
        case CHARMAP_WALL :
          need_floor = true;
          tp         = tp_wall;
          break;
        case CHARMAP_DOOR :
          need_floor = true;
          tp         = tp_door;
          break;
        case CHARMAP_TREASURE : break;
        case CHARMAP_MONST1 : break;
        case CHARMAP_PLAYER1 :
          need_floor = true;
          tp         = tp_player1;
          break;
        case CHARMAP_PLAYER2 :
          need_floor = true;
          tp         = tp_player2;
          break;
        case CHARMAP_PLAYER3 :
          need_floor = true;
          tp         = tp_player3;
          break;
        case CHARMAP_PLAYER4 :
          need_floor = true;
          tp         = tp_player4;
          break;
        case CHARMAP_EXIT :
          need_floor = true;
          tp         = tp_exit;
          break;
        case CHARMAP_KEY : need_floor = true; break;
        case CHARMAP_EMPTY : need_floor = true; break;
        default : DIE("unexpected map char '%c'", c);
      }

      if (need_floor) {
        auto tp = tp_floor;
        ::tp_set(data, x, y, tp);
      }

      if (! tp) {
        continue;
      }

      ::tp_set(data, x, y, tp);
    }
  }
}
