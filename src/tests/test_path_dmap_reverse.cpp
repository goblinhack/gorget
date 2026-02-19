//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"
#include "../my_thing.hpp"

[[nodiscard]] static bool test_path_dmap_reverse(Gamep g, Testp t)
{
  TEST_LOG(t, "begin");
  TRACE_AND_INDENT();

  LevelNum const level_num = 0;
  auto           w         = MAP_WIDTH;
  auto           h         = MAP_HEIGHT;

  //
  // How the dungeon starts out, and how we expect it to change
  //
  std::string const start
      = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"  // newline
        "x......x....................x..................x"  // newline
        "x......x....................x..................x"  // newline
        "x......x....................x..................x"  // newline
        "x......x....................x..................x"  // newline
        "x......x....................x..................x"  // newline
        "x......x....................x..................x"  // newline
        "x......x....................x..................x"  // newline
        "x...........................x..................x"  // newline
        "xxxxxxxxxxxxxxxxxxxxxxxxx...x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x......xxxxxxxxxxxxxxxxxxxxxx..................x"  // newline
        "x..............................................x"  // newline
        "x..............................................x"  // newline
        "x..............................................x"  // newline
        "x..............................................x"  // newline
        "x..............................................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x...........................x..................x"  // newline
        "x.............................................@x"  // newline
        "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"; // newline

  std::string const expect
      = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"  // newline
        "x......x....................x..................x"  // newline
        "x......x....................x..................x"  // newline
        "x......x....................x..................x"  // newline
        "x......x....................x..................x"  // newline
        "x......x....................x..................x"  // newline
        "x......x....................x..................x"  // newline
        "x......x....................x..................x"  // newline
        "x...........................x..................x"  // newline
        "xxxxxxxxxxxxxxxxxxxxxxxxx...x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#.....xxxxxxxxxxxxxxxxxxxxxx..................x"  // newline
        "x#.............................................x"  // newline
        "x#.............................................x"  // newline
        "x#.............................................x"  // newline
        "x#.............................................x"  // newline
        "x#.............................................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x#..........................x..................x"  // newline
        "x.############################################@x"  // newline
        "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"; // newline

  //
  // Create the level and start playing
  //
  Levelp  l;
  Levelsp v = game_test_init(g, &l, level_num, w, h, start.c_str());

  //
  // The guts of the test
  //
  bool result = false;

  Thingp player = nullptr;
  for (auto *it : level_find_all(g, v, l, is_player)) {
    player = it;
    break;
  }

  thing_dmap(g, v, l, player, true /* reverse */);
  auto *dmap = thing_get_dmap(g, v, l, player);

  for (auto p : dmap_solve(g, v, l, player, dmap, thing_at(player))) {
    TEST_ASSERT(t, thing_spawn(g, v, l, tp_first(is_corridor), p) != nullptr, "failed to spawn thing");
  }

  if (! (result = level_match_contents(g, v, l, t, w, h, expect.c_str()))) {
    TEST_FAILED(t, "unexpected contents");
    goto exit;
  }

  TEST_ASSERT(t, game_tick_get(g, v) == 0, "final tick counter value");

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  game_cleanup(g);

  return result;
}

bool test_load_path_dmap_reverse()
{
  TRACE_NO_INDENT();

  Testp test = test_load("path_dmap_reverse");

  // begin sort marker1 {
  test_callback_set(test, test_path_dmap_reverse);
  // end sort marker1 }

  return true;
}
