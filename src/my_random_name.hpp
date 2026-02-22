//
// Copyright goblinhack@gmail.com
//

#ifndef MY_RANDOM_NAME_HPP
#define MY_RANDOM_NAME_HPP

#include <cstdint>
#include <string>

extern auto os_rand_dict1_name() -> const char *;
extern auto os_rand_dict2_name() -> const char *;
extern auto os_random_name(int len) -> std::string;
extern auto string_to_hash(const std::string &str) -> uint32_t;

#endif
