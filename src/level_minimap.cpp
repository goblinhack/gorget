//
// Changed by goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sdl_proto.hpp"
#include "my_tests.hpp"
#include "my_tex.hpp"

static Texp solid_tex;
static int  solid_tex_id;

static void level_minimap_world_update(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  const int  fbo = FBO_MINIMAP_WORLD;
  const auto dx  = MAP_WORLD_SCALE * LEVEL_SCALE;
  const auto dy  = MAP_WORLD_SCALE * LEVEL_SCALE;

  int w, h;
  fbo_get_size(g, fbo, w, h);
  gl_enter_2d_mode(g, w, h);

  blit_fbo_bind(fbo);
  glBlendFunc(GL_ONE, GL_ZERO);
  glClear(GL_COLOR_BUFFER_BIT);
  blit_init();

  if (0) {
    blit(solid_tex_id, 0, 1, 1, 0, 0, 0, w, h, BROWN);
  }

  for (auto x = 0; x < LEVELS_ACROSS; x++) {
    for (auto y = 0; y < LEVELS_DOWN; y++) {
      color  c          = BLACK;
      Levelp level_over = nullptr;

      spoint p(x, y);
      auto   s = level_select_get(g, v, p);

      if (s->is_set) {
        level_over = game_level_get(g, v, s->level_num);
        if (level_over) {
          if (level_over->player_completed_level_via_exit) {
            c = GREEN;
          } else if (level_over->player_fell_out_of_level) {
            c = GREEN4;
          } else {
            c = GRAY20;
          }

          if (s->final_level) {
            c = YELLOW;
          }

          if (level_over == l) {
            c = CYAN;
          }
        } else {
          continue;
        }
      } else {
        continue;
      }

      auto X   = x;
      auto Y   = LEVELS_DOWN - y - 1;
      auto tlx = X * dx;
      auto tly = Y * dy;
      auto brx = tlx + dx - 2;
      auto bry = tly + dy - 2;

      blit(solid_tex_id, tlx, tly, brx, bry, c);
    }
  }

  blit_flush();
  blit_fbo_unbind();
}

static void level_minimap_world_update_rotated(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  const int fbo = FBO_MINIMAP_WORLD_ROTATED;

  int w, h;
  fbo_get_size(g, fbo, w, h);
  gl_enter_2d_mode(g, w, h);

  blit_fbo_bind(fbo);
  {
    glBlendFunc(GL_ONE, GL_ZERO);
    glClear(GL_COLOR_BUFFER_BIT);

    if (0) {
      blit_init();
      blit(solid_tex_id, 0, 1, 1, 0, 0, 0, w, h, BROWN);
      blit_flush();
    }

    glPushMatrix();
    {
      glTranslatef(0, h / 2, 0);
      glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
      float scale = (1.5);
      blit_fbo(g, FBO_MINIMAP_WORLD, 0, 0, (int) ((float) w / scale), (int) ((float) h / scale));
    }
    glPopMatrix();
  }
  blit_fbo_unbind();
}

static void level_minimap_levels_update(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  auto player = thing_player(g);
  if (! player) {
    return;
  }

  const int  fbo = FBO_MINIMAP_LEVEL;
  const auto dx  = 1;
  const auto dy  = 1;

  int w, h;
  fbo_get_size(g, fbo, w, h);
  gl_enter_2d_mode(g, w, h);

  blit_fbo_bind(fbo);
  glBlendFunc(GL_ONE, GL_ZERO);
  glClear(GL_COLOR_BUFFER_BIT);
  blit_init();

  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      color  c = BLACK;
      spoint p(x, y);

      if (! thing_vision_player_has_seen_tile(g, v, l, p)) {
        continue;
      }

      if (level_is_dirt(g, v, l, p)) {
        c = GRAY10;
      }
      if (level_is_floor(g, v, l, p)) {
        c = GRAY20;
      }
      if (level_is_corridor(g, v, l, p)) {
        c = GRAY10;
      }
      if (level_is_wall(g, v, l, p)) {
        c = GRAY50;
      }
      if (level_is_bridge(g, v, l, p)) {
        c = BROWN4;
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
      if (level_is_lava(g, v, l, p)) {
        c = ORANGE;
      }
      if (level_is_teleport(g, v, l, p)) {
        // ignore
        c = RED;
      }
      if (level_is_entrance(g, v, l, p)) {
        c = PINK;
      }
      if (level_is_exit(g, v, l, p)) {
        c = YELLOW;
      }
      if (level_is_fire(g, v, l, p)) {
        c = ORANGE2;
      }
      if (level_is_player(g, v, l, p)) {
        c = CYAN;
      }

      if (! thing_vision_can_see_tile(g, v, l, player, p)) {
        c.r /= 2;
        c.g /= 2;
        c.b /= 2;
      }

      auto X   = x;
      auto Y   = MAP_HEIGHT - y;
      auto tlx = X * dx;
      auto tly = Y * dy;
      auto brx = tlx + dx;
      auto bry = tly + dy;

      blit(solid_tex_id, tlx, tly, brx, bry, c);
    }
  }

  blit_flush();
  blit_fbo_unbind();
}

void level_minimaps_update(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  if (g_opt_tests) {
    return;
  }

  if (! solid_tex) {
    solid_tex    = tex_load("", "solid", GL_LINEAR);
    solid_tex_id = tex_get_gl_binding(solid_tex);
  }

  level_minimap_levels_update(g, v, l);
  //  sdl_fbo_dump(g, FBO_MINIMAP_LEVEL, "level");

  level_minimap_world_update(g, v, l);
  // sdl_fbo_dump(g, FBO_MINIMAP_WORLD, "world");

  level_minimap_world_update_rotated(g, v, l);
  // sdl_fbo_dump(g, FBO_MINIMAP_WORLD_ROTATED, "world-rotated");
}
