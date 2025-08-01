//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_main.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
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

  //
  // Wait for events
  //
  int ui_ts_fast_last      = time_ms();
  int ui_ts_slow_last      = ui_ts_fast_last;
  int ui_ts_very_slow_last = ui_ts_fast_last;

  g_main_loop_running = true;

  // gl_enter_2d_mode(g);

#ifdef ENABLE_UI_ASCII_MOUSE
  SDL_ShowCursor(0);
#endif

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
        CON(UI_IMPORTANT_FMT_STR "An error occurred. Check the logs above." UI_RESET_FMT);
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
      if (found) {
        if (found > 1) {
          DBG("SDL: Process %u events", found);
        } else {
          DBG("SDL: Process %u event", found);
        }
      }

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
            if (time_have_x_hundredths_passed_since(50, sdl.last_mouse_held_down_when)) {
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

      //
      // Per tick state handling
      //
      game_tick(g);
    }

    //
    // Display the level
    //
    {
      glcolor(WHITE);
      gl_enter_2d_mode(g, game_map_fbo_width_get(g), game_map_fbo_height_get(g));
      game_display(g);
      blit_fbo_unbind();
      gl_enter_2d_mode(g, game_window_pix_width_get(g), game_window_pix_height_get(g));
    }

    //
    // Display the FBOs
    //
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
        fps_ts_now    = time_ms();
        uint32_t diff = fps_ts_now - fps_ts_begin;
        if (diff != 0) {
          float fps = (float) (frames * ONESEC) / (float) diff;
          CON("FPS %f", fps);
          game_fps_value_set(g, (int) fps);
        } else {
          CON("FPS calculating...");
          game_fps_value_set(g, (int) 0);
        }
        fps_ts_begin = fps_ts_now;
        frames       = 0;
      }
    }
  }

  DBG("Exited main loop");

  gl_leave_2d_mode(g);

#ifdef ENABLE_UI_ASCII_MOUSE
  SDL_ShowCursor(1);
#endif
}
