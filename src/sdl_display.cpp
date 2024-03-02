//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_wid_console.hpp"

void sdl_display(void)
{
  {
    blit_fbo_bind(FBO_FINAL);
    glClear(GL_COLOR_BUFFER_BIT);
    glcolor(WHITE);

    glBlendFunc(GL_ONE, GL_ZERO);
    blit_fbo_window_pix(FBO_MAP);
    if (0) {
      auto x_offset = (game->config.ui_pix_width - game->config.ui_pix_height) / 2;
      blit_init();
      blit(fbo_tex_id[ FBO_MAP ], 0.0, 1.0, 1.0, 0.0, x_offset, 0, game->config.ui_pix_height + x_offset,
           game->config.ui_pix_height);
      blit_flush();
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    blit_fbo_window_pix(FBO_WID);
    blit_fbo_unbind();

    glBlendFunc(GL_ONE, GL_ZERO);
    blit_fbo_window_pix(FBO_FINAL);

    //
    // Screenshot?
    //
    if (unlikely(g_do_screenshot)) {
      g_do_screenshot = 0;
      sdl_screenshot_do();
    }

    SDL_Delay(game->config.sdl_delay);

    //
    // Flip
    //
    if (likely(game->config.gfx_vsync_locked)) {
      SDL_GL_SwapWindow(sdl.window);
    } else {
      glFlush();
    }
  }
}

void sdl_display_reset(void)
{
  CON("SDL: Video resetting");

  auto old_console = wid_console_serialize();

  wid_console_fini();
  config_game_gfx_update();

  wid_console_init();
  wid_hide(wid_console_window);
  sdl_flush_display();

  wid_console_deserialize(old_console);

  //
  // DO NOT CALL THIS HERE. We could be inside a widget mouse up handler.
  //
  // wid_gc_all();
  //
  wid_display_all();

  CON("SDL: Video reset");
  sdl_flush_display();
}
