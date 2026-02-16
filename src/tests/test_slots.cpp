//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"
#include "../my_thing_inlines.hpp"

[[nodiscard]] static bool test_slots(Gamep g, Testp t)
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
        "...@..."
        "......."
        "......."
        ".......";
  std::string expect1
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
  Levelsp v = game_test_init(g, &l, level_num, w, h, start.c_str());

  //
  // The guts of the test
  //
  bool result = false;

  TEST_PROGRESS(t);

  auto player = thing_player(g);
  if (! player) {
    TEST_FAILED(t, "no player");
    goto exit;
  }

  TEST_PROGRESS(t);

  for (auto slot = 0; slot < MAP_SLOTS * 10; slot++) {
    if (! thing_spawn(g, v, l, tp_random(is_smoke), thing_at(player))) {
      TEST_FAILED(t, "failed to spawn thing");
      break;
    }

    if (! thing_spawn(g, v, l, tp_random(is_fire), thing_at(player))) {
      TEST_FAILED(t, "failed to spawn thing");
      break;
    }

    if (! thing_spawn(g, v, l, tp_random(is_steam), thing_at(player))) {
      TEST_FAILED(t, "failed to spawn thing");
      break;
    }

    auto m = thing_spawn(g, v, l, tp_random(is_monst), thing_at(player));
    if (! m) {
      TEST_FAILED(t, "failed to spawn thing");
      break;
    }

    ThingEvent e;
    thing_dead(g, v, l, m, e);
  }

  game_event_wait(g);

  if (! game_wait_for_tick_to_finish(g, v, l)) {
    TEST_FAILED(t, "wait loop failed");
    goto exit;
  }

  if (! (result = level_match_contents(g, v, l, t, w, h, expect1.c_str()))) {
    TEST_FAILED(t, "unexpected contents");
    goto exit;
  }

  TEST_ASSERT(t, game_tick_get(g, v) == 1, "final tick counter value");

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  game_cleanup(g);

  return result;
}

bool test_load_slots(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("slots");

  // begin sort marker1 {
  test_callback_set(test, test_slots);
  // end sort marker1 }

  return true;
}
