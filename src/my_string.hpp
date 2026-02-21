//
// Copyright goblinhack@gmail.com
//

#ifndef MY_STRING_UTIL_HPP_
#define MY_STRING_UTIL_HPP_

#include "my_types.hpp"

#include <string>
#include <vector>

extern size_t my_strlcpy(char *dst, const char *src, size_t size);
extern size_t my_strlcat(char *dst, const char *src, size_t size);
extern char  *my_strcasestr(const char *s, const char *find);

//
// Max long string size
//
enum {
  MAXLONGSTR  = (1024 * 16), // Needs to be big for long tracebacks
  MAXSTR      = 1024,
  MAXSHORTSTR = 128
};

char *dynprintf(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
char *strappend(const char *in, const char *append);
char *strprepend(const char *in, const char *prepend);

int length_without_format(const std::string &text);
int snprintf_realloc(char **str, int *size, int *used, const char *fmt, ...);
int strisregexp(const char *in);

std::vector< std::string > split(const std::string &text, int max_line_len);

std::string  capitalize(std::string in);
std::string  capitalize_first(std::string in);
std::string &ltrim(std::string &s);
std::string  ltrim_ws(const std::string &s);
std::string  mybasename(const char *in, const char *who);
std::string &rtrim(std::string &s);
std::string  rtrim_ws(const std::string &s);
std::string  strerror_to_string(int err);
std::string &trim(std::string &s);
std::string  trim_ws(const std::string &s);

uint32_t strcommon(const char *a, const char *b);
void     hexdump(const unsigned char *addr, size_t len);
void     hexdump(std::vector< unsigned char > &v);
void     strchop(char *s);
void     strchopc(char *s, char c);
void     strnoescape(char *uncompressed);
void     strrepc(char *s, const char *replace_set, char replace_with);

std::vector< std::string > split_tokens(const std::string &s, char delimiter);
void                       replace(std::string &input, const std::string &pattern, const std::string &replace_with);

#ifdef _WIN32
#define strerror_r(_errno_, _buf_, _len_) strerror_s(_buf_, _len_, _errno_)
#endif

#endif
