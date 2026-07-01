//
// Copyright goblinhack@gmail.com
//

#ifndef MY_SPRINTF_HPP
#define MY_SPRINTF_HPP

#include "my_types.hpp"

#include <string>

std::string string_sprintf(const char *format, ...) CHECK_FORMAT_STR(printf, 1, 2); // NOLINT
                                                                                    //
[[nodiscard]] auto        string_sprintf(const char *format, va_list args) -> std::string;
[[nodiscard]] std::string string_append_with_comma(const std::string &in, const std::string &add);
[[nodiscard]] auto        string_sprintf_append_with_comma(const std::string &in, const char *format, va_list args) -> std::string;
[[nodiscard]] auto        string_sprintf_append_with_comma(const std::string &in, const char *format, ...) -> std::string;

#endif
