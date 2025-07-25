//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tex.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

static void level_display_tile(Gamep g, Levelsp v, Levelp l, Tpp tp, Thingp t, uint16_t tile_index, spoint tl,
                               spoint br)
{
  TRACE_NO_INDENT();

  auto tile = tile_index_to_tile(tile_index);
  if (! tile) {
    return;
  }

  color fg      = WHITE;
  color outline = BLACK;
  float x1;
  float x2;
  float y1;
  float y2;
  tile_coords(tile, &x1, &y1, &x2, &y2);

  //
  // Outlined?
  //
  auto single_pix_size = game_map_single_pix_size_get(g);

  //
  // Disable outlines when zoomed out
  //
  int zoom = game_map_zoom_get(g);
  if (zoom == 1) {
    single_pix_size = 0;
  }

  if (t) {
    //
    // Handle various effects
    //
    int fall_height;
    int submerged_pct;
    if ((fall_height = thing_is_falling(t))) {
      //
      // Falling
      //
      int dh = (int) (((MAX_FALL_TILE_HEIGHT * ((float) (br.y - tl.y))) / MAX_FALL_TIME_MS) * fall_height);
      tl.y += dh;
      br.y += dh;
    } else if ((submerged_pct = thing_submerged_pct(t))) {
      //
      // Submerge the tile if it is over some kind of liquid.
      //
      if (submerged_pct) {
        tile_submerge_pct(g, tl, br, x1, x2, y1, y2, thing_submerged_pct(t));
      }
    }
  }

  if (tp_is_blit_outlined(tp)) {
    tile_blit_outline(tile, x1, x2, y1, y2, tl, br, fg, outline, single_pix_size, false);
  } else if (tp_is_blit_square_outlined(tp)) {
    tile_blit_outline(tile, x1, x2, y1, y2, tl, br, fg, outline, single_pix_size, true);
  } else {
    tile_blit(tile, x1, x2, y1, y2, tl, br);
  }
}

void level_display_obj(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp, Thingp t)
{
  TRACE_NO_INDENT();

  int zoom = game_map_zoom_get(g);
  int dw   = INNER_TILE_WIDTH * zoom;
  int dh   = INNER_TILE_HEIGHT * zoom;

  spoint tl = spoint();
  spoint br = spoint();

  uint16_t tile_index;

  if (t) {
    //
    // Things
    //
    tile_index = t->tile_index;
  } else {
    //
    // Cursor
    //
    Tilep tile = tp_tiles_get(tp, THING_ANIM_IDLE, 0);
    tile_index = tile_global_index(tile);
  }

  if (! tile_index) {
    return;
  }

  auto tile = tile_index_to_tile(tile_index);
  if (! tile) {
    return;
  }

  auto pix_height = tile_height(tile) * zoom;
  auto pix_width  = tile_width(tile) * zoom;

  if (t) {
    //
    // All things
    //
    tl = t->pix_at;
    tl.x *= zoom;
    tl.y *= zoom;
  } else {
    //
    // Cursor
    //
    tl.x = p.x * dw;
    tl.y = p.y * dh;
  }

  tl -= v->pixel_map_at;

  if (tp_is_blit_on_ground(tp)) {
    //
    // On the ground
    //
  } else if (tp_is_blit_centered(tp)) {
    //
    // Centered
    //
    tl.x -= (pix_width - dw) / 2;
    tl.y -= (pix_height - dh) / 2;
  }

  //
  // Update the br coords if we changed the position
  //
  br.x = tl.x + pix_width;
  br.y = tl.y + pix_height;

  //
  // Flippable?
  //
  if (tp_is_animated_can_hflip(tp)) {
    if (thing_is_dir_left(t) || thing_is_dir_tl(t) || thing_is_dir_bl(t)) {
      std::swap(tl.x, br.x);
    }
  }

  //
  // Update submerged status
  //
  if (tp_is_submergible(tp)) {
    thing_submerged_pct_set(g, v, l, t, 0);
    if (level_is_deep_water(g, v, l, p)) {
      thing_submerged_pct_set(g, v, l, t, 80);
    } else if (level_is_water(g, v, l, p)) {
      thing_submerged_pct_set(g, v, l, t, 50);
    } else if (level_is_lava(g, v, l, p)) {
      thing_submerged_pct_set(g, v, l, t, 40);
    }
  }

  level_display_tile(g, v, l, tp, t, tile_index, tl, br);
}

static void level_display_cursor(Gamep g, Levelsp v, Levelp l, spoint p)
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
    level_display_obj(g, v, l, p, tp, NULL_THING);
  }
}

static void level_display_slot(Gamep g, Levelsp v, Levelp l, spoint p, int slot, int depth)
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

  level_display_obj(g, v, l, p, tp, t);
}

void level_display(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  //
  // What level is the player on?
  //
  auto player = thing_player(g);

  //
  // Soft scroll to the player
  //
  if (player) {
    level_scroll_to_focus(g, v, l);
  }

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glcolor(WHITE);

  int fbo = FBO_MAP;
  blit_fbo_bind(fbo);
  glClear(GL_COLOR_BUFFER_BIT);
  blit_init();

  //
  // Display tiles in z prio order
  //
  FOR_ALL_Z_DEPTH(z_depth)
  {
    for (auto y = v->miny; y < v->maxy; y++) {
      for (auto x = v->minx; x < v->maxx; x++) {
        for (auto slot = 0; slot < MAP_SLOTS; slot++) {
          level_display_slot(g, v, l, spoint(x, y), slot, z_depth);
        }
      }
    }
  }

  //
  // Top level cursor
  //
  for (auto y = v->miny; y < v->maxy; y++) {
    for (auto x = v->minx; x < v->maxx; x++) {
      spoint p(x, y);
      level_display_cursor(g, v, l, p);
    }
  }

  blit_flush();
}
