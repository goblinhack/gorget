//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_DICE_ROLL_HPP_
#define _MY_DICE_ROLL_HPP_

#include <string>

class Dice
{
private:
  int ndice {1};    // 1d6+2 (1)
  int sides {6};    // 1d6+2 (6)
  int modifier {0}; // 1d6+2 (2)

  std::string hitdice;
  bool        initialized {};

public:
  std::string to_string(void) const;

  Dice(void);
  Dice(std::string s);

  int  roll(void) const;
  int  max_roll(void) const;
  int  min_roll(void) const;
  bool crit_roll(void) const;

  int operator()() const;
};

bool d20_ge(int stat_total, const int dice_roll_to_exceed);
bool d20_ge(int stat_total, const int dice_roll_to_exceed, bool &fumble, bool &critical);

int stat_to_bonus(int stat);

const std::string stat_to_bonus_string(int stat);
const std::string stat_to_bonus_slash_str(int stat);
const std::string bonus_to_string(int stat);

#endif
