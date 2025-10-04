//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

static bool test_door_secret(Gamep g, Testp t)
{
  TEST_LOG(t, "begin");
  TRACE_AND_INDENT();

  LevelNum level_num = 0;
  auto     w         = 7;
  auto     h         = 7;

  //
  // How the dungeon starts out, and how we expect it to change
  //
  std::string start
      = "xxxxxxx"
        "x...x.x"
        "x...x.x"
        "x.@.s.x"
        "x...x.x"
        "x...x.x"
        "xxxxxxx";
  std::string expect1
      = "xxxxxxx"
        "x...x.x"
        "x...x.x"
        "x..@s.x"
        "x...x.x"
        "x...x.x"
        "xxxxxxx";
  std::string expect2
      = "xxxxxxx"
        "x...x.x"
        "x...x.x"
        "x...@.x"
        "x...x.x"
        "x...x.x"
        "xxxxxxx";
  std::string expect3
      = "xxxxxxx"
        "x...x.x"
        "x...x.x"
        "x....@x"
        "x...x.x"
        "x...x.x"
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
  bool up     = false;
  bool down   = false;
  bool left   = false;
  bool right  = false;

  //
  // Move right, collecting key
  //
  TEST_PROGRESS(t);
  {
    TEST_LOG(t, "move right, collecting key");
    TRACE_AND_INDENT();
    up = down = left = right = false;
    right                    = true;

    if (! (result = player_move_request(g, up, down, left, right))) {
      TEST_FAILED(t, "move fail");
      goto exit;
    }

    game_wait_for_tick_to_finish(g, v, l);

    if (! (result = level_match_contents(g, v, l, t, w, h, expect1.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }
  }

  //
  // Move right again, open door
  //
  TEST_PROGRESS(t);
  {
    TEST_LOG(t, "move right open door");
    TRACE_AND_INDENT();

    if (! (result = player_move_request(g, up, down, left, right))) {
      TEST_FAILED(t, "move failed");
      goto exit;
    }

    game_wait_for_tick_to_finish(g, v, l);

    if (! (result = level_match_contents(g, v, l, t, w, h, expect2.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }
  }

  //
  // Move right into room
  //
  TEST_PROGRESS(t);
  {
    TEST_LOG(t, "move right into room");
    TRACE_AND_INDENT();

    if (! (result = player_move_request(g, up, down, left, right))) {
      TEST_FAILED(t, "move failed");
      goto exit;
    }

    game_wait_for_tick_to_finish(g, v, l);

    if (! (result = level_match_contents(g, v, l, t, w, h, expect3.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }
  }

  TEST_ASSERT(t, game_tick_get(g, v) == 3, "final tick counter value");

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  game_cleanup(g);

  return result;
}

bool test_load_door_secret(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("door_secret");

  // begin sort marker1 {
  test_callback_set(test, test_door_secret);
  // end sort marker1 }

  return true;
}
