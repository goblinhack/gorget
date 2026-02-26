//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

[[nodiscard]] static auto test_open_unlocked_door(Gamep g, Testp t) -> bool
{
  TEST_LOG(t, "begin");
  TRACE();

  LevelNum const level_num = 0;
  auto           w         = 7;
  auto           h         = 7;

  //
  // How the dungeon starts out, and how we expect it to change
  //
  std::string const start
      = "xxxxxxx"
        "x...x.x"
        "x...x.x"
        "x.@.D.x"
        "x...x.x"
        "x...x.x"
        "xxxxxxx";
  std::string const expect1
      = "xxxxxxx"
        "x...x.x"
        "x...x.x"
        "x..@D.x"
        "x...x.x"
        "x...x.x"
        "xxxxxxx";
  std::string const expect2
      = "xxxxxxx"
        "x...x.x"
        "x...x.x"
        "x...@.x"
        "x...x.x"
        "x...x.x"
        "xxxxxxx";
  std::string const expect3
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
  Levelp  l = nullptr;
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
    TRACE();
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

  //
  // Move right again, open door
  //
  TEST_PROGRESS(t);
  {
    TEST_LOG(t, "move right open door");
    TRACE();

    if (! (result = player_move_request(g, up, down, left, right, false /* fire */))) {
      TEST_FAILED(t, "move failed");
      goto exit;
    }

    if (! game_wait_for_tick_to_finish(g, v, l)) {
      TEST_FAILED(t, "wait loop failed");
      goto exit;
    }

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
    TRACE();

    if (! (result = player_move_request(g, up, down, left, right, false /* fire */))) {
      TEST_FAILED(t, "move failed");
      goto exit;
    }

    if (! game_wait_for_tick_to_finish(g, v, l)) {
      TEST_FAILED(t, "wait loop failed");
      goto exit;
    }

    if (! (result = level_match_contents(g, v, l, t, w, h, expect3.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }
  }

  TEST_ASSERT(t, game_tick_get(g, v) == 4, "final tick counter value");

  TEST_PASSED(t);
exit:
  TRACE();
  game_cleanup(g);

  return result;
}

auto test_load_open_unlocked_door() -> bool
{
  TRACE();

  Testp test = test_load("open_unlocked_door");

  // begin sort marker1 {
  test_callback_set(test, test_open_unlocked_door);
  // end sort marker1 }

  return true;
}
