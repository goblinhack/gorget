//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_COMMAND_HPP_
#define MY_COMMAND_HPP_

#include "my_token.hpp"
#include "my_types.hpp"

using command_fn_t = uint8_t (*)(Gamep, class Tokens *, void *context);

void    command_fini();
bool    command_init();
void    command_add(Gamep g, command_fn_t callback, std::string input, std::string readable_input);
uint8_t command_handle(Gamep g, const char *input, char *expandedtext, uint8_t show_ambiguous, uint8_t show_complete,
                       uint8_t execute_command, void *context);
uint8_t command_handle(Gamep g, std::string input, std::string *expanded_text, uint8_t show_ambiguous,
                       uint8_t show_complete, uint8_t execute_command, void *context);
void    commands_test();

#endif
