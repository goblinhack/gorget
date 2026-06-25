//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game_defs.hpp"
#include "my_game_popups.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"

#include <algorithm>
#include <string>

[[nodiscard]] auto thing_noise_this_tick(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_noise_this_tick;
}

[[nodiscard]] auto thing_noise_this_tick_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }

  if (val > std::numeric_limits< decltype(t->_noise_this_tick) >::max()) {
    thing_err(t, "value overflow: %d", val);
    return 0;
  }

  return t->_noise_this_tick = val;
}

[[nodiscard]] auto thing_noise_this_tick_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (t->_noise_this_tick + val > THING_DISTANCE_NOICE_TILE_MAX) {
    t->_noise_this_tick = THING_DISTANCE_NOICE_TILE_MAX;
  }
  return t->_noise_this_tick += val;
}

[[nodiscard]] auto thing_noise_this_tick_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }

  if (static_cast< int >(t->_noise_this_tick) - val <= 0) {
    return t->_noise_this_tick = 0;
  }

  return t->_noise_this_tick -= val;
}
