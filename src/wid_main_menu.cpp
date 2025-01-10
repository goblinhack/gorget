//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_sdl_proto.hpp"
#include "my_wids.hpp"

WidPopup *wid_main_menu_window;

void wid_main_menu_destroy(class Game *g)
{
  TRACE_AND_INDENT();

  delete wid_main_menu_window;
  wid_main_menu_window = nullptr;
}

void wid_main_menu_hide(class Game *g)
{
  TRACE_AND_INDENT();
  wid_hide(wid_main_menu_window->wid_popup_container);
}

static bool wid_main_menu_load_game(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_load_select(game);
  return false;
}

static bool wid_main_menu_config(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_cfg_top_menu(game);
  wid_main_menu_hide(game);
  return false;
}

static bool game_menu_new_game(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_main_menu_hide(game);
  wid_main_menu_destroy(game);
  wid_new_game(game);
  return false;
}

static bool wid_main_menu_credits_game(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_credits_select(game);
  wid_main_menu_destroy(game);
  return false;
}

static bool wid_main_menu_quit_game(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_quit_select(game);
  wid_main_menu_destroy(game);
  return false;
}

static bool wid_main_menu_hiscores(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_hiscores_show(game);
  return false;
}

static bool wid_main_menu_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game_key_console_get(game))) {
    return false;
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        default :
          {
            TRACE_AND_INDENT();
            auto c = wid_event_to_char(key);
            switch (c) {
              case SDLK_RETURN :
              case ' ' :
              case 'n' :
              case 'N' : game_menu_new_game(nullptr, 0, 0, 0); return true;
              case 'l' :
              case 'L' : wid_main_menu_load_game(nullptr, 0, 0, 0); return true;
              case 'o' :
              case 'O' : wid_main_menu_config(nullptr, 0, 0, 0); return true;
              case 'c' :
              case 'C' : wid_main_menu_credits_game(nullptr, 0, 0, 0); return true;
              case 'h' :
              case 'H' : wid_main_menu_hiscores(nullptr, 0, 0, 0); return true;
              case 'q' :
              case 'Q' : wid_main_menu_quit_game(nullptr, 0, 0, 0); return true;
            }
          }
      }
  }

  return false;
}

static bool wid_main_menu_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game_key_console_get(game))) {
    return false;
  }

  //
  // So screenshots can work
  //
  return false;
}

static void game_display_title_bg(void)
{
  TRACE_AND_INDENT();
  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::string t = "title_bg";
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), point(0, 0),
            point(game_window_pix_width_get(game), game_window_pix_height_get(game)));
  blit_flush();
}

static void game_display_title_fg1(void)
{
  TRACE_AND_INDENT();

  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::string t = "title_fg1_1";
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), point(0, 0),
            point(game_window_pix_width_get(game), game_window_pix_height_get(game)));
  blit_flush();
}

static void game_display_title_fg2(void)
{
  TRACE_AND_INDENT();

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
  tile_blit(tile_find_mand(t.c_str()), point(0, 0),
            point(game_window_pix_width_get(game), game_window_pix_height_get(game)));
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

static void game_display_title_fg3(void)
{
  TRACE_AND_INDENT();

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

  float bright = 1.01;
  int   r      = ((float) fg.r) * bright;
  if (r > 255) {
    r = 255;
  }
  fg.r  = r;
  int g = ((float) fg.g) * bright;
  if (g > 255) {
    g = 255;
  }
  fg.g  = g;
  int b = ((float) fg.b) * bright;
  if (b > 255) {
    b = 255;
  }
  fg.b = b;

  glcolor(fg);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::string t = "title_fg3_1";
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), point(0, 0),
            point(game_window_pix_width_get(game), game_window_pix_height_get(game)));
  blit_flush();
}

static void game_display_title_fg4(void)
{
  TRACE_AND_INDENT();

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
  tile_blit(tile_find_mand(t.c_str()), point(0, 0),
            point(game_window_pix_width_get(game), game_window_pix_height_get(game)));
  blit_flush();
}

static void wid_main_menu_tick(Widp w)
{
  TRACE_NO_INDENT();

  if (0) {
    game_display_title_bg();
    game_display_title_fg1();
    game_display_title_fg2();
    game_display_title_fg3();
    game_display_title_fg4();
  }

  if (wid_main_menu_window) {
    ascii_putf(1, 1, GREEN, BLACK, "V" MYVER);

    if (! g_opt_seed_name.empty()) {
      auto seed_name = "Seed: '" + g_opt_seed_name + "'";
      ascii_putf(1, 2, YELLOW, BLACK, seed_name);
    }
  }
}

void wid_main_menu_select(class Game *g)
{
  TRACE_AND_INDENT();
  LOG("Main menu");

  if (wid_main_menu_window) {
    wid_main_menu_destroy(g);
  }

  auto box_height          = 3;
  auto box_step            = 3;
  auto box_style           = UI_WID_STYLE_NORMAL;
  auto box_highlight_style = UI_WID_STYLE_NORMAL;

  int   menu_height = 20;
  int   menu_width  = UI_WID_POPUP_WIDTH_NORMAL;
  point outer_tl(TERM_WIDTH / 2 - (menu_width / 2), TERM_HEIGHT / 2 - (menu_height / 2));
  point outer_br(TERM_WIDTH / 2 + (menu_width / 2), TERM_HEIGHT / 2 + (menu_height / 2));
  wid_main_menu_window = new WidPopup("Main menu", outer_tl, outer_br, nullptr, "nothing", false, false);

  auto button_width = outer_br.x - outer_tl.x - 2;

  {
    TRACE_NO_INDENT();
    Widp w = wid_main_menu_window->wid_popup_container;
    wid_set_on_key_up(w, wid_main_menu_key_up);
    wid_set_on_key_down(w, wid_main_menu_key_down);
    wid_set_on_tick(w, wid_main_menu_tick);
  }

  int y_at = 0;
  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "New Game");

    point tl(0, y_at);
    point br(button_width, y_at + box_height - 1);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, game_menu_new_game);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$N%%fg=reset$ew game%%fg=reset$");
  }
  y_at += box_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Load Game");

    point tl(0, y_at);
    point br(button_width, y_at + box_height - 1);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_main_menu_load_game);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$L%%fg=" UI_TEXT_COLOR_STR "$oad game");
  }
  y_at += box_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Options");

    point tl(0, y_at);
    point br(button_width, y_at + box_height - 1);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_main_menu_config);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$O%%fg=" UI_TEXT_COLOR_STR "$ptions");
  }
  y_at += box_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Credits");

    point tl(0, y_at);
    point br(button_width, y_at + box_height - 1);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_main_menu_credits_game);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$C%%fg=" UI_TEXT_COLOR_STR "$redits");
  }
  y_at += box_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Hiscores");

    point tl(0, y_at);
    point br(button_width, y_at + box_height - 1);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_main_menu_hiscores);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$H%%fg=" UI_TEXT_COLOR_STR "$iscores");
  }
  y_at += box_step;
  {
    TRACE_NO_INDENT();
    auto p = wid_main_menu_window->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "Quit Game");

    point tl(0, y_at);
    point br(button_width, y_at + box_height - 1);
    wid_set_mode(w, WID_MODE_OVER);
    wid_set_style(w, box_highlight_style);
    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_style(w, box_style);
    wid_set_on_mouse_up(w, wid_main_menu_quit_game);
    wid_set_pos(w, tl, br);
    wid_set_text(w, "%%fg=" UI_TEXT_HIGHLIGHT_COLOR_STR "$Q%%fg=" UI_TEXT_COLOR_STR "$uit Game");
  }

  wid_update(wid_main_menu_window->wid_text_area->wid_text_area);
}

void wid_new_game(class Game *g)
{
  TRACE_NO_INDENT();

  game_create_level(g);
  game_state_reset(g, "new game");
  game_entered_level(g);
}
