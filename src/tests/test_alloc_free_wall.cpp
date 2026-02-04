//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_globals.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

[[nodiscard]] static bool test_alloc_free_walls(Gamep g, Testp t)
{
  TEST_LOG(t, "begin");
  TRACE_AND_INDENT();

  LevelNum level_num = 0;
  auto     w         = 0;
  auto     h         = 0;

  //
  // How the dungeon starts out, and how we expect it to change
  //
  std::string start  = "";
  std::string expect = start;

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
      // fprintf(stderr, "ZZZ NEIL %s %s %d %d,%d\n", __FILE__, __FUNCTION__, __LINE__, X, Y);

      if (level_num++ == 0) {
        //
        // Already inited
        //
      } else {
        game_test_init_level(g, v, &l, level_num, spoint(X, Y), w, h, start.c_str());
      }

      //
      // No need to test all slots for level select. Additionally, we've filled
      // all the other levels, so not a lot of space to alloc IDs from.
      //
      auto slot_depth_to_test = MAP_SLOTS;
      if (level_num == LEVEL_SELECT_ID) {
        //
        // There's just no space in other levels if we fully allocate them!
        //
        slot_depth_to_test = 2;
        continue;
      }

      if (level_num > 10) {
        //
        // Takes too long to test them all
        //
        continue;
      }

      for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
          for (auto slot = 0; slot < slot_depth_to_test; slot++) {
            if (! thing_spawn(g, v, l, tp_random(is_wall), spoint(x, y))) {
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

  if (AN_ERROR_OCCURRED()) {
    result = false;
    TEST_FAILED(t, "error happened during thing placement");
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

bool test_load_alloc_free_walls(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("alloc_free_walls");

  // begin sort marker1 {
  test_callback_set(test, test_alloc_free_walls);
  // end sort marker1 }

  return true;
}
