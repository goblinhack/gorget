//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"

#include <algorithm>
#include <cstdint>
#include <string>

[[nodiscard]] auto thing_stat_set(Gamep g, Levelsp v, Levelp l, Thingp me, ThingStatType stat, uint8_t val) -> uint8_t
{
  TRACE_DEBUG();

  if (me == nullptr) {
    ERR("no thing pointer");
    return THING_STAT_DEFAULT;
  }

  if (stat >= THING_STAT_ENUM_MAX) {
    thing_err(g, v, l, me, "bad value in stat for %s, %d", __FUNCTION__, stat);
    return THING_STAT_DEFAULT;
  }

  return me->_stat[ stat ] = val;
}

[[nodiscard]] auto thing_stat_mod(Gamep g, Levelsp v, Levelp l, Thingp me, ThingStatType stat) -> int
{
  TRACE_DEBUG();

  auto val = thing_stat(g, v, l, me, stat);

  if (val <= THING_STAT_MIN) {
    return -9;
  }

  if (val >= THING_STAT_MAX) {
    return 9;
  }

  switch (val) {
    case 1 :  return -9;
    case 2 :  return -8;
    case 3 :  return -7;
    case 4 :  return -6;
    case 5 :  return -5;
    case 6 :  return -4;
    case 7 :  return -3;
    case 8 :  return -2;
    case 9 :  return -1;
    case 10 : return +0;
    case 11 : return +1;
    case 12 : return +2;
    case 13 : return +3;
    case 14 : return +4;
    case 15 : return +5;
    case 16 : return +6;
    case 17 : return +7;
    case 18 : return +8;
    case 19 : return +9;
    default : return +9;
  }
}

[[nodiscard]] auto thing_stat_mod_string(Gamep g, Levelsp v, Levelp l, Thingp me, ThingStatType stat) -> std::string
{
  TRACE_DEBUG();

  auto val = thing_stat(g, v, l, me, stat);

  if (val <= THING_STAT_MIN) {
    return "-9";
  }

  if (val >= THING_STAT_MAX) {
    return "+9";
  }

  switch (val) {
    case 1 :  return "-9";
    case 2 :  return "-8";
    case 3 :  return "-7";
    case 4 :  return "-6";
    case 5 :  return "-5";
    case 6 :  return "-4";
    case 7 :  return "-3";
    case 8 :  return "-2";
    case 9 :  return "-1";
    case 10 : return "+0";
    case 11 : return "+1";
    case 12 : return "+2";
    case 13 : return "+3";
    case 14 : return "+4";
    case 15 : return "+5";
    case 16 : return "+6";
    case 17 : return "+7";
    case 18 : return "+8";
    case 19 : return "+9";
    default : return "+9";
  }

  return "na";
}

[[nodiscard]] auto thing_stat_string(Gamep g, Levelsp v, Levelp l, Thingp me, ThingStatType stat) -> std::string
{
  TRACE_DEBUG();

  auto        val     = thing_stat(g, v, l, me, stat);
  auto        mod     = thing_stat_mod(g, v, l, me, stat);
  auto        mod_str = thing_stat_mod_string(g, v, l, me, stat);
  std::string stat_str;
  std::string stat_name;

  switch (stat) {
    case THING_STAT_ATT : stat_name = "Att"; return string_sprintf(UI_INFO_FMT_STR "%s" UI_RESET_FMT " %2d", stat_name.c_str(), val);
    case THING_STAT_DEF : stat_name = "Def"; return string_sprintf(UI_INFO_FMT_STR "%s" UI_RESET_FMT " %2d", stat_name.c_str(), val);
    case THING_STAT_STR : stat_name = "Str"; break;
    case THING_STAT_CON : stat_name = "Con"; break;
    case THING_STAT_INT : stat_name = "Int"; break;
    case THING_STAT_DEX : stat_name = "Dex"; break;
    case THING_STAT_PSI : stat_name = "Psi"; break;
    case THING_STAT_LCK : stat_name = "Lck"; break;
    default :             stat_name = "n/a"; break;
  }

  if (mod < -5) {
    stat_str = string_sprintf(UI_INFO_FMT_STR "%s" UI_IMPORTANT_FMT_STR "%2d/%-2s", stat_name.c_str(), val, mod_str.c_str());
  } else if (mod < -3) {
    stat_str = string_sprintf(UI_INFO_FMT_STR "%s" UI_WARN_FMT_STR "%2d/%-2s", stat_name.c_str(), val, mod_str.c_str());
  } else if (mod > 0) {
    stat_str = string_sprintf(UI_INFO_FMT_STR "%s" UI_GOOD_FMT_STR "%2d/%-2s", stat_name.c_str(), val, mod_str.c_str());
  } else {
    stat_str = string_sprintf(UI_INFO_FMT_STR "%s" UI_RESET_FMT "%2d/%-2s", stat_name.c_str(), val, mod_str.c_str());
  }

  return stat_str;
}

[[nodiscard]] auto thing_stat(Gamep g, Levelsp v, Levelp l, Thingp me, ThingStatType stat) -> int
{
  TRACE_DEBUG();

  if (me == nullptr) {
    ERR("no thing pointer");
    return THING_STAT_DEFAULT;
  }

  if (stat >= THING_STAT_ENUM_MAX) {
    thing_err(g, v, l, me, "bad value in stat for %s, %d", __FUNCTION__, stat);
    return THING_STAT_DEFAULT;
  }

  auto out = me->_stat[ stat ];

  FOR_ALL_BUFFS(g, v, l, me, buff)
  {
    int const modifier = thing_stat(g, v, l, buff, stat) - THING_STAT_DEFAULT;

    if (modifier < 0) {
      out = std::max(0, out - modifier);
    } else {
      out += modifier;
    }
  }

  return out;
}
