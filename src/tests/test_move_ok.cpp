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

  auto     level_num = 0;
  auto     v         = game_levels_set(g, levels_memory_alloc(g));
  auto     l         = game_level_get(g, v, level_num);
  auto     w         = 7;
  auto     h         = 7;
  bool     result    = false;
  uint32_t next_tick = 0;
  bool     up        = false;
  bool     down      = false;
  bool     left      = false;
  bool     right     = false;

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
  level_init(g, v, l, level_num);
  level_populate(g, v, l, w, h, start.c_str());
  game_state_reset(g, "new game");
  game_start_playing(g);
  game_state_change(g, STATE_PLAYING, "new game");

  //
  // The guts of the test
  //

  //
  // Move right
  //
  {
    LOG("Sub-test: move right");
    TRACE_AND_INDENT();
    up = down = left = right = false;
    right                    = true;
    next_tick                = v->tick + 1;
    thing_player_move_request(g, up, down, left, right);
    while ((v->tick != next_tick) || level_tick_is_in_progress(g, v, l)) {
      game_tick(g);
    }
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
    next_tick                = v->tick + 1;
    thing_player_move_request(g, up, down, left, right);
    while ((v->tick != next_tick) || level_tick_is_in_progress(g, v, l)) {
      game_tick(g);
    }
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
    next_tick                = v->tick + 1;
    thing_player_move_request(g, up, down, left, right);
    while ((v->tick != next_tick) || level_tick_is_in_progress(g, v, l)) {
      game_tick(g);
    }
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
    next_tick = v->tick + 1;
    up = down = left = right = false;
    up                       = true;
    thing_player_move_request(g, up, down, left, right);
    while ((v->tick != next_tick) || level_tick_is_in_progress(g, v, l)) {
      game_tick(g);
    }
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
