//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
// REMOVED #include "my_level.hpp"
#include "my_random.hpp"
#include "my_random_name.hpp"

void Game::set_seed(void)
{
  if (g_opt_seed_name != "") {
    seed_name = g_opt_seed_name;
  } else {
    seed_name = random_name(sizeof("4294967295") - 1);
  }

  seed = string_to_hash(seed_name);

  LOG("Set seed, name '%s', seed %u", seed_name.c_str(), seed);
  pcg_srand(seed);
}
