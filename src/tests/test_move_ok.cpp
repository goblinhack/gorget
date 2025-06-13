//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

static bool test_move_ok(Gamep g)
{
  LOG("Test: move_ok");
  TRACE_AND_INDENT();

  LevelNum level_num = 0;
  Levelsp  v;
  Levelp   l;
  auto     w = 7;
  auto     h = 7;

  std::string start
      = "xxxxxxx"
        "x.....x"
        "x.....x"
        "x.@...x"
        "x.....x"
        "x.....x"
        "xxxxxxx";
  std::string expect1
      = "xxxxxxx"
        "x.....x"
        "x.....x"
        "x..@..x"
        "x.....x"
        "x.....x"
        "xxxxxxx";
  std::string expect2
      = "xxxxxxx"
        "x.....x"
        "x.....x"
        "x.....x"
        "x..@..x"
        "x.....x"
        "xxxxxxx";
  std::string expect3
      = "xxxxxxx"
        "x.....x"
        "x.....x"
        "x.....x"
        "x.@...x"
        "x.....x"
        "xxxxxxx";
  std::string expect4
      = "xxxxxxx"
        "x.....x"
        "x.....x"
        "x.@...x"
        "x.....x"
        "x.....x"
        "xxxxxxx";

  //
  // Create the level and start playing
  //
  v = game_test_init(g, &l, level_num, w, h, start.c_str());

  //
  // The guts of the test
  //
  bool result = false;
  bool up     = false;
  bool down   = false;
  bool left   = false;
  bool right  = false;

  //
  // Move right
  //
  {
    LOG("Sub-test: move right");
    TRACE_AND_INDENT();
    up = down = left = right = false;
    right                    = true;
    thing_player_move_request(g, up, down, left, right);
    game_tick_wait_to_finish(g, v, l);
    if (! (result = level_expect(g, v, l, w, h, expect1.c_str()))) {
      goto exit;
    }
  }

  //
  // Move down
  //
  {
    LOG("Sub-test: move down");
    TRACE_AND_INDENT();
    up = down = left = right = false;
    down                     = true;
    thing_player_move_request(g, up, down, left, right);
    game_tick_wait_to_finish(g, v, l);
    if (! (result = level_expect(g, v, l, w, h, expect2.c_str()))) {
      goto exit;
    }
  }

  //
  // Move left
  //
  {
    LOG("Sub-test: move left");
    TRACE_AND_INDENT();
    up = down = left = right = false;
    left                     = true;
    thing_player_move_request(g, up, down, left, right);
    game_tick_wait_to_finish(g, v, l);
    if (! (result = level_expect(g, v, l, w, h, expect3.c_str()))) {
      goto exit;
    }
  }

  //
  // Move up
  //
  {
    LOG("Sub-test: move right");
    TRACE_AND_INDENT();
    up = down = left = right = false;
    up                       = true;
    thing_player_move_request(g, up, down, left, right);
    game_tick_wait_to_finish(g, v, l);
    if (! (result = level_expect(g, v, l, w, h, expect4.c_str()))) {
      goto exit;
    }
  }

exit:
  TRACE_NO_INDENT();
  levels_destroy(g, v);

  return result;
}

bool test_load_move_ok(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("move_ok");

  // begin sort marker1 {
  test_callback_set(test, test_move_ok);
  // end sort marker1 }

  return true;
}
