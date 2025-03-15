//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_level.hpp"

//
// Create all exit rooms
//
void rooms_exit(Gamep g)
{
  TRACE_NO_INDENT();

  /* clang-format off */

  room_add(g, true, __FUNCTION__, __LINE__, 
           (const char *)"    ^       ",
           (const char *)" xxx.xxxxxx ",
           (const char *)" x........x ",
           (const char *)" x........x ",
           (const char *)" x........x ",
           (const char *)" x........x ",
           (const char *)" x........x ",
           (const char *)" x......E.x ",
           (const char *)" x........x ",
           (const char *)" xxxxxxxxxx ",
           (const char *)"            ",
           nullptr);

  /* clang-format on */
}
