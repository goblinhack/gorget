//
// Copyright goblinhack@gmail.com
//

#include "my_console.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_sprintf.hpp"
#include "my_test.hpp"
#include "my_tests.hpp"
#include "my_time.hpp"
#include "my_ui.hpp"

#include <map>

/* clang-format off */
std::initializer_list< std::string > tests = {
    /* begin shell marker1 */
    /* shell for i in $(find . -name "*.cpp" | xargs grep -h "test_load(\"" | sort | awk '{print $4}' | cut -d\" -f2) */
    /* shell do */
    /* shell echo "    \"$i\"", */
    /* shell done */
    "alloc_free_monsts",
    "alloc_free_walls",
    "barrel_explosion",
    "barrel",
    "brazier_shove_chasm_twice",
    "brazier_shove_chasm",
    "brazier_shove_fail",
    "brazier_shove_into_mob",
    "brazier_shove_ok",
    "bridge_on_fire_over_lava",
    "bridge_on_fire",
    "door_secret",
    "fire_on_water",
    "fire_over_chasm",
    "foliage_on_fire",
    "jump_ok",
    "jump_truncated",
    "large_fire_water",
    "mob_shove_into_lava",
    "mob_shove_ok",
    "mob_water",
    "move_ok",
    "no_change",
    "open_locked_door_fail",
    "open_locked_door_success",
    "open_unlocked_door",
    "path_astar",
    "path_dmap_reverse",
    "path_dmap",
    "player_fall_chasm_into_lava",
    "player_fall_chasm_twice_into_lava",
    "player_fall_chasm_twice",
    "player_fall_while_on_fire",
    "player_in_steam",
    "player_lava",
    "player_on_fire_move_into_water",
    "player_on_fire",
    "projectile_barrel_explosion",
    "projectile_border_turns_to_lava",
    "projectile_locked_door",
    "projectile_mob",
    "projectile_over_water",
    "projectile_rock_turns_to_lava",
    "projectile_secret_door",
    "projectile_unlocked_door",
    "projectile_wall_turns_to_lava",
    "projectile",
    "save_load",
    "slots",
    "teleport_chasm",
    "teleport_shove_barrel",
    "teleport_shove_brazier",
    "teleport_shove_mob",
    "teleport",
    "trampled_grass",
    "wall",
  /* end shell marker1 */
};
/* clang-format on */

class Test
{
public:
  std::string name;

  //
  // Callbacks
  //
  test_callback_t callback;

  Test(void);
  ~Test(void);
};

using Testidmap = std::vector< class Test * >;

//
// Use std::map so the test names are sorted
//
static std::map< std::string, class Test * > test_name_map;

static bool test_init_done;

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

void test_init(void)
{
  TRACE_NO_INDENT();

  test_init_done = 1u;

  tests_init();
}

void test_fini(void)
{
  TRACE_NO_INDENT();

  if (static_cast<unsigned int>(test_init_done) == 0U) {
    return;
  }
  test_init_done = 0u;

  for (auto &test : test_name_map) {
    delete test.second;
  }

  test_name_map.clear();
}

void test_callback_set(Testp test, test_callback_t callback)
{
  TRACE_NO_INDENT();
  if (test == nullptr) {
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

  if (test_find(name_in) != nullptr) {
    CROAK("test_load: test name [%s] already loaded", name_in);
  }

  auto *test = new Test();
  test->name = name;

  auto result = test_name_map.insert(std::make_pair(name, test));
  if (! result.second) {
    CROAK("Test insert name [%s] failed", name_in);
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
  if (TERM_HEIGHT == 0) {
    TERM_HEIGHT = TERM_HEIGHT_DEF;
  }
  if (TERM_WIDTH == 0) {
    TERM_WIDTH = TERM_WIDTH_DEF;
  }

  term_log("Running tests\n");

  for (auto &test : test_name_map) {

    bool result  = false;
    bool skipped = false;

    //
    // Test name
    //
    auto  name = "test_" + test.first;
    auto *t    = test.second;
    auto  pre  = string_sprintf("Running %-70s", name.c_str());

    //
    // Skip the test if needed
    //
    if (! g_opt_test_name_filter.empty()) {
      if (name != g_opt_test_name_filter) {
        skipped = true;
        continue;
      }
    }

    g_opt_test_current = name;

    //
    // Preamble
    //
    if (! skipped) {
      LOG("Running test: %s", name.c_str());
      LOG("-------------------------------------------");
    }

    //
    // Run the test
    //
    auto started = time_ms();
    if (! skipped) {
      result = t->callback(g, t);
    }
    auto elapsed  = time_ms() - started;
    auto how_long = string_sprintf("(took %.2f secs, %u ms)", (float) elapsed / 1000.0, elapsed);

    //
    // Print the timestamp
    //
    char buf[ MAXLONGSTR ];
    buf[ 0 ] = '\0';
    get_timestamp(buf, MAXLONGSTR);

#ifdef _GITHUB_BUILD_
    std::string out(buf);

    //
    // Test preamble. We print this after the test has ran to avoid messing up the output.
    //
    out += pre;

    if (skipped) {
      out += "skipped";
    } else if (result) {
      passed++;
      out += "OK ";
      out += how_long;

      LOG("Passed %s", how_long.c_str());
    } else {
      failed++;
      out += "FAILED";
      LOG("Failed");
    }
    printf("%s\n", out.c_str());
#else
    term_log(buf);
    //
    // Test preamble. We print this after the test has ran to avoid messing up the output.
    //
    term_log(pre.c_str());

    if (skipped) {
      term_log("%%fg=yellow$skipped%%fg=reset$\n");
    } else if (result) {
      passed++;
      term_log("%%fg=green$OK%%fg=reset$ ");
      term_log(how_long.c_str());
      term_log("\n");
      LOG("Passed %s", how_long.c_str());
    } else {
      failed++;
      term_log("%%fg=red$FAILED%%fg=reset$\n");
      LOG("Failed");
    }
#endif

    if (! skipped) {
      LOG("-");
    }

    //
    // github output seems to be buffered.
    //
    fflush(stdout);
    fflush(stderr);
  }

  test_fini();

  g_opt_tests = false;

  if (failed != 0) {
    CON("Results: %d passed, %d failed", passed, failed);
    exit(1);
  } else {
    CON("All tests passed");
    DIE_CLEAN("done");
  }
}
