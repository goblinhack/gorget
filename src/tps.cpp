//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level_data.hpp"
#include "my_tps.hpp"

bool templates_init(void)
{
  TRACE_NO_INDENT();

  /* begin shell marker1 */
  /* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool tp_load" | awk '{print $2}' | cut -d'(' -f1 ) */
  /* shell do */
  /* shell echo "  if (!$i()) { return false; }" */
  /* shell done */
  if (! tp_load_cursor()) {
    return false;
  }
  if (! tp_load_player()) {
    return false;
  }
  if (! tp_load_dungeon_door()) {
    return false;
  }
  if (! tp_load_dungeon_floor()) {
    return false;
  }
  if (! tp_load_dungeon_entrance()) {
    return false;
  }
  if (! tp_load_key()) {
    return false;
  }
  if (! tp_load_dungeon_exit()) {
    return false;
  }
  if (! tp_load_dungeon_wall()) {
    return false;
  }
  /* end shell marker1 */

  return true;
}
