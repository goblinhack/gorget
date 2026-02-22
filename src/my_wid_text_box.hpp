//
// Copyright goblinhack@gmail.com
//

#ifndef MY_WID_TEXT_BOX_HPP_
#define MY_WID_TEXT_BOX_HPP_

#include "my_types.hpp"
#include "my_wid.hpp"

#include <map>
#include <vector>

using wid_text_format = enum wid_text_format_ {
  TEXT_FORMAT_NONE,
  TEXT_FORMAT_LHS,
  TEXT_FORMAT_RHS,
};

class WidTextBox
{
private:
  std::map< unsigned int, std::string > wid_text_box_lines;
  int                                   width {};
  int                                   height {};
  int                                   scroll_height {};

  std::vector< Widp > children;

public:
  int    line_count {};
  spoint tl = {};
  spoint br = {};
  Widp   wid_horiz_scroll {};
  Widp   wid_parent {};
  Widp   wid_text_area {};
  Widp   wid_text_box_container {};
  Widp   wid_text_last {};
  Widp   wid_vert_scroll {};

  ~WidTextBox();
  WidTextBox(Gamep g, spoint tl, spoint br, Widp /*vparent*/, bool horiz_scroll = true, bool vert_scoll = true,
             int scroll_height = -1);

private:
  auto log_(Gamep g, const std::string & /*str*/, wid_text_format format = TEXT_FORMAT_NONE,
            const std::string &c = "") -> Widp;

public:
  auto log(Gamep g, const std::string &s, wid_text_format format = TEXT_FORMAT_NONE, const std::string &c = "") -> Widp;
  auto log_empty_line(Gamep g) -> Widp;
};
#endif
