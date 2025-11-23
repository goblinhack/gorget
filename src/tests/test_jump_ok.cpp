//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

static bool test_jump_ok(Gamep g, Testp t)
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
      = "xxxxxxx"
        "x.....x"
        "x..C..x"
        "x.@C..x"
        "x..C..x"
        "x.....x"
        "xxxxxxx";
  std::string expect1
      = "xxxxxxx"
        "x.....x"
        "x..C..x"
        "x..C@.x"
        "x..C..x"
        "x.....x"
        "xxxxxxx";

  //
  // Create the level and start playing
  //
  Levelp  l;
  Levelsp v = game_test_init(g, &l, level_num, w, h, start.c_str());

  //
  // The guts of the test
  //
  bool result = false;

  //
  // Jump
  //
  TEST_PROGRESS(t);
  {
    TEST_LOG(t, "jump");
    TRACE_AND_INDENT();

    auto player = thing_player(g);
    if (! player) {
      TEST_FAILED(t, "no player");
      goto exit;
    }

    if (! (result = player_jump(g, v, l, player, player->at + spoint(2, 0)))) {
      TEST_FAILED(t, "move fail");
      goto exit;
    }

    if (! game_wait_for_tick_to_finish(g, v, l)) {
      TEST_FAILED(t, "wait loop failed");
      goto exit;
    }

    if (! (result = level_match_contents(g, v, l, t, w, h, expect1.c_str()))) {
      TEST_FAILED(t, "unexpected contents");
      goto exit;
    }
  }

  TEST_ASSERT(t, game_tick_get(g, v) == 1, "final tick counter value");

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  game_cleanup(g);

  return result;
}

bool test_load_jump_ok(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("jump_ok");

  // begin sort marker1 {
  test_callback_set(test, test_jump_ok);
  // end sort marker1 }

  return true;
}
