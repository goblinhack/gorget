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
  thing_pop(g, v, t);

  //
  // Need to push to the new location.
  //
  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o_id = l->thing_id[ at.x ][ at.y ][ slot ];
    if (! o_id) {
      auto tp = thing_tp(t);

      //
      // Keep track of tiles the player has been on.
      //
      if (tp_is_player(tp)) {
        l->player_has_walked_tile[ at.x ][ at.y ] = true;
      }

      //
      // Save where we were pushed so we can pop the same location
      //
      thing_is_on_map_set(g, v, l, t);
      t->level_num                        = l->level_num;
      t->last_pushed_at                   = at;
      l->thing_id[ at.x ][ at.y ][ slot ] = t->id;

      if (0) {
        THING_DBG(t, "pushed to %u,%u slot %u", at.x, at.y, slot);
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
            auto    slotp   = &l->thing_id[ at.x ][ at.y ][ slot_tmp ];
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
          l->thing_id[ at.x ][ at.y ][ slot_tmp ] = slots_sorted[ slot_tmp ];
        }
      }
#endif

      //
      // Error testing
      //
      if (0) {
        static int xxx;
        if (xxx++ == 100) {
          ERR("out of thing slots");
          return false;
        }
      }

      return true;
    }
  }

  //
  // Dump the contents here
  //
  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto dump_id = l->thing_id[ at.x ][ at.y ][ slot ];
    if (dump_id) {
      auto it = thing_find(g, v, dump_id);
      THING_CON(it, "DUMP: is using slot %u", slot);
    }
  }

  ERR("out of thing slots");
  return false;
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

  spoint at = t->last_pushed_at;

  if (0) {
    THING_DBG(t, "is on the map, last pushed %u,%u", at.x, at.y);
  }

  if (is_oob(at)) {
    return;
  }

  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto o_id = l->thing_id[ at.x ][ at.y ][ slot ];
    if (o_id == t->id) {
      l->thing_id[ at.x ][ at.y ][ slot ] = 0;
      if (0) {
        THING_DBG(t, "popped from slot %u", slot);
      }
      thing_is_on_map_unset(g, v, l, t);
      return;
    }
  }

  //
  // Dump the contents here
  //
  for (auto slot = 0; slot < MAP_SLOTS; slot++) {
    auto dump_id = l->thing_id[ at.x ][ at.y ][ slot ];
    if (dump_id) {
      auto it = thing_find(g, v, dump_id);
      THING_CON(it, "DUMP: is using slot %u", slot);
    }
  }

  THING_ERR(t, "could not pop thing that is on the map");
}
