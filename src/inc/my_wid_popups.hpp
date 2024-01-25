//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_UI_WID_POPUPS_HPP_
#define _MY_UI_WID_POPUPS_HPP_

#include "my_wid_popup.hpp"

extern void wid_load_destroy(void);
extern void wid_save_destroy(void);
extern void wid_quit_destroy(void);

extern WidPopup *wid_load;
extern WidPopup *wid_save;
extern WidPopup *wid_quit_window;

#endif
