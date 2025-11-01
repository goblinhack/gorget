//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_audio.hpp"
#include "my_command.hpp"
#include "my_font.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_music.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_test.hpp"
#include "my_wid_console.hpp"
#include "my_wid_tiles.hpp"

#include <iostream>
#include <signal.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>

//
// Free all resources
//
void cleanup(void)
{
  LOG("Cleanup called");
  TRACE_AND_INDENT();

  if (g_quitting) {
    LOG("Quitting, nested");
    return;
  }

  g_quitting = true;

  extern Gamep game;
  auto         g = game;

#ifdef ENABLE_CRASH_HANDLER
  signal(SIGSEGV, nullptr); // uninstall our handler
  signal(SIGABRT, nullptr); // uninstall our handler
  signal(SIGINT, nullptr);  // uninstall our handler
#ifndef _WIN32
  signal(SIGPIPE, nullptr); // uninstall our handler
#endif
  signal(SIGFPE, nullptr); // uninstall our handler
#endif

  sdl_prepare_to_exit(g);
  wid_console_fini(g);
  command_fini();
  font_fini();
  tex_fini();
  wid_tiles_fini();
  tile_fini();
  blit_fini();
  color_fini();
  audio_fini();
  music_fini();
  sound_fini();
  sdl_fini(g);
  rooms_fini(g);
  levels_fini(g);
  fragments_fini(g);
  fragment_alts_fini(g);

  //
  // Do this last as sdl_fini depends on it.
  //
  game_fini(g);
  g = nullptr;

  //
  // Must be post game_fini
  //
  tp_fini();

  //
  // Wid fini has to be after game_fini, as the game state change to none will
  // destroy remaining windows.
  //
  wid_fini(nullptr);

  if (g_exec_full_path_and_name) {
    myfree(g_exec_full_path_and_name);
    g_exec_full_path_and_name = nullptr;
  }

  if (g_data_path) {
    myfree(g_data_path);
    g_data_path = nullptr;
  }

  if (g_ttf_path) {
    myfree(g_ttf_path);
    g_ttf_path = nullptr;
  }

  if (g_gfx_path) {
    myfree(g_gfx_path);
    g_gfx_path = nullptr;
  }

  if (g_exec_dir) {
    myfree(g_exec_dir);
    g_exec_dir = nullptr;
  }

  LOG("Cleanup done");
}
