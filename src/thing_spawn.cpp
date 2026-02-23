//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_thing_callbacks.hpp"

auto thing_spawn(Gamep g, Levelsp v, Levelp l, Tpp tp, const fpoint &at) -> Thingp
{
  TRACE_NO_INDENT();

  auto *t = thing_init(g, v, l, tp, at);
  if (t == nullptr) {
    if (g_opt_test_current == "test_alloc_free_monsts") {
      TP_LOG(tp, "failed to init thing");
    } else {
      TP_ERR(tp, "failed to init thing");
    }
    return nullptr;
  }

  if (! thing_push(g, v, l, t)) {
    THING_ERR(t, "failed to push");
    return nullptr;
  }

  {
    THING_DBG(t, "spawned");
  }

  //
  // This is reset each tick
  //
  if (thing_is_tick_end_delay(t)) {
    l->is_tick_end_delay = true;
  }

  thing_is_spawned_set(g, v, l, t);

  return t;
}

auto thing_spawn(Gamep g, Levelsp v, Levelp l, Tpp tp, const spoint &at) -> Thingp { return thing_spawn(g, v, l, tp, make_fpoint(at)); }

auto thing_spawn(Gamep g, Levelsp v, Levelp l, Tpp tp, Thingp at) -> Thingp
{
  if (at == nullptr) {
    ERR("No thing pointer");
    return nullptr;
  }
  return thing_spawn(g, v, l, tp, thing_at(at));
}
