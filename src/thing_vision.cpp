//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_thing_inlines.hpp"

void thing_vision_reset(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

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
  TRACE_NO_INDENT();

  auto *ext = thing_ext_struct(g, t);
  if (ext == nullptr) {
    return false;
  }

  if (IS_OOB(p)) {
    return false;
  }

  //
  // Check the thing is on the same level.
  //
  auto *t_level = game_level_get(g, v, t->level_num);
  if ((t_level != nullptr) && (t_level != l)) {
    return false;
  }

  return fov_map_get(&ext->can_see, p.x, p.y) != 0U;
}

auto thing_vision_player_has_seen_tile(Gamep g, Levelsp v, Levelp l, spoint p) -> bool
{
  TRACE_NO_INDENT();

  auto *player = thing_player(g);
  if (! player) {
    return false;
  }

  auto *ext = thing_ext_struct(g, player);
  if (ext == nullptr) {
    return false;
  }

  if (IS_OOB(p)) {
    return false;
  }

  return fov_map_get(&ext->has_seen, p.x, p.y) != 0U;
}

void thing_can_see_dump(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  auto *ext = thing_ext_struct(g, t);
  if (ext == nullptr) {
    return;
  }

  THING_LOG(t, "can see:");

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    std::string debug;
    for (auto x = 0; x < MAP_WIDTH; x++) {
      spoint p(x, y);

      if (p == thing_at(t)) {
        debug += "@";
        continue;
      }

      if (level_is_wall(g, v, l, p)) {
        debug += "#";
        continue;
      }

      if (fov_map_get(&ext->can_see, p.x, p.y) != 0U) {
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
  if (ext == nullptr) {
    return;
  }

  THING_LOG(t, "has seen:");

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    std::string debug;
    for (auto x = 0; x < MAP_WIDTH; x++) {
      spoint p(x, y);

      if (p == thing_at(t)) {
        debug += "@";
        continue;
      }

      if (level_is_wall(g, v, l, p)) {
        debug += "#";
        continue;
      }

      if (fov_map_get(&ext->has_seen, p.x, p.y) != 0U) {
        debug += "*";
        continue;
      }

      debug += ".";
    }

    THING_LOG(t, "has seen: %s", debug.c_str());
  }
}

//
// What can monsters see?
//
void thing_vision_calculate_all(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  auto *player = thing_player(g);
  if (player == nullptr) {
    return;
  }

  if ((g == nullptr) || (v == nullptr) || (l == nullptr)) {
    return;
  }

  //
  // If the player is not on the level being lit, then nothing to do
  //
  if (l->level_num != player->level_num) {
    return;
  }

  //
  // Calculate all lit tiles for non player things
  //
  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t)
  {
    auto max_radius = thing_distance_vision(t);
    if (max_radius == 0) {
      continue;
    }

    auto *ext = thing_ext_struct(g, t);
    if (! ext) {
      continue;
    }

    if (thing_is_player(t)) {
      continue;
    }

    level_fov_can_see_callback_t callback = nullptr;
    level_fov(g, v, l, t, &ext->can_see, &ext->has_seen, thing_at(t), max_radius, callback);
  }
}
