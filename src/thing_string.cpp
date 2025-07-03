//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_backtrace.hpp"
#include "my_callstack.hpp"
#include "my_console.hpp"
#include "my_log.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

#include <stdarg.h>
#include <string.h>

std::string to_string(Thingp t)
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

  return (string_sprintf("%" PRIX32
                         /* level num    */ " L%u"
                         /* thing_health */ " H%d"
                         /* tp_name      */ " %s"
                         /* is_loggable  */ "%s"
                         /* is_dead      */ "%s"
                         /* is_open      */ "%s"
                         /* at           */ " @%d,%d",
                         /* newline */ t->id,
                         /* newline */ t->level_num,
                         /* newline */ thing_health(t),
                         /* newline */ tp_name(tp),
                         /* newline */ thing_is_dead(t) ? "/dead" : "",
                         /* newline */ thing_is_sleeping(t) ? "/sleeping" : "",
                         /* newline */ thing_is_open(t) ? "/open" : "",
                         /* newline */ t->at.x, t->at.y));
}

std::string to_string(ThingEvent &e)
{
  TRACE_NO_INDENT();

  std::string s = "event:";

  if (e.reason != "") {
    s += " reason: ";
    s += e.reason;
  }

  if (e.damage != THING_DAMAGE_NONE) {
    s += " damage-type: ";
    s += ThingDamage_to_string(e.damage_type);
  }

  if (e.damage) {
    s += " damage: ";
    s += std::to_string(e.damage);
  }

  if (e.source) {
    s += " source: ";
    s += to_string(e.source);
  }

  return s;
}
