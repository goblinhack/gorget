//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_thing_inlines.hpp"

void thing_vision_reset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE();

  auto *ext = thing_ext_struct(g, t);
  if (ext != nullptr) {
    ext->has_seen = {{0}};
  }

  auto *light = thing_light_struct(g, t);
  if (light != nullptr) {
    light->is_lit = {{0}};
  }
}

auto thing_vision_can_see_tile(Gamep g, Levelsp v, Levelp l, Thingp t, spoint p) -> bool
{
  TRACE();

  auto *ext = thing_ext_struct(g, t);
  if (ext == nullptr) [[unlikely]] {
    return false;
  }

  if (is_oob(p)) [[unlikely]] {
    return false;
  }

  //
  // Check the thing is on the same level.
  //
  auto *t_level = game_level_get(g, v, t->level_num);
  if ((t_level != nullptr) && (t_level != l)) {
    return false;
  }

  return static_cast< unsigned int >(fov_map_get(&ext->can_see, p.x, p.y)) != 0U;
}

auto thing_vision_player_has_seen_tile(Gamep g, Levelsp v, Levelp l, const spoint &p) -> bool
{
  TRACE();

  auto *player = thing_player(g);
  if (player == nullptr) [[unlikely]] {
    return false;
  }

  auto *ext = thing_ext_struct(g, player);
  if (ext == nullptr) [[unlikely]] {
    return false;
  }

  if (is_oob(p)) [[unlikely]] {
    return false;
  }

  return static_cast< unsigned int >(fov_map_get(&ext->has_seen, p.x, p.y)) != 0U;
}

void thing_can_see_dump(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  auto *ext = thing_ext_struct(g, t);
  if (ext == nullptr) [[unlikely]] {
    return;
  }

  THING_LOG(t, "can see:");

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    std::string debug;
    for (auto x = 0; x < MAP_WIDTH; x++) {
      spoint const p(x, y);

      if (p == thing_at(t)) {
        debug += "@";
        continue;
      }

      if (level_is_wall(g, v, l, p) != nullptr) {
        debug += "#";
        continue;
      }

      if (static_cast< unsigned int >(fov_map_get(&ext->can_see, p.x, p.y)) != 0U) {
        debug += "*";
        continue;
      }

      debug += ".";
    }

    THING_LOG(t, "can see: %s", debug.c_str());
  }
}

void thing_has_seen_dump(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  auto *ext = thing_ext_struct(g, t);
  if (ext == nullptr) [[unlikely]] {
    return;
  }

  THING_LOG(t, "has seen:");

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    std::string debug;
    for (auto x = 0; x < MAP_WIDTH; x++) {
      spoint const p(x, y);

      if (p == thing_at(t)) {
        debug += "@";
        continue;
      }

      if (level_is_wall(g, v, l, p) != nullptr) {
        debug += "#";
        continue;
      }

      if (static_cast< unsigned int >(fov_map_get(&ext->has_seen, p.x, p.y)) != 0U) {
        debug += "*";
        continue;
      }

      debug += ".";
    }

    THING_LOG(t, "has seen: %s", debug.c_str());
  }
}
