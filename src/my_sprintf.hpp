//
// Copyright goblinhack@gmail.com
//

#ifndef MY_SPRINTF_HPP
#define MY_SPRINTF_HPP

#include "my_types.hpp"

#include <string>

std::string string_sprintf(const char *format, ...) CHECK_FORMAT_STR(printf, 1, 2); // NOLINT
auto        string_sprintf(const char *format, va_list args) -> std::string;

#endif
