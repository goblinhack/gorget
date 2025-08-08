//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

static bool test_player_fall_chasm(Gamep g, Testp t)
{
  TEST_LOG(t, "begin");
  TRACE_AND_INDENT();

  LevelNum level_num = 0;
  auto     w         = 7;
  auto     h         = 7;

  //
  // How the dungeon starts out, and how we expect it to change
  //
  std::string level1 // first level
      = "......."
        "......."
        "...C..."
        "..@C..."
        "...C..."
        "......."
        ".......";
  std::string expect1 // first level
      = "......."
        "......."
        "...C..."
        "...C..."
        "...C..."
        "......."
        ".......";
  std::string level2 // second level
      = "xxxxxxx"
        "xxxxxxx"
        "xxLLLxx"
        "xxLLLxx"
        "xxLLLxx"
        "xxxxxxx"
        "xxxxxxx";
  std::string expect2 // second level
      = "xxxxxxx"
        "xxxxxxx"
        "xxLLLxx"
        "xxL@Lxx"
        "xxLLLxx"
        "xxxxxxx"
        "xxxxxxx";

  //
  // Create the level and start playing
  //
  Levelp  l1;
  Levelp  l2;
  Levelsp v = game_test_init(g, &l1, level_num, w, h, level1.c_str());
  game_test_init_level(g, v, &l2, level_num + 1, w, h, level2.c_str());

  //
  // The guts of the test
  //
  bool result = false;
  bool up     = false;
  bool down   = false;
  bool left   = false;
  bool right  = false;

  bool   found_corpse = false;
  Thingp player       = nullptr;
  spoint p;

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
    TEST_LOG(t, "move right");
    TRACE_AND_INDENT();
    up = down = left = right = false;
    right                    = true;

    if (! (result = player_move_request(g, up, down, left, right))) {
      TEST_FAILED(t, "move failed");
      goto exit;
    }

    game_wait_for_tick_to_finish(g, v, l1);
  }

  //
  // Player should have fallen now
  //
  if (! (result = level_match_contents(g, v, l1, w, h, expect1.c_str()))) {
    TEST_FAILED(t, "unexpected contents");
    goto exit;
  }

  {
    if (! (result = level_match_contents(g, v, l2, w, h, expect2.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }
  }

  for (auto tries = 0; tries < 2; tries++) {
    TRACE_NO_INDENT();
    // level_dump(g, v, l, w, h);
    game_event_wait(g);
    game_wait_for_tick_to_finish(g, v, l2);
  }

  TEST_ASSERT(t, game_tick_get(g, v) == 3, "final tick counter value");

  //
  // Check player is dead when shoved into lava. It should be popped off the level.
  //
  {
    TRACE_NO_INDENT();
    TEST_LOG(t, "check player is dead when in lava");
    p            = player->at;
    found_corpse = false;

    FOR_ALL_THINGS_AT(g, v, l2, it, p)
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

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  levels_destroy(g, v);

  return result;
}

bool test_load_player_fall_chasm(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("player_fall_chasm");

  // begin sort marker1 {
  test_callback_set(test, test_player_fall_chasm);
  // end sort marker1 }

  return true;
}
