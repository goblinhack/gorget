//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

[[nodiscard]] static bool test_projectile_secret_door(Gamep g, Testp t)
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
        "x..x..x"
        "x..x..x"
        "x@.s..x"
        "x..x..x"
        "x..x..x"
        "xxxxxxx";
  std::string expect1
      = "xxxxxxx"
        "x..x..x"
        "x..x..x"
        "x@....."
        "x..x..x"
        "x..x..x"
        "xxxxxxx";
  Levelp  l;
  Levelsp v      = game_test_init(g, &l, level_num, w, h, start.c_str());
  bool    result = true;

  auto *tp_fireball = tp_find_mand("fireball");
  tp_damage_set(tp_fireball, THING_EVENT_FIRE_DAMAGE, "100");

  auto *player = thing_player(g);
  if (player == nullptr) {
    TEST_FAILED(t, "no player");
    goto exit;
  }

  for (auto tries = 0; tries < 5; tries++) {
    player_fire(g, v, l, 1, 0, tp_fireball);
    TEST_ASSERT(t, game_event_wait(g), "failed to wait");
    if (! game_wait_for_tick_to_finish(g, v, l)) {
      TEST_FAILED(t, "wait loop failed");
      goto exit;
    }
  }

  TEST_PROGRESS(t);
  for (auto tries = 0; tries < 10; tries++) {
    TEST_LOG(t, "try: %d", tries);
    TRACE_NO_INDENT();
    TEST_ASSERT(t, game_event_wait(g), "failed to wait");
    if (! game_wait_for_tick_to_finish(g, v, l)) {
      TEST_FAILED(t, "wait loop failed");
      goto exit;
    }
  }

  TEST_PROGRESS(t);
  if (! (result = level_match_contents(g, v, l, t, w, h, expect1.c_str()))) {
    TEST_FAILED(t, "unexpected contents");
    goto exit;
  }

  TEST_ASSERT(t, game_tick_get(g, v) == 15, "final tick counter value");

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  game_cleanup(g);

  return result;
}

bool test_load_projectile_secret_door(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("projectile_secret_door");

  // begin sort marker1 {
  test_callback_set(test, test_projectile_secret_door);
  // end sort marker1 }

  return true;
}
