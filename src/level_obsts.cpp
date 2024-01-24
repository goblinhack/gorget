//
// Copyright Neil McGill, goblinhack@gmail.com
//

// REMOVED #include "my_array_bounds_check.hpp"
// REMOVED #include "my_charmap.hpp"
#include "my_level_ph3.hpp"
// REMOVED #include "my_level_ph3_obst.hpp"
// REMOVED #include "my_ptrcheck.hpp"
// REMOVED #include "my_vector_bounds_check.hpp"

void level_ph3_obstacle_init(void)
{
  return;
  TRACE_NO_INDENT();
  level_ph3_obstacle_add(OBSTACLE_TYPE_NORMAL,
                         "....."
                         "....."
                         "....."
                         "....."
                         ".....");
}
