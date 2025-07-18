//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_WID_TEXT_BOX_HPP_
#define _MY_WID_TEXT_BOX_HPP_

#include "my_types.hpp"
#include "my_wid.hpp"

#include <map>
#include <vector>

typedef enum {
  TEXT_FORMAT_NONE,
  TEXT_FORMAT_LHS,
  TEXT_FORMAT_RHS,
} wid_text_format;

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
  spoint tl = spoint();
  spoint br = spoint();
  Widp   wid_horiz_scroll {};
  Widp   wid_parent {};
  Widp   wid_text_area {};
  Widp   wid_text_box_container {};
  Widp   wid_text_last {};
  Widp   wid_vert_scroll {};

  ~WidTextBox();
  WidTextBox(Gamep, spoint tl, spoint br, Widp, bool horiz_scroll = true, bool vert_scoll = true,
             int scroll_height = -1);

private:
  void log_(Gamep, const std::string &, wid_text_format format = TEXT_FORMAT_NONE, std::string color = "");

public:
  void log(Gamep, const std::string &, wid_text_format format = TEXT_FORMAT_NONE, std::string color = "");
  void log_empty_line(Gamep);
};
#endif
