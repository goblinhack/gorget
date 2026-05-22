//
// Copyright goblinhack@gmail.com
//

#include "config.hpp"
#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_color.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_gl.hpp" // NOLINT
#include "my_globals.hpp"
#include "my_main.hpp" // NOLINT
#include "my_music.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_spoint.hpp"
#include "my_tile.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_popup.hpp"
#include "my_wids.hpp"

void wid_new_game(Gamep g)
{
  con("New game: select");
  TRACE_INDENT();

  game_state_reset(g, "new game");
  game_create_levels(g);
  game_map_zoom_in(g);
  game_start_playing(g);
  game_state_change(g, STATE_PLAYING, "new game");
}
