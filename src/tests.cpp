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
  if (! test_load_crush_grass()) {
    return false;
  }
  if (! test_load_move_ok()) {
    return false;
  }
  if (! test_load_move_obstacle()) {
    return false;
  }
  /* end shell marker1 */

  return true;
}
