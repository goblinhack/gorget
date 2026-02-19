//
// Copyright goblinhack@gmail.com
//

#ifndef _MY_MAIN_HPP_
#define _MY_MAIN_HPP_

#include "my_types.hpp"

#include <string>

std::string log_dir_create();
void        BOTCON_NEW_LINE();
void        BOTCON(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        cleanup();
void        CON_NEW_LINE();
void        CON(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        ctrlc_handler(int sig);
void        error_message(Gamep g, const std::string &error);
void        error_clear(Gamep g);
void        find_file_locations();
void        LOG(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        reset_globals();
void        restart(Gamep g, const std::string& /*restart_arg*/);
void        sdl_msg_box(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        crash_handler(int sig);
void        TOPCON_NEW_LINE();
void        TOPCON(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        WARN(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        CROAK_HANDLE(bool clean, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void        ERR_HANDLE(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);

FILE *redirect_stderr();
FILE *redirect_stdout();
void  close_stderr();
void  close_stdout();
#define MY_STDERR redirect_stderr()
#define MY_STDOUT redirect_stdout()

#define CROAK(...)                                                                                                   \
  /* Log this now, just in case we crash later */                                                                    \
  fprintf(stderr, "CROAK: " __VA_ARGS__);                                                                            \
  fprintf(stderr, "\n");                                                                                             \
  if (stderr != MY_STDERR) {                                                                                         \
    fprintf(MY_STDERR, "CROAK: " __VA_ARGS__);                                                                       \
    fprintf(MY_STDERR, "\n");                                                                                        \
  }                                                                                                                  \
  if (g_thread_id == MAIN_THREAD) {                                                                                  \
    fprintf(stderr, "Croaked it at %s:%s():%u, main thread\n", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);          \
    if (stderr != MY_STDERR) {                                                                                       \
      fprintf(MY_STDERR, "Croaked it at %s:%s():%u, main thread\n", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);     \
    }                                                                                                                \
    CROAK_HANDLE(false, __VA_ARGS__);                                                                                \
    cleanup();                                                                                                       \
    exit(1);                                                                                                         \
  } else {                                                                                                           \
    fprintf(stderr, "Croaked it at %s:%s():%u, thread %u\n", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM,             \
            g_thread_id);                                                                                            \
    if (stderr != MY_STDERR) {                                                                                       \
      fprintf(MY_STDERR, "Croaked it at %s:%s():%u, thread %u\n", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM,        \
              g_thread_id);                                                                                          \
    }                                                                                                                \
    CROAK_HANDLE(false, __VA_ARGS__);                                                                                \
    exit(1);                                                                                                         \
  }

#define DIE_CLEAN(...)                                                                                               \
  CROAK_HANDLE(true, "Exiting at %s:%s():%u", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);                           \
  cleanup();                                                                                                         \
  exit(0);

#ifdef _DEBUG_BUILD_
#define ERR CROAK
#else
#define ERR(...)                                                                                                     \
  /* Log this now, just in case we crash later */                                                                    \
  fprintf(stderr, "ERR: " __VA_ARGS__);                                                                              \
  fprintf(stderr, "\n");                                                                                             \
  if (stderr != MY_STDERR) {                                                                                         \
    fprintf(MY_STDERR, "ERR: " __VA_ARGS__);                                                                         \
    fprintf(MY_STDERR, "\n");                                                                                        \
  }                                                                                                                  \
  if (g_thread_id == MAIN_THREAD) {                                                                                  \
    fprintf(stderr, "Error at %s:%s():%u, main thread\n", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);               \
    if (stderr != MY_STDERR) {                                                                                       \
      fprintf(MY_STDERR, "Error at %s:%s():%u, main thread\n", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);          \
    }                                                                                                                \
    ERR_HANDLE(__VA_ARGS__);                                                                                         \
  } else {                                                                                                           \
    fprintf(stderr, "Error at %s:%s():%u, thread %u\n", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM, g_thread_id);    \
    if (stderr != MY_STDERR) {                                                                                       \
      fprintf(MY_STDERR, "Error at %s:%s():%u, thread %u\n", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM,             \
              g_thread_id);                                                                                          \
    }                                                                                                                \
    ERR_HANDLE(__VA_ARGS__);                                                                                         \
  }
#endif

#define DEBUG       (unlikely(g_opt_debug1))
#define DEBUG2      (unlikely(g_opt_debug2))
#define NODEBUG     (likely(! g_opt_debug1))
#define NODEBUG2    (likely(! g_opt_debug2))
#define IF_DEBUG    if (DEBUG)
#define IF_DEBUG2   if (DEBUG2)
#define IF_NODEBUG  if (NODEBUG)
#define IF_NODEBUG2 if (NODEBUG2)

#define DBG                                                                                                          \
  if (DEBUG)                                                                                                         \
  LOG

#define DBG2                                                                                                         \
  if (DEBUG2)                                                                                                        \
  LOG

//
// Used to stop the compiler removing unused code I want to keep
//
extern bool compiler_unused;

#endif
