//
// Copyright goblinhack@gmail.com
//

#ifndef MY_GAME_POPUP_HPP
#define MY_GAME_POPUP_HPP

#include "my_color.hpp"
#include "my_color_defs.hpp"

#include <list>
#include <string>

class GamePopup
{
public:
  std::string text;
  //
  // When this was created. Used to calculate fade up and timeout.
  //
  uint32_t created {};
  //
  // For duplicate messages
  //
  uint32_t count {};
  //
  // To avoid overlapping text
  //
  uint32_t y_offset {};
  //
  // Text color
  //
  color fg {};
};

class GamePopups
{
public:
  std::list< GamePopup * > all;
};

auto               game_popup_text_add(Gamep g, int x, int y, const std::string &text, color c = WHITE) -> void;
[[nodiscard]] auto game_popups_present(Gamep g, int x, int y) -> bool;
auto               game_popups_age(Gamep g) -> void;
auto               game_popups_clear(Gamep g) -> void;
auto               game_popups_display(Gamep g, Levelsp v, Levelp l) -> void;

[[nodiscard]] auto game_popups_get(Gamep g, int x, int y) -> std::list< GamePopup * > *;
auto               game_popups_set(Gamep g, int x, int y, std::list< GamePopup * > &l) -> void;

#endif /* MY_GAME_POPUP_HPP */
