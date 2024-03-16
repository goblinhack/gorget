//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_level.hpp"
#include "my_wid_rightbar.hpp"

void Game::create_level(void)
{
  LOG("Game create level");
  TRACE_AND_INDENT();

  set_seed();

  if (level) {
    TRACE_NO_INDENT();

    auto l = level;
    if (l) {
      LOG("Remove old level");
      delete l;
      level = nullptr;
    }
  }

  {
    TRACE_NO_INDENT();
    LOG("Level create");
    level = new Level();
  }

  wid_rightbar_init();
}
