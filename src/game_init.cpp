//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"

void Game::init(void)
{
  LOG("Game init");
  TRACE_AND_INDENT();

  set_seed();
  start();
}
