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

static void level_minimap_world_update(Gamep g, Levelsp v, Levelp l, const bool level_select)
{
  TRACE_NO_INDENT();

  const FboEnum fbo = FBO_MINIMAP_WORLD;
  const auto    dx  = MAP_WORLD_MAP_PIXEL_SIZE_PER_LEVEL * LEVEL_SCALE;
  const auto    dy  = MAP_WORLD_MAP_PIXEL_SIZE_PER_LEVEL * LEVEL_SCALE;

  //
  // The level passed in here could be the level select level, so always look
  // at the player
  //
  auto player = thing_player(g);
  if (! player) {
    return;
  }

  int w, h;
  fbo_get_size(g, fbo, w, h);
  gl_enter_2d_mode(g, w, h);

  blit_fbo_bind(fbo);
  {
    glBlendFunc(GL_ONE, GL_ZERO);
    gl_clear();

    blit_init();

    blit(solid_tex_id, 0, 1, 1, 0, 0, 0, w, h, GRAY5);

    for (auto x = 0; x < LEVELS_ACROSS; x++) {
      for (auto y = 0; y < LEVELS_DOWN; y++) {
        color  c              = BLACK;
        Levelp level_at_coord = nullptr;

        spoint p(x, y);
        auto   s = level_select_get(g, v, p);
        if (! s->is_set) {
          //
          // No level here
          //
          continue;
        }

        level_at_coord = game_level_get(g, v, s->level_num);
        if (! level_at_coord) {
          continue;
        }

        //
        // Only if in level selection can we be hovering over a level
        //
        Levelp level_over;
        if (level_select) {
          level_over = level_select_get_level_at_tile_coords(g, v, p);
        } else {
          level_over = nullptr;
        }

        if (level_at_coord->player_completed_level_via_exit) {
          //
          // Completed level
          //
          c = GREEN4;
        } else if (level_at_coord->player_fell_out_of_level) {
          //
          // Sort of completed level
          //
          c = ORANGE;
        } else if (level_at_coord == level_over) {
          //
          // Hovering over this level
          //
          c = GRAY50;
        } else {
          //
          // Normal unvisited level
          //
          c = GRAY20;
        }

        //
        // Final level
        //
        if (s->final_level) {
          c = YELLOW;
        }

        //
        // Cureent level
        //
        if (level_at_coord->level_num == player->level_num) {
          c = CYAN;
        }

        auto X   = x;
        auto Y   = y;
        auto tlx = X * dx;
        auto tly = Y * dy;
        auto brx = tlx + dx;
        auto bry = tly + dy;

        //
        // Shrink the tile by 1 pixel
        //
        tlx += 1;
        tly += 1;

        blit(solid_tex_id, tlx, tly, brx, bry, c);
      }
    }

    blit_flush();
  }
  blit_fbo_unbind();
}

static void level_minimap_world_update_rotated(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  const FboEnum fbo = FBO_MINIMAP_WORLD_ROTATED;

  int w, h;
  fbo_get_size(g, fbo, w, h);
  gl_enter_2d_mode(g, w, h);

  blit_fbo_bind(fbo);
  {
    glBlendFunc(GL_ONE, GL_ZERO);
    gl_clear();

    blit_init();
    blit(solid_tex_id, 0, 1, 1, 0, 0, 0, w, h, GRAY5);
    blit_flush();

    glPushMatrix();
    {
      //
      // Center the map then rotate it
      //
      float ox = w / 2;
      float oy = h / 2;
      glTranslatef(ox, oy, 0);
      glRotatef((float) -135, 0.0f, 0.0f, 1.0f);
      glTranslatef(-ox, -oy, 0);

      //
      // Compensate for the extra size due to rotation
      //
      // As we map this into a widget that is composed of text chars, it ends up slightly vertically stretched
      //
      int shrink = (int) ((float) w / 6.6); // hack hack
      blit_fbo(g, FBO_MINIMAP_WORLD, 0 + shrink, 0 + shrink, w - shrink, h - shrink);
    }
    glPopMatrix();
  }
  blit_fbo_unbind();
}

static void level_minimap_levels_update(Gamep g, Levelsp v, Levelp l, const bool level_select)
{
  TRACE_NO_INDENT();

  auto player = thing_player(g);
  if (! player) {
    return;
  }

  const FboEnum fbo = FBO_MINIMAP_LEVEL;
  const auto    dx  = 1;
  const auto    dy  = 1;

  int w, h;
  fbo_get_size(g, fbo, w, h);
  gl_enter_2d_mode(g, w, h);

  blit_fbo_bind(fbo);
  {
    glBlendFunc(GL_ONE, GL_ZERO);
    gl_clear();

    blit_init();

    for (auto x = 0; x < MAP_WIDTH; x++) {
      for (auto y = 0; y < MAP_HEIGHT; y++) {
        color  c = BLACK;
        spoint p(x, y);

        if (! g_opt_debug1) {
          if (! thing_vision_player_has_seen_tile(g, v, l, p)) {
            continue;
          }
        }

        if (level_is_dirt(g, v, l, p)) {
          c = GRAY10;
        }
        if (level_is_floor(g, v, l, p)) {
          c = GRAY30;
        }
        if (level_is_corridor(g, v, l, p)) {
          c = GRAY30;
        }
        if (level_is_wall(g, v, l, p)) {
          c = GRAY50;
        }
        if (level_is_rock(g, v, l, p)) {
          c = BROWN4;
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

        if (level_is_blit_shown_in_overlay(g, v, l, p)) {
          //
          // Keep bright colors
          //
        } else if (level_select) {
          //
          // No vision in level selection
          //
          c.r /= 2;
          c.g /= 2;
          c.b /= 2;
        } else if (! thing_vision_can_see_tile(g, v, l, player, p)) {
          //
          // Dim
          //
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
        tly--;
        bry--;

        blit(solid_tex_id, tlx, tly, brx, bry, c);
      }
    }

    blit_flush();
  }
  blit_fbo_unbind();
}

void level_minimaps_update(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  if (g_opt_tests) {
    return;
  }

  //
  // If in level select mode, avoid certain things, like vision effects
  //
  bool level_select = level_is_level_select(g, v, game_level_get(g, v));

  if (! solid_tex) {
    solid_tex    = tex_load("", "solid", GL_LINEAR);
    solid_tex_id = tex_get_gl_binding(solid_tex);
  }

  level_minimap_levels_update(g, v, l, level_select);
  //  sdl_fbo_dump(g, FBO_MINIMAP_LEVEL, "level");

  level_minimap_world_update(g, v, l, level_select);
  //  sdl_fbo_dump(g, FBO_MINIMAP_WORLD, "world");

  level_minimap_world_update_rotated(g, v, l);
  //  sdl_fbo_dump(g, FBO_MINIMAP_WORLD_ROTATED, "world-rotated");
}
