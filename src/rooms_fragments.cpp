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

  if (fragment_add(g, __FUNCTION__, __LINE__,
                   /* line */ (const char *) "xxxxx",
                   /* line */ (const char *) "x....",
                   /* line */ (const char *) "x....",
                   /* line */ (const char *) "x....",
                   /* line */ (const char *) "x....", nullptr)) {
    fragment_alt_add(g, __FUNCTION__, __LINE__,
                     /* line */ (const char *) "xxxxx",
                     /* line */ (const char *) "x$.C.",
                     /* line */ (const char *) "x..C.",
                     /* line */ (const char *) "xCCC.",
                     /* line */ (const char *) "x....", nullptr);

    fragment_alt_add(g, __FUNCTION__, __LINE__,
                     /* line */ (const char *) "xxxxx",
                     /* line */ (const char *) "x$.C.",
                     /* line */ (const char *) "x.C..",
                     /* line */ (const char *) "xC...",
                     /* line */ (const char *) "x....", nullptr);
  }

  if (fragment_add(g, __FUNCTION__, __LINE__,
                   /* line */ (const char *) "     ",
                   /* line */ (const char *) " ....",
                   /* line */ (const char *) " ....",
                   /* line */ (const char *) " ....",
                   /* line */ (const char *) " ....", nullptr)) {
    fragment_alt_add(g, __FUNCTION__, __LINE__,
                     /* line */ (const char *) "...  ",
                     /* line */ (const char *) "...B.",
                     /* line */ (const char *) ".....",
                     /* line */ (const char *) " B...",
                     /* line */ (const char *) " ....", nullptr);
  }
}
