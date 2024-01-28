//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_HISCORE_HPP_
#define _MY_HISCORE_HPP_

#include <string>

class HiScore
{
public:
  HiScore(void) = default;
  HiScore(std::string name, std::string when, int score, int level_reached)
  {
    this->name          = name;
    this->when          = when;
    this->score         = score;
    this->level_reached = level_reached;
  }

  ~HiScore(void) = default;

  //
  // Who made the score?
  //
  std::string name;
  std::string when;
  int         score;
  int         level_reached;

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

  void        add_new_hiscore(int score, int level, const std::string &name);
  bool        is_new_hiscore(int score);
  bool        is_new_highest_hiscore(int score);
  const char *place_str(int score);
};

#endif // _MY_THING_HPP_
