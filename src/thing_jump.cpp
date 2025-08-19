//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game_popups.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_sound.hpp"
#include "my_tile.hpp"
#include "my_tp_callbacks.hpp"

//
// Handles player and monster jumps
//
bool thing_jump_to(Gamep g, Levelsp v, Levelp l, Thingp t, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  if (to == t->at) {
    return false;
  }

  if (! thing_is_able_to_jump(t)) {
    return false;
  }

  thing_pop(g, v, t);

  t->pix_at.x = t->at.x * INNER_TILE_WIDTH;
  t->pix_at.y = t->at.y * INNER_TILE_HEIGHT;

  t->old_at      = t->at;
  t->moving_from = t->at;
  t->at          = to;
  thing_is_jumping_set(g, v, l, t);

  thing_push(g, v, l, t);

  tp_on_jumped(g, v, l, t);

  return true;
}
