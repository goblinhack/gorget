//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_thing_callbacks.hpp"
#include "my_ui.hpp"

//
// The player has been attacked
//
static void thing_shoved_player(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_AND_INDENT();

  auto it = e.source;

  if (it) {
    auto by_the_thing = thing_the_long_name(g, v, l, it);

    TOPCON(UI_WARNING_FMT_STR "You are shoved by %s." UI_RESET_FMT, by_the_thing.c_str());
  }
}

//
// The player has attacked
//
static void thing_shoved_by_player(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_AND_INDENT();
  auto it = e.source;

  if (it && thing_is_loggable(t)) {
    auto the_thing = capitalize_first(thing_the_long_name(g, v, l, t));
    auto by_player = thing_long_name(g, v, l, it);

    TOPCON("%s is shoved by %s.", the_thing.c_str(), by_player.c_str());
  }
}

//
// Handle interactions for a thing at its location with a dead thing
//
static bool thing_shove_handle_dead_thing(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp shover, spoint from,
                                          spoint to, spoint direction)
{
  TRACE_NO_INDENT();

  bool shoved = false;

  ThingEvent e {
      .reason     = "by shoving",       //
      .event_type = THING_EVENT_SHOVED, //
      .source     = shover              //
  };

  if (thing_can_move_to(g, v, l, t, to)) {
    if (thing_move_to(g, v, l, t, to)) {
      shoved = true;
    }
  }

  if (shoved) {
    //
    // Callback for shoving
    //
    thing_on_shoved(g, v, l, t, shover);

    if (thing_is_player(t)) {
      thing_shoved_player(g, v, l, t, e);
    } else if (e.source && thing_is_player(e.source)) {
      thing_shoved_by_player(g, v, l, t, e);
    }

    THING_DBG(shover, "shove success of %s", to_string(g, t).c_str());
  } else {
    THING_DBG(shover, "shove fail of %s", to_string(g, t).c_str());
  }

  return shoved;
}

//
// Handle interactions for a thing at its location with an alive thing
//
static bool thing_shove_handle_alive_thing(Gamep g, Levelsp v, Levelp l, Thingp t, Thingp shover, spoint from,
                                           spoint to, spoint direction)
{
  TRACE_NO_INDENT();

  bool shoved = false;

  ThingEvent e {
      .reason     = "by shoving",       //
      .event_type = THING_EVENT_SHOVED, //
      .source     = shover              //
  };

  //
  // Some items, like braziers need to be knocked over first before shoving.
  //
  if (thing_is_dead_on_shoving(t)) {
    thing_on_shoved(g, v, l, t, shover);
    thing_dead(g, v, l, t, e);
    return true;
  }

  if (thing_can_move_to(g, v, l, t, to)) {
    if (thing_move_to(g, v, l, t, to)) {
      shoved = true;
    }
  }

  if (shoved) {
    //
    // Callback for shoving
    //
    thing_on_shoved(g, v, l, t, shover);

    if (thing_is_player(t)) {
      thing_shoved_player(g, v, l, t, e);
    } else if (e.source && thing_is_player(e.source)) {
      thing_shoved_by_player(g, v, l, t, e);
    }
  }

  return shoved;
}

//
// Can we shove something at the location "at"
//
// Returns true on success at shoving something
//
bool thing_shove_handle(Gamep g, Levelsp v, Levelp l, Thingp shover, spoint at)
{
  TRACE_NO_INDENT();

  bool   ret       = false;
  auto   direction = at - shover->at;
  spoint from      = at;
  spoint to        = at + direction;

  if (thing_is_ethereal(shover)) {
    return false;
  }

  if (! thing_is_able_to_shove(shover)) {
    return false;
  }

  //
  // Common shove handling for player and anything else
  //
  FOR_ALL_THINGS_AT(g, v, l, it, at)
  {
    if (! thing_is_shovable(it)) {
      continue;
    }

    if (thing_is_dead(it)) {
      //
      // Dead things
      //
      if (thing_shove_handle_dead_thing(g, v, l, it, shover, from, to, direction)) {
        ret = true;
      }
    } else {
      //
      // Alive things
      //
      if (thing_shove_handle_alive_thing(g, v, l, it, shover, from, to, direction)) {
        ret = true;
      }
    }
  }

  return ret;
}
