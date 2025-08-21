//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_tests.hpp"

bool tests_init(void)
{
  TRACE_NO_INDENT();

  /* begin shell marker1 */
  /* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool test_load" | awk '{print $2}' | cut -d'(' -f1 ) */
  /* shell do */
  /* shell echo "  if (!$i()) { return false; }" */
  /* shell done */
  if (! test_load_collision_large_fire_water()) {
    return false;
  }
  if (! test_load_jump_ok()) {
    return false;
  }
  if (! test_load_collision_fire_chasm()) {
    return false;
  }
  if (! test_load_collision_fire_water()) {
    return false;
  }
  if (! test_load_collision_mob()) {
    return false;
  }
  if (! test_load_collision_barrel()) {
    return false;
  }
  if (! test_load_player_fall_chasm()) {
    return false;
  }
  if (! test_load_collision_mob_water()) {
    return false;
  }
  if (! test_load_collision_wall()) {
    return false;
  }
  if (! test_load_collision_mob_lava()) {
    return false;
  }
  if (! test_load_collision_brazier_shove_ok()) {
    return false;
  }
  if (! test_load_collision_brazier_shove_chasm()) {
    return false;
  }
  if (! test_load_collision_grass()) {
    return false;
  }
  if (! test_load_collision_player_lava()) {
    return false;
  }
  if (! test_load_move_ok()) {
    return false;
  }
  if (! test_load_collision_brazier_shove_into_mob()) {
    return false;
  }
  if (! test_load_collision_fire_foliage()) {
    return false;
  }
  if (! test_load_collision_brazier_shove_fail()) {
    return false;
  }
  /* end shell marker1 */

  return true;
}
