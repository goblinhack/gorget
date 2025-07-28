//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
// REMOVED #include "my_main.hpp"
// REMOVED #include "my_random.hpp"
#include "my_string.hpp"
// REMOVED #include "my_tile.hpp"
// REMOVED #include "my_tp.hpp"
#include "my_tp_callbacks.hpp"
// REMOVED #include "my_types.hpp"
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
      case THING_EVENT_LIFESPAN : //
      case THING_EVENT_SHOVE :    //
        TOPCON(UI_IMPORTANT_FMT_STR "You are shoved to death by %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_CRUSH : //
        TOPCON(UI_IMPORTANT_FMT_STR "You are crushed to death by %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_MELEE_DAMAGE : //
        TOPCON(UI_IMPORTANT_FMT_STR "You are killed by %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_HEAT_DAMAGE : //
        TOPCON(UI_IMPORTANT_FMT_STR "You die in the unsuffereble heat from %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_WATER_DAMAGE : //
        TOPCON(UI_IMPORTANT_FMT_STR "You die in the undrinkable depths from %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_FIRE_DAMAGE : //
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
    auto the_thing = capitalise_first(thing_the_long_name(g, v, l, t));
    auto by_player = thing_long_name(g, v, l, it);

    switch (e.event_type) {
      case THING_EVENT_NONE : break;
      case THING_EVENT_LIFESPAN : //
      case THING_EVENT_SHOVE :    //
        TOPCON("%s is knocked over by %s.", the_thing.c_str(), by_player.c_str());
        break;
      case THING_EVENT_CRUSH : //
        TOPCON("%s is crushed by %s.", the_thing.c_str(), by_player.c_str());
        break;
      case THING_EVENT_MELEE_DAMAGE : //
        TOPCON("%s is killed by %s.", the_thing.c_str(), by_player.c_str());
        break;
      case THING_EVENT_HEAT_DAMAGE : //
        TOPCON("%s is killed by heat damage from %s.", the_thing.c_str(), by_player.c_str());
        break;
      case THING_EVENT_WATER_DAMAGE : //
        TOPCON("%s is killed by water damage from %s.", the_thing.c_str(), by_player.c_str());
        break;
      case THING_EVENT_FIRE_DAMAGE : //
        TOPCON("%s is burnt to death by %s.", the_thing.c_str(), by_player.c_str());
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
    THING_LOG(t, "%s: dead", to_string(g, e).c_str());
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
    auto death_reason = to_death_reason(g, e);

    auto score = 666;
    if (game_is_new_hiscore(g, score)) {
      TOPCON(UI_GOOD_FMT_STR "New high score, %s place!" UI_RESET_FMT, game_place_str(g, score));
      game_add_new_hiscore(g, score, l->level_num, game_player_name_get(g), death_reason.c_str());
    }

    wid_dead_select(g, death_reason);
  }

  //
  // Per thing callback
  //
  tp_on_death(g, v, l, t, top_owner(g, v, l, t), t->at, e);
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
  if (thing_is_burnt(t) && tp_tiles_size(thing_tp(t), THING_ANIM_BURNT)) {
    //
    // If it has burnt anim frames
    //
    t->anim_type = THING_ANIM_BURNT;
  } else if (tp_tiles_size(thing_tp(t), THING_ANIM_DEAD)) {
    //
    // If it has dead anim frames
    //
    t->anim_type = THING_ANIM_DEAD;
  }

  //
  // No more following the cursor if dead...
  //
  if (thing_is_player(t)) {
    level_cursor_path_reset(g, v, l);
  }

  //
  // Stop it moving
  //
  thing_move_finish(g, v, l, t);

  //
  // Restart the animation if we have dead frames
  //
  thing_anim_init(g, v, l, t);

  //
  // Do adjacent tiles need updating due to the destruction of this tiled thing?
  //
  if (thing_is_tiled(t)) {
    level_tile_update_set(g, v, l, t->at);
  }
}
