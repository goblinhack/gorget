//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_test.hpp"

static bool test_move_ok(Gamep g)
{
  TRACE_NO_INDENT();

  auto level_num = 0;
  auto v         = game_levels_set(g, levels_memory_alloc(g));
  auto l         = game_level_get(g, v, level_num);
  auto w         = 7;
  auto h         = 7;
  bool result    = false;

  std::string start
      = "xxxxxxx"
        "x.....x"
        "x.....x"
        "x.@...x"
        "x.....x"
        "x.....x"
        "xxxxxxx";
  std::string expect
      = "xxxxxxx"
        "x.....x"
        "x.....x"
        "x..@..x"
        "x.....x"
        "x.....x"
        "xxxxxxx";

  level_init(g, v, l, level_num);
  level_populate(g, v, l, w, h, start.c_str());
  result = level_expect(g, v, l, w, h, expect.c_str());
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
