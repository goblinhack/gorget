//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

[[nodiscard]] auto level_type(LevelNum level_num) -> LevelType
{
  TRACE();

  switch (level_num) {
    case 18 : return LEVEL_TYPE_BOSS1;
    case 38 : return LEVEL_TYPE_BOSS2;
    case 58 : return LEVEL_TYPE_BOSS3;
    case 78 : return LEVEL_TYPE_BOSS4;
    case 98 : return LEVEL_TYPE_BOSS5;
    default : break;
  }
  return LEVEL_TYPE_NORMAL;
}

[[nodiscard]] auto level_is_boss_level(Gamep g, Levelsp v, Levelp l) -> bool
{
  TRACE();

  switch (l->level_num + 1) {
    case 18 : return true;
    case 38 : return true;
    case 58 : return true;
    case 78 : return true;
    case 98 : return true;
    default : break;
  }
  return false;
}
