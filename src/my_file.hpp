//
// Copyright goblinhack@gmail.com
//

#ifndef MY_FILE_HPP_
#define MY_FILE_HPP_

auto            file_write(const char *filename, unsigned char *buffer, int len) -> int;
auto        file_exists(const char *filename) -> uint8_t;
auto            file_size(const char *filename) -> int;
auto        file_non_zero_size_exists(const char *filename) -> uint8_t;
auto        file_unlink(const char *filename) -> uint8_t;
auto         file_age(const char *filename) -> double;
auto        file_exists_and_is_newer_than(const char *filename, const char *filename2) -> uint8_t;
auto file_load(const char *filename, int *outlen) -> unsigned char *;
void           log_(const char *fmt, va_list args);

#if defined(__WIN64__) || defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(_WIN32)                 \
    || defined(WIN32) || defined(__WINDOWS_386__) || defined(__CYGWIN__)
#define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#define SET_BINARY_MODE(file)
#endif

void FILE_LOG(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void FILE_DBG(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);

#endif
