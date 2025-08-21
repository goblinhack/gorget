//
// Copyright goblinhack@gmail.com
//

#include "my_console.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_test.hpp"
#include "my_tests.hpp"
#include "my_time.hpp"
#include "my_ui.hpp"

#include <map>

/* clang-format off */
std::initializer_list< std::string > tests = {
    // clang-format off
    /* begin shell marker1 */
    /* shell for i in $(find . -name "*.cpp" | xargs grep -h "test_load(\"" | awk '{print $4}' | cut -d\" -f2) */
    /* shell do */
    /* shell echo "    \"$i\"", */
    /* shell done */
    "collision_large_fire_water",
    "jump_ok",
    "collision_fire_chasm",
    "collision_fire_water",
    "collision_mob",
    "collision_barrel",
    "player_fall_chasm",
    "collision_mob_water",
    "collision_wall",
    "collision_mob_lava",
    "collision_brazier_shove_ok",
    "collision_brazier_shove_chasm",
    "collision_grass",
    "collision_player_lava",
    "move_ok",
    "collision_brazier_shove_into_mob",
    "collision_fire_foliage",
    "collision_brazier_shove_fail",
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

static std::unordered_map< std::string, class Test * > test_name_map;

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

  LOG("Load test '%s'", name_in);

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

const char *test_name(Testp test)
{
  TRACE_NO_INDENT();

  return test->name.c_str();
}

void tests_run(Gamep g)
{
  TRACE_NO_INDENT();

  int passed = 0;
  int failed = 0;

  //
  // For tests that create a widget, we need some defaults
  //
  if (! TERM_HEIGHT) {
    TERM_HEIGHT = TERM_HEIGHT_DEF;
  }
  if (! TERM_WIDTH) {
    TERM_WIDTH = TERM_WIDTH_DEF;
  }

  for (auto &test : test_name_map) {

    bool result  = false;
    bool skipped = false;

    //
    // Test name
    //
    auto name = test.first;
    auto t    = test.second;
    auto pre  = string_sprintf("Test %-70s", name.c_str());

    //
    // Preamble
    //
    LOG("Running test: %s", name.c_str());
    LOG("------------------------------");

    //
    // Skip the test if needed
    //
    if (g_opt_test_name != "") {
      if (name != g_opt_test_name) {
        skipped = true;
      }
    }

    //
    // Run the test
    //
    if (! skipped) {
      result = t->callback(g, t);
    }

    //
    // Print the timestamp
    //
    char buf[ MAXLONGSTR ];
    buf[ 0 ] = '\0';
    get_timestamp(buf, MAXLONGSTR);
    term_log(buf);

    //
    // Test preamble. We print this after the test has ran to avoid messing up the output.
    //
    term_log(pre.c_str());

    if (skipped) {
      term_log("%%fg=yellow$skipped%%fg=reset$\n");
      LOG("Skipped");
    } else if (result) {
      passed++;
      term_log("%%fg=green$OK%%fg=reset$\n");
      LOG("Passed");
    } else {
      failed++;
      term_log("%%fg=red$FAILED%%fg=reset$\n");
      LOG("Failed");
    }
    LOG("-");
  }

  for (auto &test : test_name_map) {
    delete test.second;
  }

  if (failed) {
    CON("Results: %d passed, %d failed", passed, failed);
    exit(1);
  } else {
    CON("All tests passed");
    DIE_CLEAN("done");
  }
}
