//
// Copyright goblinhack@gmail.com
//

#ifndef MY_HISCORE_HPP_
#define MY_HISCORE_HPP_

#include <string>
#include <utility>
#include <vector>

#include "my_types.hpp"

class HiScore
{
public:
  HiScore() = default;
  HiScore(std::string vname, std::string vreason, std::string vwhen, int vscore, int vlevels_completed)
      : name(std::move(vname)), reason(std::move(vreason)), when(std::move(vwhen)), score(vscore),
        levels_completed(vlevels_completed)
  {
  }

  ~HiScore() = default;

  //
  // Who made the score?
  //
  std::string name;
  std::string reason;
  std::string when;
  int         score            = {};
  int         levels_completed = {};

  //
  // The number of scores in the table.
  //
  static const int max           = 10;
  static const int max_displayed = 10;
};

class HiScores
{
public:
  HiScores();
  ~HiScores();

  //
  // All the hiscores held in the file.
  //
  std::vector< HiScore > hiscores;

  void add_new_hiscore(Gamep g, int score, LevelNum level, const std::string &name, const std::string &reason);
  auto is_new_hiscore(int score) -> bool;
  auto is_new_highest_hiscore(int score) -> bool;
  auto place_str(int score) -> const char *;
};

#endif // _MY_HISCORE_HPP_
