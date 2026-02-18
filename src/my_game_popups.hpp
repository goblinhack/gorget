//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GAME_POPUP_HPP_
#define _MY_GAME_POPUP_HPP_

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
  // To avoid overlapping text
  //
  uint32_t y_offset {};
  //
  // Text color
  //
  color fg;
};

class GamePopups
{
public:
  std::list< GamePopup * > all;
};

void game_popup_text_add(Gamep, int /*x*/, int /*y*/, const std::string & /*text*/, color c = WHITE);
bool game_popups_present(Gamep, int /*x*/, int /*y*/);
void game_popups_age(Gamep);
void game_popups_clear(Gamep);
void game_popups_display(Gamep, Levelsp, Levelp);

std::list< GamePopup * > *game_popups_get(Gamep, int /*x*/, int /*y*/);
void                      game_popups_set(Gamep, int /*x*/, int /*y*/, std::list< GamePopup * > &);

#endif /* _MY_GAME_POPUP_HPP_ */
