//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_inlines.hpp"

//
// Add an item to the things inventory
//
static auto thing_wield_item(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp wielder) -> bool
{
  TRACE();

  if (! thing_is_item(item)) {
    return false;
  }

  if (! thing_is_able_to_wield_items(wielder)) {
    return false;
  }

  if (! thing_is_player(wielder) && ! thing_is_monst(wielder)) {
    thing_err(wielder, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  auto s = to_string(g, v, l, item);
  THING_DBG(wielder, "wield: %s", s.c_str());
  TRACE_INDENT();

  if (! thing_is_wielded_try_set(g, v, l, item, wielder)) {
    THING_DBG(wielder, "wield: %s (failed)", s.c_str());
    TRACE_INDENT();

    if (thing_is_player(wielder)) {
      auto the_thing = thing_name_long_the(g, v, l, item);
      topcon("You fail to wield %s.", the_thing.c_str());
    }
    return false;
  }

  (void) thing_pop(g, v, item);

  thing_inventory_dump(g, v, l, wielder);

  if (thing_is_player(wielder)) {
    auto the_thing = thing_name_long_the(g, v, l, item);
    topcon("You wield %s.", the_thing.c_str());
    game_request_to_remake_ui_set(g);
  }

  return true;
}

//
// Drop an item from the things inventory
//
static auto thing_unwield_item(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp wielder) -> bool
{
  TRACE();

  if (! thing_is_item(item)) {
    return false;
  }

  if (! thing_is_wielded(item)) {
    return false;
  }

  if (! thing_is_player(wielder) && ! thing_is_monst(wielder)) {
    thing_err(wielder, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  auto s = to_string(g, v, l, item);
  THING_DBG(wielder, "unwield: %s", s.c_str());
  TRACE_INDENT();

  if (! thing_is_wielded_try_unset(g, v, l, item, wielder)) {
    THING_DBG(wielder, "unwield: %s (failed)", s.c_str());
    TRACE_INDENT();

    if (thing_is_player(wielder)) {
      auto the_thing = thing_name_long_the(g, v, l, item);
      topcon("You fail to unwield %s.", the_thing.c_str());
    }
    return false;
  }

  if (thing_is_player(wielder)) {
    auto the_thing = thing_name_long_the(g, v, l, item);
    topcon("You unwield %s.", the_thing.c_str());
    game_request_to_remake_ui_set(g);
  }

  return true;
}

auto thing_is_wielded(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return t->_is_wielded;
}

//
// Returns true/false on success/fail
//
auto thing_is_wielded_try_set(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp wielder, bool val) -> bool
{
  TRACE_DEBUG();

  if (! thing_is_player(wielder) && ! thing_is_monst(wielder)) {
    thing_err(wielder, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  if (item == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  if (item->_is_wielded == static_cast< int >(val)) {
    auto s = to_string(g, v, l, item);
    THING_DBG(wielder, "wield-try: %s (failed, already wielded)", s.c_str());
    return true;
  }
  auto old_value    = item->_is_wielded;
  item->_is_wielded = val;

  //
  // Attempt the wield/unwield. It can fail.
  //
  if (val) {
    //
    // Try to wield
    //
    if (! thing_on_wield_request(g, v, l, item, wielder)) {
      //
      // Collect failed
      //
      item->_is_wielded = old_value;

      auto s = to_string(g, v, l, item);
      THING_DBG(wielder, "wield-try: %s (failed, wield request)", s.c_str());
      return false;
    }
  } else {
    //
    // Try to unwield
    //
    if (! thing_on_unwield_request(g, v, l, item, wielder)) {
      //
      // Drop failed
      //
      item->_is_wielded = old_value;

      auto s = to_string(g, v, l, item);
      THING_DBG(wielder, "unwield-try: %s (failed, unwield request)", s.c_str());
      return false;
    }
  }

  return true;
}

auto thing_is_wielded_try_unset(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp wielder) -> bool
{
  TRACE_DEBUG();

  return thing_is_wielded_try_set(g, v, l, item, wielder, false);
}

void thing_on_wield_request_set(Tpp tp, thing_on_wield_request_t callback)
{
  TRACE();
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return;
  }
  tp->on_wield_request = callback;
}

auto thing_on_wield_request(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp wielder) -> bool
{
  TRACE();
  auto *tp = thing_tp(me);
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return false;
  }
  if (tp->on_wield_request == nullptr) {
    //
    // Assume success
    //
    return true;
  }
  if (! thing_is_player(wielder) && ! thing_is_monst(wielder)) {
    thing_err(wielder, "unexpected thing for %s", __FUNCTION__);
    return false;
  }
  return tp->on_wield_request(g, v, l, me, wielder);
}

void thing_on_unwield_request_set(Tpp tp, thing_on_unwield_request_t callback)
{
  TRACE();
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return;
  }
  tp->on_unwield_request = callback;
}

auto thing_on_unwield_request(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp unwieldper) -> bool
{
  TRACE();
  auto *tp = thing_tp(me);
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return false;
  }
  if (tp->on_unwield_request == nullptr) {
    //
    // Assume success
    //
    return true;
  }
  if (! thing_is_player(unwieldper) && ! thing_is_monst(unwieldper)) {
    thing_err(unwieldper, "unexpected thing for %s", __FUNCTION__);
    return false;
  }
  return tp->on_unwield_request(g, v, l, me, unwieldper);
}

auto thing_wielding(Gamep g, Levelsp v, Levelp l, Thingp me) -> Thingp
{
  TRACE();

  if (me == nullptr) {
    ERR("no thing pointer");
    return nullptr;
  }

  if (! static_cast< bool >(me->wielding_id)) {
    return nullptr;
  }

  return thing_find_optional(g, v, me->wielding_id);
}

void thing_unwield(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE();

  if (me == nullptr) {
    ERR("no thing pointer");
    return;
  }

  auto item = thing_wielding(g, v, l, me);
  if (item) {
    if (! thing_unwield_item(g, v, l, item, me)) {
      thing_err(me, "failed to unwield");
    }

    me->wielding_id = 0;
  }
}

void thing_wield(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp item)
{
  TRACE();

  if (me == nullptr) {
    ERR("no thing pointer");
    return;
  }

  if (! item) {
    thing_err(me, "no item to wield");
    return;
  }

  thing_unwield(g, v, l, me);

  if (thing_wield_item(g, v, l, item, me)) {
    me->wielding_id = item->id;
  }
}
