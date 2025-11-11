//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl_event.hpp"
#include "my_sound.hpp"
#include "my_wid_keyboard.hpp"
#include "my_wids.hpp"

/*
 * How keys appear on screen
 */
static const char *keys[ WID_KEYBOARD_DOWN ][ WID_KEYBOARD_ACROSS ] = {
    {
        "!",
        "@",
        "#",
        "$",
        "%",
        "^",
        "*",
        "(",
        ")",
        "_",
        "+",
        "DEL",
    },
    {
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "0",
        "-",
        "CLEAR",
    },
    {
        "a",
        "b",
        "c",
        "d",
        "e",
        "f",
        "g",
        "h",
        "i",
        "j",
        ";",
        "CANCL",
    },
    {
        "k",
        "l",
        "m",
        "n",
        "o",
        "p",
        "q",
        "r",
        "s",
        "t",
        ":",
        "OK",
    },
    {
        "u",
        "v",
        "w",
        "x",
        "y",
        "z",
        "<",
        ">",
        "k",
        ",",
        ".",
        "SPACE",
    },
};

/*
 * The real key behind the scenes
 */
static const char key_char[ WID_KEYBOARD_DOWN ][ WID_KEYBOARD_ACROSS ] = {
    {'!', '@', '#', '$', '%', '^', '*', '(', ')', '_', '+', ''},
    {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', ''},
    {
        'a',
        'b',
        'c',
        'd',
        'e',
        'f',
        'g',
        'h',
        'i',
        'j',
        ';',
        '',
    },
    {
        'k',
        'l',
        'm',
        'n',
        'o',
        'p',
        'q',
        'r',
        's',
        't',
        ':',
        '\n',
    },
    {
        'u',
        'v',
        'w',
        'x',
        'y',
        'z',
        '<',
        '>',
        'k',
        ',',
        '.',
        ' ',
    },
};

int wid_keyboard_visible;

static void wid_keyboard_destroy(Gamep, Widp w);
static void wid_keyboard_set_focus(Gamep, wid_keyboard_ctx *ctx, int focusx, int focusy);
static bool wid_keyboard_text_input_key_event(Gamep, Widp w, const SDL_Keysym *key);

static void wid_keyboard_update_buttons(Gamep g, Widp w)
{
  TRACE_NO_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);

  int width  = 7;
  int height = 5;

  int x, y;

  ctx->b = 0;

  for (x = 0; x < WID_KEYBOARD_ACROSS; x++) {
    for (y = 0; y < WID_KEYBOARD_DOWN; y++) {

      Widp b = ctx->buttons[ y ][ x ];

      spoint tl = {};
      spoint br = {};
      color  c;

      tl.x = x * width;
      tl.y = y * height;

      br.x = tl.x;
      br.y = tl.y;
      br.x += 6;
      br.y += 4;

      if ((x == ctx->focusx) && (y == ctx->focusy)) {
        c      = GREEN;
        ctx->b = b;
        wid_raise(g, b);
      } else {
        wid_lower(g, b);

        c = GRAY70;
      }

      if (ctx->is_new) {
        wid_set_pos(b, tl, br);
      }
    }
  }
  wid_update(g, w);
}

static void wid_keyboard_event(Gamep g, Widp w, int focusx, int focusy, const SDL_Keysym *key_in)
{
  TRACE_NO_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);

  const char *add;
  if ((focusx == -1) && (focusy == -1)) {
    add = 0;
  } else {
    add = keys[ focusy ][ focusx ];
  }

  if (key_in) {
    wid_receive_input(g, ctx->input, key_in);
  } else if (! strcasecmp(add, "OK")) {
    (ctx->selected)(g, ctx->w, wid_get_text(ctx->input));
  } else if (! strcasecmp(add, "CANCL")) {
    (ctx->cancelled)(g, ctx->w, wid_get_text(ctx->input));
  } else if (! strcasecmp(add, "CLEAR")) {
    for (;;) {
      SDL_Keysym key = {};
      key.sym        = SDLK_BACKSPACE;

      std::string tmp = wid_get_text(ctx->input);
      if (tmp.empty()) {
        break;
      }
      wid_receive_input(g, ctx->input, &key);
    }

  } else if (! strcasecmp(add, "DEL")) {
    SDL_Keysym key = {};
    key.sym        = SDLK_BACKSPACE;
    wid_receive_input(g, ctx->input, &key);
  } else if (! strcasecmp(add, "SPACE")) {
    SDL_Keysym key = {};
    key.sym        = ' ';
    wid_receive_input(g, ctx->input, &key);
  } else {
    SDL_Keysym key = {};
    key.sym        = add[ 0 ];
    wid_receive_input(g, ctx->input, &key);
  }

  if (key_in && (focusx == -1) && (focusy == -1)) {
    int x, y;

    for (x = 0; x < WID_KEYBOARD_ACROSS; x++) {
      for (y = 0; y < WID_KEYBOARD_DOWN; y++) {
        char c = key_char[ y ][ x ];
        if (c == key_in->sym) {
          focusx = x;
          focusy = y;
          break;
        }
      }

      if ((focusx != -1) && (focusy != -1)) {
        break;
      }
    }
  }

  if ((focusx != -1) && (focusy != -1)) {
    wid_keyboard_set_focus(g, ctx, focusx, focusy);
  }
}

static bool wid_keyboard_mouse_event(Gamep g, Widp w, int focusx, int focusy)
{
  TRACE_NO_INDENT();
  wid_keyboard_event(g, w, focusx, focusy, 0 /* key */);

  return true;
}

static bool wid_keyboard_button_mouse_event(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  int focus  = wid_get_int_context(w);
  int focusx = (focus & 0xff);
  int focusy = (focus & 0xff00) >> 8;

  return (wid_keyboard_mouse_event(g, w, focusx, focusy));
}

static void wid_keyboard_focus_right(Gamep g, wid_keyboard_ctx *ctx)
{
  TRACE_NO_INDENT();
  ctx->focusx++;
  if (ctx->focusx > WID_KEYBOARD_ACROSS - 1) {
    ctx->focusx = 0;
  }

  wid_keyboard_update_buttons(g, ctx->w);
}

static void wid_keyboard_focus_left(Gamep g, wid_keyboard_ctx *ctx)
{
  TRACE_NO_INDENT();
  ctx->focusx--;
  if (ctx->focusx < 0) {
    ctx->focusx = WID_KEYBOARD_ACROSS - 1;
  }

  wid_keyboard_update_buttons(g, ctx->w);
}

static void wid_keyboard_focus_down(Gamep g, wid_keyboard_ctx *ctx)
{
  TRACE_NO_INDENT();
  ctx->focusy++;
  if (ctx->focusy > WID_KEYBOARD_DOWN - 1) {
    ctx->focusy = 0;
  }

  wid_keyboard_update_buttons(g, ctx->w);
}

static void wid_keyboard_focus_up(Gamep g, wid_keyboard_ctx *ctx)
{
  TRACE_NO_INDENT();
  ctx->focusy--;
  if (ctx->focusy < 0) {
    ctx->focusy = WID_KEYBOARD_DOWN - 1;
  }

  wid_keyboard_update_buttons(g, ctx->w);
}

static void wid_keyboard_last_focus(Gamep g, wid_keyboard_ctx *ctx)
{
  TRACE_NO_INDENT();
  ctx->focusx = WID_KEYBOARD_ACROSS - 1;
  ctx->focusy = WID_KEYBOARD_DOWN - 1;

  wid_keyboard_update_buttons(g, ctx->w);
}

static void wid_keyboard_first_focus(Gamep g, wid_keyboard_ctx *ctx)
{
  TRACE_NO_INDENT();
  ctx->focusx = 0;
  ctx->focusy = 0;

  wid_keyboard_update_buttons(g, ctx->w);
}

static void wid_keyboard_set_focus(Gamep g, wid_keyboard_ctx *ctx, int focusx, int focusy)
{
  TRACE_NO_INDENT();
  ctx->focusx = focusx;
  ctx->focusy = focusy;

  wid_keyboard_update_buttons(g, ctx->w);
}

static bool wid_keyboard_parent_key_down(Gamep g, Widp w, const SDL_Keysym *key)
{
  TRACE_NO_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);

  /*
   * Don't process events too soon. Else the menu might not even have
   * appeared.
   */
  if (time_ms() - ctx->created < 100) {
    return false;
  }

  sound_play(g, "keypress");

  switch (key->sym) {
    case '`' :         return false;

    case SDLK_ESCAPE : (ctx->cancelled)(g, ctx->w, wid_get_text(ctx->input)); return true;

    case SDLK_RETURN :
      {
        (ctx->selected)(g, ctx->w, wid_get_text(ctx->input));
        return true;

        case SDLK_LEFT :  wid_keyboard_focus_left(g, ctx); break;

        case SDLK_RIGHT : wid_keyboard_focus_right(g, ctx); break;

        case SDLK_UP :    wid_keyboard_focus_up(g, ctx); break;

        case SDLK_DOWN :  wid_keyboard_focus_down(g, ctx); break;

        case SDLK_HOME :  wid_keyboard_first_focus(g, ctx); break;

        case SDLK_END :   wid_keyboard_last_focus(g, ctx); break;

        default :         wid_keyboard_event(g, ctx->w, -1, -1, key); return true;
      }
  }

  return true;
}

static bool wid_keyboard_parent_joy_button(Gamep g, Widp w, int x, int y)
{
  TRACE_NO_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);
  int ret = false;

  /*
   * Don't process events too soon. Else the menu might not even have
   * appeared.
   */
  if (time_ms() - ctx->created < 100) {
    return false;
  }

  if (sdl.joy_buttons[ SDL_JOY_BUTTON_A ]) {
    (ctx->selected)(g, ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_B ]) {
    (ctx->cancelled)(g, ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_X ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_Y ]) {
    (ctx->selected)(g, ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_TOP_LEFT ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_TOP_RIGHT ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_LEFT_STICK_DOWN ]) {
    (ctx->selected)(g, ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_RIGHT_STICK_DOWN ]) {
    (ctx->selected)(g, ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_START ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_XBOX ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_BACK ]) {
    (ctx->cancelled)(g, ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_UP ]) {
    wid_keyboard_focus_up(g, ctx);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_DOWN ]) {
    wid_keyboard_focus_down(g, ctx);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_LEFT ]) {
    wid_keyboard_focus_left(g, ctx);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_RIGHT ]) {
    wid_keyboard_focus_right(g, ctx);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_LEFT_FIRE ]) {
    (ctx->selected)(g, ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_RIGHT_FIRE ]) {
    (ctx->selected)(g, ctx->w, wid_get_text(ctx->input));
    ret = true;
  }

  wid_keyboard_update_buttons(g, ctx->w);
  if (ctx->b) {
    wid_mouse_warp(g, ctx->b);
  }

  return ret;
}

static bool wid_keyboard_button_key_event(Gamep g, Widp w, const SDL_Keysym *key)
{
  TRACE_NO_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);

  /*
   * Don't process events too soon. Else the menu might not even have
   * appeared.
   */
  if (time_ms() - ctx->created < 100) {
    return false;
  }

  sound_play(g, "keypress");

  switch (key->sym) {
    case '`' :            return false;

    case SDLK_ESCAPE :    (ctx->cancelled)(g, ctx->w, wid_get_text(ctx->input)); return true;

    case SDLK_RETURN :    (ctx->selected)(g, ctx->w, wid_get_text(ctx->input)); return true;

    case SDLK_BACKSPACE :
    case SDLK_DELETE :
    case SDLK_LEFT :
    case SDLK_RIGHT :
    case SDLK_UP :
    case SDLK_DOWN :
    case SDLK_HOME :
    case SDLK_END :       break;

    default :             wid_keyboard_event(g, w, -1, -1, key); return true;
  }

  return false;
}

static bool wid_keyboard_button_joy_button_event(Gamep g, Widp w, int x, int y)
{
  TRACE_NO_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);
  int ret = false;

  /*
   * Don't process events too soon. Else the menu might not even have
   * appeared.
   */
  if (time_ms() - ctx->created < 100) {
    return false;
  }

  if (sdl.joy_buttons[ SDL_JOY_BUTTON_A ]) {
    ret = wid_keyboard_mouse_event(g, w, ctx->focusx, ctx->focusy);
  }

  if (sdl.joy_buttons[ SDL_JOY_BUTTON_B ]) {
    (ctx->selected)(g, ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_X ]) {
    SDL_Keysym key = {};
    key.sym        = SDLK_BACKSPACE;
    wid_keyboard_text_input_key_event(g, ctx->input, &key);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_Y ]) {
    (ctx->selected)(g, ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_TOP_LEFT ]) {
    SDL_Keysym key = {};
    key.sym        = SDLK_LEFT;
    wid_keyboard_text_input_key_event(g, ctx->input, &key);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_TOP_RIGHT ]) {
    SDL_Keysym key = {};
    key.sym        = SDLK_RIGHT;
    wid_keyboard_text_input_key_event(g, ctx->input, &key);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_LEFT_STICK_DOWN ]) {
    wid_keyboard_mouse_event(g, w, ctx->focusx, ctx->focusy);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_RIGHT_STICK_DOWN ]) {
    wid_keyboard_mouse_event(g, w, ctx->focusx, ctx->focusy);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_START ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_XBOX ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_BACK ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_UP ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_DOWN ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_LEFT ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_RIGHT ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_LEFT_FIRE ]) {
    SDL_Keysym key = {};
    key.sym        = SDLK_BACKSPACE;
    wid_receive_input(g, ctx->input, &key);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_RIGHT_FIRE ]) {
    wid_keyboard_mouse_event(g, w, ctx->focusx, ctx->focusy);
    ret = true;
  }

  wid_keyboard_update_buttons(g, ctx->w);
  if (ctx->b) {
    wid_mouse_warp(g, ctx->b);
  }

  return ret;
}

static bool wid_keyboard_text_input_key_event(Gamep g, Widp w, const SDL_Keysym *key)
{
  TRACE_NO_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);

  /*
   * Don't process events too soon. Else the menu might not even have
   * appeared.
   */
  if (time_ms() - ctx->created < 100) {
    return false;
  }

  sound_play(g, "keypress");

  switch (key->sym) {
    case SDLK_ESCAPE :    (ctx->cancelled)(g, ctx->w, wid_get_text(ctx->input)); return true;

    case SDLK_RETURN :    (ctx->selected)(g, ctx->w, wid_get_text(ctx->input)); return true;

    case SDLK_BACKSPACE :
    case SDLK_DELETE :
    case SDLK_LEFT :
    case SDLK_RIGHT :
    case SDLK_UP :
    case SDLK_DOWN :
    case SDLK_HOME :
    case SDLK_END :       wid_receive_input(g, ctx->input, key); return true;

    default :             wid_keyboard_event(g, w, -1, -1, key); return true;
  }

  return false;
}

static void wid_keyboard_destroy(Gamep g, Widp w)
{
  TRACE_NO_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);

  wid_set_void_context(w, 0);
  oldptr(MTYPE_MISC, ctx);

  wid_keyboard_visible = false;
}

static void wid_keyboard_tick(Gamep g, Widp w)
{
  TRACE_NO_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);

  static int val;
  static int delta = 1;
  static int step  = 2;

  val += delta * step;

  if (val > 255) {
    val   = 255;
    delta = -1;
  }

  if (val < 200) {
    val   = 200;
    delta = 1;
  }

  int x, y;

  for (x = 0; x < WID_KEYBOARD_ACROSS; x++) {
    for (y = 0; y < WID_KEYBOARD_DOWN; y++) {

      if ((x != ctx->focusx) || (y != ctx->focusy)) {
        continue;
      }

      Widp b = ctx->buttons[ y ][ x ];

      color c;
      c   = GREEN;
      c.g = val;

      /*
       * Make sure the other widgets look plain in all modes.
       */
      int mode;
      for (mode = WID_MODE_NORMAL; mode < WID_MODE_LAST; mode++) {
        wid_set_mode(g, b, (wid_mode) mode);
        wid_set_color(b, WID_COLOR_TEXT_FG, c);
      }

      wid_set_mode(g, w, (wid_mode) WID_MODE_NORMAL);
    }
  }
}

Widp wid_keyboard(Gamep g, const std::string &text, const std::string &title, wid_keyboard_event_t selected,
                  wid_keyboard_event_t cancelled, size_t max_len)
{
  TRACE_NO_INDENT();
  wid_keyboard_visible = true;

  /*
   * Create a context to hold button info so we can update it when the focus
   * changes
   */
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) myzalloc(SIZEOF(*ctx), "wid keyboard");
  ctx->focusx           = -1;
  ctx->focusy           = -1;
  ctx->cancelled        = cancelled;
  ctx->selected         = selected;

  Widp window  = wid_new_square_window(g, "wid keyboard");
  ctx->w       = window;
  ctx->is_new  = true;
  ctx->max_len = max_len;

  /*
   * Main window
   */
  const auto width  = WID_KEYBOARD_ACROSS * 7 + 1;
  const auto height = WID_KEYBOARD_DOWN * 5 + 8;

  int left_half  = width / 2;
  int right_half = width - left_half;
  int top_half   = height / 2;
  int bot_half   = height - top_half;

  {
    spoint tl(TERM_WIDTH / 2 - left_half, TERM_HEIGHT / 2 - top_half);
    spoint br(TERM_WIDTH / 2 + right_half, TERM_HEIGHT / 2 + bot_half);

    wid_set_pos(window, tl, br);
    wid_set_style(window, UI_WID_STYLE_NORMAL);
    wid_set_on_key_down(g, window, wid_keyboard_parent_key_down);
    wid_set_on_joy_button(g, window, wid_keyboard_parent_joy_button);
    wid_set_on_destroy(g, window, wid_keyboard_destroy);
    wid_set_void_context(window, ctx);
  }

  /*
   * Create the title
   */
  {
    Widp w = wid_new_square_button(g, window, "wid keyboard title");

    spoint tl = {5, 1};
    spoint br = {width - 5, 1};

    wid_set_pos(w, tl, br);
    wid_set_text(w, title);
    wid_set_shape_none(w);
    wid_set_color(w, WID_COLOR_TEXT_FG, YELLOW);
  }

  /*
   * Create the text input container
   */
  {
    Widp w = wid_new_square_button(g, window, "wid keyboard input");

    ctx->input = w;

    spoint tl = {10, 3};
    spoint br = {width - 10, 5};

    wid_set_pos(w, tl, br);
    wid_set_text(w, text);
    wid_set_show_cursor(w, true);
    wid_set_on_key_down(g, w, wid_keyboard_text_input_key_event);
    wid_set_void_context(w, ctx);
    wid_set_style(w, UI_WID_STYLE_RED);

    if (max_len) {
      wid_set_text_max_len(w, max_len);
    }

    wid_set_color(w, WID_COLOR_BG, GRAY20);
    wid_set_color(w, WID_COLOR_TEXT_FG, GREEN);

    wid_set_mode(g, w, WID_MODE_OVER);

    wid_set_color(w, WID_COLOR_BG, GRAY20);
    wid_set_color(w, WID_COLOR_TEXT_FG, GREEN);

    wid_set_mode(g, w, WID_MODE_NORMAL);
  }

  /*
   * Create the button container
   */
  {
    Widp button_container = wid_new_square_button(g, window, "wid keyboard buttons");
    wid_set_shape_none(button_container);
    wid_set_on_tick(g, button_container, wid_keyboard_tick);

    spoint tl = {1, 7};
    spoint br = {width - 1, height - 2};

    wid_set_pos(button_container, tl, br);
    wid_set_void_context(button_container, ctx);

    /*
     * Create the buttons
     */
    int x, y;

    for (x = 0; x < WID_KEYBOARD_ACROSS; x++) {
      for (y = 0; y < WID_KEYBOARD_DOWN; y++) {
        Widp b;

        if (! strcasecmp(keys[ y ][ x ], "CLEAR")) {
          b = wid_new_cancel_button(g, button_container, "wid keyboard button");
        } else if (! strcasecmp(keys[ y ][ x ], "CANCL")) {
          b = wid_new_cancel_button(g, button_container, "wid keyboard button");
        } else if (! strcasecmp(keys[ y ][ x ], "OK")) {
          b = wid_new_green_button(g, button_container, "wid keyboard button");
        } else {
          b = wid_new_menu_button(g, button_container, "wid keyboard button");
        }
        ctx->buttons[ y ][ x ] = b;

        wid_set_text(b, keys[ y ][ x ]);

        wid_set_on_key_down(g, b, wid_keyboard_button_key_event);
        wid_set_on_joy_button(g, b, wid_keyboard_button_joy_button_event);
        wid_set_on_mouse_down(g, b, wid_keyboard_button_mouse_event);

        wid_set_void_context(b, ctx);
        int focus = (y << 8) | x;
        wid_set_int_context(b, focus);
      }
    }
  }

  wid_keyboard_update_buttons(g, window);
  wid_set_do_not_lower(window, 1);
  wid_update(g, window);
  wid_raise(g, window);
  wid_set_focus(g, window);

  ctx->created = time_ms();

  return window;
}
