//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_tps.hpp"
/* clang-format off */

bool templates_init(void)
{
  TRACE_NO_INDENT();

  /* begin shell marker1 */
  /* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool tp_load" | awk '{print $2}' | cut -d'(' -f1 ) */
  /* shell do */
  /* shell echo "  if (!$i()) { return false; }" */
  /* shell done */
  if (! tp_load_player()) {
    return false;
  }
  if (! tp_load_cursor_path()) {
    return false;
  }
  if (! tp_load_cursor_at()) {
    return false;
  }
  if (! tp_load_key()) {
    return false;
  }
  if (! tp_load_exit()) {
    return false;
  }
  if (! tp_load_door()) {
    return false;
  }
  if (! tp_load_wall()) {
    return false;
  }
  if (! tp_load_floor()) {
    return false;
  }
  /* end shell marker1 */

  return true;
}
/* clang-format on */
