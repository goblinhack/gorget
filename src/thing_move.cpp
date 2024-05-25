//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_minimal.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

#include <string.h>

void thing_dir_set_none(Thingp t)
{
  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_NONE) {
    t->dir = THING_DIR_NONE;
    // move_carried_items();
  }
}

bool thing_is_dir_none(Thingp t) { return (t->dir == THING_DIR_NONE); }

void thing_dir_set_down(Thingp t)
{
  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_DOWN) {
    t->dir = THING_DIR_DOWN;
    // move_carried_items();
  }
}

bool thing_is_dir_down(Thingp t) { return (t->dir == THING_DIR_DOWN); }

void thing_dir_set_up(Thingp t)
{
  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_UP) {
    t->dir = THING_DIR_UP;
    // move_carried_items();
  }
}

bool thing_is_dir_up(Thingp t) { return (t->dir == THING_DIR_UP); }

void thing_dir_set_left(Thingp t)
{
  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_LEFT) {
    t->dir = THING_DIR_LEFT;
    // move_carried_items();
  }
}

bool thing_is_dir_left(Thingp t) { return (t->dir == THING_DIR_LEFT); }

void thing_dir_set_right(Thingp t)
{
  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_RIGHT) {
    t->dir = THING_DIR_RIGHT;
    // move_carried_items();
  }
}

bool thing_is_dir_right(Thingp t) { return (t->dir == THING_DIR_RIGHT); }

void thing_dir_set_tl(Thingp t)
{
  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_TL) {
    t->dir = THING_DIR_TL;
    // move_carried_items();
  }
}

bool thing_is_dir_tl(Thingp t) { return (t->dir == THING_DIR_TL); }

void thing_dir_set_bl(Thingp t)
{
  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_BL) {
    t->dir = THING_DIR_BL;
    // move_carried_items();
  }
}

bool thing_is_dir_bl(Thingp t) { return (t->dir == THING_DIR_BL); }

void thing_dir_set_tr(Thingp t)
{
  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_TR) {
    t->dir = THING_DIR_TR;
    // move_carried_items();
  }
}

bool thing_is_dir_tr(Thingp t) { return (t->dir == THING_DIR_TR); }

void thing_dir_set_br(Thingp t)
{
  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_BR) {
    t->dir = THING_DIR_BR;
    // move_carried_items();
  }
}

bool thing_is_dir_br(Thingp t) { return (t->dir == THING_DIR_BR); }

void thing_set_dir_from_delta(Thingp t, int dx, int dy)
{
  if (dx < 0) {
    if (dy > 0) {
      thing_dir_set_bl(t);
    } else if (dy < 0) {
      thing_dir_set_tl(t);
    } else {
      thing_dir_set_left(t);
    }
    return;
  }

  if (dx > 0) {
    if (dy > 0) {
      thing_dir_set_br(t);
    } else if (dy < 0) {
      thing_dir_set_tr(t);
    } else {
      thing_dir_set_right(t);
    }
    return;
  }

  if (dy > 0) {
    if (dx > 0) {
      thing_dir_set_br(t);
    } else if (dx < 0) {
      thing_dir_set_bl(t);
    } else {
      thing_dir_set_down(t);
    }
    return;
  }

  if (dy < 0) {
    if (dx > 0) {
      thing_dir_set_tr(t);
    } else if (dx < 0) {
      thing_dir_set_tl(t);
    } else {
      thing_dir_set_up(t);
    }
    return;
  }
}

void thing_move(Levelp l, Thingp t, point3d to)
{
  if (level_is_oob(l, to)) {
    return;
  }

  if (to == t->at) {
    return;
  }

  thing_pop(l, t);

  t->pix_at.x = t->at.x * TILE_WIDTH;
  t->pix_at.y = t->at.y * TILE_HEIGHT;

  t->old_at = t->at;
  t->at     = to;

  thing_push(l, t);
}

bool thing_can_move_to(Levelp l, Thingp t, point3d to)
{
  if (level_is_oob(l, to)) {
    return false;
  }

  if (to == t->at) {
    return true;
  }

  auto dx = to.x - t->at.x;
  auto dy = to.y - t->at.y;
  thing_set_dir_from_delta(t, dx, dy);

  auto my_tp = thing_tp(t);

  FOR_ALL_THINGS_AND_TPS_AT(l, it, it_tp, to)
  {
    if (tp_is_player(my_tp) && tp_is_obs_player(it_tp)) {
      return false;
    }

    if (tp_is_monst(my_tp) && tp_is_obs_monst(it_tp)) {
      return false;
    }
  }

  return true;
}

void thing_interpolate(Level *l, Thingp t, float dt)
{
  if (t->old_at == t->at) {
    return;
  }

  float pix_x = (float) t->old_at.x + (((float) (t->at.x - t->old_at.x)) * dt);
  float pix_y = (float) t->old_at.y + (((float) (t->at.y - t->old_at.y)) * dt);

  t->pix_at.x = pix_x * TILE_WIDTH;
  t->pix_at.y = pix_y * TILE_HEIGHT;
}

void thing_push(Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  point3d p(t->pix_at.x / TILE_WIDTH, t->pix_at.y / TILE_HEIGHT, t->at.z);

  if (level_is_oob(l, p)) {
    return;
  }

  //
  // Already at this location?
  //
  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o_id = l->thing_id[ p.x ][ p.y ][ p.z ][ slot ];
    if (o_id == t->id) {
      return;
    }
  }

  //
  // Detach from the old location
  //
  thing_pop(l, t);

  //
  // Need to push to the new location.
  //
  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o_id = l->thing_id[ p.x ][ p.y ][ p.z ][ slot ];
    if (! o_id) {
      l->thing_id[ p.x ][ p.y ][ p.z ][ slot ] = t->id;

      //
      // Keep track of tiles the player has been on.
      //
      if (tp_is_player(thing_tp(t))) {
        l->is_walked[ p.x ][ p.y ][ p.z ] = true;
      }

      //
      // Set an initial tile so we can see the thing
      //
      auto tp   = tp_find(t->tp_id);
      auto tile = tp_first_tile(tp);
      if (tile) {
        t->tile_index = tile_global_index(tile);
      }
      return;
    }
  }

  ERR("out of thing slots");
}

void thing_pop(Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  point3d p(t->pix_at.x / TILE_WIDTH, t->pix_at.y / TILE_HEIGHT, t->at.z);

  if (level_is_oob(l, p)) {
    return;
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o_id = l->thing_id[ p.x ][ p.y ][ p.z ][ slot ];
    if (o_id == t->id) {
      l->thing_id[ p.x ][ p.y ][ p.z ][ slot ] = 0;
      return;
    }
  }
}
