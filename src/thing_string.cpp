//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"

std::string to_string(Gamep g, Thingp t)
{
  TRACE_NO_INDENT();

  if (! t) {
    ERR("no thing for %s", __FUNCTION__);
    return "<no thing>";
  }

  auto tp = thing_tp(t);
  if (! t) {
    ERR("no tp for %s", __FUNCTION__);
    return "<no tp>";
  }

  auto name = tp_name(tp);
  if (g && thing_is_player(t)) {
    name = game_player_name_get(g);
  }

  return (string_sprintf("%08" PRIX32
                         /* level num                     */ " l%u"
                         /* tick                          */ " t%u"
                         /* thing_health                  */ " h%d"
                         /* name                          */ " %s"
                         /* is_dead                       */ "%s"
                         /* is_sleeping                   */ "%s"
                         /* is_falling                    */ "%s"
                         /* is_open                       */ "%s"
                         /* is_burning                    */ "%s"
                         /* is_scheduled_for_cleanup      */ "%s"
                         /* at                            */ " @%d,%d",
                         /* newline */ t->id,
                         /* newline */ t->level_num,
                         /* newline */ t->tick,
                         /* newline */ thing_health(t),
                         /* newline */ name.c_str(),
                         /* newline */ thing_is_dead(t) ? "/dead" : "",
                         /* newline */ thing_is_sleeping(t) ? "/slp" : "",
                         /* newline */ thing_is_falling(t) ? "/fal" : "",
                         /* newline */ thing_is_open(t) ? "/opn" : "",
                         /* newline */ thing_is_burning(t) ? "/brn" : "",
                         /* newline */ thing_is_scheduled_for_cleanup(t) ? "/free" : "",
                         /* newline */ t->at.x, t->at.y));
}

std::string to_string(Gamep g, ThingEvent &e)
{
  TRACE_NO_INDENT();

  std::string s = "ev:";

  if (e.reason != "") {
    s += " r:'";
    s += e.reason;
    s += "'";
  }

  if (e.damage != THING_EVENT_NONE) {
    s += " e:";
    s += ThingEventType_to_string(e.event_type);
  }

  if (e.damage) {
    s += " d:";
    s += std::to_string(e.damage);
  }

  if (e.source) {
    s += " src:(";
    s += to_string(g, e.source);
    s += ")";
  }

  return s;
}

std::string to_death_reason_string(Gamep g, Levelsp v, Levelp l, Thingp t, ThingEvent &e)
{
  TRACE_NO_INDENT();

  std::string s;
  auto        source = e.source;

  switch (e.event_type) {
    case THING_EVENT_NONE : break;
    case THING_EVENT_FALL : //
      s += "fell to their death";
      break;
    case THING_EVENT_LIFESPAN_EXPIRED : //
      s += "ran out of life";
      break;
    case THING_EVENT_SHOVED : //
      s += "shoved and died";
      break;
    case THING_EVENT_CRUSH : //
      s += "crushed";
      break;
    case THING_EVENT_MELEE_DAMAGE : //
      s += "hacked to bits";
      break;
    case THING_EVENT_HEAT_DAMAGE : //
      s += "cooked";
      break;
    case THING_EVENT_WATER_DAMAGE : //
      s += "drowned";
      break;
    case THING_EVENT_EXPLOSION_DAMAGE : //
      s += "blown up";
      break;
    case THING_EVENT_FIRE_DAMAGE : //
      s += "burned";
      break;
    case THING_EVENT_OPEN : //
      s += "opened";
      break;
    case THING_EVENT_COLLECTED : //
      s += "collected";
      break;
    case THING_EVENT_ENUM_MAX : break;
  }

  //
  // Add some more spice to the message
  //
  if (level_is_lava(g, v, l, t->at)) {
    if (! (source && thing_is_lava(source))) {
      s += " in lava";
    }
  } else if (level_is_deep_water(g, v, l, t->at)) {
    if (! (source && thing_is_water(source))) {
      s += " in the depths";
    }
  } else if (level_is_water(g, v, l, t->at)) {
    if (! (source && thing_is_water(source))) {
      s += " in a puddle";
    }
  }

  if (source) {
    if (thing_is_lava(source) || thing_is_water(source)) {
      s += " in ";
    } else {
      s += " by ";
    }

    auto name = tp_long_name(thing_tp(source));
    if (g && thing_is_player(source)) {
      name = game_player_name_get(g);
    }

    s += name;
  }

  return s;
}
