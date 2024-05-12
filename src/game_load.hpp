//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "3rdparty/minilzo.hpp"
#include "my_alloc.hpp"
#include "my_callstack.hpp"
#include "my_sdl_proto.hpp"
#include "my_serialize.hpp"
#include "my_wid_error.hpp"
#include "my_wid_popup.hpp"

#include <array>

WidPopup *wid_load;

static std::string                    game_load_error;
bool                                  game_load_headers_only;
extern int                            GAME_SAVE_MARKER_EOL;
extern int                            GAME_SAVE_MARKER_CONFIG;
std::array< bool, UI_WID_SAVE_SLOTS > slot_valid;

#define READ_MAGIC(what, m)                                                                                          \
  {                                                                                                                  \
    uint32_t magic;                                                                                                  \
    in >> bits(magic);                                                                                               \
    if (magic != m) {                                                                                                \
      game_load_error = "bad " what " magic expected: " + std::to_string(m) + " got " + std::to_string(magic);       \
      return in;                                                                                                     \
    }                                                                                                                \
  }

std::istream &operator>>(std::istream &in, Bits< SDL_Keysym & > my)
{
  TRACE_AND_INDENT();
  in >> bits(my.t.scancode);
  in >> bits(my.t.sym);
  in >> bits(my.t.mod);
  in >> bits(my.t.unused);
  return in;
}

std::istream &operator>>(std::istream &in, Bits< Config & > my)
{
  TRACE_AND_INDENT();

  in >> bits(my.t.version);
  LOG("Read config: version                      = [%s]", my.t.version.c_str());
  in >> bits(my.t.serialized_size);
  LOG("Read config: serialized_size              = %d", my.t.serialized_size);

  if (my.t.serialized_size != sizeof(Config)) {
    game_load_error = "bad save file header version";
    return in;
  }

  in >> bits(my.t.ascii_gl_height);
  in >> bits(my.t.ascii_gl_width);
  in >> bits(my.t.aspect_ratio);
  in >> bits(my.t.config_pix_height);
  in >> bits(my.t.config_pix_width);
  in >> bits(my.t.debug_mode);
  in >> bits(my.t.fps_counter);
  in >> bits(my.t.game_pix_height);
  in >> bits(my.t.game_pix_width);
  in >> bits(my.t.gfx_allow_highdpi);
  in >> bits(my.t.gfx_borderless);
  in >> bits(my.t.gfx_fullscreen);
  in >> bits(my.t.gfx_fullscreen_desktop);
  in >> bits(my.t.gfx_vsync_enable);
  in >> bits(my.t.key_attack);
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
  in >> bits(my.t.key_unused1);
  in >> bits(my.t.map_pix_height);
  in >> bits(my.t.map_pix_width);
  in >> bits(my.t.mouse_wheel_lr_negated);
  in >> bits(my.t.mouse_wheel_ud_negated);
  in >> bits(my.t.music_volume);
  in >> bits(my.t.sdl_delay);
  in >> bits(my.t.sound_volume);
  in >> bits(my.t.tiles_visible_across);
  in >> bits(my.t.tiles_visible_down);
  in >> bits(my.t.ui_gfx_term_height);
  in >> bits(my.t.ui_gfx_term_width);
  in >> bits(my.t.ui_pix_height);
  in >> bits(my.t.ui_pix_width);
  in >> bits(my.t.window_pix_height);
  in >> bits(my.t.window_pix_width);

  LOG("Read config: ascii_gl_height        = %d", my.t.ascii_gl_height);
  LOG("Read config: ascii_gl_width         = %d", my.t.ascii_gl_width);
  LOG("Read config: aspect_ratio           = %f", my.t.aspect_ratio);
  LOG("Read config: config_pix_height      = %d", my.t.config_pix_height);
  LOG("Read config: config_pix_width       = %d", my.t.config_pix_width);
  LOG("Read config: debug_mode             = %d", my.t.debug_mode);
  LOG("Read config: fps_counter            = %d", my.t.fps_counter);
  LOG("Read config: game_pix_height        = %d", my.t.game_pix_height);
  LOG("Read config: game_pix_width         = %d", my.t.game_pix_width);
  LOG("Read config: gfx_allow_highdpi      = %d", my.t.gfx_allow_highdpi);
  LOG("Read config: gfx_borderless         = %d", my.t.gfx_borderless);
  LOG("Read config: gfx_fullscreen_desktop = %d", my.t.gfx_fullscreen_desktop);
  LOG("Read config: gfx_fullscreen         = %d", my.t.gfx_fullscreen);
  LOG("Read config: gfx_vsync_enable       = %d", my.t.gfx_vsync_enable);
  LOG("Read config: map_pix_height         = %d", my.t.map_pix_height);
  LOG("Read config: map_pix_width          = %d", my.t.map_pix_width);
  LOG("Read config: mouse_wheel_lr_negated = %d", my.t.mouse_wheel_lr_negated);
  LOG("Read config: mouse_wheel_ud_negated = %d", my.t.mouse_wheel_ud_negated);
  LOG("Read config: music_volume           = %d", my.t.music_volume);
  LOG("Read config: sdl_delay              = %d", my.t.sdl_delay);
  LOG("Read config: sound_volume           = %d", my.t.sound_volume);
  LOG("Read config: tiles_visible_across   = %d", my.t.tiles_visible_across);
  LOG("Read config: tiles_visible_down     = %d", my.t.tiles_visible_down);
  LOG("Read config: ui_pix_height          = %d", my.t.ui_pix_height);
  LOG("Read config: ui_pix_width           = %d", my.t.ui_pix_width);
  LOG("Read config: window_pix_height      = %d", my.t.window_pix_height);
  LOG("Read config: window_pix_width       = %d", my.t.window_pix_width);
  // seed name handled below

  if (! g_opt_override_debug_level) {
    if (my.t.debug_mode) {
      g_opt_debug3 = false;
      g_opt_debug2 = true;
      g_opt_debug1 = true;
    }
  }

  //
  // Allow the command line to override.
  //
  {
    std::string tmp;
    in >> bits(tmp);
    if (g_opt_seed_name.empty()) {
      g_opt_seed_name = tmp;
    }
  }

  in >> bits(my.t.hiscores);

  int eol;
  in >> bits(eol);
  if (eol != GAME_SAVE_MARKER_CONFIG) {
    game_load_error += "end of config marker not found";
    return in;
  }
  if (my.t.ascii_gl_height < 0) {
    game_load_error += "ascii_gl_height is invalid";
    return in;
  }
  if (my.t.ascii_gl_width < 0) {
    game_load_error += "ascii_gl_width is invalid";
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
  if (my.t.game_pix_height < 0) {
    game_load_error += "game_pix_height is invalid";
    return in;
  }
  if (my.t.game_pix_width < 0) {
    game_load_error += "game_pix_width is invalid";
    return in;
  }
  if (my.t.map_pix_height < 0) {
    game_load_error += "map_pix_height is invalid";
    return in;
  }
  if (my.t.map_pix_width < 0) {
    game_load_error += "map_pix_width is invalid";
    return in;
  }
  if (my.t.ui_pix_height < 0) {
    game_load_error += "ui_pix_height is invalid";
    return in;
  }
  if (my.t.ui_pix_width < 0) {
    game_load_error += "ui_pix_width is invalid";
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
  TRACE_AND_INDENT();
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
  if (game_load_headers_only) {
    return in;
  }
  in >> bits(my.t.appdata);
  in >> bits(my.t.saved_dir);
  in >> bits(my.t.config);
  if (! game_load_error.empty()) {
    return in;
  }

  in >> bits(my.t.seed);
  in >> bits(my.t.seed_manually_set);
  in >> bits(my.t.seed_name);
  in >> bits(my.t.fps_value);

  return in;
}

// binary mode is only for switching off newline translation
// ios::ate, open at end
std::vector< char > read_file(const std::string filename)
{
  TRACE_AND_INDENT();
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

static std::vector< char > read_lzo_file(const std::string filename, lzo_uint *uncompressed_sz, uint32_t *cs)
{
  TRACE_AND_INDENT();
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
    ifs.read((char *) cs, sizeof(*cs));

    sz -= (int) sizeof(*uncompressed_sz);
    sz -= (int) sizeof(*cs);
    std::vector< char > bytes(sz);
    ifs.read(bytes.data(), sz);
    return bytes;
  }
  std::vector< char > bytes;
  return bytes;
}

uint32_t csum(char *mem, uint32_t len)
{
  TRACE_AND_INDENT();
  uint32_t ret = 0;
  while (len--) {
    ret <<= 1;
    ret ^= *mem;
    mem++;
  }
  return ret;
}

bool Game::load(std::string file_to_load, class Game &target)
{
  TRACE_AND_INDENT();
  game_load_error = "";

  //
  // Read to a vector and then copy to a C buffer for LZO to use
  //
  lzo_uint uncompressed_len;
  uint32_t cs;
  auto     vec = read_lzo_file(file_to_load, &uncompressed_len, &cs);
  if (vec.size() <= 0) {
    if (! game_load_headers_only) {
      wid_error("load error, empty file [" + file_to_load + "] ?");
    }
    return false;
  }

  auto     data           = vec.data();
  lzo_uint compressed_len = vec.size();

  HEAP_ALLOC(compressed, compressed_len);
  HEAP_ALLOC(uncompressed, uncompressed_len);
  memcpy(compressed, data, compressed_len);

  lzo_uint new_len = 0;
  int      r = lzo1x_decompress((lzo_bytep) compressed, compressed_len, (lzo_bytep) uncompressed, &new_len, nullptr);
  if (r == LZO_E_OK && new_len == uncompressed_len) {
    if (! game_load_headers_only) {
      CON("INF: Loading %s, decompress %luMb -> %luMb", file_to_load.c_str(),
          (unsigned long) compressed_len / (1024 * 1024), (unsigned long) uncompressed_len / (1024 * 1024));
    }
  } else {
    /* this should NEVER happen */
    ERR("LZO internal error - decompression failed: %d", r);
    return false;
  }

  uint32_t csin = csum((char *) uncompressed, (uint32_t) uncompressed_len);
  if (cs != csin) {
    ERR("Corrupt file, checksum mismatch");
    return false;
  }

#if 0
  IF_DEBUG3 {
    std::cout << "decompressed as ";
    hexdump((const unsigned char *)uncompressed, uncompressed_len);
  }
#endif

  std::string        s((const char *) uncompressed, (size_t) uncompressed_len);
  std::istringstream in(s);

  game_load_error = "";
  in >> bits(target);
  if (! game_load_error.empty()) {
    if (! game_load_headers_only) {
      wid_error("load error, " + game_load_error);
    }
    return false;
  }

  free(uncompressed);
  free(compressed);

  return true;
}

std::string Game::load_config(void)
{
  TRACE_AND_INDENT();
  game_load_error = "";

  auto          filename = saved_dir + "config";
  std::ifstream in(filename);
  if (in.is_open()) {
    in >> bits(*(&game->config));
  }

  return game_load_error;
}

void Game::load(void)
{
  TRACE_AND_INDENT();
  LOG("-");
  CON("INF: Loading %s", save_file.c_str());
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v");

  g_loading = true;
  load(save_file, *this);
  g_loading = false;

  sdl_config_update_all();

  LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  CON("INF: Loaded %s, seed %u", save_file.c_str(), seed);
  LOG("-");
}

void Game::load(uint8_t slot)
{
  TRACE_AND_INDENT();
  if (slot < 0) {
    return;
  }

  if (slot >= UI_WID_SAVE_SLOTS) {
    return;
  }

  if (! slot_valid[ slot ]) {
    CON("No game at that slot.");
    return;
  }

  game->fini();

  auto save_file = saved_dir + "saved-slot-" + std::to_string(slot);

  if (slot == UI_WID_SAVE_SLOTS - 1) {
    save_file = saved_dir + "saved-snapshot";
  }

  LOG("-");
  CON("INF: Loading %s", save_file.c_str());
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v");

  g_loading = true;
  load(save_file, *this);
  g_loading = false;

  sdl_config_update_all();

  LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  CON("INF: Loaded %s, seed %d", save_file.c_str(), seed);
  LOG("-");

  CON("Loaded the game from %s.", save_file.c_str());

  sdl_display_reset();
}

void Game::load_snapshot(void)
{
  TRACE_AND_INDENT();
  game->fini();

  auto save_file = saved_dir + "saved-snapshot";

  LOG("-");
  CON("INF: Loading %s", save_file.c_str());
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v");

  g_loading = true;
  load(save_file, *this);
  g_loading = false;

  sdl_config_update_all();

  LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  CON("INF: Loaded %s, seed %d", save_file.c_str(), seed);
  LOG("-");

  CON("Loaded the game from %s.", save_file.c_str());
}

void wid_load_destroy(class Game *game)
{
  TRACE_AND_INDENT();
  if (wid_load) {
    delete wid_load;
    wid_load = nullptr;
    game->state_reset("wid load destroy");
  }
}

static bool wid_load_key_up(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

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
                    CON("No game at that slot.");
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
                  TRACE_AND_INDENT();
                  CON("INF: Load game cancelled");
                  wid_load_destroy(game);
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static bool wid_load_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

static bool wid_load_mouse_up(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  auto slot = wid_get_int_context(w);
  game->load(slot);
  wid_load_destroy(game);
  return true;
}

static bool wid_load_saved_snapshot(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  game->load_snapshot();
  wid_load_destroy(game);
  return true;
}

static bool wid_load_cancel(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_load_destroy(game);
  return true;
}

void Game::load_select(void)
{
  TRACE_AND_INDENT();
  CON("INF: Loading a saved game, destroy old");

  if (wid_load) {
    return;
  }

  game_load_error = "";

  int   menu_height = UI_WID_SAVE_SLOTS + 8;
  int   menu_width  = UI_WID_POPUP_WIDTH_WIDE;
  point tl          = make_point(TERM_WIDTH / 2 - (menu_width / 2), TERM_HEIGHT / 2 - (menu_height / 2));
  point br          = make_point(TERM_WIDTH / 2 + (menu_width / 2), TERM_HEIGHT / 2 + (menu_height / 2));
  wid_load          = new WidPopup("Game load", tl, br, nullptr, "", false, false);

  wid_set_on_key_up(wid_load->wid_popup_container, wid_load_key_up);
  wid_set_on_key_down(wid_load->wid_popup_container, wid_load_key_down);

  {
    TRACE_AND_INDENT();
    auto p = wid_load->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "back");

    point tl = make_point(menu_width / 2 - 4, menu_height - 4);
    point br = make_point(menu_width / 2 + 3, menu_height - 2);

    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(w, wid_load_cancel);

    wid_set_pos(w, tl, br);
    wid_set_text(w, "BACK");
  }

  game_load_headers_only = true;

  wid_load->log("Choose a load slot.");

  int y_at = 3;
  for (auto slot = 0; slot < UI_WID_SAVE_SLOTS; slot++) {
    Game tmp;
    auto tmp_file = saved_dir + "saved-slot-" + std::to_string(slot);

    if (slot == UI_WID_SAVE_SLOTS - 1) {
      tmp_file = saved_dir + "saved-snapshot";
    }

    auto  p  = wid_load->wid_text_area->wid_text_area;
    auto  w  = wid_new_square_button(p, "load slot");
    point tl = make_point(0, y_at);
    point br = make_point(menu_width - 2, y_at);

    std::string s = std::to_string(slot) + ": ";
    if (! load(tmp_file, tmp)) {
      if (! game_load_error.empty()) {
        s += game_load_error;
        wid_set_style(w, UI_WID_STYLE_RED);
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
        wid_set_on_mouse_up(w, wid_load_saved_snapshot);
      } else {
        wid_set_on_mouse_up(w, wid_load_mouse_up);
      }
      wid_set_style(w, UI_WID_STYLE_GREEN);
      slot_valid[ slot ] = true;
    }
    wid_set_int_context(w, slot);

    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    y_at++;
  }
  game_load_headers_only = false;
  wid_update(wid_load->wid_text_area->wid_text_area);

  game->state_change(STATE_LOAD_MENU, "load select");

  //
  // Not sure why we need this; but the level ends up blank post loading.
  // It's probably a good idea anyway, in case we were in a difference gfx mode.
  //
  sdl_display_reset();
}

void wid_load_select(class Game *game) { game->load_select(); }

void game_load_last_config(const char *appdata)
{
  TRACE_NO_INDENT();

  CON("INI: Load config");

  game              = new Game(std::string(appdata));
  auto config_error = game->load_config();

  //
  // If the seed is set on the command line, make it stick
  //
  if (game->seed_manually_set) {
    game->seed_manually_set = true;
  }

  std::string version = "" MYVER "";

  if (game->config.version != version) {
    SDL_MSG_BOX("Config version change. Will need to reset config. Found version [%s]. Expected version [%s].",
                game->config.version.c_str(), version.c_str());
    delete game;
    game = new Game(std::string(appdata));
    reset_globals();
    game_save_config(game);
    g_errored = false;
  } else if (! config_error.empty()) {
    SDL_MSG_BOX("Config error: %s. Will need to reset config.", config_error.c_str());
    delete game;
    reset_globals();
    game = new Game(std::string(appdata));
    game_save_config(game);
    g_errored = false;
  }
}
