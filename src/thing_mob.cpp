//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_inlines.hpp"

#include <string.h>

//
// Add a minion to the mob if possible
//
int thing_mob_minion_count_get(Gamep g, Levelsp v, Levelp l, Thingp mob)
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
Thingp thing_mob_spawn_a_minion(Gamep g, Levelsp v, Levelp l, Thingp mob, Tpp tp_minion)
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

  //
  // Can't spawn over certain things
  //
  if (level_is_obs_to_spawning(g, v, l, thing_at(mob))) {
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
  if (thing_mob_minion_count_get(g, v, l, mob) >= THING_MINION_MAX - 1) {
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

    THING_LOG(mob, "spawned minion %s", thing_short_name(g, v, l, new_minion).c_str());
    THING_LOG(new_minion, "new born minion");

    return new_minion;
  }

  //
  // Out of slots; but we checked above
  //
  THING_ERR(mob, "unexpectedly out of minion slots");
  return nullptr;
}

//
// Detach or kill all minions (or a specific one)
//
static bool thing_mob_process_minions(Gamep g, Levelsp v, Levelp l, Thingp mob, Thingp specific_minion, ThingEvent &e)
{
  TRACE_NO_INDENT();

  if (! mob) {
    return false;
  }

  if (! thing_is_mob(mob)) {
    THING_ERR(mob, "non mob trying to detach minions");
    return false;
  }

  auto ext_struct = thing_ext_struct(g, mob);
  if (! ext_struct) {
    return false;
  }

  FOR_ALL_MINION_SLOTS(g, v, l, mob, slot, minion)
  {
    if (! minion) {
      continue;
    }

    if (specific_minion) {
      if (minion != specific_minion) {
        continue;
      }
    }

    if (! minion->mob_id) {
      THING_ERR(mob, "mob found detached minion: %s", thing_short_name(g, v, l, minion).c_str());
      return false;
    }

    if (ext_struct->minions.count <= 0) {
      THING_ERR(mob, "mob has unexpected minion count when detaching: %s", thing_short_name(g, v, l, minion).c_str());
      return false;
    }

    ext_struct->minions.count--;
    memset(slot, 0, sizeof(*slot));
    minion->mob_id = 0;

    if (e.event_type != THING_EVENT_NONE) {
      THING_LOG(mob, "kill minion %s", thing_short_name(g, v, l, minion).c_str());
      thing_dead(g, v, l, minion, e);
    } else {
      THING_LOG(mob, "detach minion %s", thing_short_name(g, v, l, minion).c_str());
    }
  }

  return true;
}

//
// Detach all minions from their mob
//
bool thing_mob_detach_all_minions(Gamep g, Levelsp v, Levelp l, Thingp mob)
{
  TRACE_NO_INDENT();

  ThingEvent e = {};
  return thing_mob_process_minions(g, v, l, mob, nullptr, e);
}

//
// Kill all minions
//
bool thing_mob_kill_all_minions(Gamep g, Levelsp v, Levelp l, Thingp mob, ThingEvent &e)
{
  TRACE_NO_INDENT();

  return thing_mob_process_minions(g, v, l, mob, nullptr, e);
}

//
// Detach a minion from its mob
//
bool thing_mob_detach_minion(Gamep g, Levelsp v, Levelp l, Thingp mob, Thingp minion)
{
  TRACE_NO_INDENT();

  ThingEvent e = {};
  return thing_mob_process_minions(g, v, l, mob, minion, e);
}

//
// Dump all minions
//
void thing_mob_dump_minions(Gamep g, Levelsp v, Levelp l, Thingp mob)
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
