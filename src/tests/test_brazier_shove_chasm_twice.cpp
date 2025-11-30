//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"
#include "../my_thing_inlines.hpp"

static bool test_brazier_shove_chasm_twice(Gamep g, Testp t)
{
  TEST_LOG(t, "begin");
  TRACE_AND_INDENT();

  LevelNum level_num = 0;
  auto     w         = 7;
  auto     h         = 7;

  //
  // How the dungeon starts out, and how we expect it to change
  //
  std::string level1
      = "......."
        "......."
        "....C.."
        "..@BC.."
        "....C.."
        "......."
        ".......";
  std::string expect_1a // first shove
      = "......."
        "......."
        "....C.."
        "..@;;.."
        "....C.."
        "......."
        ".......";
  std::string expect_1b // second shove
      = "......."
        "......."
        "....C.."
        "..@.C.."
        "....C.."
        "......."
        ".......";
  std::string level2
      = "......."
        "......."
        "....C.."
        "....C.."
        "....C.."
        "......."
        ".......";
  std::string expect2
      = "......."
        "......."
        "....C.."
        "....C.."
        "....C.."
        "......."
        ".......";
  std::string level3
      = "......."
        "......."
        "......."
        "......."
        "......."
        "......."
        ".......";
  std::string expect3
      = "......."
        "......."
        "......."
        "....B.."
        "......."
        "......."
        ".......";

  //
  // Create the level and start playing
  //
  Levelp  l1;
  Levelp  l2;
  Levelp  l3;
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

  //
  // Bump into a brazier. It should be knocked over.
  //
  TEST_PROGRESS(t);
  {
    TEST_LOG(t, "move right");
    TRACE_AND_INDENT();
    up = down = left = right = false;
    right                    = true;

    if (! (result = player_move_request(g, up, down, left, right))) {
      TEST_FAILED(t, "move failed");
      goto exit;
    }

    game_wait_for_tick_to_finish(g, v, l1);

    if (! (result = level_match_contents(g, v, l1, t, w, h, expect_1a.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }

    auto player = thing_player(g);
    if (! player) {
      TEST_FAILED(t, "no player");
      goto exit;
    }

    //
    // Check the brazier is dead
    //
    TEST_LOG(t, "check brazier is dead");
    auto p        = player->at + spoint(1, 0);
    bool found_it = false;

    FOR_ALL_THINGS_AT(g, v, l1, it, p)
    {
      if (thing_is_brazier(it) && thing_is_dead(it)) {
        found_it = true;
        break;
      }
    }

    if (! found_it) {
      TEST_FAILED(t, "no dead brazier");
      goto exit;
    }
  }

  //
  // Second shove, we should be able to move the dead brazier
  //
  TEST_PROGRESS(t);
  {
    TEST_LOG(t, "move right");
    TRACE_AND_INDENT();
    up = down = left = right = false;
    right                    = true;

    if (! (result = player_move_request(g, up, down, left, right))) {
      TEST_FAILED(t, "move failed");
      goto exit;
    }
  }

  TEST_PROGRESS(t);
  for (auto tries = 0; tries < 10; tries++) {
    TEST_LOG(t, "try: %d", tries);
    TRACE_NO_INDENT();
    // level_dump(g, v, l, w, h);
    game_event_wait(g);
    game_wait_for_tick_to_finish(g, v, l1);
  }

  TEST_PROGRESS(t);
  {
    if (! (result = level_match_contents(g, v, l1, t, w, h, expect_1b.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }

    auto player = thing_player(g);
    if (! player) {
      TEST_FAILED(t, "no player");
      goto exit;
    }
  }

  TEST_ASSERT(t, game_tick_get(g, v) == 11, "final tick counter value");

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

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  game_cleanup(g);

  return result;
}

bool test_load_brazier_shove_chasm_twice(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("brazier_shove_chasm_twice");

  // begin sort marker1 {
  test_callback_set(test, test_brazier_shove_chasm_twice);
  // end sort marker1 }

  return true;
}
