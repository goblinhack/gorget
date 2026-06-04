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

void thing_on_use_set(Tpp tp, thing_on_use_t callback)
{
  TRACE();
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return;
  }
  tp->on_use = callback;
}

[[nodiscard]] auto thing_on_use(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp user) -> bool
{
  TRACE();
  auto *tp = thing_tp(me);
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return false;
  }
  if (tp->on_use == nullptr) {
    //
    // Assume success
    //
    return false;
  }
  if (! thing_is_player(user) && ! thing_is_monst(user)) {
    thing_err(user, "unexpected thing for %s", __FUNCTION__);
    return false;
  }
  return tp->on_use(g, v, l, me, user);
}

//
// Use an item an remove it from the inventory if dead
//
static auto thing_use_item(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp user, ThingEvent &e) -> bool
{
  TRACE();

  if (! thing_is_item(item)) {
    thing_err(user, "unexpected non item thing, %s", __FUNCTION__);
    return false;
  }

  if (! thing_is_carried(item)) {
    thing_err(user, "unexpected uncarried thing, %s", __FUNCTION__);
    return false;
  }

  if (! thing_is_player(user) && ! thing_is_monst(user)) {
    thing_err(user, "unexpected thing, %s", __FUNCTION__);
    return false;
  }

  {
    auto s = to_string(g, v, l, item);
    THING_DBG(user, "use: %s", s.c_str());
  }
  TRACE_INDENT();

  if (! thing_on_use(g, v, l, item, user)) {
    if (e.event_type == THING_EVENT_USER_INITIATED) {
      auto the_thing = thing_name_long_the(g, v, l, item);
      topcon("You fail to use %s.", the_thing.c_str());
    }
    return false;
  }

  {
    auto s = to_string(g, v, l, item);
    THING_DBG(user, "used: %s", s.c_str());
  }
  TRACE_INDENT();

  //
  // This should either remove the thing or decrease the slot count
  //
  {
    auto new_event       = e;
    new_event.event_type = THING_EVENT_USED;

    (void) thing_drop(g, v, l, user, item, new_event);
  }

  if (thing_is_player(user)) {
    if (e.event_type == THING_EVENT_USER_INITIATED) {
      auto the_thing = thing_name_long_the(g, v, l, item);
      topcon("You use %s.", the_thing.c_str());
    }
    game_request_to_remake_ui_set(g);
  }

  return true;
}

[[nodiscard]] auto thing_use(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp item, ThingEvent &e) -> bool
{
  TRACE();

  if (me == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  if (item == nullptr) {
    thing_err(me, "no item to use");
    return false;
  }

  return thing_use_item(g, v, l, item, me, e);
}
