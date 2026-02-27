//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level_inlines.hpp"
#include "my_line.hpp"
#include "my_main.hpp"
#include "my_thing_inlines.hpp"

#include <ranges>

//
// If jumping too far, truncate the jump
//
static void thing_jump_truncate(Gamep g, Levelsp v, Levelp l, Thingp t, spoint &to)
{
  //
  // Add some random delta for fun and some for diagonals
  //
  auto        curr_at                = thing_at(t);
  float       how_far_i_can_jump     = thing_distance_jump(t);
  float const how_far_i_want_to_jump = distance(curr_at, to);

  //
  // Cannot jump in lava for example
  //
  if (level_is_obs_to_jumping_out_of(g, v, l, curr_at) != nullptr) {
    how_far_i_can_jump = 1;
  }

  //
  // Check if trying to jump too far.
  //
  if (how_far_i_want_to_jump > how_far_i_can_jump) {
    //
    // Yep. Trying to jump too far.
    //
    fpoint u = make_fpoint(to) - make_fpoint(curr_at);
    u.unit();
    u *= how_far_i_can_jump;

    fpoint const fto = make_fpoint(curr_at) + u;

    to = make_spoint(fto);
  }
}

//
// Check if jumping over something we cannot
//
static auto thing_jump_something_in_the_way(Gamep g, Levelsp v, Levelp l, Thingp t, spoint to) -> Thingp
{
  auto at        = thing_at(t);
  auto jump_path = draw_line(at, to);

  for (auto intermediate : std::ranges::reverse_view(jump_path)) {
    auto *what = level_is_obs_to_jump_over(g, v, l, intermediate);
    if (what != nullptr) {
      return what;
    }
  }
  return nullptr;
}

//
// Handles player and monster jumps
//
auto thing_jump_to(Gamep g, Levelsp v, Levelp l, Thingp t, spoint to, bool warn) -> bool
{
  TRACE();

  if (is_oob(to)) [[unlikely]] {
    return false;
  }

  auto at = thing_at(t);
  if (to == at) {
    return false;
  }

  if (! thing_is_able_to_jump(t)) {
    return false;
  }

  //
  // If jumping too far, truncate the jump
  //
  thing_jump_truncate(g, v, l, t, to);

  THING_DBG(t, "jump to %d,%d", to.x, to.y);

  //
  // Check if jumping over something we cannot
  //
  auto *obs = thing_jump_something_in_the_way(g, v, l, t, to);
  if (obs != nullptr) {
    if (thing_is_player(t)) {
      if (warn) {
        auto the_thing = thing_the_long_name(g, v, l, obs);
        TOPCON("You cannot jump over %s.", the_thing.c_str());
      }
    }
    return false;
  }

  //
  // No landing in solid obstacles
  //
  if (level_is_obs_to_jumping_onto(g, v, l, to) != nullptr) {
    if (thing_is_player(t)) {
      if (warn) {
        TOPCON("There is something in the way of jumping there.");
      }
    }
    return false;
  }

  (void) thing_pop(g, v, t);

  spoint pix_at;
  pix_at.x = at.x * TILE_WIDTH;
  pix_at.y = at.y * TILE_HEIGHT;

  thing_pix_at_set(g, v, l, t, pix_at);
  thing_moving_from_set(t, at);
  thing_at_set(g, v, l, t, to);
  (void) thing_push(g, v, l, t);

  thing_is_jumping_set(g, v, l, t);

  return true;
}
