//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GAME_POPUP_HPP_
#define _MY_GAME_POPUP_HPP_

#include <list>

class GamePopup
{
public:
  std::string text;
  //
  // When this was created. Used to calculate fade up and timeout.
  //
  uint32_t created {};
};

class GamePopups
{
public:
  std::list< GamePopup > all;
};

void game_popup_text_add(Gamep, int, int, const char *);
bool game_popups_present(Gamep, int, int);
void game_popup_cleanup(Gamep);

std::list< GamePopup > &game_popups_get(Gamep, int, int);

#endif /* _MY_GAME_POPUP_HPP_ */
