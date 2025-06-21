//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_COMMAND_HPP_
#define _MY_COMMAND_HPP_

#include "my_types.hpp"
#include "my_token.hpp"

typedef uint8_t (*command_fn_t)(Gamep, class Tokens *, void *context);

void    command_fini(void);
uint8_t command_init(void);
void    command_add(Gamep, command_fn_t callback, std::string input, std::string readable_input);
uint8_t command_handle(Gamep, const char *input, char *expandedtext, uint8_t show_ambiguous, uint8_t show_complete,
                       uint8_t execute_command, void *context);
uint8_t command_handle(Gamep, std::string input, std::string *expanded_text, uint8_t show_ambiguous,
                       uint8_t show_complete, uint8_t execute_command, void *context);
void    commands_test(void);

#endif
