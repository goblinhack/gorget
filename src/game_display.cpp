//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_level.hpp"

void Game::display(void)
{
  if (level) {
    level->tick();
    level->anim();
    level->display();
  }
}
