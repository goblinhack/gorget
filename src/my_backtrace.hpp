//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_BACKTRACE_HPP_
#define _MY_BACKTRACE_HPP_

#include <string>

void        backtrace_dump(void);
void        backtrace_dump(FILE        */*fp*/);
std::string backtrace_string(void);

#endif
