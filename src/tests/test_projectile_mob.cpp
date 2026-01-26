//
// Copyright goblinhack@gmail.com
//

#include "../my_game.hpp"
#include "../my_level.hpp"
#include "../my_main.hpp"
#include "../my_test.hpp"

static bool test_projectile_mob(Gamep g, Testp t)
{
  TEST_LOG(t, "begin");
  TRACE_AND_INDENT();

  LevelNum level_num = 0;
  auto     w         = 27;
  auto     h         = 7;

  //
  // How the dungeon starts out, and how we expect it to change
  //
  std::string start
      = "xxxxxxxxxxxxxxxxxxxxxxxxxxx"
        "x.........................x"
        "x.........................x"
        "x@.......................Gx"
        "x.........................x"
        "x.........................x"
        "xxxxxxxxxxxxxxxxxxxxxxxxxxx";
  std::string expect1
      = "xxxxxxxxxxxxxxxxxxxxxxxxxxx"
        "x.........................x"
        "x.........................x"
        "x@........-.......-......!x"
        "x.........................x"
        "x.........................x"
        "xxxxxxxxxxxxxxxxxxxxxxxxxxx";
  Levelp  l;
  Levelsp v      = game_test_init(g, &l, level_num, w, h, start.c_str());
  bool    result = true;

  auto tp_fireball = tp_find_mand("fireball");
  tp_damage_set(tp_fireball, THING_EVENT_FIRE_DAMAGE, "100");

  auto player = thing_player(g);
  if (! player) {
    TEST_FAILED(t, "no player");
    goto exit;
  }

  //
  // Spawn fire. This should be enough to blow up all the barrels
  //
  TEST_PROGRESS(t);

  //
  // Wait for the projectile to ignite a barrel
  //
  TEST_PROGRESS(t);
  for (auto tries = 0; tries < 5; tries++) {
    TEST_LOG(t, "try: %d", tries);
    player_fire(g, v, l, 1, 0, tp_fireball);
    TRACE_NO_INDENT();
    game_event_wait(g);
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

  TEST_ASSERT(t, game_tick_get(g, v) == 5, "final tick counter value");

  TEST_PASSED(t);
exit:
  TRACE_NO_INDENT();
  game_cleanup(g);

  return result;
}

bool test_load_projectile_mob(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("projectile_mob");

  // begin sort marker1 {
  test_callback_set(test, test_projectile_mob);
  // end sort marker1 }

  return true;
}
