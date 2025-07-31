//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_font.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_string.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_ui.hpp"

static void thing_blit_text(Gamep g, Levelsp v, Levelp l, spoint tl, spoint br, std::string const &text,
                            color fg = WHITE)
{
  TRACE_NO_INDENT();

  int len = length_without_format(text);

  if (br.x < tl.x) {
    std::swap(tl, br);
    std::swap(tl.y, br.y);
  }
  auto w = br.x - tl.x;

  br.x -= (len - 1) * w;
  tl.x -= (len - 1) * w;

  br.x += (len / 2) * w;
  tl.x += (len / 2) * w;

  bool found_format_string = false;
  char c;
  auto text_start = text.begin();
  auto text_iter  = text_start;

  for (;;) {
    Tilep tile = nullptr;

    c = *text_iter;
    if (! c) {
      break;
    }

    if (! found_format_string) {
      if (c == '%') {
        found_format_string = true;
        continue;
      }
    } else if (found_format_string) {
      if (std::string(text_iter, text_iter + 3) == "fg=") {
        text_iter += 3;
        auto tmp = std::string(text_iter, text.end());

        int tmplen = 0;
        fg         = string2color(tmp, &tmplen);
        text_iter += tmplen + 1;

        found_format_string = false;
        continue;
      }
      if (std::string(text_iter, text_iter + 3) == "bg=") {
        text_iter += 3;
        auto tmp = std::string(text_iter, text.end());

        int tmp_len = 0;
        (void) string2color(tmp, &tmp_len);
        text_iter += tmp_len + 1;

        found_format_string = false;
        continue;
      }
      if (std::string(text_iter, text_iter + 4) == "tex=") {
        text_iter += 4;
        auto tmp = std::string(text_iter, text.end());

        int tmp_len = 0;
        (void) string2tex(tmp, &tmp_len);
        text_iter += tmp_len + 1;

        found_format_string = false;
        continue;
      }
      if (std::string(text_iter, text_iter + 3) == "tp=") {
        text_iter += 3;
        auto tmp = std::string(text_iter, text.end());

        int         tmp_len = 0;
        const char *tmpc    = tmp.c_str();
        auto        tp      = string2tp(&tmpc, &tmp_len);
        text_iter += tmp_len + 1;

        tile                = tp_first_tile(tp, THING_ANIM_IDLE);
        found_format_string = false;
        continue;
      }
      if (std::string(text_iter, text_iter + 5) == "tile=") {
        text_iter += 5;
        auto tmp = std::string(text_iter, text.end());

        int tmp_len = 0;
        tile        = string2tile(tmp, &tmp_len);
        text_iter += tmp_len + 1;

        found_format_string = false;
        continue;
      }
      if (c == '%') {
        // line_len -= 1;
      } else {
        found_format_string = false;
        text_iter--;
      }

      text_iter++;
      continue;
    }

    text_iter++;

    if (! tile) {
      tile = font_ui->font_get_tile(c);
      if (! tile) {
        tile = tile_find_mand(FONT_TILENAME_UNKNOWN_STR);
      }
    }

    tile_blit(tile, tl, br, fg);
    tl.x += w;
    br.x += w;
  }
  glcolor(WHITE);
}

void thing_display(Gamep g, Levelsp v, Levelp l, Tpp tp, Thingp t, uint16_t tile_index, spoint tl, spoint br)
{
  TRACE_NO_INDENT();

  auto tile = tile_index_to_tile(tile_index);
  if (! tile) {
    return;
  }

  if (0) {
    if (t && thing_is_player(t)) {
      thing_blit_text(g, v, l, tl, br, "123", RED);
    }
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
