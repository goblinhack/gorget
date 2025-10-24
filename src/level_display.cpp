//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_game_popups.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"

static void level_display_cursor(Gamep g, Levelsp v, Levelp l, spoint p, int fbo)
{
  TRACE_NO_INDENT();

  Tpp tp = nullptr;

  switch (v->cursor[ p.x ][ p.y ]) {
    case CURSOR_NONE :
      //
      // Normal case. No cursor or anything else here.
      //
      return;
    case CURSOR_PATH :
      {
        //
        // No paths over a chasm
        //
        if (level_is_cursor_path_none(g, v, l, p)) {
          return;
        }

        //
        // No cursor path during level selection
        //
        if (level_is_level_select(g, v, l)) {
          return;
        }

        //
        // If the player is dead, then don't show the move path, but do allow them to move
        // the cursor around so they can still look at the level/cause of death.
        //
        auto player = thing_player(g);
        if (player && thing_is_dead(player)) {
          break;
        }

        //
        // Cursors do not use up slots on the map, to avoid them interacting with anything
        //
        static Tpp tp_once;
        if (! tp_once) {
          tp_once = tp_find_mand("cursor_path");
        }
        tp = tp_once;
        break;
      }
    case CURSOR_AT :
      {
        //
        // Cursors do not use up slots on the map, to avoid them interacting with anything
        //
        static Tpp tp_once;
        if (! tp_once) {
          tp_once = tp_find_mand("cursor_at");
        }
        tp = tp_once;
        break;
      }
  }

  if (tp) {
    spoint   tl, br;
    uint16_t tile_index;
    thing_get_coords(g, v, l, p, tp, NULL_THING, &tl, &br, &tile_index);
    thing_display(g, v, l, p, tp, NULL_THING, tl, br, tile_index, fbo);
  }
}

static void level_display_slot(Gamep g, Levelsp v, Levelp l, spoint p, int slot, int depth, int fbo)
{
  TRACE_NO_INDENT();

  Tpp  tp;
  auto t = thing_and_tp_get_at(g, v, l, p, slot, &tp);
  if (! tp) {
    return;
  }

  if (thing_is_falling(t)) {
    if (depth != MAP_Z_DEPTH_FLOOR) {
      return;
    }
  } else if (tp_z_depth_get(tp) != depth) {
    return;
  }

  spoint   tl, br;
  uint16_t tile_index;
  thing_get_coords(g, v, l, p, tp, t, &tl, &br, &tile_index);
  thing_display(g, v, l, p, tp, t, tl, br, tile_index, fbo);
}

//
// Render the level to an FBO
//
static void level_display_fbo(Gamep g, Levelsp v, Levelp l, int fbo)
{
  TRACE_NO_INDENT();

  const bool is_level_select = level_is_level_select(g, v, l);

  //
  // What level is the player on?
  //
  auto player = thing_player(g);
  if (! player) {
    ERR("No player");
    return;
  }

  //
  // Soft scroll to the player
  //
  level_scroll_to_focus(g, v, l);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glcolor(WHITE);

  blit_fbo_bind(fbo);
  glClear(GL_COLOR_BUFFER_BIT);
  blit_init();

  //
  // Display tiles in z prio order
  //
  FOR_ALL_MAP_Z_DEPTH(z_depth)
  {
    for (auto y = v->miny; y < v->maxy; y++) {
      for (auto x = v->minx; x < v->maxx; x++) {

        spoint p(x, y);
        auto   display_tile = false;

        if (g_opt_debug1) {
          display_tile = true;
        } else if (is_level_select) {
          //
          // No lighting in level selection
          //
          display_tile = true;
        } else if (thing_vision_can_see_tile(g, v, l, player, p)) {
          //
          // Can see currently
          //
          display_tile = true;

          //
          // If too few light rays hit this tile, darken it to avoid flicker
          //
          auto lit = v->light_map.tile[ p.x ][ p.y ].lit;
          if (lit < (LIGHT_MAX_RAYS_MAX / 90)) {
            g_monochrome = true;
          }

          //
          // If this is the overlay, filter to only things that are always blitted
          //
          if (fbo == FBO_MAP_FG_OVERLAY) {
            if (level_is_blit_colored_always(g, v, l, p)) {
              //
              // Always show
              //
              display_tile = true;
              g_monochrome = false;
            } else {
              //
              // Filter all other tiles that were shown in the lower layer FBO anyway
              //
              display_tile = false;
            }
          }
        } else if (thing_vision_has_seen_tile(g, v, l, player, p)) {
          //
          // Has seen previously
          //
          if (level_is_blit_colored_always(g, v, l, p)) {
            //
            // Show in normal colors. Implies "is_blit_if_has_seen".
            //
            display_tile = true;
          } else {
            //
            // Show in monochrome
            //
            display_tile = true;
            g_monochrome = true;
          }
        }

        if (fbo == FBO_MAP_BG) {
          g_monochrome = true;
        }

        if (display_tile) {
          for (auto slot = 0; slot < MAP_SLOTS; slot++) {
            level_display_slot(g, v, l, p, slot, z_depth, fbo);
          }
        }

        g_monochrome = false;
      }
    }
  }

  //
  // Top level cursor
  //
  for (auto y = v->miny; y < v->maxy; y++) {
    for (auto x = v->minx; x < v->maxx; x++) {
      spoint p(x, y);
      level_display_cursor(g, v, l, p, fbo);
    }
  }

  blit_flush();

  if (fbo == FBO_MAP_FG_OVERLAY) {
    game_popups_display(g, v, l);
  }

  blit_fbo_unbind();
}

void level_display(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  level_display_fbo(g, v, l, FBO_MAP_BG);
  level_display_fbo(g, v, l, FBO_MAP_FG);
  level_display_fbo(g, v, l, FBO_MAP_FG_OVERLAY);
}

static void level_blit_light(Gamep g, Levelsp v, Levelp l, color c)
{
  TRACE_NO_INDENT();

  //
  // Get the pixel extents of the map on screen
  //
  int visible_map_tl_x;
  int visible_map_tl_y;
  int visible_map_br_x;
  int visible_map_br_y;
  game_visible_map_pix_get(g, &visible_map_tl_x, &visible_map_tl_y, &visible_map_br_x, &visible_map_br_y);

  if (game_map_zoom_is_full_map_visible(g)) {
    //
    // Zoomed out. Full map visible.
    //
    blit_init();
    blit(g_fbo_tex_id[ FBO_MAP_LIGHT ], 0, 1, 1, 0, visible_map_tl_x, visible_map_tl_y, visible_map_br_x,
         visible_map_br_y, c);
    blit_flush();
  } else {
    //
    // Zoomed in. Partial map visible.
    //
    spoint tl1;
    spoint br1;
    spoint tl2;
    spoint br2;
    //
    // Get the on screen pixel co-oords of the top left and bottom right tiles
    //
    thing_get_coords(g, v, l, spoint(0, 0), NULL_TP, NULL_THING, &tl1, &br1, nullptr);
    thing_get_coords(g, v, l, spoint(MAP_WIDTH - 1, MAP_HEIGHT - 1), NULL_TP, NULL_THING, &tl2, &br2, nullptr);

    tl1.x += visible_map_tl_x;
    tl1.y += visible_map_tl_y;
    br2.x += visible_map_tl_x;
    br2.y += visible_map_tl_y;

    //
    // glScissor co-ordinates are inverted
    //
    auto y = game_window_pix_height_get(g) - visible_map_br_y;
    auto w = visible_map_br_x - visible_map_tl_x;
    auto h = visible_map_br_y - visible_map_tl_y;

    //
    // As we display the light map zoomed in, we need to clip it
    //
    glEnable(GL_SCISSOR_TEST);
    glScissor(visible_map_tl_x, y, w, h);

    //
    // Blit the entire light map, scaled to the pixel size of the zoomed in mode
    //
    blit_init();
    blit(g_fbo_tex_id[ FBO_MAP_LIGHT ], 0, 1, 1, 0, tl1.x, tl1.y, br2.x, br2.y, c);
    blit_flush();

    glDisable(GL_SCISSOR_TEST);
  }
}

void level_blit(Gamep g)
{
  TRACE_NO_INDENT();

  if (! g) {
    return;
  }

  auto v = game_levels_get(g);
  if (! v) {
    return;
  }

  auto l = game_level_get(g, v);
  if (! l) {
    return;
  }

  //
  // Get the pixel extents of the map on screen
  //
  int visible_map_tl_x;
  int visible_map_tl_y;
  int visible_map_br_x;
  int visible_map_br_y;
  game_visible_map_pix_get(g, &visible_map_tl_x, &visible_map_tl_y, &visible_map_br_x, &visible_map_br_y);

  if (DEBUG || level_is_level_select(g, v, l)) {
    //
    // No lighting for level selection
    //
    blit_fbo_bind(FBO_MAP_FG_MERGED);
    glClear(GL_COLOR_BUFFER_BIT);
    glcolor(WHITE);

    blit_fbo(g, FBO_MAP_FG, visible_map_tl_x, visible_map_tl_y, visible_map_br_x, visible_map_br_y);
    blit_fbo_unbind();
  } else {
    //
    // Blit the dark background tiles that have been seen previously
    //
    blit_fbo_bind(FBO_MAP_BG_MERGED);
    glClear(GL_COLOR_BUFFER_BIT);
    glcolor(WHITE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    blit_fbo(g, FBO_MAP_BG, visible_map_tl_x, visible_map_tl_y, visible_map_br_x, visible_map_br_y);

    level_blit_light(g, v, l, BLACK);
    blit_fbo_unbind();

    //
    // Blit the light as a mask
    //
    blit_fbo_bind(FBO_MAP_FG_MERGED);
    glClear(GL_COLOR_BUFFER_BIT);
    glcolor(WHITE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    level_blit_light(g, v, l, WHITE);

    //
    // Mask out non lit areas of the foreground
    //
    glBlendFunc(GL_DST_ALPHA, GL_ZERO);
    blit_fbo(g, FBO_MAP_FG, visible_map_tl_x, visible_map_tl_y, visible_map_br_x, visible_map_br_y);

    //
    // Blit things that are always shown once seen (and popups)
    //
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    blit_fbo(g, FBO_MAP_FG_OVERLAY, visible_map_tl_x, visible_map_tl_y, visible_map_br_x, visible_map_br_y);
    blit_fbo_unbind();
  }

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  blit_fbo_bind(FBO_FINAL);
  blit_init();
  blit_fbo(g, FBO_MAP_BG_MERGED);
  blit_fbo(g, FBO_MAP_FG_MERGED);
  blit_flush();
}
