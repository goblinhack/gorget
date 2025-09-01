//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_TEST_H_
#define _MY_TEST_H_

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_string.hpp"
#include "my_types.hpp"

#include <string>

class Test;

const char *test_name(Testp);
Testp       test_load(const char *);

typedef bool (*test_callback_t)(Gamep, Testp);
void test_callback_set(Testp, test_callback_t);
void tests_run(Gamep);

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

#if defined(__clang__)
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

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#pragma GCC diagnostic pop

#define TEST_PROGRESS(test) LOG("Test %s: %s:%u: progress", test_name(test), __FUNCTION__, __LINE__);

#endif // _MY_TEST_H_
