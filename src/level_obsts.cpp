//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_charmap.hpp"
#include "my_level_ph3.hpp"
#include "my_level_ph3_obst.hpp"
#include "my_ptrcheck.hpp"
#include "my_vector_bounds_check.hpp"

void level_ph3_obstacle_init(void)
{
  //
  // Ground
  //
  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_GROUND,
                         "11111"
                         "....."
                         ".....");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_GROUND,
                         "....."
                         "1111."
                         ".....");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_GROUND,
                         "....."
                         ".|.|."
                         "11111");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_GROUND,
                         "....."
                         "2.2.."
                         "1|1||");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_GROUND,
                         "....."
                         ".2.2."
                         "|1|1|");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_GROUND,
                         "....."
                         "222.."
                         "111|.");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_GROUND,
                         "....."
                         ".222."
                         ".111.");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_GROUND,
                         "111.."
                         "222.."
                         ".....");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_GROUND,
                         ".111."
                         ".222."
                         ".....");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_GROUND,
                         "....."
                         ".222."
                         "21112");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_GROUND,
                         "....."
                         "2.1.."
                         "||11|");

  //
  // Air
  //
  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_AIR,
                         "11111"
                         "....."
                         ".....");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_AIR,
                         "22222"
                         "....."
                         ".....");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_AIR,
                         "111.."
                         "222.."
                         ".....");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_AIR,
                         ".111."
                         ".222."
                         ".....");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_AIR,
                         "....."
                         ".111."
                         ".....");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_AIR,
                         "....."
                         ".111."
                         ".222.");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_AIR,
                         "....."
                         ".222."
                         ".111.");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_AIR,
                         "....."
                         "..22."
                         ".1111");

  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_AIR,
                         "....."
                         "222.."
                         "111..");
}
