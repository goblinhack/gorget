//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

static bool test_large_fire_water(Gamep g, Testp t)
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
        "...~~~."
        "..@~~~."
        "...~~~."
        "......."
        ".......";
  std::string expect1
      = "......."
        "......."
        "...~~~."
        "..@~:~."
        "...~~~."
        "......."
        ".......";
  std::string expect2
      = "......."
        "......."
        "...~~~."
        "..@~~~."
        "...~~~."
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
  bool   result = false;
  Thingp player = nullptr;

  //
  // Push the mob into lava
  //
  TEST_LOG(t, "spawn fire over water");
  TRACE_AND_INDENT();

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
  // Spawn fire twice. This should be enough to evaporate the water.
  //
  thing_spawn(g, v, l, tp_first(is_fire), thing_at(player) + spoint(2, 0));

  TEST_PROGRESS(t);
  for (auto tries = 0; tries < 3; tries++) {
    TEST_LOG(t, "try: %d", tries);
    TRACE_NO_INDENT();
    // level_dump(g, v, l, w, h);
    game_event_wait(g);
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

  TEST_PROGRESS(t);
  for (auto tries = 0; tries < 10; tries++) {
    TEST_LOG(t, "try: %d", tries);
    TRACE_NO_INDENT();
    // level_dump(g, v, l, w, h);
    game_event_wait(g);
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
    if (! (result = level_match_contents(g, v, l, t, w, h, expect2.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }
  }

  //
  // Check the tick is as expected
  //
  TEST_PROGRESS(t);
  {
    TEST_ASSERT(t, game_tick_get(g, v) == 13, "final tick counter value");
  }

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  game_cleanup(g);

  return result;
}

bool test_load_large_fire_water(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("large_fire_water");

  // begin sort marker1 {
  test_callback_set(test, test_large_fire_water);
  // end sort marker1 }

  return true;
}
