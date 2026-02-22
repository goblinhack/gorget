//
// Copyright goblinhack@gmail.com
//

#ifndef MY_TPS_HPP_
#define MY_TPS_HPP_

auto templates_init() -> bool;

// clang-format off
/* begin shell marker1 */
/* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool tp_load" | sort | awk '{print $2}' | cut -d'(' -f1 ) */
/* shell do */
/* shell echo "bool $i();" */
/* shell done */
  /* end shell marker1 */

#endif
