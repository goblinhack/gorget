//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
// REMOVED #include "my_level.hpp"

void Game::init(void)
{
  LOG("Game init");
  TRACE_AND_INDENT();

  set_seed();
}
