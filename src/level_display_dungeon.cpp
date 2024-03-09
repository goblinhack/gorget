//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_tex.hpp"
#include "my_tp.hpp"

void Level::display_dungeon_tile(Tpp tp, Tilep tile, point tl, point br, point offset)
{
  tl += offset;
  br += offset;

  if (tp->is_blit_outlined) {
    tile_blit_outline(tile, tl, br, WHITE, BLACK, true);
  } else if (tp->is_blit_square_outlined) {
    tile_blit_outline(tile, tl, br, WHITE, BLACK, false);
  } else {
    tile_blit(tile, tl, br);
  }
}

void Level::display_dungeon_tile(Tpp tp, uint16_t tile_index, point tl, point br, point offset)
{
  auto tile = tile_index_to_tile(tile_index);
  if (! tile) {
    return;
  }

  display_dungeon_tile(tp, tile, tl, br, offset);
}

void Level::display_dungeon_z_layer(int x, int y, int slot, int z, bool deco)
{
  int dw = TILE_WIDTH;
  int dh = TILE_HEIGHT;

  glcolor(WHITE);

  point tl;
  point br;

  Tpp   tp;
  point p(x, y);
  auto  t = thing_get(p, slot, &tp);
  if (! tp) {
    return;
  }

  if (tp->z_depth != z) {
    return;
  }

  auto obj        = &data->obj[ x ][ y ][ slot ];
  auto tile_index = obj->tile;
  if (! tile_index) {
    return;
  }

  auto tile = tile_index_to_tile(tile_index);
  if (! tile) {
    return;
  }

  auto pix_height = tile->pix_height;
  auto pix_width  = tile->pix_width;

  if (t) {
    tl.x = t->pix_x;
    tl.y = t->pix_y;
  } else {
    tl.x = x * TILE_WIDTH;
    tl.y = y * TILE_WIDTH;
  }

  tl.x -= data->pixel_map_at_x;
  tl.y -= data->pixel_map_at_y;

  if (tp->is_blit_on_ground) {
    //
    // On the ground
    //
    tl.y -= (pix_height - dh);
    //
    // Center x
    //
    tl.x -= (pix_width - dw) / 2;
  } else if (tp->is_blit_centered) {
    //
    // Centered
    //
    tl.x -= (pix_width - dw) / 2;
    tl.y -= (pix_height - dh) / 2;
  }

  br.x = tl.x + pix_width;
  br.y = tl.y + pix_height;

  if (deco) {
    display_dungeon_tile(tp, tile_index + 47, tl, br, point(0, 0));
  } else {
    display_dungeon_tile(tp, tile_index, tl, br, point(0, 0));
  }
}

void Level::display_dungeon(void)
{
  TRACE_NO_INDENT();

  set_display_bounds();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glcolor(WHITE);

  {
    int fbo = FBO_MAP_VISIBLE;
    blit_fbo_bind(fbo);
    glClear(GL_COLOR_BUFFER_BIT);
    blit_init();

    const bool deco    = true;
    const bool no_deco = false;

    for (auto y = miny; y < maxy; y++) {
      for (auto x = maxx - 1; x >= minx; x--) {
        for (auto slot = 0; slot < MAP_SLOTS; slot++) {
          display_dungeon_z_layer(x, y, slot, MAP_DEPTH_FLOOR, no_deco);
          display_dungeon_z_layer(x, y, slot, MAP_DEPTH_WALL, no_deco);
        }
      }
    }
    for (auto y = miny; y < maxy; y++) {
      for (auto x = maxx - 1; x >= minx; x--) {
        for (auto slot = 0; slot < MAP_SLOTS; slot++) {
          display_dungeon_z_layer(x, y, slot, MAP_DEPTH_DOOR, no_deco);
        }
      }
    }

    for (auto y = miny; y < maxy; y++) {
      for (auto x = maxx - 1; x >= minx; x--) {
        for (auto slot = 0; slot < MAP_SLOTS; slot++) {
          display_dungeon_z_layer(x, y, slot, MAP_DEPTH_WALL, deco);
          display_dungeon_z_layer(x, y, slot, MAP_DEPTH_DOOR, deco);
        }
      }
    }
  }

  glcolor(WHITE);
  blit_flush();

  {
    blit_fbo_bind(FBO_MAP);
    glClear(GL_COLOR_BUFFER_BIT);
    blit_fbo_game_pix(FBO_MAP_VISIBLE);
  }

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
