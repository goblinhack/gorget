//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_tests.hpp"

bool tests_init(void)
{
  TRACE_NO_INDENT();

  // clang-format off
  /* begin shell marker1 */
  /* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool test_load" | sort | awk '{print $2}' | cut -d'(' -f1 ) */
  /* shell do */
  /* shell echo "  if (!$i()) { return false; }" */
  /* shell done */
  if (!test_load_barrel_explosion()) { return false; }
  if (!test_load_barrel()) { return false; }
  if (!test_load_brazier_shove_chasm()) { return false; }
  if (!test_load_brazier_shove_fail()) { return false; }
  if (!test_load_brazier_shove_into_mob()) { return false; }
  if (!test_load_brazier_shove_ok()) { return false; }
  if (!test_load_bridge_on_fire_over_lava()) { return false; }
  if (!test_load_bridge_on_fire()) { return false; }
  if (!test_load_door_secret()) { return false; }
  if (!test_load_fire_on_water()) { return false; }
  if (!test_load_fire_over_chasm()) { return false; }
  if (!test_load_foliage_on_fire()) { return false; }
  if (!test_load_jump_ok()) { return false; }
  if (!test_load_jump_truncated()) { return false; }
  if (!test_load_large_fire_water()) { return false; }
  if (!test_load_mob_lava()) { return false; }
  if (!test_load_mob_water()) { return false; }
  if (!test_load_mob()) { return false; }
  if (!test_load_move_ok()) { return false; }
  if (!test_load_open_door()) { return false; }
  if (!test_load_player_fall_chasm_into_lava()) { return false; }
  if (!test_load_player_fall_chasm_twice_into_lava()) { return false; }
  if (!test_load_player_fall_chasm_twice()) { return false; }
  if (!test_load_player_fall_while_on_fire()) { return false; }
  if (!test_load_player_lava()) { return false; }
  if (!test_load_player_on_fire_move_into_water()) { return false; }
  if (!test_load_player_on_fire()) { return false; }
  if (!test_load_save_load()) { return false; }
  if (!test_load_teleport()) { return false; }
  if (!test_load_trampled_grass()) { return false; }
  if (!test_load_wall()) { return false; }
  /* end shell marker1 */
  // clang-format on

  return true;
}
