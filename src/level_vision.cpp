//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_thing_inlines.hpp"

//
// What can monsters see?
//
void level_vision_calculate_all(Gamep g, Levelsp v, Levelp l)
{
  TRACE();

  if (((g == nullptr) || (v == nullptr) || (l == nullptr))) [[unlikely]] {
    return;
  }

  auto *player = thing_player(g);
  if (player == nullptr) [[unlikely]] {
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
    if (ext == nullptr) [[unlikely]] {
      continue;
    }

    if ((thing_is_player(t))) [[unlikely]] {
      continue;
    }

    level_fov_can_see_callback_t callback = nullptr;
    level_fov(g, v, l, t, &ext->can_see, &ext->has_seen, thing_at(t), max_radius, callback);
  }
}
