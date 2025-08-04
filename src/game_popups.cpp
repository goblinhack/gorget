//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_game_popups.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_time.hpp"

void game_popup_text_add(Gamep g, int x, int y, std::string &text, color c)
{
  TRACE_NO_INDENT();

  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }

  if (is_oob(x, y)) {
    ERR("Text is oob");
    return;
  }

  auto      l = game_popups_get(g, x, y);
  GamePopup popup;
  popup.text    = text;
  popup.created = time_ms_cached();
  popup.fg      = c;
  l->push_front(popup);
}

void game_popups_age(Gamep g)
{
  TRACE_NO_INDENT();

  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      if (! game_popups_present(g, x, y)) {
        continue;
      }

      //
      // Age out popups
      //
      std::list< GamePopup > out;
      for (auto i : *game_popups_get(g, x, y)) {
        if (! time_have_x_ms_passed_since(POPUP_DURATION_MS, i.created)) {
          out.push_back(i);
        }
      }

      game_popups_set(g, x, y, out);
    }
  }
}

void game_popups_display(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      if (! game_popups_present(g, x, y)) {
        continue;
      }

      spoint last_tl;
      spoint last_br;

      for (auto i : *game_popups_get(g, x, y)) {
        uint16_t tile_index;
        spoint   p(x, y);
        spoint   tl;
        spoint   br;

        //
        // Get the coords of the tile on the map this text would be over
        //
        static Tpp tp_once;
        if (! tp_once) {
          tp_once = tp_find_mand("cursor_path");
        }
        thing_get_coords(g, v, l, p, tp_once, NULL_THING, &tl, &br, &tile_index);

        //
        // Fade out and raise the text up with a percentage
        //
        float pct = (float) (time_ms_cached() - i.created) / (float) POPUP_DURATION_MS;

        //
        // Fade out
        //
        color fg = i.fg;
        color bg = BLACK;

        fg.a = 255 - (int) (255.0 * pct / 2);
        bg.a = 255 - (int) (255.0 * pct);

        //
        // Rise up
        //
        auto tile_height = br.y - tl.y;
        auto h           = (int) (pct * (float) tile_height * POPUP_DURATION_TILE_HEIGHT);
        tl.y -= h;
        br.y -= h;

        //
        // Start the text above the player
        //
        tl.y -= tile_height;
        br.y -= tile_height;

        //
        // Avoid overlapping popups
        while ((tl.y >= last_tl.y) && (tl.y <= last_br.y)) {
          tl.y -= tile_height / 2;
          br.y -= tile_height / 2;
        }

        blit_init();
        thing_blit_text(g, v, l, tl, br, i.text, bg, true /* outline */);
        blit_flush();
        blit_init();
        thing_blit_text(g, v, l, tl, br, i.text, fg, false /* outline */);
        blit_flush();

        last_tl = tl;
        last_br = br;
      }
    }
  }
}

void game_popups_clear(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      if (! game_popups_present(g, x, y)) {
        continue;
      }

      auto l = game_popups_get(g, x, y);
      l->clear();
    }
  }
}
