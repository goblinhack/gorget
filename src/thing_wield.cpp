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
#include "my_ui.hpp"

//

// Drop an item from the things inventory
//
auto thing_unwield_item(Gamep g, Levelsp v, Levelp l, Thingp wielder, Thingp item, ThingEvent &e) -> bool
{
  TRACE();

  if (! thing_is_item(item)) {
    auto s = to_string(g, v, l, item);
    THING_DBG(g, v, l, wielder, "unwield fail (not an item): %s", s.c_str());
    return false;
  }

  if (! thing_is_wielded(item)) {
    auto s = to_string(g, v, l, item);
    THING_DBG(g, v, l, wielder, "unwield fail (not wielded): %s", s.c_str());
    return false;
  }

  if (! thing_is_player(wielder) && ! thing_is_monst(wielder)) {
    thing_err(g, v, l, wielder, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  auto s = to_string(g, v, l, item);
  THING_DBG(g, v, l, wielder, "unwield: %s", s.c_str());
  TRACE_INDENT();

  if (! thing_is_wielded_try_unset(g, v, l, item, wielder)) {
    THING_DBG(g, v, l, wielder, "unwield: %s (failed)", s.c_str());
    TRACE_INDENT();

    if (thing_is_player(wielder)) {
      if (e.event_type == THING_EVENT_USER_INITIATED) {
        auto the_thing = thing_name_long_the(g, v, l, item);
        topcon(UI_IMPORTANT_FMT_STR "You fail to unwield %s." UI_RESET_FMT, the_thing.c_str());
      }
    }
    return false;
  }

  if (thing_is_player(wielder)) {
    if (e.event_type == THING_EVENT_USER_INITIATED) {
      auto the_thing = thing_name_long_the(g, v, l, item);
      topcon("You unwield %s.", the_thing.c_str());
    }
    game_request_to_remake_ui_set(g);

    if (thing_is_tick_on_unwield(item)) {
      (void) level_tick_begin_requested(g, v, l, "player wielded an item");
    }
  }

  bool removed {};

  FOR_ALL_WIELD_TYPES(w)
  {
    if (wielder->wielding_id[ w ] == item->id) {
      wielder->wielding_id[ w ] = 0;
      removed                   = true;
      break;
    }
  }

  if (! removed) {
    thing_err(g, v, l, wielder, "unwield failed (remove did not find): %s", s.c_str());
    return false;
  }

  THING_DBG(g, v, l, wielder, "unwield success: %s", s.c_str());
  TRACE_INDENT();

  thing_inventory_dump(g, v, l, wielder);

  return true;
}

[[nodiscard]] auto thing_is_wielded(Thingp t) -> bool
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
[[nodiscard]] auto thing_is_wielded_try_set(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp wielder, bool val) -> bool
{
  TRACE_DEBUG();

  if (! thing_is_player(wielder) && ! thing_is_monst(wielder)) {
    thing_err(g, v, l, wielder, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  if (item == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  if (item->_is_wielded == static_cast< int >(val)) {
    auto s = to_string(g, v, l, item);
    THING_DBG(g, v, l, wielder, "wield-try: %s (failed, already wielded)", s.c_str());
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
      THING_DBG(g, v, l, wielder, "wield-try: %s (failed, wield request)", s.c_str());
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
      THING_DBG(g, v, l, wielder, "unwield-try: %s (failed, unwield request)", s.c_str());
      return false;
    }
  }

  return true;
}

[[nodiscard]] auto thing_is_wielded_try_unset(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp wielder) -> bool
{
  TRACE_DEBUG();

  return thing_is_wielded_try_set(g, v, l, item, wielder, false);
}

[[nodiscard]] auto thing_wielding_get(Gamep g, Levelsp v, Levelp l, Thingp wielder, WieldType w) -> Thingp
{
  TRACE();

  if (wielder == nullptr) {
    ERR("no thing pointer");
    return nullptr;
  }

  if (! static_cast< bool >(wielder->wielding_id[ w ])) {
    return nullptr;
  }

  return thing_find_optional(g, v, wielder->wielding_id[ w ]);
}

//
// Add an item to the things inventory
//
static auto thing_wield_item_do(Gamep g, Levelsp v, Levelp l, Thingp wielder, Thingp item, ThingEvent &e) -> bool
{
  TRACE();

  if (! thing_is_item(item)) {
    return false;
  }

  if (! thing_is_able_to_wield_items(wielder)) {
    return false;
  }

  if (! thing_is_player(wielder) && ! thing_is_monst(wielder)) {
    thing_err(g, v, l, wielder, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  auto s = to_string(g, v, l, item);
  THING_DBG(g, v, l, wielder, "wield: %s", s.c_str());
  TRACE_INDENT();

  if (! thing_is_wielded_try_set(g, v, l, item, wielder)) {
    THING_DBG(g, v, l, wielder, "wield: %s (failed)", s.c_str());
    TRACE_INDENT();

    if (thing_is_player(wielder)) {
      auto the_thing = thing_name_long_the(g, v, l, item);
      topcon(UI_IMPORTANT_FMT_STR "You fail to wield %s." UI_RESET_FMT, the_thing.c_str());
    }
    return false;
  }

  (void) thing_pop(g, v, item);

  thing_inventory_dump(g, v, l, wielder);

  if (thing_is_player(wielder)) {
    if (e.event_type != THING_EVENT_SPAWNED) {
      auto the_thing = thing_name_long_the(g, v, l, item);
      topcon("You wield %s.", the_thing.c_str());
    }
    game_request_to_remake_ui_set(g);

    if (thing_is_tick_on_wield(item)) {
      (void) level_tick_begin_requested(g, v, l, "player wielded an item");
    }
  }

  if (! thing_is_wielded(item)) {
    thing_err(g, v, l, wielder, "wield fail (claimed success): %s", s.c_str());
    return false;
  }

  return true;
}

[[nodiscard]] static auto thing_wield_item_slot(Gamep g, Levelsp v, Levelp l, Thingp wielder, Thingp item, WieldType w, ThingEvent &e) -> bool
{
  TRACE();

  if (wielder == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  if (item == nullptr) {
    thing_err(g, v, l, wielder, "no item to wield");
    return false;
  }

  auto s = to_string(g, v, l, item);
  THING_DBG(g, v, l, wielder, "wield: %s (%s)", s.c_str(), WieldType_to_string(w).c_str());
  TRACE_INDENT();

  if (wielder->wielding_id[ w ] != 0U) {
    auto *existing_item = thing_wielding_get(g, v, l, wielder, w);
    if (existing_item == nullptr) {
      thing_err(g, v, l, wielder, "wielding_id is set, but no item");
      return false;
    }

    //
    // Already wielded
    //
    if (existing_item == item) {
      THING_DBG(g, v, l, wielder, "wield (already wielded): %s", s.c_str());
      return true;
    }

    auto s2 = to_string(g, v, l, existing_item);
    THING_DBG(g, v, l, wielder, "unwield existing: %s", s2.c_str());
    TRACE_INDENT();

    if (! thing_unwield_item(g, v, l, wielder, existing_item, e)) {
      THING_DBG(g, v, l, wielder, "unwield existing fail: %s (%s)", s.c_str(), WieldType_to_string(w).c_str());
      return false;
    }
  }

  if (! thing_wield_item_do(g, v, l, wielder, item, e)) {
    THING_DBG(g, v, l, wielder, "wield fail: %s (%s)", s.c_str(), WieldType_to_string(w).c_str());
    return false;
  }

  if (! thing_is_wielded(item)) {
    thing_err(g, v, l, wielder, "wield fail (claimed success): %s", s.c_str());
    return false;
  }

  THING_DBG(g, v, l, wielder, "wield success: %s (%s)", s.c_str(), WieldType_to_string(w).c_str());

  wielder->wielding_id[ w ] = item->id;

  return true;
}

//
// Wield into a free slot. If there is something there already, or no free slots, unwield something
//
[[nodiscard]] auto thing_wield_item(Gamep g, Levelsp v, Levelp l, Thingp wielder, Thingp item, ThingEvent &e) -> bool
{
  TRACE();

  if (wielder == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  if (item == nullptr) {
    thing_err(g, v, l, wielder, "no item to wield");
    return false;
  }

  auto s = to_string(g, v, l, item);
  THING_DBG(g, v, l, wielder, "wield: %s", s.c_str());
  TRACE_INDENT();

  if (thing_is_weapon(item)) {
    auto *existing_item = thing_wielding_get(g, v, l, wielder, WIELD_TYPE_WEAPON);
    if (existing_item != nullptr) {
      //
      // Already wielded
      //
      if (existing_item == item) {
        THING_DBG(g, v, l, wielder, "wield (already wielded): %s", s.c_str());
        return true;
      }

      auto s2 = to_string(g, v, l, existing_item);
      THING_DBG(g, v, l, wielder, "unwield weapon: %s", s2.c_str());
      TRACE_INDENT();

      if (! thing_unwield_item(g, v, l, wielder, existing_item, e)) {
        return false;
      }
    }
    return thing_wield_item_slot(g, v, l, wielder, item, WIELD_TYPE_WEAPON, e);
  }

  if (thing_is_ring(item)) {
    auto *ring1 = thing_wielding_get(g, v, l, wielder, WIELD_TYPE_RING1);
    auto *ring2 = thing_wielding_get(g, v, l, wielder, WIELD_TYPE_RING2);

    //
    // Already wielded
    //
    if ((ring1 == item) || (ring2 == item)) {
      THING_DBG(g, v, l, wielder, "wield (already wielded): %s", s.c_str());
      return true;
    }

    if (ring1 != nullptr) {
      if (ring2 != nullptr) {
        auto s2 = to_string(g, v, l, ring2);
        THING_DBG(g, v, l, wielder, "unwield existing ring: %s", s2.c_str());
        TRACE_INDENT();

        if (! thing_unwield_item(g, v, l, wielder, ring2, e)) {
          return false;
        }
      }

      THING_DBG(g, v, l, wielder, "wield as ring2: %s", s.c_str());
      TRACE_INDENT();

      return thing_wield_item_slot(g, v, l, wielder, item, WIELD_TYPE_RING2, e);
    }
    THING_DBG(g, v, l, wielder, "wield as ring1: %s", s.c_str());
    TRACE_INDENT();

    return thing_wield_item_slot(g, v, l, wielder, item, WIELD_TYPE_RING1, e);
  }

  if (! thing_is_wielded(item)) {
    thing_err(g, v, l, wielder, "wield fail (claimed success): %s", s.c_str());
    return false;
  }

  return false;
}

//
// Wield into a free slot if there is nothing there already.
//
[[nodiscard]] auto thing_auto_wield_try(Gamep g, Levelsp v, Levelp l, Thingp wielder, Thingp item, ThingEvent &e) -> bool
{
  TRACE();

  if (! thing_is_auto_wield(item)) {
    return false;
  }

  auto s = to_string(g, v, l, item);
  THING_DBG(g, v, l, wielder, "auto wield: %s", s.c_str());
  TRACE_INDENT();

  if (thing_is_weapon(item)) {
    if (thing_wielding_get(g, v, l, wielder, WIELD_TYPE_WEAPON) == nullptr) {
      return thing_wield_item(g, v, l, wielder, item, e);
    }
  }

  if (thing_is_ring(item)) {
    if (thing_wielding_get(g, v, l, wielder, WIELD_TYPE_RING1) == nullptr) {
      return thing_wield_item_slot(g, v, l, wielder, item, WIELD_TYPE_RING1, e);
    }
    if (thing_wielding_get(g, v, l, wielder, WIELD_TYPE_RING2) == nullptr) {
      return thing_wield_item_slot(g, v, l, wielder, item, WIELD_TYPE_RING2, e);
    }
  }

  return false;
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

[[nodiscard]] auto thing_on_wield_request(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp wielder) -> bool
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
    thing_err(g, v, l, wielder, "unexpected thing for %s", __FUNCTION__);
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

[[nodiscard]] auto thing_on_unwield_request(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp unwieldper) -> bool
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
    thing_err(g, v, l, unwieldper, "unexpected thing for %s", __FUNCTION__);
    return false;
  }
  return tp->on_unwield_request(g, v, l, me, unwieldper);
}
