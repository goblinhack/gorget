//
// Copyright goblinhack@gmail.com
//

#include <utility>

#include "my_random_name.hpp"

auto os_random_name(int len) -> std::string
{
  for (;;) {
    std::string const d1(os_rand_dict1_name());
    std::string const d2(os_rand_dict2_name());
    if (std::cmp_greater((d1.size() + d2.size()), len)) {
      continue;
    }

    return d1 + d2;
  }
}

// https://stackoverflow.com/questions/7666509/hash-function-for-string
static auto hash(const char *s) -> unsigned long
{
  unsigned long hash = 5381;
  char          c = 0;

  while ((c = *s++) != 0) {
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }

  return hash;
}

auto string_to_hash(const std::string &str) -> uint32_t
{
#ifdef FANCY_BUT_GIVES_DIFFERENT_RESULTS_ON_DIFFERENT_PLATFORMS
  return static_cast< uint32_t >(std::hash< std::string > {}(str));
#else
  return hash(str.c_str());
#endif
}
