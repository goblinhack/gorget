//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <array>
#include <string.h>

#include "my_array_bounds_check.hpp"
#include "my_charmap.hpp"
#include "my_dice.hpp"
#include "my_level_ph1.hpp"
#include "my_level_ph2.hpp"
#include "my_level_ph3.hpp"
#include "my_main.hpp"
#include "my_point.hpp"
#include "my_random.hpp"
#include "my_template.hpp"

void LevelPh3::dump(void)
{
  TRACE_NO_INDENT();

  const auto w = LEVEL_PH3_WIDTH;
  const auto h = LEVEL_PH3_HEIGHT;

  for (auto y = 0; y < h; y++) {
    std::string s;
    for (auto x = 0; x < w; x++) {
      auto c = get(data, x, y);
      if (c) {
        s += c;
      } else {
        s += ' ';
      }
    }
    LOG("Phase3: [%s]", s.c_str());
  }
  LOG("Phase3: -");
}

bool LevelPh3::expand(const LevelPh2 &ph2)
{
  TRACE_NO_INDENT();

  const auto w = LEVEL_PH3_WIDTH;
  const auto h = LEVEL_PH3_HEIGHT;

  for (auto y = 0; y < h; y++) {
    for (auto x = 0; x < w; x++) {
      set(data, x, y, (char) PH2_CHAR_ROCK);
    }
  }

  for (auto room_across = 0; room_across < LEVEL_PH1_WIDTH; room_across++) {
    for (auto room_down = 0; room_down < LEVEL_PH1_HEIGHT; room_down++) {
      LevelPh2Roomp r = get(ph2.rooms, room_across, room_down);
      if (r) {
        for (auto ry = 0; ry < LEVEL_PH2_ROOM_HEIGHT; ry++) {
          for (auto rx = 0; rx < LEVEL_PH2_ROOM_WIDTH; rx++) {
            auto c = get(r->data, rx, ry);
            auto x = (room_across * LEVEL_PH2_ROOM_WIDTH) + rx;
            auto y = (room_down * LEVEL_PH2_ROOM_HEIGHT) + ry;
            set(data, x + LEVEL_PH3_MAP_BORDER, y + LEVEL_PH3_MAP_BORDER, c);
          }
        }
      }
    }
  }

  return true;
}

static bool is_oob(int x, int y)
{
  if (x < 0) {
    return true;
  }
  if (y < 0) {
    return true;
  }
  if (x >= LEVEL_PH3_WIDTH) {
    return true;
  }
  if (y >= LEVEL_PH3_HEIGHT) {
    return true;
  }
  return false;
}

void LevelPh3::add_obstacle_at(const LevelPh2 &ph2, point at, LevelPh3Obstaclesp o)
{
  TRACE_NO_INDENT();

  for (auto y = 0; y < LEVEL_PH3_OBSTACLE_HEIGHT; y++) {
    for (auto x = 0; x < LEVEL_PH3_OBSTACLE_WIDTH; x++) {
      auto c  = get(o->data, x, y);
      auto rx = at.x + x;
      auto ry = at.y + y;

      //
      // For each obst char, check there is a wildcard char on the level
      //
      if (! is_oob(rx, ry)) {
        switch (get(data, rx, ry)) {
          default : break;
          case PH2_CHAR_WILDCARD :
          case PH2_CHAR_OBSTACLE_AIR :
          case PH2_CHAR_OBSTACLE_GROUND : set(data, rx, ry, c); break;
        }
      }

      //
      // Cater for flipped rooms
      //
      rx = at.x - x;
      if (! is_oob(rx, ry)) {
        switch (get(data, rx, ry)) {
          default : break;
          case PH2_CHAR_WILDCARD :
          case PH2_CHAR_OBSTACLE_AIR :
          case PH2_CHAR_OBSTACLE_GROUND : set(data, rx, ry, c); break;
        }
      }
    }
  }
}

void LevelPh3::add_obstacles(const LevelPh2 &ph2)
{
  TRACE_NO_INDENT();

  const auto w = LEVEL_PH3_WIDTH;
  const auto h = LEVEL_PH3_HEIGHT;

  for (auto y = 0; y < h; y++) {
    for (auto x = 0; x < w; x++) {
      point at(x, y);
      switch (get(data, x, y)) {
        case PH2_CHAR_OBSTACLE_AIR :
          add_obstacle_at(ph2, at, one_of(LevelPh3Obstacles::all_obsts_of_type[ OBSTACLE_TYPE_AIR ]));
          break;
        case PH2_CHAR_OBSTACLE_GROUND :
          add_obstacle_at(ph2, at, one_of(LevelPh3Obstacles::all_obsts_of_type[ OBSTACLE_TYPE_GROUND ]));
          break;
      }
    }
  }
}

void LevelPh3::fix_obstacles(const LevelPh2 &ph2)
{
  TRACE_NO_INDENT();

  const auto w = LEVEL_PH3_WIDTH;
  const auto h = LEVEL_PH3_HEIGHT;

  for (auto y = 0; y < h; y++) {
    for (auto x = 0; x < w; x++) {
      point at(x, y);
      switch (get(data, x, y)) {
        case PH2_CHAR_SPIKE_33_PERCENT : break;
        case PH2_CHAR_WALL_100_PERCENT : break;
        case PH2_CHAR_WALL_50_PERCENT :
          if (d100() > 50) {
            set(data, x, y, (char) PH2_CHAR_EMPTY);
          } else {
            set(data, x, y, (char) PH2_CHAR_WALL_100_PERCENT);

            //
            // Possible push block
            //
            if (y < h - 1) {
              if (get(data, x, y + 1) == PH2_CHAR_WALL_100_PERCENT) {
                //
                // Push block sitting on stone
                //
                if (d100() > 50) {
                  set(data, x, y, (char) PH2_CHAR_BLOCK);
                }
              } else if ((x > 0) && (x < w - 1)) {
                //
                // Drop block?
                //
                if ((get(data, x + 1, y) == PH2_CHAR_WALL_100_PERCENT)
                    && (get(data, x - 1, y) == PH2_CHAR_WALL_100_PERCENT)) {
                  if (d100() > 50) {
                    set(data, x, y, (char) PH2_CHAR_BLOCK);
                  }
                }
              }
            }
          }
      }
    }
  }
}

void LevelPh3::fix_floating_objs(const LevelPh2 &ph2)
{
  TRACE_NO_INDENT();

  const auto w = LEVEL_PH3_WIDTH;
  const auto h = LEVEL_PH3_HEIGHT;

  for (auto y = 0; y < h - 1; y++) {
    for (auto x = 0; x < w; x++) {
      point at(x, y);
      switch (get(data, x, y)) {
        case PH2_CHAR_SPIKE_33_PERCENT :
        case PH2_CHAR_MONST1 :
        case PH2_CHAR_CRYSTAL :
        case PH2_CHAR_TREASURE :
          switch (get(data, x, y + 1)) {
            case PH2_CHAR_EMPTY : set(data, x, y + 1, (char) PH2_CHAR_WALL_100_PERCENT); break;
            case PH2_CHAR_WALL_100_PERCENT : break;
            case PH2_CHAR_WALL_50_PERCENT : break;
            case PH2_CHAR_ROCK : break;
            default : set(data, x, y, (char) PH2_CHAR_EMPTY); break;
          }
      }
    }
  }

  for (auto y = 0; y < h - 1; y++) {
    for (auto x = 1; x < w - 1; x++) {
      point at(x, y);
      switch (get(data, x, y)) {
        case PH2_CHAR_BLOCK :
          //
          // Push blocks are ok if there is some rock either side.
          //
          bool ok = false;

          switch (get(data, x - 1, y)) {
            case PH2_CHAR_WALL_100_PERCENT :
            case PH2_CHAR_WALL_50_PERCENT :
            case PH2_CHAR_ROCK :
            case PH2_CHAR_BLOCK : ok = true; break;
          }
          switch (get(data, x + 1, y)) {
            case PH2_CHAR_WALL_100_PERCENT :
            case PH2_CHAR_WALL_50_PERCENT :
            case PH2_CHAR_ROCK :
            case PH2_CHAR_BLOCK : ok = true; break;
          }

          if (ok) {
            continue;
          }

          switch (get(data, x, y + 1)) {
            case PH2_CHAR_EMPTY : set(data, x, y + 1, (char) PH2_CHAR_WALL_100_PERCENT); break;
            case PH2_CHAR_WALL_100_PERCENT : break;
            case PH2_CHAR_WALL_50_PERCENT : break;
            case PH2_CHAR_ROCK : break;
            default : set(data, x, y, (char) PH2_CHAR_EMPTY); break;
          }
      }
    }
  }
}

LevelPh3::LevelPh3(const LevelPh2 &ph2)
{
  TRACE_NO_INDENT();

  LOG("Phase3: Initial layout:");
  expand(ph2);
  dump();

  LOG("Phase3: Replace obstacle blocks:");
  add_obstacles(ph2);
  dump();

  LOG("Phase3: Replace random chance tiles:");
  fix_obstacles(ph2);
  dump();

  LOG("Phase3: Ensure spikes have something under them:");
  fix_floating_objs(ph2);
  dump();

  ok = true;
}

LevelPh3 level_ph3(const LevelPh2 &ph2)
{
  TRACE_NO_INDENT();

  LevelPh3 ph3(ph2);

  return ph3;
}
