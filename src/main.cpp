//
// Copyright goblinhack@gmail.com
//

#include <iostream>
#include <signal.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>

#include "my_ascii.hpp"
#include "my_audio.hpp"
#include "my_command.hpp"
#include "my_font.hpp"
#include "my_gfx.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_music.hpp"
#include "my_ramdisk.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_test.hpp"
#include "my_tests.hpp"
#include "my_wid_console.hpp"
#include "my_wid_tiles.hpp"
#include "my_wids.hpp"

static bool skip_gfx_and_audio; // For tests

static void usage(void)
{
  TRACE_NO_INDENT();
  static int whinged;

  if (whinged) {
    return;
  }
  whinged = true;

  CON("Gorget, options:");
  CON(" ");
  CON("Commonly used options:");
  CON(" --seed <name/number>              -- Set the random seed.");
  CON(" ");
  CON("Debugging:");
  CON(" --debug                           -- Basic debug.");
  CON(" --debug2                          -- All debugs. Slow.");
  CON(" ");
  CON("Testing:");
  CON(" --tests                           -- Run all tests.");
  CON(" --test foo                        -- Run test foo only.");
  CON(" --level foo                       -- Start in this level only.");
  CON(" ");
  CON("Debugging:");
  CON(" --quick-start                     -- Quick start inside level.");
  CON(" --quick-start-level-select-menu   -- Quick start in the level select menu.");
  CON(" ");
  CON("Code generation:");
  CON(" --do-level-gen                    -- Do level gen only.");
  CON(" --do-level-select-gen             -- Do level select gen only.");
  CON(" --do-room-gen                     -- Generate room files only.");
  CON(" ");
  CON("Written by goblinhack@gmail.com");
}

static void parse_args(int argc, char *argv[])
{
  TRACE_NO_INDENT();
  int i;

  //
  // Parse format args
  //
  if (g_opt_debug1) {
    CON("Parse command line arguments for '%s'", argv[ 0 ]);
  } else {
    LOG("Parse command line arguments for '%s'", argv[ 0 ]);
  }

  for (i = 1; i < argc; i++) {
    if (g_opt_debug1) {
      CON("+ argument: \"%s\"", argv[ i ]);
    } else {
      LOG("+ argument: \"%s\"", argv[ i ]);
    }
  }

  if (argc) {
    g_opt_no_slow_log_flush = true;
  }

  for (i = 1; i < argc; i++) {
    if (! strcasecmp(argv[ i ], "--seed") || ! strcasecmp(argv[ i ], "-seed")) {
      if (i == argc - 1) {
        usage();
        DIE("Missing parameter for argument, %s", argv[ i ]);
      }
      g_opt_seed_name = argv[ i + 1 ];
      i++;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--debug") || ! strcasecmp(argv[ i ], "-debug") || ! strcasecmp(argv[ i ], "--debug1")
        || ! strcasecmp(argv[ i ], "-debug1")) {
      g_opt_debug1               = true;
      g_opt_override_debug_level = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--debug2") || ! strcasecmp(argv[ i ], "-debug2")) {
      g_opt_debug1               = true;
      g_opt_debug2               = true;
      g_opt_override_debug_level = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--quick-start") || ! strcasecmp(argv[ i ], "-quick-start")) {
      g_opt_quick_start = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--quick-start-level-select-menu")
        || ! strcasecmp(argv[ i ], "-quick-start-level-select-menu")) {
      g_opt_quick_start_level_select_menu = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--level") || ! strcasecmp(argv[ i ], "-level")) {
      if (i == argc - 1) {
        usage();
        DIE("Missing parameter for argument, %s", argv[ i ]);
      }
      g_opt_level_name  = argv[ i + 1 ];
      g_opt_quick_start = true;
      i++;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--test") || ! strcasecmp(argv[ i ], "-test")) {
      if (i == argc - 1) {
        usage();
        DIE("Missing parameter for argument, %s", argv[ i ]);
      }
      g_opt_test_name    = argv[ i + 1 ];
      g_opt_tests        = true;
      g_opt_debug2       = true;
      skip_gfx_and_audio = true;
      i++;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--tests") || ! strcasecmp(argv[ i ], "-tests")) {
      g_opt_tests        = true;
      g_opt_debug2       = true;
      skip_gfx_and_audio = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--do-room-gen") || ! strcasecmp(argv[ i ], "-do-room-gen")) {
      g_opt_do_room_gen  = true;
      skip_gfx_and_audio = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--do-level-select-gen") || ! strcasecmp(argv[ i ], "-do-level-select-gen")) {
      g_opt_do_level_select_gen = true;
      skip_gfx_and_audio        = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--do-level-gen") || ! strcasecmp(argv[ i ], "-do-level-gen")) {
      g_opt_do_level_gen = true;
      skip_gfx_and_audio = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--restart") || ! strcasecmp(argv[ i ], "-restart")) {
      g_opt_restarted = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--restart-in-gfx-menu") || ! strcasecmp(argv[ i ], "-restart-in-gfx-menu")) {
      g_opt_restarted_in_gfx_menu = true;
      continue;
    }

    //
    // Bad argument.
    //
    if (argv[ i ][ 0 ] == '-') {
      usage();
      //
      // Win32 puts spaces in argv when we restart the process. I'm not sure
      // how to handle that, so don't fail the program. Warn and continue.
      //
      CON("Unknown format argument, %s", argv[ i ]);
#ifdef _WIN32
      return;
#else
      exit(1);
#endif
    }

    usage();
    CON("Unknown format argument, %s", argv[ i ]);
#ifdef _WIN32
    return;
#else
    exit(1);
#endif
  }
}

int main(int argc, char *argv[])
{
  TRACE_NO_INDENT();
  Gamep g = nullptr;
  g_argv  = argv;
  g_argc  = argc;

  auto appdata = log_dir_create(); // Want this first so we get all logs

  g_thread_id = -1;
  redirect_stdout();
  redirect_stderr();
  LOG("Will use STDOUT as '%s'", g_log_stdout_filename.c_str());
  LOG("Will use STDERR as '%s'", g_log_stderr_filename.c_str());

  //////////////////////////////////////////////////////////////////////////////
  // Use LOG instead of CON until we set stdout or you see two logs
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  //////////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
  LOG("Platform is _WIN32");
#endif
#ifdef __MINGW32__
  LOG("Platform is __MINGW32__");
#endif
#ifdef __MINGW64__
  LOG("Platform is __MINGW64__");
#endif
#ifdef __APPLE__
  LOG("Platform is __APPLE__");
#endif
#ifdef __linux__
  LOG("Platform is __linux__");
#endif

  {
    TRACE_NO_INDENT();
    find_file_locations();
  }

  {
    TRACE_NO_INDENT();
    parse_args(argc, argv);
  }

  {
    LOG("Ramdisk init");
    TRACE_NO_INDENT();
    ramdisk_init();
  }

  //////////////////////////////////////////////////////////////////////////////
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ Use LOG
  // instead of CON until we set stdout or you see two logs
  //////////////////////////////////////////////////////////////////////////////

  {
    LOG("Create console");
    TRACE_NO_INDENT();
    ascii_init();
  }

  //
  // Need this to get the UTF on the console
  //
#ifndef _WIN32
  LOG("Set locale for console");
  std::locale loc("");
  std::ios_base::sync_with_stdio(false);
  std::wcout.imbue(loc);
#endif

#ifdef ENABLE_CRASH_HANDLER
  //
  // Crash handlers
  LOG("Install crash handlers");
  signal(SIGSEGV, segv_handler);
  signal(SIGABRT, segv_handler);
  signal(SIGFPE, segv_handler);
  signal(SIGILL, segv_handler);
#ifndef _WIN32
  signal(SIGPIPE, ctrlc_handler);
#endif
  signal(SIGINT, ctrlc_handler);
#endif

  //
  // Create and load the last saved game
  //
  game_load_last_config(appdata.c_str());
  extern Gamep game;
  g = game;
  game_init(g);

  if (! g_opt_tests) {
    TRACE_NO_INDENT();
    if (! sdl_init()) {
      ERR("SDL: Init");
    }
  }

  if (! g_opt_tests) {
    TRACE_NO_INDENT();
    if (! sdl_display_init(g)) {
      ERR("SDL: Display init");
    }
  }

  if (! g_opt_tests) {
    TRACE_NO_INDENT();
    sdl_config_update_all(g);
  }

  if (skip_gfx_and_audio) {
    //
    // Skip for speed of test setup
    //
  } else {
    //
    // Causes a 0.3 sec delay first time it seems to run
    //
    LOG("SDL: Pump events");
    SDL_PumpEvents();
    LOG("SDL: Pump events done");
  }

  if (g_need_restart_with_given_arguments != "") {
    TRACE_NO_INDENT();
    restart(g, g_need_restart_with_given_arguments);
  }

  {
    TRACE_NO_INDENT();
    if (g_opt_debug1) {
      CON("Load early gfx tiles, text, UI etc...");
    } else {
      LOG("Load early gfx tiles, text, UI etc...");
    }
    gfx_init();
  }

  //
  // Disable vsync so the console is faster
  //
  if (! g_opt_tests) {
    TRACE_NO_INDENT();
    SDL_GL_SetSwapInterval(0);
  }

  //
  // Colors
  //
  color_init();

  if (! skip_gfx_and_audio) {
    TRACE_NO_INDENT();
    if (g_opt_debug1) {
      CON("Load fonts");
    } else {
      LOG("Load fonts");
    }
    if (! font_init()) {
      ERR("Font init");
    }
  }

  if (! skip_gfx_and_audio) {
    TRACE_NO_INDENT();
    if (g_opt_debug1) {
      CON("Load widgets");
    } else {
      LOG("Load widgets");
    }
    if (! wid_init()) {
      ERR("Wid init");
    }
  }

  if (! skip_gfx_and_audio) {
    TRACE_NO_INDENT();
    if (g_opt_debug1) {
      CON("Load console");
    } else {
      LOG("Load console");
    }
    if (! wid_console_init(g)) {
      ERR("Wid_console init");
    }
    wid_console_flush(g);
  }

  if (! g_opt_tests) {
    CON(UI_INFO_FMT_STR "          @@@@@@@@   @@@@@@   @@@@@@@    @@@@@@@@  @@@@@@@@  @@@@@@@" UI_RESET_FMT);
    CON(UI_INFO_FMT_STR "         @@@@@@@@@  @@@@@@@@  @@@@@@@@  @@@@@@@@@  @@@@@@@@  @@@@@@@" UI_RESET_FMT);
    CON(UI_INFO_FMT_STR "         !@@        @@!  @@@  @@!  @@@  !@@        @@!         @@!" UI_RESET_FMT);
    CON(UI_INFO_FMT_STR "         !@!        !@!  @!@  !@!  @!@  !@!        !@!         !@!" UI_RESET_FMT);
    CON(UI_INFO_FMT_STR "         !@! @!@!@  @!@  !@!  @!@!!@!   !@! @!@!@  @!!!:!      @!!" UI_RESET_FMT);
    CON(UI_INFO_FMT_STR "         !!! !!@!!  !@!  !!!  !!@!@!    !!! !!@!!  !!!!!:      !!!" UI_RESET_FMT);
    CON(UI_INFO_FMT_STR "         :!!   !!:  !!:  !!!  !!: :!!   :!!   !!:  !!:         !!:" UI_RESET_FMT);
    CON(UI_INFO_FMT_STR "         :!:   !::  :!:  !:!  :!:  !:!  :!:   !::  :!:         :!:" UI_RESET_FMT);
    CON(UI_INFO_FMT_STR "          ::: ::::  ::::: ::  ::   :::   ::: ::::   :: ::::     ::" UI_RESET_FMT);
    CON(UI_INFO_FMT_STR "          :: :: :    : :  :    :   : :   :: :: :   : :: ::      :" UI_RESET_FMT);
    CON(UI_INFO_FMT_STR "           :              :    .         :: :      :  :  :" UI_RESET_FMT "");
    CON(UI_INFO_FMT_STR "           .              :               : .      .     ." UI_RESET_FMT "");
    CON(UI_INFO_FMT_STR "                          :               ." UI_RESET_FMT);
    CON(UI_INFO_FMT_STR "                          ." UI_RESET_FMT);
    CON(UI_INFO_FMT_STR "Version: " MYVER UI_RESET_FMT);
    CON("Press " UI_WARNING_FMT_STR "<tab>" UI_RESET_FMT " to complete commands.");
    CON("Press " UI_WARNING_FMT_STR "?" UI_RESET_FMT " to show command options.");
  }

  //
  // Need to preserve spaces for restarting via exec
  //
  if (! skip_gfx_and_audio) {
    TRACE_NO_INDENT();
    g_program_name = std::string(argv[ 0 ]);
    if (g_opt_debug1) {
      CON("Original program name: %s", g_program_name.c_str());
    } else {
      LOG("Original program name: %s", g_program_name.c_str());
    }
    wid_console_flush(g);
  }

  if (! skip_gfx_and_audio) {
    TRACE_NO_INDENT();
    if (g_opt_debug1) {
      CON("Load tiles");
    } else {
      LOG("Load tiles");
    }
    if (! wid_tiles_init()) {
      ERR("Wid tiles init");
    }
  }

  if (! skip_gfx_and_audio) {
    TRACE_NO_INDENT();
    if (! tile_init()) {
      ERR("Tile init");
    }
    wid_console_flush(g);
  }

  if (! skip_gfx_and_audio) {
    TRACE_NO_INDENT();
    if (g_opt_debug1) {
      CON("Load textures");
    } else {
      LOG("Load textures");
    }
    if (! tex_init()) {
      ERR("Tex init");
    }
    wid_console_flush(g);
  }

  if (! skip_gfx_and_audio) {
    TRACE_NO_INDENT();
    if (g_opt_debug1) {
      CON("Init audio");
    } else {
      LOG("Init audio");
    }
    if (! audio_init()) {
      ERR("Audio init");
    }
    wid_console_flush(g);
  }

  if (! skip_gfx_and_audio) {
    TRACE_NO_INDENT();
    if (g_opt_debug1) {
      CON("Init music");
    } else {
      LOG("Init music");
    }
    if (! music_init()) {
      ERR("Music init");
    }
    wid_console_flush(g);
  }

  if (! skip_gfx_and_audio) {
    TRACE_NO_INDENT();
    if (g_opt_debug1) {
      CON("Load sounds");
    } else {
      LOG("Load sounds");
    }
    if (! sound_init()) {
      ERR("Sound init");
    } else {
      sounds_init();
    }
    wid_console_flush(g);
  }

  {
    TRACE_NO_INDENT();

    LOG("Load templates");
    if (! tp_init()) {
      ERR("Templates init");
    }
    LOG("Loaded templates");
  }

  {
    TRACE_NO_INDENT();
    LOG("Load commands");
    if (! command_init()) {
      ERR("Command init");
    }
    LOG("Loaded commands");
    wid_console_flush(g);
  }

  {
    rooms_init(g);
    levels_init(g);
    fragments_init(g);

    if (g_opt_tests) {
      tests_init();

      CON("Running tests");
      CON("-------------");
      tests_run(g);

      DIE_CLEAN("done");
    }

    if (g_opt_do_level_gen) {
      CON("Creating many levels. Look in the log file for output.");
      CON("------------------------------------------------------");
      level_gen_test(g);
      DIE_CLEAN("done");
    }

    if (g_opt_do_level_select_gen) {
      CON("Creating level select levels. Look in the log file for output.");
      CON("--------------------------------------------------------------");
      level_select_test(g);
      DIE_CLEAN("done");
    }

    if (g_opt_do_room_gen) {
      CON("Creating room gen files. You will need to recompile after this.");
      CON("---------------------------------------------------------------");
      rooms_test(g);
      DIE_CLEAN("done");
    }
  }

  {
    TRACE_NO_INDENT();
    wid_console_flush(g);

    //
    // Main menu
    //
    TRACE_NO_INDENT();
    if (g_opt_restarted_in_gfx_menu) {
      g_opt_restarted_in_gfx_menu = false;
      wid_cfg_gfx_select(g);
    } else if (g_opt_quick_start) {
      wid_new_game(g);
    } else if (g_opt_quick_start_level_select_menu) {
      wid_new_game(g);
    } else {
      wid_main_menu_select(g);
    }

    wid_console_flush(g);
  }

  wid_hide(g, wid_console_window);

  {
    glEnable(GL_TEXTURE_2D);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    GL_ERROR_CHECK();

    if (game_gfx_vsync_enable_get(g)) {
      SDL_GL_SetSwapInterval(1);
    } else {
      SDL_GL_SetSwapInterval(0);
    }
    GL_ERROR_CHECK();

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    GL_ERROR_CHECK();
  }

  g_opt_no_slow_log_flush = false;

  TRACE_NO_INDENT();
  sdl_loop(g);
  LOG("SDL loop finished");
  wid_console_flush(g);

  if (g_need_restart_with_given_arguments != "") {
    TRACE_NO_INDENT();
    restart(g, g_need_restart_with_given_arguments);
  }

  LOG("Quit");
  cleanup();

  CON("Goodbye my friend and take care until next time!");
  return 0;
}
