//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

static bool test_bridge_on_fire_over_lava(Gamep g, Testp t)
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
        "...LLL."
        "..@===."
        "...LLL."
        "......."
        ".......";
  std::string expect1
      = "......."
        "......."
        "...LLL."
        "..@!!=."
        "...LLL."
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
  TEST_LOG(t, "spawn fire over a bridge");
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
  // Spawn fire twice. This should be enough to destroy the bridge.
  //
  thing_spawn(g, v, l, tp_random(is_fire), player->at + spoint(2, 0));

  TEST_PROGRESS(t);
  for (auto tries = 0; tries < 3; tries++) {
    TEST_LOG(t, "try: %d", tries);
    TRACE_NO_INDENT();
    // level_dump(g, v, l, w, h);
    game_event_wait(g);
    game_wait_for_tick_to_finish(g, v, l);
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
  // Check the tick is as expected
  //
  TEST_PROGRESS(t);
  {
    TEST_ASSERT(t, game_tick_get(g, v) == 3, "final tick counter value");
  }

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  game_cleanup(g);

  return result;
}

bool test_load_bridge_on_fire_over_lava(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("bridge_on_fire_over_lava");

  // begin sort marker1 {
  test_callback_set(test, test_bridge_on_fire_over_lava);
  // end sort marker1 }

  return true;
}
