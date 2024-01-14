//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_level.hpp"
#include "my_level_ph1.hpp"
#include "my_level_ph2.hpp"
#include "my_level_ph3.hpp"
#include "my_level_ph4.hpp"

void Game::init(void)
{
  LOG("Game init");
  TRACE_AND_INDENT();

  set_seed();

  static bool first_init_done;

  if (! first_init_done) {
    first_init_done = true;

    LOG("INI: Init level phases");
    TRACE_AND_INDENT();

    level_ph2_norm_init();
    level_ph2_entrances();
    level_ph2_exit_init();
    level_ph2_secr_init();
    level_ph2_lock_init();
    level_ph2_key_init();
    level_ph3_obstacle_init();
  }
}
