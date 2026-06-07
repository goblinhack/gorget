//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_types.hpp"

[[nodiscard]] auto level_request_to_cleanup_things(Gamep g, Levelsp /*v*/, Levelp l) -> bool
{
  TRACE();

  return l->request_to_cleanup_things;
}

void level_request_to_cleanup_things_set(Gamep g, Levelsp /*v*/, Levelp l)
{
  TRACE();

  l->request_to_cleanup_things = true;
}

void level_request_to_cleanup_things_unset(Gamep g, Levelsp /*v*/, Levelp l)
{
  TRACE();

  l->request_to_cleanup_things = false;
}

[[nodiscard]] auto level_is_player_level(Gamep g, Levelsp /*v*/, Levelp l) -> bool
{
  TRACE();

  return l->_is_player_level;
}

void level_is_player_level_set(Gamep g, Levelsp /*v*/, Levelp l)
{
  TRACE();

  l->_is_player_level = true;
}

void level_is_player_level_unset(Gamep g, Levelsp /*v*/, Levelp l)
{
  TRACE();

  l->_is_player_level = false;
}
