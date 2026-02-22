//
// Copyright goblinhack@gmail.com
//

#ifndef MY_TIME_UTIL_HPP
#define MY_TIME_UTIL_HPP

#undef ONESEC
#define ONESEC 1000

#define MY_TIMESTAMP_SIZE 20

using ts_t = int;

#include <string>

auto time_have_x_hundredths_passed_since(ts_t val, ts_t since) -> bool;
auto time_have_x_ms_passed_since(ts_t val, ts_t since) -> bool;
auto time_have_x_secs_passed_since(ts_t val, ts_t since) -> bool;
auto time_have_x_tenths_passed_since(ts_t val, ts_t since) -> bool;

auto time2str(ts_t ms, char *buf, int len) -> const char *;
auto timestamp(char *buf, int len) -> const char *;

auto time_game_ms() -> ts_t;
auto time_game_ms_cached() -> ts_t;

auto time_ms() -> ts_t;
auto time_ms_cached() -> ts_t;

void get_timestamp(char *buf, int len);

auto current_date() -> std::string;
auto string_timestamp() -> std::string &;

extern ts_t time_now;
extern ts_t time_game;

#endif
