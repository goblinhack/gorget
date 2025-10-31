//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
// REMOVED #include "my_tile.hpp"
#include "my_wid_console.hpp"

void sdl_display(Gamep g)
{
  TRACE_NO_INDENT();

  if (! sdl.window) {
    return;
  }

  blit_fbo_bind(FBO_FINAL);
  glClear(GL_COLOR_BUFFER_BIT);
  glcolor(WHITE);

  //
  // Blit the game map.
  //
  level_blit(g);

  //
  // Blit the widgets
  //
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  blit_fbo(g, FBO_WID);
  blit_fbo_unbind();
  glBlendFunc(GL_ONE, GL_ZERO);
  blit_fbo(g, FBO_FINAL);

  //
  // Screenshot?
  //
  if (unlikely(g_do_screenshot)) {
    g_do_screenshot = 0;
    sdl_screenshot_do(g);
  }

  SDL_Delay(game_sdl_delay_get(g));

  //
  // Flip
  //
  SDL_GL_SwapWindow(sdl.window);
}

void sdl_flush_display(Gamep g, bool force)
{
  TRACE_NO_INDENT();

  if (! sdl.window) {
    return;
  }

  if (! force) {
    IF_NODEBUG { return; }
    if (g_opt_no_slow_log_flush) {
      return;
    }
  }

  wid_display_all(g);
  gl_enter_2d_mode(g, game_window_pix_width_get(g), game_window_pix_height_get(g));
  sdl_display(g);
}

void sdl_display_reset(Gamep g)
{
  TRACE_NO_INDENT();

  if (! sdl.window) {
    return;
  }

  CON("SDL: Video resetting");

  auto old_console = wid_console_serialize();

  wid_console_fini(g);
  config_game_gfx_update(g);

  wid_console_init(g);
  wid_hide(g, wid_console_window);
  sdl_flush_display(g);

  wid_console_deserialize(old_console);

  //
  // DO NOT CALL THIS HERE. We could be inside a widget mouse up handler.
  //
  // wid_gc_all();
  //
  wid_display_all(g);

  CON("SDL: Video reset");
  sdl_flush_display(g);
}

static inline void sdl_list_video_size(void)
{
  TRACE_NO_INDENT();
  int i;

  if (! g_opt_debug1) {
    return;
  }

  for (i = 0; i < SDL_GetNumDisplayModes(0); ++i) {
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, i, &mode);
    DBG("+ SDL video            : %dx%d available, ratio %f", mode.w, mode.h, ((float) mode.w) / ((float) mode.h));
  }
}

uint8_t sdl_display_init(Gamep g)
{
  int video_width;
  int video_height;

  sdl.init_video = 1;

  sdl_list_video_size();

  //
  // If we have a saved setting, use that.
  //
  if (game_config_pix_width_get(g) && game_config_pix_height_get(g)) {
    video_width  = game_config_pix_width_get(g);
    video_height = game_config_pix_height_get(g);
    LOG("SDL: Used saved resolution %ux%u", video_width, video_height);
  } else {
    //
    // Else guess.
    //
    SDL_DisplayMode mode;
    memset(&mode, 0, SIZEOF(mode));

    LOG("SDL: Init display");
    if (SDL_GetCurrentDisplayMode(0, &mode) < 0) {
      DIE("SDL_GetCurrentDisplayMode couldn't set windowed display: '%s'", SDL_GetError());
      return false;
    }

    game_config_pix_width_set(g, mode.w);
    game_config_pix_height_set(g, mode.h);

    video_width  = game_config_pix_width_get(g);
    video_height = game_config_pix_height_get(g);
    LOG("SDL: Used current resolution %ux%u", video_width, video_height);
  }

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

  uint32_t video_flags;

  LOG("SDL: Set SDL_WINDOW_OPENGL");
  video_flags = SDL_WINDOW_OPENGL;

  //
  // SDL_WINDOW_ALWAYS_ON_TOP is meant to help with focus
  //
  // but does it cause issues with debugging, where the debugger window is always behind?
  //
  // video_flags |= SDL_WINDOW_ALWAYS_ON_TOP;

  if (game_gfx_borderless_get(g)) {
    LOG("SDL: Set SDL_WINDOW_BORDERLESS");
    video_flags |= SDL_WINDOW_BORDERLESS;
  }

  if (game_gfx_fullscreen_get(g)) {
    LOG("SDL: Set SDL_WINDOW_FULLSCREEN");
    video_flags |= SDL_WINDOW_FULLSCREEN;
  }

  if (game_gfx_fullscreen_desktop_get(g)) {
    LOG("SDL: Set SDL_WINDOW_FULLSCREEN_DESKTOP");
    video_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
  }

  if (g_opt_do_level_select_gen || g_opt_do_room_gen || g_opt_do_level_gen) {
    video_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_ALWAYS_ON_TOP;
  }

  LOG("SDL: Create window size %ux%u", video_width, video_height);
  sdl.window = SDL_CreateWindow("gorget", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, video_width, video_height,
                                video_flags);
  if (! sdl.window) {
    ERR("SDL_CreateWindow couldn't set windowed display %ux%u: '%s'", video_width, video_height, SDL_GetError());
    game_config_reset(g);
    game_save_config(g);
    return false;
  }

  int w, h;
  SDL_GetWindowSize(sdl.window, &w, &h);
  LOG("SDL: Created window size %ux%u", w, h);

  game_config_pix_width_set(g, w);
  game_config_pix_height_set(g, h);
  game_window_pix_width_set(g, w);
  game_window_pix_height_set(g, h);

  LOG("SDL: Call SDL_GL_CreateContext(%dx%d)", game_window_pix_width_get(g), game_window_pix_height_get(g));
  sdl.context = SDL_GL_CreateContext(sdl.window);
  if (! sdl.context) {
    SDL_ClearError();
    ERR("SDL_GL_CreateContext failed %s", SDL_GetError());
    return false;
  }

  LOG("SDL: Call SDL_GL_MakeCurrent()");
  if (SDL_GL_MakeCurrent(sdl.window, sdl.context) < 0) {
    SDL_ClearError();
    ERR("SDL_GL_MakeCurrent failed %s", SDL_GetError());
    return false;
  }

  SDL_ClearError();

  //
  // Clear the screen, both buffers
  //
  glcolor(WHITE);
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //
  // Do we really need to do this? it takes a small bit of time.
  //
  if (0) {
    SDL_GL_SwapWindow(sdl.window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_GL_SwapWindow(sdl.window);
  }

  SDL_SetWindowTitle(sdl.window, "gorget");

  //
  // Ensure the window is always in front.
  //
  SDL_RaiseWindow(sdl.window);
  SDL_SetWindowInputFocus(sdl.window);
  // SDL_OnWindowFocusLost

  LOG("SDL: OpenGL Vendor   : %s", glGetString(GL_VENDOR));
  LOG("SDL: OpenGL Renderer : %s", glGetString(GL_RENDERER));
  LOG("SDL: OpenGL Version  : %s", glGetString(GL_VERSION));

  IF_DEBUG { DBG("SDL: OpenGL Exts     : %s", glGetString(GL_EXTENSIONS)); }

  return true;
}

void sdl_display_fini(Gamep g)
{
  LOG("SDL: Video fini");
  TRACE_AND_INDENT();

  gl_fini_2d_mode(g);

#ifdef ENABLE_UI_ASCII_MOUSE
  SDL_ShowCursor(0);
  SDL_ShowCursor(1);
#endif

  if (sdl.init_video) {
    LOG("SDL: Video quit");
    sdl.init_video = 0;
    SDL_VideoQuit();
  }

  LOG("SDL: Delete GL context");
  SDL_GL_DeleteContext(sdl.context);
  sdl.context = nullptr;

  LOG("SDL: Destroy window");
  SDL_DestroyWindow(sdl.window);
  sdl.window = nullptr;
}
