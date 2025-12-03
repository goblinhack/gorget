//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"
#include "../my_thing_inlines.hpp"

static bool test_barrel(Gamep g, Testp t)
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
        "......."
        "..@b..."
        "......."
        "......."
        ".......";
  std::string expect1
      = "......."
        "......."
        "......."
        "...@b.."
        "......."
        "......."
        ".......";

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
  // Bump into a barrel. It should move and not be knocked over.
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

    if (! game_wait_for_tick_to_finish(g, v, l)) {
      TEST_FAILED(t, "wait loop failed");
      goto exit;
    }

    if (! (result = level_match_contents(g, v, l, t, w, h, expect1.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }

    auto player = thing_player(g);
    if (! player) {
      TEST_FAILED(t, "no player");
      goto exit;
    }

    //
    // Check the barrel is alive
    //
    TEST_LOG(t, "check barrel is alive");
    auto p        = player->at + spoint(1, 0);
    bool found_it = false;

    FOR_ALL_THINGS_AT(g, v, l, it, p)
    {
      if (thing_is_barrel(it) && ! thing_is_dead(it)) {
        found_it = true;
        break;
      }
    }

    if (! found_it) {
      TEST_FAILED(t, "no alive barrel");
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

bool test_load_barrel(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("barrel");

  // begin sort marker1 {
  test_callback_set(test, test_barrel);
  // end sort marker1 }

  return true;
}
