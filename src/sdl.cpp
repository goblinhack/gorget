//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_command.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_wid_console.hpp"

SDL sdl;

void sdl_fini(Gamep g)
{
  if (! sdl.init_video) {
    return;
  }

  LOG("SDL: Fini");
  TRACE_AND_INDENT();

  sdl_display_fini(g);

  LOG("SDL: Quit");
  SDL_Quit();
}

void sdl_joy_rumble(float strength, uint32_t ms)
{
  TRACE_NO_INDENT();
  if (! sdl.haptic) {
    return;
  }

  SDL_HapticRumblePlay(sdl.haptic, strength, ms);
}

static void sdl_init_rumble(void)
{
  LOG("SDL: Init rumble:");
  TRACE_AND_INDENT();

  if (! sdl.haptic) {
    sdl.haptic = SDL_HapticOpenFromJoystick(sdl.joy);
    if (! sdl.haptic) {
      LOG("- Couldn't initialize SDL rumble: %s", SDL_GetError());
      SDL_ClearError();
      return;
    }
  }

  if (! SDL_HapticRumbleSupported(sdl.haptic)) {
    LOG("- No SDL rumble support: %s", SDL_GetError());
    SDL_ClearError();
    return;
  }

  if (SDL_HapticRumbleInit(sdl.haptic) != 0) {
    LOG("- SDL rumble nit failed: %s", SDL_GetError());
    SDL_ClearError();
    return;
  }

  LOG("- Opened Haptic for joy index %d", sdl.joy_index);
}

static void sdl_init_joystick(void)
{
  LOG("SDL: Init input:");
  TRACE_NO_INDENT();

  SDL_GameController *controller = nullptr;

  LOG("- Init game controleer");
  SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

  LOG("- Init haptic");
  SDL_InitSubSystem(SDL_INIT_HAPTIC);

  LOG("- Init joystick");
  SDL_InitSubSystem(SDL_INIT_JOYSTICK);

  sdl.joy_index = 0;
  for (sdl.joy_index = 0; sdl.joy_index < SDL_NumJoysticks(); ++sdl.joy_index) {

    if (SDL_IsGameController(sdl.joy_index)) {
      controller = SDL_GameControllerOpen(sdl.joy_index);
      if (controller) {
        LOG("- Found gamecontroller");
        break;
      }
      WARN("Could not open gamecontroller %i: %s", sdl.joy_index, SDL_GetError());
      SDL_ClearError();
    }
  }

  if (! controller) {
    LOG("- No found gamecontroller");
    return;
  }

  sdl.joy = SDL_JoystickOpen(sdl.joy_index);
  if (sdl.joy) {
    LOG("- Opened Joystick  : %d", sdl.joy_index);
    LOG("- Name             : %s", SDL_JoystickNameForIndex(0));
    LOG("- Number of Axes   : %d", SDL_JoystickNumAxes(sdl.joy));
    LOG("- Number of Buttons: %d", SDL_JoystickNumButtons(sdl.joy));
    LOG("- Number of Balls  : %d", SDL_JoystickNumBalls(sdl.joy));

    sdl.joy_naxes    = SDL_JoystickNumAxes(sdl.joy);
    sdl.joy_nbuttons = SDL_JoystickNumButtons(sdl.joy);
    sdl.joy_balls    = SDL_JoystickNumBalls(sdl.joy);
  } else {
    WARN("Couldn't open Joystick 0");
  }
}

uint8_t sdl_init(void)
{
  gl_ext_init();

  LOG("SDL: Version: %u.%u", SDL_MAJOR_VERSION, SDL_MINOR_VERSION);
  TRACE_AND_INDENT();

  LOG("SDL: Init audio and video");
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    DIE("SDL_Init failed %s", SDL_GetError());
    return false;
  }

  LOG("SDL: Init video");
  if (SDL_VideoInit(nullptr) != 0) {
    DIE("SDL_VideoInit failed %s", SDL_GetError());
    return false;
  }

  //
  // Unused for now
  //
  if (0) {
    sdl_init_joystick();
    sdl_init_rumble();
  }

  return true;
}

int sdl_get_mouse(void)
{
  TRACE_NO_INDENT();

  if (! wid_mouse_visible) {
    return 0;
  }

  int x = 0, y = 0;
  int button = SDL_GetMouseState(&x, &y);

  if (! x && ! y) {
    return button;
  }

  sdl.mouse_x = x;
  sdl.mouse_y = y;

  return button;
}

void sdl_mouse_center(Gamep g)
{
  TRACE_NO_INDENT();

  int x, y;

  x = game_window_pix_width_get(g) / 2;
  y = game_window_pix_height_get(g) / 2;

  sdl_mouse_warp(g, x, y);
}

void sdl_mouse_warp(Gamep g, int x, int y)
{
  TRACE_NO_INDENT();

  int border = 10;

  if (x <= 0) {
    x = border;
  } else if (x >= game_window_pix_width_get(g) - border) {
    x = game_window_pix_width_get(g) - border;
  }
  if (y <= 0) {
    y = border;
  } else if (y >= game_window_pix_height_get(g) - border) {
    y = game_window_pix_height_get(g) - border;
  }

  SDL_WarpMouseInWindow(sdl.window, x, y);

  sdl.mouse_x = x;
  sdl.mouse_y = y;
}

void sdl_tick(Gamep g)
{
  TRACE_NO_INDENT();
  sdl.left_fire = false;
  sdl.left_fire = true;

  sdl.joy1_right = false;
  sdl.joy1_left  = false;
  sdl.joy1_down  = false;
  sdl.joy1_up    = false;

  sdl.joy2_right = false;
  sdl.joy2_left  = false;
  sdl.joy2_down  = false;
  sdl.joy2_up    = false;

  sdl_get_mouse();

  //
  // Right stick
  //
  if (sdl.joy_axes[ 3 ] > sdl.joy_deadzone) {
    DBG2("SDL: right stick, right");
    sdl.joy1_right = true;

    sdl.joy_buttons[ SDL_JOY_BUTTON_RIGHT ]++;
    wid_joy_button(g, sdl.mouse_x, sdl.mouse_y);
    sdl.joy_buttons[ SDL_JOY_BUTTON_RIGHT ]--;
  }

  if (sdl.joy_axes[ 3 ] < -sdl.joy_deadzone) {
    DBG2("SDL: right stick, left");
    sdl.joy1_left = true;

    sdl.joy_buttons[ SDL_JOY_BUTTON_LEFT ]++;
    wid_joy_button(g, sdl.mouse_x, sdl.mouse_y);
    sdl.joy_buttons[ SDL_JOY_BUTTON_LEFT ]--;
  }

  if (sdl.joy_axes[ 4 ] > sdl.joy_deadzone) {
    DBG2("SDL: right stick, down");
    sdl.joy1_down = true;

    sdl.joy_buttons[ SDL_JOY_BUTTON_DOWN ]++;
    wid_joy_button(g, sdl.mouse_x, sdl.mouse_y);
    sdl.joy_buttons[ SDL_JOY_BUTTON_DOWN ]--;
  }

  if (sdl.joy_axes[ 4 ] < -sdl.joy_deadzone) {
    DBG2("SDL: right stick, up");
    sdl.joy1_up = true;

    sdl.joy_buttons[ SDL_JOY_BUTTON_UP ]++;
    wid_joy_button(g, sdl.mouse_x, sdl.mouse_y);
    sdl.joy_buttons[ SDL_JOY_BUTTON_UP ]--;
  }

  //
  // Left stick
  //
  int mx = 0;
  int my = 0;

  if (sdl.joy_axes[ 0 ] > sdl.joy_deadzone) {
    DBG2("SDL: left stick, right");
    sdl.joy2_right = true;
    mx             = 1;
  }

  if (sdl.joy_axes[ 0 ] < -sdl.joy_deadzone) {
    DBG2("SDL: left stick, left");
    sdl.joy2_left = true;
    mx            = -1;
  }

  if (sdl.joy_axes[ 1 ] > sdl.joy_deadzone) {
    DBG2("SDL: left stick, down");
    sdl.joy2_down = true;
    my            = 1;
  }

  if (sdl.joy_axes[ 1 ] < -sdl.joy_deadzone) {
    DBG2("SDL: left stick, up");
    sdl.joy2_up = true;
    my          = -1;
  }

  static float accel = 1.0;
  static ts_t  ts;

  if (time_have_x_tenths_passed_since(5, ts)) {
    accel = 1.0;
  }

  if ((mx != 0) || (my != 0)) {
    ts = time_ms();

    accel *= (float) UI_SCROLL_JOY_SCALE;

    if (accel > (float) UI_SCROLL_JOY_SCALE_MAX) {
      accel = (float) UI_SCROLL_JOY_SCALE_MAX;
    }

    int x = (int) (sdl.mouse_x + ((float) mx * accel));
    int y = (int) (sdl.mouse_y + ((float) my * accel));

    if (x < 0) {
      x = 0;
    }

    if (y < 0) {
      y = 0;
    }

    if (x > game_window_pix_width_get(g) - 1) {
      x = game_window_pix_width_get(g) - 1;
    }

    if (y > game_window_pix_height_get(g) - 1) {
      y = game_window_pix_height_get(g) - 1;
    }

    if (wid_mouse_visible) {
      sdl_mouse_warp(g, x, y);
    }
  }
}

void sdl_prepare_to_exit(Gamep g)
{
  if (! g_main_loop_running) {
    return;
  }

  LOG("Finishing: SDL main loop is exiting...");
  TRACE_AND_INDENT();

#ifdef ENABLE_UI_ASCII_MOUSE
  SDL_ShowCursor(1);
#endif

  g_main_loop_running = false;
}

//
// User has entered a command, run it
//
uint8_t config_fps_counter_set(Gamep g, class Tokens *tokens, void *context)
{
  TRACE_NO_INDENT();

  char *s = tokens->args[ 2 ];

  if (! s || (*s == '\0')) {
    game_fps_counter_set(g);
    CON("FPS counter enabled (default).");
  } else {
    if (strtol(s, nullptr, 10)) {
      game_fps_counter_set(g);
    } else {
      game_fps_counter_unset(g);
    }
    if (game_fps_counter_get(g)) {
      CON("FPS counter enabled.");
    } else {
      CON("FPS counter disabled.");
    }
  }

  return true;
}

//
// User wants to change the debug level
//
uint8_t config_debug_set(Gamep g, class Tokens *tokens, void *context)
{
  TRACE_NO_INDENT();

  char *s = tokens->args[ 2 ];

  if (! s || (*s == '\0')) {
    g_opt_debug1 = false;
    g_opt_debug2 = false;
  } else {
    g_opt_debug1 = false;
    g_opt_debug2 = false;
    switch (strtol(s, nullptr, 10) ? 1 : 0) {
      case 0 :  break;
      default : g_opt_debug1 = true; break;
    }
  }

  if (g_opt_debug1) {
    CON("Debug: on.");
  } else {
    CON("Debug: off.");
  }

  return true;
}

//
// User has entered a command, run it
//
uint8_t config_gfx_vsync_enable(Gamep g, class Tokens *tokens, void *context)
{
  TRACE_NO_INDENT();

  char *s = tokens->args[ 2 ];

  if (! s || (*s == '\0')) {
    game_gfx_vsync_enable_set(g);
  } else {
    if (strtol(s, nullptr, 10)) {
      game_gfx_vsync_enable_set(g);
    } else {
      game_gfx_vsync_enable_unset(g);
    }
  }

  if (game_gfx_vsync_enable_get(g)) {
    CON("SDL: Vsync enabled.");
    SDL_GL_SetSwapInterval(1);
  } else {
    CON("SDL: Vsync disabled.");
    SDL_GL_SetSwapInterval(0);
  }
  GL_ERROR_CHECK();

  return true;
}

void config_gfx_vsync_update(Gamep g)
{
  TRACE_NO_INDENT();

  if (game_gfx_vsync_enable_get(g)) {
    SDL_GL_SetSwapInterval(1);
  } else {
    SDL_GL_SetSwapInterval(0);
  }
  GL_ERROR_CHECK();
}

//
// User has entered a command, run it
//
uint8_t config_errored(Gamep g, class Tokens *tokens, void *context)
{
  TRACE_NO_INDENT();
  g_errored = false;
  CON("SDL: Errored mode cleared.");
  wid_hide(g, wid_console_window);
  sdl_display_reset(g);
  return true;
}

void sdl_config_update_all(Gamep g)
{
  LOG("SDL: Update config");
  TRACE_AND_INDENT();

  config_game_gfx_update(g);
  config_gfx_vsync_update(g);
  gl_init_2d_mode(g);

  LOG("SDL: Updated config");
}

//
// User has entered a command, run it
//
uint8_t sdl_user_exit(Gamep g, class Tokens *tokens, void *context)
{
  TRACE_NO_INDENT();
  sdl_prepare_to_exit(g);

  return true;
}

void config_game_gfx_update(Gamep g)
{
  LOG("SDL: Update");
  TRACE_AND_INDENT();

  //
  // Display ratio
  //
  game_aspect_ratio_set(g, (float) game_window_pix_width_get(g) / (float) game_window_pix_height_get(g));

  TERM_WIDTH  = game_ui_term_width_get(g);
  TERM_HEIGHT = game_ui_term_height_get(g);

  if (! TERM_WIDTH) {
    ERR("TERM_WIDTH is zero");
    return;
  }
  if (! TERM_HEIGHT) {
    ERR("TERM_HEIGHT is zero");
    return;
  }

  if (TERM_WIDTH > TERM_WIDTH_MAX) {
    LOG("SDL: - %d exceeded console max width: %d", TERM_WIDTH, TERM_WIDTH_MAX);
    TERM_WIDTH = TERM_WIDTH_MAX;
  }

  if (TERM_HEIGHT > TERM_HEIGHT_MAX) {
    LOG("SDL: - %d exceeded console max height: %d", TERM_HEIGHT, TERM_HEIGHT_MAX);
    TERM_HEIGHT = TERM_HEIGHT_MAX;
  }

  int font_width  = UI_FONT_WIDTH;
  int font_height = UI_FONT_HEIGHT;

  TERM_WIDTH  = game_window_pix_width_get(g) / font_width;
  TERM_HEIGHT = game_window_pix_height_get(g) / font_height;

  LOG("SDL: Window:");
  LOG("SDL: - window pixel size       : %dx%d", game_window_pix_width_get(g), game_window_pix_height_get(g));
  LOG("SDL: - aspect ratio            : %f", game_aspect_ratio_get(g));
  LOG("SDL: Initial Terminal");
  LOG("SDL: - term size               : %dx%d", TERM_WIDTH, TERM_HEIGHT);
  LOG("SDL: - ascii gl size           : %ux%u", font_width, font_height);

  //
  // Adjust the font until it is a reasonable size.
  //
  int tries = 100;
  while (tries-- > 0) {
    if ((TERM_WIDTH > TERM_WIDTH_MAX) || (TERM_HEIGHT > TERM_HEIGHT_MAX)) {
      LOG("SDL: Terminal (try %ux%u min %ux%u max %ux%u font %ux%u) > max terminal size, try larger font", TERM_WIDTH,
          TERM_HEIGHT, TERM_WIDTH_MIN, TERM_HEIGHT_MIN, TERM_WIDTH_MAX, TERM_HEIGHT_MAX, font_width, font_height);
      font_width *= 2;
      font_height *= 2;
      TERM_WIDTH  = game_window_pix_width_get(g) / font_width;
      TERM_HEIGHT = game_window_pix_height_get(g) / font_height;
      continue;
    }

    if ((TERM_WIDTH < TERM_WIDTH_MIN) || (TERM_HEIGHT < TERM_HEIGHT_MIN)) {
      LOG("SDL: Terminal (try %ux%u min %ux%u max %ux%u font %ux%u) < min terminal size, try smaller font",
          TERM_WIDTH, TERM_HEIGHT, TERM_WIDTH_MIN, TERM_HEIGHT_MIN, TERM_WIDTH_MAX, TERM_HEIGHT_MAX, font_width,
          font_height);
      font_width /= 2;
      font_height /= 2;
      TERM_WIDTH  = game_window_pix_width_get(g) / font_width;
      TERM_HEIGHT = game_window_pix_height_get(g) / font_height;
      continue;
    }

    if (TERM_WIDTH > TERM_WIDTH_MAX) {
      LOG("SDL: Terminal (try %ux%u min %ux%u max %ux%u font %ux%u) > max width", TERM_WIDTH, TERM_HEIGHT,
          TERM_WIDTH_MIN, TERM_HEIGHT_MIN, TERM_WIDTH_MAX, TERM_HEIGHT_MAX, font_width, font_height);
      TERM_WIDTH = TERM_WIDTH_MAX;
      continue;
    }

    if (TERM_HEIGHT > TERM_HEIGHT_MAX) {
      LOG("SDL: Terminal (try %ux%u min %ux%u max %ux%u font %ux%u) > max height", TERM_WIDTH, TERM_HEIGHT,
          TERM_WIDTH_MIN, TERM_HEIGHT_MIN, TERM_WIDTH_MAX, TERM_HEIGHT_MAX, font_width, font_height);
      TERM_HEIGHT = TERM_HEIGHT_MAX;
      continue;
    }

    if (font_width * TERM_WIDTH < game_window_pix_width_get(g) - font_width - 1) {
      LOG("SDL: Terminal (try %ux%u min %ux%u max %ux%u font %ux%u) can grow horiz", TERM_WIDTH, TERM_HEIGHT,
          TERM_WIDTH_MIN, TERM_HEIGHT_MIN, TERM_WIDTH_MAX, TERM_HEIGHT_MAX, font_width, font_height);
      TERM_WIDTH++;
      continue;
    }

    if (font_height * TERM_HEIGHT < game_window_pix_height_get(g) - font_height - 1) {
      LOG("SDL: Terminal (try %ux%u min %ux%u max %ux%u font %ux%u) can grow vert", TERM_WIDTH, TERM_HEIGHT,
          TERM_WIDTH_MIN, TERM_HEIGHT_MIN, TERM_WIDTH_MAX, TERM_HEIGHT_MAX, font_width, font_height);
      TERM_HEIGHT++;
      continue;
    }

    break;
  }

  //
  // Failed to find a good size.
  //
  if (tries < 0) {
    TERM_WIDTH  = TERM_WIDTH_MIN;
    TERM_HEIGHT = TERM_HEIGHT_MIN;
    font_width  = game_window_pix_width_get(g) / TERM_WIDTH;
    font_height = game_window_pix_height_get(g) / TERM_HEIGHT;
    LOG("SDL: Terminal (try %ux%u min %ux%u max %ux%u font %ux%u) best effort", TERM_WIDTH, TERM_HEIGHT,
        TERM_WIDTH_MIN, TERM_HEIGHT_MIN, TERM_WIDTH_MAX, TERM_HEIGHT_MAX, font_width, font_height);
  }

  //
  // Try again, just in case we had to resort to a best effort font size and can get a few more columns
  // and rows out of the terminal.
  //
  tries = 100;
  while (tries-- > 0) {
    if (TERM_WIDTH >= TERM_WIDTH_MAX) {
      LOG("SDL: Terminal (try %ux%u min %ux%u max %ux%u font %ux%u) > max width", TERM_WIDTH, TERM_HEIGHT,
          TERM_WIDTH_MIN, TERM_HEIGHT_MIN, TERM_WIDTH_MAX, TERM_HEIGHT_MAX, font_width, font_height);
      TERM_WIDTH = TERM_WIDTH_MAX;
      continue;
    }

    if (TERM_HEIGHT >= TERM_HEIGHT_MAX) {
      LOG("SDL: Terminal (try %ux%u min %ux%u max %ux%u font %ux%u) > max height", TERM_WIDTH, TERM_HEIGHT,
          TERM_WIDTH_MIN, TERM_HEIGHT_MIN, TERM_WIDTH_MAX, TERM_HEIGHT_MAX, font_width, font_height);
      TERM_HEIGHT = TERM_HEIGHT_MAX;
      continue;
    }

    if (font_width * TERM_WIDTH < game_window_pix_width_get(g) - font_width - 1) {
      LOG("SDL: Terminal (try %ux%u min %ux%u max %ux%u font %ux%u) can grow horiz", TERM_WIDTH, TERM_HEIGHT,
          TERM_WIDTH_MIN, TERM_HEIGHT_MIN, TERM_WIDTH_MAX, TERM_HEIGHT_MAX, font_width, font_height);
      TERM_WIDTH++;
      continue;
    }

    if (font_height * TERM_HEIGHT < game_window_pix_height_get(g) - font_height - 1) {
      LOG("SDL: Terminal (try %ux%u min %ux%u max %ux%u font %ux%u) can grow vert", TERM_WIDTH, TERM_HEIGHT,
          TERM_WIDTH_MIN, TERM_HEIGHT_MIN, TERM_WIDTH_MAX, TERM_HEIGHT_MAX, font_width, font_height);
      TERM_HEIGHT++;
      continue;
    }
    break;
  }

  LOG("SDL: Final terminal");
  LOG("SDL: - term size               : %dx%d", TERM_WIDTH, TERM_HEIGHT);
  LOG("SDL: - ascii gl size           : %ux%u", font_width, font_height);

  game_ascii_pix_width_set(g, font_width);
  game_ascii_pix_height_set(g, font_height);

  //
  // Work out the size of the game map
  //
  if (! INNER_TILE_WIDTH) {
    ERR("INNER_TILE_WIDTH zero");
    return;
  }

  if (! INNER_TILE_HEIGHT) {
    ERR("INNER_TILE_HEIGHT zero");
    return;
  }

  LOG("SDL: Map:");

  auto w          = game_ascii_pix_width_get(g);
  auto h          = game_ascii_pix_height_get(g);
  int  map_term_w = TERM_WIDTH - (UI_LEFTBAR_WIDTH + UI_RIGHTBAR_WIDTH);
  int  map_term_h = (TERM_HEIGHT - 3) - UI_TOPCON_HEIGHT;

  int visible_map_tl_x = w * UI_LEFTBAR_WIDTH;
  int visible_map_br_x = (TERM_WIDTH - UI_RIGHTBAR_WIDTH) * w;

  int visible_map_tl_y = h * UI_TOPCON_HEIGHT;
  int visible_map_br_y = (TERM_HEIGHT - 3) * h;

  //
  // For screens that are very wide, unstretch the map
  //
  if (map_term_w > map_term_h) {
    int pad = (((map_term_w * w) - (map_term_h * h)) / w) / 2;
    if (pad > 0) {
      LOG("SDL: - map is over wide      : %dx%d (reduce by %d cells either side)", map_term_w, map_term_h, pad);
      visible_map_tl_x += w * pad;
      visible_map_br_x -= w * pad;
    }
  }

  int map_w = visible_map_br_x - visible_map_tl_x;
  int map_h = visible_map_br_y - visible_map_tl_y;

  int max_fbo_w = INNER_TILE_WIDTH * MAP_WIDTH;
  int max_fbo_h = INNER_TILE_HEIGHT * MAP_HEIGHT;

  double map_w_h_ratio = (double) map_w / (double) map_h;
  int    fbo_w         = INNER_TILE_WIDTH * game_tiles_visible_across_get(g);
  int    fbo_h         = (int) ceil(fbo_w / map_w_h_ratio);

  if (fbo_w > max_fbo_w) {
    fbo_w = max_fbo_w;
  }

  if (fbo_h > max_fbo_h) {
    fbo_h = max_fbo_h;
  }

  game_visible_map_pix_set(g, visible_map_tl_x, visible_map_tl_y, visible_map_br_x, visible_map_br_y);

  LOG("SDL: - map location            : %d,%d -> %d,%d", visible_map_tl_x, visible_map_tl_y, visible_map_br_x,
      visible_map_br_y);
  LOG("SDL: - map onscreen sz         : %dx%d", map_w, map_h);
  LOG("SDL: - map w to h ratio        : %g", map_w_h_ratio);
  LOG("SDL: - map pix sz              : %dx%d", fbo_w, fbo_h);
  LOG("SDL: - map max pix sz          : %dx%d", max_fbo_w, max_fbo_h);

  int zoom = game_map_zoom_get(g);
  if (zoom == 0) {
    game_map_zoom_set(g, game_map_zoom_def_get(g));
    zoom = game_map_zoom_get(g);
  }

  if (game_map_zoom_is_full_map_visible(g)) {
    //
    // Zoomed out to see the entire map
    //
    game_map_fbo_width_set(g, max_fbo_w);
    game_map_fbo_height_set(g, max_fbo_h);

    //
    // Used in outlines.
    //
    game_map_single_pix_size_set(g, 1);
  } else {
    //
    // Zoomed in to see a portion of the map
    //
    game_map_fbo_width_set(g, map_w);
    game_map_fbo_height_set(g, map_h);

    //
    // Used in outlines.
    //
    game_map_single_pix_size_set(g, (int) (ceil(map_w / fbo_w)));
  }

  //
  // The map within the game fbo. Use the height of the screen so the width is pixel perfect.
  //
  int tiles_across = (int) ceil(game_map_fbo_width_get(g) / (INNER_TILE_WIDTH * zoom));
  int tiles_down   = (int) ceil(game_map_fbo_height_get(g) / (INNER_TILE_HEIGHT * zoom));

  game_tiles_visible_across_set(g, tiles_across);
  game_tiles_visible_down_set(g, tiles_down);

  LOG("SDL: - game map fbo sz         : %dx%d", game_map_fbo_width_get(g), game_map_fbo_height_get(g));
  LOG("SDL: - map single pixel size   : %d", game_map_single_pix_size_get(g));

  int fbo_tmp_w, fbo_tmp_h;

  LOG("SDL: FBO sizes:");
  fbo_get_size(g, FBO_MAP_BG_MERGED, fbo_tmp_w, fbo_tmp_h);
  LOG("SDL: - FBO_MAP_BG_MERGED size  : %dx%d", fbo_tmp_w, fbo_tmp_h);

  fbo_get_size(g, FBO_MAP_FG_MERGED, fbo_tmp_w, fbo_tmp_h);
  LOG("SDL: - FBO_MAP_FG_MERGED size  : %dx%d", fbo_tmp_w, fbo_tmp_h);

  fbo_get_size(g, FBO_MAP_BG, fbo_tmp_w, fbo_tmp_h);
  LOG("SDL: - FBO_MAP_BG size         : %dx%d", fbo_tmp_w, fbo_tmp_h);

  fbo_get_size(g, FBO_MAP_FG, fbo_tmp_w, fbo_tmp_h);
  LOG("SDL: - FBO_MAP_FG size         : %dx%d", fbo_tmp_w, fbo_tmp_h);

  fbo_get_size(g, FBO_MAP_FG_OVERLAY, fbo_tmp_w, fbo_tmp_h);
  LOG("SDL: - FBO_MAP_FG_OVERLAY size : %dx%d", fbo_tmp_w, fbo_tmp_h);

  fbo_get_size(g, FBO_MAP_LIGHT, fbo_tmp_w, fbo_tmp_h);
  LOG("SDL: - FBO_MAP_LIGHT size      : %dx%d", fbo_tmp_w, fbo_tmp_h);

  fbo_get_size(g, FBO_WID, fbo_tmp_w, fbo_tmp_h);
  LOG("SDL: - FBO_WID size            : %dx%d", fbo_tmp_w, fbo_tmp_h);

  fbo_get_size(g, FBO_FINAL, fbo_tmp_w, fbo_tmp_h);
  LOG("SDL: - FBO_FINAL size          : %dx%d", fbo_tmp_w, fbo_tmp_h);

  LOG("SDL: Map");
  LOG("SDL: - size                    : %dx%d", MAP_WIDTH, MAP_HEIGHT);
  LOG("SDL: - tiles visible           : %dx%d", (int) tiles_across, (int) tiles_down);
  LOG("SDL: - tiles zoom              : %d", game_map_zoom_get(g));
}
