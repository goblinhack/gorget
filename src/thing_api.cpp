//
// Copyright goblinhack@gmail.com
//

#include <cstdint>
#include <limits>

#include "my_bpoint.hpp"
#include "my_callstack.hpp"
#include "my_fpoint.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_spoint.hpp"
#include "my_thing.hpp"
#include "my_thing_inlines.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

[[nodiscard]] auto thing_at(Thingp t) -> bpoint
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }
  return make_bpoint(t->_at);
}

void thing_at_set(Gamep g, Levelsp v, Levelp l, Thingp t, const bpoint &val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }

  auto valf = make_fpoint(val);

  //
  // Not sure we need this, it ends up doing updates twice per tick as we do one at the tick end anyway
  //
  if (compiler_unused) {
    if (thing_is_player(t)) {
      if (t->_at != valf) {
        l->request_to_update_per_tile_visibility = true;
      }
    }
  }

  t->_old_at = t->_at;
  t->_at     = valf;
}

[[nodiscard]] auto thing_real_at(Thingp t) -> fpoint
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }
  return t->_at;
}

void thing_at_set(Gamep g, Levelsp v, Levelp l, Thingp t, const fpoint &val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }

  //
  // Not sure we need this, it ends up doing updates twice per tick as we do one at the tick end anyway
  //
  if (compiler_unused) {
    if (thing_is_player(t)) {
      if (t->_at != val) {
        l->request_to_update_per_tile_visibility = true;
      }
    }
  }

  t->_old_at = t->_at;
  t->_at     = val;
}

[[nodiscard]] auto thing_old_at(Thingp t) -> bpoint
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }
  return make_bpoint(t->_old_at);
}

[[nodiscard]] auto thing_prev_pix_at(Thingp t) -> spoint
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }
  return t->_prev_pix_at;
}

void thing_prev_pix_at_set(Gamep g, Levelsp v, Levelp l, Thingp t, const spoint &val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }
  t->_prev_pix_at = val;
}

void thing_pix_at_set(Gamep g, Levelsp v, Levelp l, Thingp t, const spoint &val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }

  if (thing_is_player(t)) {
    if (t->_curr_pix_at != val) {
      l->request_to_update_per_pixel_visibility = true;
    }
  }

  t->_prev_pix_at = t->_curr_pix_at;
  t->_curr_pix_at = val;
}

void thing_pix_at_set(Gamep g, Levelsp v, Levelp l, Thingp t, short x, short y)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    CROAK("no thing pointer");
  }

  spoint const val(x, y);

  if (thing_is_player(t)) {
    if (t->_curr_pix_at != val) {
      l->request_to_update_per_pixel_visibility = true;
    }
  }

  t->_prev_pix_at = t->_curr_pix_at;
  t->_curr_pix_at = val;
}

[[nodiscard]] auto thing_weight(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_weight;
}

[[nodiscard]] auto thing_weight_set(Gamep g, Levelsp v, Levelp l, Thingp t, uint32_t val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }

  if (val > std::numeric_limits< decltype(t->_weight) >::max()) {
    thing_err(t, "value overflow: %d", val);
    return 0;
  }

  return t->_weight = val;
}

[[nodiscard]] auto thing_is_on_map(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return t->_is_on_map;
}

void thing_is_on_map_set(Gamep g, Levelsp v, Levelp l, Thingp t, bool val)
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return;
  }
  t->_is_on_map = val;
}

void thing_is_on_map_unset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_DEBUG();

  thing_is_on_map_set(g, v, l, t, false);
}

[[nodiscard]] auto thing_is_animated_can_hflip(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_animated_can_hflip) != 0;
}

[[nodiscard]] auto thing_is_animated_no_dir(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_animated_no_dir) != 0;
}

[[nodiscard]] auto thing_is_animated_sync_first(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_animated_sync_first) != 0;
}

[[nodiscard]] auto thing_is_animated(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_animated) != 0;
}

[[nodiscard]] auto thing_is_barrel(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_barrel) != 0;
}

[[nodiscard]] auto thing_is_blit_centered(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_centered) != 0;
}

[[nodiscard]] auto thing_is_blit_flush_per_line(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_flush_per_line) != 0;
}

[[nodiscard]] auto thing_is_blit_outlined(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_outlined) != 0;
}

[[nodiscard]] auto thing_is_blit_square_outlined(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_square_outlined) != 0;
}

[[nodiscard]] auto thing_is_brazier(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_brazier) != 0;
}

[[nodiscard]] auto thing_is_bridge(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_bridge) != 0;
}

[[nodiscard]] auto thing_is_chasm(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_chasm) != 0;
}

[[nodiscard]] auto thing_is_corridor(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_corridor) != 0;
}

[[nodiscard]] auto thing_is_obs_to_cursor_path(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  //
  // Unless open
  //
  if (thing_is_openable(t)) {
    if (thing_is_open(t)) {
      return false;
    }
  }

  return tp_flag(thing_tp(t), is_obs_to_cursor_path) != 0;
}

[[nodiscard]] auto thing_is_cursor_path_hazard(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path_hazard) != 0;
}

[[nodiscard]] auto thing_is_cursor_path(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path) != 0;
}

[[nodiscard]] auto thing_is_cursor(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor) != 0;
}

[[nodiscard]] auto thing_is_deep_water(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_deep_water) != 0;
}

[[nodiscard]] auto thing_is_described_cursor(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_described_cursor) != 0;
}

[[nodiscard]] auto thing_is_dirt(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_dirt) != 0;
}

[[nodiscard]] auto thing_is_door_unlocked(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_door_unlocked) != 0;
}

[[nodiscard]] auto thing_is_dungeon_entrance(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_dungeon_entrance) != 0;
}

[[nodiscard]] auto thing_is_entrance(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_entrance) != 0;
}

[[nodiscard]] auto thing_is_exit(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_exit) != 0;
}

[[nodiscard]] auto thing_is_ghost(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_ghost) != 0;
}

[[nodiscard]] auto thing_is_kobalos(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_kobalos) != 0;
}

[[nodiscard]] auto thing_is_grass(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_grass) != 0;
}

[[nodiscard]] auto thing_is_key(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_key) != 0;
}

[[nodiscard]] auto thing_is_lava(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_lava) != 0;
}

[[nodiscard]] auto thing_is_usable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_usable) != 0;
}

[[nodiscard]] auto thing_is_level_curr(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_curr) != 0;
}

[[nodiscard]] auto thing_is_critical_to_level(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_critical_to_level) != 0;
}

[[nodiscard]] auto thing_is_level_final_icon(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_final_icon) != 0;
}

[[nodiscard]] auto thing_is_level_next_icon(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_next_icon) != 0;
}

[[nodiscard]] auto thing_is_level_locked_icon(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_locked_icon) != 0;
}

[[nodiscard]] auto thing_is_level_closed_icon(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_closed_icon) != 0;
}

[[nodiscard]] auto thing_is_pillar(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_pillar) != 0;
}

[[nodiscard]] auto thing_is_rock(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_rock) != 0;
}

[[nodiscard]] auto thing_is_door_secret(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_door_secret) != 0;
}

[[nodiscard]] auto thing_is_slime(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_slime) != 0;
}

[[nodiscard]] auto thing_is_tickable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_tickable) != 0;
}

[[nodiscard]] auto thing_is_tiled(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_tiled) != 0;
}

[[nodiscard]] auto thing_is_trap(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_trap) != 0;
}

[[nodiscard]] auto thing_is_treasure(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_treasure) != 0;
}

[[nodiscard]] auto thing_is_unused1(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused1) != 0;
}

[[nodiscard]] auto thing_is_unused2(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused2) != 0;
}

[[nodiscard]] auto thing_is_unused3(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused3) != 0;
}

[[nodiscard]] auto thing_is_unused4(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused4) != 0;
}

[[nodiscard]] auto thing_is_unused5(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused5) != 0;
}

[[nodiscard]] auto thing_is_unused6(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused6) != 0;
}

[[nodiscard]] auto thing_is_unused7(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused7) != 0;
}

[[nodiscard]] auto thing_is_noisey(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_noisey) != 0;
}

[[nodiscard]] auto thing_is_shown_noise(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_shown_noise) != 0;
}

[[nodiscard]] auto thing_is_obs_to_hearing(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_obs_to_hearing) != 0;
}

[[nodiscard]] auto thing_is_able_to_be_thrown(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_be_thrown) != 0;
}

[[nodiscard]] auto thing_is_obs_to_throwing_over(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_obs_to_throwing_over) != 0;
}

[[nodiscard]] auto thing_is_obs_to_throwing_onto(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_obs_to_throwing_onto) != 0;
}

[[nodiscard]] auto thing_is_unused_98(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused_98) != 0;
}

[[nodiscard]] auto thing_is_tick_on_unwield(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_tick_on_unwield) != 0;
}

[[nodiscard]] auto thing_is_tick_on_wield(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_tick_on_wield) != 0;
}

[[nodiscard]] auto thing_is_buff(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_buff) != 0;
}

[[nodiscard]] auto thing_is_able_to_be_buffed(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_be_buffed) != 0;
}

[[nodiscard]] auto thing_is_tick_on_drop(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_tick_on_drop) != 0;
}

[[nodiscard]] auto thing_is_tick_on_use(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_tick_on_use) != 0;
}

[[nodiscard]] auto thing_is_able_to_throw_items_items(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_throw_items_items) != 0;
}

[[nodiscard]] auto thing_is_throwable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_throwable) != 0;
}

[[nodiscard]] auto thing_is_chest(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_chest) != 0;
}

[[nodiscard]] auto thing_is_flammable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_flammable) != 0;
}

[[nodiscard]] auto thing_is_auto_wield(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_auto_wield) != 0;
}

[[nodiscard]] auto thing_is_able_to_fire_weapons(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_fire_weapons) != 0;
}

[[nodiscard]] auto thing_wieldable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), wieldable) != 0;
}

[[nodiscard]] auto thing_is_able_to_wield_items(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_wield_items) != 0;
}

[[nodiscard]] auto thing_is_wand(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_wand) != 0;
}

[[nodiscard]] auto thing_is_staff(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_staff) != 0;
}

[[nodiscard]] auto thing_is_argusul(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_argusul) != 0;
}

[[nodiscard]] auto thing_is_wait_on_anim(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_wait_on_anim) != 0;
}

[[nodiscard]] auto thing_is_flat(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_flat) != 0;
}

[[nodiscard]] auto thing_is_obs_to_beam(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_obs_to_beam) != 0;
}

[[nodiscard]] auto thing_is_beam_weapon(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_beam_weapon) != 0;
}

[[nodiscard]] auto thing_is_vault(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_vault) != 0;
}

[[nodiscard]] auto thing_is_biome_underhell(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_biome_underhell) != 0;
}

[[nodiscard]] auto thing_is_biome_graveyard(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_biome_graveyard) != 0;
}

[[nodiscard]] auto thing_is_biome_nethervoid(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_biome_nethervoid) != 0;
}

[[nodiscard]] auto thing_is_biome_bogland(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_biome_bogland) != 0;
}

[[nodiscard]] auto thing_is_biome_dungeon(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_biome_dungeon) != 0;
}

[[nodiscard]] auto thing_is_level_open_icon(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_open_icon) != 0;
}

[[nodiscard]] auto thing_is_blit_bg(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_bg) != 0;
}

[[nodiscard]] auto thing_is_level_select_bg(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_level_select_bg) != 0;
}

[[nodiscard]] auto thing_is_blit_hit_outline_w_black_inside(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_hit_outline_w_black_inside) != 0;
}

[[nodiscard]] auto thing_is_blit_hit_outline_w_invis_inside(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_hit_outline_w_invis_inside) != 0;
}

[[nodiscard]] auto thing_is_blit_when_obscured_outline(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_when_obscured_outline) != 0;
}

[[nodiscard]] auto thing_is_effect(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_effect) != 0;
}

[[nodiscard]] auto thing_is_effect_attack(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_effect_attack) != 0;
}

[[nodiscard]] auto thing_is_effect_blood(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_effect_blood) != 0;
}

[[nodiscard]] auto thing_is_blitzhound(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blitzhound) != 0;
}

[[nodiscard]] auto thing_is_potion(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_potion) != 0;
}

[[nodiscard]] auto thing_is_grouped_thing(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_grouped_thing) != 0;
}

[[nodiscard]] auto thing_is_able_to_lunge(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_lunge) != 0;
}

[[nodiscard]] auto thing_is_obs_to_paths(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_obs_to_paths) != 0;
}

[[nodiscard]] auto thing_is_blit_on_ground(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_on_ground) != 0;
}

[[nodiscard]] auto thing_is_insectoid(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_insectoid) != 0;
}

[[nodiscard]] auto thing_is_mantisman(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_mantisman) != 0;
}

[[nodiscard]] auto thing_is_dmap(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_dmap) != 0;
}

[[nodiscard]] auto thing_is_obs_to_spawning(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_obs_to_spawning) != 0;
}

[[nodiscard]] auto thing_is_border(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_border) != 0;
}

[[nodiscard]] auto thing_is_gold(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_gold) != 0;
}

[[nodiscard]] auto thing_is_glass(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_glass) != 0;
}

[[nodiscard]] auto thing_is_plant(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_plant) != 0;
}

[[nodiscard]] auto thing_is_wood(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_wood) != 0;
}

[[nodiscard]] auto thing_is_metal(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_metal) != 0;
}

[[nodiscard]] auto thing_is_flesh(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_flesh) != 0;
}

[[nodiscard]] auto thing_is_stone(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_stone) != 0;
}

[[nodiscard]] auto thing_is_meltable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_meltable) != 0;
}

[[nodiscard]] auto thing_is_blit_per_pixel_lighting(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_per_pixel_lighting) != 0;
}

[[nodiscard]] auto thing_is_cursor_path_warning(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path_warning) != 0;
}

[[nodiscard]] auto thing_is_unused_99(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_unused_99) != 0;
}

[[nodiscard]] auto thing_is_projectile(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_projectile) != 0;
}

[[nodiscard]] auto thing_is_item_mergeable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_item_mergeable) != 0;
}

[[nodiscard]] auto thing_is_door_locked(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_door_locked) != 0;
}

[[nodiscard]] auto thing_is_inventory_item(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_inventory_item) != 0;
}

[[nodiscard]] auto thing_is_able_to_open_things(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_open_things) != 0;
}

[[nodiscard]] auto thing_is_item(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_item) != 0;
}

[[nodiscard]] auto thing_is_able_to_crush_grass(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_crush_grass) != 0;
}

[[nodiscard]] auto thing_is_able_to_collect_keys(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_collect_keys) != 0;
}

[[nodiscard]] auto thing_is_able_to_collect_items(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_collect_items) != 0;
}

[[nodiscard]] auto thing_is_collectable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_collectable) != 0;
}

[[nodiscard]] auto thing_is_blit_when_obscured_faded(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_when_obscured_faded) != 0;
}

[[nodiscard]] auto thing_is_openable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_openable) != 0;
}

[[nodiscard]] auto thing_is_tick_end_delay(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_tick_end_delay) != 0;
}

[[nodiscard]] auto thing_is_physics_explosion(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_physics_explosion) != 0;
}

[[nodiscard]] auto thing_is_explosion(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_explosion) != 0;
}

[[nodiscard]] auto thing_is_obs_to_explosion(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  //
  // Unless open
  //
  if (thing_is_openable(t)) {
    if (thing_is_open(t)) {
      return false;
    }
  }

  return tp_flag(thing_tp(t), is_obs_to_explosion) != 0;
}

[[nodiscard]] auto thing_is_cursor_path_none(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_cursor_path_none) != 0;
}

[[nodiscard]] auto thing_is_able_to_throw_items(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_throw_items) != 0;
}

[[nodiscard]] auto thing_is_blit_obscures(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_obscures) != 0;
}

[[nodiscard]] auto thing_is_flying(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_flying) != 0;
}

[[nodiscard]] auto thing_is_physics_water(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_physics_water) != 0;
}

[[nodiscard]] auto thing_is_indestructible(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_indestructible) != 0;
}

[[nodiscard]] auto thing_is_floating(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_floating) != 0;
}

[[nodiscard]] auto thing_is_obs_to_fire(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  //
  // Unless open
  //
  if (thing_is_openable(t)) {
    if (thing_is_open(t)) {
      return false;
    }
  }

  return tp_flag(thing_tp(t), is_obs_to_fire) != 0;
}

[[nodiscard]] auto thing_is_combustible(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_combustible) != 0;
}

[[nodiscard]] auto thing_is_blit_shown_in_chasms(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_shown_in_chasms) != 0;
}

[[nodiscard]] auto thing_is_gaseous(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_gaseous) != 0;
}

[[nodiscard]] auto thing_is_blit_if_has_seen(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_if_has_seen) != 0;
}

[[nodiscard]] auto thing_is_smoke(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_smoke) != 0;
}

[[nodiscard]] auto thing_is_steam(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_steam) != 0;
}

[[nodiscard]] auto thing_is_fire(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_fire) != 0;
}

[[nodiscard]] auto thing_is_burnable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_burnable) != 0;
}

[[nodiscard]] auto thing_is_loggable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }

  if (g_opt_tests) {
    //
    // Everything is logged
    //
    return true;
  }

  IF_DEBUG2
  {
    //
    // Everything is logged
    //
    return true;
  }

  return tp_flag(thing_tp(t), is_loggable) != 0;
}

[[nodiscard]] auto thing_is_crushable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_crushable) != 0;
}

[[nodiscard]] auto thing_is_ethereal(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_ethereal) != 0;
}

[[nodiscard]] auto thing_is_blit_shown_in_overlay(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_blit_shown_in_overlay) != 0;
}

[[nodiscard]] auto thing_is_levitating(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_levitating) != 0;
}

[[nodiscard]] auto thing_is_equippable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_equippable) != 0;
}

[[nodiscard]] auto thing_is_droppable(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_droppable) != 0;
}

[[nodiscard]] auto thing_is_able_to_walk_through_walls(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_able_to_walk_through_walls) != 0;
}

[[nodiscard]] auto thing_value1(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value1;
}

[[nodiscard]] auto thing_value1_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value1 = val;
}

[[nodiscard]] auto thing_value1_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value1 += val;
}

[[nodiscard]] auto thing_value1_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value1) - val <= 0) {
    return t->_value1 = 0;
  }
  return t->_value1 -= val;
}
[[nodiscard]] auto thing_value2(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value2;
}

[[nodiscard]] auto thing_value2_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value2 = val;
}

[[nodiscard]] auto thing_value2_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value2 += val;
}

[[nodiscard]] auto thing_value2_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value2) - val <= 0) {
    return t->_value2 = 0;
  }
  return t->_value2 -= val;
}
[[nodiscard]] auto thing_value3(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value3;
}

[[nodiscard]] auto thing_value3_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value3 = val;
}

[[nodiscard]] auto thing_value3_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value3 += val;
}

[[nodiscard]] auto thing_value3_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value3) - val <= 0) {
    return t->_value3 = 0;
  }
  return t->_value3 -= val;
}
[[nodiscard]] auto thing_value4(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value4;
}

[[nodiscard]] auto thing_value4_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value4 = val;
}

[[nodiscard]] auto thing_value4_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value4 += val;
}

[[nodiscard]] auto thing_value4_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value4) - val <= 0) {
    return t->_value4 = 0;
  }
  return t->_value4 -= val;
}
[[nodiscard]] auto thing_value5(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value5;
}

[[nodiscard]] auto thing_value5_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value5 = val;
}

[[nodiscard]] auto thing_value5_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value5 += val;
}

[[nodiscard]] auto thing_value5_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value5) - val <= 0) {
    return t->_value5 = 0;
  }
  return t->_value5 -= val;
}
[[nodiscard]] auto thing_value6(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value6;
}

[[nodiscard]] auto thing_value6_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value6 = val;
}

[[nodiscard]] auto thing_value6_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value6 += val;
}

[[nodiscard]] auto thing_value6_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value6) - val <= 0) {
    return t->_value6 = 0;
  }
  return t->_value6 -= val;
}
[[nodiscard]] auto thing_value7(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value7;
}

[[nodiscard]] auto thing_value7_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value7 = val;
}

[[nodiscard]] auto thing_value7_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value7 += val;
}

[[nodiscard]] auto thing_value7_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value7) - val <= 0) {
    return t->_value7 = 0;
  }
  return t->_value7 -= val;
}
[[nodiscard]] auto thing_value8(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value8;
}

[[nodiscard]] auto thing_value8_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value8 = val;
}

[[nodiscard]] auto thing_value8_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value8 += val;
}

[[nodiscard]] auto thing_value8_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value8) - val <= 0) {
    return t->_value8 = 0;
  }
  return t->_value8 -= val;
}
[[nodiscard]] auto thing_value9(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value9;
}

[[nodiscard]] auto thing_value9_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value9 = val;
}

[[nodiscard]] auto thing_value9_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value9 += val;
}

[[nodiscard]] auto thing_value9_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value9) - val <= 0) {
    return t->_value9 = 0;
  }
  return t->_value9 -= val;
}
[[nodiscard]] auto thing_value10(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value10;
}

[[nodiscard]] auto thing_value10_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value10 = val;
}

[[nodiscard]] auto thing_value10_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value10 += val;
}

[[nodiscard]] auto thing_value10_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value10) - val <= 0) {
    return t->_value10 = 0;
  }
  return t->_value10 -= val;
}
[[nodiscard]] auto thing_value11(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value11;
}

[[nodiscard]] auto thing_value11_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value11 = val;
}

[[nodiscard]] auto thing_value11_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value11 += val;
}

[[nodiscard]] auto thing_value11_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value11) - val <= 0) {
    return t->_value11 = 0;
  }
  return t->_value11 -= val;
}
[[nodiscard]] auto thing_value12(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value12;
}

[[nodiscard]] auto thing_value12_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value12 = val;
}

[[nodiscard]] auto thing_value12_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_value12 += val;
}

[[nodiscard]] auto thing_value12_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_value12) - val <= 0) {
    return t->_value12 = 0;
  }
  return t->_value12 -= val;
}
[[nodiscard]] auto thing_hearing_threshold(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_hearing_threshold;
}

[[nodiscard]] auto thing_hearing_threshold_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_hearing_threshold = val;
}

[[nodiscard]] auto thing_hearing_threshold_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_hearing_threshold += val;
}

[[nodiscard]] auto thing_hearing_threshold_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_hearing_threshold) - val <= 0) {
    return t->_hearing_threshold = 0;
  }
  return t->_hearing_threshold -= val;
}
[[nodiscard]] auto thing_distance_avoid_target(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_distance_avoid_target;
}

[[nodiscard]] auto thing_distance_avoid_target_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_distance_avoid_target = val;
}

[[nodiscard]] auto thing_distance_avoid_target_incr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_distance_avoid_target += val;
}

[[nodiscard]] auto thing_distance_avoid_target_decr(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  if (static_cast< int >(t->_distance_avoid_target) - val <= 0) {
    return t->_distance_avoid_target = 0;
  }
  return t->_distance_avoid_target -= val;
}

[[nodiscard]] auto thing_variant(Thingp t) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_variant;
}

[[nodiscard]] auto thing_variant_set(Gamep g, Levelsp v, Levelp l, Thingp t, int val) -> int
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return 0;
  }
  return t->_variant = val;
}

[[nodiscard]] auto thing_priority(Thingp t) -> ThingPriorityType
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return THING_PRIORITY_LOWEST;
  }
  if (thing_is_dead(t)) {
    return THING_PRIORITY_DEAD;
  }
  return t->_priority;
}

[[nodiscard]] auto thing_priority_set(Gamep g, Levelsp v, Levelp l, Thingp t, ThingPriorityType val) -> ThingPriorityType
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return THING_PRIORITY_LOWEST;
  }
  return t->_priority = val;
}
