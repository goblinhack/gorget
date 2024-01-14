//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_level.hpp"

void Game::fini(void)
{
  LOG("Game fini");
  TRACE_AND_INDENT();

  if (level) {
    auto l = level;
    level  = nullptr;
    delete l;
  }
}
