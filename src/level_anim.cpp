//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
// REMOVED #include "my_game.hpp"
#include "my_level.hpp"
// REMOVED #include "my_main.hpp"
// REMOVED #include "my_tile.hpp"
#include "my_time.hpp"
// REMOVED #include "my_tp.hpp"

void level_anim(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  auto            ts = time_ms();
  static uint32_t last_ts;

  if (! last_ts) {
    last_ts = ts;
    return;
  }

  auto time_step = ts - last_ts;
  last_ts        = ts;

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        Tpp    tp;
        spoint p(x, y);
        Thingp t = thing_and_tp_get_at(g, v, l, p, slot, &tp);
        if (! t) {
          continue;
        }

        thing_anim_time_step(g, v, l, t, time_step);

        if (thing_is_falling(t)) {
          thing_fall_time_step(g, v, l, t, time_step);
        }
      }
    }
  }
}
