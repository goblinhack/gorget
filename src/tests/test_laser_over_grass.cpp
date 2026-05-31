//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

[[nodiscard]] static auto test_laser_over_grass(Gamep g, Testp t) -> bool
{
  TEST_LOG(t, "begin");
  TRACE();

  LevelNum const level_num = 0;
  auto           w         = 14;
  auto           h         = 7;

  //
  // How the dungeon starts out, and how we expect it to change
  //
  std::string const start
      = "xxxxxxxxxxxxxx"
        "x............x"
        "x............x"
        "x@'''''''''''x"
        "x............x"
        "x............x"
        "xxxxxxxxxxxxxx";
  std::string const expect1
      = "xxxxxxxxxxxxxx"
        "x............x"
        "x............x"
        "x@'''''''''''x"
        "x............x"
        "x............x"
        "xxxxxxxxxxxxxx";
  Levelp  l      = nullptr;
  Levelsp v      = game_test_init(g, &l, level_num, w, h, start.c_str());
  bool    result = true;

  auto *tp_laser_fire = tp_find_mand("laser_fire");
  tp_damage_set(tp_laser_fire, THING_EVENT_FIRE_DAMAGE, "100");

  auto *player = thing_player(g);
  if (player == nullptr) [[unlikely]] {
    TEST_FAILED(t, "no player");
    goto exit;
  }

  //
  // Wait for the laser to ignite a barrel
  //
  level_dump(g, v, l, w, h);
  TEST_PROGRESS(t);
  for (auto tries = 0; tries < 5; tries++) {
    TEST_LOG(t, "try: %d", tries);
    (void) player_fire(g, v, l, 1, 0, tp_laser_fire, bpoint(13, 3));
    TRACE();
    TEST_ASSERT(t, game_event_wait(g), "failed to wait");
    if (! game_wait_for_tick_to_finish(g, v, l)) {
      TEST_FAILED(t, "wait loop failed");
      goto exit;
    }
  }

  level_dump(g, v, l, w, h);
  TEST_PROGRESS(t);
  if (! (result = level_match_contents(g, v, l, t, w, h, expect1.c_str()))) {
    TEST_FAILED(t, "unexpected contents");
    goto exit;
  }

  TEST_ASSERT(t, game_tick_get(g, v) == 5, "final tick counter value");

  level_dump(g, v, l, w, h);
  TEST_PASSED(t);
exit:
  TRACE();
  game_cleanup(g);

  return result;
}

[[nodiscard]] auto test_load_laser_over_grass() ->  bool // NOLINT
{
  TRACE();

  Testp test = test_load("laser_over_grass");

  // begin sort marker1 {
  test_callback_set(test, test_laser_over_grass);
  // end sort marker1 }

  return true;
}
