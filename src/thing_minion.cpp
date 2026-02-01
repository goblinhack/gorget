//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_inlines.hpp"

#include <string.h>

//
// Add a minion to the mob if possible
//
int thing_minion_count(Gamep g, Levelsp v, Levelp l, Thingp mob)
{
  if (! mob) {
    return 0;
  }

  if (! thing_is_mob(mob)) {
    return 0;
  }

  auto ext_struct = thing_ext_struct(g, mob);
  if (! ext_struct) {
    return 0;
  }

  return ext_struct->minions.count;
}

//
// Add a minion to the mob if possible
//
Thingp thing_minion_spawn(Gamep g, Levelsp v, Levelp l, Thingp mob, Tpp tp_minion)
{
  TRACE_NO_INDENT();

  if (! mob) {
    return nullptr;
  }

  if (! thing_is_mob(mob)) {
    THING_ERR(mob, "non mob trying to spawn minions");
    return nullptr;
  }

  if (! tp_minion) {
    THING_ERR(mob, "no minion to spawn");
    return nullptr;
  }

  if (! tp_is_minion(tp_minion)) {
    THING_ERR(mob, "mob trying to spawn non minion %s", tp_name(tp_minion).c_str());
    return nullptr;
  }

  auto ext_struct = thing_ext_struct(g, mob);
  if (! ext_struct) {
    THING_ERR(mob, "mob is missing ext struct");
    return nullptr;
  }

  //
  // Too many minions
  //
  if (thing_minion_count(g, v, l, mob) >= THING_MINION_MAX - 1) {
    return nullptr;
  }

  //
  // Create the minion. Should be no chance to fail now.
  //
  auto new_minion = thing_spawn(g, v, l, tp_minion, thing_at(mob));
  if (! new_minion) {
    return nullptr;
  }

  //
  // Look for a free slot
  //
  FOR_ALL_MINION_SLOTS(g, v, l, mob, slot, existing_minion)
  {
    if (existing_minion) {
      continue;
    }

    memset(slot, 0, sizeof(*slot));
    slot->minion_id    = new_minion->id;
    new_minion->mob_id = mob->id;
    ext_struct->minions.count++;
    return new_minion;
  }

  //
  // Out of slots; but we checked above
  //
  THING_ERR(mob, "unexpectedly out of minion slots");
  return nullptr;
}

//
// Detach a minion from its mob
//
bool thing_minion_detach(Gamep g, Levelsp v, Levelp l, Thingp mob, Thingp minion)
{
  TRACE_NO_INDENT();

  if (! mob) {
    return false;
  }

  if (! minion) {
    return false;
  }

  if (! minion->mob_id) {
    return false;
  }

  if (! thing_is_mob(mob)) {
    THING_ERR(mob, "non mob trying to detach minion");
    return false;
  }

  if (! thing_is_minion(minion)) {
    THING_ERR(mob, "mob trying to detach non minion %s", thing_short_name(g, v, l, minion).c_str());
    return false;
  }

  auto ext_struct = thing_ext_struct(g, mob);
  if (! ext_struct) {
    return false;
  }

  //
  // Look for the thing
  //
  FOR_ALL_MINION_SLOTS(g, v, l, mob, slot, existing_minion)
  {
    if (minion != existing_minion) {
      continue;
    }

    if (ext_struct->minions.count <= 0) {
      THING_ERR(mob, "mob has unexpected minion count when detaching: %s", thing_short_name(g, v, l, minion).c_str());
      return false;
    }

    ext_struct->minions.count--;
    memset(slot, 0, sizeof(*slot));

    if (! minion->mob_id) {
      THING_ERR(mob, "mob found detached minion: %s", thing_short_name(g, v, l, minion).c_str());
      return false;
    }

    minion->mob_id = 0;
    return true;
  }

  THING_ERR(mob, "mob could not find minion to detach: %s", thing_short_name(g, v, l, minion).c_str());
  return false;
}

//
// Dump all minions
//
void thing_minions_dump(Gamep g, Levelsp v, Levelp l, Thingp mob)
{
  TRACE_NO_INDENT();

  if (! mob) {
    return;
  }

  if (! thing_is_mob(mob)) {
    THING_ERR(mob, "non mob trying to detach minion");
    return;
  }

  auto ext_struct = thing_ext_struct(g, mob);
  if (! ext_struct) {
    return;
  }

  FOR_ALL_MINION_SLOTS(g, v, l, mob, slot, existing_minion)
  {
    if (! existing_minion) {
      THING_LOG(mob, "slot %d: -", _n_);
      continue;
    }

    auto s = to_string(g, existing_minion);
    THING_LOG(mob, "slot %d: %s", _n_, s.c_str());
  }
}
