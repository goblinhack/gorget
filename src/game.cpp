//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"

Game::Game(std::string appdata)
{
  TRACE_AND_INDENT();

  config.reset();

  this->appdata = appdata;

  saved_dir = appdata + DIR_SEP + "yelindor" + DIR_SEP;
  save_slot = 1;

  save_meta = "seed " + seed_name + ", ";
  save_meta += string_timestamp();

  save_file = saved_dir + "saved-slot-" + std::to_string(save_slot);
}
