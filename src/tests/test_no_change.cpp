//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

[[nodiscard]] static bool test_no_change(Gamep g, Testp t)
{
  TEST_LOG(t, "begin");
  TRACE_AND_INDENT();

  LevelNum const level_num = 0;
  auto           w         = 7;
  auto           h         = 7;

  //
  // How the dungeon starts out, and how we expect it to change
  //
  std::string const start
      = "xxxxxxx"
        "xbB=C#x"
        "xW~,+sx"
        "x.@..`x"
        "x.k...x"
        "x|.Tt#x"
        "xxxxxxx";
  std::string const expect
      = "xxxxxxx"
        "xbB=C#x"
        "xW~,+sx"
        "x.@..`x"
        "x.k...x"
        "x|.Tt#x"
        "xxxxxxx";

  //
  // Create the level and start playing
  //
  Levelp  l;
  Levelsp v = game_test_init(g, &l, level_num, w, h, start.c_str());

  //
  // The guts of the test
  //
  bool result = false;

  //
  // Wait
  //
  TEST_PROGRESS(t);
  for (auto tries = 0; tries < 10; tries++) {
    TEST_LOG(t, "try: %d", tries);
    TRACE_NO_INDENT();
    TEST_ASSERT(t, game_event_wait(g), "failed to wait");
    if (! game_wait_for_tick_to_finish(g, v, l)) {
      TEST_FAILED(t, "wait loop failed");
      goto exit;
    }
  }

  if (! (result = level_match_contents(g, v, l, t, w, h, expect.c_str()))) {
    TEST_FAILED(t, "unexpected contents");
    goto exit;
  }

  TEST_ASSERT(t, game_tick_get(g, v) == 10, "final tick counter value");

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  game_cleanup(g);

  return result;
}

bool test_load_no_change()
{
  TRACE_NO_INDENT();

  Testp test = test_load("no_change");

  // begin sort marker1 {
  test_callback_set(test, test_no_change);
  // end sort marker1 }

  return true;
}
