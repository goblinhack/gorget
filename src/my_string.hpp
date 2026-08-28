//
// Copyright goblinhack@gmail.com
//

#ifndef MY_STRING_UTIL_HPP
#define MY_STRING_UTIL_HPP

#include "my_types.hpp"

#include <string>
#include <vector>

//
// Max long string size
//
enum {
  MAXLONGSTR  = (1024 * 16), // Needs to be big for long tracebacks
  MAXSTR      = 1024,
  MAXSHORTSTR = 128
};

[[nodiscard]] auto  my_strlcpy(char *dst, const char *src, size_t max_len) -> size_t;
[[nodiscard]] auto  my_strlcat(char *dst, const char *src, size_t max_len) -> size_t;
[[nodiscard]] auto  my_strcasestr(const char *s, const char *find) -> char *;
[[nodiscard]] auto  capitalize_first(const std::string &in) -> std::string;
[[nodiscard]] auto  capitalize(std::string in) -> std::string;
[[nodiscard]] auto  length_without_format(const std::string &text) -> int;
[[nodiscard]] auto  ltrim_ws(const std::string &s) -> std::string;
[[nodiscard]] auto  ltrim(std::string &s) -> std::string &;
[[nodiscard]] auto  mybasename(const char *in, const char *who) -> std::string;
[[nodiscard]] auto  rtrim_ws(const std::string &s) -> std::string;
[[nodiscard]] auto  rtrim(std::string &s) -> std::string &;
[[nodiscard]] auto  split(const std::string &text, int max_line_len) -> std::vector< std::string >;
[[nodiscard]] auto  strappend(const char *in, const char *append) -> char *;
[[nodiscard]] auto  strcommon(const char *a, const char *b) -> uint32_t;
[[nodiscard]] auto  strerror_to_string(int err) -> std::string;
[[nodiscard]] auto  strisregexp(const char *in) -> int;
[[nodiscard]] auto  strprepend(const char *in, const char *prepend) -> char *;
[[nodiscard]] auto  trim_ws(const std::string &s) -> std::string;
[[nodiscard]] auto  trim(std::string &s) -> std::string &;
[[nodiscard]] auto  split_tokens(const std::string &s, char delimiter) -> std::vector< std::string >;
[[nodiscard]] char *dynprintf(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2); // NOLINT
[[nodiscard]] auto  truncate(std::string str, size_t width, bool show_ellipsis = true) -> std::string;

auto hexdump(const uint8_t *addr, size_t len) -> void;
auto hexdump(std::vector< uint8_t > &v) -> void;
auto strchop(char *s) -> void;
auto strchopc(char *s, char c) -> void;
auto strnoescape(char *uncompressed) -> void;
auto strrepc(char *s, const char *replace_set, char replace_with) -> void;
auto replace(std::string &input, const std::string &pattern, const std::string &replace_with) -> void;

#ifdef _WIN32
#define strerror_r(_errno_, _buf_, _len_) strerror_s(_buf_, _len_, _errno_)
#endif

#endif
