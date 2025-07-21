//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

static bool test_collision_brazier_shove_into_mob(Gamep g, Testp t)
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
        "..@Bg.."
        "......."
        "......."
        ".......";
  std::string expect1 // first shove
      = "......."
        "......."
        "......."
        "..@Bg.."
        "......."
        "......."
        ".......";
  std::string expect2 // second shove, mob should be dead by now
      = "......."
        "......."
        "......."
        "..@B..."
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

  //
  // Bump into a brazier. It should be knocked over.
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

    game_wait_for_tick_to_finish(g, v, l);

    if (! (result = level_match_contents(g, v, l, w, h, expect1.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }

    auto player = thing_player(g);
    if (! player) {
      TEST_FAILED(t, "no player");
      goto exit;
    }

    //
    // Check the brazier is dead
    //
    TEST_LOG(t, "check brazier is dead");
    auto p        = player->at + spoint(1, 0);
    bool found_it = false;

    FOR_ALL_THINGS_AT(g, v, l, it, p)
    {
      if (thing_is_brazier(it) && thing_is_dead(it)) {
        found_it = true;
        break;
      }
    }

    if (! found_it) {
      TEST_FAILED(t, "no dead brazier");
      goto exit;
    }
  }

  //
  // Second shove, we should be able to move the dead brazier
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

    game_wait_for_tick_to_finish(g, v, l);

    if (! (result = level_match_contents(g, v, l, w, h, expect2.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }

    auto player = thing_player(g);
    if (! player) {
      TEST_FAILED(t, "no player");
      goto exit;
    }
  }

  TEST_ASSERT(t, game_tick_get(g, v) == 2, "final tick");

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  levels_destroy(g, v);

  return result;
}

bool test_load_collision_brazier_shove_into_mob(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("collision_brazier_shove_into_mob");

  // begin sort marker1 {
  test_callback_set(test, test_collision_brazier_shove_into_mob);
  // end sort marker1 }

  return true;
}
