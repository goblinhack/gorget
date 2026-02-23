//
// Copyright goblinhack@gmail.com
//

#ifndef MY_STRING_UTIL_HPP
#define MY_STRING_UTIL_HPP

#include "my_types.hpp"

#include <string>
#include <vector>

extern auto my_strlcpy(char *dst, const char *src, size_t max_len) -> size_t;
extern auto my_strlcat(char *dst, const char *src, size_t max_len) -> size_t;
extern auto my_strcasestr(const char *s, const char *find) -> char *;

//
// Max long string size
//
enum {
  MAXLONGSTR  = (1024 * 16), // Needs to be big for long tracebacks
  MAXSTR      = 1024,
  MAXSHORTSTR = 128
};

char *dynprintf(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2); // NOLINT
auto  strappend(const char *in, const char *append) -> char *;
auto  strprepend(const char *in, const char *prepend) -> char *;

auto length_without_format(const std::string &text) -> int;
auto snprintf_realloc(char **str, int *size, int *used, const char *fmt, ...) -> int;
auto strisregexp(const char *in) -> int;

auto split(const std::string &text, int max_line_len) -> std::vector< std::string >;

auto capitalize(std::string in) -> std::string;
auto capitalize_first(const std::string &in) -> std::string;
auto ltrim(std::string &s) -> std::string &;
auto ltrim_ws(const std::string &s) -> std::string;
auto mybasename(const char *in, const char *who) -> std::string;
auto rtrim(std::string &s) -> std::string &;
auto rtrim_ws(const std::string &s) -> std::string;
auto strerror_to_string(int err) -> std::string;
auto trim(std::string &s) -> std::string &;
auto trim_ws(const std::string &s) -> std::string;

auto strcommon(const char *a, const char *b) -> uint32_t;
void hexdump(const unsigned char *addr, size_t len);
void hexdump(std::vector< unsigned char > &v);
void strchop(char *s);
void strchopc(char *s, char c);
void strnoescape(char *uncompressed);
void strrepc(char *s, const char *replace_set, char replace_with);

auto split_tokens(const std::string &s, char delimiter) -> std::vector< std::string >;
void replace(std::string &input, const std::string &pattern, const std::string &replace_with);

#ifdef _WIN32
#define strerror_r(_errno_, _buf_, _len_) strerror_s(_buf_, _len_, _errno_)
#endif

#endif
