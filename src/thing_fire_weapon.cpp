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

void thing_on_use_weapon_request_set(Tpp tp, thing_on_use_weapon_request_t callback)
{
  TRACE();
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return;
  }
  tp->on_use_weapon_request = callback;
}

auto thing_on_use_weapon_request(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp user) -> Tpp
{
  TRACE();
  auto *tp = thing_tp(me);
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return nullptr;
  }
  if (tp->on_use_weapon_request == nullptr) {
    //
    // Assume success
    //
    return nullptr;
  }
  if (! thing_is_player(user) && ! thing_is_monst(user)) {
    thing_err(user, "unexpected thing for %s", __FUNCTION__);
    return nullptr;
  }
  return tp->on_use_weapon_request(g, v, l, me, user);
}

auto thing_fire_at(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp item, Tpp fire_what, const bpoint &target) -> bool
{
  TRACE();

  //
  // Decrement charge count if we have a thing
  //
  if (item != nullptr) {
    if (thing_charge_count_decr(g, v, l, item) <= 0) {
      if (thing_is_dead_when_discharged(item)) {
        ThingEvent e {
            .reason     = "by discharging",             //
            .event_type = THING_EVENT_LIFESPAN_EXPIRED, //
        };

        if (thing_is_player(me)) {
          auto the_thing = thing_name_long_The(g, v, l, item);
          topcon("%s disintegrates.", the_thing.c_str());
        }

        thing_dead(g, v, l, item, e);
      }
      return false;
    }
  }

  //
  // Fire away!
  //
  if (tp_is_laser(fire_what)) {
    if (! thing_laser_fire_at(g, v, l, me, fire_what, target)) {
      return false;
    }
  } else {
    if (! thing_projectile_fire_at(g, v, l, me, fire_what, target)) {
      return false;
    }
  }

  return true;
}
