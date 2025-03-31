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

      //
      // Brighter map effect
      //
      glBlendFunc(GL_ONE, GL_DST_COLOR);

      blit_init();
      blit(g_fbo_tex_id[ FBO_MAP ], 0.0, 1.0, 1.0, 0.0, visible_map_tl_x, visible_map_tl_y, visible_map_br_x,
           visible_map_br_y);
      blit(g_fbo_tex_id[ FBO_MAP ], 0.0, 1.0, 1.0, 0.0, visible_map_tl_x, visible_map_tl_y, visible_map_br_x,
           visible_map_br_y);
      blit_flush();
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
