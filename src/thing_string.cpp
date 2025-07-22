//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_backtrace.hpp"
#include "my_callstack.hpp"
#include "my_console.hpp"
#include "my_game.hpp"
#include "my_log.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

#include <stdarg.h>
#include <string.h>

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
                         /* level num                     */ " L%u"
                         /* level num                     */ " T%u"
                         /* thing_health                  */ " H%d"
                         /* name                          */ " %s"
                         /* is_loggable                   */ "%s"
                         /* is_dead                       */ "%s"
                         /* is_open                       */ "%s"
                         /* is_scheduled_for_cleanup      */ "%s"
                         /* at                            */ " @%d,%d",
                         /* newline */ t->id,
                         /* newline */ t->level_num,
                         /* newline */ t->tick,
                         /* newline */ thing_health(t),
                         /* newline */ name,
                         /* newline */ thing_is_dead(t) ? "/dead" : "",
                         /* newline */ thing_is_sleeping(t) ? "/sleeping" : "",
                         /* newline */ thing_is_open(t) ? "/open" : "",
                         /* newline */ thing_is_scheduled_for_cleanup(t) ? "/cleanup" : "",
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

std::string to_death_reason(Gamep g, ThingEvent &e)
{
  TRACE_NO_INDENT();

  std::string s;

  switch (e.event_type) {
    case THING_EVENT_NONE : break;
    case THING_EVENT_LIFESPAN : //
      s += "ran out of life";
      break;
    case THING_EVENT_SHOVE : //
      s += "shoved to death";
      break;
    case THING_EVENT_CRUSH : //
      s += "crushed to death";
      break;
    case THING_EVENT_MELEE_DAMAGE : //
      s += "hacked to death";
      break;
    case THING_EVENT_HEAT_DAMAGE : //
      s += "cooked to death";
      break;
    case THING_EVENT_WATER_DAMAGE : //
      s += "drowned";
      break;
    case THING_EVENT_FIRE_DAMAGE : //
      s += "burnt to death";
      break;
    case THING_EVENT_ENUM_MAX : break;
  }

  if (e.source) {
    s += " by ";

    auto t    = e.source;
    auto name = tp_long_name(thing_tp(t));
    if (g && thing_is_player(t)) {
      name = game_player_name_get(g);
    }

    s += name;
  }

  return s;
}

std::string thing_long_name(Gamep g, Levelsp v, Levelp l, Thingp t, bool include_owner)
{
  TRACE_NO_INDENT();

  if (unlikely(! t)) {
    return ("<no name>");
  }

  auto tp = thing_tp(t);

  std::string out;

#if 0
  //
  // Tamed?
  //
  auto l = leader();
  if (l && (l == level->player)) {
    out = "your ";
  }

#endif
  //
  // "the goblin's short sword" for example
  //
  auto t_o = top_owner(g, v, l, t);
  if (include_owner) {
    if (t_o && ! thing_is_player(t_o)) {

      out += tp_long_name(thing_tp(t_o));
      out += "'s ";
    }
  }

  if (thing_is_dead(t)) {
    if (thing_is_player(t) || thing_is_monst(t)) {
      if (thing_is_undead(t)) {
        out += "extra dead ";
      } else {
        out += "dead ";
      }
    }
    if (thing_is_broken_on_death(t)) {
      out += "broken ";
    }
    if (thing_is_extinguished_on_death(t)) {
      out += "extinguished ";
    }
  }

#if 0
  if (is_frozen) {
    out += "frozen ";
  } else if (is_gaseous) {
    out += "burnt ";
  } else if (tpp->charge_count() && ! charge_count()) {
    out += "spent ";
  }

  //
  // Tamed?
  //
  if (l && (l == level->player)) {
    if (is_not_shown_as_a_pet()) {
      //
      // Not really a pet
      //
    } else {
      out += "pet ";
    }
  }
#endif

  {
    auto name = tp_long_name(tp);
    if (g && thing_is_player(t)) {
      name = game_player_name_get(g);
    }

    out += name;
  }

#if 0
  if (tpp->is_spell()) {
    out += " spell";
  }

  if (tpp->is_skill()) {
    out += " skill";
  }
#endif

  return out;
}

std::string thing_the_long_name(Gamep g, Levelsp v, Levelp l, Thingp t, bool include_owner)
{
  TRACE_NO_INDENT();

  return "the " + thing_long_name(g, v, l, t, include_owner);
}
