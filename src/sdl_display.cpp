//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_main.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_wid_console.hpp"

void sdl_display(Gamep g)
{
  TRACE_NO_INDENT();

  blit_fbo_bind(FBO_FINAL);
  glClear(GL_COLOR_BUFFER_BIT);
  glcolor(WHITE);

  //
  // Blit the game map in the middle of the screen as a square
  //
  glBlendFunc(GL_ONE, GL_ZERO);

  if (g) {
    auto level = game_levels_get(g);
    if (level) {
      //
      // Get the pixel extents of the map on screen
      //
      int visible_map_tl_x;
      int visible_map_tl_y;
      int visible_map_br_x;
      int visible_map_br_y;
      game_visible_map_pix_get(g, &visible_map_tl_x, &visible_map_tl_y, &visible_map_br_x, &visible_map_br_y);

      color c = WHITE;
      c.a     = 255;
      glcolor(c);

      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      blit_init();
      blit(g_fbo_tex_id[ FBO_MAP ], 0.0, 1.0, 1.0, 0.0, visible_map_tl_x, visible_map_tl_y, visible_map_br_x,
           visible_map_br_y);
      blit_flush();

      if (0) {
        c.a = 5;
        glcolor(c);

        //
        // Paste this code prior to the blend in question
        //
        extern int         vals[];
        extern std::string vals_str[];
        extern int         g_blend_a;
        extern int         g_blend_b;
        CON("glBlendFunc(%s, %s)", vals_str[ g_blend_a ].c_str(), vals_str[ g_blend_b ].c_str());
        glBlendFunc(vals[ g_blend_a ], vals[ g_blend_b ]);

        blit_init();
        blit(g_fbo_tex_id[ FBO_MAP ], 0.0, 1.0, 1.0, 0.0, visible_map_tl_x - 1, visible_map_tl_y - 1,
             visible_map_br_x + 1, visible_map_br_y + 1);
        blit_flush();

        if (0) {
          blit_init();
          blit(g_fbo_tex_id[ FBO_MAP ], 0.0, 1.0, 1.0, 0.0, visible_map_tl_x + 1, visible_map_tl_y + 1,
               visible_map_br_x + 1, visible_map_br_y + 1);
          blit_flush();

          blit_init();
          blit(g_fbo_tex_id[ FBO_MAP ], 0.0, 1.0, 1.0, 0.0, visible_map_tl_x + 1, visible_map_tl_y - 1,
               visible_map_br_x + 1, visible_map_br_y - 1);
          blit_flush();

          blit_init();
          blit(g_fbo_tex_id[ FBO_MAP ], 0.0, 1.0, 1.0, 0.0, visible_map_tl_x - 1, visible_map_tl_y + 1,
               visible_map_br_x - 1, visible_map_br_y + 1);
          blit_flush();
        }
      }
    }
  }

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  blit_fbo_window_pix(g, FBO_WID);
  blit_fbo_unbind();
  glBlendFunc(GL_ONE, GL_ZERO);
  blit_fbo_window_pix(g, FBO_FINAL);

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
      DIE("SDL_GetCurrentDisplayMode couldn't set windowed display: %s", SDL_GetError());
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

  if (game_gfx_allow_highdpi_get(g)) {
    //
    // For a lo pixel game this makes no sense as the frame
    // buffers are really large and slows things down.
    //
    LOG("SDL: Calling SDL_GetDisplayDPI");
    float dpi;
    if (SDL_GetDisplayDPI(0, nullptr, &dpi, nullptr) == 0) {
      video_flags |= SDL_WINDOW_ALLOW_HIGHDPI;
      LOG("SDL: Set SDL_WINDOW_ALLOW_HIGHDPI");
    } else {
      ERR("SDL: Cannot enable high DPI: %s", SDL_GetError());
    }
  }

  if (g_opt_test_grid || g_opt_test_rooms || g_opt_test_levels) {
    video_flags = SDL_WINDOW_OPENGL;
  }

  LOG("SDL: Create window size %ux%u", video_width, video_height);
  sdl.window = SDL_CreateWindow("gorget", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, video_width, video_height,
                                video_flags);
  if (! sdl.window) {
    ERR("SDL_CreateWindow couldn't set windowed display %ux%u: %s", video_width, video_height, SDL_GetError());
    game_config_reset(g);
    game_save_config(g);
    return false;
  }

  int w, h;
  if (video_flags & SDL_WINDOW_ALLOW_HIGHDPI) {
    SDL_GL_GetDrawableSize(sdl.window, &w, &h);
    LOG("SDL: Created dpi window size %ux%u", w, h);
  } else {
    SDL_GetWindowSize(sdl.window, &w, &h);
    LOG("SDL: Created window size %ux%u", w, h);
  }

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

  LOG("SDL: OpenGL Vendor   : %s", glGetString(GL_VENDOR));
  LOG("SDL: OpenGL Renderer : %s", glGetString(GL_RENDERER));
  LOG("SDL: OpenGL Version  : %s", glGetString(GL_VERSION));

  IF_DEBUG { DBG("SDL: OpenGL Exts     : %s", glGetString(GL_EXTENSIONS)); }

  return true;
}
