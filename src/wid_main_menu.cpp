//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
// REMOVED #include "my_gl.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_wids.hpp"

WidPopup *wid_main_menu_window;

void wid_main_menu_destroy(Gamep g)
{
  TRACE_NO_INDENT();

  delete wid_main_menu_window;
  wid_main_menu_window = nullptr;
}

void wid_main_menu_hide(Gamep g)
{
  TRACE_NO_INDENT();

  if (! wid_main_menu_window) {
    return;
  }

  wid_hide(g, wid_main_menu_window->wid_popup_container);
}

static bool wid_main_menu_load(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_load_select(g);
  return true;
}

static bool wid_main_menu_cfg(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_options_menu_select(g);
  wid_main_menu_hide(g);
  return true;
}

static bool wid_main_menu_more(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_more_select(g);
  wid_main_menu_hide(g);
  return true;
}

static bool game_menu_new_game(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_main_menu_hide(g);
  wid_main_menu_destroy(g);
  wid_new_game(g);
  return false; // suppress mouse click
}

static bool wid_main_menu_quit(Gamep g, Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  wid_quit_select(g);
  wid_main_menu_destroy(g);
  return true;
}

static bool wid_main_menu_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
{
  TRACE_NO_INDENT();

  if (sdlk_eq(*key, game_key_console_get(g))) {
    sound_play(g, "keypress");
    return false;
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        default :
          {
            TRACE_NO_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case SDLK_RETURN :
              case ' ' :
              case 'n' :
              case 'N' :
                sound_play(g, "keypress");
                game_menu_new_game(g, nullptr, 0, 0, 0);
                return true;
              case 'l' :
              case 'L' :
                sound_play(g, "keypress");
                wid_main_menu_load(g, nullptr, 0, 0, 0);
                return true;
              case 'o' :
              case 'O' :
                sound_play(g, "keypress");
                wid_main_menu_cfg(g, nullptr, 0, 0, 0);
                return true;
              case 'm' :
              case 'M' :
                sound_play(g, "keypress");
                wid_main_menu_more(g, nullptr, 0, 0, 0);
                return true;
              case 'q' :
              case 'Q' :
                sound_play(g, "keypress");
                wid_main_menu_quit(g, nullptr, 0, 0, 0);
                return true;
            }
          }
      }
  }

  return false;
}

static void game_display_title_bg(Gamep g)
{
  TRACE_NO_INDENT();
  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::string t = "title_bg";
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), spoint(0, 0),
            spoint(game_window_pix_width_get(g), game_window_pix_height_get(g)), WHITE);
  blit_flush();
}

static void game_display_title_fg1(Gamep g)
{
  TRACE_NO_INDENT();

  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::string t = "title_fg1_1";
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), spoint(0, 0),
            spoint(game_window_pix_width_get(g), game_window_pix_height_get(g)), WHITE);
  blit_flush();
}

static void game_display_title_fg2(Gamep g)
{
  TRACE_NO_INDENT();

  static color fg    = WHITE;
  static int   delta = 10;
  static int   red   = 255;

  if (pcg_random_range(0, 100) < 50) {
    red += delta;
    if (red > 255) {
      delta = -delta;
      red   = 255;
    } else if (red < 200) {
      delta = -delta;
      red   = 200;
    }
  }

  fg.g = red;
  fg.b = red;
  glcolor(fg);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::string t = "title_fg2_1";
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), spoint(0, 0),
            spoint(game_window_pix_width_get(g), game_window_pix_height_get(g)), WHITE);
  blit_flush();
}

static uint8_t clamp(float v) // define a function to bound and round the input float value to 0-255
{
  if (v < 0)
    return 0;
  if (v > 255)
    return 255;
  return (uint8_t) v;
}

// https://stackoverflow.com/questions/8507885/shift-hue-of-an-rgb-color#8509802
color color_change_hue(const color &in, const float fHue)
{
  color       out;
  const float cosA = cos(fHue * 3.14159265f / 180); // convert degrees to radians
  const float sinA = sin(fHue * 3.14159265f / 180); // convert degrees to radians
  // calculate the rotation matrix, only depends on Hue
  float matrix[ 3 ][ 3 ]
      = {{cosA + (1.0f - cosA) / 3.0f, 1.0f / 3.0f * (1.0f - cosA) - sqrtf(1.0f / 3.0f) * sinA,
          1.0f / 3.0f * (1.0f - cosA) + sqrtf(1.0f / 3.0f) * sinA},
         {1.0f / 3.0f * (1.0f - cosA) + sqrtf(1.0f / 3.0f) * sinA, cosA + 1.0f / 3.0f * (1.0f - cosA),
          1.0f / 3.0f * (1.0f - cosA) - sqrtf(1.0f / 3.0f) * sinA},
         {1.0f / 3.0f * (1.0f - cosA) - sqrtf(1.0f / 3.0f) * sinA,
          1.0f / 3.0f * (1.0f - cosA) + sqrtf(1.0f / 3.0f) * sinA, cosA + 1.0f / 3.0f * (1.0f - cosA)}};
  // Use the rotation matrix to convert the RGB directly
  out.r = clamp(((float) in.r) * matrix[ 0 ][ 0 ] + ((float) in.g) * matrix[ 0 ][ 1 ]
                + ((float) in.b) * matrix[ 0 ][ 2 ]);
  out.g = clamp(((float) in.r) * matrix[ 1 ][ 0 ] + ((float) in.g) * matrix[ 1 ][ 1 ]
                + ((float) in.b) * matrix[ 1 ][ 2 ]);
  out.b = clamp(((float) in.r) * matrix[ 2 ][ 0 ] + ((float) in.g) * matrix[ 2 ][ 1 ]
                + ((float) in.b) * matrix[ 2 ][ 2 ]);
  return out;
}

static void game_display_title_fg3(Gamep g)
{
  TRACE_NO_INDENT();

  static color fg  = RED;
  static int   hue = 0;

  hue = 1;
  if (hue > 255) {
    hue = 0;
  }

  fg   = color_change_hue(fg, hue);
  fg.a = 255;

  if (fg.r + fg.g + fg.b < 100) {
    fg = RED;
  }

  float bright = (float) 1.01;
  int   r      = (int) (((float) fg.r) * bright);
  if (r > 255) {
    r = 255;
  }
  fg.r      = r;
  int green = (int) (((float) fg.g) * bright);
  if (green > 255) {
    green = 255;
  }
  fg.g  = green;
  int b = (int) (((float) fg.b) * bright);
  if (b > 255) {
    b = 255;
  }
  fg.b = b;

  glcolor(fg);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::string t = "title_fg3_1";
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), spoint(0, 0),
            spoint(game_window_pix_width_get(g), game_window_pix_height_get(g)), WHITE);
  blit_flush();
}

static void game_display_title_fg4(Gamep g)
{
  TRACE_NO_INDENT();

  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  static int  frame = 1;
  static ts_t ts;

  if (time_have_x_tenths_passed_since(5, ts)) {
    frame++;
    if (frame > 64) {
      frame = 1;
    }
    ts = time_ms_cached();
  }

  std::string t = "title_fg4_" + std::to_string(frame);
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), spoint(0, 0),
            spoint(game_window_pix_width_get(g), game_window_pix_height_get(g)), WHITE);
  blit_flush();
}

static void wid_main_menu_tick(Gamep g, Widp w)
{
  TRACE_NO_INDENT();

  if (0) {
    game_display_title_bg(g);
    game_display_title_fg1(g);
    game_display_title_fg2(g);
    game_display_title_fg3(g);
    game_display_title_fg4(g);
  }

  if (wid_main_menu_window) {
    ascii_putf(TERM_WIDTH - SIZEOF(MYVER), TERM_HEIGHT - 1, GREEN, BLACK, "v" MYVER);

    std::string seed_name(game_seed_name_get(g));
    auto        seed_text = "Seed: '" + seed_name + "'";

    switch (game_seed_source_get(g)) {
      case SEED_SOURCE_COMMAND_LINE : seed_text += " (set via cli)"; break;
      case SEED_SOURCE_USER :         seed_text += " (set via user)"; break;
      case SEED_SOURCE_RANDOM :       seed_text += " (randomly generated)"; break;
    }

    ascii_putf(0, TERM_HEIGHT - 1, YELLOW, BLACK, seed_text);
  }
}

void wid_main_menu_select(Gamep g)
{
  LOG("Main menu");
  TRACE_NO_INDENT();

  if (wid_main_menu_window) {
    wid_main_menu_destroy(g);
  }

  const auto button_height = 2;
  const auto button_step   = 3;
  const auto menu_height   = 16;
  const auto menu_width    = UI_WID_POPUP_WIDTH_NORMAL;

  auto y_at = 0;

  const spoint outer_tl(TERM_WIDTH / 2 - (menu_width / 2), TERM_HEIGHT / 2 - (menu_height / 2));
  const spoint outer_br(TERM_WIDTH / 2 + (menu_width / 2), TERM_HEIGHT / 2 + (menu_height / 2));

  wid_main_menu_window = new WidPopup(g, "Main menu", outer_tl, outer_br, nullptr, "nothing", false, false);

  auto button_width = outer_br.x - outer_tl.x - 2;

  {
    TRACE_NO_INDENT();
    Widp w = wid_main_menu_window->wid_popup_container;
    wid_set_on_key_down(g, w, wid_main_menu_key_down);
    wid_set_on_tick(g, w, wid_main_menu_tick);
  }

  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_menu_button(g, p, "New Game");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + button_height);
    wid_set_on_mouse_up(g, w, game_menu_new_game);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "N" UI_RESET_FMT "ew game" UI_RESET_FMT);
  }
  y_at += button_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_menu_button(g, p, "Load Game");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + button_height);
    wid_set_on_mouse_up(g, w, wid_main_menu_load);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "L" UI_FMT_STR "oad game");
  }
  y_at += button_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_menu_button(g, p, "Options");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + button_height);
    wid_set_on_mouse_up(g, w, wid_main_menu_cfg);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "O" UI_FMT_STR "ptions");
  }
  y_at += button_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_menu_button(g, p, "More");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + button_height);
    wid_set_on_mouse_up(g, w, wid_main_menu_more);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "M" UI_FMT_STR "ore");
  }
  y_at += button_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_cancel_button(g, p, "Quit Game");

    spoint tl(0, y_at);
    spoint br(button_width, y_at + button_height);
    wid_set_on_mouse_up(g, w, wid_main_menu_quit);
    wid_set_pos(w, tl, br);
    wid_set_text(w, UI_HIGHLIGHT_FMT_STR "Q" UI_FMT_STR "uit Game");
  }

  wid_update(g, wid_main_menu_window->wid_text_area->wid_text_area);
}

void wid_new_game(Gamep g)
{
  LOG("New game");
  TRACE_NO_INDENT();

  game_state_reset(g, "new game");
  game_create_levels(g);
  game_map_zoom_in(g);
  game_start_playing(g);
  game_state_change(g, STATE_PLAYING, "new game");
}
