//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_ui.hpp"
#include "my_wid_console.hpp"

static struct SDL_Keysym last_key_pressed;

int sdl_filter_events(void *userdata, SDL_Event *event)
{
  TRACE_NO_INDENT();

  switch (event->type) {
    // This is important!  Queue it if we want to quit. */
    case SDL_QUIT : return 1;

    // Mouse and keyboard events go to threads */
    case SDL_MOUSEMOTION :
    case SDL_MOUSEBUTTONDOWN :
    case SDL_MOUSEBUTTONUP :
    case SDL_MOUSEWHEEL :
    case SDL_KEYDOWN :
    case SDL_KEYUP :
    case SDL_CONTROLLERDEVICEADDED :
    case SDL_CONTROLLERBUTTONDOWN :
    case SDL_CONTROLLERBUTTONUP :
    case SDL_CONTROLLERAXISMOTION :
    case SDL_JOYAXISMOTION : // Joystick axis motion
    case SDL_JOYBALLMOTION : // Joystick trackball motion
    case SDL_JOYHATMOTION :  // Joystick hat position change
    case SDL_JOYBUTTONDOWN : // Joystick button pressed
    case SDL_JOYBUTTONUP :   // Joystick button released
      return 1;

    // Drop all other events
    default : return 0;
  }
}

static void __attribute__((noinline)) sdl_event_keydown_repeat(Gamep g, SDL_Keysym *key, SDL_Event *event)
{
  TRACE_NO_INDENT();

  //
  // Pressing the same key
  //
  if (sdl.key_repeat_count > 0) {
    //
    // Fast repeat
    //
    if (! time_have_x_hundredths_passed_since(SDL_KEY_REPEAT_HUNDREDTHS_NEXT, sdl.key_repeat_this_key)) {
      return;
    }
  } else {
    //
    // First press
    //
    if (! time_have_x_hundredths_passed_since(SDL_KEY_REPEAT_HUNDREDTHS_FIRST, sdl.key_repeat_this_key)) {
      return;
    }
    sdl.key_repeat_count++;
  }

  sdl.key_repeat_this_key = time_ms();
}

static bool __attribute__((noinline)) sdl_event_keydown_same_key(Gamep g, SDL_Keysym *key)
{
  TRACE_NO_INDENT();

  //
  // SDL2 has no auto repeat.
  //
  // Do not use memcmp; SDL_Keysym has an unused field and this will trigger valgrind.
  //
  if (key->scancode != last_key_pressed.scancode)
    return false;

  if (key->sym != last_key_pressed.sym)
    return false;

  if (key->mod != last_key_pressed.mod)
    return false;

  return true;
}

static void __attribute__((noinline)) sdl_event_keydown_handler(Gamep g, SDL_Keysym *key, SDL_Event *event)
{
  TRACE_NO_INDENT();

  last_key_pressed.scancode = key->scancode;
  last_key_pressed.sym      = key->sym;
  last_key_pressed.mod      = key->mod;

  wid_key_down(g, key, sdl.mouse_x, sdl.mouse_y);

  sdl.shift_held = (key->mod & KMOD_SHIFT) ? 1 : 0;
}

static void __attribute__((noinline)) sdl_event_keydown(Gamep g, SDL_Keysym *key, SDL_Event *event)
{
  TRACE_NO_INDENT();

  sdl.event_count++;

  LOG("SDL: Keyboard: Key pressed keycode 0x%08" PRIx32 " = %s %d", event->key.keysym.sym,
      to_string(event->key.keysym).c_str(), key->mod);

  //
  // SDL2 has no auto repeat.
  //
  if (sdl_event_keydown_same_key(g, key)) {
    sdl_event_keydown_repeat(g, key, event);
  } else {
    //
    // Pressing a different key
    //
    sdl.key_repeat_count = 0;
  }

  sdl_event_keydown_handler(g, key, event);
}

static void __attribute__((noinline)) sdl_event_keyup(Gamep g, SDL_Keysym *key, SDL_Event *event)
{
  TRACE_NO_INDENT();

  sdl.event_count++;
  if (g_grab_next_key) {
    LOG("SDL: Keyboard: Grabbed 0x%08" PRIx32 " = %s / %s", event->key.keysym.sym,
        to_string(event->key.keysym).c_str(), SDL_GetScancodeName(event->key.keysym.scancode));

    g_grab_next_key = false;
    sdl.grabbed_key = sdlk_normalize(event->key.keysym);
    if (sdl.on_sdl_key_grab) {
      sound_play(g, "keypress");
      (*sdl.on_sdl_key_grab)(g, sdl.grabbed_key);
    }
    return;
  }

  sdl.key_repeat_count    = 0;
  sdl.key_repeat_this_key = 0;

  memset(&last_key_pressed, 0, SIZEOF(last_key_pressed));

  LOG("SDL: Keyboard: Key released keycode 0x%08" PRIx32 " = %s", event->key.keysym.sym,
      to_string(event->key.keysym).c_str());

  key = &event->key.keysym;

  wid_key_up(g, key, sdl.mouse_x, sdl.mouse_y);

  sdl.shift_held = (key->mod & KMOD_SHIFT) ? 1 : 0;
}

static void __attribute__((noinline)) sdl_event_mousemotion(Gamep g, SDL_Keysym *key, SDL_Event *event,
                                                            bool &processed_mouse_motion_event)
{
  TRACE_NO_INDENT();

  sdl.event_count++;
  sdl.mouse_down = sdl_get_mouse();
  int        mx;
  int        my;
  static int last_mx;
  static int last_my;

  //
  // Catch up with the latest mouse position; and dampen identical events.
  //
  SDL_GetMouseState(&mx, &my);
  if ((mx == last_mx) && (my == last_my)) {
    return;
  }

  last_mx = mx;
  last_my = my;

  DBG2("SDL: Mouse: Moved to @%d,%d (rel %d,%d) state %d (actually at %d,%d)", event->motion.x, event->motion.y,
       event->motion.xrel, event->motion.yrel, sdl.mouse_down, mx, my);

  wid_mouse_visible = 1;
  sdl.mouse_tick++;
  if (! processed_mouse_motion_event) {
    wid_mouse_motion(g, mx, my, event->motion.xrel, event->motion.yrel, 0, 0);
    processed_mouse_motion_event = true;
  }
}

static void __attribute__((noinline)) sdl_event_mousedown(Gamep g, SDL_Keysym *key, SDL_Event *event)
{
  TRACE_NO_INDENT();

  sdl.event_count++;
  sdl.mouse_down                = sdl_get_mouse();
  sdl.last_mouse_held_down_when = time_ms();
  sdl.held_mouse_x              = sdl.mouse_x;
  sdl.held_mouse_y              = sdl.mouse_y;

  LOG("SDL: Mouse DOWN: button %d pressed at %d,%d state %X", event->button.button, event->button.x, event->button.y,
      sdl.mouse_down);

  auto now             = time_ms();
  wid_mouse_visible    = 1;
  wid_mouse_two_clicks = (now - sdl.mouse_down_when < UI_MOUSE_DOUBLE_CLICK);

  wid_mouse_down(g, event->button.button, sdl.mouse_x, sdl.mouse_y);
  sdl.mouse_down_when = now;
}

static void __attribute__((noinline)) sdl_event_mouseup(Gamep g, SDL_Keysym *key, SDL_Event *event)
{
  TRACE_NO_INDENT();

  sdl.event_count++;
  sdl.mouse_down                = sdl_get_mouse();
  sdl.last_mouse_held_down_when = 0;
  sdl.held_mouse_x              = 0;
  sdl.held_mouse_y              = 0;

  LOG("SDL: Mouse UP: button %d released at %d,%d state %d", event->button.button, event->button.x, event->button.y,
      sdl.mouse_down);

  wid_mouse_up(g, event->button.button, sdl.mouse_x, sdl.mouse_y);
}

void sdl_event(Gamep g, SDL_Event *event, bool &processed_mouse_motion_event)
{
  TRACE_NO_INDENT();

  SDL_Keysym *key = &event->key.keysym;

  wid_mouse_two_clicks = false;

  switch (event->type) {
    case SDL_KEYDOWN :
      LOG("SDL: Event key down");
      sdl_event_keydown(g, key, event);
      break;
    case SDL_KEYUP :
      LOG("SDL: Event key up");
      sdl_event_keyup(g, key, event);
      break;
    case SDL_MOUSEMOTION : sdl_event_mousemotion(g, key, event, processed_mouse_motion_event); break;
    case SDL_MOUSEBUTTONDOWN :
      LOG("SDL: Event mouse button down");
      sdl_event_mousedown(g, key, event);
      break;
    case SDL_MOUSEBUTTONUP :
      LOG("SDL: Event mouse button up");
      sdl_event_mouseup(g, key, event);
      break;
    case SDL_TEXTINPUT :
      {
        sdl.event_count++;
        LOG("SDL: Keyboard: Text input \"%s\" in window %d", event->text.text, event->text.windowID);
        break;
      }
    case SDL_MOUSEWHEEL :
      {
        sdl.event_count++;
        LOG("SDL: Mouse: Wheel scrolled %d in x and %d in y in window %d", event->wheel.x, event->wheel.y,
            event->wheel.windowID);

        sdl_get_mouse();

        static double accel = 1.0;

        {
          static ts_t ts;

          if (time_have_x_tenths_passed_since(10, ts)) {
            accel = 1.0;
          } else {
            if (wid_over) {
              //
              // Slower wheel acceleration when over a wid
              //
              accel *= UI_WID_MOUSE_WHEEL_SCALE;

              if (accel > UI_WID_MOUSE_WHEEL_SCALE_MAX) {
                accel = UI_WID_MOUSE_WHEEL_SCALE_MAX;
              }
            } else {
              //
              // Faster wheel acceleration when over the map
              //
              accel *= UI_GAME_MOUSE_WHEEL_SCALE;

              if (accel > UI_GAME_MOUSE_WHEEL_SCALE_MAX) {
                accel = UI_GAME_MOUSE_WHEEL_SCALE_MAX;
              }
            }
          }

          ts = time_ms();
        }

        sdl.wheel_x = event->wheel.x;
        sdl.wheel_y = event->wheel.y;

        //
        // Handle "natural" scrolling direction.
        //
        if (! game_mouse_wheel_lr_negated_get(g)) {
          sdl.wheel_x = -sdl.wheel_x;
        }

        if (game_mouse_wheel_ud_negated_get(g)) {
          sdl.wheel_y = -sdl.wheel_y;
        }

        sdl.wheel_x = (int) ((float) sdl.wheel_x * accel);
        sdl.wheel_y = (int) ((float) sdl.wheel_y * accel);

        wid_mouse_visible = 1;
        sdl.mouse_tick++;
        if (! processed_mouse_motion_event) {
          wid_mouse_motion(g, sdl.mouse_x, sdl.mouse_y, 0, 0, -sdl.wheel_x, sdl.wheel_y);
          processed_mouse_motion_event = true;
        }
        break;
      }
    case SDL_JOYAXISMOTION :
      {
        sdl.event_count++;
        LOG("SDL: Joystick %d: Axis %d moved by %d", event->jaxis.which, event->jaxis.axis, event->jaxis.value);

        int axis  = event->jaxis.axis;
        int value = event->jaxis.value;

        if (! sdl.joy_axes) {
          sdl.joy_axes = (int *) myzalloc(SIZEOF(int) * sdl.joy_naxes, "joy axes");
        }

        sdl.joy_axes[ axis ] = value;

        sdl.left_fire  = false;
        sdl.right_fire = false;

        if (sdl.joy_axes[ 2 ] > sdl.joy_deadzone) {
          LOG("SDL: left fire");
          sdl.left_fire                               = true;
          sdl.joy_buttons[ SDL_JOY_BUTTON_LEFT_FIRE ] = (uint8_t) 1;
        } else {
          sdl.joy_buttons[ SDL_JOY_BUTTON_LEFT_FIRE ] = (uint8_t) 0;
        }

        if (sdl.joy_axes[ 5 ] > sdl.joy_deadzone) {
          LOG("SDL: right fire");
          sdl.right_fire                               = true;
          sdl.joy_buttons[ SDL_JOY_BUTTON_RIGHT_FIRE ] = (uint8_t) 1;
        } else {
          sdl.joy_buttons[ SDL_JOY_BUTTON_RIGHT_FIRE ] = (uint8_t) 0;
        }

        if (sdl.right_fire || sdl.left_fire) {
          sdl_get_mouse();
          wid_joy_button(g, sdl.mouse_x, sdl.mouse_y);
        }

        break;
      }
    case SDL_JOYBALLMOTION :
      {
        sdl.event_count++;
        LOG("SDL: Joystick %d: Ball %d moved by %d,%d", event->jball.which, event->jball.ball, event->jball.xrel,
            event->jball.yrel);
        break;
      }
    case SDL_JOYHATMOTION :
      {
        sdl.event_count++;
        LOG("SDL: Joystick %d: Hat %d moved to ", event->jhat.which, event->jhat.hat);

        switch (event->jhat.value) {
          case SDL_HAT_CENTERED : break;
          case SDL_HAT_UP :
            {
              LOG("SDL: UP");
              sdl.joy2_up = true;
              break;
            }
          case SDL_HAT_RIGHTUP :
            {
              LOG("SDL: RIGHTUP");
              sdl.joy2_right = true;
              sdl.joy2_up    = true;
              break;
            }
          case SDL_HAT_RIGHT :
            {
              LOG("SDL: RIGHT");
              sdl.joy2_right = true;
              break;
            }
          case SDL_HAT_RIGHTDOWN :
            {
              LOG("SDL: RIGHTDOWN");
              sdl.joy2_right = true;
              sdl.joy2_down  = true;
              break;
            }
          case SDL_HAT_DOWN :
            {
              LOG("SDL: DOWN");
              sdl.joy2_down = true;
              break;
            }
          case SDL_HAT_LEFTDOWN :
            {
              LOG("SDL: LEFTDOWN");
              sdl.joy2_left = true;
              sdl.joy2_down = true;
              break;
            }
          case SDL_HAT_LEFT :
            {
              LOG("SDL: LEFT");
              sdl.joy2_left = true;
              break;
            }
          case SDL_HAT_LEFTUP :
            {
              sdl.joy2_left = true;
              sdl.joy2_up   = true;
              LOG("SDL: LEFTUP");
              break;
            }
          default : LOG("SDL: UNKNOWN"); break;
        }
        break;
      }
    case SDL_JOYBUTTONDOWN :
      {
        sdl.event_count++;
        LOG("SDL: Joystick %d: Button %d pressed", event->jbutton.which, event->jbutton.button);
        sdl.joy_buttons[ event->jbutton.button ] = (uint8_t) 1;
        sdl_get_mouse();
        wid_joy_button(g, sdl.mouse_x, sdl.mouse_y);
        break;
      }
    case SDL_JOYBUTTONUP :
      {
        sdl.event_count++;
        LOG("SDL: Joystick %d: Button %d released", event->jbutton.which, event->jbutton.button);
        sdl.joy_buttons[ event->jbutton.button ] = (uint8_t) 0;
        break;
      }
    case SDL_CLIPBOARDUPDATE :
      {
        LOG("SDL: Clipboard updated");
        break;
      }
    case SDL_QUIT :
      {
#ifdef ENABLE_UI_ASCII_MOUSE
        SDL_ShowCursor(1);
#endif
        DIE_CLEAN("Quit requested");
        break;
      }
    case SDL_USEREVENT :
      {
        LOG("SDL: User event %d", event->user.code);
        break;
      }
    default :
      {
        LOG("SDL: Unknown event %d", event->type);
        break;
      }
  }
}

void sdl_key_repeat_events(Gamep g)
{
  TRACE_NO_INDENT();

  if (game_state(g) != STATE_PLAYING) {
    return;
  }

  const uint8_t *state = SDL_GetKeyboardState(nullptr);

  static bool up_held_prev;
  static bool down_held_prev;
  static bool left_held_prev;
  static bool right_held_prev;

  bool up_held    = state[ sdlk_to_scancode(game_key_move_up_get(g)) ];
  bool down_held  = state[ sdlk_to_scancode(game_key_move_down_get(g)) ];
  bool left_held  = state[ sdlk_to_scancode(game_key_move_left_get(g)) ];
  bool right_held = state[ sdlk_to_scancode(game_key_move_right_get(g)) ];

  //
  // Keypad stuff is hardcoded.
  //
  if (state[ SDL_SCANCODE_KP_1 ]) {
    // 7 8 9
    // 4   6
    // 1 2 3
    left_held = true;
    down_held = true;
  }
  if (state[ SDL_SCANCODE_KP_2 ]) {
    // 7 8 9
    // 4   6
    // 1 2 3
    down_held = true;
  }
  if (state[ SDL_SCANCODE_KP_3 ]) {
    // 7 8 9
    // 4   6
    // 1 2 3
    right_held = true;
    down_held  = true;
  }
  if (state[ SDL_SCANCODE_KP_4 ]) {
    // 7 8 9
    // 4   6
    // 1 2 3
    left_held = true;
  }
  if (state[ SDL_SCANCODE_KP_6 ]) {
    // 7 8 9
    // 4   6
    // 1 2 3
    right_held = true;
  }
  if (state[ SDL_SCANCODE_KP_7 ]) {
    // 7 8 9
    // 4   6
    // 1 2 3
    left_held = true;
    up_held   = true;
  }
  if (state[ SDL_SCANCODE_KP_8 ]) {
    // 7 8 9
    // 4   6
    // 1 2 3
    up_held = true;
  }
  if (state[ SDL_SCANCODE_KP_9 ]) {
    // 7 8 9
    // 4   6
    // 1 2 3
    right_held = true;
    up_held    = true;
  }

  static int up_pressed    = 0;
  static int down_pressed  = 0;
  static int left_pressed  = 0;
  static int right_pressed = 0;

  if (up_held && (up_held != up_held_prev)) {
    up_pressed++;
  }
  if (down_held && (down_held != down_held_prev)) {
    down_pressed++;
  }
  if (left_held && (left_held != left_held_prev)) {
    left_pressed++;
  }
  if (right_held && (right_held != right_held_prev)) {
    right_pressed++;
  }

  up_held_prev    = up_held;
  down_held_prev  = down_held;
  right_held_prev = right_held;
  left_held_prev  = left_held;

  bool up    = up_pressed || up_held;
  bool down  = down_pressed || down_held;
  bool left  = left_pressed || left_held;
  bool right = right_pressed || right_held;

  static ts_t last_movement_keypress = 0;

  if (! last_movement_keypress) {
    last_movement_keypress = time_ms();
  }

  if (time_have_x_hundredths_passed_since(SDL_KEY_REPEAT_PLAYER, last_movement_keypress)) {
    if (player_move_request(g, up, down, left, right)) {
      last_movement_keypress = time_ms();

      if (up_pressed > 0) {
        up_pressed--;
      }
      if (down_pressed > 0) {
        down_pressed--;
      }
      if (left_pressed > 0) {
        left_pressed--;
      }
      if (right_pressed > 0) {
        right_pressed--;
      }
    }
  }
}
