//
// Copyright Neil McGill, goblinhack@gmail.com
//

// REMOVED #include <array>
// REMOVED #include <string.h>

#include "my_array_bounds_check.hpp"
// REMOVED #include "my_bits.hpp"
#include "my_charmap.hpp"
// REMOVED #include "my_dice.hpp"
#include "my_game.hpp"
#include "my_level_ph4.hpp"
// REMOVED #include "my_main.hpp"
// REMOVED #include "my_point.hpp"
// REMOVED #include "my_random.hpp"
// REMOVED #include "my_template.hpp"
#include "my_tp.hpp"

void LevelPH4::add_object_ids(const LevelPh3 &ph3)
{
  TRACE_NO_INDENT();

  const auto w = LEVEL_PH4_WIDTH;
  const auto h = LEVEL_PH4_HEIGHT;

  memset(data.obj, 0, sizeof(data.obj));

  for (auto y = 0; y < h; y++) {
    for (auto x = 0; x < w; x++) {
      auto c  = get(ph3.data, x, y);
      Tpp  tp = nullptr;
      switch (c) {
        case CHARMAP_DOWN : break;
        case CHARMAP_EMPTY : break;
        case CHARMAP_DUNGEON_ENTRANCE : tp = tp_random_dungeon_entrance(); break;
        case CHARMAP_DUNGEON_EXIT : tp = tp_random_dungeon_exit(); break;
        case CHARMAP_KEY : tp = tp_random_key(); break;
        case CHARMAP_TREASURE : break;
        case CHARMAP_MONST1 :
          {
            auto tp = tp_random_monst1();
            auto t  = thing_new(&data, tp, point(x, y));
            thing_push(&data, t);
          }
          break;
        case CHARMAP_LEFT : break;
        case CHARMAP_LOCK : break;
        case CHARMAP_OBSTACLE_WILDCARD : break;
        case CHARMAP_RIGHT : break;
        case CHARMAP_ROCK : break;
        case CHARMAP_SECRET_DOOR : break;
        case CHARMAP_UP : break;
        case CHARMAP_WALL_100_PERCENT :
#if 0
          tp = tp_random_dungeon_wall();

          //
          // If surrounded by rock
          //
          if (d100() < 10) {
            auto tp = tp_random_dungeon_rock_gold();
            if (tp) {
              data.obj[ x ][ y ][ tp->z_depth ].id = tp->id;
            }
          }
#endif
          break;
        case CHARMAP_WALL_50_PERCENT :
#if 0
          tp = tp_random_dungeon_wall();
#endif
          break;
        case CHARMAP_WILDCARD : break;
      }

      if (tp) {
        data.obj[ x ][ y ][ tp->z_depth ].id = tp->id;
      }
    }
  }
}

LevelPH4::LevelPH4(const LevelPh3 &ph3)
{
  TRACE_NO_INDENT();

  add_object_ids(ph3);

  ok = true;
}

LevelPH4 level_ph4(const LevelPh3 &ph3)
{
  TRACE_NO_INDENT();

  LevelPH4 pH4(ph3);

  return pH4;
}
