//
// Changed by goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_gl.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_tests.hpp"
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
      color c = BLACK;

      spoint p(x, y);

      if (level_is_dirt(g, v, l, p)) {
        c = GRAY10;
      }
      if (level_is_floor(g, v, l, p)) {
        c = GRAY20;
      }
      if (level_is_corridor(g, v, l, p)) {
        c = GRAY10;
      }
      if (level_alive_is_foliage(g, v, l, p)) {
        c = GREEN4;
      }
      if (level_alive_is_grass(g, v, l, p)) {
        // ignore
      }
      if (level_is_wall(g, v, l, p)) {
        c = GRAY50;
      }
      if (level_is_barrel(g, v, l, p)) {
        // ignore
      }
      if (level_is_brazier(g, v, l, p)) {
        c = YELLOW;
      }
      if (level_is_bridge(g, v, l, p)) {
        c = BROWN;
      }
      if (level_is_chasm(g, v, l, p)) {
        c = BLACK;
      }
      if (level_is_water(g, v, l, p)) {
        c = BLUE;
      }
      if (level_is_deep_water(g, v, l, p)) {
        c = BLUE4;
      }
      if (level_is_door_unlocked(g, v, l, p)) {
        // ignore
      }
      if (level_is_door_locked(g, v, l, p)) {
        if (level_open_is_door_locked(g, v, l, p)) {
          // ignore
        } else {
          c = BROWN;
        }
      }
      if (level_is_door_secret(g, v, l, p)) {
        if (level_open_is_door_secret(g, v, l, p)) {
          // ignore
        } else {
          c = GRAY40;
        }
      }
      if (level_is_key(g, v, l, p)) {
        c = YELLOW;
      }
      if (level_is_lava(g, v, l, p)) {
        c = RED;
      }
      if (level_is_mob1(g, v, l, p)) {
        c = ORANGE;
      }
      if (level_is_mob2(g, v, l, p)) {
        c = ORANGE;
      }
      if (level_is_monst_group_easy(g, v, l, p)) {
        c = ORANGE;
      }
      if (level_is_monst_group_hard(g, v, l, p)) {
        c = ORANGE;
      }
      if (level_is_pillar(g, v, l, p)) {
        // ignore
      }
      if (level_is_teleport(g, v, l, p)) {
        // ignore
        c = PURPLE;
      }
      if (level_is_trap(g, v, l, p)) {
        // ignore
      }
      if (level_is_treasure(g, v, l, p)) {
        c = GOLD;
      }
      if (level_is_entrance(g, v, l, p)) {
        c = PINK;
      }
      if (level_is_exit(g, v, l, p)) {
        c = PURPLE;
      }
      if (level_is_fire(g, v, l, p)) {
        c = ORANGE2;
      }
      if (level_is_player(g, v, l, p)) {
        c = CYAN;
      }
      if (level_is_steam(g, v, l, p)) {
        // ignore
      }
      if (level_is_smoke(g, v, l, p)) {
        // ignore
      }

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
