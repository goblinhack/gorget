//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

static bool test_collision_wall(Gamep g, Testp t)
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
      = "......."
        "......."
        ".xxx..."
        ".x@x..."
        ".xxx..."
        "......."
        ".......";
  std::string expect = start;

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
  // Move right
  //
  {
    TEST_LOG(t, "move right");
    TRACE_AND_INDENT();
    up = down = left = right = false;
    right                    = true;

    if (! (result = player_move_request(g, up, down, left, right))) {
      TEST_FAILED(t, "move failed");
      goto exit;
    }

    game_wait_for_tick_to_finish(g, v, l);

    if (! (result = level_match_contents(g, v, l, w, h, expect.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }
  }

  //
  // Move down
  //
  {
    TEST_LOG(t, "move down");
    TRACE_AND_INDENT();
    up = down = left = right = false;
    down                     = true;

    if (! (result = player_move_request(g, up, down, left, right))) {
      TEST_FAILED(t, "move failed");
      goto exit;
    }

    game_wait_for_tick_to_finish(g, v, l);

    if (! (result = level_match_contents(g, v, l, w, h, expect.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }
  }

  //
  // Move left
  //
  {
    TEST_LOG(t, "move left");
    TRACE_AND_INDENT();
    up = down = left = right = false;
    left                     = true;

    if (! (result = player_move_request(g, up, down, left, right))) {
      TEST_FAILED(t, "move failed");
      goto exit;
    }

    game_wait_for_tick_to_finish(g, v, l);

    if (! (result = level_match_contents(g, v, l, w, h, expect.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }
  }

  //
  // Move up
  //
  {
    TEST_LOG(t, "move up");
    TRACE_AND_INDENT();
    up = down = left = right = false;
    up                       = true;

    if (! (result = player_move_request(g, up, down, left, right))) {
      TEST_FAILED(t, "move failed");
      goto exit;
    }

    game_wait_for_tick_to_finish(g, v, l);

    if (! (result = level_match_contents(g, v, l, w, h, expect.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }
  }

  TEST_ASSERT(t, game_tick_get(g, v) == 4, "final tick counter value");

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  levels_destroy(g, v);

  return result;
}

bool test_load_collision_wall(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("collision_wall");

  // begin sort marker1 {
  test_callback_set(test, test_collision_wall);
  // end sort marker1 }

  return true;
}
