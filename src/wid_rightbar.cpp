//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_sdl_event.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_popups.hpp"
#include "my_wid_rightbar.hpp"

static bool wid_rightbar_create(void);

Widp wid_rightbar {};
Widp wid_map_mini {};

static WidPopup *wid_rightbar_popup;

void wid_rightbar_fini(void)
{
  TRACE_AND_INDENT();
  wid_destroy(&wid_rightbar);
  wid_destroy(&wid_map_mini);

  delete wid_rightbar_popup;
  wid_rightbar_popup = nullptr;
}

bool wid_rightbar_init(void)
{
  TRACE_AND_INDENT();
  return wid_rightbar_create();
}

bool wid_rightbar_create(void)
{
  wid_rightbar_fini();

  auto level = game->level;
  if (! level) {
    return false;
  }

  return wid_rightbar_ascii_create();
}

bool is_mouse_over_rightbar(void)
{
  if (! wid_rightbar) {
    return false;
  }

  //
  // If we are in the portion of the lower screen above the itembar
  // then do not scroll
  //
  int x = sdl.mouse_x;
  int y = sdl.mouse_y;
  pixel_to_ascii(&x, &y);

  static int tlx, tly, brx, bry, cached;
  if (cached != TERM_HEIGHT) {
    cached = TERM_HEIGHT;
  }

  wid_get_tl_x_tl_y_br_x_br_y(wid_rightbar, &tlx, &tly, &brx, &bry);

  //
  // Add some border
  //
  tlx -= 1;
  brx++;
  tly -= 1;
  bry++;

  if ((x >= tlx) && (x < brx) && (y >= tly)) {
    // CON("    rightbar %d %d %d", tlx, brx, x);
    return true;
  }
  // CON("NOT rightbar %d %d %d", tlx, brx, x);

  return false;
}
