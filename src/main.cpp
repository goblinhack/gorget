//
// Copyright goblinhack@gmail.com
//

#include <ctime>
#include <iostream>
#include <libgen.h> // dirname
#include <signal.h> // dirname
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "my_ascii.hpp"
#include "my_audio.hpp"
#include "my_callstack.hpp"
#include "my_command.hpp"
#include "my_dir.hpp"
#include "my_file.hpp"
#include "my_font.hpp"
#include "my_game.hpp"
#include "my_gfx.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_music.hpp"
#include "my_ptrcheck.hpp"
#include "my_ramdisk.hpp"
#include "my_random.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_tp.hpp"
#include "my_wid_console.hpp"
#include "my_wid_tiles.hpp"
#include "my_wids.hpp"

static char      **ARGV;
static std::string original_program_name;

void quit(Gamep *g_in)
{
  LOG("Exiting, quit callded");
  TRACE_AND_INDENT();

  Gamep g = *g_in;
  *g_in   = nullptr;

  if (g_quitting) {
    LOG("Quitting, nested");
    return;
  }

  g_quitting = true;

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

  if (EXEC_FULL_PATH_AND_NAME) {
    myfree(EXEC_FULL_PATH_AND_NAME);
    EXEC_FULL_PATH_AND_NAME = nullptr;
  }

  if (DATA_PATH) {
    myfree(DATA_PATH);
    DATA_PATH = nullptr;
  }

  if (TTF_PATH) {
    myfree(TTF_PATH);
    TTF_PATH = nullptr;
  }

  if (GFX_PATH) {
    myfree(GFX_PATH);
    GFX_PATH = nullptr;
  }

  if (EXEC_DIR) {
    myfree(EXEC_DIR);
    EXEC_DIR = nullptr;
  }

#ifdef ENABLE_DEBUG_MEM_LEAKS
  if (! g_die_occurred) {
    ptrcheck_leak_print();
  }
#endif

  LOG("Cleanup done");
}

void restart(Gamep g)
{
  LOG("Exiting, restart callded");
  TRACE_AND_INDENT();

  char *args[] = {nullptr, (char *) "-restart", nullptr};
  char *executable;

  if (g_opt_debug1) {
    wid_visible(g, wid_console_window);
    wid_raise(g, wid_console_window);
    wid_update(g, wid_console_window);
  }

  executable = (char *) original_program_name.c_str();

  bool use_system;

#ifdef __linux__
  //
  // For some reason SDL audio fails if we use execve
  //
  use_system = true;
#elif _WIN32
  //
  // Windows has spaces in the path name and that ends up being incorrectly
  // split by execve on the 2nd boot. So, just avoid the issue.
  //
  executable = (char *) "gorget.exe";
  use_system = false;
#else
  use_system = false;
#endif

  CON("Restart \"%s\"", executable);
  if (g_opt_debug1) {
    sdl_flush_display(g, true);
  }

  CON("Quit");
  quit(&g);

  if (use_system) {
    char tmp_cmd[ PATH_MAX ];
    snprintf(tmp_cmd, sizeof(tmp_cmd), "%s &", executable);
    system(tmp_cmd);
    exit(0);
  } else {
    args[ 0 ] = executable;
    execve(executable, (char *const *) args, nullptr);
    DIE("Failed to restart");
  }
}

void die(void)
{
  LOG("Exiting, die called");
  TRACE_AND_INDENT();

  extern Gamep game;
  auto         g = game;

  quit(&g);

  LOG("Bye, error exit");
  fprintf(MY_STDERR, "exit(1) error\n");

  exit(1);
}

//
// Find the binary we are running.
//
static void find_executable(void)
{
  TRACE_NO_INDENT();

  char       *parent_dir         = nullptr;
  char       *curr_dir           = nullptr;
  std::string exec_name          = "";
  char       *exec_expanded_name = nullptr;
  char       *path               = nullptr;
  char       *tmp;

  exec_name = mybasename(ARGV[ 0 ], __FUNCTION__);
  LOG("Will use EXEC_NAME as '%s'", exec_name.c_str());

  //
  // Get the current directory, ending in a single /
  //
  curr_dir = dynprintf("%s" DIR_SEP, dir_dot());
  tmp      = strsub(curr_dir, DIR_SEP DIR_SEP, DIR_SEP, "curr_dir");
  myfree(curr_dir);
  curr_dir = tmp;

  //
  // Get the parent directory, ending in a single /
  //
  parent_dir = dynprintf("%s" DIR_SEP, dir_dotdot(dir_dot()));
  tmp        = strsub(parent_dir, DIR_SEP DIR_SEP, DIR_SEP, "parent_dir");
  myfree(parent_dir);
  parent_dir = tmp;

  //
  // Get rid of ../ from the program name and replace with the path.
  //
  exec_expanded_name = dupstr(ARGV[ 0 ], __FUNCTION__);
  if (*exec_expanded_name == '.') {
    tmp = strsub(exec_expanded_name, ".." DIR_SEP, parent_dir, "exec_expanded_name");
    myfree(exec_expanded_name);
    exec_expanded_name = tmp;
  }

  //
  // Get rid of ./ from the program name.
  //
  if (*exec_expanded_name == '.') {
    tmp = strsub(exec_expanded_name, "." DIR_SEP, "", "exec_expanded_name2");
    myfree(exec_expanded_name);
    exec_expanded_name = tmp;
  }

  //
  // Get rid of any // from the path
  //
  tmp = strsub(exec_expanded_name, DIR_SEP DIR_SEP, DIR_SEP, "exec_expanded_name3");
  myfree(exec_expanded_name);
  exec_expanded_name = tmp;

  //
  // Look in the simplest case first.
  //
  EXEC_FULL_PATH_AND_NAME = dynprintf("%s%s", curr_dir, exec_name.c_str());
  if (file_exists(EXEC_FULL_PATH_AND_NAME)) {
    EXEC_DIR = dupstr(curr_dir, "exec dir 1");
    goto cleanup;
  }

  myfree(EXEC_FULL_PATH_AND_NAME);

  //
  // Try the parent dir.
  //
  EXEC_FULL_PATH_AND_NAME = dynprintf("%s%s", parent_dir, exec_name.c_str());
  if (file_exists(EXEC_FULL_PATH_AND_NAME)) {
    EXEC_DIR = dupstr(parent_dir, "exec dir 2");
    goto cleanup;
  }

  myfree(EXEC_FULL_PATH_AND_NAME);

  //
  // Try the PATH.
  //
  path = getenv("PATH");
  if (path) {
    char *dir = nullptr;

    path = dupstr(path, "path");

    for (dir = strtok(path, PATHSEP); dir; dir = strtok(nullptr, PATHSEP)) {
      EXEC_FULL_PATH_AND_NAME = dynprintf("%s" DIR_SEP "%s", dir, exec_name.c_str());
      if (file_exists(EXEC_FULL_PATH_AND_NAME)) {
        EXEC_DIR = dynprintf("%s" DIR_SEP, dir);
        goto cleanup;
      }

      myfree(EXEC_FULL_PATH_AND_NAME);
    }

    myfree(path);
    path = nullptr;
  }

  EXEC_FULL_PATH_AND_NAME = dupstr(exec_expanded_name, "full path");
  EXEC_DIR                = dupstr(dirname(exec_expanded_name), "exec dir");

cleanup:
  auto new_EXEC_DIR = strsub(EXEC_DIR, "/", DIR_SEP, "EXEC_DIR");
  myfree(EXEC_DIR);
  EXEC_DIR = new_EXEC_DIR;

  DBG3("EXEC_DIR set to %s", EXEC_DIR);
  DBG3("Parent dir  : \"%s\"", parent_dir);
  DBG3("Curr dir    : \"%s\"", curr_dir);
  DBG3("Full name   : \"%s\"", exec_expanded_name);

  if (path) {
    myfree(path);
  }

  if (exec_expanded_name) {
    myfree(exec_expanded_name);
  }

  if (parent_dir) {
    myfree(parent_dir);
  }

  if (curr_dir) {
    myfree(curr_dir);
  }
}

//
// Find all installed file locations.
//
static void find_exec_dir(void)
{
  TRACE_NO_INDENT();
  find_executable();

  //
  // Make sure the exec dir ends in a /
  //
  auto tmp  = dynprintf("%s" DIR_SEP, EXEC_DIR);
  auto tmp2 = strsub(tmp, "//", DIR_SEP, "EXEC_DIR");
  auto tmp3 = strsub(tmp2, "\\\\", DIR_SEP, "EXEC_DIR");
  auto tmp4 = strsub(tmp3, "/", DIR_SEP, "EXEC_DIR");
  auto tmp5 = strsub(tmp4, "\\", DIR_SEP, "EXEC_DIR");
  myfree(tmp);
  myfree(tmp2);
  myfree(tmp3);
  myfree(tmp4);
  if (EXEC_DIR) {
    myfree(EXEC_DIR);
  }
  EXEC_DIR = tmp5;

  LOG("Will use EXEC_DIR as '%s'", EXEC_DIR);
}

//
// Hunt down the data/ dir.
//
static void find_data_dir(void)
{
  TRACE_NO_INDENT();
  DATA_PATH = dynprintf("%sdata" DIR_SEP, EXEC_DIR);
  if (dir_exists(DATA_PATH)) {
    return;
  }
  myfree(DATA_PATH);

  DATA_PATH = dynprintf(".." DIR_SEP "data");
  if (dir_exists(DATA_PATH)) {
    return;
  }
  myfree(DATA_PATH);

  DATA_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

//
// Hunt down the fonts/ dir.
//
static void find_ttf_dir(void)
{
  TRACE_NO_INDENT();
  TTF_PATH = dynprintf("%sdata" DIR_SEP "ttf" DIR_SEP, EXEC_DIR);
  if (dir_exists(TTF_PATH)) {
    return;
  }
  myfree(TTF_PATH);

  TTF_PATH = dynprintf(".." DIR_SEP "data" DIR_SEP "ttf" DIR_SEP);
  if (dir_exists(TTF_PATH)) {
    return;
  }
  myfree(TTF_PATH);

  TTF_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

//
// Hunt down the gfx/ dir.
//
static void find_gfx_dir(void)
{
  TRACE_NO_INDENT();
  GFX_PATH = dynprintf("%sdata" DIR_SEP "gfx" DIR_SEP, EXEC_DIR);
  if (dir_exists(GFX_PATH)) {
    return;
  }
  myfree(GFX_PATH);

  GFX_PATH = dynprintf(".." DIR_SEP "gfx" DIR_SEP);
  if (dir_exists(GFX_PATH)) {
    return;
  }
  myfree(GFX_PATH);

  GFX_PATH = dupstr(EXEC_DIR, __FUNCTION__);
}

//
// Find all installed file locations.
//
static void find_file_locations(void)
{
  TRACE_NO_INDENT();

  find_exec_dir();
  find_data_dir();
  find_ttf_dir();
  find_gfx_dir();

  LOG("Gfx path    : \"%s\"", GFX_PATH);
  LOG("Font path   : \"%s\"", TTF_PATH);
}

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
  CON(" --seed <name/number>        -- Set the random seed.");
  CON(" ");
  CON("Debugging options:");
  CON(" --debug                     -- Basic debug.");
  CON(" --debug2                    -- Most debugs. Most useful.");
  CON(" --debug3                    -- All debugs. Slow.");
  CON(" --no-debug                  -- Disable debugs.");
  CON("Testing options:");
  CON(" --test-start                -- Start in a level.");
  CON(" --test-select               -- Start in level select.");
  CON(" --test-room-gen             -- Test room gen and then exit.");
  CON(" --test-level-select-gen     -- Test room grid gen and then exit.");
  CON(" --test-level-gen            -- Test level gen and then exit.");
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
  LOG("Parse command line arguments for '%s'", argv[ 0 ]);
  for (i = 1; i < argc; i++) {
    LOG("+ argument: \"%s\"", argv[ i ]);
  }

  if (argc) {
    g_opt_no_slow_log_flush = true;
  }

  for (i = 1; i < argc; i++) {
    if (! strcasecmp(argv[ i ], "--seed") || ! strcasecmp(argv[ i ], "-seed")) {
      g_opt_seed_name = argv[ i + 1 ];
      i++;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--no-debug") || ! strcasecmp(argv[ i ], "-no-debug")
        || ! strcasecmp(argv[ i ], "--nodebug") || ! strcasecmp(argv[ i ], "-nodebug")) {
      g_opt_debug1               = false;
      g_opt_debug2               = false;
      g_opt_debug3               = false;
      g_opt_override_debug_level = true;
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

    if (! strcasecmp(argv[ i ], "--debug3") || ! strcasecmp(argv[ i ], "-debug3")) {
      g_opt_debug1               = true;
      g_opt_debug2               = true;
      g_opt_debug3               = true;
      g_opt_override_debug_level = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--test-start") || ! strcasecmp(argv[ i ], "-test-start")) {
      g_opt_test_start = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--test-select") || ! strcasecmp(argv[ i ], "-test-select")) {
      g_opt_test_select = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--test-room-gen") || ! strcasecmp(argv[ i ], "-test-room-gen")) {
      g_opt_test_room_gen = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--test-level-select-gen") || ! strcasecmp(argv[ i ], "-test-level-select-gen")) {
      g_opt_test_level_select_gen = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--test-level-gen") || ! strcasecmp(argv[ i ], "-test-level-gen")) {
      g_opt_test_level_gen = true;
      continue;
    }

    if (! strcasecmp(argv[ i ], "--restart") || ! strcasecmp(argv[ i ], "-restart")) {
      g_opt_restarted = true;
      continue;
    }

    //
    // Bad argument.
    //
    if (argv[ i ][ 0 ] == '-') {
      usage();
#ifdef _WIN32
      //
      // Win32 puts spaces in argv when we restart the process. I'm not sure
      // how to handle that, so don't fail the program. Warn and continue.
      //
      CON("Unknown format argument, %s", argv[ i ]);
      return;
#else
      DIE("Unknown format argument, %s", argv[ i ]);
#endif
    }

    usage();
#ifdef _WIN32
    CON("Unknown format argument, %s", argv[ i ]);
#else
    DIE("Unknown format argument, %s", argv[ i ]);
#endif
  }
}

//
// Where all logs go
//
static std::string create_appdata_dir(void)
{
  const char *appdata;
  appdata = getenv("APPDATA");
  if (! appdata || ! appdata[ 0 ]) {
    appdata = "appdata";
  }

#ifdef _WIN32
  mkdir(appdata);
#else
  mkdir(appdata, 0700);
#endif

  char *dir = dynprintf("%s%s%s", appdata, DIR_SEP, "gorget");
#ifdef _WIN32
  mkdir(dir);
#else
  mkdir(dir, 0700);
#endif
  myfree(dir);

  if (! g_log_stdout) {
    char *out             = dynprintf("%s%s%s%s%s", appdata, DIR_SEP, "gorget", DIR_SEP, "stdout.txt");
    g_log_stdout_filename = std::string(out);
    g_log_stdout          = fopen(out, "w+");
    LOG("Will use STDOUT as '%s'", out);
    myfree(out);
  }

  if (! g_log_stderr) {
    char *err             = dynprintf("%s%s%s%s%s", appdata, DIR_SEP, "gorget", DIR_SEP, "stderr.txt");
    g_log_stderr_filename = std::string(err);
    g_log_stderr          = fopen(err, "w+");
    LOG("Will use STDERR as '%s'", err);
    myfree(err);
  }

  return std::string(appdata);
}

void flush_the_console(Gamep g)
{
  //
  // Easier to see progress on windows where there is no console
  //
  if (g_opt_debug1) {
    wid_visible(g, wid_console_window);
    wid_raise(g, wid_console_window);
    wid_update(g, wid_console_window);
    sdl_flush_display(g, true);
  }
}

int main(int argc, char *argv[])
{
  TRACE_NO_INDENT();
  Gamep g = nullptr;
  ARGV    = argv;

  auto appdata = create_appdata_dir(); // Want this first so we get all logs

  LOG("Greetings mortal");

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
    parse_args(argc, argv);
  }

  {
    LOG("Ramdisk");
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

  {
    TRACE_NO_INDENT();
    if (! sdl_init()) {
      ERR("SDL: Init");
    }
  }

  {
    TRACE_NO_INDENT();
    if (! sdl_display_init(g)) {
      ERR("SDL: Init");
    }
  }

  {
    TRACE_NO_INDENT();
    sdl_config_update_all(g);
  }

  if (g_opt_test_level_select_gen || g_opt_test_room_gen || g_opt_test_level_gen) {
    //
    // Skip for speed of test setuip
    //
  } else {
    //
    // Causes a 0.3 sec delay first time it seems to run
    //
    LOG("SDL: Pump events");
    SDL_PumpEvents();
    LOG("SDL: Pump events done");
  }

  {
    TRACE_NO_INDENT();
    if (g_need_restart) {
      restart(g);
    }
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
  {
    TRACE_NO_INDENT();
    SDL_GL_SetSwapInterval(0);
  }

  //
  // Random number
  //
  if (g_opt_debug1) {
    CON("Init random seed");
  } else {
    LOG("Init random seed");
  }
  pcg_srand((unsigned int) std::time(nullptr));

  color_init();

  {
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

  {
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

  {
    TRACE_NO_INDENT();
    if (g_opt_debug1) {
      CON("Load console");
    } else {
      LOG("Load console");
    }
    if (! wid_console_init(g)) {
      ERR("Wid_console init");
    }
    wid_toggle_hidden(g, wid_console_window);
    flush_the_console(g);

    if (g_opt_debug1) {
      wid_visible(g, wid_console_window);
      wid_raise(g, wid_console_window);
      wid_update(g, wid_console_window);
    }
  }

  {
    CON("%%fg=red$          @@@@@@@@   @@@@@@   @@@@@@@    @@@@@@@@  @@@@@@@@  @@@@@@@%%fg=reset$");
    CON("%%fg=red$         @@@@@@@@@  @@@@@@@@  @@@@@@@@  @@@@@@@@@  @@@@@@@@  @@@@@@@%%fg=reset$");
    CON("%%fg=red$         !@@        @@!  @@@  @@!  @@@  !@@        @@!         @@!%%fg=reset$");
    CON("%%fg=red$         !@!        !@!  @!@  !@!  @!@  !@!        !@!         !@!%%fg=reset$");
    CON("%%fg=red$         !@! @!@!@  @!@  !@!  @!@!!@!   !@! @!@!@  @!!!:!      @!!%%fg=reset$");
    CON("%%fg=red$         !!! !!@!!  !@!  !!!  !!@!@!    !!! !!@!!  !!!!!:      !!!%%fg=reset$");
    CON("%%fg=red$         :!!   !!:  !!:  !!!  !!: :!!   :!!   !!:  !!:         !!:%%fg=reset$");
    CON("%%fg=red$         :!:   !::  :!:  !:!  :!:  !:!  :!:   !::  :!:         :!:%%fg=reset$");
    CON("%%fg=red$          ::: ::::  ::::: ::  ::   :::   ::: ::::   :: ::::     ::%%fg=reset$");
    CON("%%fg=red$          :: :: :    : :  :    :   : :   :: :: :   : :: ::      :%%fg=reset$");
    CON("%%fg=red$           :              :    .         :: :      :  :  :%%fg=reset$");
    CON("%%fg=red$           .              :               : .      .     .%%fg=reset$");
    CON("%%fg=red$                          :               .%%fg=reset$");
    CON("%%fg=red$                          .%%fg=reset$");
    CON("%%fg=green$Version: " MYVER "%%fg=reset$");
    CON("Press %%fg=yellow$<tab>%%fg=reset$ to complete commands.");
    CON("Press %%fg=yellow$?%%fg=reset$ to show command options.");
  }

  //
  // Need to preserve spaces for restarting via exec
  //
  {
    TRACE_NO_INDENT();
    original_program_name = std::string(argv[ 0 ]);
    if (g_opt_debug1) {
      CON("Original program name: %s", original_program_name.c_str());
    } else {
      LOG("Original program name: %s", original_program_name.c_str());
    }
    flush_the_console(g);
  }

  {
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

  {
    TRACE_NO_INDENT();
    if (! tile_init()) {
      ERR("Tile init");
    }
    flush_the_console(g);
  }

  {
    TRACE_NO_INDENT();
    if (g_opt_debug1) {
      CON("Load textures");
    } else {
      LOG("Load textures");
    }
    if (! tex_init()) {
      ERR("Tex init");
    }
    flush_the_console(g);
  }

  {
    TRACE_NO_INDENT();
    if (g_opt_debug1) {
      CON("Load audio");
    } else {
      LOG("Load audio");
    }
    if (! audio_init()) {
      ERR("Audio init");
    }
    flush_the_console(g);
  }

  {
    TRACE_NO_INDENT();
    if (g_opt_debug1) {
      CON("Load music");
    } else {
      LOG("Load music");
    }
    if (! music_init()) {
      ERR("Music init");
    }
    flush_the_console(g);
  }

  {
    TRACE_NO_INDENT();
    if (g_opt_debug1) {
      CON("Load sound");
    } else {
      LOG("Load sound");
    }
    if (! sound_init()) {
      ERR("Sound init");
    }
    sound_load(0.5, "data/sounds/interface/click2.wav", "click");
    sound_load(0.5, "data/sounds/interface/error.wav", "error");
    flush_the_console(g);
  }

  {
    TRACE_NO_INDENT();
    if (g_opt_debug1) {
      CON("Find resource locations for gfx and music");
    } else {
      LOG("Find resource locations for gfx and music");
    }
    find_file_locations();
    flush_the_console(g);
  }

  {
    TRACE_NO_INDENT();
    if (g_opt_debug1) {
      CON("Load templates");
    } else {
      LOG("Load templates");
    }
    if (! tp_init()) {
      ERR("Templates init");
    }
  }

  {
    TRACE_NO_INDENT();
    if (g_opt_debug1) {
      CON("Load commands");
    } else {
      LOG("Load commands");
    }
    if (! command_init()) {
      ERR("Command init");
    }
    flush_the_console(g);
  }

  {
    rooms_init(g);
    fragments_init(g);

    if (g_opt_test_level_select_gen) {
      level_select_test(g);
      DIE_CLEAN("done");
    }

    if (g_opt_test_room_gen) {
      rooms_test(g);
      DIE_CLEAN("done");
    }

    if (g_opt_test_level_gen) {
      level_gen_test(g);
      DIE_CLEAN("done");
    }
  }

  {
    TRACE_NO_INDENT();
    flush_the_console(g);

    //
    // Main menu
    //
    TRACE_NO_INDENT();
    if (g_opt_restarted) {
      wid_cfg_gfx_select(g);
      g_opt_restarted = false;
    } else if (g_opt_test_start) {
      wid_new_game(g);
    } else if (g_opt_test_select) {
      wid_new_game(g);
    } else {
      wid_main_menu_select(g);
    }

    flush_the_console(g);
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
  flush_the_console(g);

  if (g_need_restart) {
    g_need_restart = false;
    restart(g);
  }

  CON("Quit");
  quit(&g);

  CON("Goodbye my friend and take care until next time!");
  return 0;
}
