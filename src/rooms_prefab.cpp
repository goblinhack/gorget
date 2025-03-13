//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_level.hpp"

//
// Create all rooms
//
void rooms_prefab(Gamep g)
{
  TRACE_NO_INDENT();

  /* clang-format off */

  room_add(g, __FUNCTION__, __LINE__, 
           (const char *)"    ^       ",
           (const char *)" xxx.xxxxxx ",
           (const char *)" x........x ",
           (const char *)" x........x ",
           (const char *)"^.........x ",
           (const char *)" x........x ",
           (const char *)" x........x ",
           (const char *)" x........x ",
           (const char *)" x.........^",
           (const char *)" xxxxx.xxxx ",
           (const char *)"      ^     ",
           nullptr);

  /* clang-format on */
}
