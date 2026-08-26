//
// Copyright goblinhack@gmail.com
//

#ifndef MY_BACKTRACE_HPP
#define MY_BACKTRACE_HPP

#include <string>

auto               backtrace_dump() -> void;
auto               backtrace_dump(FILE *fp) -> void;
[[nodiscard]] auto backtrace_string() -> std::string;

#endif
