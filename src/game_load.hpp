//
// Copyright goblinhack@gmail.com
//

#include "3rdparty/minilzo.hpp"
#include "my_alloc.hpp"
#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl_proto.hpp"
#include "my_serialize.hpp"
#include "my_sound.hpp"
#include "my_wid_error.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_progress_bar.hpp"

#include <array>
#include <format>

static WidPopup *wid_load;

static std::string                    game_load_error;
bool                                  game_headers_only;
extern int                            GAME_SAVE_MARKER_EOL;
extern int                            GAME_SAVE_MARKER_CONFIG;
std::array< bool, UI_WID_SAVE_SLOTS > slot_valid;

#define READ_MAGIC(what, m)                                                                                          \
  {                                                                                                                  \
    uint32_t magic;                                                                                                  \
    in >> bits(magic);                                                                                               \
    if (magic != m) {                                                                                                \
      game_load_error                                                                                                \
          = "bad '" what "' magic expected: " + std::format("0x{:x}", m) + " got " + std::format("0x{:x}", magic);   \
      return in;                                                                                                     \
    }                                                                                                                \
    IF_DEBUG2 { CON("Read magic '%s' %s", what, std::format("0x{:x}", magic).c_str()); }                             \
  }

std::istream &operator>>(std::istream &in, Bits< SDL_Keysym & > my)
{
  TRACE_NO_INDENT();
  in >> bits(my.t.scancode);
  in >> bits(my.t.sym);
  in >> bits(my.t.mod);
  in >> bits(my.t.unused);
  return in;
}

std::istream &operator>>(std::istream &in, Bits< Config & > my)
{
  TRACE_NO_INDENT();

  in >> bits(my.t.version);
  LOG("Read config: version                = [%s]", my.t.version.c_str());
  in >> bits(my.t.serialized_size);
  LOG("Read config: serialized_size        = %d", my.t.serialized_size);

  if (my.t.serialized_size != sizeof(Config)) {
    game_load_error = "bad save file header version";
    return in;
  }

  in >> bits(my.t.seed_name);
  in >> bits(my.t.seed_num);

  READ_MAGIC("config part 1", CONFIG_MAGIC_1);

  in >> bits(my.t.seed_source);
  in >> bits(my.t.player_name);

  READ_MAGIC("config part 2", CONFIG_MAGIC_2);

  in >> bits(my.t.config_pix_height);
  in >> bits(my.t.config_pix_width);
  in >> bits(my.t.debug_mode);
  in >> bits(my.t.fps_counter);

  READ_MAGIC("config part 3", CONFIG_MAGIC_3);

  in >> bits(my.t.gfx_allow_highdpi);
  in >> bits(my.t.gfx_borderless);
  in >> bits(my.t.gfx_fullscreen);
  in >> bits(my.t.gfx_fullscreen_desktop);
  in >> bits(my.t.gfx_vsync_enable);

  READ_MAGIC("config part 4", CONFIG_MAGIC_4);

  in >> bits(my.t.key_wait);
  in >> bits(my.t.key_console);
  in >> bits(my.t.key_help);
  in >> bits(my.t.key_load);
  in >> bits(my.t.key_move_down);
  in >> bits(my.t.key_move_left);
  in >> bits(my.t.key_move_right);
  in >> bits(my.t.key_move_up);
  in >> bits(my.t.key_quit);
  in >> bits(my.t.key_save);
  in >> bits(my.t.key_screenshot);

  READ_MAGIC("config part 5", CONFIG_MAGIC_5);

  in >> bits(my.t.key_unused1);
  in >> bits(my.t.key_unused2);
  in >> bits(my.t.key_unused3);
  in >> bits(my.t.key_unused4);
  in >> bits(my.t.key_unused5);
  in >> bits(my.t.key_unused6);
  in >> bits(my.t.key_unused7);
  in >> bits(my.t.key_unused8);
  in >> bits(my.t.key_unused9);
  in >> bits(my.t.key_unused10);
  in >> bits(my.t.key_unused11);
  in >> bits(my.t.key_unused12);
  in >> bits(my.t.key_unused13);
  in >> bits(my.t.key_unused14);
  in >> bits(my.t.key_unused15);
  in >> bits(my.t.key_inventory);
  in >> bits(my.t.key_jump);
  in >> bits(my.t.key_ascend);
  in >> bits(my.t.key_descend);
  in >> bits(my.t.key_zoom);

  READ_MAGIC("config part 6", CONFIG_MAGIC_6);

  in >> bits(my.t.mouse_wheel_lr_negated);
  in >> bits(my.t.mouse_wheel_ud_negated);
  in >> bits(my.t.music_volume);
  in >> bits(my.t.sdl_delay);
  in >> bits(my.t.sound_volume);

  LOG("Read config: config_pix_height      = %d", my.t.config_pix_height);
  LOG("Read config: config_pix_width       = %d", my.t.config_pix_width);
  LOG("Read config: debug_mode             = %d", my.t.debug_mode);
  LOG("Read config: fps_counter            = %d", my.t.fps_counter);
  LOG("Read config: gfx_allow_highdpi      = %d", my.t.gfx_allow_highdpi);
  LOG("Read config: gfx_borderless         = %d", my.t.gfx_borderless);
  LOG("Read config: gfx_fullscreen         = %d", my.t.gfx_fullscreen);
  LOG("Read config: gfx_fullscreen_desktop = %d", my.t.gfx_fullscreen_desktop);
  LOG("Read config: gfx_vsync_enable       = %d", my.t.gfx_vsync_enable);
  LOG("Read config: mouse_wheel_lr_negated = %d", my.t.mouse_wheel_lr_negated);
  LOG("Read config: mouse_wheel_ud_negated = %d", my.t.mouse_wheel_ud_negated);
  LOG("Read config: music_volume           = %d", my.t.music_volume);
  LOG("Read config: sdl_delay              = %d", my.t.sdl_delay);
  LOG("Read config: sound_volume           = %d", my.t.sound_volume);

  if (! g_opt_override_debug_level) {
    if (my.t.debug_mode) {
      g_opt_debug2 = true;
      g_opt_debug1 = true;
    }
  }

  in >> bits(my.t.hiscores);

  int eol;
  in >> bits(eol);
  if (eol != GAME_SAVE_MARKER_CONFIG) {
    game_load_error += "end of config marker not found";
    return in;
  }
  if (my.t.ascii_pix_height < 0) {
    game_load_error += "ascii_pix_height is invalid";
    return in;
  }
  if (my.t.ascii_pix_width < 0) {
    game_load_error += "ascii_pix_width is invalid";
    return in;
  }
  if (my.t.config_pix_height < 0) {
    game_load_error += "config_pix_height is invalid";
    return in;
  }
  if (my.t.config_pix_width < 0) {
    game_load_error += "config_pix_width is invalid";
    return in;
  }
  if (my.t.map_fbo_height < 0) {
    game_load_error += "map_fbo_height is invalid";
    return in;
  }
  if (my.t.map_fbo_width < 0) {
    game_load_error += "map_fbo_width is invalid";
    return in;
  }
  if (my.t.aspect_ratio < 0) {
    game_load_error += "aspect_ratio is invalid";
    return in;
  }
  if (my.t.window_pix_height < 0) {
    game_load_error += "window_pix_height is invalid";
    return in;
  }
  if (my.t.window_pix_width < 0) {
    game_load_error += "window_pix_width is invalid";
    return in;
  }

  return in;
}

std::istream &operator>>(std::istream &in, Bits< class Game & > my)
{
  TRACE_NO_INDENT();
  in >> bits(my.t.version);
  in >> bits(my.t.serialized_size);

  if (my.t.serialized_size != (uint32_t) sizeof(Game)) {
    if (my.t.version == MYVER) {
      game_load_error = "Incompatible save file for version " + my.t.version;
    } else {
      game_load_error = "Incompatible version. Expected version " MYVER ", found version " + my.t.version;
    }
    return in;
  }

  in >> bits(my.t.save_slot);
  in >> bits(my.t.save_meta);
  in >> bits(my.t.save_file);
  if (game_headers_only) {
    return in;
  }
  in >> bits(my.t.appdata);
  in >> bits(my.t.saved_dir);

  Levelsp tmp = (Levelsp) mymalloc(sizeof(Levels), "loaded level");
  newptr(MTYPE_LEVELS, tmp, "loaded levels");
  in.read(reinterpret_cast< char * >(tmp), sizeof(Levels));
  my.t.levels = tmp;

  return in;
}

// binary mode is only for switching off newline translation
// ios::ate, open at end
std::vector< char > read_file(const std::string filename)
{
  TRACE_NO_INDENT();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary | std::ios::ate);
  if (ifs.is_open()) {
    ifs.unsetf(std::ios::skipws);

    std::ifstream::pos_type sz = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    std::vector< char > bytes(sz);
    ifs.read(bytes.data(), sz);
    return bytes;
  }
  std::vector< char > bytes;
  return bytes;
}

static std::vector< char > read_lzo_file(const std::string filename, lzo_uint *uncompressed_sz)
{
  TRACE_NO_INDENT();
  std::ifstream ifs(filename, std::ios::in | std::ios::binary | std::ios::ate);
  if (ifs.is_open()) {
    // tellg is not ideal, look into <filesystem> post mojave
    std::ifstream::pos_type sz = ifs.tellg();
    if (sz < 0) {
      return (std::vector< char >());
    }

    ifs.seekg(0, std::ios::beg);
    ifs.unsetf(std::ios::skipws);
    ifs.read((char *) uncompressed_sz, sizeof(*uncompressed_sz));

    sz -= (int) sizeof(*uncompressed_sz);
    std::vector< char > bytes(sz);
    ifs.read(bytes.data(), sz);
    return bytes;
  }
  std::vector< char > bytes;
  return bytes;
}

bool Game::load(const std::string &file_to_load, class Game &target)
{
  LOG("Load: %s", file_to_load.c_str());
  TRACE_AND_INDENT();

  TRACE_NO_INDENT();
  verify(MTYPE_GAME, this);
  game_load_error = "";

  //
  // Read to a vector and then copy to a C buffer for LZO to use
  //
  lzo_uint uncompressed_len;

  TRACE_NO_INDENT();
  if (! game_headers_only) {
    verify(MTYPE_GAME, this);
    wid_progress_bar(this, "Loading...", 0.0);
  }

  TRACE_NO_INDENT();
  auto vec = read_lzo_file(file_to_load, &uncompressed_len);

  TRACE_NO_INDENT();
  if (vec.size() <= 0) {
    if (! game_headers_only) {
      wid_error(game, "load error, empty file [" + file_to_load + "] ?");
    }
    verify(MTYPE_GAME, this);
    wid_progress_bar_destroy(this);
    return false;
  }

  TRACE_NO_INDENT();
  auto     data           = vec.data();
  lzo_uint compressed_len = vec.size();

  HEAP_ALLOC(compressed, compressed_len);
  HEAP_ALLOC(uncompressed, uncompressed_len);
  memcpy(compressed, data, compressed_len);

  TRACE_NO_INDENT();
  if (! game_headers_only) {
    verify(MTYPE_GAME, this);
    wid_progress_bar(this, "Decompressing...", 0.5);
  }

  TRACE_NO_INDENT();
  lzo_uint new_len = 0;
  int      r = lzo1x_decompress((lzo_bytep) compressed, compressed_len, (lzo_bytep) uncompressed, &new_len, nullptr);
  if (r == LZO_E_OK && new_len == uncompressed_len) {
    if (! game_headers_only) {
      LOG("Loading: %s, decompress %luMb -> %luMb", file_to_load.c_str(),
          (unsigned long) compressed_len / (1024 * 1024), (unsigned long) uncompressed_len / (1024 * 1024));
    }
  } else {
    /* this should NEVER happen */
    ERR("LZO internal error - decompression failed: %d", r);
    verify(MTYPE_GAME, this);
    wid_progress_bar_destroy(this);
    return false;
  }

  TRACE_NO_INDENT();
  if (! game_headers_only) {
    verify(MTYPE_GAME, this);
    wid_progress_bar(this, "Reading...", 0.75);
  }

#if 0
  IF_DEBUG2 {
    std::cout << "decompressed as ";
    hexdump((const unsigned char *)uncompressed, uncompressed_len);
  }
#endif

  std::string        s((const char *) uncompressed, (size_t) uncompressed_len);
  std::istringstream in(s);

  TRACE_NO_INDENT();
  game_load_error = "";
  in >> bits(target);
  TRACE_NO_INDENT();
  if (! game_load_error.empty()) {
    if (! game_headers_only) {
      wid_error(game, "load error, " + game_load_error);
    }
    return false;
  }

  free(uncompressed);
  free(compressed);

  if (! game_headers_only) {
    verify(MTYPE_GAME, this);
    wid_progress_bar(this, "Loaded", 1.0);
  }

  wid_progress_bar_destroy(this);

  return true;
}

bool game_load(Gamep g, const std::string &file_to_load)
{
  TRACE_NO_INDENT();

  return g->load(file_to_load, *g);
}

std::string Game::load_config(void)
{
  TRACE_NO_INDENT();
  game_load_error = "";

  auto          filename = saved_dir + "config";
  std::ifstream in(filename);
  if (in.is_open()) {
    in >> bits(*(&game->config));
  }

  return game_load_error;
}

bool Game::load(int slot)
{
  LOG("Load slot: %d", slot);
  TRACE_AND_INDENT();

  if (slot < 0) {
    return false;
  }

  if (slot >= UI_WID_SAVE_SLOTS) {
    return false;
  }

  if (! slot_valid[ slot ]) {
    LOG("No game at that slot.");
    return false;
  }

  LOG("Clean up current game");
  game->fini();

  auto this_save_file = saved_dir + "saved-slot-" + std::to_string(slot);

  if (slot == UI_WID_SAVE_SLOTS - 1) {
    this_save_file = saved_dir + "saved-snapshot";
  }

  LOG("Loading: %s", this_save_file.c_str());
  g_loading = true;
  load(this_save_file, *this);
  g_loading = false;

  state_change(STATE_LOADED, "reset");
  state_change(STATE_PLAYING, "loaded game");

  TOPCON("Loaded the game from %s", this_save_file.c_str());

  return game_load_error == "";
}

bool Game::load_snapshot(void)
{
  LOG("Load snapshot");
  TRACE_AND_INDENT();

  game->fini();

  auto this_save_file = saved_dir + "saved-snapshot";

  LOG("Loading: %s", this_save_file.c_str());
  g_loading = true;
  load(this_save_file, *this);
  g_loading = false;

  state_change(STATE_PLAYING, "loaded snapshot");

  TOPCON("Loaded the game from %s", this_save_file.c_str());

  return game_load_error == "";
}

void wid_load_destroy(Gamep g)
{
  if (! wid_load) {
    return;
  }

  LOG("Wid load destroy");
  TRACE_AND_INDENT();

  delete wid_load;
  wid_load = nullptr;
}

static bool wid_load_key_up(Gamep g, Widp w, const struct SDL_Keysym *key)
{
  TRACE_NO_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
    default :
      switch (key->sym) {
        default :
          {
            auto c = wid_event_to_char(key);
            switch (c) {
              case '0' :
              case '1' :
              case '2' :
              case '3' :
              case '4' :
              case '5' :
              case '6' :
              case '7' :
              case '8' :
              case '9' :
                {
                  int slot = c - '0';
                  if (! slot_valid[ slot ]) {
                    LOG("No game at that slot.");
                  } else {
                    game->load(slot);
                    wid_load_destroy(game);
                  }
                  return true;
                }
              case 'b' :
              case 'B' :
              case SDLK_ESCAPE :
                {
                  TRACE_NO_INDENT();
                  LOG("Load game cancelled");
                  wid_load_destroy(game);
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static bool wid_load_key_down(Gamep g, Widp w, const struct SDL_Keysym *key)
{
  TRACE_NO_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    sound_play(g, "keypress");
    return false;
  }

  sound_play(g, "keypress");
  return true;
}

static bool wid_load_mouse_up(Gamep g, Widp w, int x, int y, uint32_t button)
{
  LOG("Load selected slot");
  TRACE_AND_INDENT();

  auto slot = wid_get_int_context(w);
  game->load(slot);
  wid_load_destroy(game);
  return true;
}

static bool wid_load_saved_snapshot(Gamep g, Widp w, int x, int y, uint32_t button)
{
  LOG("Load snapshot");
  TRACE_AND_INDENT();

  game->load_snapshot();
  wid_load_destroy(game);
  return true;
}

static bool wid_load_cancel(Gamep g, Widp w, int x, int y, uint32_t button)
{
  LOG("Load cancel");
  TRACE_AND_INDENT();

  wid_load_destroy(game);
  return true;
}

void Game::load_select(void)
{
  LOG("Load menu");
  TRACE_AND_INDENT();

  if (wid_load) {
    return;
  }

  game_load_error = "";

  int    menu_height = UI_WID_SAVE_SLOTS + 8;
  int    menu_width  = UI_WID_POPUP_WIDTH_WIDE;
  spoint outer_tl(TERM_WIDTH / 2 - (menu_width / 2), TERM_HEIGHT / 2 - (menu_height / 2));
  spoint outer_br(TERM_WIDTH / 2 + (menu_width / 2), TERM_HEIGHT / 2 + (menu_height / 2));
  wid_load = new WidPopup(game, "Game load", outer_tl, outer_br, nullptr, "", false, false);

  wid_set_on_key_up(game, wid_load->wid_popup_container, wid_load_key_up);
  wid_set_on_key_down(game, wid_load->wid_popup_container, wid_load_key_down);

  {
    TRACE_NO_INDENT();
    auto p = wid_load->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(game, p, "back");

    spoint tl(menu_width / 2 - 4, menu_height - 4);
    spoint br(menu_width / 2 + 3, menu_height - 2);

    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(game, w, wid_load_cancel);

    wid_set_pos(w, tl, br);
    wid_set_text(w, "BACK");

    wid_set_mode(game, w, WID_MODE_OVER);
    wid_set_style(w, UI_WID_STYLE_SOLID_GRAY);
    wid_set_color(w, WID_COLOR_BG, RED);
    wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
    wid_set_mode(game, w, WID_MODE_NORMAL);
  }

  game_headers_only = true;

  wid_load->log(game, "Choose a load slot.");

  int y_at = 3;
  for (auto slot = 0; slot < UI_WID_SAVE_SLOTS; slot++) {
    Game tmp;
    auto tmp_file = saved_dir + "saved-slot-info-" + std::to_string(slot);

    if (slot == UI_WID_SAVE_SLOTS - 1) {
      tmp_file = saved_dir + "saved-snapshot-info";
    }

    auto   p = wid_load->wid_text_area->wid_text_area;
    auto   w = wid_new_square_button(game, p, "load slot");
    spoint tl(0, y_at);
    spoint br(menu_width - 2, y_at);

    std::string s = std::to_string(slot) + ": ";
    if (! load(tmp_file, tmp)) {
      if (! game_load_error.empty()) {
        s += game_load_error;
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        CON("GAME LOADING ERROR: %s", game_load_error.c_str());
      } else {
        if (slot == UI_WID_SAVE_SLOTS - 1) {
          s += "<no-snapshot>";
        } else {
          s += "<empty>";
        }
        wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
      }
      slot_valid[ slot ] = false;
    } else {
      if (slot == UI_WID_SAVE_SLOTS - 1) {
        s += "snapshot: " + tmp.save_meta;
      } else {
        s += tmp.save_meta;
      }
      if (slot == UI_WID_SAVE_SLOTS - 1) {
        wid_set_on_mouse_up(game, w, wid_load_saved_snapshot);
      } else {
        wid_set_on_mouse_up(game, w, wid_load_mouse_up);
      }
      wid_set_style(w, UI_WID_STYLE_HORIZ_LIGHT);
      slot_valid[ slot ] = true;
    }
    wid_set_int_context(w, slot);

    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    y_at++;
  }
  game_headers_only = false;
  wid_update(game, wid_load->wid_text_area->wid_text_area);

  game->state_change(STATE_LOAD_MENU, "load select");
}

void wid_load_select(Gamep g) { g->load_select(); }

bool game_load_last_config(const char *appdata)
{
  TRACE_NO_INDENT();

  CON("Load config");

  game = new Game(std::string(appdata));
  newptr(MTYPE_GAME, game, "game");

  auto config_error = game->load_config();

  std::string version = "" MYVER "";

  if (game->config.version != version) {
    sdl_msg_box("Config version change. Will need to reset config. Found version [%s]. Expected version [%s].",
                game->config.version.c_str(), version.c_str());
    oldptr(MTYPE_GAME, game);
    delete game;
    game = new Game(std::string(appdata));
    newptr(MTYPE_GAME, game, "game (1)");
    reset_globals();
    game_save_config(game);
    g_errored = false;
  } else if (! config_error.empty()) {
    sdl_msg_box("Config error: %s. Will need to reset config.", config_error.c_str());
    oldptr(MTYPE_GAME, game);
    delete game;
    game = nullptr;
    reset_globals();
    game = new Game(std::string(appdata));
    newptr(MTYPE_GAME, game, "game (2)");
    game_save_config(game);
    g_errored = false;
  }

  return game_load_error == "";
}
