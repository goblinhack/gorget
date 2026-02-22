//
// Copyright goblinhack@gmail.com
//

#ifndef MY_DICE_CLASS_HPP_
#define MY_DICE_CLASS_HPP_

#include <string>

class Dice
{
private:
  int ndice {0};    // 1d6+2 (1)
  int sides {0};    // 1d6+2 (6)
  int modifier {0}; // 1d6+2 (2)

  std::string hitdice;
  bool        initialized {};

public:
  [[nodiscard]] auto to_string() const -> std::string;

  Dice();
  Dice(const std::string &s);

  [[nodiscard]] auto roll() const -> int;
  [[nodiscard]] auto max_roll() const -> int;
  [[nodiscard]] auto min_roll() const -> int;

  auto operator()() const -> int;
};

auto d20_ge(int stat_total, int dice_roll_to_exceed) -> bool;
auto d20_ge(int stat_total, int dice_roll_to_exceed, bool &fumble, bool &critical) -> bool;

auto stat_to_bonus(int stat) -> int;

auto stat_to_bonus_string(int stat) -> std::string;
auto stat_to_bonus_slash_str(int stat) -> std::string;
auto bonus_to_string(int stat) -> std::string;

#endif
