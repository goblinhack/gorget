//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_dice_rolls.hpp"
#include "my_game_popups.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_music.hpp"
#include "my_player.hpp"
#include "my_random.hpp"
#include "my_sound.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"

[[nodiscard]] auto tp_load_player1() -> bool
{
  auto *tp   = tp_load("player1"); // keep as string for scripts
  auto  name = tp_name(tp);

  tp_load_player_common(tp);

  // begin sort marker1 {
  // end sort marker1 }

  return true;
}
