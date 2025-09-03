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

void thing_blit_text(Gamep g, Levelsp v, Levelp l, spoint tl, spoint br, std::string const &text, color fg,
                     bool outline)
{
  TRACE_NO_INDENT();

  auto single_pix_size = game_map_single_pix_size_get(g);
  int  len             = length_without_format(text);

  if (br.x < tl.x) {
    std::swap(tl, br);
    std::swap(tl.y, br.y);
  }

  auto w  = br.x - tl.x;
  auto ow = w;
  auto h  = br.y - tl.y;
  auto oh = h;

  w = (int) (((float) w) / (float) POPUP_TEXT_SCALE_ACROSS);
  h = (int) (((float) h) / (float) POPUP_TEXT_SCALE_DOWN);

  auto pix_w = w * len;
  tl.x -= pix_w / 2;
  tl.x += ow / 2;

  br.x = tl.x + w;
  br.y = tl.y + h;

  tl.y += oh / 2;
  br.y = tl.y + h;

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

    if (outline) {
      float x1;
      float x2;
      float y1;
      float y2;
      tile_coords(tile, &x1, &y1, &x2, &y2);
      if (single_pix_size > 1) {
        tile_blit_outline(tile, x1, x2, y1, y2, tl, br, fg, BLACK, single_pix_size, true);
        tile_blit_outline(tile, x1, x2, y1, y2, tl + spoint(1, 0), br + spoint(1, 0), fg, BLACK, single_pix_size,
                          true);
        tile_blit_outline(tile, x1, x2, y1, y2, tl - spoint(1, 0), br - spoint(1, 0), fg, BLACK, single_pix_size,
                          true);
        tile_blit_outline(tile, x1, x2, y1, y2, tl + spoint(0, 1), br + spoint(0, 1), fg, BLACK, single_pix_size,
                          true);
        tile_blit_outline(tile, x1, x2, y1, y2, tl - spoint(0, 1), br - spoint(0, 1), fg, BLACK, single_pix_size,
                          true);
      }
    } else {
      tile_blit(tile, tl, br, fg);

      //
      // Text seems a bit skinny
      //
      if (single_pix_size > 1) {
        tile_blit(tile, tl + spoint(1, 0), br + spoint(1, 0), fg);
      }
    }

    tl.x += w;
    br.x += w;
  }
  glcolor(WHITE);
}
