//
// Copyright goblinhack@gmail.com
//

#ifndef MY_BACKTRACE_HPP
#define MY_BACKTRACE_HPP

#include <string>

void backtrace_dump();
void backtrace_dump(FILE *fp);
auto backtrace_string() -> std::string;

#endif
