//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_tps.hpp"

bool templates_init(void)
{
  TRACE_NO_INDENT();

  /* begin shell marker1 */
  /* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool tp_load" | awk '{print $2}' | cut -d'(' -f1 ) */
  /* shell do */
  /* shell echo "  if (!$i()) { return false; }" */
  /* shell done */
  if (! tp_load_barrel()) {
    return false;
  }
  if (! tp_load_pillar()) {
    return false;
  }
  if (! tp_load_brazier()) {
    return false;
  }
  if (! tp_load_grass()) {
    return false;
  }
  if (! tp_load_exit()) {
    return false;
  }
  if (! tp_load_chasm()) {
    return false;
  }
  if (! tp_load_floor()) {
    return false;
  }
  if (! tp_load_secret_door()) {
    return false;
  }
  if (! tp_load_foliage()) {
    return false;
  }
  if (! tp_load_smoke()) {
    return false;
  }
  if (! tp_load_wall()) {
    return false;
  }
  if (! tp_load_door()) {
    return false;
  }
  if (! tp_load_water()) {
    return false;
  }
  if (! tp_load_bridge()) {
    return false;
  }
  if (! tp_load_steam()) {
    return false;
  }
  if (! tp_load_entrance()) {
    return false;
  }
  if (! tp_load_rock()) {
    return false;
  }
  if (! tp_load_lava()) {
    return false;
  }
  if (! tp_load_fire()) {
    return false;
  }
  if (! tp_load_key()) {
    return false;
  }
  if (! tp_load_corridor()) {
    return false;
  }
  if (! tp_load_dirt()) {
    return false;
  }
  if (! tp_load_deep_water()) {
    return false;
  }
  if (! tp_load_trap()) {
    return false;
  }
  if (! tp_load_teleport()) {
    return false;
  }
  if (! tp_load_cursor_path()) {
    return false;
  }
  if (! tp_load_cursor_at()) {
    return false;
  }
  if (! tp_load_goblin()) {
    return false;
  }
  if (! tp_load_slime()) {
    return false;
  }
  if (! tp_load_ghost()) {
    return false;
  }
  if (! tp_load_level_curr()) {
    return false;
  }
  if (! tp_load_level_visited()) {
    return false;
  }
  if (! tp_load_level_across()) {
    return false;
  }
  if (! tp_load_level_next()) {
    return false;
  }
  if (! tp_load_level_not_visited()) {
    return false;
  }
  if (! tp_load_level_final()) {
    return false;
  }
  if (! tp_load_level_down()) {
    return false;
  }
  if (! tp_load_treasure()) {
    return false;
  }
  if (! tp_load_potion()) {
    return false;
  }
  if (! tp_load_ghost_mob()) {
    return false;
  }
  if (! tp_load_goblin_mob()) {
    return false;
  }
  if (! tp_load_player()) {
    return false;
  }
  /* end shell marker1 */

  return true;
}
