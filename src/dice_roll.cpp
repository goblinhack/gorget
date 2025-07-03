//
// Copyright goblinhack@gmail.com
//

#include "my_dice.hpp"
#include "my_dice_roll.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

// Roll -30 -> bonus -20
// Roll -29 -> bonus -19
// Roll -28 -> bonus -19
// Roll -27 -> bonus -18
// Roll -26 -> bonus -18
// Roll -25 -> bonus -17
// Roll -24 -> bonus -17
// Roll -23 -> bonus -16
// Roll -22 -> bonus -16
// Roll -21 -> bonus -15
// Roll -20 -> bonus -15
// Roll -19 -> bonus -14
// Roll -18 -> bonus -14
// Roll -17 -> bonus -13
// Roll -16 -> bonus -13
// Roll -15 -> bonus -12
// Roll -14 -> bonus -12
// Roll -13 -> bonus -11
// Roll -12 -> bonus -11
// Roll -11 -> bonus -10
// Roll -10 -> bonus -10
// Roll -9 ->  bonus -9
// Roll -8 ->  bonus -9
// Roll -7 ->  bonus -8
// Roll -6 ->  bonus -8
// Roll -5 ->  bonus -7
// Roll -4 ->  bonus -7
// Roll -3 ->  bonus -6
// Roll -2 ->  bonus -6
// Roll -1 ->  bonus -5
// Roll 0 ->   bonus -5
// Roll 1 ->   bonus -4
// Roll 2 ->   bonus -4
// Roll 3 ->   bonus -3
// Roll 4 ->   bonus -3
// Roll 5 ->   bonus -2
// Roll 6 ->   bonus -2
// Roll 7 ->   bonus -1
// Roll 8 ->   bonus -1
// Roll 9 ->   bonus +0
// Roll 10 ->  bonus +0
// Roll 11 ->  bonus +0
// Roll 12 ->  bonus +1
// Roll 13 ->  bonus +1
// Roll 14 ->  bonus +2
// Roll 15 ->  bonus +2
// Roll 16 ->  bonus +3
// Roll 17 ->  bonus +3
// Roll 18 ->  bonus +4
// Roll 19 ->  bonus +4
// Roll 20 ->  bonus +5
// Roll 21 ->  bonus +5
// Roll 22 ->  bonus +6
// Roll 23 ->  bonus +6
// Roll 24 ->  bonus +7
// Roll 25 ->  bonus +7
// Roll 26 ->  bonus +8
// Roll 27 ->  bonus +8
// Roll 28 ->  bonus +9
// Roll 29 ->  bonus +9
// Roll 30 ->  bonus +10
int stat_to_bonus(int stat)
{
  int bonus = (stat - 10) / 2;
  if (bonus < -20) {
    return -20;
  }
  if (bonus > 20) {
    return 20;
  }

#if 0
  //
  // Generate all rolls to see the bonus
  //
  static int first = true;
  if (first) {
    first = false;
    for (auto i = -30; i <= 30; i++) {
      printf("Roll %d -> bonus %d\n", i, stat_to_bonus(i));
    }
    DIE("See above rolls");
  }
#endif

  return bonus;
}

const std::string bonus_to_string(int stat)
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

const std::string stat_to_bonus_string(int stat) { return bonus_to_string(stat_to_bonus(stat)); }

const std::string stat_to_bonus_slash_str(int stat)
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
bool d20_ge(int stat_total, const int dice_roll_to_exceed, bool &fumble, bool &critical)
{
  int dice_roll = pcg_random_range_inclusive(1, 20);

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
bool d20_ge(int stat_total, const int dice_roll_to_exceed)
{
  int dice_roll = pcg_random_range_inclusive(1, 20);

  if (dice_roll == 20) {
    DBG("d20: rolled a 20 => success");
    return true;
  }

  if (dice_roll == 1) {
    DBG("d20: fumble");
    return false;
  }

  DBG("d20: %d(rolled %d+%d) >= %d", dice_roll + stat_to_bonus(stat_total), dice_roll, stat_to_bonus(stat_total),
      dice_roll_to_exceed);

  dice_roll += stat_to_bonus(stat_total);

  return dice_roll >= dice_roll_to_exceed;
}

Dice::Dice(void) = default;

std::string Dice::to_string(void) const { return hitdice; }

Dice::Dice(std::string s)
{
  hitdice = s;

  //
  // 1d6+1
  //
  for (auto x : split_tokens(s, '+')) {
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
    // CON("new dice %dd%d+%d", ndice, sides, modifier);
  }
}

int Dice::roll(void) const
{
  int n   = ndice;
  int tot = 0;
  // CON("roll %dd%d+%d", ndice, sides, modifier);
  while (n-- > 0) {
    tot += pcg_random_range(0, sides) + 1;
  }
  tot += modifier;
  // CON("roll %dd%d+%d => %d", ndice, sides, modifier, tot);
  return tot;
}

int Dice::max_roll(void) const { return ndice * sides + modifier; }

int Dice::min_roll(void) const { return ndice * 1 + modifier; }

bool Dice::crit_roll(void) const
{
  auto r = roll();
  return r >= (ndice * sides);
}
