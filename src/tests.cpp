//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_tests.hpp"

auto tests_init() -> bool
{
  TRACE_NO_INDENT();

  // clang-format off
  /* begin shell marker1 */
  /* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool test_load" | sort | awk '{print $2}' | cut -d'(' -f1 ) */
  /* shell do */
  /* shell echo "  if (!$i()) { return false; }" */
  /* shell done */
  /* end shell marker1 */
  // clang-format on

  return true;
}
