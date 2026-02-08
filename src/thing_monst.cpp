//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_cpp_template.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_line.hpp"
#include "my_main.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_wid_warning.hpp"

[[nodiscard]] static bool thing_minion_choose_target_near_mob(Gamep g, Levelsp v, Levelp l, Thingp minion,
                                                              spoint &target)
{
  TRACE_NO_INDENT();

  auto mob = thing_minion_mob_get(g, v, l, minion);
  if (! mob) {
    //
    // Acceptable when the minion is detached
    //
    return false;
  }

  auto mob_ext = thing_ext_struct(g, mob);
  if (! mob_ext) {
    THING_ERR(minion, "mob has no ext memory");
    return false;
  }

  auto                  minion_at = thing_at(minion);
  auto                  mob_at    = thing_at(mob);
  std::vector< spoint > cands;

  auto dmap = &mob_ext->dmap;
  THING_LOG(mob, "mob");
  dmap_print(dmap, mob_at, spoint(0, 0), spoint(MAP_WIDTH - 1, MAP_HEIGHT - 1));

  auto distance_minion_from_mob_max = thing_distance_minion_from_mob_max(minion);
  for (int x = -distance_minion_from_mob_max; x <= distance_minion_from_mob_max; x++) {
    for (int y = -distance_minion_from_mob_max; y <= distance_minion_from_mob_max; y++) {
      spoint p(x + mob_at.x, y + mob_at.y);
      if (is_oob(p)) {
        continue;
      }

      if (p == minion_at) {
        continue;
      }

      if (p == mob_at) {
        continue;
      }

      if (level_is_obs_to_movement(g, v, l, p)) {
        continue;
      }

      if (level_is_monst(g, v, l, p)) {
        continue;
      }

      if (dmap->val[ p.x ][ p.y ] >= distance_minion_from_mob_max) {
        continue;
      }

      cands.push_back(p);
    }
  }

  if (! cands.size()) {
    return false;
  }

  auto tries = cands.size();
  while (tries--) {
    target = pcg_rand_one_of(cands);

    THING_LOG(minion, "allow diag");
    thing_astar_solve(g, v, l, minion, minion_at, target, dmap, true /* diag */);
    THING_LOG(minion, "block diag");
    thing_astar_solve(g, v, l, minion, minion_at, target, dmap, false /* diag */);
#if 0
    auto p         = dmap_solve(g, v, l, minon, dmap, minion_at);
    auto path_size = p.size();
    if (! path_size) {
      return empty;
    }

    //
    // If we could not reach the target, then the path will just plot the distance from the start, which is not what
    // we want.
    //
    if (p[ path_size - 1 ] != end) {
      if (0) {
        LOG("did not reach %d,%d", end.x, end.y);
      }
      return empty;
    }
#endif
  }

  if (0) {
    THING_LOG(minion, "%s", __FUNCTION__);
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      std::string out;
      for (auto x = 0; x < MAP_WIDTH; x++) {
        char   c = {};
        spoint p(x, y);

        if (! c && (p == target)) {
          c = '*';
        }

        if (! c) {
          for (auto cand : cands) {
            if (p == cand) {
              c = '_';
              break;
            }
          }
        }

        if (! c && (p == minion_at)) {
          c = '@';
        }
        if (! c && (p == mob_at)) {
          c = 'G';
        }
        if (! c && level_is_obs_to_movement(g, v, l, p)) {
          c = 'X';
        }
        if (! c && level_is_monst(g, v, l, p)) {
          c = 'm';
        }
        if ((p == mob_at)) {
          c = 'G';
        }
        if (! c) {
          c = '.';
        }
        out += c;
      }
      THING_LOG(minion, "%s", out.c_str());
    }
  }
  TOPCON(".");

  return true;
}

[[nodiscard]] static bool thing_monst_choose_target(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (thing_is_minion(t)) {
    spoint target;
    if (thing_minion_choose_target_near_mob(g, v, l, t, target)) {
      return true;
    }
  }

  return false;
}

//
// Called per tick
//
void thing_monst_event_loop(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  switch (monst_state(g, v, l, t)) {
    case MONST_STATE_INIT : // newline
      monst_state_change(g, v, t, MONST_STATE_NORMAL);
    case MONST_STATE_NORMAL :
      // newline
      (void) thing_monst_choose_target(g, v, l, t);
      break;
    case MONST_STATE_DEAD :
      // newline
      break;
    case MONST_STATE_PATH_REQUESTED :
      // newline
      break;
    case MONST_STATE_FOLLOWING_PATH :
      // newline
      break;
    case MONST_STATE_ENUM_MAX : break;
  }
}

std::string monst_state_to_string(MonstState state)
{
  TRACE_NO_INDENT();
  return MonstState_to_string(state);
}

MonstState monst_state(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  return t->_monst_state;
}

void monst_state_change(Gamep g, Levelsp v, Thingp t, MonstState new_state)
{
  TRACE_NO_INDENT();

  auto old_state = t->_monst_state;

  switch (old_state) {
    case MONST_STATE_INIT :
      // newline
      break;
    case MONST_STATE_DEAD :
      // newline
      return;
    case MONST_STATE_NORMAL :
      // newline
      break;
    case MONST_STATE_PATH_REQUESTED :
      // newline
      break;
    case MONST_STATE_FOLLOWING_PATH :
      // newline
      break;
    case MONST_STATE_ENUM_MAX : break;
  }

  if (t->_monst_state == new_state) {
    return;
  }

  //
  // Set here to stop recursion.
  //
  t->_monst_state = new_state;

  //
  // Why oh why change state
  //
  THING_LOG(t, "state change: %s -> %s", monst_state_to_string(old_state).c_str(),
            monst_state_to_string(new_state).c_str());

  switch (new_state) {
    case MONST_STATE_INIT :
      // newline
      break;
    case MONST_STATE_DEAD :
      // newline
      break;
    case MONST_STATE_NORMAL :
      // newline
      break;
    case MONST_STATE_PATH_REQUESTED :
      // newline
      break;
    case MONST_STATE_FOLLOWING_PATH :
      // newline
      break;
    case MONST_STATE_ENUM_MAX : break;
  }
}
