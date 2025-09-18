//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game_popups.hpp"
#include "my_level.hpp"
#include "my_string.hpp"
#include "my_ui.hpp"

//
// The player has been attacked
//
static void thing_damage_to_player(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_AND_INDENT();

  auto it = e.source;

  std::string msg = "-" + std::to_string(e.damage);
  game_popup_text_add(g, t->at.x, t->at.y, msg, RED);

  if (it) {
    auto by_the_thing = thing_the_long_name(g, v, l, it);

    switch (e.event_type) {
      case THING_EVENT_SHOVED : //
        TOPCON(UI_WARNING_FMT_STR "You are shoved by %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_CRUSH : //
        TOPCON(UI_WARNING_FMT_STR "You are crushed by %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_MELEE_DAMAGE : //
        TOPCON(UI_WARNING_FMT_STR "You are hit by %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_HEAT_DAMAGE : //
        TOPCON(UI_WARNING_FMT_STR "You suffer heat damage from %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_WATER_DAMAGE : //
        TOPCON(UI_WARNING_FMT_STR "You suffer water damage from %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_EXPLOSION_DAMAGE : //
        TOPCON(UI_WARNING_FMT_STR "You suffer blast damage from %s." UI_RESET_FMT, by_the_thing.c_str());
        break;
      case THING_EVENT_FIRE_DAMAGE :
        if (thing_is_lava(it)) {
          TOPCON(UI_WARNING_FMT_STR "You are burning in lava!" UI_RESET_FMT);
        } else if (thing_is_fire(it)) {
          TOPCON(UI_WARNING_FMT_STR "The flames wrap around you!" UI_RESET_FMT);
        } else {
          TOPCON(UI_WARNING_FMT_STR "You are burnt by %s." UI_RESET_FMT, by_the_thing.c_str());
        }
        break;
      case THING_EVENT_NONE :             //
      case THING_EVENT_OPEN :             //
      case THING_EVENT_LIFESPAN_EXPIRED : //
      case THING_EVENT_FALL :             //
      case THING_EVENT_CARRIED :          //
      case THING_EVENT_CARRIED_MERGED :   //
      case THING_EVENT_ENUM_MAX :         //
        ERR("unexpected event: %s", ThingEventType_to_string(e.event_type).c_str());
        break;
    }
  } else {
    switch (e.event_type) {
      case THING_EVENT_FALL : //
        TOPCON(UI_WARNING_FMT_STR "You fall." UI_RESET_FMT);
        break;
      case THING_EVENT_SHOVED : //
        TOPCON(UI_WARNING_FMT_STR "You are shoved." UI_RESET_FMT);
        break;
      case THING_EVENT_CRUSH : //
        TOPCON(UI_WARNING_FMT_STR "You are crushed." UI_RESET_FMT);
        break;
      case THING_EVENT_MELEE_DAMAGE : //
        TOPCON(UI_WARNING_FMT_STR "You are hit." UI_RESET_FMT);
        break;
      case THING_EVENT_HEAT_DAMAGE : //
        TOPCON(UI_WARNING_FMT_STR "You suffer heat damage." UI_RESET_FMT);
        break;
      case THING_EVENT_WATER_DAMAGE : //
        TOPCON(UI_WARNING_FMT_STR "You suffer water damage." UI_RESET_FMT);
        break;
      case THING_EVENT_EXPLOSION_DAMAGE : //
        TOPCON(UI_WARNING_FMT_STR "You suffer blast damage." UI_RESET_FMT);
        break;
      case THING_EVENT_FIRE_DAMAGE : //
        TOPCON(UI_WARNING_FMT_STR "You are burnt." UI_RESET_FMT);
        break;
      case THING_EVENT_NONE :             //
      case THING_EVENT_OPEN :             //
      case THING_EVENT_LIFESPAN_EXPIRED : //
      case THING_EVENT_CARRIED :          //
      case THING_EVENT_CARRIED_MERGED :   //
      case THING_EVENT_ENUM_MAX :         //
        ERR("unexpected event: %s", ThingEventType_to_string(e.event_type).c_str());
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

  std::string msg = "-" + std::to_string(e.damage);
  game_popup_text_add(g, t->at.x, t->at.y, msg, WHITE);

  if (it && thing_is_loggable(t)) {
    auto the_thing = capitalize_first(thing_the_long_name(g, v, l, t));
    auto by_player = thing_long_name(g, v, l, it);

    switch (e.event_type) {
      case THING_EVENT_SHOVED : //
        TOPCON("%s is shoved by %s.", the_thing.c_str(), by_player.c_str());
        break;
      case THING_EVENT_CRUSH : //
        TOPCON("%s is crushed by %s.", the_thing.c_str(), by_player.c_str());
        break;
      case THING_EVENT_MELEE_DAMAGE : //
        TOPCON("%s is hit by %s.", the_thing.c_str(), by_player.c_str());
        break;
      case THING_EVENT_HEAT_DAMAGE : //
        TOPCON("%s suffers heat damage from %s.", the_thing.c_str(), by_player.c_str());
        break;
      case THING_EVENT_WATER_DAMAGE : //
        TOPCON("%s suffers water damage from %s.", the_thing.c_str(), by_player.c_str());
        break;
      case THING_EVENT_EXPLOSION_DAMAGE : //
        TOPCON("%s suffers blast damage from %s.", the_thing.c_str(), by_player.c_str());
        break;
      case THING_EVENT_FIRE_DAMAGE : //
        TOPCON("%s is burnt by %s.", the_thing.c_str(), by_player.c_str());
        break;
      case THING_EVENT_NONE :             //
      case THING_EVENT_OPEN :             //
      case THING_EVENT_LIFESPAN_EXPIRED : //
      case THING_EVENT_FALL :             //
      case THING_EVENT_CARRIED :          //
      case THING_EVENT_CARRIED_MERGED :   //
      case THING_EVENT_ENUM_MAX :         //
        ERR("unexpected event: %s", ThingEventType_to_string(e.event_type).c_str());
        break;
    }
  }
}

//
// Do not apply too much for one event
//
static void thing_damage_cap_for_this_event(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_NO_INDENT();

  auto       tp = thing_tp(t);
  const auto h  = tp_health_max_get(tp);

  //
  // Limit the damage that can occur this event.
  //
  auto max_damage_this_time = h / 4;
  if (max_damage_this_time < 1) {
    max_damage_this_time = 1;
  }

  if (e.damage > max_damage_this_time) {
    auto old_d = e.damage;
    e.damage   = max_damage_this_time;
    THING_LOG(t, "%s: limit damage %d -> %d", to_string(g, e).c_str(), old_d, e.damage);
  }
}

//
// Do not apply too much damage per tick
//
static void thing_damage_cap_for_this_tick(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_NO_INDENT();

  auto       tp = thing_tp(t);
  const auto h  = tp_health_max_get(tp);

  //
  // Limit the total damage that can occur per tick.
  //
  auto max_damage_per_tick = h / 3;
  if (max_damage_per_tick < 1) {
    max_damage_per_tick = 1;
  }

  auto d_total = thing_damage_this_tick_incr(g, v, l, t, e.damage);
  if (d_total > max_damage_per_tick) {
    auto old_d = e.damage;
    e.damage -= d_total - max_damage_per_tick;
    THING_LOG(t, "%s: limit per tick damage %d -> %d", to_string(g, e).c_str(), old_d, e.damage);
  }
}

//
// Do not apply too much damage per tick
//
static void thing_damage_cap(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_NO_INDENT();

  if (! thing_is_damage_capped(t)) {
    return;
  }

  thing_damage_cap_for_this_event(g, v, l, t, e);
  thing_damage_cap_for_this_tick(g, v, l, t, e);
}

//
// Apply a damage type to a thing
//
void thing_damage(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_AND_INDENT();

  auto tp = thing_tp(t);

  //
  // Indestructible?
  //
  if (thing_is_indestructible(t)) {
    THING_LOG(t, "%s: no damage as indestructible", to_string(g, e).c_str());
    return;
  }

  //
  // Already dead?
  //
  if (thing_is_dead(t)) {
    THING_LOG(t, "%s: no damage as already dead", to_string(g, e).c_str());
    return;
  }

  //
  // Immune to this attack?
  //
  if (thing_is_immune_to(t, e.event_type)) {
    THING_LOG(t, "%s: no damage as immune", to_string(g, e).c_str());
    return;
  }

  //
  // Limit damage?
  //
  thing_damage_cap(g, v, l, t, e);

  //
  // No damage?
  //
  if (e.damage <= 0) {
    THING_LOG(t, "%s: no damage to apply", to_string(g, e).c_str());
    return;
  }

  //
  // Log the reason for attack?
  //
  THING_LOG(t, "%s: apply damage", to_string(g, e).c_str());

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
      case THING_EVENT_NONE : //
        break;
      case THING_EVENT_LIFESPAN_EXPIRED : //
        break;
      case THING_EVENT_FALL : //
        break;
      case THING_EVENT_SHOVED : //
        break;
      case THING_EVENT_CRUSH : //
        break;
      case THING_EVENT_MELEE_DAMAGE : //
        break;
      case THING_EVENT_HEAT_DAMAGE : //
        {
          auto temp_burn = tp_temperature_burns_at_get(tp);
          if (temp_burn && (thing_temperature(t) > temp_burn)) {
            if (! level_is_fire(g, v, l, t->at)) {
              THING_DBG(t, "spawn flames due to heat damage");
              thing_spawn(g, v, l, tp_random(is_fire), t->at);
            }

            if (level_is_water(g, v, l, t->at)) {
              if (! level_is_steam(g, v, l, t->at)) {
                THING_DBG(t, "spawn steam over water due to fire damage");
                thing_spawn(g, v, l, tp_random(is_steam), t->at);
              }
            }

            thing_is_burning_set(g, v, l, t);
          }
        }
        break;
      case THING_EVENT_FIRE_DAMAGE : //
        if (! level_is_fire(g, v, l, t->at)) {
          THING_DBG(t, "spawn flames due to fire damage");
          thing_spawn(g, v, l, tp_random(is_fire), t->at);
        }

        if (level_is_water(g, v, l, t->at)) {
          if (! level_is_steam(g, v, l, t->at)) {
            THING_DBG(t, "spawn steam over water due to fire damage");
            thing_spawn(g, v, l, tp_random(is_steam), t->at);
          }
        }

        thing_is_burning_set(g, v, l, t);
        break;
      case THING_EVENT_WATER_DAMAGE : //
        if (! level_is_steam(g, v, l, t->at)) {
          THING_DBG(t, "spawn steam due to water damage");
          thing_spawn(g, v, l, tp_random(is_steam), t->at);
        }
        break;
      case THING_EVENT_EXPLOSION_DAMAGE : //
        break;
      case THING_EVENT_OPEN :           //
      case THING_EVENT_CARRIED :        //
      case THING_EVENT_CARRIED_MERGED : //
      case THING_EVENT_ENUM_MAX :       //
        ERR("unexpected event: %s", ThingEventType_to_string(e.event_type).c_str());
        break;
    }

    thing_dead(g, v, l, t, e);
  }

  THING_LOG(t, "post damage");
}
