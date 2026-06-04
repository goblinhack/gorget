//
// Copyright goblinhack@gmail.com
//

#include "my_bpoint.hpp"
#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

void thing_on_thrown_set(Tpp tp, thing_on_thrown_t callback)
{
  TRACE();
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return;
  }
  tp->on_thrown = callback;
}

void thing_on_thrown(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp thrower)
{
  TRACE();
  auto *tp = thing_tp(me);
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return;
  }
  if (tp->on_thrown == nullptr) {
    return;
  }
  tp->on_thrown(g, v, l, me, thrower);
}
