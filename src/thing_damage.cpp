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

//
// The player has been attacked
//
static void thing_damage_to_player(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_AND_INDENT();

  auto it = e.source;

  if (it) {
    auto by_the_thing = thing_the_long_name(g, v, l, it);

    switch (e.event_type) {
      case THING_EVENT_NONE :     break;
      case THING_EVENT_LIFESPAN : break;
      case THING_EVENT_SHOVE : //
        TOPCON(UI_WARNING_FMT_STR "You are shoved by %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_CRUSH : //
        TOPCON(UI_WARNING_FMT_STR "You are crushed by %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_MELEE : //
        TOPCON(UI_WARNING_FMT_STR "You are hit by %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_HEAT : //
        TOPCON(UI_WARNING_FMT_STR "You suffer heat damage from %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_FIRE : //
        TOPCON(UI_WARNING_FMT_STR "You are burnt by %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_ENUM_MAX : break;
    }
  }
}

//
// The player has attacked
//
static void thing_damage_by_player(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_AND_INDENT();
  auto it = e.source;

  if (it && thing_is_loggable(t)) {
    auto the_thing    = capitalise_first(thing_the_long_name(g, v, l, t));
    auto by_the_thing = thing_the_long_name(g, v, l, it);

    switch (e.event_type) {
      case THING_EVENT_NONE :     break;
      case THING_EVENT_LIFESPAN : break;
      case THING_EVENT_SHOVE : //
        TOPCON("%s is shoved by %s.", the_thing.c_str(), by_the_thing.c_str());
        break;
      case THING_EVENT_CRUSH : //
        TOPCON("%s is crushed by %s.", the_thing.c_str(), by_the_thing.c_str());
        break;
      case THING_EVENT_MELEE : //
        TOPCON("%s is hit by %s.", the_thing.c_str(), by_the_thing.c_str());
        break;
      case THING_EVENT_HEAT : //
        TOPCON("%s suffers heat damage from %s.", the_thing.c_str(), by_the_thing.c_str());
        break;
      case THING_EVENT_FIRE : //
        TOPCON("%s is burnt by %s.", the_thing.c_str(), by_the_thing.c_str());
        break;
      case THING_EVENT_ENUM_MAX : break;
    }
  }
}

//
// Apply a damage type to a thing
//
void thing_damage(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_AND_INDENT();

  if (thing_is_dead(t)) {
    //
    // Log the reason for attack?
    //
    if (thing_is_loggable(t)) {
      THING_LOG(t, "%s: no damage as already dead", to_string(e).c_str());
    }
    return;
  }

  //
  // Immune to this attack?
  //
  if (thing_is_immune_to(t, e.event_type)) {
    if (thing_is_loggable(t)) {
      THING_LOG(t, "%s: no damage as immune", to_string(e).c_str());
    }
    return;
  }

  //
  // Log the reason for attack?
  //
  if (thing_is_loggable(t)) {
    THING_LOG(t, "%s: apply damage", to_string(e).c_str());
  }

  if (thing_is_player(t)) {
    thing_damage_to_player(g, v, l, t, e);
  } else if (e.source && thing_is_player(e.source)) {
    thing_damage_by_player(g, v, l, t, e);
  }

  //
  // Change the health
  //
  if (thing_health_decr(g, v, l, t, e.damage) <= 0) {
    //
    // Damage type specifics
    //
    switch (e.event_type) {
      case THING_EVENT_NONE :     break;
      case THING_EVENT_LIFESPAN : break;
      case THING_EVENT_SHOVE : //
        break;
      case THING_EVENT_CRUSH : //
        break;
      case THING_EVENT_MELEE : //
        break;
      case THING_EVENT_HEAT : //
        if (! level_is_fire(g, v, l, t->at)) {
          thing_spawn(g, v, l, tp_random(is_fire), t->at);
        }
        thing_is_burnt_set(g, v, l, t);
        break;
      case THING_EVENT_FIRE : //
        if (! level_is_fire(g, v, l, t->at)) {
          thing_spawn(g, v, l, tp_random(is_fire), t->at);
        }
        thing_is_burnt_set(g, v, l, t);
        break;
      case THING_EVENT_ENUM_MAX : break;
    }

    thing_dead(g, v, l, t, e);
  }

  THING_LOG(t, "post damage");
}
