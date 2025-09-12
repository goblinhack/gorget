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

  level_add(g, CHANCE_NORMAL, LEVEL_TYPE_TEST, "bridge1", __FUNCTION__, __LINE__,
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

  level_add(g, CHANCE_NORMAL, LEVEL_TYPE_TEST, "bridge2", __FUNCTION__, __LINE__,
            /* line */ (const char *) "           ",
            /* line */ (const char *) " xxxxxxxxx ",
            /* line */ (const char *) " x.......x ",
            /* line */ (const char *) " x.......x ",
            /* line */ (const char *) " x..LLL..x ",
            /* line */ (const char *) " x.@====.x ",
            /* line */ (const char *) " x..LLL..x ",
            /* line */ (const char *) " x.......x ",
            /* line */ (const char *) " x.......x ",
            /* line */ (const char *) " xxxxxxxxx ",
            /* line */ (const char *) "           ",
            /* end */ nullptr);

  level_add(g, CHANCE_NORMAL, LEVEL_TYPE_TEST, "shove", __FUNCTION__, __LINE__,
            /* line */ (const char *) "           ",
            /* line */ (const char *) " xxxxxxxxx ",
            /* line */ (const char *) " x.......x ",
            /* line */ (const char *) " x.......x ",
            /* line */ (const char *) " x...bC..x ",
            /* line */ (const char *) " x.@.GC..x ",
            /* line */ (const char *) " x...BC..x ",
            /* line */ (const char *) " x.......x ",
            /* line */ (const char *) " x.......x ",
            /* line */ (const char *) " xxxxxxxxx ",
            /* line */ (const char *) "           ",
            /* end */ nullptr);

  level_add(g, CHANCE_NORMAL, LEVEL_TYPE_TEST, "barrel", __FUNCTION__, __LINE__,
            /* line */ (const char *) "           ",
            /* line */ (const char *) " xxxxxxxxx ",
            /* line */ (const char *) " x.......x ",
            /* line */ (const char *) " xbbbbbb.x ",
            /* line */ (const char *) " xb....b.x ",
            /* line */ (const char *) " xb.@..b.x ",
            /* line */ (const char *) " xb....b.x ",
            /* line */ (const char *) " xbbbbbb.x ",
            /* line */ (const char *) " x.......x ",
            /* line */ (const char *) " xxxxxxxxx ",
            /* line */ (const char *) "           ",
            /* end */ nullptr);

  level_add(g, CHANCE_NORMAL, LEVEL_TYPE_TEST, "door_secret", __FUNCTION__, __LINE__,
            /* line */ (const char *) "           ",
            /* line */ (const char *) " xxxxx     ",
            /* line */ (const char *) " x...x     ",
            /* line */ (const char *) " x...xxxxx ",
            /* line */ (const char *) " x...x...x ",
            /* line */ (const char *) " x..@s...x ",
            /* line */ (const char *) " x...x...x ",
            /* line */ (const char *) " x...xxxxx ",
            /* line */ (const char *) " x...x     ",
            /* line */ (const char *) " xxxxx     ",
            /* line */ (const char *) "           ",
            /* end */ nullptr);

  level_add(g, CHANCE_NORMAL, LEVEL_TYPE_TEST, "door_unlocked", __FUNCTION__, __LINE__,
            /* line */ (const char *) "           ",
            /* line */ (const char *) " xxxxx     ",
            /* line */ (const char *) " x...x     ",
            /* line */ (const char *) " x...xxxxx ",
            /* line */ (const char *) " x...x...x ",
            /* line */ (const char *) " x@..D...x ",
            /* line */ (const char *) " x...x...x ",
            /* line */ (const char *) " x...xxxxx ",
            /* line */ (const char *) " x...x     ",
            /* line */ (const char *) " xxxxx     ",
            /* line */ (const char *) "           ",
            /* end */ nullptr);

  level_add(g, CHANCE_NORMAL, LEVEL_TYPE_TEST, "door_locked", __FUNCTION__, __LINE__,
            /* line */ (const char *) "           ",
            /* line */ (const char *) " xxxxx     ",
            /* line */ (const char *) " x...x     ",
            /* line */ (const char *) " x...xxxxx ",
            /* line */ (const char *) " x...x...x ",
            /* line */ (const char *) " x@.k+...x ",
            /* line */ (const char *) " x...x...x ",
            /* line */ (const char *) " x...xxxxx ",
            /* line */ (const char *) " x...x     ",
            /* line */ (const char *) " xxxxx     ",
            /* line */ (const char *) "           ",
            /* end */ nullptr);

  level_add(g, CHANCE_NORMAL, LEVEL_TYPE_TEST, "item", __FUNCTION__, __LINE__,
            /* line */ (const char *) "           ",
            /* line */ (const char *) " xxxxxxxxx ",
            /* line */ (const char *) " x...$$$$x ",
            /* line */ (const char *) " x...$$$$x ",
            /* line */ (const char *) " x...$$$$x ",
            /* line */ (const char *) " x..@$$$$x ",
            /* line */ (const char *) " x...$$$$x ",
            /* line */ (const char *) " x...$$$$x ",
            /* line */ (const char *) " x...$$$$x ",
            /* line */ (const char *) " xxxxxxxxx ",
            /* line */ (const char *) "           ",
            /* end */ nullptr);
}
