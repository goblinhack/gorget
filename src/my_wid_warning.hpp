//
// Copyright goblinhack@gmail.com
//

#ifndef MY_WID_WARNING_HPP
#define MY_WID_WARNING_HPP

#include "my_wid_popup.hpp"

//
// Return true on the event being consumed
//
using wid_warning_callback_t = void (*)(Gamep, bool);
extern void      wid_warning(Gamep g, const std::string &warning, wid_warning_callback_t callback = nullptr);
extern WidPopup *wid_warning_window;

#endif
