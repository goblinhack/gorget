//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"

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
