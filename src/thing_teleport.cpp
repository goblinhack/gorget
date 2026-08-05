//
// Copyright goblinhack@gmail.com
//

#include "my_bpoint.hpp"
#include "my_callstack.hpp"
#include "my_cpp_template.hpp"
#include "my_fpoint.hpp"
#include "my_game_defs.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp" // NOLINT
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp" // NOLINT
#include "my_tp.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"
#include <cstdint>
#include <initializer_list>
#include <vector>

[[nodiscard]] auto thing_is_teleporting(Thingp me) -> bool
{
  TRACE_DEBUG();

  if (me == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return me->_is_teleporting;
}

void thing_is_teleporting_set(Gamep g, Levelsp v, Levelp l, Thingp me, bool val)
{
  TRACE_DEBUG();

  if (me == nullptr) {
    ERR("no thing pointer");
    return;
  }

  if (me->_is_teleporting == static_cast< int >(val)) {
    return;
  }
  me->_is_teleporting = val;

  if (val) {
    thing_on_teleported(g, v, l, me);
  }
}

void thing_is_teleporting_unset(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_DEBUG();

  thing_is_teleporting_set(g, v, l, me, false);
}

[[nodiscard]] static auto teleport_find_other(Gamep g, Levelsp v, Levelp l, const bpoint &in, bpoint &out) -> bool
{
  TRACE();

  std::vector< Thingp > teleports;

  FOR_ALL_THINGS_ON_LEVEL(g, v, l, me)
  {
    if (thing_at(g, v, l, me) == in) {
      continue;
    }

    if (thing_is_teleport(me)) {
      teleports.push_back(me);
    }
  }

  if (teleports.empty()) {
    return false;
  }

  auto *other = pcg_rand_one_of(teleports);

  if (other != nullptr) {
    //
    // Sets reference
    //
    out = thing_at(g, v, l, other);
    return true;
  }

  return false;
}

//
// Find a spot next to the teleport where we can land.
//
[[nodiscard]] static auto teleport_find_landing_spot(Gamep g, Levelsp v, Levelp l, Thingp me, bpoint &out, int attempt) -> bool
{
  auto   outf  = make_fpoint(out);
  fpoint delta = thing_real_at(g, v, l, me) - make_fpoint(thing_old_at(me));
  fpoint tof   = outf + delta;
  bpoint to    = make_bpoint(tof);

  THING_DBG(g, v, l, me, "find a landing spot, target (%d,%d)", to.x, to.y);
  TRACE_INDENT();

  //
  // No need to check for collisions for things like projectile_fires otherwise we will
  // not be able to say fire through a teleport and hit a barrel.
  //
  if (thing_is_projectile(me) || thing_is_beam_weapon(me)) {
    delta = thing_get_direction(g, v, l, me);
    tof   = outf + delta;
    to    = make_bpoint(tof);
    out   = to;
    THING_DBG(g, v, l, me, "teleport projectile, delta %f,%f bpoint %d,%d", delta.x, delta.y, to.x, to.y);
    return true;
  }

  if (attempt == 0) {
    if ((delta == fpoint(0, 0)) || (level_is_obs_to_teleporting_onto(g, v, l, to) != nullptr)) {
      delta = thing_get_direction(g, v, l, me);
      tof   = outf + delta;
      to    = make_bpoint(tof);
      THING_DBG(g, v, l, me, "found a landing spot (%d,%d) (1)", to.x, to.y);
    }

    if ((delta == fpoint(0, 0)) || (level_is_obs_to_teleporting_onto(g, v, l, to) != nullptr)) {
      delta = thing_get_direction(g, v, l, me);
      tof   = outf + delta;
      to    = make_bpoint(tof);
      THING_DBG(g, v, l, me, "found a landing spot (%d,%d) (2)", to.x, to.y);
    }
  }

  //
  //  x
  // x.x
  //  x
  //
  if ((delta == fpoint(0, 0)) || (level_is_obs_to_teleporting_onto(g, v, l, to) != nullptr)) {
    const std::initializer_list< fpoint > deltas = {
        fpoint(1, 0),
        fpoint(-1, 0),
        fpoint(0, 1),
        fpoint(0, -1),
    };

    std::vector< bpoint > cands;

    for (auto d : deltas) {
      delta = d;
      tof   = outf + delta;
      to    = make_bpoint(tof);
      if (level_is_obs_to_teleporting_onto(g, v, l, to) == nullptr) {
        cands.push_back(to);
        THING_DBG(g, v, l, me, "found a landing spot cand (%d,%d) (3)", to.x, to.y);
      }
    }

    if (cands.size()) {
      to  = pcg_rand_one_of(cands);
      out = to;
      THING_DBG(g, v, l, me, "found a landing spot (%d,%d) (4)", to.x, to.y);
      return true;
    }
  }

  //
  // x x
  //  .
  // x x
  //
  if ((delta == fpoint(0, 0)) || (level_is_obs_to_teleporting_onto(g, v, l, to) != nullptr)) {
    const std::initializer_list< fpoint > deltas = {
        fpoint(1, 0),
        fpoint(-1, 0),
        fpoint(0, 1),
        fpoint(0, -1),
    };

    std::vector< bpoint > cands;

    for (auto d : deltas) {
      delta = d;
      tof   = outf + delta;
      to    = make_bpoint(tof);
      if (level_is_obs_to_teleporting_onto(g, v, l, to) == nullptr) {
        cands.push_back(to);
        THING_DBG(g, v, l, me, "found a landing spot cand (%d,%d) (3)", to.x, to.y);
      }
    }

    if (cands.size()) {
      to  = pcg_rand_one_of(cands);
      out = to;
      THING_DBG(g, v, l, me, "found a landing spot (%d,%d) (4)", to.x, to.y);
      return true;
    }
  }

  tof = outf + delta;
  to  = make_bpoint(tof);

  if (compiler_unused) {
    THING_DBG(g, v, l, me, "delta %f,%f bpoint %d,%d out %d,%d", delta.x, delta.y, to.x, to.y, out.x, out.y);
  }

  if (level_is_obs_to_teleporting_onto(g, v, l, to) != nullptr) {
    //
    // Not sure how this happens, but we need the teleport to take us somewhere.
    //
    return false;
  }

  if (delta == fpoint(0, 0)) {
    //
    // This can happen if the teleport is surrounded by chasms
    //
    return false;
  }

  out = to;
  THING_DBG(g, v, l, me, "landing spot (%d,%d)", out.x, out.y);
  return true;
}

//
// Find a safe spot next to the teleport where we can land (depending on luck).
//
[[nodiscard]] static auto teleport_find_maybe_safe_landing_spot(Gamep g, Levelsp v, Levelp l, Thingp me, bpoint &target) -> bool
{
  THING_DBG(g, v, l, me, "find a maybe safe landing spot, target (%d,%d)", target.x, target.y);
  TRACE_INDENT();

  //
  // Where do we spawn?
  //
  for (auto attempt = 0; attempt < 100; attempt++) {
    bpoint out = target;

    //
    // Find a place to teleport that is not an obstacle.
    //
    if (! teleport_find_landing_spot(g, v, l, me, out, attempt)) {
      THING_DBG(g, v, l, me, "failed to find landing spot next to chosen teleport");
      return false;
    }

    if (level_is_teleport_hazard_bool(g, v, l, out)) {
      THING_DBG(g, v, l, me, "target is on a hazard (%d,%d)", out.x, out.y);
      TRACE_INDENT();

      //
      // Teleport destination is a hazard
      //
      if (thing_stat_success(g, v, l, me, THING_STAT_LUCK, TARGET_ROLL_TELEPORT_HAZARD)) {
        //
        // Lucky. Try again.
        //
        THING_DBG(g, v, l, me, "found an unsafe landing spot (%d,%d); try again", out.x, out.y);
        continue;
      }

      //
      // Unlucky. You land in something bad.
      //
      if (thing_is_player(me)) {
        if (level_is_chasm_bool(g, v, l, out)) {
          topcon(UI_IMPORTANT_FMT_STR "Bad luck. You teleport onto a chasm!" UI_RESET_FMT);
        } else if (level_is_lava_bool(g, v, l, out)) {
          topcon(UI_IMPORTANT_FMT_STR "Bad luck. You teleport into lava!" UI_RESET_FMT);
        } else {
          topcon(UI_IMPORTANT_FMT_STR "You feel unlucky with that teleport." UI_RESET_FMT);
        }
      }

      THING_DBG(g, v, l, me, "found an unsafe landing spot (%d,%d)", out.x, out.y);
      target = out;
      return true;
    }

    //
    // No hazard
    //
    THING_DBG(g, v, l, me, "found a landing spot (%d,%d)", out.x, out.y);
    target = out;
    return true;
  }

  return false;
}

//
// Handles player and monster teleports
//
[[nodiscard]] static auto thing_teleport_to(Gamep g, Levelsp v, Levelp l, Thingp me, const bpoint to) -> bool
{
  THING_DBG(g, v, l, me, "pre teleport, warp to (%d,%d)", to.x, to.y);
  TRACE_INDENT();

  if (! thing_warp_to(g, v, l, me, to)) {
    THING_DBG(g, v, l, me, "pre teleport, warp to (%d,%d) failed", to.x, to.y);
    return false;
  }

  thing_is_teleporting_set(g, v, l, me);

  v->scroll_speed = MAP_SCROLL_TELEPORT_SPEED;

  thing_is_teleporting_set(g, v, l, me, false);

  THING_DBG(g, v, l, me, "post teleport");
  TRACE_INDENT();

  thing_sound_play(g, v, l, me, "teleport");

  me->tick_teleport = v->tick;

  return true;
}

//
// Handles player and monster teleports
//
[[nodiscard]] auto thing_teleport_handle(Gamep g, Levelsp v, Levelp l, Thingp me) -> bool
{
  THING_DBG(g, v, l, me, "teleport, try");
  TRACE_INDENT();

  if (me->tick_teleport != 0U) {
    if (me->tick_teleport == v->tick) {
      THING_DBG(g, v, l, me, "teleport, no; too frequent");
      return false;
    }
  }

  if (thing_is_teleporting(me)) {
    THING_DBG(g, v, l, me, "teleport, no; already teleporting");
    return false;
  }

  if (thing_is_teleport_blocked(me)) {
    THING_DBG(g, v, l, me, "teleport, no; blocked");
    return false;
  }

  bpoint to;
  if (! teleport_find_other(g, v, l, thing_at(g, v, l, me), to)) {
    THING_DBG(g, v, l, me, "teleport, no; none found");
    return false;
  }

  if (is_oob_or_border(to)) [[unlikely]] {
    THING_DBG(g, v, l, me, "teleport, no; oob");
    return false;
  }

  //
  // Find a place to teleport that is not an obstacle.
  //
  if (! teleport_find_maybe_safe_landing_spot(g, v, l, me, to)) {
    THING_DBG(g, v, l, me, "failed to find landing spot next to chosen teleport");
    return false;
  }

  if (to == thing_at(g, v, l, me)) {
    THING_DBG(g, v, l, me, "teleport, no; same location");
    return false;
  }

  return thing_teleport_to(g, v, l, me, to);
}

//
// Handles player and monster random teleports
//
[[nodiscard]] auto thing_teleport_random(Gamep g, Levelsp v, Levelp l, Thingp me) -> bool
{
  THING_DBG(g, v, l, me, "teleport, try");
  TRACE_INDENT();

  if (me->tick_teleport != 0U) {
    if (me->tick_teleport == v->tick) {
      THING_DBG(g, v, l, me, "teleport, no; too frequent");
      return false;
    }
  }

  if (thing_is_teleporting(me)) {
    THING_DBG(g, v, l, me, "teleport, no; already teleporting");
    return false;
  }

  if (thing_is_teleport_blocked(me)) {
    THING_DBG(g, v, l, me, "teleport, no; blocked");
    return false;
  }

  bpoint to;
  bool   got_one {};
  auto   at = thing_at(g, v, l, me);

  //
  // Find somewhere random to land
  //
  for (auto attempt = 0; attempt < 1000; attempt++) {
    uint8_t const border = MAP_BORDER;
    to.x                 = PCG_RANDOM_RANGE(border, (uint8_t) MAP_WIDTH - border);
    to.y                 = PCG_RANDOM_RANGE(border, (uint8_t) MAP_HEIGHT - border);

    if (is_oob_or_border(to)) [[unlikely]] {
      THING_DBG(g, v, l, me, "teleport, no; oob");
      continue;
    }

    if (distance(to, at) < MAP_WIDTH / 4) {
      THING_DBG(g, v, l, me, "teleport, no; too close");
      continue;
    }

    if (attempt < 100) {
      if (l->info.on_path_entrance_to_exit[ to.x ][ to.y ] == 0U) {
        THING_DBG(g, v, l, me, "teleport, no; not on safe path");
        continue;
      }
    }

    if (level_is_teleport_hazard_bool(g, v, l, to)) {
      continue;
    }

    if (! teleport_find_maybe_safe_landing_spot(g, v, l, me, to)) {
      THING_DBG(g, v, l, me, "failed to find a random landing spot");
      continue;
    }

    got_one = true;
    break;
  }

  //
  // Try again, but look at all tiles
  //
  if (! got_one) {
    for (uint8_t y = MAP_BORDER; y < MAP_HEIGHT - MAP_BORDER; y++) {
      for (uint8_t x = MAP_BORDER; x < MAP_WIDTH - MAP_BORDER; x++) {
        to.x = x;
        to.y = y;

        if (is_oob_or_border(to)) [[unlikely]] {
          THING_DBG(g, v, l, me, "teleport, no; oob");
          continue;
        }

        if (distance(to, at) < MAP_WIDTH / 4) {
          THING_DBG(g, v, l, me, "teleport, no; too close");
          continue;
        }

        if (l->info.on_path_entrance_to_exit[ to.x ][ to.y ] == 0U) {
          THING_DBG(g, v, l, me, "teleport, no; not on safe path");
          continue;
        }

        if (level_is_teleport_hazard_bool(g, v, l, to)) {
          continue;
        }

        if (! teleport_find_maybe_safe_landing_spot(g, v, l, me, to)) {
          THING_DBG(g, v, l, me, "failed to find a random landing (2)");
          continue;
        }

        got_one = true;
        break;
      }

      if (got_one) {
        break;
      }
    }
  }

  //
  // Ignore the entrance to exit path
  //
  if (! got_one) {
    for (uint8_t y = MAP_BORDER; y < MAP_HEIGHT - MAP_BORDER; y++) {
      for (uint8_t x = MAP_BORDER; x < MAP_WIDTH - MAP_BORDER; x++) {
        to.x = x;
        to.y = y;

        if (is_oob_or_border(to)) [[unlikely]] {
          THING_DBG(g, v, l, me, "teleport, no; oob");
          continue;
        }

        if (distance(to, at) < MAP_WIDTH / 4) {
          THING_DBG(g, v, l, me, "teleport, no; too close");
          continue;
        }

        if (level_is_teleport_hazard_bool(g, v, l, to)) {
          continue;
        }

        if (! teleport_find_landing_spot(g, v, l, me, to, 0)) {
          THING_DBG(g, v, l, me, "failed to find a random landing (3)");
          continue;
        }

        got_one = true;
        break;
      }

      if (got_one) {
        break;
      }
    }
  }

  //
  // Ignore the entrance to exit path. Consider hazard tiles.
  //
  if (! got_one) {
    for (uint8_t y = MAP_BORDER; y < MAP_HEIGHT - MAP_BORDER; y++) {
      for (uint8_t x = MAP_BORDER; x < MAP_WIDTH - MAP_BORDER; x++) {
        to.x = x;
        to.y = y;

        if (is_oob_or_border(to)) [[unlikely]] {
          THING_DBG(g, v, l, me, "teleport, no; oob");
          continue;
        }

        if (distance(to, at) < MAP_WIDTH / 4) {
          THING_DBG(g, v, l, me, "teleport, no; too close");
          continue;
        }

        if (! teleport_find_landing_spot(g, v, l, me, to, 0)) {
          THING_DBG(g, v, l, me, "failed to find a random landing (3)");
          continue;
        }

        got_one = true;
        break;
      }

      if (got_one) {
        break;
      }
    }
  }

  //
  // Very last chance
  //
  if (! got_one) {
    for (uint8_t y = MAP_BORDER; y < MAP_HEIGHT - MAP_BORDER; y++) {
      for (uint8_t x = MAP_BORDER; x < MAP_WIDTH - MAP_BORDER; x++) {
        to.x = x;
        to.y = y;

        if (is_oob_or_border(to)) [[unlikely]] {
          THING_DBG(g, v, l, me, "teleport, no; oob");
          continue;
        }

        if (to == at) {
          THING_DBG(g, v, l, me, "teleport, no; same location");
          continue;
        }

        got_one = true;
        break;
      }

      if (got_one) {
        break;
      }
    }
  }

  if (! got_one) {
    return false;
  }

  return thing_teleport_to(g, v, l, me, to);
}

[[nodiscard]] auto thing_is_teleport(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_teleport) != 0;
}

[[nodiscard]] auto thing_is_teleport_blocked(Thingp t) -> bool
{
  TRACE_DEBUG();

  if (t == nullptr) {
    ERR("no thing pointer");
    return false;
  }
  return tp_flag(thing_tp(t), is_teleport_blocked) != 0;
}

[[nodiscard]] auto thing_is_obs_to_teleporting_onto(Thingp t) -> bool
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

  return tp_flag(thing_tp(t), is_obs_to_teleporting_onto) != 0;
}
