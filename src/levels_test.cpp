//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"

//
// Create all test levels
//
void levels_test(Gamep g)
{
  TRACE_NO_INDENT();

  level_add(g, CHANCE_NORMAL, LEVEL_TYPE_TEST, "test1", __FUNCTION__, __LINE__,
            /* line */ (const char *) "           ",
            /* line */ (const char *) " xxxxxxxxx ",
            /* line */ (const char *) " x.......x ",
            /* line */ (const char *) " x.......x ",
            /* line */ (const char *) " x..CCC..x ",
            /* line */ (const char *) " x.@====.x ",
            /* line */ (const char *) " x..CCC..x ",
            /* line */ (const char *) " x.......x ",
            /* line */ (const char *) " x.......x ",
            /* line */ (const char *) " xxxxxxxxx ",
            /* line */ (const char *) "           ",
            /* end */ nullptr);
}
