//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_main.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_wid_console.hpp"

void sdl_display(class Game *g)
{
  blit_fbo_bind(FBO_FINAL);
  glClear(GL_COLOR_BUFFER_BIT);
  glcolor(WHITE);

  //
  // Blit the game map in the middle of the screen as a square
  //
  glBlendFunc(GL_ONE, GL_ZERO);

  if (g) {
    auto level = game_level_get(g);
    if (level) {
      auto w = game_ascii_gl_width_get(game);
      auto h = game_ascii_gl_height_get(game);

      int visible_map_tl_x = w * UI_LEFTBAR_WIDTH;
      int visible_map_tl_y = h * UI_TOPCON_HEIGHT;
      int visible_map_br_x = (TERM_WIDTH - UI_RIGHTBAR_WIDTH) * w;
      int visible_map_br_y = (TERM_HEIGHT - 2) * h;

      blit_init();
      blit(g_fbo_tex_id[ FBO_MAP ], 0.0, 1.0, 1.0, 0.0, visible_map_tl_x, visible_map_tl_y, visible_map_br_x,
           visible_map_br_y);

      blit_flush();
    }
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

  SDL_Delay(game_sdl_delay_get(game));

  //
  // Flip
  //
  SDL_GL_SwapWindow(sdl.window);
}

void sdl_display_reset(void)
{
  CON("SDL: Video resetting");

  auto old_console = wid_console_serialize();

  wid_console_fini();
  config_game_gfx_update();

  wid_console_init();
  wid_hide(wid_console_window);
  sdl_flush_display(game);

  wid_console_deserialize(old_console);

  //
  // DO NOT CALL THIS HERE. We could be inside a widget mouse up handler.
  //
  // wid_gc_all();
  //
  wid_display_all();

  CON("SDL: Video reset");
  sdl_flush_display(game);
}
