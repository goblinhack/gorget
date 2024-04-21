//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_wid_console.hpp"

int  wid_mouse_visible = 1;
bool wid_mouse_two_clicks;
ts_t wid_last_mouse_motion;

//
// Catch recursive cases:
//
static int wid_mouse_motion_recursion;

static int saved_mouse_x;
static int saved_mouse_y;

void wid_mouse_motion_end(void) {}

void wid_mouse_motion_begin(Widp w, int x, int y) { wid_mouse_motion_end(); }

void wid_mouse_focus_end(void)
{
  Widp w {};

  w                = wid_focus;
  wid_focus        = nullptr;
  wid_focus_locked = nullptr;

  if (unlikely(! w)) {
    return;
  }

  if (w->on_mouse_focus_end) {
    w->on_mouse_focus_end(w);
  }
}

void wid_mouse_focus_begin(Widp w)
{
  Widp top {};

  if (unlikely(! w)) {
    wid_mouse_focus_end();
    wid_focus = nullptr;

    wid_find_top_focus();
    return;
  }

  if (wid_focus == w) {
    return;
  }

  wid_mouse_focus_end();

  if (wid_ignore_for_focus(w)) {
    return;
  }

  top = wid_get_top_parent(w);

  wid_focus       = w;
  top->focus_last = w->focus_order;

  if (w->on_mouse_focus_begin) {
    w->on_mouse_focus_begin(w);
  }
}

void wid_mouse_over_end(void)
{
  Widp w {};

  if (! wid_mouse_visible) {
    return;
  }

  w = wid_over;
  if (wid_over) {
    if (! wid_ignore_events(wid_over)) {
      wid_last_over_event = time_ms_cached();
      // DBG("mouse over end %s mouse %d,%d.", wid_over->name.c_str(), ascii_mouse_x, ascii_mouse_y);
    }
  }
  wid_over = nullptr;

  if (unlikely(! w)) {
    return;
  }

  wid_set_mode(w, WID_MODE_NORMAL);

  if (wid_exiting) {
    return;
  }

  if (w->on_mouse_over_end) {
    w->on_mouse_over_end(w);
  }
}

static bool wid_mouse_over_begin(Widp w, uint32_t x, uint32_t y, int relx, int rely, int wheelx, int wheely)
{
  if (! wid_mouse_visible) {
    return false;
  }

  if (wid_over == w) {
    return true;
  }

  if (wid_ignore_events(w)) {
    return false;
  }

  if (wheelx || wheely) {
    if (wid_ignore_scroll_events(w)) {
      return false;
    }
  }

  if (! w->on_mouse_over_begin && ! w->on_mouse_down) {
    if (w->cfg[ WID_MODE_OVER ].color_set[ WID_COLOR_BG ] || w->cfg[ WID_MODE_OVER ].color_set[ WID_COLOR_TEXT_FG ]) {
      //
      // Changes appearance on mouse over, so choose this wid even
      // if it has no over callback.
      //
    } else {
      //
      // Can ignore. It doesn't really do anything when the mouse
      // is over.
      //
      if (! wid_over && wid_on_screen_at[ x ][ y ]) {
        //
        // But if we have nothing else, use this
        //
      } else {
        return false;
      }
    }
  }

  if (wid_ignore_being_destroyed(w)) {
    return false;
  }

  wid_mouse_over_end();

  wid_over = w;
  if (! wid_ignore_events(wid_over)) {
    wid_last_over_event = time_ms_cached();
    // DBG("mouse over %s mouse %d,%d.", wid_over->name.c_str(), ascii_mouse_x, ascii_mouse_y);
  }

  wid_set_mode(w, WID_MODE_OVER);

  if (w->on_mouse_over_begin) {
    (w->on_mouse_over_begin)(w, relx, rely, wheelx, wheely);
  }

  return true;
}
void wid_set_on_mouse_down(Widp w, on_mouse_down_t fn) { w->on_mouse_down = fn; }

void wid_set_on_mouse_held(Widp w, on_mouse_down_t fn) { w->on_mouse_held = fn; }

void wid_set_on_mouse_up(Widp w, on_mouse_up_t fn) { w->on_mouse_up = fn; }

void wid_set_on_mouse_motion(Widp w, on_mouse_motion_t fn) { w->on_mouse_motion = fn; }

void wid_set_on_mouse_focus_begin(Widp w, on_mouse_focus_begin_t fn) { w->on_mouse_focus_begin = fn; }

void wid_set_on_mouse_focus_end(Widp w, on_mouse_focus_end_t fn) { w->on_mouse_focus_end = fn; }

void wid_set_on_mouse_over_begin(Widp w, on_mouse_over_begin_t fn) { w->on_mouse_over_begin = fn; }

void wid_set_on_mouse_over_end(Widp w, on_mouse_over_end_t fn) { w->on_mouse_over_end = fn; }

bool wid_scroll_trough_mouse_down(Widp w, int x, int y, uint32_t button)
{
  int dx;
  int dy;

  std::vector< Widp > worklist;
  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;
    worklist.push_back(child);
  }

  for (auto &child : worklist) {
    dx = 0;
    dy = 0;

    if (x < wid_get_tl_x(child)) {
      dx = -1;
    }

    if (x > wid_get_tl_x(child)) {
      dx = 1;
    }

    if (y < wid_get_tl_y(child)) {
      dy = -1;
    }

    if (y > wid_get_tl_y(child)) {
      dy = 1;
    }

    if (dx || dy) {
      wid_set_mode(child, WID_MODE_ACTIVE);
    }

    if (! wid_get_moveable_horiz(child)) {
      dx = 0;
    }

    if (! wid_get_moveable_vert(child)) {
      dy = 0;
    }

    wid_move_delta(child, dx, dy);
  }

  return true;
}

bool wid_scroll_trough_mouse_motion(Widp w, int x, int y, int relx, int rely, int wheelx, int wheely)
{
  int dx;
  int dy;

  if ((SDL_BUTTON(SDL_BUTTON_LEFT) & SDL_GetMouseState(0, 0)) || wheely || wheelx) {

    dy = rely ? rely : -wheely;

    dx = relx ? relx : -wheelx;

    if (dx < 0) {
      dx = -1;
    }
    if (dy < 0) {
      dy = -1;
    }
    if (dx > 0) {
      dx = 1;
    }
    if (dy > 0) {
      dy = 1;
    }
  } else {
    return false;
  }

  std::vector< Widp > worklist;
  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;
    worklist.push_back(child);
  }

  for (auto &child : worklist) {
    if (dx || dy) {
      wid_set_mode(child, WID_MODE_ACTIVE);
    }

    if (! wid_get_moveable_horiz(child)) {
      dx = 0;
    }

    if (! wid_get_moveable_vert(child)) {
      dy = 0;
    }

    wid_move_delta(child, dx, dy);
  }

  return true;
}

void wid_update_mouse(void)
{
  //
  // So if we are now over a new widget that was created on top of the
  // mouse, we activate it.
  //
  int x;
  int y;

  SDL_GetMouseState(&x, &y);

  wid_mouse_motion(x, y, 0, 0, 0, 0);
}

Widp wid_find_under_mouse(void)
{
  if (ascii_is_empty(ascii_mouse_x, ascii_mouse_y)) {
    return nullptr;
  }

  auto w = wid_find_at(ascii_mouse_x, ascii_mouse_y);
  if (w) {
    w = wid_get_top_parent(w);
    // CON("mouse %d,%d over %s %p", ascii_mouse_x, ascii_mouse_y, w->name.c_str(), w);
    if (wid_ignore_events_only(w)) {
      return nullptr;
    }
    return w;
  }
  return nullptr;
}

Widp wid_find_under_mouse_when_scrolling(void)
{
  if (ascii_is_empty(ascii_mouse_x, ascii_mouse_y)) {
    return nullptr;
  }
  auto w = wid_find_at(ascii_mouse_x, ascii_mouse_y);
  if (w) {
    w = wid_get_top_parent(w);
    if (wid_ignore_scroll_events(w)) {
      // CON("ign2 %s.", wid_name(w).c_str());
      return nullptr;
    } else {
      // CON("over2 %s.", wid_name(w).c_str());
      return w;
    }
  }
  return w;
}

static Widp wid_mouse_down_handler_at(Widp w, int x, int y, uint8_t strict)
{
  if (unlikely(! w)) {
    return nullptr;
  }

  if (! w->visible) {
    return nullptr;
  }

  if (w->ignore_for_mouse_down) {
    return nullptr;
  }

  if (wid_ignore_events(w)) {
    return nullptr;
  }

  //
  // Prevent newly created widgets grabbing events too soon; like
  // for example a scancode causes a widget to be created but the
  // same keypress is taken by the widget.
  //
  if (! time_have_x_tenths_passed_since(1, wid_ignore_events_briefly_ts)) {
    return nullptr;
  }

  if (strict) {
    if ((x < w->abs_tl.x) || (y < w->abs_tl.y) || (x > w->abs_br.x) || (y > w->abs_br.y)) {
      return nullptr;
    }
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    if (wid_focus_locked && (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    Widp closer_match = wid_mouse_down_handler_at(child, x, y, true /* strict */);
    if (closer_match) {
      return closer_match;
    }
  }

  if (w->on_mouse_down) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  if (wid_get_moveable(w)) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  //
  // Prevent mouse events that occur in the bounds of one window, leaking
  // into lower levels.
  //
  if (! w->parent) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  return nullptr;
}

static Widp wid_mouse_held_handler_at(Widp w, int x, int y, uint8_t strict)
{
  if (unlikely(! w)) {
    return nullptr;
  }

  if (! w->visible) {
    return nullptr;
  }

  if (wid_ignore_events(w)) {
    return nullptr;
  }

  //
  // Prevent newly created widgets grabbing events too soon; like
  // for example a scancode causes a widget to be created but the
  // same keypress is taken by the widget.
  //
  if (! time_have_x_tenths_passed_since(1, wid_ignore_events_briefly_ts)) {
    return nullptr;
  }

  if (strict) {
    if ((x < w->abs_tl.x) || (y < w->abs_tl.y) || (x > w->abs_br.x) || (y > w->abs_br.y)) {
      return nullptr;
    }
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    if (wid_focus_locked && (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    Widp closer_match = wid_mouse_held_handler_at(child, x, y, true /* strict */);
    if (closer_match) {
      return closer_match;
    }
  }

  if (w->on_mouse_held) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  if (wid_get_moveable(w)) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  //
  // Prevent mouse events that occur in the bounds of one window, leaking
  // into lower levels.
  //
  if (! w->parent) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  return nullptr;
}

static Widp wid_mouse_up_handler_at(Widp w, int x, int y, uint8_t strict)
{
  if (unlikely(! w)) {
    return nullptr;
  }

  if (! w->visible) {
    return nullptr;
  }

  if (wid_ignore_events(w)) {
    return nullptr;
  }

  //
  // Prevent newly created widgets grabbing events too soon; like
  // for example a scancode causes a widget to be created but the
  // same keypress is taken by the widget.
  //
  if (! time_have_x_tenths_passed_since(1, wid_ignore_events_briefly_ts)) {
    return nullptr;
  }

  if (strict) {
    if ((x < w->abs_tl.x) || (y < w->abs_tl.y) || (x > w->abs_br.x) || (y > w->abs_br.y)) {
      return nullptr;
    }
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    if (wid_focus_locked && (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    Widp closer_match = wid_mouse_up_handler_at(child, x, y, true /* strict */);
    if (closer_match) {
      return closer_match;
    }
  }

  if (w->on_mouse_up) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  if (wid_get_moveable(w)) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  //
  // Prevent mouse events that occur in the bounds of one window, leaking
  // into lower levels.
  //
  if (! w->parent) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  return nullptr;
}

static Widp wid_mouse_down_handler(int x, int y)
{
  Widp w {};

  w = wid_mouse_down_handler_at(wid_focus, x, y, true /* strict */);
  if (w) {
    return w;
  }

  w = wid_mouse_down_handler_at(wid_over, x, y, true /* strict */);
  if (w) {
    return w;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    w = wid_mouse_down_handler_at(w, x, y, true /* strict */);
    if (unlikely(! w)) {
      continue;
    }

    return w;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    w = wid_mouse_down_handler_at(w, x, y, false /* strict */);
    if (unlikely(! w)) {
      continue;
    }

    return w;
  }

  return nullptr;
}

static Widp wid_mouse_held_handler(int x, int y)
{
  Widp w {};

  w = wid_mouse_held_handler_at(wid_focus, x, y, true /* strict */);
  if (w) {
    return w;
  }

  w = wid_mouse_held_handler_at(wid_over, x, y, true /* strict */);
  if (w) {
    return w;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    w = wid_mouse_held_handler_at(w, x, y, true /* strict */);
    if (unlikely(! w)) {
      continue;
    }

    return w;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    w = wid_mouse_held_handler_at(w, x, y, false /* strict */);
    if (unlikely(! w)) {
      continue;
    }

    return w;
  }

  return nullptr;
}

static Widp wid_mouse_up_handler(int x, int y)
{
  Widp w {};

  w = wid_mouse_up_handler_at(wid_focus, x, y, true /* strict */);
  if (w) {
    return w;
  }

  w = wid_mouse_up_handler_at(wid_over, x, y, true /* strict */);
  if (w) {
    return w;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    w = wid_mouse_up_handler_at(w, x, y, true /* strict */);
    if (unlikely(! w)) {
      continue;
    }

    return w;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    w = wid_mouse_up_handler_at(w, x, y, false /* strict */);
    if (unlikely(! w)) {
      continue;
    }

    return w;
  }

  return nullptr;
}

static Widp wid_mouse_motion_handler(int x, int y, int relx, int rely, int wheelx, int wheely)
{
  Widp w {};

  w = wid_on_screen_at[ x ][ y ];
  if (w) {
    if (w->hidden) {
      return nullptr;
    }
    return w;
  }

  return nullptr;
}

void wid_mouse_motion(int x, int y, int relx, int rely, int wheelx, int wheely)
{
  int got_one = false;

  //
  // To avoid lag, just grab the current mouse position.
  //
  SDL_GetMouseState(&x, &y);

  //
  // Map to ascii
  //
  pixel_to_ascii(&x, &y);
  if (! ascii_ok(x, y)) {
    return;
  }
  ascii_mouse_x = x;
  ascii_mouse_y = y;

  if (relx || rely) {
    wid_last_mouse_motion = time_ms_cached();
  }

  if (wid_mouse_motion_recursion) {
    return;
  }

  wid_mouse_motion_recursion = 1;

  uint8_t over = false;

  for (auto &iter : wid_top_level) {
    auto w = iter.second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    //
    // Allow wheel events to go everywhere
    //
    if (! wheelx && ! wheely) {
      w = wid_find_at(x, y);
      if (unlikely(! w)) {
        continue;
      }
    }

    if (wid_ignore_events(w)) {
      //
      // This wid is ignoring events, but what about the parent?
      //
      w = w->parent;
      while (w) {
        if (! wid_ignore_events(w)) {
          break;
        }
        w = w->parent;
      }

      if (unlikely(! w)) {
        continue;
      }
    }

    //
    // Over a new wid.
    //

    while (w && ! wid_mouse_over_begin(w, x, y, relx, rely, wheelx, wheely)) {
      w = w->parent;
    }

    uint8_t done = false;

    if (unlikely(! w)) {
      //
      // Allow scrollbar to grab.
      //
    } else {
      //
      // This widget reacted somehow when we went over it. i.e. popup ot
      // function.
      //
      over = true;
    }

    w = wid_mouse_motion_handler(x, y, relx, rely, wheelx, wheely);
    if (w) {
      if (wid_mouse_over_begin(w, x, y, relx, rely, wheelx, wheely)) {
        over = true;
      }

      //
      // If the mouse event is fully processed then do not pass onto
      // scrollbars.
      //
      if (w->on_mouse_motion) {
        if ((w->on_mouse_motion)(w, x, y, relx, rely, wheelx, wheely)) {
          got_one = true;
          break;
        }
      }

      if (wid_over == w) {
        if (! wheelx && ! wheely) {
          break;
        }
      }

      while (w) {
        //
        // If there are scrollbars and the wid did not grab the event
        // then scroll for it.
        //
        if (wheely) {
          if (w->scrollbar_vert && ! wid_get_moveable_no_user_scroll(w->scrollbar_vert)) {

            got_one = true;
            wid_move_delta(w->scrollbar_vert, 0, -wheely);
            done = true;
          }
        }

        if (wheelx) {
          if (w->scrollbar_horiz && ! wid_get_moveable_no_user_scroll(w->scrollbar_horiz)) {

            got_one = true;
            wid_move_delta(w->scrollbar_horiz, -wheelx, 0);
            done = true;
          }
        }

        if (done) {
          break;
        }

        //
        // Maybe the container has a scrollbar. Try it.
        //
        w = w->parent;
      }
    }

    if (done) {
      break;
    }
  }

  if (! over) {
    wid_mouse_over_end();
  }

  //
  // If nothing then pass the event to the console to allow scrolling
  // of the console.
  //
  if (! got_one) {
    if (wid_console_window && wid_console_window->visible) {
      if (wid_console_container && (wheelx || wheely)) {
        Widp w = wid_console_container->scrollbar_vert;
        if (w) {
          w = w->parent;
        }

        if (w && w->on_mouse_motion) {
          if ((w->on_mouse_motion)(w, x, y, relx, rely, wheelx, wheely)) {
            got_one = true;
          }
        }
      }
    }
  }

  wid_mouse_motion_recursion = 0;

  if (! got_one) {
    if (relx || rely || wheelx || wheely) {
      game_mouse_motion(x, y, relx, rely, wheelx, wheely);
    }
  }
}

void wid_mouse_down(uint32_t button, int x, int y)
{
  Widp w {};

  pixel_to_ascii(&x, &y);
  if (! ascii_ok(x, y)) {
    return;
  }
  ascii_mouse_x = x;
  ascii_mouse_y = y;

  w = wid_mouse_down_handler(x, y);
  if (unlikely(! w)) {
    return;
  }

  //
  // Raise on mouse.
  //
  if ((w->on_mouse_down && (w->on_mouse_down)(w, x, y, button)) || wid_get_moveable(w)) {
    sound_play("click");

    wid_set_focus(w);
    wid_set_mode(w, WID_MODE_ACTIVE);
    wid_raise(w);

    //
    // Move on mouse.
    //
    if (wid_get_moveable(w)) {
      wid_mouse_motion_begin(w, x, y);
      return;
    }

    if (game) {
      game->last_mouse_down = time_ms_cached();
    }

    return;
  }

  if (wid_get_moveable(w)) {
    wid_set_mode(w, WID_MODE_ACTIVE);
    wid_raise(w);
    wid_mouse_motion_begin(w, x, y);
    return;
  }

  if (game_mouse_down(x, y, button)) {
    sound_play("click");
    if (game) {
      game->last_mouse_down = time_ms_cached();
    }
  }
}

void wid_mouse_held(uint32_t button, int x, int y)
{
  Widp w {};

  pixel_to_ascii(&x, &y);
  if (! ascii_ok(x, y)) {
    return;
  }
  ascii_mouse_x = x;
  ascii_mouse_y = y;

  w = wid_mouse_held_handler(x, y);
  if (unlikely(! w)) {
    return;
  }

  //
  // Raise on mouse.
  //
  if ((w->on_mouse_held && (w->on_mouse_held)(w, x, y, button)) || wid_get_moveable(w)) {

    wid_set_focus(w);
    wid_set_mode(w, WID_MODE_ACTIVE);
    wid_raise(w);

    //
    // Move on mouse.
    //
    if (wid_get_moveable(w)) {
      wid_mouse_motion_begin(w, x, y);
      return;
    }

    return;
  }

  if (wid_get_moveable(w)) {
    wid_set_mode(w, WID_MODE_ACTIVE);
    wid_raise(w);
    wid_mouse_motion_begin(w, x, y);
    return;
  }
}

void wid_mouse_up(uint32_t button, int x, int y)
{
  Widp w {};

  pixel_to_ascii(&x, &y);
  if (! ascii_ok(x, y)) {
    return;
  }
  ascii_mouse_x = x;
  ascii_mouse_y = y;

  wid_mouse_motion_end();

  w = wid_mouse_up_handler(x, y);
  if (unlikely(! w)) {
    return;
  }

  if ((w->on_mouse_up && (w->on_mouse_up)(w, x, y, button)) || wid_get_moveable(w)) {
    sound_play("click");

    wid_set_mode(w, WID_MODE_ACTIVE);
    wid_raise(w);
    return;
  }

  game_mouse_up(x, y, button);
}

void wid_mouse_hide(int value)
{
  int visible = ! value;

  if (visible != wid_mouse_visible) {
    wid_mouse_visible = visible;
    if (visible) {
      sdl_mouse_warp(saved_mouse_x, saved_mouse_y);
    } else {
      saved_mouse_x = sdl.mouse_x;
      saved_mouse_y = sdl.mouse_y;
    }
  }
}

void wid_mouse_warp(Widp w)
{
  int tlx, tly, brx, bry;

  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int x = (tlx + brx) / 2.0;
  int y = (tly + bry) / 2.0;

  sdl_mouse_warp(x, y);
}

void wid_mouse_move(Widp w)
{
  int tlx, tly, brx, bry;

  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int x = (tlx + brx) / 2.0;
  int y = (tly + bry) / 2.0;

  saved_mouse_x = sdl.mouse_x;
  saved_mouse_y = sdl.mouse_y;

  sdl.mouse_x = x;
  sdl.mouse_y = y;
}
