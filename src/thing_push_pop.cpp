//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"

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
        l->player_has_walked_tile[ p.x ][ p.y ] = true;
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
      thing_is_on_map_unset(g, v, l, t);
      return;
    }
  }

  ERR("could not pop thing that is on the map");
}
