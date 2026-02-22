//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_tps.hpp"

auto templates_init() -> bool
{
  TRACE_NO_INDENT();

  // clang-format off
  /* begin shell marker1 */
  /* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool tp_load" | sort | awk '{print $2}' | cut -d'(' -f1 ) */
  /* shell do */
  /* shell echo "  if (!$i()) { return false; }" */
  /* shell done */
  /* end shell marker1 */
  // clang-format on

  return true;
}
