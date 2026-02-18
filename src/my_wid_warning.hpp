//
// Copyright goblinhack@gmail.com
//

#pragma once

#include "my_wid_popup.hpp"

//
// Return true on the event being consumed
//
typedef void (*wid_warning_callback_t)(Gamep, bool);
extern void      wid_warning(Gamep, std::string error, wid_warning_callback_t callback = nullptr);
extern WidPopup *wid_warning_window;
