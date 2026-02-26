//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_sound.hpp"

void thing_sound_play(Gamep g, Levelsp v, Levelp l, Thingp t, const std::string &alias)
{
  TRACE();

  if (g_opt_tests) {
    return;
  }

  auto *player = thing_player(g);
  if (player == nullptr) [[unlikely]] {
    return;
  }

  Levelp player_level = thing_player_level(g);
  if (player_level == nullptr) {
    return;
  }

  auto *next_level_down = level_select_get_next_level_down(g, v, player_level);

  float scale = 1.0;

  //
  // Where did the thing play the sound? Might not be on the same level as the player.
  //
  auto *t_level = game_level_get(g, v, t->level_num);
  if (t_level == next_level_down) {
    //
    // It's the level below. Dampen the sound.
    //
    scale = 0.01F;
  } else if ((t_level != nullptr) && (t_level != player_level)) {
    //
    // It's too far away. Ignore the sound.
    //
    return;
  }

  //
  // Dampen sounds on the same level.
  //
  if (t_level == player_level) {
    auto at = thing_at(t);

    if (! thing_vision_can_see_tile(g, v, l, player, at)) {
      scale /= 5;
    }

    if (! thing_vision_player_has_seen_tile(g, v, l, at)) {
      scale /= 5;
    }
  }

  if (scale <= 0) {
    return;
  }

  (void) sound_play(g, alias, scale);
}
