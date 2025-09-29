//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_UI_HPP_
#define _MY_UI_HPP_

#include "my_ascii.hpp"

#define UI_CONSOLE_HEIGHT             (TERM_HEIGHT * 2)
#define UI_CONSOLE_INPUT_COLOR        ORANGE
#define UI_CONSOLE_TEXT_COLOR         WHITE
#define UI_CONSOLE_WIDTH              (TERM_WIDTH - 3)
#define UI_CURSOR_COLOR               PURPLE
#define UI_CURSOR_OTHER_COLOR         WHITE
#define UI_FONT_HEIGHT                8
#define UI_FONT_WIDTH                 6
#define UI_LEFTBAR_WIDTH              34 // In characters
#define UI_HEALTH_BAR_STEPS           (UI_LEFTBAR_WIDTH - 2)
#define UI_RIGHTBAR_WIDTH             34  // In characters
#define UI_MOUSE_DOUBLE_CLICK         500 // Double click time
#define UI_WID_MOUSE_WHEEL_SCALE      1.0 // How much the wheel mouse moves when over a wid
#define UI_WID_MOUSE_WHEEL_SCALE_MAX  10
#define UI_GAME_MOUSE_WHEEL_SCALE     2.0 // How much the wheel mouse moves
#define UI_GAME_MOUSE_WHEEL_SCALE_MAX 50
#define UI_POPUP_TEXT_COLOR           UI_COLOR
#define UI_SCROLL_JOY_SCALE           1.0
#define UI_SCROLL_JOY_SCALE_MAX       1.5
#define UI_COLOR                      GRAY  // Default text color
#define UI_HIGHLIGHT_COLOR            WHITE // Default highlight color
#define UI_COLOR_STR                  "gray"
#define UI_FMT_STR                    "%%fg=" UI_COLOR_STR "$"
#define UI_INFO_FMT_STR               "%%fg=green$"
#define UI_HIGHLIGHT_FMT_STR          "%%fg=white$"
#define UI_SHORTCUT_FMT_STR           "%%fg=orange$"
#define UI_WARNING_FMT_STR            "%%fg=yellow$"
#define UI_IMPORTANT_FMT_STR          "%%fg=red$"
#define UI_GOOD_FMT_STR               "%%fg=gold$"
#define UI_RESET_FMT                  "%%fg=reset$"
#define UI_GREEN_FMT_STR              "%%fg=green$"
#define UI_WHITE_FMT_STR              "%%fg=white$"
#define UI_ORANGE_FMT_STR             "%%fg=orange$"
#define UI_YELLOW_FMT_STR             "%%fg=yellow$"
#define UI_RED_FMT_STR                "%%fg=red$"
#define UI_TILE_HEIGHT                8
#define UI_TILE_WIDTH                 8
#define UI_TYPE_PIXELART              0
#define UI_TYPES_MAX                  1
#define UI_WID_POPUP_WIDTH_NORMAL     18
#define UI_WID_POPUP_WIDTH_WIDE       60
#define UI_WID_SAVE_SLOTS             10 // How many save game slots
#define UI_MAX_SEED_NAME_LEN          10
#define UI_MAX_PLAYER_NAME_LEN        12
#define UI_MAX_WID_CONTEXT            2

#define UI_CENTER_WIDTH (TERM_WIDTH - UI_RIGHTBAR_WIDTH - UI_LEFTBAR_WIDTH)

#define UI_TOPCON_TEXT_COLOR UI_COLOR
#define UI_TOPCON_HEIGHT     4
#define UI_TOPCON_WIDTH      UI_CENTER_WIDTH

#define UI_BOTCON_WIDTH      UI_CENTER_WIDTH
#define UI_BOTCON_HEIGHT     1 // Scrollbar limit
#define UI_BOTCON_TEXT_COLOR UI_COLOR

#define UI_INVENTORY_WIDTH  (UI_CENTER_WIDTH - 2)
#define UI_INVENTORY_HEIGHT (THING_INVENTORY_MAX + 9)

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
  UI_WID_STYLE_SOLID_GRAY,
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
