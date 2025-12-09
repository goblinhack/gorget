//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

static bool test_mob_shove_into_lava(Gamep g, Testp t)
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
        "..@gL.."
        "......."
        "......."
        ".......";
  std::string expect1
      = "......."
        "......."
        "......."
        "...@!.."
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

  spoint  p;
  bool    found_it = false;
  ThingId mob_id   = 0;
  Thingp  player   = nullptr;

  //
  // Push the mob into lava
  //
  TEST_LOG(t, "push mob into lava");
  TRACE_AND_INDENT();
  up = down = left = right = false;
  right                    = true;

  //
  // Find the player
  //
  TEST_PROGRESS(t);
  {
    TRACE_NO_INDENT();
    player = thing_player(g);
    if (! player) {
      TEST_FAILED(t, "no player");
      goto exit;
    }
  }

  //
  // Find the mob before shoving it via the player
  //
  TEST_PROGRESS(t);
  {
    TRACE_NO_INDENT();
    p        = thing_at(player) + spoint(1, 0);
    found_it = false;
    FOR_ALL_THINGS_AT(g, v, l, it, p)
    {
      if (thing_is_mob(it)) {
        found_it = true;
        mob_id   = it->id;
        break;
      }
    }
  }

  //
  // Move right, shoving the mob
  //
  TEST_PROGRESS(t);
  {
    TRACE_NO_INDENT();
    if (! (result = player_move_request(g, up, down, left, right, false /* fire */))) {
      TEST_FAILED(t, "move failed");
      goto exit;
    }
  }

  //
  // Wait for the end of tick
  //
  TEST_PROGRESS(t);
  {
    TRACE_NO_INDENT();
    if (! game_wait_for_tick_to_finish(g, v, l)) {
      TEST_FAILED(t, "wait loop failed");
      goto exit;
    }
  }

  //
  // Check the level contents
  //
  TEST_PROGRESS(t);
  {
    TRACE_NO_INDENT();
    if (! (result = level_match_contents(g, v, l, t, w, h, expect1.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }
  }

  //
  // Check mob is dead when shoved into lava. It should be popped off the level.
  //
  TEST_PROGRESS(t);
  {
    TRACE_NO_INDENT();
    TEST_LOG(t, "check mob is dead when shoved into lava");
    p        = thing_at(player) + spoint(1, 0);
    found_it = false;

    FOR_ALL_THINGS_AT(g, v, l, it, p)
    {
      if (thing_is_mob(it)) {
        found_it = true;
        break;
      }
    }

    if (found_it) {
      TEST_FAILED(t, "found mob, but it should have been popped");
      goto exit;
    }
  }

  //
  // Check the mob has been cleaned up
  //
  TEST_PROGRESS(t);
  {
    TRACE_NO_INDENT();
    if (thing_find_optional(g, v, mob_id)) {
      TEST_FAILED(t, "found mob, but it should have been freed");
      goto exit;
    }
  }

  //
  // Check the tick is as expected
  //
  TEST_PROGRESS(t);
  {
    TEST_ASSERT(t, game_tick_get(g, v) == 2, "final tick counter value");
  }

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  game_cleanup(g);

  return result;
}

bool test_load_mob_shove_into_lava(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("mob_shove_into_lava");

  // begin sort marker1 {
  test_callback_set(test, test_mob_shove_into_lava);
  // end sort marker1 }

  return true;
}
