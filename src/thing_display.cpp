//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_font.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_math.hpp"

void thing_get_coords(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp, Thingp t, spoint *tl, spoint *br,
                      uint16_t *tile_index)
{
  TRACE_NO_INDENT();

  int zoom = game_map_zoom_get(g);
  int dw   = INNER_TILE_WIDTH * zoom;
  int dh   = INNER_TILE_HEIGHT * zoom;

  if (t) {
    //
    // Things
    //
    *tile_index = t->tile_index;
  } else if (tp) {
    //
    // Cursor
    //
    Tilep tile  = tp_tiles_get(tp, THING_ANIM_IDLE, 0);
    *tile_index = tile_global_index(tile);
  } else {
    static Tilep tile;
    if (! tile) {
      tile = tile_find_mand("none");
    }
    *tile_index = tile_global_index(tile);
  }

  auto tile = tile_index_to_tile(*tile_index);
  if (! tile) {
    tile = tile_find_mand("none");
  }
  auto pix_height = tile_height(tile) * zoom;
  auto pix_width  = tile_width(tile) * zoom;

  if (t) {
    //
    // All things
    //
    *tl = t->pix_at;
    tl->x *= zoom;
    tl->y *= zoom;
  } else {
    //
    // Cursor
    //
    tl->x = p.x * dw;
    tl->y = p.y * dh;
  }

  *tl -= v->pixel_map_at;

  if (tp && tp_is_blit_on_ground(tp)) {
    //
    // On the ground
    //
  } else if (tp && tp_is_blit_centered(tp)) {
    //
    // Centered
    //
    tl->x -= (pix_width - dw) / 2;
    tl->y -= (pix_height - dh) / 2;
  }

  if (t && thing_is_jumping(t)) {
    auto jump_height = (int) ((sin(PI * t->thing_dt)) * (float) dh);
    tl->y -= jump_height;
    br->y -= jump_height;
  }

  //
  // Update the br coords if we changed the position
  //
  br->x = tl->x + pix_width;
  br->y = tl->y + pix_height;

  //
  // Flippable?
  //
  if (tp && tp_is_animated_can_hflip(tp)) {
    if (thing_is_dir_left(t) || thing_is_dir_tl(t) || thing_is_dir_bl(t)) {
      std::swap(tl->x, br->x);
    }
  }

  //
  // Update submerged status
  //
  if (tp && tp_is_submergible(tp)) {
    thing_submerged_pct_set(g, v, l, t, 0);
    if (level_is_deep_water(g, v, l, p)) {
      thing_submerged_pct_set(g, v, l, t, 80);
    } else if (level_is_water(g, v, l, p)) {
      thing_submerged_pct_set(g, v, l, t, 50);
    } else if (level_is_lava(g, v, l, p)) {
      thing_submerged_pct_set(g, v, l, t, 40);
    }
  }
}

void thing_display(Gamep g, Levelsp v, Levelp l, Tpp tp, Thingp t, spoint tl, spoint br, uint16_t tile_index)
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
  if (game_map_zoom_is_full_map_visible(g)) {
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
      // THING_TOPCON(t, "%d", dh);
    } else if ((submerged_pct = thing_submerged_pct(t))) {
      //
      // Submerge the tile if it is over some kind of liquid.
      //
      if (submerged_pct) {
        tile_submerge_pct(g, tl, br, x1, x2, y1, y2, thing_submerged_pct(t));
      }
    }
  }

  //
  // Show the player as faded when teleporting
  //
  if (t && thing_is_teleporting(t)) {
    fg.a = 100;
  }

  if (tp_is_blit_outlined(tp)) {
    tile_blit_outline(tile, x1, x2, y1, y2, tl, br, fg, outline, single_pix_size, false);
  } else if (tp_is_blit_square_outlined(tp)) {
    tile_blit_outline(tile, x1, x2, y1, y2, tl, br, fg, outline, single_pix_size, true);
  } else {
    tile_blit(tile, x1, x2, y1, y2, tl, br);
  }
}
