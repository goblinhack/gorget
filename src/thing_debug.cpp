//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"

auto thing_debug(Gamep g, Levelsp v, Levelp l, Thingp t, uint32_t iter_index) -> bool
{
  TRACE();
  if (! thing_is_projectile(t)) {
    return true;
  }
  THING_LOG(t, "debug iter %u v-iter %u", t->iter[ iter_index ], v->iter[ iter_index ]);
  return true;
}
