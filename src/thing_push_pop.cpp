//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_thing_inlines.hpp"

//
// Push the thing onto the level
//
bool thing_push(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto at = thing_at(t);
  if (is_oob(at)) {
    return false;
  }

  //
  // Already at this location?
  //
  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o_id = l->thing_id[ at.x ][ at.y ][ slot ];
    if (o_id == t->id) {
      return true;
    }
  }

  //
  // Detach from the old location
  //
  (void) thing_pop(g, v, t);

  //
  // Need to push to the new location.
  //
  for (auto tries = 0; tries < MAP_SLOTS; tries++) {
    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
      auto o_id = l->thing_id[ at.x ][ at.y ][ slot ];
      if (o_id == 0U) {
        auto *tp = thing_tp(t);

        //
        // Keep track of tiles the player has been on.
        //
        if (tp_is_player(tp)) {
          l->player_has_walked_tile[ at.x ][ at.y ] = 1U;
        }

        //
        // Save where we were pushed so we can pop the same location
        //
        thing_is_on_map_set(g, v, l, t);
        t->level_num                        = l->level_num;
        t->last_pushed_at                   = at;
        l->thing_id[ at.x ][ at.y ][ slot ] = t->id;

        if (__unused__) {
          THING_DBG(t, "pushed to %u,%u slot %u", at.x, at.y, slot);
        }

        return true;
      }
    }

    //
    // We failed to pop this thing. Try to remove something and try again.
    // Try the lowest priority stuff first.
    //
    bool removed_one = false;

    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
      auto o_id = l->thing_id[ at.x ][ at.y ][ slot ];
      if (o_id != 0U) {
        auto *it = thing_find(g, v, o_id);
        if ((it != nullptr) && thing_is_removable_on_err(it)) {
          if (thing_pop(g, v, it)) {
            THING_DBG(t, "removed from the map due to lack of slots");
            removed_one = true;
            break;
          }
        }
      }
    }

    if (removed_one) {
      continue;
    }

    //
    // We failed to pop this thing. Try to remove something and try again.
    // Try to remove any higher priority things if we're still stuck.
    //
    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
      auto o_id = l->thing_id[ at.x ][ at.y ][ slot ];
      if (o_id != 0U) {
        auto *it = thing_find(g, v, o_id);
        if ((it != nullptr) && thing_is_dead(it) && thing_is_removable_when_dead_on_err(it)) {
          if (thing_pop(g, v, it)) {
            THING_DBG(t, "removed from the map due to lack of slots");
            removed_one = true;
            break;
          }
        }
      }
    }

    if (removed_one) {
      continue;
    }

    //
    // Give up
    //
    break;
  }

  //
  // Dump the contents of slots if we were unable to push
  //
  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto dump_id = l->thing_id[ at.x ][ at.y ][ slot ];
    if (dump_id != 0U) {
      auto *it = thing_find(g, v, dump_id);
      THING_CON(it, "DUMP: is using slot %u", slot);
    }
  }

  THING_ERR(t, "out of thing slots");
  return false;
}

//
// Pop the thing off the level
//
bool thing_pop(Gamep g, Levelsp v, Thingp t)
{
  TRACE_NO_INDENT();

  auto *l = thing_level(g, v, t);
  if (l == nullptr) {
    return false;
  }

  //
  // Pop from where we were pushed
  //
  if (! thing_is_on_map(t)) {
    return false;
  }

  spoint at = t->last_pushed_at;

  if (__unused__) {
    THING_DBG(t, "is on the map, last pushed %u,%u", at.x, at.y);
  }

  if (is_oob(at)) {
    return false;
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o_id = l->thing_id[ at.x ][ at.y ][ slot ];
    if (o_id == t->id) {
      l->thing_id[ at.x ][ at.y ][ slot ] = 0;
      if (__unused__) {
        THING_DBG(t, "popped from slot %u", slot);
      }
      thing_is_on_map_unset(g, v, l, t);
      return true;
    }
  }

  //
  // Dump the contents if we failed to pop
  //
  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto dump_id = l->thing_id[ at.x ][ at.y ][ slot ];
    if (dump_id != 0U) {
      auto *it = thing_find(g, v, dump_id);
      THING_CON(it, "DUMP: is using slot %u", slot);
    }
  }

  THING_ERR(t, "could not pop thing that is on the map");
  return false;
}
