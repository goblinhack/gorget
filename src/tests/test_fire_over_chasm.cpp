//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

[[nodiscard]] static auto test_fire_over_chasm(Gamep g, Testp t) -> bool
{
  TEST_LOG(t, "begin");
  TRACE_AND_INDENT();

  LevelNum const level_num = 0;
  auto           w         = 7;
  auto           h         = 7;

  //
  // How the dungeon starts out, and how we expect it to change
  //
  std::string const start
      = "......."
        "......."
        "...CCC."
        "..@CCC."
        "...CCC."
        "......."
        ".......";
  std::string const expect1
      = "......."
        "......."
        "...CCC."
        "..@CCC."
        "...CCC."
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
  TEST_LOG(t, "spawn fire over chasm");
  TRACE_AND_INDENT();

  //
  // Find the player
  //
  TEST_PROGRESS(t);
  {
    TRACE_NO_INDENT();
    player = thing_player(g);
    if (player == nullptr) {
      TEST_FAILED(t, "no player");
      goto exit;
    }
  }

  //
  // Spawn fire.
  //
  if (thing_spawn(g, v, l, tp_first(is_fire), thing_at(player) + spoint(2, 0)) == nullptr) {
    TEST_FAILED(t, "spawn failed");
    goto exit;
  }

  TEST_PROGRESS(t);
  for (auto tries = 0; tries < 3; tries++) {
    TEST_LOG(t, "try: %d", tries);
    TRACE_NO_INDENT();
    // level_dump(g, v, l, w, h);
    TEST_ASSERT(t, game_event_wait(g), "failed to wait");
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

auto test_load_fire_over_chasm() -> bool
{
  TRACE_NO_INDENT();

  Testp test = test_load("fire_over_chasm");

  // begin sort marker1 {
  test_callback_set(test, test_fire_over_chasm);
  // end sort marker1 }

  return true;
}
