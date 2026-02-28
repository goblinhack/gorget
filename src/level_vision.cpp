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

    FovContext ctx;

    ctx.g                  = g;
    ctx.v                  = v;
    ctx.l                  = l;
    ctx.me                 = t;
    ctx.pov                = thing_at(t);
    ctx.thing_at_in_pixels = thing_pix_at(t);
    ctx.max_radius         = max_radius;
    ctx.fov_can_see_tile   = &ext->can_see;
    ctx.fov_has_seen_tile  = &ext->has_seen;

    level_fov(ctx);
  }
}
