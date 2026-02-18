//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_TOKEN_HPP_
#define _MY_TOKEN_HPP_

#include "3rdparty/slre.hpp"
#include "my_string.hpp"

class Tokens
{
public:
  struct slre regexp[ MAXSHORTSTR ];
  char       *args[ MAXSHORTSTR ];
  char        data[ MAXSHORTSTR ];
  uint32_t    cnt;
};

class Tokens *tokens_to_string(const char *input, class Tokens * /*tokens*/);
void          tokens_print_to(class Tokens          */*tokens*/, char *output, int output_size);
void          tokens_print(class Tokens          */*tokens*/);
void          tokens_test(void);
#endif
