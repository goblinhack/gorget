//
// Copyright goblinhack@gmail.com
//

#include "my_charmap.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_test.hpp"
#include "my_thing_inlines.hpp"
#include "my_ui.hpp"
#include "my_wids.hpp"

#include <format>

auto level_request_to_cleanup_things(Gamep g, Levelsp v, Levelp l) -> bool
{
  TRACE_NO_INDENT();

  return l->request_to_cleanup_things;
}

void level_request_to_cleanup_things_set(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  l->request_to_cleanup_things = true;
}

void level_request_to_cleanup_things_unset(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  l->request_to_cleanup_things = false;
}

auto level_is_player_level(Gamep g, Levelsp v, Levelp l) -> bool
{
  TRACE_NO_INDENT();

  return l->_is_player_level;
}

void level_is_player_level_set(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  l->_is_player_level = true;
}

void level_is_player_level_unset(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  l->_is_player_level = false;
}
