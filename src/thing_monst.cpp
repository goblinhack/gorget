//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_cpp_template.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_line.hpp"
#include "my_main.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_wid_warning.hpp"

//
// Return true on a successful move (or a popup asking more info)
//
[[nodiscard]] static bool thing_monst_move_try(Gamep g, Levelsp v, Levelp l, Thingp t, spoint to, bool need_path)
{
  THING_DBG(t, "move try");

  TRACE_AND_INDENT();

  if (thing_can_move_to_attempt(g, v, l, t, to)) {
    return true;
  }

  if (thing_can_move_to_attempt_by_shoving(g, v, l, t, to)) {
    //
    // Can we shove it out of the way to move?
    //
    THING_DBG(t, "move try: can move to by shoving");

    if (thing_shove_to(g, v, l, t, to)) {
      //
      // Do not step onto the thing we just shoved.
      //
      if (level_is_dead_on_shoving(g, v, l, to)) {
        return false;
      } else {
        return true;
      }
    }
  }

  if (thing_can_move_to_attempt_by_opening(g, v, l, t, to)) {
    //
    // Can we open it allow movement?
    //
    THING_DBG(t, "move try: can move to by opening");

    if (thing_move_to(g, v, l, t, to)) {
      return true;
    }
  }

  //
  // Bumped into obstacle
  //
  return false;
}

//
// Move to the next path on the popped path if it exits.
//
[[nodiscard]] static bool thing_monst_move_to_next(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  THING_DBG(t, "move to next");

  //
  // If already moving, do not pop the next path tile
  //
  if (thing_is_moving(t)) {
    THING_DBG(t, "move to next: already moving");
    return false;
  }

  //
  // Get the next tile to move to
  //
  spoint move_next = {};
  if (! thing_move_path_pop(g, v, l, t, move_next)) {
    //
    // If could not pop, then no path is left
    //
    THING_DBG(t, "move to next: no move path to pop");
    return false;
  }

  spoint move_destination = {};
  if (thing_move_path_target(g, v, l, t, move_destination)) {
    if (level_is_cursor_path_hazard(g, v, l, move_next)) {
      if (thing_jump_to(g, v, l, t, move_destination)) {
        //
        // If could jump, then abort the path walk
        //
        THING_DBG(t, "move to next: jump");
        return false;
      }

      //
      // Something was in the way of jumping. Best to stop rather than accidentally
      // walk into a chasm.
      //
      THING_DBG(t, "move to next: something in the way");
      return false;
    }
  }

  if (! thing_monst_move_try(g, v, l, t, move_next, false)) {
    //
    // If could not move, then abort the path walk
    //
    THING_DBG(t, "move to next: could not move");
    return false;
  }

  return thing_move_to(g, v, l, t, move_next);
}

[[nodiscard]] static bool thing_monst_choose_target(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (thing_is_minion(t)) {
    spoint target;
    if (thing_minion_choose_target_near_mob(g, v, l, t, target)) {
      THING_DBG(t, "minion chose target");
      return true;
    }

    THING_DBG(t, "minion has no target");
    return false;
  }

  THING_DBG(t, "monst has no target");
  return false;
}

//
// Called per tick
//
void thing_monst_event_loop(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // Early state check
  //
  switch (monst_state(g, v, l, t)) {
    case MONST_STATE_INIT : // newline
      monst_state_change(g, v, l, t, MONST_STATE_NORMAL);
      [[fallthrough]];
    case MONST_STATE_NORMAL : // newline
      monst_state_change(g, v, l, t, MONST_STATE_PATH_REQUESTED);
      if (thing_monst_choose_target(g, v, l, t)) {
        monst_state_change(g, v, l, t, MONST_STATE_FOLLOWING_PATH);
      } else {
        monst_state_change(g, v, l, t, MONST_STATE_NORMAL);
      }
      break;
    case MONST_STATE_DEAD :
      // newline
      break;
    case MONST_STATE_PATH_REQUESTED :
      // newline
      break;
    case MONST_STATE_FOLLOWING_PATH :
      // newline
      break;
    case MONST_STATE_ENUM_MAX : break;
  }

  //
  // Post thinking state check
  //
  switch (monst_state(g, v, l, t)) {
    case MONST_STATE_INIT : // newline
      break;
    case MONST_STATE_NORMAL : // newline
      break;
    case MONST_STATE_DEAD :
      // newline
      break;
    case MONST_STATE_PATH_REQUESTED :
      // newline
      break;
    case MONST_STATE_FOLLOWING_PATH :
      if (! thing_monst_move_to_next(g, v, l, t)) {
        THING_DBG(t, "end of move");
        monst_state_change(g, v, l, t, MONST_STATE_NORMAL);
      }
      break;
    case MONST_STATE_ENUM_MAX : break;
  }
}

std::string monst_state_to_string(MonstState state)
{
  TRACE_NO_INDENT();
  return MonstState_to_string(state);
}

MonstState monst_state(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  return t->_monst_state;
}

void monst_state_change(Gamep g, Levelsp v, Levelp l, Thingp t, MonstState new_state)
{
  TRACE_NO_INDENT();

  auto old_state = t->_monst_state;

  switch (old_state) {
    case MONST_STATE_INIT :
      // newline
      break;
    case MONST_STATE_DEAD :
      // newline
      return;
    case MONST_STATE_NORMAL :
      // newline
      break;
    case MONST_STATE_PATH_REQUESTED :
      // newline
      break;
    case MONST_STATE_FOLLOWING_PATH :
      // newline
      break;
    case MONST_STATE_ENUM_MAX : break;
  }

  if (t->_monst_state == new_state) {
    return;
  }

  //
  // Set here to stop recursion.
  //
  t->_monst_state = new_state;

  //
  // Why oh why change state
  //
  IF_DEBUG
  {
    THING_DBG(t, "state change: %s -> %s", monst_state_to_string(old_state).c_str(),
              monst_state_to_string(new_state).c_str());
  }

  switch (new_state) {
    case MONST_STATE_INIT :
      // newline
      break;
    case MONST_STATE_DEAD :
      // newline
      break;
    case MONST_STATE_NORMAL :
      // newline
      break;
    case MONST_STATE_PATH_REQUESTED :
      // newline
      break;
    case MONST_STATE_FOLLOWING_PATH :
      // newline
      break;
    case MONST_STATE_ENUM_MAX : break;
  }

  (void) thing_move_remaining_set(g, v, l, t, 0);
}

//
// Called at the beginning of each tick and whenever the move_remaining
// count exceeds the players speed and there is still some level tick to go.
//
void thing_monst_tick(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (thing_is_dead(t)) {
    return;
  }

  if (! thing_is_monst(t)) {
    return;
  }

  if (! level_is_player_level(g, v, l)) {
    return;
  }

  auto player = thing_player(g);
  if (! player) {
    return;
  }

  const int player_speed = thing_speed(player);

  if (0) {
    THING_LOG(t, "move_rem %d dt %f", thing_move_remaining(t), t->thing_dt);
  }

  //
  // Give the thing more ability to move
  //
  auto m = thing_move_remaining_incr(g, v, l, t, thing_speed(t));
  if (m >= player_speed) {
    (void) thing_move_remaining_decr(g, v, l, t, player_speed);

    thing_monst_event_loop(g, v, l, t);
  }
}
