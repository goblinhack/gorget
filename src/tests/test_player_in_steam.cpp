//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"
#include "../my_thing_inlines.hpp"

[[nodiscard]] static bool test_player_in_steam(Gamep g, Testp t)
{
  TEST_LOG(t, "begin");
  TRACE_AND_INDENT();

  LevelNum level_num = 0;
  auto     w         = 7;
  auto     h         = 7;

  std::string level // first level
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
  Levelp  l;
  Levelsp v = game_test_init(g, &l, level_num, w, h, level.c_str());

  //
  // The guts of the test
  //
  bool   result = false;
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
  // Spawn steam on the player
  //
  TEST_PROGRESS(t);
  if (! thing_spawn(g, v, l, tp_first(is_steam), player)) {
    TEST_FAILED(t, "spawn failed");
    goto exit;
  }
  if (! thing_spawn(g, v, l, tp_first(is_steam), player)) {
    TEST_FAILED(t, "spawn failed");
    goto exit;
  }
  if (! thing_spawn(g, v, l, tp_first(is_steam), player)) {
    TEST_FAILED(t, "spawn failed");
    goto exit;
  }
  if (! thing_spawn(g, v, l, tp_first(is_steam), player)) {
    TEST_FAILED(t, "spawn failed");
    goto exit;
  }

  TEST_PROGRESS(t);
  for (auto tries = 0; tries < 7; tries++) {
    TEST_LOG(t, "try: %d", tries);
    TRACE_NO_INDENT();
    // level_dump(g, v, l, w, h);
    game_event_wait(g);
    if (! game_wait_for_tick_to_finish(g, v, l)) {
      TEST_FAILED(t, "wait loop failed");
      goto exit;
    }
  }

  TEST_ASSERT(t, ! thing_is_dead(player), "player is dead");

  //
  // Wait until the player is dead
  //
  TEST_PROGRESS(t);
  for (auto tries = 0; tries < 100; tries++) {
    TEST_LOG(t, "try: %d", tries);
    TRACE_NO_INDENT();
    // level_dump(g, v, l, w, h);
    game_event_wait(g);
    if (! game_wait_for_tick_to_finish(g, v, l)) {
      TEST_FAILED(t, "wait loop failed");
      goto exit;
    }

    if (thing_is_dead(player)) {
      break;
    }
  }

  TEST_ASSERT(t, thing_is_dead(player), "player is expected to be dead");
  TEST_ASSERT(t, game_tick_get(g, v) == 8, "final tick counter value");

  TEST_PASSED(t);

  result = true;
exit:
  TRACE_NO_INDENT();
  game_cleanup(g);

  return result;
}

bool test_load_player_in_steam(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("player_in_steam");

  // begin sort marker1 {
  test_callback_set(test, test_player_in_steam);
  // end sort marker1 }

  return true;
}
