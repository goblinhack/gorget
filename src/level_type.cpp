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
    case LEVEL_NUM_BOSS_1 : return LEVEL_TYPE_BOSS1;
    case LEVEL_NUM_BOSS_2 : return LEVEL_TYPE_BOSS2;
    case LEVEL_NUM_BOSS_3 : return LEVEL_TYPE_BOSS3;
    case LEVEL_NUM_BOSS_4 : return LEVEL_TYPE_BOSS4;
    case LEVEL_NUM_BOSS_5 : return LEVEL_TYPE_BOSS5;
    default :               break;
  }
  return LEVEL_TYPE_NORMAL;
}

[[nodiscard]] auto level_type_is_boss_level(LevelNum level_num) -> bool
{
  TRACE();

  switch (level_num) {
    case LEVEL_NUM_BOSS_1 : return true;
    case LEVEL_NUM_BOSS_2 : return true;
    case LEVEL_NUM_BOSS_3 : return true;
    case LEVEL_NUM_BOSS_4 : return true;
    case LEVEL_NUM_BOSS_5 : return true;
    default :               break;
  }
  return false;
}

[[nodiscard]] auto level_is_boss_level(Gamep g, Levelsp v, Levelp l) -> bool
{
  TRACE();

  if (! l) {
    ERR("no level pointer");
    return false;
  }

  switch (l->level_num + 1) {
    case LEVEL_NUM_BOSS_1 : return true;
    case LEVEL_NUM_BOSS_2 : return true;
    case LEVEL_NUM_BOSS_3 : return true;
    case LEVEL_NUM_BOSS_4 : return true;
    case LEVEL_NUM_BOSS_5 : return true;
    default :               break;
  }
  return l->is_boss_level;
}

auto level_is_boss_level_set(Gamep g, Levelsp v, Levelp l, bool val) -> void
{
  TRACE();

  if (! l) {
    ERR("no level pointer");
    return;
  }

  l->is_boss_level = val;
}

[[nodiscard]] auto level_is_boss_final_level(Gamep g, Levelsp v, Levelp l) -> bool
{
  TRACE();

  if (! l) {
    ERR("no level pointer");
    return false;
  }

  return l->is_boss_final_level;
}

auto level_is_boss_final_level_set(Gamep g, Levelsp v, Levelp l, bool val) -> void
{
  TRACE();

  if (! l) {
    ERR("no level pointer");
    return;
  }

  l->is_boss_final_level = val;
}

[[nodiscard]] auto level_is_valid_grid_coord(int x, int y) -> bool
{
  TRACE();

  bool valid[ LEVEL_GRID_DOWN ][ LEVEL_GRID_ACROSS ] = {
      {true, true, true, true, true},     //
      {true, true, true, true, true},     //
      {true, true, true, true, true},     //
      {false, false, true, false, false}, //
      {true, true, true, true, true},     //
      {true, true, true, true, true},     //
      {true, true, true, true, true},     //
      {false, false, true, false, false}, //
      {true, true, true, true, true},     //
      {true, true, true, true, true},     //
      {true, true, true, true, true},     //
      {false, false, true, false, false}, //
      {true, true, true, true, true},     //
      {true, true, true, true, true},     //
      {true, true, true, true, true},     //
      {false, false, true, false, false}, //
      {true, true, true, true, true},     //
      {true, true, true, true, true},     //
      {true, true, true, true, true},     //
      {false, false, true, false, false}, //
  };

  return valid[ y ][ x ];
}
