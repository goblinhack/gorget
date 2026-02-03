//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_line.hpp"
#include "my_main.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_wid_warning.hpp"

//
// Called per tick
//
void thing_monst_event_loop(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  switch (monst_state(g, v, l, t)) {
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

void monst_state_change(Gamep g, Levelsp v, Thingp t, MonstState new_state)
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
  THING_LOG(t, "state change: %s -> %s", monst_state_to_string(old_state).c_str(),
            monst_state_to_string(new_state).c_str());

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
}
