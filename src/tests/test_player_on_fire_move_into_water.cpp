//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"
#include "../my_thing_inlines.hpp"

static bool test_player_on_fire_move_into_water(Gamep g, Testp t)
{
  TEST_LOG(t, "begin");
  TRACE_AND_INDENT();

  LevelNum level_num = 0;
  auto     w         = 7;
  auto     h         = 7;

  //
  // How the dungeon starts out, and how we expect it to change
  //
  std::string level // first level
      = "......."
        "......."
        "...~..."
        "..@~..."
        "...~..."
        "......."
        ".......";
  std::string expect // first level
      = "......."
        "......."
        "...~..."
        "..!:..."
        "...~..."
        "......."
        ".......";

  //
  // Create the level and start playing
  //
  Levelp  l;
  Levelsp v = game_test_init(g, &l, level_num, w, h, level.c_str());

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
    if (! player) {
      TEST_FAILED(t, "no player");
      goto exit;
    }
  }

  //
  // Spawn fire on the player
  //
  TEST_PROGRESS(t);
  {
    thing_spawn(g, v, l, tp_first(is_fire), player->at);
    // level_dump(g, v, l, w, h);
    game_event_wait(g);
    if (! game_wait_for_tick_to_finish(g, v, l)) {
      TEST_FAILED(t, "wait loop failed");
      goto exit;
    }

    TEST_ASSERT(t, thing_is_burning(player), "player is not burning");
    TEST_ASSERT(t, ! thing_is_dead(player), "player is dead");
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

    if (! game_wait_for_tick_to_finish(g, v, l)) {
      TEST_FAILED(t, "wait loop failed");
      goto exit;
    }
  }

  //
  // Player should be in the water now
  //
  TEST_PROGRESS(t);
  {
    if (! (result = level_match_contents(g, v, l, t, w, h, expect.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }
  }

  TEST_ASSERT(t, ! thing_is_burning(player), "player is burning still");
  TEST_ASSERT(t, ! thing_is_dead(player), "player is dead");
  TEST_ASSERT(t, game_tick_get(g, v) == 2, "final tick counter value");

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  game_cleanup(g);

  return result;
}

bool test_load_player_on_fire_move_into_water(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("player_on_fire_move_into_water");

  // begin sort marker1 {
  test_callback_set(test, test_player_on_fire_move_into_water);
  // end sort marker1 }

  return true;
}
