//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <array>
#include <string.h>

#include "my_array_bounds_check.hpp"
#include "my_bits.hpp"
#include "my_charmap.hpp"
#include "my_dice.hpp"
#include "my_game.hpp"
#include "my_level_ph4.hpp"
#include "my_main.hpp"
#include "my_point.hpp"
#include "my_random.hpp"
#include "my_template.hpp"
#include "my_thing_template.hpp"

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
        case CHARMAP_ENTRANCE : tp = tp_random_entrance(); break;
        case CHARMAP_EXIT : tp = tp_random_exit(); break;
        case CHARMAP_KEY : tp = tp_random_key(); break;
        case CHARMAP_TREASURE : tp = tp_random_crystal(); break;
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
        case CHARMAP_ROCK : tp = tp_random_rock(); break;
        case CHARMAP_SECRET_DOOR : break;
        case CHARMAP_UP : break;
        case CHARMAP_WALL_100_PERCENT :
          tp = tp_random_wall();

          //
          // If surrounded by rock
          //
          if (d100() < 10) {
            auto tp = tp_random_rock_gold();
            if (tp) {
              data.obj[ x ][ y ][ tp->z_depth ].id = tp->id;
            }
          }
          break;
        case CHARMAP_WALL_50_PERCENT : tp = tp_random_wall(); break;
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
