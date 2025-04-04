//
// Copyright goblinhack@gmail.com
//

#pragma once

typedef void (*wid_keyboard_event_t)(Gamep g, Widp, const std::string &text);

#define WID_KEYBOARD_ACROSS 12
#define WID_KEYBOARD_DOWN   5

typedef struct {
  /*
   * Parent widget
   */
  Widp w;

  /*
   * Current button
   */
  Widp b;

  /*
   * Text input widget
   */
  Widp input;

  /*
   * Entered text.
   */
  std::string text;

  /*
   * Item currently in focus
   */
  int focusx;
  int focusy;

  /*
   * When the keyboard was made.
   */
  uint32_t created;

  /*
   * Items in the keyboard
   */
  Widp buttons[ WID_KEYBOARD_DOWN ][ WID_KEYBOARD_ACROSS ];

  /*
   * What to call on events
   */
  wid_keyboard_event_t selected;
  wid_keyboard_event_t cancelled;

  /*
   * Just created?
   */
  int is_new;

  size_t max_len;

} wid_keyboard_ctx;

Widp wid_keyboard(Gamep, const std::string &text, const std::string &title, wid_keyboard_event_t selected,
                  wid_keyboard_event_t cancelled, size_t max_len);

extern int wid_keyboard_visible;
