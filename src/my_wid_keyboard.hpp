//
// Copyright goblinhack@gmail.com
//

#pragma once

using wid_keyboard_event_t = void (*)(Gamep, Widp, const std::string &text);

#define WID_KEYBOARD_ACROSS 12
#define WID_KEYBOARD_DOWN   5

using wid_keyboard_ctx = struct {
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

};

Widp wid_keyboard(Gamep g, const std::string &text, const std::string &title, wid_keyboard_event_t selected,
                  wid_keyboard_event_t cancelled, size_t max_len);

extern int wid_keyboard_visible;
