//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"

#include <string.h>

void level_cursor_set(Level *l, int x, int y, int cursor)
{
  TRACE_NO_INDENT();

  l->cursor[ x ][ y ] = cursor;
}

void level_cursor_unset(Level *l, int x, int y, int cursor)
{
  TRACE_NO_INDENT();

  l->cursor[ x ][ y ] = CURSOR_NONE;
}

int level_cursor_get(Level *l, int x, int y)
{
  TRACE_NO_INDENT();

  return l->cursor[ x ][ y ];
}
