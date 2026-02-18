//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_TEST_H_
#define _MY_TEST_H_

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level_ext.hpp"
#include "my_string.hpp"
#include "my_types.hpp"

#include <string>

class Test;

const char *test_name(Testp /*test*/);
Testp       test_load(const char       */*name_in*/);

typedef bool (*test_callback_t)(Gamep, Testp);
void test_callback_set(Testp /*test*/, test_callback_t /*callback*/);
void tests_run(Gamep g);

#define TEST_FAILED(test, why)                                                                                       \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    LOG("Test %s: failed at %s:%u, reason: %s", test_name(test), __FUNCTION__, __LINE__, why);                       \
    result = false;                                                                                                  \
    goto exit;                                                                                                       \
  }

#define TEST_ASSERT(test, what, why)                                                                                 \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    if (! (what)) {                                                                                                  \
      LOG("Test %s: assertion failed at %s:%u, reason: %s", test_name(test), __FUNCTION__, __LINE__, why);           \
      result = false;                                                                                                \
      goto exit;                                                                                                     \
    }                                                                                                                \
  }

#define TEST_PASSED(test) LOG("Test %s: passed at %s:%u", test_name(test), __FUNCTION__, __LINE__);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvariadic-macros"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#endif

#define TEST_LOG(test, msg, ...)                                                                                     \
  {                                                                                                                  \
    char tmp[ MAXSTR ];                                                                                              \
    snprintf(tmp, sizeof(tmp), msg, ##__VA_ARGS__);                                                                  \
    LOG("Test %s: %s:%u: %s", test_name(test), __FUNCTION__, __LINE__, tmp);                                         \
  }

#define TEST_CON(test, msg, ...)                                                                                     \
  {                                                                                                                  \
    char tmp[ MAXSTR ];                                                                                              \
    snprintf(tmp, sizeof(tmp), msg, ##__VA_ARGS__);                                                                  \
    CON("Test %s: %s:%u: %s", test_name(test), __FUNCTION__, __LINE__, tmp);                                         \
  }

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#pragma GCC diagnostic pop

#define TEST_PROGRESS(test) LOG("Test %s: %s:%u: progress", test_name(test), __FUNCTION__, __LINE__);

void test_init(void);
void test_fini(void);

[[nodiscard]] Levelsp game_test_init(Gamep, Levelp * out, LevelNum level_num, int w, int h,
                                     const char *contents, Overrides /*overrides*/ = no_overrides);

void game_test_init_level(Gamep, Levelsp, Levelp * out, LevelNum level_num, int w, int h,
                          const char *contents, Overrides /*overrides*/ = no_overrides);

void game_test_init_level(Gamep, Levelsp, Levelp * out, LevelNum level_num, spoint level_at, int w,
                          int h, const char *contents, Overrides /*overrides*/ = no_overrides);

#endif // _MY_TEST_H_
