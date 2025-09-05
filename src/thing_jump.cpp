//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_fpoint.hpp"
#include "my_game_popups.hpp"
#include "my_level.hpp"
#include "my_line.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_sound.hpp"
#include "my_tile.hpp"
#include "my_tp_callbacks.hpp"

//
// If jumping too far, truncate the jump
//
static void thing_jump_truncate(Gamep g, Levelsp v, Levelp l, Thingp t, spoint &to)
{
  //
  // Add some random delta for fun and some for diagonals
  //
  auto  curr_at = t->at;
  float d       = thing_jump_distance(t);
  float dist    = distance(curr_at, to);

  //
  // Check if trying to jump too far.
  //
  if (dist > d) {
    //
    // Yep. Trying to jump too far.
    //
    fpoint u = make_fpoint(to) - make_fpoint(curr_at);
    u.unit();
    u *= d;

    fpoint fto = make_fpoint(curr_at) + u;

    to = make_spoint(fto);
  }
}

//
// Check if jumping over something we cannot
//
static bool thing_jump_something_in_the_way(Gamep g, Levelsp v, Levelp l, Thingp t, spoint to)
{
  auto jump_path = draw_line(t->at, to);

  for (auto i = jump_path.rbegin(); i != jump_path.rend(); i++) {
    spoint intermediate = *i;
    if (level_is_obs_to_jump_over(g, v, l, intermediate)) {
      return true;
    }
  }
  return false;
}

//
// Handles player and monster jumps
//
bool thing_jump_to(Gamep g, Levelsp v, Levelp l, Thingp t, spoint to, bool warn)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  if (to == t->at) {
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
  if (thing_jump_something_in_the_way(g, v, l, t, to)) {
    if (thing_is_player(t)) {
      if (warn) {
        TOPCON("You cannot jump over that.");
      }
    }
    return false;
  }

  //
  // No landing in solid obstacles
  //
  if (level_is_obs_to_jump_landing(g, v, l, to)) {
    if (thing_is_player(t)) {
      if (warn) {
        TOPCON("There is something in the way of jumping there.");
      }
    }
    return false;
  }

  thing_pop(g, v, t);

  t->pix_at.x = t->at.x * INNER_TILE_WIDTH;
  t->pix_at.y = t->at.y * INNER_TILE_HEIGHT;

  t->old_at      = t->at;
  t->moving_from = t->at;
  t->at          = to;

  thing_push(g, v, l, t);

  thing_is_jumping_set(g, v, l, t);

  return true;
}
