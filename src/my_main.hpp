//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_MAIN_HPP_
#define _MY_MAIN_HPP_

#include "my_types.hpp"

#include <string>

FILE       *redirect_stderr(void);
FILE       *redirect_stdout(void);
std::string log_dir_create(void);
void        BOTCON_NEW_LINE(void);
void        BOTCON(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        cleanup(void);
void        CON_NEW_LINE(void);
void        CON(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        ctrlc_handler(int sig);
void        err_wrapper(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        error_handler(const std::string &error);
void        find_file_locations(void);
void        LOG(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        reset_globals(void);
void        restart(Gamep, const std::string);
void        sdl_msg_box(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        segv_handler(int sig);
void        TOPCON_NEW_LINE(void);
void        TOPCON(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        WARN(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        CLEANUP_ERR(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        CLEANUP_OK(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        DYING(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);

#define MY_STDERR redirect_stderr()
#define MY_STDOUT redirect_stdout()

#define DIE(...)                                                                                                     \
  /* Log this now, just in case we crash later */                                                                    \
  fprintf(stderr, "DIE: " __VA_ARGS__);                                                                              \
  fprintf(stderr, "\n");                                                                                             \
  fprintf(MY_STDERR, "DIE: " __VA_ARGS__);                                                                           \
  fprintf(MY_STDERR, "\n");                                                                                          \
  if (g_thread_id == -1) {                                                                                           \
    DYING("Died at %s:%s():%u, thread %u", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM, g_thread_id);                 \
    CLEANUP_ERR(__VA_ARGS__);                                                                                        \
    exit(1);                                                                                                         \
  } else {                                                                                                           \
    DYING("Thread died at %s:%s():%u, thread %u", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM, g_thread_id);          \
  }

#define DIE_CLEAN(...)                                                                                               \
  DYING("Exiting at %s:%s():%u", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);                                        \
  CLEANUP_OK(__VA_ARGS__);                                                                                           \
  exit(0);

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

#ifdef _DEBUG_BUILD_
#define ERR DIE
#else
#define ERR                                                                                                          \
  TRACE_NO_INDENT();                                                                                                 \
  LOG("Error at %s:%s():%u", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);                                            \
  err_wrapper
#endif

#endif
