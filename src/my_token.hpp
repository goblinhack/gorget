//
// Copyright goblinhack@gmail.com
//

#ifndef MY_TOKEN_HPP
#define MY_TOKEN_HPP

#include "3rdparty/slre.hpp"
#include "my_string.hpp"

class Tokens
{
public:
  struct Slre regexp[ MAXSHORTSTR ];
  char       *args[ MAXSHORTSTR ];
  char        data[ MAXSHORTSTR ];
  uint32_t    cnt;
};

[[nodiscard]] auto tokens_to_string(const char *input, class Tokens *tokens) -> class Tokens *;

auto tokens_print_to(class Tokens *tokens, char *output, int output_size) -> void;
auto tokens_print(class Tokens *tokens) -> void;
auto tokens_test() -> void;

#endif
