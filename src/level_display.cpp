//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sdl_event.hpp"
#include "my_tex.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

static int onscreen_map_tl_x;
static int onscreen_map_tl_y;
static int onscreen_map_br_x;
static int onscreen_map_br_y;
static int onscreen_map_mouse_x;
static int onscreen_map_mouse_y;

static void level_display_tile(Levelp l, Tpp tp, uint16_t tile_index, point tl, point br, point offset)
{
  auto tile = tile_index_to_tile(tile_index);
  if (! tile) {
    return;
  }

  tl += offset;
  br += offset;

  if (tp_is_blit_outlined_get(tp)) {
    tile_blit_outline(tile, tl, br, WHITE, BLACK, false);
  } else if (tp_is_blit_square_outlined_get(tp)) {
    tile_blit_outline(tile, tl, br, WHITE, BLACK, true);
  } else {
    tile_blit(tile, tl, br);
  }
}

static void level_display_z_layer(Levelp l, int x, int y, int slot, int z, bool deco)
{
  int dw = TILE_WIDTH;
  int dh = TILE_HEIGHT;

  point tl;
  point br;

  Tpp  tp;
  auto t = level_thing_or_tp_get(l, x, y, slot, &tp);
  if (! tp) {
    return;
  }

  if (tp_z_depth_get(tp) != z) {
    return;
  }

  auto obj        = &l->obj[ x ][ y ][ slot ];
  auto tile_index = obj->tile;
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

  if (tp_is_blit_on_ground_get(tp)) {
    //
    // On the ground
    //
    tl.y -= (pix_height - dh);
    //
    // Center x
    //
    tl.x -= (pix_width - dw) / 2;
  } else if (tp_is_blit_centered_get(tp)) {
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
  if (z == MAP_DEPTH_FLOOR) {
    if ((onscreen_map_mouse_x >= tl.x) && (onscreen_map_mouse_x < br.x) && (onscreen_map_mouse_y >= tl.y)
        && (onscreen_map_mouse_y < br.y)) {
      CON("CURSOR %d %d %d,%d -> %d,%d", onscreen_map_mouse_x, onscreen_map_mouse_y, tl.x, tl.y, br.x, br.y);
      level_cursor_set(l, x, y, CURSOR_AT);
      return;
    }
  }

  //
  // Flippable?
  //
  if (tp_is_animated_can_hflip_get(tp)) {
    if (thing_is_dir_left(t) || thing_is_dir_tl(t) || thing_is_dir_bl(t)) {
      std::swap(tl.x, br.x);
    }
  }

  if (deco) {
    tile_index += 47;
  }

  level_display_tile(l, tp, tile_index, tl, br, point(0, 0));
}

void level_display(Levelp l)
{
  TRACE_NO_INDENT();

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
  // Get the visible map bounds
  //
  game_onscreen_map_get(game, &onscreen_map_tl_x, &onscreen_map_tl_y, &onscreen_map_br_x, &onscreen_map_br_y);

  //
  // Find out what pixel on the map the mouse is over
  //
  onscreen_map_mouse_x = sdl.mouse_x - onscreen_map_tl_x;
  onscreen_map_mouse_y = sdl.mouse_y;
  float scale_x        = (float) game_pix_width_get(game) / (float) game_window_pix_width_get(game);
  float scale_y        = (float) game_pix_height_get(game) / (float) game_window_pix_height_get(game);
  onscreen_map_mouse_x = (int) ((float) onscreen_map_mouse_x * scale_x);
  onscreen_map_mouse_y = (int) ((float) onscreen_map_mouse_y * scale_y);

  for (auto y = l->miny; y < l->maxy; y++) {
    for (auto x = l->maxx - 1; x >= l->minx; x--) {
      for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        level_display_z_layer(l, x, y, slot, MAP_DEPTH_FLOOR, no_deco);
        level_display_z_layer(l, x, y, slot, MAP_DEPTH_WALL, no_deco);
      }
    }
  }

  //
  // Doors only
  //
  for (auto y = l->miny; y < l->maxy; y++) {
    for (auto x = l->maxx - 1; x >= l->minx; x--) {
      for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        level_display_z_layer(l, x, y, slot, MAP_DEPTH_DOOR, no_deco);
        level_display_z_layer(l, x, y, slot, MAP_DEPTH_OBJ1, no_deco);
        level_display_z_layer(l, x, y, slot, MAP_DEPTH_OBJ2, no_deco);
        level_display_z_layer(l, x, y, slot, MAP_DEPTH_PLAYER, no_deco);
      }
    }
  }

  //
  // Shadows
  //
  for (auto y = l->miny; y < l->maxy; y++) {
    for (auto x = l->maxx - 1; x >= l->minx; x--) {
      for (auto slot = 0; slot < MAP_SLOTS; slot++) {
        level_display_z_layer(l, x, y, slot, MAP_DEPTH_WALL, deco);
        level_display_z_layer(l, x, y, slot, MAP_DEPTH_DOOR, deco);
      }
    }
  }

  //
  // Top level cursor
  //
  for (auto y = l->miny; y < l->maxy; y++) {
    for (auto x = l->maxx - 1; x >= l->minx; x--) {
      level_display_z_layer(l, x, y, 0, MAP_DEPTH_CURSOR, no_deco);
    }
  }

  blit_flush();
}
