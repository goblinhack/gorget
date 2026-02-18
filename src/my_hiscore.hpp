//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_HISCORE_HPP_
#define MY_HISCORE_HPP_

#include <string>
#include <vector>

#include "my_types.hpp"

class HiScore
{
public:
  HiScore(void) = default;
  HiScore(std::string vname, std::string vreason, std::string vwhen, int vscore, int vlevels_completed)
  {
    this->name             = vname;
    this->reason           = vreason;
    this->when             = vwhen;
    this->score            = vscore;
    this->levels_completed = vlevels_completed;
  }

  ~HiScore(void) = default;

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
  HiScores(void);
  ~HiScores(void);

  //
  // All the hiscores held in the file.
  //
  std::vector< HiScore > hiscores;

  void        add_new_hiscore(Gamep g, int score, LevelNum level, const std::string &name, const std::string &reason);
  bool        is_new_hiscore(int score);
  bool        is_new_highest_hiscore(int score);
  const char *place_str(int score);
};

#endif // _MY_HISCORE_HPP_
