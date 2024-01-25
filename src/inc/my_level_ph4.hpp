//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once

#include "my_game_defs.hpp"
#include "my_level_data.hpp"
#include "my_level_ph3.hpp"
#include "my_sys.hpp"

class LevelPH4
{
public:
  LevelData data {};

  bool ok {};

  LevelPH4(const LevelPh3 &);

  void add_object_ids(const LevelPh3 &);
  void add_object_tiles(const LevelPh3 &);
};

LevelPH4 level_ph4(const LevelPh3 &);
