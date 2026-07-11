//
// Copyright goblinhack@gmail.com
//

#ifndef MY_DICE_CLASS_HPP
#define MY_DICE_CLASS_HPP

#include <string>

class Dice
{
private:
  int ndice {0};    // 1d6+2 (1)
  int sides {0};    // 1d6+2 (6)
  int modifier {0}; // 1d6+2 (2)

  std::string hitdice;

public:
  bool initialized {};

  [[nodiscard]] auto to_string() const -> std::string;

  Dice();
  explicit Dice(const std::string &s);

  [[nodiscard]] auto roll() const -> int;
  [[nodiscard]] auto max_roll() const -> int;
  [[nodiscard]] auto min_roll() const -> int;

  auto operator()() const -> int;
};

#endif
