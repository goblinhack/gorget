//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_thing_inlines.hpp"
#include "my_time.hpp"

void level_anim(Gamep g, Levelsp v, Levelp l)
{
  TRACE();

  l->ts = time_ms();
  if (! static_cast< bool >(l->last_ts)) {
    l->last_ts = l->ts;
    return;
  }

  auto time_step = l->ts - l->last_ts;
  l->last_ts     = l->ts;

  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t)
  {
    Tpp tp = thing_tp(t);

    if (compiler_unused) {
      if (thing_is_level_curr(t)) {
        THING_LOG(t, "anim");
      }
    }

    thing_hot_time_step(g, v, l, t, time_step);

    if (tp_is_animated(tp)) {
      thing_anim_time_step(g, v, l, t, tp, time_step);
    }

    if (thing_is_hit(t) != 0) {
      thing_hit_time_step(g, v, l, t, time_step);
    }

    if (thing_is_falling(t) != 0) {
      thing_fall_time_step(g, v, l, t, time_step);
    }
  }
}
