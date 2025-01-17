//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_UI_HPP_
#define _MY_UI_HPP_

#define UI_CONSOLE_HEIGHT           (TERM_HEIGHT * 2)
#define UI_CONSOLE_INPUT_COLOR      ORANGE
#define UI_CONSOLE_TEXT_COLOR       GRAY
#define UI_CONSOLE_WIDTH            (TERM_WIDTH - 3)
#define UI_CURSOR_COLOR             GRAY
#define UI_CURSOR_OTHER_COLOR       WHITE
#define UI_FONT_HEIGHT              8
#define UI_FONT_WIDTH               6
#define UI_LEFTBAR_WIDTH            20  // In characters
#define UI_RIGHTBAR_WIDTH           20  // In characters
#define UI_LOGGING_EMPTY_LINE       "`" // Complete hack, char I use to force space
#define UI_MOUSE_DOUBLE_CLICK       500 // Double click time
#define UI_MOUSE_WHEEL_SCALE        2.0 // How much the wheel mouse moves.
#define UI_MOUSE_WHEEL_SCALE_MAX    10
#define UI_POPUP_TEXT_COLOR         UI_TEXT_COLOR
#define UI_SCROLL_JOY_SCALE         1.0
#define UI_SCROLL_JOY_SCALE_MAX     1.5
#define UI_TEXT_COLOR               GRAY // Default text color
#define UI_TEXT_COLOR_STR           "gray"
#define UI_TEXT_HIGHLIGHT_COLOR_STR "white"
#define UI_TILE_HEIGHT              8
#define UI_TILE_WIDTH               8
#define UI_TOPCON_HEIGHT            4 // Scrollbar limit
#define UI_TOPCON_TEXT_COLOR        UI_TEXT_COLOR
#define UI_TOPCON_VIS_HEIGHT        UI_TOPCON_HEIGHT
#define UI_TOPCON_VIS_WIDTH         UI_TOPCON_WIDTH
#define UI_TOPCON_WIDTH             (TERM_WIDTH - UI_RIGHTBAR_WIDTH - UI_LEFTBAR_WIDTH)
#define UI_TYPE_PIXELART            0
#define UI_TYPES_MAX                1
#define UI_WID_POPUP_WIDTH_NORMAL   18
#define UI_WID_POPUP_WIDTH_WIDE     24
#define UI_WID_SAVE_SLOTS           10 // How many save game slots

//
// Do faster processing of events, like reading the keyboard and updating widgets.
//
#define UI_EVENT_LOOP_FREQ_FAST_MS 5

//
// Less frequent updates like updating the FPS.
//
#define UI_EVENT_LOOP_FREQ_SLOW_MS 10

//
// This is for waiting for level fade in.
//
#define UI_EVENT_LOOP_FREQ_VERY_SLOW_MS 20

enum {
  UI_WID_STYLE_SPARSE_NONE = -1, // Used for widgets with their own backgrounds
  UI_WID_STYLE_SOLID_NONE,
  UI_WID_STYLE_GREEN,
  UI_WID_STYLE_RED,
  UI_WID_STYLE_NORMAL,
  UI_WID_STYLE_CONSOLE,
  UI_WID_STYLE_UNUSED1,
  UI_WID_STYLE_UNUSED2,
  UI_WID_STYLE_UNUSED3,
  UI_WID_STYLE_VERT_DARK,
  UI_WID_STYLE_VERT_LIGHT,
  UI_WID_STYLE_HORIZ_DARK,
  UI_WID_STYLE_HORIZ_LIGHT,
  UI_WID_STYLE_VERT_SCROLL_DARK,
  UI_WID_STYLE_VERT_SCROLL_LIGHT,
  UI_WID_STYLE_HORIZ_SCROLL_DARK,
  UI_WID_STYLE_HORIZ_SCROLL_LIGHT,
  UI_WID_STYLE_MAX,
};

#endif
