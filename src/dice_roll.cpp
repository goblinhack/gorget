//
// Copyright goblinhack@gmail.com
//

#include "my_dice_class.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_string.hpp"

#include <string>

[[nodiscard]] auto stat_to_bonus(int stat) -> int
{
  if (stat < 0) {
    return -9;
  }
  if (stat > 20) {
    return 9;
  }

  switch (stat) {
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

[[nodiscard]] auto bonus_to_string(int stat) -> std::string
{
  switch (stat) {
    case -20 : return "-20";
    case -19 : return "-19";
    case -18 : return "-18";
    case -17 : return "-17";
    case -16 : return "-16";
    case -15 : return "-15";
    case -14 : return "-14";
    case -13 : return "-13";
    case -12 : return "-12";
    case -11 : return "-11";
    case -10 : return "-10";
    case -9 :  return "-9";
    case -8 :  return "-8";
    case -7 :  return "-7";
    case -6 :  return "-6";
    case -5 :  return "-5";
    case -4 :  return "-4";
    case -3 :  return "-3";
    case -2 :  return "-2";
    case -1 :  return "-1";
    case 0 :   return "--";
    case 1 :   return "+1";
    case 2 :   return "+2";
    case 3 :   return "+3";
    case 4 :   return "+4";
    case 5 :   return "+5";
    case 6 :   return "+6";
    case 7 :   return "+7";
    case 8 :   return "+8";
    case 9 :   return "+9";
    case 10 :  return "+10";
    case 11 :  return "+11";
    case 12 :  return "+12";
    case 13 :  return "+13";
    case 14 :  return "+14";
    case 15 :  return "+15";
    case 16 :  return "+16";
    case 17 :  return "+17";
    case 18 :  return "+18";
    case 19 :  return "+19";
    case 20 :  return "+20";
    default :  return "na";
  }
}

[[nodiscard]] auto stat_to_bonus_string(int stat) -> std::string { return bonus_to_string(stat_to_bonus(stat)); }

[[nodiscard]] auto stat_to_bonus_slash_str(int stat) -> std::string
{
  switch (stat_to_bonus(stat)) {
    case -20 : return "/-20";
    case -19 : return "/-19";
    case -18 : return "/-18";
    case -17 : return "/-17";
    case -16 : return "/-16";
    case -15 : return "/-15";
    case -14 : return "/-14";
    case -13 : return "/-13";
    case -12 : return "/-12";
    case -11 : return "/-11";
    case -10 : return "/-10";
    case -9 :  return "/-9";
    case -8 :  return "/-8";
    case -7 :  return "/-7";
    case -6 :  return "/-6";
    case -5 :  return "/-5";
    case -4 :  return "/-4";
    case -3 :  return "/-3";
    case -2 :  return "/-2";
    case -1 :  return "/-1";
    case 0 :   return "/--";
    case 1 :   return "/+1";
    case 2 :   return "/+2";
    case 3 :   return "/+3";
    case 4 :   return "/+4";
    case 5 :   return "/+5";
    case 6 :   return "/+6";
    case 7 :   return "/+7";
    case 8 :   return "/+8";
    case 9 :   return "/+9";
    case 10 :  return "/+10";
    case 11 :  return "/+11";
    case 12 :  return "/+12";
    case 13 :  return "/+13";
    case 14 :  return "/+14";
    case 15 :  return "/+15";
    case 16 :  return "/+16";
    case 17 :  return "/+17";
    case 18 :  return "/+18";
    case 19 :  return "/+19";
    case 20 :  return "/+20";
    default :  return "/na";
  }
}

//
// Return true if we exceed the target roll
//
[[nodiscard]] auto d20_ge(int stat_total, const int dice_roll_to_exceed, bool &fumble, bool &critical) -> bool
{
  int const dice_roll = PCG_RANDOM_RANGE_INCLUSIVE(1, 20);

  critical = false;
  fumble   = false;

  if (dice_roll == 20) {
    critical = true;
    return true;
  }

  if (dice_roll == 1) {
    fumble = true;
    return false;
  }

  return dice_roll + stat_to_bonus(stat_total) >= dice_roll_to_exceed;
}

//
// Roll for stat modifier "a" to see if it beats "b"
//
[[nodiscard]] auto d20_ge(int stat_total, const int dice_roll_to_exceed) -> bool
{
  int dice_roll = PCG_RANDOM_RANGE_INCLUSIVE(1, 20);

  if (dice_roll == 20) {
    DBG("d20: rolled a 20 => success");
    return true;
  }

  if (dice_roll == 1) {
    DBG("d20: fumble");
    return false;
  }

  DBG("d20: %d(rolled %d+%d) >= %d", dice_roll + stat_to_bonus(stat_total), dice_roll, stat_to_bonus(stat_total), dice_roll_to_exceed);

  dice_roll += stat_to_bonus(stat_total);

  return dice_roll >= dice_roll_to_exceed;
}

Dice::Dice(void) = default;

[[nodiscard]] auto Dice::to_string() const -> std::string { return hitdice; }

Dice::Dice(const std::string &s)
{
  if (s.empty()) {
    return;
  }

  initialized = true;
  hitdice     = s;

  //
  // 1d6+1
  //
  for (const auto &x : split_tokens(s, '+')) {
    auto sp = split_tokens(x, 'd');
    if (sp.size() == 2) {
      //
      // 1d6
      // ^
      ndice = std::stoi(sp[ 0 ]);
      //
      // 1d6
      //   ^
      //
      sides = std::stoi(sp[ 1 ]);
    } else {
      //
      // +1
      //
      modifier += std::stoi(sp[ 0 ]);
    }
  }
  // con("new dice [%s] %dd%d+%d", s.c_str(), ndice, sides, modifier);
}

[[nodiscard]] auto Dice::roll() const -> int
{
  if (! initialized) {
    return 0;
  }

  int n   = ndice;
  int tot = 0;
  // con("roll %dd%d+%d", ndice, sides, modifier);
  while (n-- > 0) {
    tot += PCG_RANDOM_RANGE(0, sides) + 1;
  }
  tot += modifier;
  // con("roll %dd%d+%d => %d", ndice, sides, modifier, tot);
  return tot;
}

[[nodiscard]] auto Dice::max_roll() const -> int
{
  if (! initialized) {
    return 0;
  }

  return (ndice * sides) + modifier;
}

[[nodiscard]] auto Dice::min_roll() const -> int
{
  if (! initialized) {
    return 0;
  }

  return (ndice * 1) + modifier;
}
