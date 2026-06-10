//
// Copyright goblinhack@gmail.com
//

#include "my_bpoint.hpp"
#include "my_callstack.hpp"
#include "my_fpoint.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp"
#include "my_line.hpp"
#include "my_main.hpp"
#include "my_spoint.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tile.hpp"
#include "my_types.hpp"

#include <cmath>
#include <ranges>

void thing_is_thrown_set(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp thrower, bool val)
{
  TRACE_DEBUG();

  if (item == nullptr) {
    ERR("no thing pointer");
    return;
  }

  if (item->_is_thrown == static_cast< int >(val)) {
    return;
  }
  item->_is_thrown = val;

  if (val) {
    thing_on_thrown_begin(g, v, l, item, thrower);
  } else {
    thing_on_thrown_end(g, v, l, item, thrower);

    thing_owner_unset(g, v, l, item);
  }
}

void thing_is_thrown_unset(Gamep g, Levelsp v, Levelp l, Thingp item, Thingp thrower)
{
  TRACE_DEBUG();

  if (! item->_is_thrown) {
    return;
  }

  THING_DBG(item, "throw end");

  thing_is_thrown_set(g, v, l, item, thrower, false);
}

//
// If throwing too far, truncate the throw
//
static void thing_throw_truncate(Gamep g, Levelsp v, Levelp l, Thingp thrower, Thingp item, bpoint &to, int how_far_i_can_throw)
{
  //
  // Add some random delta for fun and some for diagonals
  //
  auto curr_at = thing_at(thrower);
  //
  // Need to allow diagonal throws of n tiles
  //
  // x--a-->
  // |    .
  // |   .
  // b  . sqrt((a*a) + (b*b))
  // | .
  // |.
  // v
  const auto how_far_i_want_to_throw = std::floor(distance(curr_at, to));

  THING_DBG(thrower, "curr_at (%d,%d), throw to (%d,%d)", curr_at.x, curr_at.y, to.x, to.y);
  THING_DBG(thrower, "how_far_i_want_to_throw %f, how_far_i_can_throw %d", how_far_i_want_to_throw, how_far_i_can_throw);
  TRACE_INDENT();

  //
  // Check if trying to throw too far.
  //
  if (how_far_i_want_to_throw > how_far_i_can_throw) {
    //
    // Yep. Trying to throw too far.
    //
    THING_DBG(thrower, "trying to throw too far");
    fpoint u = make_fpoint(to) - make_fpoint(curr_at);
    u.unit();
    u *= how_far_i_can_throw;

    fpoint const fto = make_fpoint(curr_at) + u;

    to = make_bpoint(fto);
  }
}

//
// Check if throwing over something we cannot
//
static auto thing_throw_something_in_the_way(Gamep g, Levelsp v, Levelp l, Thingp thrower, bpoint to) -> Thingp
{
  auto at         = thing_at(thrower);
  auto throw_path = draw_line(at, to);

  for (auto intermediate : std::ranges::reverse_view(throw_path)) {
    auto *item = level_is_obs_to_throwing_over(g, v, l, intermediate, thrower);
    if (item != nullptr) {
      return item;
    }
  }
  return nullptr;
}

//
// Handles player and monster throws
//
[[nodiscard]] auto thing_throw_to(Gamep g, Levelsp v, Levelp l, Thingp thrower, Thingp item, bpoint to) -> bool
{
  if (! thrower) {
    ERR("no thing pointer");
    return false;
  }

  if (! item) {
    ERR("no thing pointer to throw");
    return false;
  }

  THING_DBG(thrower, "throw %s to (%d,%d)", thing_name_short(g, v, l, item).c_str(), to.x, to.y);
  TRACE_INDENT();

  if (! thing_is_able_to_throw_items(thrower)) {
    if (thing_is_player(thrower)) {
      topcon("You are unable to throw items.");
    }
    return false;
  }

  if (! thing_is_able_to_be_thrown(item)) {
    auto the_thing = thing_name_long_the(g, v, l, item);
    topcon("You cannot throw the %s.", the_thing.c_str());
    return false;
  }

  if (is_oob_or_border(to)) [[unlikely]] {
    return false;
  }

  auto at = thing_at(thrower);
  if (to == at) {
    return false;
  }

  if (! thing_is_able_to_throw_items(thrower)) {
    return false;
  }

  //
  // If throwing too far, truncate the throw
  //
  auto how_far_i_can_throw = thing_distance_throw(g, v, l, thrower);
  if (how_far_i_can_throw == 0) {
    if (thing_is_player(thrower)) {
      topcon("You are too tired to throw items.");
    }
    return false;
  }

  thing_throw_truncate(g, v, l, thrower, item, to, how_far_i_can_throw);

  auto how_far_i_want_to_throw = static_cast< int >(floor(distance(at, to)));

  THING_DBG(thrower, "throw to (%d,%d) (final, how_far_i_can_throw:%d how_far_i_want_to_throw %d)", to.x, to.y, how_far_i_can_throw,
            how_far_i_want_to_throw);
  TRACE_INDENT();

  //
  // Check if throwing over something we cannot
  //
  auto *obs = thing_throw_something_in_the_way(g, v, l, thrower, to);
  if (obs != nullptr) {
    if (thing_is_player(thrower)) {
      auto the_thing = thing_name_long_the(g, v, l, obs);
      topcon("You cannot throw items over %s.", the_thing.c_str());
    }
    return false;
  }

  bool blocked = {};

  //
  // No throwing into solid obstacles
  //
  if (level_is_obs_to_throwing_onto(g, v, l, to, thrower) != nullptr) {
    blocked = true;
    if (thing_is_player(thrower)) {
      topcon("There is something in the way of throwing there.");
    }

    THING_DBG(thrower, "something in the way of throwing onto");
  }

  if (blocked) {
    //
    // Try again, but with a shorter distance.
    //
    if (how_far_i_want_to_throw > 1) {
      thing_throw_truncate(g, v, l, thrower, item, to, how_far_i_want_to_throw - 1);
      THING_DBG(thrower, "try truncated throw to (%d,%d)", to.x, to.y);

      return thing_throw_to(g, v, l, thrower, item, to);
    }

    return false;
  }

  (void) thing_pop(g, v, item);

  spoint pix_at;
  pix_at.x = at.x * TILE_WIDTH;
  pix_at.y = at.y * TILE_HEIGHT;

  thing_pix_at_set(g, v, l, item, pix_at);
  thing_moving_from_set(item, at);
  thing_at_set(g, v, l, item, to);
  (void) thing_push(g, v, l, item);

  thing_is_thrown_set(g, v, l, item, thrower);

  //
  // Look in the direction of throwing
  //
  auto dx = to.x - at.x;
  auto dy = to.y - at.y;
  thing_set_dir_from_delta(item, dx, dy);

  THING_DBG(item, "throw begin delta %d,%d", dx, dy);

  return true;
}

[[nodiscard]] auto thing_distance_throw_max(Gamep g, Levelsp v, Levelp l, Thingp thrower) -> int
{
  TRACE_DEBUG();

  if (thrower == nullptr) {
    ERR("no thing pointer");
    return 0;
  }

  return thrower->_distance_throw;
}

[[nodiscard]] auto thing_distance_throw(Gamep g, Levelsp v, Levelp l, Thingp thrower) -> int
{
  TRACE_DEBUG();

  if (thrower == nullptr) {
    ERR("no thing pointer");
    return 0;
  }

  auto d = thrower->_distance_throw;

  auto stamina     = thing_stamina(g, v, l, thrower);
  auto stamina_max = thing_stamina_max(g, v, l, thrower);

  if (stamina < stamina_max / 4) {
    d /= 2;
  }

  if (stamina != 0) {
    if (d == 0) {
      d = 1;
    }
  }

  return d;
}

[[nodiscard]] auto thing_distance_throw_set(Gamep g, Levelsp v, Levelp l, Thingp thrower, int val) -> int
{
  TRACE_DEBUG();

  if (thrower == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return thrower->_distance_throw = val;
}

[[nodiscard]] auto thing_distance_throw_incr(Gamep g, Levelsp v, Levelp l, Thingp thrower, int val) -> int
{
  TRACE_DEBUG();

  if (thrower == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return thrower->_distance_throw += val;
}

[[nodiscard]] auto thing_distance_throw_decr(Gamep g, Levelsp v, Levelp l, Thingp thrower, int val) -> int
{
  TRACE_DEBUG();

  if (thrower == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(thrower->_distance_throw) - val <= 0) {
    return thrower->_distance_throw = 0;
  }
  return thrower->_distance_throw -= val;
}
