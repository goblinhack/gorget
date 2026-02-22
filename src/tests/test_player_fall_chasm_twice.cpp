//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

[[nodiscard]] static auto test_player_fall_chasm_twice(Gamep g, Testp t) -> bool
{
  TEST_LOG(t, "begin");
  TRACE_AND_INDENT();

  LevelNum const level_num = 0;
  auto           w         = 7;
  auto           h         = 7;

  //
  // How the dungeon starts out, and how we expect it to change
  //
  std::string const level1 // first level
      = "......."
        "......."
        "...C..."
        "..@C..."
        "...C..."
        "......."
        ".......";
  std::string const expect1 // first level
      = "......."
        "......."
        "...C..."
        "...C..."
        "...C..."
        "......."
        ".......";
  std::string const level2 // second level
      = "......."
        "......."
        "...C..."
        "...C..."
        "...C..."
        "......."
        ".......";
  std::string const expect2 // second level
      = "......."
        "......."
        "...C..."
        "...C..."
        "...C..."
        "......."
        ".......";
  std::string const level3 // third level
      = "......."
        "......."
        "......."
        "......."
        "......."
        "......."
        ".......";
  std::string const expect3 // third level
      = "......."
        "......."
        "......."
        "...@..."
        "......."
        "......."
        ".......";

  //
  // Create the level and start playing
  //
  Levelp  l1 = nullptr;
  Levelp  l2 = nullptr;
  Levelp  l3 = nullptr;
  Levelsp v = game_test_init(g, &l1, level_num, w, h, level1.c_str());
  game_test_init_level(g, v, &l2, level_num + 1, w, h, level2.c_str());
  game_test_init_level(g, v, &l3, level_num + 2, w, h, level3.c_str());

  //
  // The guts of the test
  //
  bool result = false;
  bool up     = false;
  bool down   = false;
  bool left   = false;
  bool right  = false;

  Thingp player = nullptr;

  //
  // Find the player
  //
  TEST_PROGRESS(t);
  {
    TRACE_NO_INDENT();
    player = thing_player(g);
    if (player == nullptr) {
      TEST_FAILED(t, "no player");
      goto exit;
    }
  }

  //
  // Move right
  //
  TEST_PROGRESS(t);
  {
    TEST_LOG(t, "move right");
    TRACE_AND_INDENT();
    up = down = left = right = false;
    right                    = true;

    if (! (result = player_move_request(g, up, down, left, right, false /* fire */))) {
      TEST_FAILED(t, "move failed");
      goto exit;
    }

    TEST_ASSERT(t, game_wait_for_tick_to_finish(g, v, l1), "failed to wait for tick to finish");
  }

  if (compiler_unused) {
    TEST_PROGRESS(t);
    for (auto tries = 0; tries < 2; tries++) {
      TEST_LOG(t, "try: %d", tries);
      TRACE_NO_INDENT();
      // level_dump(g, v, l, w, h);
      TEST_ASSERT(t, game_event_wait(g), "failed to wait");
      TEST_ASSERT(t, game_wait_for_tick_to_finish(g, v, l1), "failed to wait for tick to finish");
    }
  }

  //
  // Player should have fallen all the way down now
  //
  TEST_PROGRESS(t);
  if (! (result = level_match_contents(g, v, l1, t, w, h, expect1.c_str()))) {
    TEST_FAILED(t, "unexpected contents");
    goto exit;
  }

  TEST_PROGRESS(t);
  {
    if (! (result = level_match_contents(g, v, l2, t, w, h, expect2.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }
  }

  TEST_PROGRESS(t);
  {
    if (! (result = level_match_contents(g, v, l3, t, w, h, expect3.c_str()))) {
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

auto test_load_player_fall_chasm_twice() -> bool
{
  TRACE_NO_INDENT();

  Testp test = test_load("player_fall_chasm_twice");

  // begin sort marker1 {
  test_callback_set(test, test_player_fall_chasm_twice);
  // end sort marker1 }

  return true;
}
