//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_game.hpp"
#include "my_game_defs.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

void level_map_set(Levelp l, const char *in)
{
  TRACE_NO_INDENT();
  const auto row_len      = MAP_WIDTH;
  auto       expected_len = row_len * MAP_HEIGHT;

  if ((int) strlen(in) != expected_len) {
    DIE("bad map size, expected %d, got %d", (int) strlen(in), (int) expected_len);
  }

  auto tp_wall    = tp_random_wall();
  auto tp_door    = tp_find("door");
  auto tp_floor   = tp_find("floor");
  auto tp_exit    = tp_find("exit");
  auto tp_player1 = tp_find("player1");
  auto tp_player2 = tp_find("player2");
  auto tp_player3 = tp_find("player3");
  auto tp_player4 = tp_find("player4");

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      auto offset = (row_len * y) + x;
      auto c      = in[ offset ];
      Tpp  tp     = nullptr;

      bool need_floor = false;

      switch (c) {
        case CHARMAP_WALL :
          need_floor = true;
          tp         = tp_wall;
          break;
        case CHARMAP_DOOR :
          need_floor = true;
          tp         = tp_door;
          break;
        case CHARMAP_TREASURE : break;
        case CHARMAP_MONST1 : break;
        case CHARMAP_PLAYER1 :
          need_floor = true;
          tp         = tp_player1;
          break;
        case CHARMAP_PLAYER2 :
          need_floor = true;
          tp         = tp_player2;
          break;
        case CHARMAP_PLAYER3 :
          need_floor = true;
          tp         = tp_player3;
          break;
        case CHARMAP_PLAYER4 :
          need_floor = true;
          tp         = tp_player4;
          break;
        case CHARMAP_EXIT :
          need_floor = true;
          tp         = tp_exit;
          break;
        case CHARMAP_KEY : need_floor = true; break;
        case CHARMAP_EMPTY : need_floor = true; break;
        default : DIE("unexpected map char '%c'", c);
      }

      if (need_floor) {
        auto tp = tp_floor;
        level_tp_set(l, x, y, tp);
      }

      if (! tp) {
        continue;
      }

      level_tp_set(l, x, y, tp);
    }
  }
}

bool level_is_same_type(Levelp l, int x, int y, Tpp tp)
{
  TRACE_NO_INDENT();

  if (! l) {
    return false;
  }

  if (level_is_oob(l, x, y)) {
    return false;
  }

  auto id = l->obj[ x ][ y ][ tp_z_depth_get(tp) ].id;
  if (! id) {
    return false;
  }

  return id == tp_id_get(tp);
}

void level_bounds_set(Levelp l)
{
  TRACE_NO_INDENT();

  auto dw = TILE_WIDTH;
  auto dh = TILE_HEIGHT;

  //
  // The number of tiles additionally to draw to avoid clipping
  //
  auto clipping_border = 2;

  //
  // Set the scroll bounds
  //
  if (l->pixel_map_at_x < 0) {
    l->pixel_map_at_x = 0;
  }
  if (l->pixel_map_at_y < 0) {
    l->pixel_map_at_y = 0;
  }

  //
  // Square map
  //
  auto max_pix_x = (MAP_WIDTH * dw) - game_pix_height_get(game);
  auto max_pix_y = (MAP_HEIGHT * dh) - game_pix_height_get(game);

  if (l->pixel_map_at_x > max_pix_x) {
    l->pixel_map_at_x = max_pix_x;
  }
  if (l->pixel_map_at_y > max_pix_y) {
    l->pixel_map_at_y = max_pix_y;
  }

  //
  // Set the tile bounds
  //
  int tmp_minx = l->pixel_map_at_x / dw;
  int tmp_miny = l->pixel_map_at_y / dh;
  tmp_minx -= clipping_border;
  tmp_minx -= clipping_border;

  if (tmp_minx < 0) {
    tmp_minx = 0;
  }
  if (tmp_miny < 0) {
    tmp_miny = 0;
  }

  int tmp_maxx = (l->pixel_map_at_x + game_map_pix_width_get(game)) / dw;
  int tmp_maxy = (l->pixel_map_at_y + game_map_pix_height_get(game)) / dh;

  tmp_maxx += clipping_border;
  tmp_maxy += clipping_border;

  if (tmp_maxx >= MAP_WIDTH) {
    tmp_maxx = MAP_WIDTH;
  }
  if (tmp_maxy >= MAP_HEIGHT) {
    tmp_maxy = MAP_HEIGHT;
  }

  l->minx = tmp_minx;
  l->miny = tmp_miny;
  l->maxx = tmp_maxx;
  l->maxy = tmp_maxy;
}
