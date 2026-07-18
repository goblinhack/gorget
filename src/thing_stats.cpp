//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_dice_rolls.hpp"
#include "my_main.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"
#include "my_thing_inlines.hpp" // NOLINT
#include "my_tp.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"

#include <algorithm>
#include <cstdint>
#include <string>

[[nodiscard]] auto stat_to_mod(int val) -> int
{
  if (val <= THING_STAT_MIN) {
    return -9;
  }

  if (val >= THING_STAT_MAX) {
    return +9;
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
    case 20 : return +10;
    default : return 0;
  }
}

[[nodiscard]] static auto stat_to_mod_string(int val) -> const std::string
{
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
    case 20 : return "+X";
    default : return "??";
  }
}

[[nodiscard]] static auto stat_to_name(ThingStatType stat) -> const std::string
{
  switch (stat) {
    case THING_STAT_ATT :  return "Att";
    case THING_STAT_DEF :  return "Def";
    case THING_STAT_STR :  return "Str";
    case THING_STAT_CON :  return "Con";
    case THING_STAT_INT :  return "Int";
    case THING_STAT_DEX :  return "Dex";
    case THING_STAT_PSI :  return "Psi";
    case THING_STAT_LUCK : return "Lck";
    default :              return "???";
  }
}

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

//
// 19 -> 9
//
[[nodiscard]] auto thing_stat_mod(Gamep g, Levelsp v, Levelp l, Thingp me, ThingStatType stat) -> int
{
  TRACE_DEBUG();

  return stat_to_mod(thing_stat(g, v, l, me, stat));
}

//
// 19 -> "+9"
//
[[nodiscard]] static auto thing_stat_mod_value_string(Gamep g, Levelsp v, Levelp l, Thingp me, ThingStatType stat) -> std::string
{
  TRACE_DEBUG();

  auto val = thing_stat(g, v, l, me, stat);

  return stat_to_mod_string(val);
}

//
// "Con +9"
//
[[nodiscard]] auto thing_stat_mod_string(Gamep g, Levelsp v, Levelp l, Thingp me, ThingStatType stat) -> std::string
{
  TRACE_DEBUG();

  auto              mod       = thing_stat_mod(g, v, l, me, stat);
  auto              mod_str   = thing_stat_mod_value_string(g, v, l, me, stat);
  std::string const stat_name = stat_to_name(stat);
  std::string       stat_str;

  if (mod < -5) {
    stat_str = string_sprintf(UI_INFO_FMT_STR "%s" UI_IMPORTANT_FMT_STR " %-2s", stat_name.c_str(), mod_str.c_str());
  } else if (mod < -3) {
    stat_str = string_sprintf(UI_INFO_FMT_STR "%s" UI_WARN_FMT_STR " %-2s", stat_name.c_str(), mod_str.c_str());
  } else if (mod > 0) {
    stat_str = string_sprintf(UI_INFO_FMT_STR "%s" UI_GOOD_FMT_STR " %-2s", stat_name.c_str(), mod_str.c_str());
  } else {
    stat_str = string_sprintf(UI_INFO_FMT_STR "%s" UI_RESET_FMT " %-2s", stat_name.c_str(), mod_str.c_str());
  }

  return stat_str;
}

//
// "Att 20/+9"
//
[[nodiscard]] auto thing_stat_string(Gamep g, Levelsp v, Levelp l, Thingp me, ThingStatType stat) -> std::string
{
  TRACE_DEBUG();

  auto              val       = thing_stat(g, v, l, me, stat);
  auto              mod       = thing_stat_mod(g, v, l, me, stat);
  auto              mod_str   = thing_stat_mod_value_string(g, v, l, me, stat);
  std::string const stat_name = stat_to_name(stat);
  std::string       stat_str;

  switch (stat) {
    case THING_STAT_ATT :  return string_sprintf(UI_INFO_FMT_STR "%s" UI_RESET_FMT " %2d", stat_name.c_str(), val);
    case THING_STAT_DEF :  return string_sprintf(UI_INFO_FMT_STR "%s" UI_RESET_FMT " %2d", stat_name.c_str(), val);
    case THING_STAT_STR :  break;
    case THING_STAT_CON :  break;
    case THING_STAT_INT :  break;
    case THING_STAT_DEX :  break;
    case THING_STAT_PSI :  break;
    case THING_STAT_LUCK : break;
    default :              break;
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

//
// Luck -> 10 + +1 -> 11
//
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

  int out = me->_stat[ stat ];

  FOR_ALL_BUFFS(g, v, l, me, buff)
  {
    auto mod = thing_stat_mod(g, v, l, buff, stat);

    out += mod;
  }

  FOR_ALL_INVENTORY_ITEMS(g, v, l, me, item)
  {
    auto mod = thing_stat_mod(g, v, l, item, stat);

    auto item_count = thing_inventory_get_item_count(g, v, l, item, me);
    if (item_count > 0) {
      mod *= item_count;
    }

    out += mod;
  }

  out = std::max(THING_STAT_MIN, out);
  out = std::min(THING_STAT_MAX, out);

  return out;
}

[[nodiscard]] auto thing_stat_success(Gamep g, Levelsp v, Levelp l, Thingp me, ThingStatType stat, int modifier) -> bool
{
  TRACE_DEBUG();

  int const result[ 20 ][ 20 ] = {
      //       10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10  stat
      //       -9 -8 -7 -6 -5 -4 -3 -2 -1 +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +10 mod
      //        1  2  3  4  5  6  7  8  9 10 11 12 12 14 15 16 17 18 19 20  total
      // roll +----------------------------------------------------------------
      /* 1  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //
      /* 2  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}, //
      /* 3  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1}, //
      /* 4  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}, //
      /* 5  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1}, //
      /* 6  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1}, //
      /* 7  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1}, //
      /* 8  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1}, //
      /* 9  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //
      /* 10 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //
      /* 11 */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //
      /* 12 */ {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //
      /* 13 */ {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //
      /* 14 */ {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //
      /* 15 */ {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //
      /* 16 */ {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //
      /* 17 */ {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //
      /* 18 */ {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //
      /* 19 */ {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //
      /* 20 */ {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //
  };

  auto roll       = d20();
  auto total_stat = thing_stat(g, v, l, me, stat);

  total_stat += modifier;

  if (total_stat <= 1) {
    return false;
  }
  if (total_stat >= 20) {
    return true;
  }
  //  topcon("tot %d roll %d mod %d", total_stat, roll, modifier);

  return result[ roll - 1 ][ total_stat - 1 ] != 0;
}
