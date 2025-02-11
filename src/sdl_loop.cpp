//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_font.hpp"
#include "my_game.hpp"
#include "my_gfx.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_tex.hpp"
#include "my_tile.hpp"
#include "my_ui.hpp"
#include "my_wid_console.hpp"

//
// Main loop
//
void sdl_loop(Gamep g)
{
  TRACE_NO_INDENT();
  DBG("SDL: main loop");

  //
  // Keep this lowish to avoid too much lag when processing mouse motion events, that redraw the cursor path.
  //
  // 2 - seems too slow as it adds a noticeable lag when you do a wheel mouse event after a lot of mouse moves.
  // 3 - still some lag
  // 4 - seems ok
  // 10 - too much lag now due to cursor redraws
  //
  SDL_Event events[ 6 ] = {};
  int       found       = 0;
  int       i           = 0;
  int       frames      = 0;

  sdl_mouse_center(g);
  SDL_SetEventFilter(sdl_filter_events, nullptr);

  glEnable(GL_TEXTURE_2D);

  //
  // Wait for events
  //
  int ui_ts_fast_last      = time_ms();
  int ui_ts_slow_last      = ui_ts_fast_last;
  int ui_ts_very_slow_last = ui_ts_fast_last;

  g_main_loop_running = true;

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  GL_ERROR_CHECK();

  if (game_gfx_vsync_enable_get(g)) {
    SDL_GL_SetSwapInterval(1);
  } else {
    SDL_GL_SetSwapInterval(0);
  }
  GL_ERROR_CHECK();

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  GL_ERROR_CHECK();

  gl_enter_2d_mode(g);

#ifdef ENABLE_UI_ASCII_MOUSE
  SDL_ShowCursor(0);
#endif

  //
  // Causes a 0.3 sec delay first time it seems to run
  //
  SDL_PumpEvents();

  for (; /*ever*/;) {
    // DBG("SDL: tick");

    frames++;

    //
    // Reset joystick handling before we poll and update.
    //
    if (unlikely(sdl.joy_axes != nullptr)) {
      sdl_tick(g);
    }

    static bool old_g_errored;
    if (unlikely(g_errored)) {
      if (g_errored != old_g_errored) {
        CON("%%fg=red$An error occurred. Check the logs above.%%fg=reset$");
        CON("To dismiss this console, press TAB.");
        CON("To continue playing at your own risk, try 'clear errored'");
        if (wid_console_window && ! wid_is_visible(wid_console_window)) {
          wid_visible(g, wid_console_window);
          wid_raise(g, wid_console_window);
        }
      }
    }
    old_g_errored = g_errored;

    //
    // Various event frequencies
    //
    int  ts_now           = time_ms();
    bool update_very_slow = (ts_now - ui_ts_very_slow_last >= UI_EVENT_LOOP_FREQ_VERY_SLOW_MS);
    bool update_slow      = (ts_now - ui_ts_slow_last >= UI_EVENT_LOOP_FREQ_SLOW_MS);
    bool update_fast      = (ts_now - ui_ts_fast_last >= UI_EVENT_LOOP_FREQ_FAST_MS);

    //
    // Check for clock reset due to leaving robot mode
    //
    if ((ts_now < ui_ts_fast_last) || (ts_now < ui_ts_slow_last) || (ts_now < ui_ts_very_slow_last)) {
      ui_ts_fast_last      = time_ms();
      ui_ts_slow_last      = ui_ts_fast_last;
      ui_ts_very_slow_last = ui_ts_fast_last;
    }

    //
    // This is for when in pixel art mode and between levels and waiting for level fade in
    //
    if (unlikely(update_very_slow)) {
      ui_ts_very_slow_last = ts_now;
      wid_display_all(g);
    }

    //
    // Less frequent updates like updating the FPS
    //
    if (unlikely(update_slow)) {
      ui_ts_slow_last = ts_now;
    }

    //
    // Do faster processing of events, like reading the keyboard and updating widgets.
    //
    if (unlikely(update_fast)) {
      ui_ts_fast_last = ts_now;

      //
      // Clean up dead widgets.
      //
      wid_gc_all(g);

      //
      // Read events
      //
      SDL_PumpEvents();

      sdl.wheel_x = 0;
      sdl.wheel_y = 0;

      found = SDL_PeepEvents(events, ARRAY_SIZE(events), SDL_GETEVENT, SDL_QUIT, SDL_LASTEVENT);

      //
      // Only process one mouse motion event; and when we do we only look at the latest
      // mouse position, to avoid perception of lag. Mouse motion events can be expensive
      // as we redraw the cursor path.
      //
      DBG("SDL: Process %u events", found);
      bool processed_mouse_motion_event = false;
      for (i = 0; i < found; ++i) {
        sdl_event(g, &events[ i ], processed_mouse_motion_event);
      }

      //
      // Handle key auto repeat
      //
      sdl_key_repeat_events(g);

      //
      // Mouse held?
      //
      if (unlikely(! found)) {
        auto mouse_down = sdl_get_mouse();
        if (mouse_down) {
          if (sdl.last_mouse_held_down_when) {
            if (time_have_x_hundredths_passed_since(10, sdl.last_mouse_held_down_when)) {
              if (sdl.held_mouse_x && sdl.held_mouse_y) {
                DBG2("SDL: Mouse DOWN: held: Button %d now at %d,%d initially at %d,%d", mouse_down, sdl.mouse_x,
                     sdl.mouse_y, sdl.held_mouse_x, sdl.held_mouse_y);
                wid_mouse_held(g, sdl.mouse_down, sdl.held_mouse_x, sdl.held_mouse_y);
                sdl.held_mouse_x = 0;
                sdl.held_mouse_y = 0;
              } else {
                DBG2("SDL: Mouse DOWN: held: Button %d now at %d,%d", sdl.mouse_down, sdl.mouse_x, sdl.mouse_y);
                wid_mouse_held(g, sdl.mouse_down, sdl.mouse_x, sdl.mouse_y);
              }
            }
          }
        }
      }

      //
      // Screenshot?
      //
      if (unlikely(! g_do_screenshot)) {
        if (unlikely(! g_main_loop_running)) {
          DBG("Exit main loop");
          break;
        }
      }

      //
      // If the user has moved the mouse, update the widgets.
      //
      if (processed_mouse_motion_event) {
        wid_display_all(g);
      }
    }

    gl_enter_2d_mode(g, game_pix_width_get(g), game_pix_height_get(g));

    glcolor(WHITE);
    game_display(g);
    blit_fbo_unbind();

    gl_enter_2d_mode(g, game_window_pix_width_get(g), game_window_pix_height_get(g));

    sdl_display(g);

    //
    // Config change?
    //
    if (unlikely(g_need_restart)) {
      LOG("Restart needed");
      break;
    }

    //
    // Update FPS counter.
    //
    if (unlikely(game_fps_counter_get(g))) {
      static uint32_t fps_ts_begin;
      static uint32_t fps_ts_now;

      if (unlikely(! fps_ts_begin)) {
        fps_ts_begin = time_ms();
      }

      if (unlikely(frames >= 100)) {
        fps_ts_now = time_ms();
        auto  diff = fps_ts_now - fps_ts_begin;
        float fps  = (float) (frames * ONESEC) / (float) diff;
        CON("FPS %f ", fps);
        game_fps_value_set(g, (int) fps);
        fps_ts_begin = fps_ts_now;
        frames       = 0;
      }
    }

    //
    // Fixed frame counter, 100 per second
    //
    auto level = game_levels_get(g);
    if (level) {
      static uint32_t level_ts_begin;
      static uint32_t level_ts_now;

      if (unlikely(! level_ts_begin)) {
        level_ts_begin = time_ms();
      }

      level_ts_now = time_ms();
      level->frame += level_ts_now - level_ts_begin;
      level_ts_begin = level_ts_now;
    }
  }

  DBG("Exited main loop");

  gl_leave_2d_mode(g);

#ifdef ENABLE_UI_ASCII_MOUSE
  SDL_ShowCursor(1);
#endif
}
