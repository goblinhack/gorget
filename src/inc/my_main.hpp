//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_MAIN_HPP_
#define _MY_MAIN_HPP_

#include "my_sys.hpp"

#include <map>
// REMOVED #include <string>
#include <string> // do not remove
#include <vector> // linux

extern char *DATA_PATH;
extern char *EXEC_DIR;
extern char *EXEC_FULL_PATH_AND_NAME;
extern char *GFX_PATH;
extern char *TTF_PATH;
extern char *WORLD_PATH;

extern bool g_die_occurred;             // Fatal error has occurred
extern bool g_do_screenshot;            // Grab a screen shot next fram
extern bool g_errored;                  // An error has occurred
extern bool g_grab_next_key;            // Waiting for key input
extern bool g_loading;                  // Currently loading
extern bool g_main_loop_running;        // SDL main loop is running.
extern bool g_need_restart;             // Need to restart game
extern bool g_opt_no_slow_log_flush;    // Do not flush after each console log at start
extern bool g_opt_override_debug_level; // Temporary, used to disable existing debugs
extern bool g_opt_test_skip_main_menu;  // Start in the main menu
extern bool g_quitting;                 // Exiting the game

extern bool g_opt_debug1;
extern bool g_opt_debug2;
extern bool g_opt_debug3;

extern std::map< std::string, class Tile * > all_tiles;
extern std::vector< class Tile * >           all_tiles_array;

extern std::string g_opt_seed_name;
extern std::string g_opt_player_name;

extern std::string g_log_stderr_filename;
extern std::string g_log_stdout_filename;

extern FILE *g_log_stdout;
extern FILE *g_log_stderr;

//
// The number of tiles on screen.
//
extern int TILES_VISIBLE_ACROSS;
extern int TILES_VISIBLE_DOWN;

#define DEBUG1 (unlikely(g_opt_debug1))
#define DEBUG2 (unlikely(g_opt_debug2))
#define DEBUG3 (unlikely(g_opt_debug3))

#define NODEBUG1 (likely(! g_opt_debug1))
#define NODEBUG2 (likely(! g_opt_debug2))
#define NODEBUG3 (likely(! g_opt_debug3))

#define IF_DEBUG                                                                                                     \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG1)
#define IF_DEBUG1                                                                                                    \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG1)
#define IF_DEBUG2                                                                                                    \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG2)
#define IF_DEBUG3                                                                                                    \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG3)

#define IF_NODEBUG                                                                                                   \
  TRACE_NO_INDENT();                                                                                                 \
  if (NODEBUG1)
#define IF_NODEBUG1                                                                                                  \
  TRACE_NO_INDENT();                                                                                                 \
  if (NODEBUG1)
#define IF_NODEBUG2                                                                                                  \
  TRACE_NO_INDENT();                                                                                                 \
  if (NODEBUG2)
#define IF_NODEBUG2                                                                                                  \
  TRACE_NO_INDENT();                                                                                                 \
  if (NODEBUG2)
#define IF_NODEBUG3                                                                                                  \
  TRACE_NO_INDENT();                                                                                                 \
  if (NODEBUG3)

#define ERR                                                                                                          \
  TRACE_NO_INDENT();                                                                                                 \
  myerr

#define dbg                                                                                                          \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG1)                                                                                                        \
  log
#define dbg2                                                                                                         \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG2)                                                                                                        \
  log
#define dbg3                                                                                                         \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG3)                                                                                                        \
  log

#define DBG                                                                                                          \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG1)                                                                                                        \
  LOG
#define DBG2                                                                                                         \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG2)                                                                                                        \
  LOG
#define DBG3                                                                                                         \
  TRACE_NO_INDENT();                                                                                                 \
  if (DEBUG3)                                                                                                        \
  LOG

#define MY_STDERR (g_log_stderr ? g_log_stderr : stderr)
#define MY_STDOUT (g_log_stdout ? g_log_stdout : stdout)

#if defined(__GNUC__) || defined(__clang__)
#define CHECK_FORMAT_STR(a, b, c) __attribute__((format(a, b, c)))
#else
#define CHECK_FORMAT_STR(a, b, c)
#endif

void DYING(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void CROAK(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void CROAK_CLEAN(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);

#define DIE(...)                                                                                                     \
  DYING("Died at %s:%s():%u", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);                                           \
  CROAK(__VA_ARGS__);                                                                                                \
  exit(1);

#define DIE_CLEAN(...)                                                                                               \
  DYING("Exiting at %s:%s():%u", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);                                        \
  CROAK_CLEAN(__VA_ARGS__);                                                                                          \
  exit(1);

#ifdef DEBUG
#define DODEBUG(x) x
#else
#define DODEBUG(x)
#endif

#ifdef ENABLE_ASSERT
#undef ASSERT
#define ASSERT(x)                                                                                                    \
  if (! (x)) {                                                                                                       \
    TRACE_AND_INDENT();                                                                                              \
    std::stringstream ss;                                                                                            \
    ss << "Assert '" << #x << "' failed at line " << __LINE__ << ", file " << __FILE__ << ", function "              \
       << __FUNCTION__ << "()";                                                                                      \
    {                                                                                                                \
      auto s = ss.str();                                                                                             \
      DIE("%s", s.c_str());                                                                                          \
    }                                                                                                                \
  }
#else
#define ASSERT(x)
#endif

// Based on
// https://stackoverflow.com/questions/2193544/how-to-print-additional-information-when-assert-fails
#ifdef ENABLE_ASSERT
#define ASSERT_EX(left, operator, right)                                                                                             \
  if (! ((left) operator(right))) {                                                                                                  \
    TRACE_AND_INDENT();                                                                                                              \
    std::cerr << "ASSERT FAILED: " << #left << " "                                                                                   \
              << #                                                                                                                   \
        operator<< " " << #right << " @ " << SRC_FILE_NAME << ":" << SRC_FUNC_NAME << " line"                                        \
                                                                                      " " << SRC_LINE_NUM << " " << #left << "=" <<( \
                                                                                          left)                                      \
              << "; " << #right << "=" << (right) << std::endl;                                                                      \
    ASSERT(left operator right);                                                                                                     \
  }
#else
#define ASSERT_EX(left, operator, right)
#endif

void common_error_handler(const std::string &error);
void CON(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void con(const char *fmt);
void CON(const char *fmt, ...);
void ctrlc_handler(int sig);
void die(void);
void error_handler(const std::string &error);
void flush_the_console(void);
void GAME_UI_MSG_BOX(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void LOG(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void myerr(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void py_myerr(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void quit(void);
void reset_globals(void);
void restart(void);
void SDL_MSG_BOX(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void segv_handler(int sig);
void CON(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void CON(const char *fmt, ...);
void WARN(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);

// REMOVED #include "my_callstack.hpp"

#endif
