//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_serialize.hpp"
#include "my_time.hpp"

HiScores::HiScores(void)
{
  TRACE_NO_INDENT();
  if ((int) hiscores.size() > HiScore::max) {
    hiscores.resize(HiScore::max);
  } else {
    while ((int) hiscores.size() < HiScore::max) {
      hiscores.push_back(HiScore("AAA", "", "",
                                 0, // score
                                 0  // levels_completed
                                 ));
    }
  }
}

HiScores::~HiScores(void) { TRACE_NO_INDENT(); }

void HiScores::add_new_hiscore(Gamep g, int score, LevelNum level_num, const std::string &name,
                               const std::string &reason)
{
  TRACE_NO_INDENT();
  auto        h = hiscores.begin();
  std::string hiscore_name;

  hiscore_name = name;

  while (h != hiscores.end()) {
    if (score > h->score) {
      hiscores.insert(h, HiScore(hiscore_name, reason, current_date(), score, level_num));

      hiscores.resize(HiScore::max);

      DBG("Save hiscore config");
      game_save_config(g);
      return;
    }

    h++;
  }
}

bool HiScores::is_new_hiscore(int score)
{
  TRACE_NO_INDENT();
  auto h = hiscores.begin();

  if (! score) {
    //
    // Poor player.
    //
    return false;
  }

  while (h != hiscores.end()) {
    if (score > h->score) {
      return true;
    }
    h++;
  }

  return false;
}

bool HiScores::is_new_highest_hiscore(int score)
{
  auto h = hiscores.begin();

  if (! score) {
    //
    // Poor player.
    //
    return false;
  }

  while (h != hiscores.end()) {
    return score > h->score;
  }
  return false;
}

const char *HiScores::place_str(int score)
{
  const char *which[ HiScore::max_displayed ] = {
      "first", "second", "third", "fourth", "fifth", "sixth", "seventh", "eighth", "ninth", "tenth",
  };

  if (! score) {
    //
    // Poor player.
    //
    return ("");
  }

  auto h = hiscores.begin();

  while (h != hiscores.end()) {
    if (score > h->score) {
      return (which[ h - hiscores.begin() ]);
    }
    h++;
  }
  return ("");
}

std::istream &operator>>(std::istream &in, Bits< HiScore & > my)
{
  TRACE_NO_INDENT();
  in >> bits(my.t.name);
  in >> bits(my.t.reason);
  in >> bits(my.t.when);
  in >> bits(my.t.score);
  in >> bits(my.t.levels_completed);
  DBG("Read Hiscore: who:%s score:%d demise:%s when:%s", my.t.name.c_str(), my.t.score, my.t.reason.c_str(),
      my.t.when.c_str());
  return in;
}

std::ostream &operator<<(std::ostream &out, Bits< const HiScore & > const my)
{
  TRACE_NO_INDENT();
  out << bits(my.t.name);
  out << bits(my.t.reason);
  out << bits(my.t.when);
  out << bits(my.t.score);
  out << bits(my.t.levels_completed);
  DBG("Saved Hiscore: who:%s score:%d demise:%s when:%s", my.t.name.c_str(), my.t.score, my.t.reason.c_str(),
      my.t.when.c_str());
  return out;
}

std::ostream &operator<<(std::ostream &out, Bits< HiScore & > const my)
{
  TRACE_NO_INDENT();
  out << bits(my.t.name);
  out << bits(my.t.reason);
  out << bits(my.t.when);
  out << bits(my.t.score);
  out << bits(my.t.levels_completed);
  DBG("Saved Hiscore: who:%s score:%d demise:%s when:%s", my.t.name.c_str(), my.t.score, my.t.reason.c_str(),
      my.t.when.c_str());
  return out;
}

std::istream &operator>>(std::istream &in, Bits< HiScores & > my)
{
  TRACE_NO_INDENT();
  my.t.hiscores.resize(0);
  in >> bits(my.t.hiscores);

  return in;
}

std::ostream &operator<<(std::ostream &out, Bits< const HiScores & > const my)
{
  TRACE_NO_INDENT();
  out << bits(my.t.hiscores);
  return out;
}
