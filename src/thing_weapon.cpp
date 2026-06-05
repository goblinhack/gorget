//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_fpoint.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_thing.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

#include <cstring>

[[nodiscard]] auto thing_weapon_get_delta_from_dt(Gamep g, Thingp t, float dt) -> fpoint
{
  TRACE();

  float s = 0;
  float c = 0;
  SINCOSF(t->angle, &s, &c);

  auto *player = thing_player(g);
  if (player == nullptr) [[unlikely]] {
    CROAK("no player struct found");
    return fpoint(0, 0);
  }

  const int   player_speed = thing_speed(player);
  const float t_speed      = thing_speed(t);
  const auto  tile_speed   = (t_speed / static_cast< float >(player_speed));

  auto delta = fpoint(c * dt * tile_speed, s * dt * tile_speed);
  if ((delta.x == 0) && (delta.y == 0)) {
    CROAK("no delta for weapon sin %f cos %f dt %f tile_speed %f", s, c, dt, tile_speed);
  }

  return delta;
}

[[nodiscard]] auto thing_weapon_get_direction(Gamep g, Levelsp /*v*/, Levelp /*l*/, Thingp t) -> fpoint
{
  TRACE();

  return unit(thing_weapon_get_delta_from_dt(g, t, 1.0));
}

//
// Add a weapon if possible
//
[[nodiscard]] auto thing_spawn_weapon(Gamep g, Levelsp v, Levelp l, Thingp me, Tpp what, const fpoint target) -> Thingp
{
  TRACE();

  if (me == nullptr) {
    return nullptr;
  }

  if (! thing_is_able_to_fire_weapons(me)) {
    thing_err(me, "thing trying to spawn projectiles when it cannot");
    return nullptr;
  }

  if (what == nullptr) {
    thing_err(me, "no weapon to spawn");
    return nullptr;
  }

  auto *ext_struct = thing_ext_struct(g, me);
  if (ext_struct == nullptr) {
    thing_err(me, "missing ext struct");
    return nullptr;
  }

  //
  // Too many projectiles
  //
  if (thing_fired_by_count_get(g, v, l, me) >= thing_fired_weapon_count_max(g, v, l, me)) {
    THING_DBG(me, "trying to fire too many weapons");
    thing_dump_weapons(g, v, l, me);

    if (thing_is_player(me)) {
      topcon("Trying to fire too many weapons!");
    }

    return nullptr;
  }

  //
  // Look for a free slot
  //
  FOR_ALL_WEAPON_SLOTS(g, v, l, me, slot, existing_projectile)
  {
    if (existing_projectile != nullptr) {
      continue;
    }

    //
    // Create the weapon. Should be no chance to fail now.
    //
    auto *new_projectile = thing_spawn(g, v, l, what, target);
    if (new_projectile == nullptr) {
      return nullptr;
    }

    memset(slot, 0, sizeof(*slot));
    slot->weapon_id             = new_projectile->id;
    new_projectile->fired_by_id = me->id;
    ext_struct->weapons.count++;

    THING_DBG(me, "spawned weapon %s", to_string(g, v, l, new_projectile).c_str());
    THING_DBG(new_projectile, "new born weapon");

    return new_projectile;
  }

  //
  // Out of slots; but we checked above
  //
  thing_err(me, "unexpectedly out of weapon slots");

  return nullptr;
}

//
// Is this weapon attached to a thing?
//
[[nodiscard]] auto thing_fired_by_get(Gamep g, Levelsp v, Levelp /*l*/, Thingp me) -> Thingp
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
[[nodiscard]] auto thing_fired_by_count_get(Gamep g, Levelsp /*v*/, Levelp /*l*/, Thingp me) -> int
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

  FOR_ALL_WEAPON_SLOTS(g, v, l, me, slot, weapon)
  {
    if (weapon == nullptr) {
      continue;
    }

    if (specific_projectile != nullptr) {
      if (weapon != specific_projectile) {
        continue;
      }
    }

    if (! static_cast< bool >(weapon->fired_by_id)) {
      thing_err(me, "found detached weapon: %s", to_string(g, v, l, weapon).c_str());
      return false;
    }

    if (ext_struct->weapons.count <= 0) {
      thing_err(me, "has unexpected weapon count when detaching: %s", to_string(g, v, l, weapon).c_str());
      return false;
    }

    ext_struct->weapons.count--;
    memset(slot, 0, sizeof(*slot));
    weapon->fired_by_id = 0;

    if (e.event_type != THING_EVENT_NONE) {
      THING_DBG(me, "kill weapon %s", to_string(g, v, l, weapon).c_str());
      TRACE_INDENT();
      thing_dead(g, v, l, weapon, e);
      got_one = true;
    } else {
      THING_DBG(me, "detach weapon %s", to_string(g, v, l, weapon).c_str());
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
[[nodiscard]] auto thing_weapon_detach_all_fired(Gamep g, Levelsp v, Levelp l, Thingp me) -> bool
{
  TRACE();

  ThingEvent e = {};
  return thing_weapon_process_all(g, v, l, me, nullptr, e);
}

//
// Kill all projectiles
//
[[nodiscard]] auto thing_weapon_kill_all_fired(Gamep g, Levelsp v, Levelp l, Thingp me, ThingEvent &e) -> bool
{
  TRACE();

  return thing_weapon_process_all(g, v, l, me, nullptr, e);
}

//
// Detach a weapon from its owner
//
static auto thing_weapon_detach_from_firer(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp weapon) -> bool
{
  TRACE();

  ThingEvent e = {};
  return thing_weapon_process_all(g, v, l, me, weapon, e);
}

//
// Detach a weapon from its firer
//
[[nodiscard]] auto thing_weapon_detach_me_from_firer(Gamep g, Levelsp v, Levelp l, Thingp me) -> bool
{
  TRACE();

  if (me == nullptr) {
    return false;
  }

  if (! thing_is_projectile(me) && ! thing_is_laser(me)) {
    thing_err(me, "non weapon trying to detach itself");
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
    thing_err(me, "non owner trying to detach weapon");
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
