//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_globals.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

static bool test_alloc_free_monsts(Gamep g, Testp t)
{
  TEST_LOG(t, "begin");
  TRACE_AND_INDENT();

  LevelNum level_num = 0;
  auto     w         = 0;
  auto     h         = 0;

  std::string start = "";

  //
  // Create the level and start playing
  //
  Levelp  l;
  Levelsp v      = game_test_init(g, &l, level_num, w, h, start.c_str());
  bool    result = true;

  TEST_ASSERT(t, levels_thing_count(g, v) == 0, "expected thing count to be 0");
  TEST_ASSERT(t, levels_thing_ext_count(g, v) == 0, "expected thing count to be 0");

  for (auto X = 0; X < LEVEL_ACROSS; X++) {
    for (auto Y = 0; Y < LEVEL_DOWN; Y++) {
      if ((X == 0) && (Y == 0)) {
        continue;
      }

      level_num++;
      game_test_init_level(g, v, &l, level_num, spoint(X, Y), w, h, start.c_str());

      for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
          if (! thing_spawn(g, v, l, tp_random(is_monst_group_easy), spoint(x, y))) {
            break;
          }

          if (AN_ERROR_OCCURRED()) {
            break;
          }
        }
        if (AN_ERROR_OCCURRED()) {
          break;
        }
      }
      if (AN_ERROR_OCCURRED()) {
        break;
      }

      level_debug(g, v, l);
    }
    if (AN_ERROR_OCCURRED()) {
      break;
    }
  }

  game_debug_info(g);

  if (v->thing_ext_count != THING_EXT_MAX - 1) {
    TEST_FAILED(t, "not enough monsters allocated");
    goto exit;
  }

  game_event_wait(g);

  if (! game_wait_for_tick_to_finish(g, v, l)) {
    TEST_FAILED(t, "wait loop failed");
    goto exit;
  }

  //
  // No player, so 0
  //
  TEST_ASSERT(t, game_tick_get(g, v) == 0, "final tick counter value");

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  game_cleanup(g);

  return result;
}

bool test_load_alloc_free_monsts(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("alloc_free_monsts");

  // begin sort marker1 {
  test_callback_set(test, test_alloc_free_monsts);
  // end sort marker1 }

  return true;
}
