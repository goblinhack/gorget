//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_string.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"
#include "my_wids.hpp"

//
// The player has been attacked
//
static void thing_killed_player(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_AND_INDENT();

  auto it = e.source;

  if (it) {
    auto by_the_thing = thing_the_long_name(g, v, l, it);

    switch (e.event_type) {
      case THING_EVENT_NONE : break;
      case THING_EVENT_SHOVE : // newline
        TOPCON(UI_IMPORTANT_FMT_STR "You are shoved to death by %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_CRUSH : // newline
        TOPCON(UI_IMPORTANT_FMT_STR "You are crushed to death by %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_MELEE : // newline
        TOPCON(UI_IMPORTANT_FMT_STR "You are killed by %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_HEAT : // newline
        TOPCON(UI_IMPORTANT_FMT_STR "You die in the unsuffereble heat from %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_FIRE : // newline
        TOPCON(UI_IMPORTANT_FMT_STR "You are burnt to death by %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_ENUM_MAX : break;
    }
  }
}

//
// The player has attacked
//
static void thing_killed_by_player(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_AND_INDENT();
  auto it = e.source;

  if (it && thing_is_loggable(t)) {
    auto the_thing    = capitalise_first(thing_the_long_name(g, v, l, t));
    auto by_the_thing = thing_the_long_name(g, v, l, it);

    switch (e.event_type) {
      case THING_EVENT_NONE : break;
      case THING_EVENT_SHOVE : // newline
        TOPCON("%s is knocked over by %s.", the_thing.c_str(), by_the_thing.c_str());
        break;
      case THING_EVENT_CRUSH : // newline
        TOPCON("%s is crushed by %s.", the_thing.c_str(), by_the_thing.c_str());
        break;
      case THING_EVENT_MELEE : // newline
        TOPCON("%s is killed by %s.", the_thing.c_str(), by_the_thing.c_str());
        break;
      case THING_EVENT_HEAT : // newline
        TOPCON("%s is killed by heat damage from %s.", the_thing.c_str(), by_the_thing.c_str());
        break;
      case THING_EVENT_FIRE : // newline
        TOPCON("%s is burnt to death by %s.", the_thing.c_str(), by_the_thing.c_str());
        break;
      case THING_EVENT_ENUM_MAX : break;
    }
  }
}

//
// Initiate the death process
//
void thing_dead(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_NO_INDENT();

  if (thing_is_dead(t)) {
    return;
  }

  //
  // Log the reason of demise?
  //
  if (thing_is_loggable(t)) {
    THING_LOG(t, "%s: dead", to_string(e).c_str());
  }

  //
  // Call this prior to setting death, else we are told that we killed an already dead thing
  //
  if (thing_is_player(t)) {
    thing_killed_player(g, v, l, t, e);
  } else if (e.source && thing_is_player(e.source)) {
    thing_killed_by_player(g, v, l, t, e);
  }

  thing_is_dead_set(g, v, l, t);

  if (thing_is_corpse_on_death(t)) {
    //
    // Keep the thing on the map, but in dead state.
    //
    thing_is_corpse_set(g, v, l, t);
  } else {
    //
    // Schedule for removal from the map and freeing
    //
    thing_is_scheduled_for_cleanup_set(g, v, l, t);
  }

  if (thing_is_player(t)) {
    wid_dead_select(g, e.reason);
  }
}

//
// Complete the death process
//
void thing_is_dead_handle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // Update the animation, for example, flattened grass
  //
  t->anim_type = THING_ANIM_DEAD;
  thing_anim_init(g, v, l, t);

  //
  // Stop it moving
  //
  thing_move_finish(g, v, l, t);

  //
  // Restart the animation if we have dead frames
  //
  thing_anim_reset(g, v, l, t);
}
