//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"

#include <cmath>

//
// Is this projectile attached to a thing?
//
auto thing_fired_by_get(Gamep g, Levelsp v, Levelp l, Thingp me) -> Thingp
{
  if (me == nullptr) {
    return nullptr;
  }

  if (me->fired_by_id == 0U) {
    return nullptr;
  }

  return thing_find(g, v, me->fired_by_id);
}

//
// How many projectils?
//
auto thing_fired_by_count_get(Gamep g, Levelsp v, Levelp l, Thingp me) -> int
{
  if (me == nullptr) {
    return 0;
  }

  if (! thing_is_able_to_fire_weapons(me)) {
    return 0;
  }

  auto *ext_struct = thing_ext_struct(g, me);
  if (ext_struct == nullptr) {
    return 0;
  }

  return ext_struct->weapons.count;
}

//
// Detach or kill all projectiles (or a specific one)
//
[[nodiscard]] static auto thing_weapon_process_all(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp specific_projectile, ThingEvent &e)
    -> bool
{
  TRACE();

  if (me == nullptr) {
    return false;
  }

  if (! thing_is_able_to_fire_weapons(me)) {
    thing_err(me, "non owner trying to detach projectiles");
    return false;
  }

  auto *ext_struct = thing_ext_struct(g, me);
  if (ext_struct == nullptr) {
    return false;
  }

  bool got_one = false;

  FOR_ALL_WEAPON_SLOTS(g, v, l, me, slot, projectile)
  {
    if (projectile == nullptr) {
      continue;
    }

    if (specific_projectile != nullptr) {
      if (projectile != specific_projectile) {
        continue;
      }
    }

    if (! static_cast< bool >(projectile->fired_by_id)) {
      thing_err(me, "found detached projectile: %s", to_string(g, v, l, projectile).c_str());
      return false;
    }

    if (ext_struct->weapons.count <= 0) {
      thing_err(me, "has unexpected projectile count when detaching: %s", to_string(g, v, l, projectile).c_str());
      return false;
    }

    ext_struct->weapons.count--;
    memset(slot, 0, sizeof(*slot));
    projectile->fired_by_id = 0;

    if (e.event_type != THING_EVENT_NONE) {
      THING_DBG(me, "kill projectile %s", to_string(g, v, l, projectile).c_str());
      TRACE_INDENT();
      thing_dead(g, v, l, projectile, e);
      got_one = true;
    } else {
      THING_DBG(me, "detach projectile %s", to_string(g, v, l, projectile).c_str());
      got_one = true;
    }
  }

  if (! got_one) {
    THING_DBG(me, "could not detach");
  }

  return got_one;
}

//
// Detach all projectiles from their owner
//
auto thing_weapon_detach_all_fired(Gamep g, Levelsp v, Levelp l, Thingp me) -> bool
{
  TRACE();

  ThingEvent e = {};
  return thing_weapon_process_all(g, v, l, me, nullptr, e);
}

//
// Kill all projectiles
//
auto thing_weapon_kill_all_fired(Gamep g, Levelsp v, Levelp l, Thingp me, ThingEvent &e) -> bool
{
  TRACE();

  return thing_weapon_process_all(g, v, l, me, nullptr, e);
}

//
// Detach a projectile from its owner
//
static auto thing_weapon_detach_from_firer(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp projectile) -> bool
{
  TRACE();

  ThingEvent e = {};
  return thing_weapon_process_all(g, v, l, me, projectile, e);
}

//
// Detach a projectile from its firer
//
auto thing_weapon_detach_me_from_firer(Gamep g, Levelsp v, Levelp l, Thingp me) -> bool
{
  TRACE();

  if (me == nullptr) {
    return false;
  }

  if (! thing_is_projectile(me)) {
    thing_err(me, "non projectile trying to detach itself");
    return false;
  }

  auto *fired_by = thing_fired_by_get(g, v, l, me);
  if (fired_by == nullptr) {
    return false; // can be normal if detached
  }

  THING_DBG(me, "detach me from firer");
  TRACE_INDENT();

  return thing_weapon_detach_from_firer(g, v, l, fired_by, me);
}

//
// Dump all projectiles
//
void thing_dump_weapons(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE();

  if (me == nullptr) {
    return;
  }

  if (! thing_is_able_to_fire_weapons(me)) {
    thing_err(me, "non owner trying to detach projectile");
    return;
  }

  auto *ext_struct = thing_ext_struct(g, me);
  if (ext_struct == nullptr) {
    return;
  }

  FOR_ALL_WEAPON_SLOTS(g, v, l, me, slot, existing_projectile)
  {
    if (existing_projectile == nullptr) {
      THING_DBG(me, "slot %d: -", _n_);
      continue;
    }

    auto s = to_string(g, v, l, existing_projectile);
    THING_DBG(me, "slot %d: %s", _n_, s.c_str());
  }
}
