//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_audio.hpp"
#include "my_command.hpp"
#include "my_font.hpp"
#include "my_gfx.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_music.hpp"
#include "my_ramdisk.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_test.hpp"
#include "my_tests.hpp"
#include "my_wid_tiles.hpp"
#include "my_wids.hpp"

#include <csignal>
#include <cstring>
#include <iostream>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>

//
// Used to stop the compiler removing unused code I want to keep
//
bool compiler_unused;

static void usage()
{
  TRACE_NO_INDENT();
  static int whinged;

  if (whinged != 0) {
    return;
  }
  whinged = 1;

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
  CON(" --level name/<number>             -- Start in this level only.");
  CON(" --level-select                    -- Start in the level select menu.");
  CON(" --quick-start                     -- Quick start inside level.");
  CON(" --test <name>                     -- Run test foo only.");
  CON(" --tests                           -- Run all tests.");
  CON(" ");
  CON("Code generation:");
  CON(" --do-level-gen                    -- Do level gen only.");
  CON(" --do-level-select-gen             -- Do level select gen only.");
  CON(" --do-room-gen                     -- Generate room files only.");
  CON(" ");
  CON("Examples");
  CON(" # start on seed crowcod, level 10");
  CON(" ./gorget --seed crowcod --level 10");
  CON(" ");
  CON(" # start on seed crowcod, last level and at the level select meny");
  CON(" ./gorget --seed crowcod --level 100 --level-select");
  CON(" ");
  CON("Written by goblinhack@gmail.com");
}

static void parse_args(int argc, char *argv[])
{
  TRACE_NO_INDENT();
  int i = 0;

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

  if (argc != 0) {
    g_opt_no_slow_log_flush = true;
  }

  for (i = 1; i < argc; i++) {
    if ((strcasecmp(argv[ i ], "--seed") == 0) || (strcasecmp(argv[ i ], "-seed") == 0)) {
      if (i == argc - 1) {
        usage();
        CROAK("Missing parameter for argument, %s", argv[ i ]);
      }
      g_opt_seed_name = argv[ i + 1 ];
      i++;
      continue;
    }

    if ((strcasecmp(argv[ i ], "--debug") == 0) || (strcasecmp(argv[ i ], "-debug") == 0) || (strcasecmp(argv[ i ], "--debug1") == 0)
        || (strcasecmp(argv[ i ], "-debug1") == 0)) {
      g_opt_debug1               = true;
      g_opt_override_debug_level = true;
      continue;
    }

    if ((strcasecmp(argv[ i ], "--debug2") == 0) || (strcasecmp(argv[ i ], "-debug2") == 0)) {
      g_opt_debug1               = true;
      g_opt_debug2               = true;
      g_opt_override_debug_level = true;
      continue;
    }

    if ((strcasecmp(argv[ i ], "--quick-start") == 0) || (strcasecmp(argv[ i ], "-quick-start") == 0)) {
      g_opt_quick_start = true;
      continue;
    }

    if ((strcasecmp(argv[ i ], "--level-select") == 0) || (strcasecmp(argv[ i ], "-level-select") == 0)) {
      g_opt_level_select_menu = true;
      continue;
    }

    if ((strcasecmp(argv[ i ], "--level") == 0) || (strcasecmp(argv[ i ], "-level") == 0)) {
      if (i == argc - 1) {
        usage();
        CROAK("Missing parameter for argument, %s", argv[ i ]);
      }

      //
      // Check if this is a level number or name
      //
      char *p   = nullptr; // NOLINT
      auto  num = strtol(argv[ i + 1 ], &p, 10);
      if (*p != 0) {
        //
        // Level name
        //
        g_level_opt.level_name = argv[ i + 1 ];
        g_level_opt.is_set     = true;
      } else if (num > 0) {
        //
        // Level number
        //
        g_level_opt.level_num = num - 1;
        g_level_opt.is_set    = true;
      }

      g_opt_quick_start = true;
      i++;
      continue;
    }

    if ((strcasecmp(argv[ i ], "--test") == 0) || (strcasecmp(argv[ i ], "-test") == 0)) {
      if (i == argc - 1) {
        usage();
        CROAK("Missing parameter for argument, %s", argv[ i ]);
      }
      g_opt_test_name_filter = argv[ i + 1 ];
      g_opt_tests            = true;
      g_opt_debug1           = true;
      g_skip_audio_and_gfx   = true;
      i++;
      continue;
    }

    if ((strcasecmp(argv[ i ], "--tests") == 0) || (strcasecmp(argv[ i ], "-tests") == 0)) {
      g_opt_tests          = true;
      g_opt_debug1         = true;
      g_skip_audio_and_gfx = true;
      continue;
    }

    if ((strcasecmp(argv[ i ], "--do-room-gen") == 0) || (strcasecmp(argv[ i ], "-do-room-gen") == 0)) {
      g_opt_do_room_gen    = true;
      g_skip_audio_and_gfx = true;
      continue;
    }

    if ((strcasecmp(argv[ i ], "--do-level-select-gen") == 0) || (strcasecmp(argv[ i ], "-do-level-select-gen") == 0)) {
      g_opt_do_level_select_gen = true;
      g_skip_audio_and_gfx      = true;
      continue;
    }

    if ((strcasecmp(argv[ i ], "--do-level-gen") == 0) || (strcasecmp(argv[ i ], "-do-level-gen") == 0)) {
      g_opt_do_level_gen   = true;
      g_skip_audio_and_gfx = true;
      continue;
    }

    if ((strcasecmp(argv[ i ], "--restart") == 0) || (strcasecmp(argv[ i ], "-restart") == 0)) {
      g_opt_restarted = true;
      continue;
    }

    if ((strcasecmp(argv[ i ], "--restart-in-gfx-menu") == 0) || (strcasecmp(argv[ i ], "-restart-in-gfx-menu") == 0)) {
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

auto main(int argc, char *argv[]) -> int
{
  TRACE_NO_INDENT();
  Gamep g = nullptr;
  g_argv  = argv;
  g_argc  = argc;

  g_thread_id = MAIN_THREAD;

  //////////////////////////////////////////////////////////////////////////////
  // Call parse_args before any memory allocations, in case debug2 is enabled
  //////////////////////////////////////////////////////////////////////////////
  {
    TRACE_NO_INDENT();
    parse_args(argc, argv);
  }

  TRACE_NO_INDENT();
  auto appdata = log_dir_create(); // Want this first so we get all logs

  TRACE_NO_INDENT();
  redirect_stdout();

  TRACE_NO_INDENT();
  redirect_stderr();

  TRACE_NO_INDENT();
  LOG("Will use STDOUT as '%s'", g_log_stdout_filename.c_str());
  LOG("Will use STDERR as '%s'", g_log_stderr_filename.c_str());

  //////////////////////////////////////////////////////////////////////////////
  // Use LOG instead of CON until we set stdout or you see two logs
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  //////////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
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

  //////////////////////////////////////////////////////////////////////////////
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ Use LOG
  // instead of CON until we set stdout or you see two logs
  //////////////////////////////////////////////////////////////////////////////

  {
    TRACE_NO_INDENT();
    find_file_locations();
  }

  {
    LOG("Ramdisk init");
    TRACE_NO_INDENT();
    ramdisk_init();
  }

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
  std::locale const loc("");
  std::ios_base::sync_with_stdio(false);
  std::wcout.imbue(loc);
#endif

#ifdef ENABLE_CRASH_HANDLER
  //
  // Crash handlers
  //
  LOG("Install crash handlers");
#ifdef SIGSEGV
  signal(SIGSEGV, crash_handler);
#endif
#ifdef SIGBUS
  signal(SIGBUS, crash_handler);
#endif
#ifdef SIGABRT
  signal(SIGABRT, crash_handler);
#endif
#ifdef SIGFPE
  signal(SIGFPE, crash_handler);
#endif
#ifdef SIGILL
  signal(SIGILL, crash_handler);
#endif

#ifdef SIGPIPE
  signal(SIGPIPE, ctrlc_handler);
#endif
#ifdef SIGINT
  signal(SIGINT, ctrlc_handler);
#endif

#endif // ENABLE_CRASH_HANDLER

  //
  // Create and load the last saved game
  //
  (void) game_load_last_config(appdata.c_str());
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

  if (g_skip_audio_and_gfx) {
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

  if (! g_need_restart_with_given_arguments.empty()) {
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

  if (! wid_init()) {
    ERR("Wid init");
  }

  //
  // Colors
  //
  color_init();

  if (! g_skip_audio_and_gfx) {
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

  if (! g_skip_audio_and_gfx) {
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
    CON("Press " UI_WARNING_FMT_STR "?" UI_RESET_FMT "     to show command options.");
    auto key = ::to_string(game_key_console_get(g));
    CON("Press " UI_WARNING_FMT_STR "<%s>" UI_RESET_FMT "   to hide this console", key.c_str());
  }

  //
  // Need to preserve spaces for restarting via exec
  //
  if (! g_skip_audio_and_gfx) {
    TRACE_NO_INDENT();
    g_program_name = std::string(argv[ 0 ]);
    if (g_opt_debug1) {
      CON("Original program name: %s", g_program_name.c_str());
    } else {
      LOG("Original program name: %s", g_program_name.c_str());
    }
    wid_console_flush(g);
  }

  if (! g_skip_audio_and_gfx) {
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

  if (! g_skip_audio_and_gfx) {
    TRACE_NO_INDENT();
    if (! tile_init()) {
      ERR("Tile init");
    }
    wid_console_flush(g);
  }

  if (! g_skip_audio_and_gfx) {
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

  if (! g_skip_audio_and_gfx) {
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

  if (! g_skip_audio_and_gfx) {
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

  if (! g_skip_audio_and_gfx) {
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
      test_init();

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
    if (AN_ERROR_OCCURRED()) {
      wid_console_raise(g);
    } else if (g_opt_restarted_in_gfx_menu) {
      g_opt_restarted_in_gfx_menu = false;
      wid_hide(g, wid_console_window);
      wid_cfg_gfx_select(g);
    } else if (g_opt_quick_start) {
      wid_hide(g, wid_console_window);
      wid_new_game(g);
    } else if (g_opt_level_select_menu) {
      wid_hide(g, wid_console_window);
      wid_new_game(g);
    } else {
      wid_hide(g, wid_console_window);
      wid_main_menu_select(g);
    }
  }

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

  if (! g_need_restart_with_given_arguments.empty()) {
    TRACE_NO_INDENT();
    restart(g, g_need_restart_with_given_arguments);
  }

  LOG("Quit");
  cleanup();

  CON("Goodbye my friend and take care until next time!");
  return 0;
}
