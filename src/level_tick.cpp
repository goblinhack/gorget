//
// Copyright Neil McGill, goblinhack@gmail.com
//

// REMOVED #include "my_game.hpp"
#include "my_level.hpp"
// REMOVED #include "my_level_data.hpp"
// REMOVED #include "my_main.hpp"
// REMOVED #include "my_tp.hpp"

void Level::tick(void)
{
  TRACE_NO_INDENT();

  static uint16_t tick;
  tick++;

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        Tpp   tp;
        point p(x, y);
        auto  t = thing_get(p, slot, &tp);
        if (! t) {
          continue;
        }

        if (t->tick == tick) {
          continue;
        }

        t->tick = tick;
        thing_update_pos(t);
      }
    }
  }
}
