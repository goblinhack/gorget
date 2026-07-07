//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

[[nodiscard]] auto thing_stat_set(Gamep g, Levelsp v, Levelp l, Thingp me, ThingStatType stat, uint8_t val) -> uint8_t
{
  TRACE_DEBUG();

  if (me == nullptr) {
    ERR("no thing pointer");
    return THING_STAT_DEFAULT;
  }

  if (stat >= THING_STAT_ENUM_MAX) {
    thing_err(g, v, l, me, "bad value in stat for %s, %d", __FUNCTION__, stat);
    return THING_STAT_DEFAULT;
  }

  return me->_stat[ stat ] = val;
}

[[nodiscard]] auto thing_stat(Gamep g, Levelsp v, Levelp l, Thingp me, ThingStatType stat) -> int
{
  TRACE_DEBUG();

  if (me == nullptr) {
    ERR("no thing pointer");
    return THING_STAT_DEFAULT;
  }

  if (stat >= THING_STAT_ENUM_MAX) {
    thing_err(g, v, l, me, "bad value in stat for %s, %d", __FUNCTION__, stat);
    return THING_STAT_DEFAULT;
  }

  auto out = me->_stat[ stat ];

  FOR_ALL_BUFFS(g, v, l, me, buff)
  {
    int modifier = thing_stat(g, v, l, buff, stat) - THING_STAT_DEFAULT;

    if (modifier < 0) {
      out = std::max(0, out - modifier);
    } else {
      out += modifier;
    }
  }

  return out;
}
