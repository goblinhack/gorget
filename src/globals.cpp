//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <string>

class Game *game;

char *DATA_PATH;
char *EXEC_DIR;
char *EXEC_FULL_PATH_AND_NAME;
char *GFX_PATH;
char *TTF_PATH;

FILE       *g_log_stdout;
FILE       *g_log_stderr;
std::string g_log_stderr_filename;
std::string g_log_stdout_filename;

bool g_die_occurred;             // Fatal error has occurred
bool g_do_screenshot;            // Grab a screen shot next fram
bool g_errored;                  // An error has occurred
bool g_grab_next_key;            // Waiting for key input
bool g_loading;                  // Currently loading
bool g_main_loop_running;        // SDL main loop running.
bool g_need_restart;             // Need to restart game
bool g_opt_no_slow_log_flush;    // Do not flush after each console log at start
bool g_opt_override_debug_level; // Temporary used to disable debugs on load
bool g_quitting;                 // Exiting the game
bool g_opt_test_skip_main_menu;  // Start in the main menu

// --debug  Basic debug
// --debug2 Map is visible and memory checks enabled
// --debug3 All debugs. Slow.
bool g_opt_debug1; // Basic debug
bool g_opt_debug2; // As above but includes log indentation and more detailed debugs
bool g_opt_debug3; // As above but show the entire level

std::string g_opt_seed_name;

//
// The number of tiles on screen.
//
int TILES_VISIBLE_ACROSS;
int TILES_VISIBLE_DOWN;

int g_last_logged_callframes_depth;

void reset_globals(void)
{
  g_opt_debug1               = false;
  g_opt_debug2               = false;
  g_opt_debug3               = false;
  g_opt_no_slow_log_flush    = false;
  g_opt_override_debug_level = false;
  g_opt_test_skip_main_menu  = false;
}
