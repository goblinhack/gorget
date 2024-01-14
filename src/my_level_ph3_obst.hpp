//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_LEVEL_PH3_OBSTACLE_HPP_
#define _MY_LEVEL_PH3_OBSTACLE_HPP_

#include <array>
#include <string>

#include "my_fwd.hpp"
#include "my_game_defs.hpp"

using LevelPh3Obstacless = std::vector< LevelPh3Obstaclesp >;

typedef enum {
  OBSTACLE_TYPE_AIR,
  OBSTACLE_TYPE_GROUND,
  OBSTACLE_TYPE_MAX,
} ObstacleType;

class LevelPh3Obstacles
{
private:
public:
  static LevelPh3Obstacless all_obsts_of_type[ OBSTACLE_TYPE_MAX ];
  static LevelPh3Obstacless all_obsts;

  LevelPh3Obstacles(void);
  ~LevelPh3Obstacles(void);

  //
  // Unique per obst.
  //
  uint32_t     obstno {0};
  ObstacleType type;
  uint8_t      width {LEVEL_PH3_OBSTACLE_WIDTH};
  uint8_t      height {LEVEL_PH3_OBSTACLE_HEIGHT};

  std::array< std::array< char, LEVEL_PH3_OBSTACLE_HEIGHT >, LEVEL_PH3_OBSTACLE_WIDTH > data {};

  LevelPh3Obstaclesp flip(void);
  void               dump(void);
};

void level_ph3_init(void);
void level_ph3_fini(void);

LevelPh3Obstaclesp obstacle_new(void);

void level_ph3_obstacle_init(void);
void level_ph3_obstacle_add(ObstacleType, const char *);

#endif
