//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

[[nodiscard]] static bool test_teleport_shove_mob(Gamep g, Testp t)
{
  TEST_LOG(t, "begin");
  TRACE_AND_INDENT();

  LevelNum level_num = 0;
  auto     w         = 8;
  auto     h         = 8;

  //
  // How the dungeon starts out, and how we expect it to change
  //
  std::string start
      = "xxxxxxxx"
        "x...C..x"
        "x...C..x"
        "x...C..x"
        "x@GTCT.x"
        "x...C..x"
        "x...C..x"
        "xxxxxxxx";
  std::string expect1
      = "xxxxxxxx"
        "x...C..x"
        "x...C..x"
        "x...C..x"
        "x.@TCTGx"
        "x...C..x"
        "x...C..x"
        "xxxxxxxx";

  //
  // Create the level and start playing
  //
  Levelp  l;
  Levelsp v = game_test_init(g, &l, level_num, w, h, start.c_str());

  //
  // The guts of the test
  //
  bool result = false;
  bool up     = false;
  bool down   = false;
  bool left   = false;
  bool right  = false;

  //
  // Move right and teleport
  //
  TEST_PROGRESS(t);
  {
    TEST_LOG(t, "move right");
    TRACE_AND_INDENT();
    up = down = left = right = false;
    right                    = true;

    if (! (result = player_move_request(g, up, down, left, right, false /* fire */))) {
      TEST_FAILED(t, "move fail");
      goto exit;
    }

    if (! game_wait_for_tick_to_finish(g, v, l)) {
      TEST_FAILED(t, "wait loop failed");
      goto exit;
    }

    if (! (result = level_match_contents(g, v, l, t, w, h, expect1.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }
  }

  TEST_ASSERT(t, game_tick_get(g, v) == 2, "final tick counter value");

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  game_cleanup(g);

  return result;
}

bool test_load_teleport_shove_mob(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("teleport_shove_mob");

  // begin sort marker1 {
  test_callback_set(test, test_teleport_shove_mob);
  // end sort marker1 }

  return true;
}
