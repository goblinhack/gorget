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
        case PH2_CHAR_CONNECTOR : break;
        case PH2_CHAR_DOWN : break;
        case PH2_CHAR_EMPTY : break;
        case PH2_CHAR_ENTRANCE : tp = tp_random_entrance(); break;
        case PH2_CHAR_EXIT : tp = tp_random_exit(); break;
        case PH2_CHAR_KEY : tp = tp_random_key(); break;
        case PH2_CHAR_LADDER : tp = tp_random_ladder(); break;
        case PH2_CHAR_ROCK_GOLD : tp = tp_random_rock_gold(); break;
        case PH2_CHAR_BLOCK : tp = tp_random_block(); break;
        case PH2_CHAR_CRYSTAL : tp = tp_random_crystal(); break;
        case PH2_CHAR_TREASURE : tp = tp_random_crystal(); break;
        case PH2_CHAR_MONST1 :
          {
            auto tp = tp_random_monst1();
            auto t  = thing_new(&data, tp, x, y);
            thing_push(&data, t);
          }
          break;
        case PH2_CHAR_LEFT : break;
        case PH2_CHAR_LOCK : break;
        case PH2_CHAR_OBSTACLE_AIR : break;
        case PH2_CHAR_OBSTACLE_GROUND : break;
        case PH2_CHAR_RIGHT : break;
        case PH2_CHAR_ROCK : tp = tp_random_rock(); break;
        case PH2_CHAR_SECRET_DOOR : break;
        case PH2_CHAR_SPIKE_33_PERCENT : tp = tp_random_spike(); break;
        case PH2_CHAR_UP : break;
        case PH2_CHAR_WALL_100_PERCENT :
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
        case PH2_CHAR_WALL_50_PERCENT : tp = tp_random_wall(); break;
        case PH2_CHAR_WILDCARD : break;
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
