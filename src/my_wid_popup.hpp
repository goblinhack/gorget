//
// Copyright goblinhack@gmail.com
//

#ifndef _MY_UI_WID_POPUP_HPP_
#define _MY_UI_WID_POPUP_HPP_

#include <map>
#include <string>
#include <vector>

#include "my_wid_text_box.hpp"

class WidPopup
{
private:
  std::map< unsigned int, std::string > wid_popup_lines;
  std::vector< Widp >                   children;

public:
  Widp        wid_popup_container {};
  Widp        wid_title {};
  WidTextBox *wid_text_area {};

  spoint      tl;
  spoint      br;
  Tilep       title_tile {};
  std::string background;
  std::string name;
  int         outer_w {};
  int         outer_h {};
  int         inner_w {};
  int         inner_h {};

  ~WidPopup();
  WidPopup(Gamep g, std::string name, spoint tl, spoint br, Tilep title_tile = nullptr, std::string background = "",
           bool horiz_scroll = true, bool vert_scoll = true, int vert_scroll_size = -1);

  Widp log(Gamep g, std::string s, wid_text_format format = TEXT_FORMAT_NONE, std::string c = "") const;
  Widp log_empty_line(Gamep g) const;

  //
  // Get rid of trailing empty lines
  //
  void compress(Gamep g) const;
};

#endif
