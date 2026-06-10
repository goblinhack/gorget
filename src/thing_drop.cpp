//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

//
// Drop an item from the things inventory
//
static auto thing_drop_item(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp user, ThingEvent &e) -> bool
{
  TRACE();

  if (! thing_is_item(item)) {
    thing_err(user, "unexpected non thing, %s", __FUNCTION__);
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

  auto s = to_string(g, v, l, item);
  THING_DBG(user, "drop: %s", s.c_str());
  TRACE_INDENT();

  if (! thing_is_carried_unset(g, v, l, item, user, e)) {
    THING_DBG(user, "drop: %s (failed)", s.c_str());
    TRACE_INDENT();

    if (thing_is_player(user)) {
      if (e.event_type == THING_EVENT_USER_INITIATED) {
        auto the_thing = thing_name_long_the(g, v, l, item);
        topcon("You fail to drop %s.", the_thing.c_str());
      }
    }
    return false;
  }

  //
  // Drop the thing where the player is
  //
  if (thing_inventory_get_item_count(g, v, l, item, user) == -1) {
    //
    // But only if the last item
    //
    if (! thing_is_thrown(item)) {
      if (! thing_warp_to(g, v, l, item, thing_at(user))) {
        if (e.event_type == THING_EVENT_USER_INITIATED) {
          auto the_thing = thing_name_long_the(g, v, l, item);
          topcon("You fail to place %s.", the_thing.c_str());
        }
        return false;
      }
    }
  }

  if (thing_is_player(user)) {
    if (e.event_type == THING_EVENT_USER_INITIATED) {
      auto the_thing = thing_name_long_the(g, v, l, item);
      topcon("You drop %s.", the_thing.c_str());
    }
    game_request_to_remake_ui_set(g);
  }

  if (e.event_type == THING_EVENT_USER_INITIATED) {
    if (thing_is_tick_on_drop(item)) {
      (void) level_tick_begin_requested(g, v, l, "player dropped an item");
    }
  }

  thing_owner_unset(g, v, l, item);

  return true;
}

void thing_on_drop_request_set(Tpp tp, thing_on_drop_request_t callback)
{
  TRACE();
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return;
  }
  tp->on_drop_request = callback;
}

[[nodiscard]] auto thing_on_drop_request(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp user, ThingEvent &e) -> bool
{
  TRACE();
  auto *tp = thing_tp(me);
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return false;
  }
  if (tp->on_drop_request == nullptr) {
    //
    // Assume success
    //
    return true;
  }
  if (! thing_is_player(user) && ! thing_is_monst(user)) {
    thing_err(user, "unexpected thing for %s", __FUNCTION__);
    return false;
  }
  return tp->on_drop_request(g, v, l, me, user, e);
}

void thing_on_drop_success_set(Tpp tp, thing_on_drop_success_t callback)
{
  TRACE();
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return;
  }
  tp->on_drop_success = callback;
}

[[nodiscard]] auto thing_on_drop_success(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp user, ThingEvent &e) -> bool
{
  TRACE();
  auto *tp = thing_tp(me);
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return false;
  }
  if (tp->on_drop_success == nullptr) {
    //
    // Assume success
    //
    return true;
  }
  if (! thing_is_player(user) && ! thing_is_monst(user)) {
    thing_err(user, "unexpected thing for %s", __FUNCTION__);
    return false;
  }
  return tp->on_drop_success(g, v, l, me, user, e);
}

[[nodiscard]] auto thing_drop(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp item, ThingEvent &e) -> bool
{
  TRACE();

  if (me == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  if (item == nullptr) {
    thing_err(me, "no item to drop");
    return false;
  }

  if (thing_is_wielded(item)) {
    if (! thing_unwield(g, v, l, me, e)) {
      return false;
    }
  }

  return thing_drop_item(g, v, l, item, me, e);
}
