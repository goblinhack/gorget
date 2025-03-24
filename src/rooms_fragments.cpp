//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_level.hpp"

//
// Create all fragments
//
void fragments_init(Gamep g)
{
  TRACE_NO_INDENT();

  /* clang-format off */

  {
      if (fragment_add(g, __FUNCTION__, __LINE__, 
                       (const char *)"xxxxx",
                       (const char *)"x....",
                       (const char *)"x....",
                       (const char *)"x....",
                       (const char *)"x....",
                       nullptr)) {
          fragment_alt_add(g, __FUNCTION__, __LINE__, 
                           (const char *)"xxxx.",
                           (const char *)"x$.C.",
                           (const char *)"x..C.",
                           (const char *)"xCCC.",
                           (const char *)".....",
                           nullptr);
      }
  }

  /* clang-format on */
}
