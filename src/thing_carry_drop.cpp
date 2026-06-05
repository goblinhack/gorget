//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

//
// Add an item to the things inventory
//
static auto thing_carry_item(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp carrier, ThingEvent &e) -> bool
{
  TRACE();

  if (! thing_is_able_to_collect_items(carrier)) {
    return false;
  }

  if (! thing_is_item(item)) {
    return false;
  }

  if (! thing_is_player(carrier) && ! thing_is_monst(carrier)) {
    thing_err(carrier, "unexpected thing, %s", __FUNCTION__);
    return false;
  }

  auto s = to_string(g, v, l, item);
  THING_DBG(carrier, "carry: %s", s.c_str());
  TRACE_INDENT();

  if (! thing_is_carried_set(g, v, l, item, carrier, e)) {
    THING_DBG(carrier, "carry: %s (failed)", s.c_str());
    TRACE_INDENT();

    if (thing_is_player(carrier)) {
      auto the_thing = thing_name_long_the(g, v, l, item);
      topcon("You fail to carry %s.", the_thing.c_str());
    }
    return false;
  }

  (void) thing_pop(g, v, item);

  thing_inventory_dump(g, v, l, carrier);

  if (thing_is_player(carrier)) {
    if (e.event_type != THING_EVENT_SPAWNED) {
      auto the_thing = thing_name_long_the(g, v, l, item);
      topcon("You carry %s.", the_thing.c_str());
    }
    game_request_to_remake_ui_set(g);
  }

  thing_owner_set(g, v, l, item, carrier);

  return true;
}

//
// Drop an item from the things inventory
//
static auto thing_drop_item(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp dropper, ThingEvent &e) -> bool
{
  TRACE();

  if (! thing_is_item(item)) {
    thing_err(dropper, "unexpected non thing, %s", __FUNCTION__);
    return false;
  }

  if (! thing_is_carried(item)) {
    thing_err(dropper, "unexpected uncarried thing, %s", __FUNCTION__);
    return false;
  }

  if (! thing_is_player(dropper) && ! thing_is_monst(dropper)) {
    thing_err(dropper, "unexpected thing, %s", __FUNCTION__);
    return false;
  }

  auto s = to_string(g, v, l, item);
  THING_DBG(dropper, "drop: %s", s.c_str());
  TRACE_INDENT();

  if (! thing_is_carried_unset(g, v, l, item, dropper, e)) {
    THING_DBG(dropper, "drop: %s (failed)", s.c_str());
    TRACE_INDENT();

    if (thing_is_player(dropper)) {
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
  if (! thing_warp_to(g, v, l, item, thing_at(dropper))) {
    if (e.event_type == THING_EVENT_USER_INITIATED) {
      auto the_thing = thing_name_long_the(g, v, l, item);
      topcon("You fail to place %s.", the_thing.c_str());
    }
    return false;
  }

  if (thing_is_player(dropper)) {
    if (e.event_type == THING_EVENT_USER_INITIATED) {
      auto the_thing = thing_name_long_the(g, v, l, item);
      topcon("You drop %s.", the_thing.c_str());
    }
    game_request_to_remake_ui_set(g);
  }

  if (thing_is_tick_on_drop(item)) {
    (void) level_tick_begin_requested(g, v, l, "player dropped an item");
  }

  thing_owner_unset(g, v, l, item);

  return true;
}

[[nodiscard]] auto thing_is_carried(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return t->_is_carried;
}

//
// Returns true/false on success/fail
//
[[nodiscard]] auto thing_is_carried_set(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp carrier, ThingEvent &e, bool val) -> bool
{
  TRACE_DEBUG();

  if (! thing_is_player(carrier) && ! thing_is_monst(carrier)) {
    thing_err(carrier, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  if (item == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  if (item->_is_carried == static_cast< int >(val)) {
    auto s = to_string(g, v, l, item);
    THING_DBG(carrier, "carry-try: %s (failed, already carried)", s.c_str());
    return true;
  }
  auto old_value    = item->_is_carried;
  item->_is_carried = val;

  //
  // Attempt the collect/drop. It can fail.
  //
  if (val) {
    //
    // Try to collect
    //
    THING_DBG(item, "carry request");
    TRACE_INDENT();

    if (! thing_on_carry_request(g, v, l, item, carrier, e)) {
      //
      // Collect failed
      //
      item->_is_carried = old_value;

      auto s = to_string(g, v, l, item);
      THING_DBG(carrier, "carry-try: %s (failed, carry request)", s.c_str());
      return false;
    }

    //
    // Add to the inventory.
    //
    if (thing_inventory_add(g, v, l, item, carrier)) {
      //
      // Success
      //
      (void) thing_on_carry_success(g, v, l, item, carrier, e);
    } else {
      //
      // Possibly out of slots
      //
      item->_is_carried = old_value;

      auto s = to_string(g, v, l, item);
      THING_DBG(carrier, "carry-try: %s (failed, inventory add)", s.c_str());
      return false;
    }

  } else {
    //
    // Try to drop
    //
    THING_DBG(item, "drop request");
    TRACE_INDENT();

    if (! thing_on_drop_request(g, v, l, item, carrier, e)) {
      //
      // Drop failed
      //
      item->_is_carried = old_value;

      auto s = to_string(g, v, l, item);
      THING_DBG(carrier, "drop-try: %s (failed, drop request)", s.c_str());
      return false;
    }

    //
    // Remove from the inventory.
    //
    if (thing_inventory_remove(g, v, l, item, carrier)) {
      //
      // Success
      //
      (void) thing_on_drop_success(g, v, l, item, carrier, e);

      //
      // If counts remain, keep the item as carried
      //
      if (thing_inventory_get_item_count(g, v, l, item, carrier) != 0) {
        item->_is_carried = old_value;
      }
    } else {
      //
      // Remove failed
      //
      item->_is_carried = old_value;

      auto s = to_string(g, v, l, item);
      THING_DBG(carrier, "drop-try: %s (failed, inventory remove)", s.c_str());
      return false;
    }
  }

  //
  // Reset animation
  //
  thing_anim_init(g, v, l, item, THING_ANIM_IDLE);

  return true;
}

[[nodiscard]] auto thing_is_carried_unset(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp carrier, ThingEvent &e) -> bool
{
  TRACE_DEBUG();

  return thing_is_carried_set(g, v, l, item, carrier, e, false);
}

void thing_on_carry_request_set(Tpp tp, thing_on_carry_request_t callback)
{
  TRACE();
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return;
  }
  tp->on_carry_request = callback;
}

[[nodiscard]] auto thing_on_carry_request(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp carrier, ThingEvent &e) -> bool
{
  TRACE();
  auto *tp = thing_tp(me);
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return false;
  }
  if (tp->on_carry_request == nullptr) {
    //
    // Assume success
    //
    return true;
  }
  if (! thing_is_player(carrier) && ! thing_is_monst(carrier)) {
    thing_err(carrier, "unexpected thing for %s", __FUNCTION__);
    return false;
  }
  return tp->on_carry_request(g, v, l, me, carrier, e);
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

[[nodiscard]] auto thing_on_drop_request(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp dropper, ThingEvent &e) -> bool
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
  if (! thing_is_player(dropper) && ! thing_is_monst(dropper)) {
    thing_err(dropper, "unexpected thing for %s", __FUNCTION__);
    return false;
  }
  return tp->on_drop_request(g, v, l, me, dropper, e);
}

void thing_on_carry_success_set(Tpp tp, thing_on_carry_success_t callback)
{
  TRACE();
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return;
  }
  tp->on_carry_success = callback;
}

[[nodiscard]] auto thing_on_carry_success(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp carrier, ThingEvent &e) -> bool
{
  TRACE();
  auto *tp = thing_tp(me);
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return false;
  }
  if (tp->on_carry_success == nullptr) {
    //
    // Assume success
    //
    return true;
  }
  if (! thing_is_player(carrier) && ! thing_is_monst(carrier)) {
    thing_err(carrier, "unexpected thing for %s", __FUNCTION__);
    return false;
  }
  return tp->on_carry_success(g, v, l, me, carrier, e);
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

[[nodiscard]] auto thing_on_drop_success(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp dropper, ThingEvent &e) -> bool
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
  if (! thing_is_player(dropper) && ! thing_is_monst(dropper)) {
    thing_err(dropper, "unexpected thing for %s", __FUNCTION__);
    return false;
  }
  return tp->on_drop_success(g, v, l, me, dropper, e);
}

[[nodiscard]] auto thing_carry(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp item, ThingEvent &e) -> bool
{
  TRACE();

  if (me == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  if (item == nullptr) {
    thing_err(me, "no item to carry");
    return false;
  }

  if (! thing_carry_item(g, v, l, item, me, e)) {
    return false;
  }

  //
  // Auto wield if nothing wielded?
  //
  if (thing_is_auto_wield(item)) {
    if (thing_wielding(g, v, l, me) == nullptr) {
      if (! thing_wield(g, v, l, me, item, e)) {
        return false;
      }
    }
  }

  return true;
}

[[nodiscard]] auto thing_drop(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp item, ThingEvent &e) -> bool
{
  TRACE();

  if (me == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  if (item == nullptr) {
    thing_err(me, "no item to carry");
    return false;
  }

  if (thing_is_wielded(item)) {
    if (! thing_unwield(g, v, l, me, e)) {
      return false;
    }
  }

  return thing_drop_item(g, v, l, item, me, e);
}
