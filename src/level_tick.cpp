//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_level.hpp"
#include "my_level_data.hpp"
#include "my_main.hpp"
#include "my_thing_template.hpp"

void Level::tick(void)
{
  TRACE_NO_INDENT();

  static uint16_t tick;
  tick++;

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    for (auto y = miny; y < maxy; y++) {
      for (auto x = minx; x < maxx; x++) {
        Tpp  tp;
        auto t = thing_get(x, y, slot, &tp);
        if (! t) {
          continue;
        }

        if (t->tick == tick) {
          continue;
        }

        t->tick = tick;
        thing_update_pos(t);
        thing_update_speed(t);
      }
    }
  }
}
