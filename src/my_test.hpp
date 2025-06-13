//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_TEST_H_
#define _MY_TEST_H_

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_minimal.hpp"
#include <string>

class Test;

const char *test_name(Testp);
Testp       test_load(const char *);

typedef bool (*test_callback_t)(Gamep, Testp);
void test_callback_set(Testp, test_callback_t);
void tests_run(Gamep);

#define TEST_FAILED(test)   LOG("Test %s: failed at %s:%u", test_name(test), __FUNCTION__, __LINE__);
#define TEST_PASSED(test)   LOG("Test %s: passed at %s:%u", test_name(test), __FUNCTION__, __LINE__);
#define TEST_LOG(test, msg) LOG("Test %s: %s:%u: %s", test_name(test), __FUNCTION__, __LINE__, msg);

#endif // _MY_TEST_H_
