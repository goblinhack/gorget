//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GLOBALS_HPP_
#define _MY_GLOBALS_HPP_

#include <string>

extern char             **g_argv;
extern char              *g_data_path;
extern char              *g_exec_dir;
extern char              *g_exec_full_path_and_name;
extern char              *g_gfx_path;
extern char              *g_ttf_path;
extern int                g_argc;
extern std::string        g_log_stderr_filename;
extern std::string        g_log_stdout_filename;
extern std::string        g_opt_level_name;
extern std::string        g_opt_seed_name;
extern std::string        g_opt_test_name;
extern std::string        g_program_name;
extern thread_local FILE *g_log_stderr;
extern thread_local FILE *g_log_stdout;
extern thread_local int   g_thread_id;

extern bool        g_die_occurred;                      // Fatal error has occurred
extern bool        g_do_screenshot;                     // Grab a screen shot next fram
extern bool        g_errored;                           // An error has occurred
extern bool        g_grab_next_key;                     // Waiting for key input
extern bool        g_loading;                           // Currently loading
extern bool        g_main_loop_running;                 // SDL main loop is running.
extern std::string g_need_restart_with_given_arguments; // Need to restart game with the given arg
extern bool        g_quitting;                          // Exiting the game
extern bool        g_opt_no_slow_log_flush;             // Do not flush after each console log at start
extern bool        g_opt_override_debug_level;          // Temporary, used to disable existing debugs
extern bool        g_opt_quick_start;                   // Start in the main menu
extern bool        g_opt_quick_start_level_select_menu; // Start in the select menu
extern bool        g_opt_do_room_gen;                   // Test room gen
extern bool        g_opt_do_level_select_gen;           // Test level select gen
extern bool        g_opt_do_level_gen;                  // Test level gen
extern bool        g_opt_restarted;                     // Post restart
extern bool        g_opt_restarted_in_gfx_menu;         // Post restart
extern bool        g_opt_debug1;                        // Normal debugs
extern bool        g_opt_debug2;                        // All debugs
extern bool        g_opt_tests;                         // Dungeon tests

#endif
