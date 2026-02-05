//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"

void thing_display_get_tile_info(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp_maybe_null, Thingp t_maybe_null,
                                 spoint *tl, spoint *br, uint16_t *tile_index)
{
  TRACE_NO_INDENT();

  int   zoom = game_map_zoom_get(g);
  int   dw   = TILE_WIDTH * zoom;
  int   dh   = TILE_HEIGHT * zoom;
  Tilep tile = nullptr;

  tile = thing_display_get_tile_info(g, v, l, p, tp_maybe_null, t_maybe_null);
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
  } else if (tp_maybe_null) {
    //
    // Cursor usually
    //
    tile = tp_tiles_get(tp_maybe_null, THING_ANIM_IDLE, 0);

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

  auto pix_height = tile_height(tile) * zoom;
  auto pix_width  = tile_width(tile) * zoom;

  //
  // Centered
  //
  if (tp_maybe_null && tp_is_blit_centered(tp_maybe_null)) {
    tl->x -= (pix_width - dw) / 2;
    tl->y -= (pix_height - dh) / 2;
  }

  if (tp_maybe_null && tp_is_blit_on_ground(tp_maybe_null)) {
    tl->x -= (pix_width - dw) / 2;
    tl->y -= (pix_height - dh);
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
  if (t_maybe_null && tp_is_animated_can_hflip(tp_maybe_null)) {
    if (thing_is_dir_left(t_maybe_null) || thing_is_dir_tl(t_maybe_null) || thing_is_dir_bl(t_maybe_null)) {
      std::swap(tl->x, br->x);
    }
  }

  //
  // Update submerged status
  //
  if (t_maybe_null && tp_is_submergible(tp_maybe_null)) {
    (void) thing_submerged_pct_set(g, v, l, t_maybe_null, 0);
    if (level_is_deep_water(g, v, l, p)) {
      (void) thing_submerged_pct_set(g, v, l, t_maybe_null, 80);
    } else if (level_is_water(g, v, l, p)) {
      (void) thing_submerged_pct_set(g, v, l, t_maybe_null, 50);
    } else if (level_is_lava(g, v, l, p)) {
      (void) thing_submerged_pct_set(g, v, l, t_maybe_null, 40);
    }
  }
}

//
// Solid black outline
//
static void thing_display_outlined_blit(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp, Thingp t_maybe_null,
                                        spoint tl, spoint br, Tilep tile, float x1, float x2, float y1, float y2,
                                        FboEnum fbo, color fg)
{
  TRACE_NO_INDENT();

  const color outline = BLACK;

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

  if (tp_is_blit_outlined(tp)) {
    tile_blit_outlined(tile, x1, x2, y1, y2, tl, br, fg, outline, single_pix_size, false);
  } else if (tp_is_blit_square_outlined(tp)) {
    tile_blit_outlined(tile, x1, x2, y1, y2, tl, br, fg, outline, single_pix_size, true);
  }
}

//
// Show an outline if obscured? e.g. foliage and the player hiding in it
//
[[nodiscard]] static bool thing_display_outline_blit(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp,
                                                     Thingp t_maybe_null, spoint tl, spoint br, Tilep tile, float x1,
                                                     float x2, float y1, float y2, FboEnum fbo, color fg)
{
  TRACE_NO_INDENT();

  if (level_is_blit_obscures(g, v, l, p)) {
    if (tp_is_blit_when_obscured(tp)) {
      color c = CYAN;
      c.a     = 230;
      tile_blit_outline(tile, x1, x2, y1, y2, tl, br, c);
      return true;
    }
  }

  return false;
}

static void thing_display_blit(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp, Thingp t_maybe_null, spoint tl,
                               spoint br, Tilep tile, float x1, float x2, float y1, float y2, FboEnum fbo, color fg,
                               LightPixels *light_pixels = nullptr, bool blit_flush_per_line = false)
{
  TRACE_NO_INDENT();

  switch (fbo) {
    case FBO_MAP_FG_OVERLAY :

      //
      // Things like exits and entrances are shown in color once seen
      //
      if (! tp_is_blit_shown_in_overlay(tp)) {
        return;
      }

      if (thing_display_outline_blit(g, v, l, p, tp, t_maybe_null, tl, br, tile, x1, x2, y1, y2, fbo, fg)) {
        return;
      }

      break;

    default : break;
  }

  //
  // light_pixels is set for things like floors and walls, and blits the tile as lots of individual
  // pixels with their own lighting
  //

  if (tp_is_blit_outlined(tp) || tp_is_blit_square_outlined(tp)) {
    thing_display_outlined_blit(g, v, l, p, tp, t_maybe_null, tl, br, tile, x1, x2, y1, y2, fbo, fg);
  } else {
    tile_blit(tile, x1, x2, y1, y2, tl, br, fg, light_pixels, blit_flush_per_line);
  }
}

//
// Display a spinning falling thing
//
static void thing_display_falling(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp, Thingp t, spoint tl, spoint br,
                                  Tilep tile, float x1, float x2, float y1, float y2, FboEnum fbo, color fg)
{
  TRACE_NO_INDENT();

  int fall_height = thing_is_falling(t);

  int dh = (int) (((0.5 * ((float) (br.y - tl.y))) / MAX_FALL_TIME_MS) * fall_height);
  tl.x += dh;
  tl.y += dh;
  br.x -= dh;
  br.y -= dh;

  auto mid = (tl + br) / (short) 2;
  blit_flush();
  glPushMatrix();
  glTranslatef(mid.x, mid.y, 0);
  float ang = dh * 10;
  glRotatef(ang, 0.0f, 0.0f, 1.0f);
  glTranslatef(-mid.x, -mid.y, 0);
  thing_display_blit(g, v, l, p, tp, t, tl, br, tile, x1, x2, y1, y2, fbo, fg);
  blit_flush();
  glPopMatrix();
}

//
// Display a spinning thing
//
static void thing_display_rotated(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp, Thingp t, spoint tl, spoint br,
                                  Tilep tile, float x1, float x2, float y1, float y2, FboEnum fbo, color fg)
{
  TRACE_NO_INDENT();

  auto mid = (tl + br) / (short) 2;
  blit_flush();
  glPushMatrix();
  glTranslatef(mid.x, mid.y, 0);
  float ang = t->angle * (180.0f / RAD_180);
  glRotatef(ang, 0.0f, 0.0f, 1.0f);
  glTranslatef(-mid.x, -mid.y, 0);
  thing_display_blit(g, v, l, p, tp, t, tl, br, tile, x1, x2, y1, y2, fbo, fg);
  blit_flush();
  glPopMatrix();
}

//
// Display a single thing to an FBO
//
void thing_display(Gamep g, Levelsp v, Levelp l, spoint p, Tpp tp, Thingp t_maybe_null, spoint tl, spoint br,
                   uint16_t tile_index, FboEnum fbo)
{
  TRACE_NO_INDENT();

  bool is_falling = false;

  auto player = thing_player(g);
  if (unlikely(! player)) {
    return;
  }

  //
  // What level are we currently displaying?
  //
  const auto is_level_select = level_is_level_select(g, v, l);

  if (t_maybe_null) {
    is_falling = thing_is_falling(t_maybe_null) > 0;
  }

  if (DEBUG || is_level_select) {
    //
    // No hiding of objects
    //
  } else {
    //
    // What level is the player on?
    //
    auto player_level = game_level_get(g, v, player->level_num);
    if (unlikely(! player_level)) {
      return;
    }

    //
    // If we're blitting the level below, filter to only things we can see through chasms
    //
    if (player_level != l) {
      if (! tp_is_blit_shown_in_chasms(tp)) {
        return;
      }
    }

    if (t_maybe_null && ! thing_vision_can_see_tile(g, v, player_level, player, p)) {
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
      } else if (is_falling) {
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
  }

  auto tile = tile_index_to_tile(tile_index);
  if (! tile) {
    return;
  }

  color fg = WHITE;
  float x1;
  float x2;
  float y1;
  float y2;
  tile_coords(tile, &x1, &y1, &x2, &y2);

  LightPixels *light_pixels = nullptr;

  if (is_level_select) {
    //
    // No lighting
    //
    fg = WHITE;
  } else if (thing_vision_can_see_tile(g, v, l, player, p)) {
    //
    // Apply lighting to current tiles
    //
    if (fbo == FBO_MAP_FG) {
      auto pixel = &v->light_map.tile[ p.x ][ p.y ].pixels.pixel[ 0 ][ 0 ];
      fg.r       = pixel->r > 255 ? 255 : (uint8_t) (int) pixel->r;
      fg.g       = pixel->g > 255 ? 255 : (uint8_t) (int) pixel->g;
      fg.b       = pixel->b > 255 ? 255 : (uint8_t) (int) pixel->b;

      //
      // Too many tiny tiles
      //
      if (! game_map_zoom_is_full_map_visible(g)) {
        light_pixels = &v->light_map.tile[ p.x ][ p.y ].pixels;
      }

      //
      // Can only light things that are exactly on pixel boundaries
      //
      if (! tp_is_blit_pixel_lighting(tp)) {
        light_pixels = nullptr;
      }

      if (tile_width(tile) != LIGHT_PIXEL) {
        light_pixels = nullptr;
      }
    } else {
      fg = WHITE;
    }
  } else {
    //
    // Default color, which might be monochrome for non visited tiles
    //
  }

  if (t_maybe_null) {
    //
    // Handle various effects
    //
    if (is_falling) {
      thing_display_falling(g, v, l, p, tp, t_maybe_null, tl, br, tile, x1, x2, y1, y2, fbo, fg);
      return;
    }

    int submerged_pct;
    if ((submerged_pct = thing_submerged_pct(t_maybe_null))) {
      //
      // Submerge the tile if it is over some kind of liquid.
      //
      if (submerged_pct) {
        tile_blit_apply_submerge_pct(g, tl, br, x1, x2, y1, y2, thing_submerged_pct(t_maybe_null));
        thing_display_blit(g, v, l, p, tp, t_maybe_null, tl, br, tile, x1, x2, y1, y2, fbo, fg);

        //
        // Add a reflection
        //
        if (fbo != FBO_MAP_FG_OVERLAY) {
          fg.a /= 8;
          fg.r /= 2;
          fg.g /= 2;
          fg.b /= 2;
          light_pixels = nullptr;
          auto h       = br.y - tl.y;
          std::swap(br.y, tl.y);
          tl.y += h;
          br.y += h;
        }
      }
    }
  }

  IF_DEBUG
  {
    light_pixels = nullptr;
    fg.r         = 255;
    fg.g         = 255;
    fg.b         = 255;
  }

  if (t_maybe_null) {
    //
    // Flash if hit
    //
    if (thing_is_hit(t_maybe_null)) {
      //
      // Preserve original alpha
      //
      color flash  = ORANGE;
      fg.r         = flash.r;
      fg.g         = flash.g;
      fg.b         = flash.b;
      light_pixels = nullptr;
    }

    if (thing_is_hot(t_maybe_null)) {
      //
      // Preserve original alpha
      //
      auto  pulse = thing_is_hot(t_maybe_null);
      color flash = RED;
      fg.r        = flash.r;
      if (pulse < 128) {
        pulse = 255 - pulse;
      }
      fg.g = pulse;
      fg.b = pulse;

      light_pixels = nullptr;
    }

    //
    // Rotate when falling
    //
    if (t_maybe_null->angle != 0.0) {
      thing_display_rotated(g, v, l, p, tp, t_maybe_null, tl, br, tile, x1, x2, y1, y2, fbo, fg);
      return;
    }

    //
    // If we have alpha values in the texture, the end of one triangle line and the start of another creates
    // a visible strip
    //
    bool is_blit_flush_per_line = thing_is_blit_flush_per_line(t_maybe_null);
    thing_display_blit(g, v, l, p, tp, t_maybe_null, tl, br, tile, x1, x2, y1, y2, fbo, fg, light_pixels,
                       is_blit_flush_per_line);

    //
    // Flash red outline if hit
    //
    if (thing_is_hit(t_maybe_null)) {
      color outline = RED;
      int   a       = (int) (((float) thing_is_hit(t_maybe_null) / (float) MAX_HIT_TIME_MS) * 255.0);
      if (a > 255) {
        a = 255;
      }
      outline.a = (uint8_t) a;
      tile_blit_outline(tile, x1, x2, y1, y2, tl, br, outline);
    }
  } else {
    //
    // Probably the cursor
    //
    thing_display_blit(g, v, l, p, tp, t_maybe_null, tl, br, tile, x1, x2, y1, y2, fbo, fg, nullptr, false);
  }
}
