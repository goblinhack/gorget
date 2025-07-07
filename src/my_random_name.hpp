#pragma once

#include <cstdint>
#include <string>

extern const char *os_rand_dict1_name(void);
extern const char *os_rand_dict2_name(void);
extern std::string os_random_name(int len);
extern uint32_t    string_to_hash(const std::string &str);
