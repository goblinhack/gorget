//
// Changed by goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tex.hpp"

static void level_minimap_update(Gamep g, Levelsp v, Levelp l, int fbo)
{
  TRACE_NO_INDENT();

  static Texp solid_tex;
  static int  solid_tex_id;
  if (! solid_tex) {
    solid_tex    = tex_load("", "solid", GL_LINEAR);
    solid_tex_id = tex_get_gl_binding(solid_tex);
  }

  int w, h;
  fbo_get_size(g, FBO_MAP_LIGHT, w, h);
  gl_enter_2d_mode(g, w, h);

  glBlendFunc(GL_ONE, GL_ZERO);
  blit_fbo_bind(fbo);
  glClear(GL_COLOR_BUFFER_BIT);
  blit_init();

  const auto dx = 1;
  const auto dy = 1;

  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      color c = WHITE;

      auto X   = x;
      auto Y   = MAP_HEIGHT - y;
      auto tlx = X * dx;
      auto tly = Y * dy;
      auto brx = tlx + dx;
      auto bry = tly + dy;
      blit(solid_tex_id, 0, 0, 1, 1, tlx, tly, brx, bry, c);
    }
  }

  blit_fini();
  blit_fbo_unbind();
}

void level_minimaps_update(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  if (g_opt_tests) {
    return;
  }

  level_minimap_update(g, v, l, FBO_MINIMAP_WORLD);
  level_minimap_update(g, v, l, FBO_MINIMAP_LEVEL);
}
