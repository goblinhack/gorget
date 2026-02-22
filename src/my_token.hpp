//
// Copyright goblinhack@gmail.com
//

#ifndef MY_TOKEN_HPP
#define MY_TOKEN_HPP

#include "3rdparty/slre.hpp" // NOLINT
#include "my_string.hpp"

class Tokens
{
public:
  struct slre regexp[ MAXSHORTSTR ];
  char       *args[ MAXSHORTSTR ];
  char        data[ MAXSHORTSTR ];
  uint32_t    cnt;
};

auto tokens_to_string(const char *input, class Tokens *tokens) -> class Tokens *;
void tokens_print_to(class Tokens *tokens, char *output, int output_size);
void tokens_print(class Tokens *tokens);
void tokens_test();
#endif
