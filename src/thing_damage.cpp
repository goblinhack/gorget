//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

//
// The player has been attacked
//
static void thing_damage_to_player(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_AND_INDENT();

  auto it = e.source;

  if (it) {
    auto it_tp = thing_tp(it);

    switch (e.damage_type) {
      case THING_DAMAGE_NONE : break;
      case THING_DAMAGE_MELEE : // newline
        TOPCON("You are hit by the %s.", tp_long_name(it_tp));
        break;
      case THING_DAMAGE_HEAT : // newline
        TOPCON("You suffer heat damage from the %s.", tp_long_name(it_tp));
        break;
      case THING_DAMAGE_FIRE : // newline
        TOPCON("You are burnt by the %s.", tp_long_name(it_tp));
        break;
      case THING_DAMAGE_ENUM_MAX : break;
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
  auto tp = thing_tp(t);

  if (it) {
    auto it_tp = thing_tp(it);

    switch (e.damage_type) {
      case THING_DAMAGE_NONE : break;
      case THING_DAMAGE_MELEE : // newline
        TOPCON("%s is hit by the %s.", tp_long_name(tp), tp_long_name(it_tp));
        break;
      case THING_DAMAGE_HEAT : // newline
        TOPCON("%s suffers heat damage from the %s.", tp_long_name(tp), tp_long_name(it_tp));
        break;
      case THING_DAMAGE_FIRE : // newline
        TOPCON("%s is burnt by the %s.", tp_long_name(tp), tp_long_name(it_tp));
        break;
      case THING_DAMAGE_ENUM_MAX : break;
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
  if (thing_is_immune_to(t, e.damage_type)) {
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
    thing_dead(g, v, l, t, e);
  }

  THING_LOG(t, "post damage");
}
