//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_font.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"

void thing_display_get_tile_info(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp, Thingp t_maybe_null, spoint *tl,
                                 spoint *br, uint16_t *tile_index)
{
  TRACE_NO_INDENT();

  int   zoom = game_map_zoom_get(g);
  int   dw   = INNER_TILE_WIDTH * zoom;
  int   dh   = INNER_TILE_HEIGHT * zoom;
  Tilep tile = nullptr;

  tile = thing_display_get_tile_info(g, v, l, p, tp, t_maybe_null);
  if (tile) {
    //
    // Allow override of the tile
    //
    if (tile_index) {
      *tile_index = tile_global_index(tile);
    }
  } else if (t_maybe_null) {
    //
    // Things
    //
    if (tile_index) {
      *tile_index = t_maybe_null->tile_index;
    }
  } else if (tp) {
    //
    // Cursor usually
    //
    tile = tp_tiles_get(tp, THING_ANIM_IDLE, 0);

    if (tile_index) {
      *tile_index = tile_global_index(tile);
    }
  } else {
    static Tilep no_tile;
    if (! no_tile) {
      no_tile = tile_find_mand("none");
    }
    tile = no_tile;

    if (tile_index) {
      *tile_index = tile_global_index(tile);
    }
  }

  if (tile_index) {
    tile = tile_index_to_tile(*tile_index);
  }

  if (! tile) {
    tile = tile_find_mand("none");
  }

  auto pix_height = tile_height(tile) * zoom;
  auto pix_width  = tile_width(tile) * zoom;

  if (t_maybe_null) {
    //
    // All things
    //
    *tl = thing_pix_at(t_maybe_null);
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

  if (t_maybe_null && thing_is_jumping(t_maybe_null)) {
    auto jump_height = (int) ((sin(PI * t_maybe_null->thing_dt)) * (float) dh);
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
  if (t_maybe_null && tp_is_animated_can_hflip(tp)) {
    if (thing_is_dir_left(t_maybe_null) || thing_is_dir_tl(t_maybe_null) || thing_is_dir_bl(t_maybe_null)) {
      std::swap(tl->x, br->x);
    }
  }

  //
  // Update submerged status
  //
  if (t_maybe_null && tp_is_submergible(tp)) {
    thing_submerged_pct_set(g, v, l, t_maybe_null, 0);
    if (level_is_deep_water(g, v, l, p)) {
      thing_submerged_pct_set(g, v, l, t_maybe_null, 80);
    } else if (level_is_water(g, v, l, p)) {
      thing_submerged_pct_set(g, v, l, t_maybe_null, 50);
    } else if (level_is_lava(g, v, l, p)) {
      thing_submerged_pct_set(g, v, l, t_maybe_null, 40);
    }
  }
}

//
// Display a single thing to an FBO
//
void thing_display(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp, Thingp t_maybe_null, spoint tl, spoint br,
                   uint16_t tile_index, int fbo)
{
  TRACE_NO_INDENT();

  auto player = thing_player(g);
  if (! player) {
    return;
  }

  auto player_level = game_level_get(g, v, player->level_num);
  if (! player_level) {
    return;
  }

  //
  // If the thing is falling, do not show it in the overlay, else it appears in front of floor tiles
  //
  if (t_maybe_null && (fbo == FBO_MAP_FG_OVERLAY)) {
    if (thing_is_falling(t_maybe_null)) {
      return;
    }
  }

  const auto is_level_select = level_is_level_select(g, v, player_level);

  if (DEBUG || is_level_select) {
    //
    // No hiding of oobjects
    //
  } else if (t_maybe_null && ! thing_vision_can_see_tile(g, v, player_level, player, p)) {
    //
    // We cannot see this tile currently.
    //
    if (level_is_blit_if_has_seen(g, v, player_level, p)) {
      //
      // But if it has been seen, then show it, if allowed.
      //
      // Note that we use the level_ version. This is because you could have flames and a mob
      // on the same tile. We would only see the flames without this check.
      //
    } else if (thing_is_falling(t_maybe_null)) {
      //
      // The thing is not currently seen and has not been seen previously.
      // If the thing is falling, always show it in the background, else things appear to vanish.
      //
    } else {
      //
      // The thing is not currently seen and has not been seen previously. Hide it.
      //
      return;
    }
  }

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

  if (t_maybe_null) {
    //
    // Handle various effects
    //
    int fall_height;
    int submerged_pct;
    if ((fall_height = thing_is_falling(t_maybe_null))) {
      //
      // Falling
      //
      int dh = (int) (((MAX_FALL_TILE_HEIGHT * ((float) (br.y - tl.y))) / MAX_FALL_TIME_MS) * fall_height);
      tl.y += dh;
      br.y += dh;
      // THING_TOPCON(t_maybe_null, "%d", dh);
    } else if ((submerged_pct = thing_submerged_pct(t_maybe_null))) {
      //
      // Submerge the tile if it is over some kind of liquid.
      //
      if (submerged_pct) {
        tile_submerge_pct(g, tl, br, x1, x2, y1, y2, thing_submerged_pct(t_maybe_null));
      }
    }
  }

  if (player_level != l) {
    //
    // The level below.
    //
    if (! tp_is_blit_in_chasm(tp)) {
      return;
    }
  } else if (is_level_select) {
    //
    // No lighting
    //
    fg = WHITE;
  } else if (thing_vision_can_see_tile(g, v, l, player, p)) {
    //
    // Apply lighting to current tiles
    //
    if (fbo == FBO_MAP_FG) {
      fg = v->light_map.tile[ p.x ][ p.y ].c;
    } else {
      fg = WHITE;
    }
  } else {
    //
    // Default color, which might be monochrome for non visited tiles
    //
  }

  if (tp_is_blit_outlined(tp)) {
    tile_blit_outline(tile, x1, x2, y1, y2, tl, br, fg, outline, single_pix_size, false);
  } else if (tp_is_blit_square_outlined(tp)) {
    tile_blit_outline(tile, x1, x2, y1, y2, tl, br, fg, outline, single_pix_size, true);
  } else {
    tile_blit(tile, x1, x2, y1, y2, tl, br, fg);
  }
}
