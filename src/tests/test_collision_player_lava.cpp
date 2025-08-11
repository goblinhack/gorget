//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

static bool test_collision_player_lava(Gamep g, Testp t)
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
        "..@L..."
        "......."
        "......."
        ".......";
  std::string expect1
      = "......."
        "......."
        "......."
        "...@..." // is a corpse
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

  spoint p;
  bool   found_corpse = false;
  Thingp player       = nullptr;

  //
  // Move into the lava. The player should die.
  //
  TEST_LOG(t, "move player into lava right");
  TRACE_AND_INDENT();
  up = down = left = right = false;
  right                    = true;

  //
  // Find the player
  //
  {
    TRACE_NO_INDENT();
    player = thing_player(g);
    if (! player) {
      TEST_FAILED(t, "no player");
      goto exit;
    }
  }

  //
  // Move right
  //
  {
    TRACE_NO_INDENT();
    if (! (result = player_move_request(g, up, down, left, right))) {
      TEST_FAILED(t, "move failed");
      goto exit;
    }
  }

  //
  // Wait for the end of tick
  //
  {
    TRACE_NO_INDENT();
    game_wait_for_tick_to_finish(g, v, l);
  }

  //
  // Check the level contents
  //
  {
    TRACE_NO_INDENT();
    if (! (result = level_match_contents(g, v, l, w, h, expect1.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }
  }

  for (auto tries = 0; tries < 3; tries++) {
    TRACE_NO_INDENT();
    game_event_wait(g);
    game_wait_for_tick_to_finish(g, v, l);
  }

  //
  // Check player is dead when shoved into lava. It should be popped off the level.
  //
  {
    TRACE_NO_INDENT();
    TEST_LOG(t, "check player is dead when in lava");
    p            = player->at;
    found_corpse = false;

    FOR_ALL_THINGS_AT(g, v, l, it, p)
    {
      if (thing_is_player(it) && thing_is_corpse(it)) {
        found_corpse = true;
        break;
      }
    }

    if (! found_corpse) {
      TEST_FAILED(t, "did not find player as a corpse");
      goto exit;
    }
  }

  //
  // Check the tick is as expected
  //
  {
    TEST_ASSERT(t, game_tick_get(g, v) == 4, "final tick counter value");
  }

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  game_cleanup(g);

  return result;
}

bool test_load_collision_player_lava(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("collision_player_lava");

  // begin sort marker1 {
  test_callback_set(test, test_collision_player_lava);
  // end sort marker1 }

  return true;
}
