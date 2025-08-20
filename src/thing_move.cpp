//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_tile.hpp"
#include "my_tp_callbacks.hpp"

//
// Get thing direction
//
bool thing_is_dir_br(Thingp t) { return (t->dir == THING_DIR_BR); }
bool thing_is_dir_tr(Thingp t) { return (t->dir == THING_DIR_TR); }
bool thing_is_dir_bl(Thingp t) { return (t->dir == THING_DIR_BL); }
bool thing_is_dir_tl(Thingp t) { return (t->dir == THING_DIR_TL); }
bool thing_is_dir_right(Thingp t) { return (t->dir == THING_DIR_RIGHT); }
bool thing_is_dir_none(Thingp t) { return (t->dir == THING_DIR_NONE); }
bool thing_is_dir_down(Thingp t) { return (t->dir == THING_DIR_DOWN); }
bool thing_is_dir_up(Thingp t) { return (t->dir == THING_DIR_UP); }
bool thing_is_dir_left(Thingp t) { return (t->dir == THING_DIR_LEFT); }

//
// Set thing direction
//
void thing_dir_set_none(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_NONE) {
    t->dir = THING_DIR_NONE;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_down(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_DOWN) {
    t->dir = THING_DIR_DOWN;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_up(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_UP) {
    t->dir = THING_DIR_UP;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_left(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_LEFT) {
    t->dir = THING_DIR_LEFT;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_right(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_RIGHT) {
    t->dir = THING_DIR_RIGHT;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_tl(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_TL) {
    t->dir = THING_DIR_TL;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_bl(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_BL) {
    t->dir = THING_DIR_BL;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_tr(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_TR) {
    t->dir = THING_DIR_TR;
    // move_carried_items();
  }
}

//
// Set thing direction
//
void thing_dir_set_br(Thingp t)
{
  TRACE_NO_INDENT();

  if (tp_is_animated_no_dir(thing_tp(t))) {
    return;
  }

  if (t->dir != THING_DIR_BR) {
    t->dir = THING_DIR_BR;
    // move_carried_items();
  }
}

//
// Set tile direction from delta
//
void thing_set_dir_from_delta(Thingp t, int dx, int dy)
{
  TRACE_NO_INDENT();

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

//
// Handles manual and mouse follow moves
//
bool thing_move_to(Gamep g, Levelsp v, Levelp l, Thingp t, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  if (to == t->at) {
    return false;
  }

  thing_pop(g, v, t);

  t->pix_at.x = t->at.x * INNER_TILE_WIDTH;
  t->pix_at.y = t->at.y * INNER_TILE_HEIGHT;

  t->old_at      = t->at;
  t->moving_from = t->at;
  t->at          = to;

  thing_push(g, v, l, t);

  thing_is_moving_set(g, v, l, t);

  return true;
}

//
// Handles shoving to a location. We can't move there yet.
//
bool thing_shove_to(Gamep g, Levelsp v, Levelp l, Thingp t, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  if (to == t->at) {
    return false;
  }

  return thing_shove_handle(g, v, l, t, to);
}

//
// Handles immediate moves even across levels.
//
bool thing_warp_to(Gamep g, Levelsp v, Levelp new_level, Thingp t, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  //
  // Check if already present.
  //
  auto curr_level = thing_level(g, v, t);
  if (new_level == curr_level) {
    if (to == t->at) {
      return false;
    }
  }

  thing_pop(g, v, t);

  t->pix_at.x = t->at.x * INNER_TILE_WIDTH;
  t->pix_at.y = t->at.y * INNER_TILE_HEIGHT;

  t->old_at = t->at;
  t->at     = to;

  thing_push(g, v, new_level, t);

  //
  // Need to update with the new pixel position
  //
  thing_update_pos(g, t);

  return true;
}

//
// Move to the next tile is completed. Need to stop interpolating.
// There could be more tiles to pop.
//
void thing_move_or_jump_finish(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto player_struct = thing_player_struct(g);
  if (! player_struct) {
    return;
  }

  t->moving_from = t->at;

  thing_is_teleporting_set(g, v, l, t, false);
  thing_is_moving_set(g, v, l, t, false);
  thing_is_jumping_set(g, v, l, t, false);
}

//
// Returns true if the thing can move to this location
//
bool thing_can_move_to(Gamep g, Levelsp v, Levelp l, Thingp me, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  if (to == me->at) {
    return true;
  }

  auto dx = to.x - me->at.x;
  auto dy = to.y - me->at.y;
  thing_set_dir_from_delta(me, dx, dy);

  FOR_ALL_THINGS_AT(g, v, l, it, to)
  {
    //
    // A wall or pillar or somesuch?
    //
    if (thing_is_obstacle_to_movement(it)) {
      return false;
    }
  }

  return true;
}

//
// Returns true if we can move to this location by shoving
//
bool thing_can_move_to_by_shoving(Gamep g, Levelsp v, Levelp l, Thingp me, spoint to)
{
  TRACE_NO_INDENT();

  if (is_oob(to)) {
    return false;
  }

  if (to == me->at) {
    return true;
  }

  auto dx = to.x - me->at.x;
  auto dy = to.y - me->at.y;
  thing_set_dir_from_delta(me, dx, dy);

  FOR_ALL_THINGS_AT(g, v, l, it, to)
  {
    //
    // A wall or pillar or somesuch?
    //
    if (thing_is_obstacle_to_movement(it)) {
      //
      // But make exceptions for things like braziers
      //
      if (thing_is_able_to_shove(me)) {
        if (thing_is_shovable(it)) {
          continue;
        }
      }

      return false;
    }
  }

  return true;
}

//
// Post init/warp, we need to update the position so we can determine the level draw bounds
//
void thing_update_pos(Gamep g, Thingp t)
{
  TRACE_NO_INDENT();

  t->pix_at.x = t->at.x * INNER_TILE_WIDTH;
  t->pix_at.y = t->at.y * INNER_TILE_HEIGHT;
}

//
// Push the thing onto the level
//
void thing_push(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  spoint p = t->at;
  if (is_oob(p)) {
    return;
  }

  //
  // Already at this location?
  //
  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o_id = l->thing_id[ p.x ][ p.y ][ slot ];
    if (o_id == t->id) {
      return;
    }
  }

  //
  // Detach from the old location
  //
  thing_pop(g, v, t);

  //
  // Need to push to the new location.
  //
  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o_id = l->thing_id[ p.x ][ p.y ][ slot ];
    if (! o_id) {
      auto tp = thing_tp(t);

      //
      // Keep track of tiles the player has been on.
      //
      if (tp_is_player(tp)) {
        l->is_walked[ p.x ][ p.y ] = true;
      }

      //
      // Save where we were pushed so we can pop the same location
      //
      thing_is_on_map_set(g, v, l, t);
      t->level_num                      = l->level_num;
      t->last_pushed_at                 = p;
      l->thing_id[ p.x ][ p.y ][ slot ] = t->id;

      if (0) {
        LOG("l %p(%u) %s %d,%d", (void *) l, l->level_num, tp_name(tp).c_str(), p.x, p.y);
      }

#if 0
      if (0) {
        //
        // Sort the map slots by z prio for display order.
        //
        ThingId slots_sorted[ MAP_SLOTS ] = {};
        auto    slots_sorted_count        = 0;

        FOR_ALL_Z_LAYER(z_layer)
        {
          for (auto slot_tmp = 0; slot_tmp < MAP_SLOTS; slot_tmp++) {
            auto    slotp   = &l->thing_id[ p.x ][ p.y ][ slot_tmp ];
            ThingId cand_id = *slotp;
            if (cand_id) {
              Thingp o    = thing_find(g, v, cand_id);
              auto   o_tp = thing_tp(o);
              if (o && (tp_z_layer_get(o_tp) == z_layer)) {
                slots_sorted[ slots_sorted_count++ ] = cand_id;
                *slotp                               = 0;
              }
            }
          }
        }

        //
        // Copy the new sorted slots.
        //
        for (auto slot_tmp = 0; slot_tmp < MAP_SLOTS; slot_tmp++) {
          l->thing_id[ p.x ][ p.y ][ slot_tmp ] = slots_sorted[ slot_tmp ];
        }
      }
#endif

      return;
    }
  }

  ERR("out of thing slots");

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto dump_id = l->thing_id[ p.x ][ p.y ][ slot ];
    if (dump_id) {
      auto it = thing_find(g, v, dump_id);
      THING_LOG(it, "is using slot %u", slot);
    }
  }
}

//
// Pop the thing off the level
//
void thing_pop(Gamep g, Levelsp v, Thingp t)
{
  TRACE_NO_INDENT();

  auto l = thing_level(g, v, t);
  if (! l) {
    return;
  }

  //
  // Pop from where we were pushed
  //
  if (! thing_is_on_map(t)) {
    return;
  }
  spoint p = t->last_pushed_at;

  if (is_oob(p)) {
    return;
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o_id = l->thing_id[ p.x ][ p.y ][ slot ];
    if (o_id == t->id) {
      l->thing_id[ p.x ][ p.y ][ slot ] = 0;
      thing_is_on_map_set(g, v, l, t, false);
      return;
    }
  }

  ERR("could not pop thing that is on the map");
}
