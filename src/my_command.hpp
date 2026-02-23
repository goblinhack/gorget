//
// Copyright goblinhack@gmail.com
//

#ifndef MY_COMMAND_HPP
#define MY_COMMAND_HPP

#include "my_token.hpp"
#include "my_types.hpp"

using command_fn_t = uint8_t (*)(Gamep, class Tokens *, void *context);

void command_fini();
auto command_init() -> bool;
void command_add(Gamep g, command_fn_t callback, const std::string &input, const std::string &readable_input);
auto command_handle(Gamep g, const char *input, char *expandedtext, uint8_t show_ambiguous, uint8_t show_complete, uint8_t execute_command,
                    void *context) -> uint8_t;
auto command_handle(Gamep g, const std::string &input, std::string *expanded_text, uint8_t show_ambiguous, uint8_t show_complete,
                    uint8_t execute_command, void *context) -> uint8_t;
void commands_test();

#endif
