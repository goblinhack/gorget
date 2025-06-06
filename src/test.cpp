//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_test.hpp"
#include "my_tests.hpp"
#include "my_thing.hpp"

#include <inttypes.h>
#include <map>
#include <vector>

/* clang-format off */
std::initializer_list< std::string > tests = {
    // clang-format off
    /* begin shell marker1 */
    /* shell for i in $(find . -name "*.cpp" | xargs grep -h "test_load(\"" | awk '{print $4}' | cut -d\" -f2) */
    /* shell do */
    /* shell echo "    \"$i\"", */
    /* shell done */
    "move",
  /* end shell marker1 */
};
/* clang-format on */

class Test
{
public:
  std::string name {};

  //
  // Callbacks
  //
  test_callback_t callback;

  Test(void);
  ~Test(void);
};

using Testidmap = std::vector< class Test * >;

static std::map< std::string, class Test * > test_name_map;

static uint8_t test_init_done;

Test::Test(void) { newptr(MTYPE_TP, this, "Test"); }

Test::~Test(void) { oldptr(MTYPE_TP, this); }

Testp test_find(const char *name_in)
{
  TRACE_NO_INDENT();

  std::string name(name_in);
  auto        result = test_name_map.find(name);

  if (unlikely(result != test_name_map.end())) {
    return result->second;
  }

  DIE("test_find: thing template %s not found", name_in);
  return nullptr;
}

bool test_init(void)
{
  TRACE_NO_INDENT();

  test_init_done = true;

  tests_init();

  return true;
}

void test_fini(void)
{
  TRACE_NO_INDENT();

  if (! test_init_done) {
    return;
  }
  test_init_done = false;

  for (auto &test : test_name_map) {
    delete test.second;
  }

  test_name_map.clear();
}

void test_callback_set(Testp test, test_callback_t callback)
{
  TRACE_NO_INDENT();
  if (! test) {
    ERR("no test for %s", __FUNCTION__);
    return;
  }
  test->callback = callback;
}

Testp test_load(const char *name_in)
{
  TRACE_NO_INDENT();

  std::string name(name_in);

  if (test_find(name_in)) {
    DIE("test_load: test name [%s] already loaded", name_in);
  }

  auto test  = new Test();
  test->name = name;

  auto result = test_name_map.insert(std::make_pair(name, test));
  if (! result.second) {
    DIE("Test insert name [%s] failed", name_in);
  }

  return test;
}
