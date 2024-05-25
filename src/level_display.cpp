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

static int visible_map_mouse_x;
static int visible_map_mouse_y;

static void level_display_tile_index(Levelp l, Tpp tp, uint16_t tile_index, point tl, point br, point offset)
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

static void level_display_obj(Levelp l, int x, int y, Tpp tp, Thingp t, bool deco)
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
    tl.x = t->pix_x;
    tl.y = t->pix_y;
  } else {
    tl.x = x * TILE_WIDTH;
    tl.y = y * TILE_WIDTH;
  }

  tl.x -= l->pixel_map_at_x;
  tl.y -= l->pixel_map_at_y;

  if (tp_is_blit_on_ground(tp)) {
    //
    // On the ground
    //
    tl.y -= (pix_height - dh);
    //
    // Center x
    //
    tl.x -= (pix_width - dw) / 2;
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
  // Is the cursor here?
  //
  if (tp_is_floor(tp)) {
    if ((visible_map_mouse_x >= tl.x) && (visible_map_mouse_x < br.x) && (visible_map_mouse_y >= tl.y)
        && (visible_map_mouse_y < br.y)) {
      level_cursor_set(l, x, y);
    }
  }

  //
  // Flippable?
  //
  if (tp_is_animated_can_hflip(tp)) {
    if (thing_is_dir_left(t) || thing_is_dir_tl(t) || thing_is_dir_bl(t)) {
      std::swap(tl.x, br.x);
    }
  }

  if (deco) {
    return;
    tile_index += 47;
  }

  level_display_tile_index(l, tp, tile_index, tl, br, point(0, 0));
}

static void level_display_cursor(Levelp l, int x, int y)
{
  Tpp tp = nullptr;

  switch (l->cursor[ x ][ y ]) {
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
    level_display_obj(l, x, y, tp, NULL_THING, false);
  }
}

static void level_display_slot(Levelp l, int x, int y, int z, int slot, int depth, bool deco)
{
  Tpp  tp;
  auto t = thing_and_tp_get(l, x, y, z, slot, &tp);
  if (! tp) {
    return;
  }

  if (tp_z_depth_get(tp) != depth) {
    return;
  }

  level_display_obj(l, x, y, tp, t, deco);
}

void level_display(Levelp l)
{
  TRACE_NO_INDENT();

  //
  // What level is the player on?
  //
  auto player = thing_player(l);
  if (! player) {
    return;
  }
  auto z = player->at.z;

  //
  // Soft scroll to the player/
  //
  level_scroll_to_player(l);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glcolor(WHITE);

  int fbo = FBO_MAP;
  blit_fbo_bind(fbo);
  glClear(GL_COLOR_BUFFER_BIT);
  blit_init();

  const bool deco    = true;
  const bool no_deco = false;

  //
  // We need to find out what pixel on the map the mouse is over
  //
  game_visible_map_mouse_get(game, &visible_map_mouse_x, &visible_map_mouse_y);

  for (auto y = l->miny; y < l->maxy; y++) {
    for (auto x = l->maxx - 1; x >= l->minx; x--) {
      for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        level_display_slot(l, x, y, z, slot, MAP_Z_DEPTH_FLOOR, no_deco);
        level_display_slot(l, x, y, z, slot, MAP_Z_DEPTH_WALL, no_deco);
      }
    }
  }

  //
  // Doors only
  //
  for (auto y = l->miny; y < l->maxy; y++) {
    for (auto x = l->maxx - 1; x >= l->minx; x--) {
      for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        level_display_slot(l, x, y, z, slot, MAP_Z_DEPTH_DOOR, no_deco);
        level_display_slot(l, x, y, z, slot, MAP_Z_DEPTH_OBJ1, no_deco);
        level_display_slot(l, x, y, z, slot, MAP_Z_DEPTH_OBJ2, no_deco);
        level_display_slot(l, x, y, z, slot, MAP_Z_DEPTH_PLAYER, no_deco);
      }
    }
  }

  //
  // Shadows
  //
  for (auto y = l->miny; y < l->maxy; y++) {
    for (auto x = l->maxx - 1; x >= l->minx; x--) {
      for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        level_display_slot(l, x, y, z, slot, MAP_Z_DEPTH_WALL, deco);
        level_display_slot(l, x, y, z, slot, MAP_Z_DEPTH_DOOR, deco);
      }
    }
  }

  //
  // Top level cursor
  //
  for (auto y = l->miny; y < l->maxy; y++) {
    for (auto x = l->maxx - 1; x >= l->minx; x--) {
      level_display_cursor(l, x, y);
    }
  }

  blit_flush();
}
