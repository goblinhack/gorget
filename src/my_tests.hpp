//
// Copyright goblinhack@gmail.com
//

#ifndef MY_TESTS_HPP_
#define MY_TESTS_HPP_

extern auto tests_init() -> bool;

// clang-format off
/* begin shell marker1 */
/* shell for i in $(find . -name "*.cpp" | xargs grep -h "^bool test_load" | sort | awk '{print $2}' | cut -d'(' -f1 ) */
/* shell do */
/* shell echo "extern bool $i();" */
/* shell done */
  /* end shell marker1 */
#endif // _MY_TESTS_HPP_
