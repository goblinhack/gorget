//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_inlines.hpp"

#include <string.h>

//
// Anything in the inventory
//
bool thing_inventory_is_empty(Gamep g, Levelsp v, Levelp l, Thingp player_or_monst)
{
  TRACE_NO_INDENT();

  if (! thing_is_player(player_or_monst) && ! thing_is_monst(player_or_monst)) {
    THING_ERR(player_or_monst, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  FOR_ALL_INVENTORY_ITEMS(g, v, l, player_or_monst, item) { return false; }

  return true;
}

//
// Can we combine identical items?
//
bool thing_inventory_item_mergeable(Gamep g, Levelsp v, Levelp l, Thingp a, Thingp b)
{
  if (! thing_is_item_mergeable(a)) {
    return false;
  }

  if (! thing_is_item_mergeable(b)) {
    return false;
  }

  if (a->tp_id != b->tp_id) {
    return false;
  }

  return true;
}

//
// Add an item to the inventory
//
bool thing_inventory_add(Gamep g, Levelsp v, Levelp l, Thingp new_item, Thingp player_or_monst)
{
  TRACE_NO_INDENT();

  if (! thing_is_player(player_or_monst) && ! thing_is_monst(player_or_monst)) {
    THING_ERR(player_or_monst, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  if (! new_item) {
    return false;
  }

  auto ai_struct = thing_ext_struct(g, player_or_monst);
  if (! ai_struct) {
    return false;
  }

  //
  // Look for a matching item first.
  //
  FOR_ALL_INVENTORY_SLOTS(g, v, l, player_or_monst, slot, item)
  {
    if (! item) {
      continue;
    }

    if (! thing_inventory_item_mergeable(g, v, l, item, new_item)) {
      continue;
    }

    slot->count++;

    ThingEvent e {
        .reason     = "by merging",               //
        .event_type = THING_EVENT_CARRIED_MERGED, //
        .source     = player_or_monst             //
    };

    thing_dead(g, v, l, new_item, e);

    return true;
  }

  //
  // Look for a free slot
  //
  FOR_ALL_INVENTORY_SLOTS(g, v, l, player_or_monst, slot, item)
  {
    if (item) {
      continue;
    }

    memset(slot, 0, sizeof(*slot));
    slot->item_id = new_item->id;
    slot->count   = 1;
    return true;
  }

  //
  // Out of slots
  //
  return false;
}

//
// Drop an item to the inventory
//
bool thing_inventory_remove(Gamep g, Levelsp v, Levelp l, Thingp drop_item, Thingp player_or_monst)
{
  TRACE_NO_INDENT();

  if (! thing_is_player(player_or_monst) && ! thing_is_monst(player_or_monst)) {
    THING_ERR(player_or_monst, "unexpected thing for %s", __FUNCTION__);
    return false;
  }

  if (! drop_item) {
    return false;
  }

  auto ai_struct = thing_ext_struct(g, player_or_monst);
  if (! ai_struct) {
    return false;
  }

  //
  // Look for the thing
  //
  FOR_ALL_INVENTORY_SLOTS(g, v, l, player_or_monst, slot, item)
  {
    if (thing_tp(drop_item) != thing_tp(item)) {
      continue;
    }

    slot->count--;

    if (slot->count > 1) {
      continue;
    }

    memset(slot, 0, sizeof(*slot));
    return true;
  }

  return true;
}

//
// Drop an item to the inventory
//
void thing_inventory_dump(Gamep g, Levelsp v, Levelp l, Thingp player_or_monst)
{
  TRACE_NO_INDENT();

  if (! thing_is_player(player_or_monst) && ! thing_is_monst(player_or_monst)) {
    THING_ERR(player_or_monst, "unexpected thing for %s", __FUNCTION__);
    return;
  }

  auto ai_struct = thing_ext_struct(g, player_or_monst);
  if (! ai_struct) {
    return;
  }

  FOR_ALL_INVENTORY_SLOTS(g, v, l, player_or_monst, slot, item)
  { //
    if (! item) {
      THING_LOG(player_or_monst, "slot %d: -", _n_);
      continue;
    }

    auto s = to_string(g, item);
    if (slot->count) {
      THING_LOG(player_or_monst, "slot %d: %s, count %d", _n_, s.c_str(), slot->count);
    } else {
      THING_LOG(player_or_monst, "slot %d: %s", _n_, s.c_str());
    }
  }
}
