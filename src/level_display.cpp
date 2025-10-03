//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game_popups.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"

static void level_display_cursor(Gamep g, Levelsp v, Levelp l, spoint p)
{
  TRACE_NO_INDENT();

  Tpp tp = nullptr;

  switch (v->cursor[ p.x ][ p.y ]) {
    case CURSOR_NONE :
      //
      // Normal case. No cursor or anything else here.
      //
      return;
    case CURSOR_PATH :
      {
        //
        // No paths over a chasm
        //
        if (level_is_cursor_path_none(g, v, l, p)) {
          return;
        }

        //
        // No cursor path during level selection
        //
        if (l->level_num == LEVEL_SELECT_ID) {
          return;
        }

        //
        // If the player is dead, then don't show the move path, but do allow them to move
        // the cursor around so they can still look at the level/cause of death.
        //
        auto player = thing_player(g);
        if (player && thing_is_dead(player)) {
          break;
        }

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
    spoint   tl, br;
    uint16_t tile_index;
    thing_get_coords(g, v, l, p, tp, NULL_THING, &tl, &br, &tile_index);
    thing_display(g, v, l, tp, NULL_THING, tl, br, tile_index);
  }
}

static void level_display_slot(Gamep g, Levelsp v, Levelp l, spoint p, int slot, int depth)
{
  TRACE_NO_INDENT();

  Tpp  tp;
  auto t = thing_and_tp_get_at(g, v, l, p, slot, &tp);
  if (! tp) {
    return;
  }

  if (thing_is_falling(t)) {
    if (depth != MAP_Z_DEPTH_FLOOR) {
      return;
    }
  } else if (tp_z_depth_get(tp) != depth) {
    return;
  }

  spoint   tl, br;
  uint16_t tile_index;
  thing_get_coords(g, v, l, p, tp, t, &tl, &br, &tile_index);
  thing_display(g, v, l, tp, t, tl, br, tile_index);
}

void level_display(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  //
  // What level is the player on?
  //
  auto player = thing_player(g);
  if (! player) {
    ERR("No player");
    return;
  }

  //
  // Soft scroll to the player
  //
  level_scroll_to_focus(g, v, l);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glcolor(WHITE);

  int fbo = FBO_MAP;
  blit_fbo_bind(fbo);
  glClear(GL_COLOR_BUFFER_BIT);
  blit_init();

  //
  // Display tiles in z prio order
  //
  FOR_ALL_MAP_Z_DEPTH(z_depth)
  {
    for (auto y = v->miny; y < v->maxy; y++) {
      for (auto x = v->minx; x < v->maxx; x++) {

        spoint p(x, y);
        auto   display_tile = false;

        if (l->level_num == LEVEL_SELECT_ID) {
          //
          // No lighting in level selection
          //
          display_tile = true;
        } else if (thing_vision_can_see_tile(g, v, l, player, p)) {
          //
          // Can see currently
          //
          display_tile = true;
        } else if (thing_vision_has_seen_tile(g, v, l, player, p)) {
          //
          // Has seen previously
          //
          display_tile = true;
          if (level_is_blit_never_monochrome(g, v, l, p)) {
            //
            // Show in normal colors
            //
          } else {
            g_monochrome = true;
          }
        }

        if (display_tile) {
          for (auto slot = 0; slot < MAP_SLOTS; slot++) {
            level_display_slot(g, v, l, p, slot, z_depth);
          }
        }

        g_monochrome = false;
      }
    }
  }

  //
  // Top level cursor
  //
  for (auto y = v->miny; y < v->maxy; y++) {
    for (auto x = v->minx; x < v->maxx; x++) {
      spoint p(x, y);
      level_display_cursor(g, v, l, p);
    }
  }

  blit_flush();

  game_popups_display(g, v, l);
}
