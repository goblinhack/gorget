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

typedef bool (*test_callback_t)(Gamep);
void test_callback_set(Testp, test_callback_t);

#endif // _MY_TEST_H_
