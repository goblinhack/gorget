//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_MAIN_HPP_
#define _MY_MAIN_HPP_

#include "my_globals.hpp"
#include "my_types.hpp"

#include <string>

void        LOG(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        WARN(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        CON(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        CON_NEW_LINE(void);
void        TOPCON(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        TOPCON_NEW_LINE(void);
void        BOTCON(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        BOTCON_NEW_LINE(void);
void        cleanup(void);
void        restart(Gamep, const std::string);
void        reset_globals(void);
void        ctrlc_handler(int sig);
void        error_handler(const std::string &error);
void        segv_handler(int sig);
void        err_wrapper(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void        sdl_msg_box(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
FILE       *redirect_stdout(void);
FILE       *redirect_stderr(void);
void        find_file_locations(void);
std::string log_dir_create(void);

#define MY_STDERR redirect_stderr()
#define MY_STDOUT redirect_stdout()

void DYING(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void CLEANUP_ERR(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void CLEANUP_OK(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);

#define DIE(...)                                                                                                     \
  DYING("Died at %s:%s():%u", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);                                           \
  CLEANUP_ERR(__VA_ARGS__);                                                                                          \
  exit(1);

#define DIE_CLEAN(...)                                                                                               \
  DYING("Exiting at %s:%s():%u", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);                                        \
  CLEANUP_OK(__VA_ARGS__);                                                                                           \
  exit(0);

#ifdef DEBUG
#define DODEBUG(x) x
#else
#define DODEBUG(x)
#endif

#ifdef ENABLE_ASSERT
#undef ASSERT
#define ASSERT(x)                                                                                                    \
  if (unlikely(! (x))) {                                                                                             \
    DIE("Assert '%s' failed at %s:%s():%u", #x, SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);                         \
  }
#else
#define ASSERT(x)
#endif

// Based on
// https://stackoverflow.com/questions/2193544/how-to-print-additional-information-when-assert-fails
#ifdef ENABLE_ASSERT
#define ASSERT_EX(left, operator, right)                                                                             \
  if (! ((left) operator(right))) {                                                                                  \
    DIE("Assert '%s %s %s' failed at %s:%s():%u", #left, #operator, #right, SRC_FILE_NAME, SRC_FUNC_NAME,            \
        SRC_LINE_NUM);                                                                                               \
    ASSERT(left operator right);                                                                                     \
  }
#else
#define ASSERT_EX(left, operator, right)
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

#ifdef OPT_DEV
#define ERR DIE
#else
#define ERR                                                                                                          \
  TRACE_NO_INDENT();                                                                                                 \
  LOG("Error at %s:%s():%u", SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);                                            \
  err_wrapper
#endif

#endif
