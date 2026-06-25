//
// Copyright goblinhack@gmail.com
//

#include "my_bpoint.hpp"
#include "my_callstack.hpp"
#include "my_dmap.hpp"
#include "my_game.hpp"
#include "my_game_defs.hpp"
#include "my_level.hpp"
#include "my_level_inlines.hpp"
#include "my_line.hpp"
#include "my_main.hpp"
#include "my_thing.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

void level_hearing_gen(Gamep g, Levelsp v, Levelp l)
{
  TRACE();

  auto *player = thing_player(g);
  if (! player) {
    return;
  }

  //
  // If the player is not on the level being lit, then nothing to do
  //
  if (l->level_num != player->level_num) {
    return;
  }

  auto dmap = &v->dmap_noise;
  memset(dmap, DMAP_IS_WALL, sizeof(*dmap));

  auto noise_level = thing_noise_this_tick(player);
  if (! noise_level) {
    return;
  }

  auto   end = thing_at(player);
  bpoint dmap_start(end.x - noise_level, end.y - noise_level);
  bpoint dmap_end(end.x + noise_level, end.y + noise_level);

  dmap_start.x = std::max((int8_t) 0, dmap_start.x);
  dmap_start.y = std::max((int8_t) 0, dmap_start.y);
  dmap_end.x   = std::min((int8_t) (MAP_WIDTH - 1), dmap_end.x);
  dmap_end.y   = std::min((int8_t) (MAP_HEIGHT - 1), dmap_end.y);

  for (auto x = dmap_start.x; x < dmap_end.x; x++) {
    for (auto y = dmap_start.y; y < dmap_end.y; y++) {
      bpoint p(x, y);
      if (! level_is_obs_to_hearing(g, v, l, p)) {
        dmap->val[ x ][ y ] = DMAP_IS_PASSABLE;
      }
    }
  }

  dmap->val[ end.x ][ end.y ] = DMAP_IS_GOAL_REVERSE - noise_level;

  if (compiler_unused) {
    dmap_print(dmap, end, dmap_start, dmap_end);
  }

  dmap_process_reverse(dmap, dmap_start, dmap_end);

  if (1 || compiler_unused) {
    dmap_print(dmap, end, dmap_start, dmap_end);
  }
}
