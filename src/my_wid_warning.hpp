//
// Copyright goblinhack@gmail.com
//

#pragma once

#include "my_wid_popup.hpp"

//
// Return true on the event being consumed
//
using wid_warning_callback_t = void (*)(Gamep, bool);
extern void      wid_warning(Gamep g, std::string error, wid_warning_callback_t callback = nullptr);
extern WidPopup *wid_warning_window;
