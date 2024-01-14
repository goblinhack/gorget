//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <string.h>

#include "my_array_bounds_check.hpp"
#include "my_charmap.hpp"
#include "my_level_ph3_obst.hpp"
#include "my_ptrcheck.hpp"

LevelPh3Obstacless LevelPh3Obstacles::all_obsts_of_type[ OBSTACLE_TYPE_MAX ];
LevelPh3Obstacless LevelPh3Obstacles::all_obsts;

void level_ph3_init(void) { TRACE_NO_INDENT(); }

void level_ph3_fini(void)
{
  TRACE_NO_INDENT();
  for (auto &o : LevelPh3Obstacles::all_obsts) {
    delete o;
  }
}

LevelPh3Obstacles::LevelPh3Obstacles(void)
{
  TRACE_NO_INDENT();
  this->obstno = all_obsts.size();
  newptr(MTYPE_OBST, this, "obst");
}

LevelPh3Obstacles::~LevelPh3Obstacles(void)
{
  TRACE_NO_INDENT();
  oldptr(MTYPE_OBST, this);
}

LevelPh3Obstaclesp LevelPh3Obstacles::flip(void)
{
  TRACE_NO_INDENT();
  auto f = new LevelPh3Obstacles();

  f->type = type;

  for (auto x = 0; x < LEVEL_PH3_OBSTACLE_WIDTH; x++) {
    for (auto y = 0; y < LEVEL_PH3_OBSTACLE_HEIGHT; y++) {
      auto c = get(data, x, y);
      set(f->data, LEVEL_PH3_OBSTACLE_WIDTH - x - 1, y, c);
    }
  }

  return f;
}

void LevelPh3Obstacles::dump(void)
{
  TRACE_NO_INDENT();

  LOG("LevelPh3Obstaclesno: %u", obstno);

  std::array< std::array< char, LEVEL_PH3_OBSTACLE_WIDTH >, LEVEL_PH3_OBSTACLE_HEIGHT > out {};

  for (auto ry = 0; ry < LEVEL_PH3_OBSTACLE_HEIGHT; ry++) {
    for (auto rx = 0; rx < LEVEL_PH3_OBSTACLE_WIDTH; rx++) {
      auto c = get(data, rx, ry);
      set(out, rx, ry, c);
    }
  }

  for (auto y = 0; y < LEVEL_PH3_OBSTACLE_HEIGHT; y++) {
    std::string s;
    for (auto x = 0; x < LEVEL_PH3_OBSTACLE_WIDTH; x++) {
      auto c = get(out, x, y);
      if (c) {
        s += c;
      } else {
        s += ' ';
      }
    }
    LOG("%s", s.c_str());
  }

  LOG("-");
}

LevelPh3Obstaclesp obstacle_new(void)
{
  TRACE_NO_INDENT();
  auto o = new LevelPh3Obstacles();
  LevelPh3Obstacles::all_obsts.push_back(o);
  return o;
}

void level_ph3_obstacle_add(ObstacleType type, const char *data)
{
  TRACE_NO_INDENT();

  const auto row_len      = LEVEL_PH3_OBSTACLE_WIDTH;
  auto       expected_len = row_len * LEVEL_PH3_OBSTACLE_HEIGHT;

  if ((int) strlen(data) != expected_len) {
    DIE("bad obstacle size, expected %d, got %d", (int) strlen(data), (int) expected_len);
  }

  //
  // Break the grid of obsts up into individual obsts
  //
  auto o  = obstacle_new();
  o->type = type;

  for (auto ry = 0; ry < LEVEL_PH3_OBSTACLE_HEIGHT; ry++) {
    for (auto rx = 0; rx < LEVEL_PH3_OBSTACLE_WIDTH; rx++) {
      auto offset = (row_len * ry) + rx;
      auto c      = data[ offset ];

      switch (c) {
        case PH2_CHAR_ROCK : break;
        case PH2_CHAR_WILDCARD : DIE("obstacle should not have a wildcard"); break;
        case PH2_CHAR_WALL_100_PERCENT : break;
        case PH2_CHAR_WALL_50_PERCENT : break;
        case PH2_CHAR_SPIKE_33_PERCENT : break;
        case PH2_CHAR_OBSTACLE_GROUND : break;
        case PH2_CHAR_OBSTACLE_AIR : break;
        case PH2_CHAR_LADDER : break;
        case PH2_CHAR_ROCK_GOLD : break;
        case PH2_CHAR_BLOCK : break;
        case PH2_CHAR_CRYSTAL : break;
        case PH2_CHAR_TREASURE : break;
        case PH2_CHAR_MONST1 : break;
        case PH2_CHAR_ENTRANCE : DIE("obstacle should not have an entrance"); break;
        case PH2_CHAR_EXIT : DIE("obstacle should not have an exit"); break;
        case PH2_CHAR_LOCK : break;
        case PH2_CHAR_KEY : break;
        case PH2_CHAR_SECRET_DOOR : DIE("obstacle should not have a secret door"); break;
        case PH2_CHAR_EMPTY : break;
        default : DIE("unexpected obstacle char '%c'", c);
      }

      o->data[ rx ][ ry ] = c;
    }
  }

  LevelPh3Obstacles::all_obsts_of_type[ o->type ].push_back(o);
  // o->dump();

  auto f = o->flip();
  LevelPh3Obstacles::all_obsts_of_type[ f->type ].push_back(f);
  // f->dump();
}
