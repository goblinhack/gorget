//
// Copyright Neil McGill, goblinhack@gmail.com
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

static void level_display_tile_index(Gamep g, Levelsp v, Levelp l, Tpp tp, uint16_t tile_index, point tl, point br,
                                     point offset)
{
  auto tile = tile_index_to_tile(tile_index);
  if (! tile) {
    return;
  }

  tl += offset;
  br += offset;

  if (tp_is_blit_outlined(tp)) {
    tile_blit_outline(tile, tl, br, WHITE, BLACK, false);
  } else if (tp_is_blit_square_outlined(tp)) {
    tile_blit_outline(tile, tl, br, WHITE, BLACK, true);
  } else {
    tile_blit(tile, tl, br);
  }
}

static void level_display_obj(Gamep g, Levelsp v, Levelp l, point p, Tpp tp, Thingp t)
{
  int dw = TILE_WIDTH;
  int dh = TILE_HEIGHT;

  point tl;
  point br;

  int tile_index;

  if (t) {
    tile_index = t->tile_index;
  } else {
    Tilep tile = tp_tiles_get(tp, 0);
    tile_index = tile_global_index(tile);
  }

  if (! tile_index) {
    return;
  }

  auto tile = tile_index_to_tile(tile_index);
  if (! tile) {
    return;
  }

  auto pix_height = tile_height(tile);
  auto pix_width  = tile_width(tile);

  if (t) {
    //
    // All things
    //
    tl = t->pix_at;
  } else {
    //
    // Cursor
    //
    tl.x = p.x * TILE_WIDTH;
    tl.y = p.y * TILE_WIDTH;
  }

  tl -= v->pixel_map_at;

  if (tp_is_blit_on_ground(tp)) {
    //
    // Center x
    //
    tl.x -= (pix_width - dw) / 2;
    tl.y -= (pix_height - dh) / 2;
    //
    // On the ground
    //
    tl.y += TILE_WIDTH / 2;
    tl.y -= TILE_HEIGHT / 2;
    tl.y -= TILE_HEIGHT / 4;
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

  level_display_tile_index(g, v, l, tp, tile_index, tl, br, point(0, 0));
}

static void level_display_cursor(Gamep g, Levelsp v, Levelp l, point p)
{
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

static void level_display_slot(Gamep g, Levelsp v, Levelp l, point p, int slot, int depth, int prio)
{
  Tpp  tp;
  auto t = thing_and_tp_get_at(g, v, l, p, slot, &tp);
  if (! tp) {
    return;
  }

  if (tp_z_depth_get(tp) != depth) {
    return;
  }

  if (tp_z_prio_get(tp) != prio) {
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
  if (! player) {
    return;
  }

  //
  // Soft scroll to the player
  //
  level_scroll_to_player(g, v, l);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glcolor(WHITE);

  int fbo = FBO_MAP;
  blit_fbo_bind(fbo);
  glClear(GL_COLOR_BUFFER_BIT);
  blit_init();

  //
  // Display tiles in z prio order
  //
  FOR_ALL_Z_PRIO(z_depth)
  {
    for (auto y = v->miny; y < v->maxy; y++) {
      FOR_ALL_Z_PRIO(z_prio)
      {
        for (auto x = v->minx; x < v->maxx; x++) {
          for (auto slot = 0; slot < MAP_SLOTS; slot++) {
            level_display_slot(g, v, l, point(x, y), slot, z_depth, z_prio);
          }
        }
      }
    }
  }

  //
  // Top level cursor
  //
  for (auto y = v->miny; y < v->maxy; y++) {
    for (auto x = v->minx; x < v->maxx; x++) {
      point p(x, y);
      level_display_cursor(g, v, l, p);
    }
  }

  blit_flush();
}
