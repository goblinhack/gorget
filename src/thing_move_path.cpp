//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"

//
// Remove the move path
//
void thing_move_path_reset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto *ext_struct = thing_ext_struct(g, t);
  if (ext_struct == nullptr) {
    return;
  }

  ext_struct->move_path.size = 0;
}

//
// Get the move path size
//
auto thing_move_path_size(Gamep g, Levelsp v, Levelp l, Thingp t) -> int
{
  TRACE_NO_INDENT();

  auto *ext_struct = thing_ext_struct(g, t);
  if (ext_struct == nullptr) {
    return 0;
  }

  return ext_struct->move_path.size;
}

//
// Return true if there is a move to pop (and pop it)
//
auto thing_move_path_pop(Gamep g, Levelsp v, Levelp l, Thingp t, spoint &out) -> bool
{
  TRACE_NO_INDENT();

  auto *ext_struct = thing_ext_struct(g, t);
  if (ext_struct == nullptr) {
    return false;
  }

  if (ext_struct->move_path.size == 0) {
    return false;
  }

  out = ext_struct->move_path.points[ 0 ];

  for (int index = 0; index < ext_struct->move_path.size - 1; index++) {
    ext_struct->move_path.points[ index ] = ext_struct->move_path.points[ index + 1 ];
  }
  ext_struct->move_path.size--;

  return true;
}

//
// Copy the given path to the thing
//
auto thing_move_path_apply(Gamep g, Levelsp v, Levelp l, Thingp t, std::vector< spoint > &move_path) -> bool
{
  auto *ext_struct = thing_ext_struct(g, t);
  if (ext_struct == nullptr) {
    THING_ERR(t, "no ext struct");
    return false;
  }

  int index                  = 0;
  ext_struct->move_path.size = 0;

  IF_DEBUG2
  {
    THING_DBG(t, "apply path size: %d", (int) move_path.size());
    for (auto p : move_path) {
      THING_DBG(t, " - path: %d,%d", p.x, p.y);
    }
  }

  for (auto p : move_path) {
    ext_struct->move_path.points[ index ].x = p.x;
    ext_struct->move_path.points[ index ].y = p.y;
    ext_struct->move_path.size              = ++index;
    if (index >= ARRAY_SIZE(ext_struct->move_path.points)) {
      break;
    }
  }

  return true;
}

//
// Return true if there is a move to pop.
//
auto thing_move_path_target(Gamep g, Levelsp v, Levelp l, Thingp t, spoint &out) -> bool
{
  TRACE_NO_INDENT();

  auto *ext_struct = thing_ext_struct(g, t);
  if (ext_struct == nullptr) {
    return false;
  }

  if (ext_struct->move_path.size == 0) {
    return false;
  }

  out = ext_struct->move_path.points[ ext_struct->move_path.size - 1 ];

  return true;
}
