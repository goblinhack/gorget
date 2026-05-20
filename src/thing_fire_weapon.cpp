//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_thing_inlines.hpp"

void thing_on_fire_weapon_request_set(Tpp tp, thing_on_fire_weapon_request_t callback)
{
  TRACE();
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return;
  }
  tp->on_fire_weapon_request = callback;
}

auto thing_on_fire_weapon_request(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp user) -> Tpp
{
  TRACE();
  auto *tp = thing_tp(me);
  if (tp == nullptr) [[unlikely]] {
    ERR("no thing template pointer");
    return nullptr;
  }
  if (tp->on_fire_weapon_request == nullptr) {
    //
    // Assume success
    //
    return nullptr;
  }
  if (! thing_is_player(user) && ! thing_is_monst(user)) {
    thing_err(user, "unexpected thing for %s", __FUNCTION__);
    return nullptr;
  }
  return tp->on_fire_weapon_request(g, v, l, me, user);
}
