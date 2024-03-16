//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_alloc.hpp"
#include "my_sdl_proto.hpp"
#include "my_serialize.hpp"
#include "my_wid_popup.hpp"
#include "third-party/minilzo.hpp"

WidPopup *wid_save;
void      wid_save_destroy(void);

extern bool     game_load_headers_only;
bool            game_save_config_only;
int             GAME_SAVE_MARKER_EOL    = 123456;
int             GAME_SAVE_MARKER_CONFIG = 987654;
extern uint32_t csum(char *mem, uint32_t len);

#define WRITE_MAGIC(m)                                                                                               \
  {                                                                                                                  \
    uint32_t magic = m;                                                                                              \
    out << bits(magic);                                                                                              \
  }

std::ostream &operator<<(std::ostream &out, Bits< const SDL_Keysym & > const my)
{
  TRACE_AND_INDENT();
  out << bits(my.t.scancode);
  out << bits(my.t.sym);
  out << bits(my.t.mod);
  out << bits(my.t.unused);
  return out;
}

std::ostream &operator<<(std::ostream &out, Bits< const Config & > const my)
{
  TRACE_AND_INDENT();
  out << bits(my.t.version);
  uint32_t serialized_size = sizeof(Config);
  out << bits(serialized_size);

  out << bits(my.t.ascii_gl_height);
  out << bits(my.t.ascii_gl_width);
  out << bits(my.t.config_pix_height);
  out << bits(my.t.config_pix_width);
  out << bits(my.t.debug_mode);
  out << bits(my.t.fps_counter);
  out << bits(my.t.game_pix_height);
  out << bits(my.t.game_pix_width);
  out << bits(my.t.map_pix_height);
  out << bits(my.t.map_pix_width);
  out << bits(my.t.game_pix_scale_height);
  out << bits(my.t.game_pix_scale_width);
  out << bits(my.t.gfx_allow_highdpi);
  out << bits(my.t.gfx_borderless);
  out << bits(my.t.gfx_fullscreen);
  out << bits(my.t.gfx_fullscreen_desktop);
  out << bits(my.t.gfx_vsync_enable);
  out << bits(my.t.mouse_wheel_lr_negated);
  out << bits(my.t.mouse_wheel_ud_negated);
  out << bits(my.t.key_action0);
  out << bits(my.t.key_action1);
  out << bits(my.t.key_action2);
  out << bits(my.t.key_action3);
  out << bits(my.t.key_action4);
  out << bits(my.t.key_action5);
  out << bits(my.t.key_action6);
  out << bits(my.t.key_action7);
  out << bits(my.t.key_action8);
  out << bits(my.t.key_action9);
  out << bits(my.t.key_attack);
  out << bits(my.t.key_console);
  out << bits(my.t.key_unused1);
  out << bits(my.t.key_unused2);
  out << bits(my.t.key_unused3);
  out << bits(my.t.key_unused4);
  out << bits(my.t.key_unused5);
  out << bits(my.t.key_unused6);
  out << bits(my.t.key_unused7);
  out << bits(my.t.key_unused8);
  out << bits(my.t.key_unused9);
  out << bits(my.t.key_unused10);
  out << bits(my.t.key_unused11);
  out << bits(my.t.key_unused12);
  out << bits(my.t.key_unused13);
  out << bits(my.t.key_unused14);
  out << bits(my.t.key_unused15);
  out << bits(my.t.key_unused16);
  out << bits(my.t.key_unused17);
  out << bits(my.t.key_unused18);
  out << bits(my.t.key_unused19);
  out << bits(my.t.key_unused20);
  out << bits(my.t.key_drop);
  out << bits(my.t.key_help);
  out << bits(my.t.key_jump);
  out << bits(my.t.key_load);
  out << bits(my.t.key_move_down);
  out << bits(my.t.key_move_left);
  out << bits(my.t.key_move_right);
  out << bits(my.t.key_move_up);
  out << bits(my.t.key_quit);
  out << bits(my.t.key_save);
  out << bits(my.t.key_screenshot);
  out << bits(my.t.music_volume);
  out << bits(my.t.sdl_delay);
  out << bits(my.t.sound_volume);
  out << bits(my.t.ui_pix_height);
  out << bits(my.t.ui_pix_width);
  out << bits(my.t.ui_gfx_term_height);
  out << bits(my.t.ui_gfx_term_width);
  out << bits(my.t.aspect_ratio);
  out << bits(my.t.window_pix_height);
  out << bits(my.t.window_pix_width);

  out << bits(g_opt_seed_name);
  out << bits(my.t.hiscores);

  auto eol = GAME_SAVE_MARKER_CONFIG;
  out << bits(eol);

  return out;
}

std::ostream &operator<<(std::ostream &out, Bits< const class Game & > const my)
{
  TRACE_AND_INDENT();
  uint32_t serialized_size = (uint32_t) (sizeof(Game));
  out << bits(my.t.version);
  out << bits(serialized_size);
  out << bits(my.t.save_slot);
  out << bits(my.t.save_meta);
  out << bits(my.t.save_file);
  out << bits(my.t.appdata);
  out << bits(my.t.saved_dir);
  out << bits(my.t.config);

  out << bits(my.t.seed);
  out << bits(my.t.seed_manually_set);
  out << bits(my.t.seed_name);
  out << bits(my.t.frame_count);
  out << bits(my.t.fps_value);

  return out;
}

bool Game::save(std::string file_to_save)
{
  TRACE_AND_INDENT();
  std::stringstream s(std::ios::in | std::ios::out | std::ios::binary);

  const class Game &c = *this;
  s << bits(c);

  //
  // Get the pre compress buffer
  //
  auto data = s.str();
  s.seekg(0, std::ios::end);
  lzo_uint uncompressed_len = s.tellg();
  s.seekg(0, std::ios::beg);

  HEAP_ALLOC(uncompressed, uncompressed_len);
  HEAP_ALLOC(compressed, uncompressed_len);
  memcpy(uncompressed, data.c_str(), uncompressed_len);

#if 0
  IF_DEBUG3 {
    std::cout << "before compression ";
    (void) hexdump((const unsigned char*)uncompressed, uncompressed_len);
  }
#endif

  if (lzo_init() != LZO_E_OK) {
    ERR("LZO init fail: Enable '-DLZO_DEBUG' for diagnostics)");
  }

  HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);

  lzo_uint compressed_len = 0;
  int      r
      = lzo1x_1_compress((lzo_bytep) uncompressed, uncompressed_len, (lzo_bytep) compressed, &compressed_len, wrkmem);
  if (r == LZO_E_OK) {
    LOG("INF: Saved as %s, compress %luMb -> %luMb", file_to_save.c_str(),
        (unsigned long) uncompressed_len / (1024 * 1024), (unsigned long) compressed_len / (1024 * 1024));
  } else {
    ERR("LZO internal error - compression failed: %d", r);
    return false;
  }

  //
  // Uncompress and check the data matches
  //
  IF_DEBUG3
  {
    HEAP_ALLOC(tmp_compressed, compressed_len);
    HEAP_ALLOC(tmp_uncompressed, uncompressed_len);
    memcpy(tmp_compressed, compressed, compressed_len);

    lzo_uint new_len = 0;
    int      r = lzo1x_decompress((lzo_bytep) tmp_compressed, compressed_len, (lzo_bytep) tmp_uncompressed, &new_len,
                                  nullptr);
    if (r == LZO_E_OK && new_len == uncompressed_len) {
      if (memcmp(tmp_uncompressed, uncompressed, uncompressed_len)) {
        ERR("LZO compress-decompress failed");
      }
    } else {
      /* this should NEVER happen */
      ERR("LZO internal error - decompression failed: %d", r);
      return false;
    }
  }

  //
  // Dump the post compress buffer
  //
#if 0
  IF_DEBUG3 {
    std::cout << "after compression ";
    (void) hexdump((const unsigned char *)compressed, compressed_len);
  }
#endif

  //
  // Save the post compress buffer
  //
  uint32_t cs = csum((char *) uncompressed, uncompressed_len);

  auto ofile = fopen(file_to_save.c_str(), "wb");
  if (! ofile) {
    ERR("Failed to open %s for writing: %s", file_to_save.c_str(), strerror(errno));
    return false;
  }
  CON("INF: Opened [%s] for writing", file_to_save.c_str());

  fwrite((char *) &uncompressed_len, sizeof(uncompressed_len), 1, ofile);
  fwrite((char *) &cs, sizeof(cs), 1, ofile);
  fwrite(compressed, compressed_len, 1, ofile);
  fclose(ofile);

  free(uncompressed);
  free(compressed);
  free(wrkmem);

  return true;
}

void Game::save(void)
{
  TRACE_AND_INDENT();
  LOG("-");
  CON("INF: Saving %s", save_file.c_str());
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v");

  save(save_file);

  LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  CON("INF: Saved %s, seed %u", save_file.c_str(), seed);
  LOG("-");
}

void Game::save(uint8_t slot)
{
  TRACE_AND_INDENT();
  if (slot < 0) {
    return;
  }

  if (slot >= UI_WID_SAVE_SLOTS) {
    return;
  }

  auto save_file = saved_dir + "saved-slot-" + std::to_string(slot);

  LOG("-");
  CON("INF: Saving %s", save_file.c_str());
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v");

  save(save_file);

  LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  CON("INF: Saved %s, seed %u", save_file.c_str(), seed);
  LOG("-");

  CON("Saved the game to %s.", save_file.c_str());
}

void Game::save_snapshot(void)
{
  CON("Autosaving...");

  TRACE_AND_INDENT();

  auto save_file = saved_dir + "saved-snapshot";

  LOG("-");
  CON("INF: Saving %s", save_file.c_str());
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v");

  save(save_file);

  LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
  LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  CON("INF: Saved %s, seed %u", save_file.c_str(), seed);
  LOG("-");

  CON("%%fg=green$Autosaved.%%fg=reset$");
}

void Game::save_config(void)
{
  TRACE_AND_INDENT();
  auto          filename = saved_dir + "config";
  std::ofstream out(filename, std::ios::binary);
  if (! out) {
    ERR("Failed to open %s for writing: %s", filename.c_str(), strerror(errno));
    return;
  }
  CON("INF: Opened [%s] for writing", filename.c_str());
  const Config &c = game->config;
  out << bits(c);
}

void wid_save_destroy(void)
{
  TRACE_AND_INDENT();
  if (wid_save) {
    delete wid_save;
    wid_save = nullptr;
    game->change_state(Game::STATE_NORMAL, "save destroy");
  }
}

static uint8_t wid_save_key_up(Widp w, const struct SDL_Keysym *key)
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
            TRACE_AND_INDENT();
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
                  TRACE_AND_INDENT();
                  int slot = c - '0';
                  game->save(slot);
                  wid_save_destroy();
                  return true;
                }
              case 'b' :
              case SDLK_ESCAPE :
                {
                  TRACE_AND_INDENT();
                  CON("INF: Save game cancelled");
                  wid_save_destroy();
                  return true;
                }
            }
          }
      }
  }

  return true;
}

static uint8_t wid_save_key_down(Widp w, const struct SDL_Keysym *key)
{
  TRACE_AND_INDENT();

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  return true;
}

static uint8_t wid_save_mouse_up(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  auto slot = wid_get_int_context(w);
  game->save(slot);
  wid_save_destroy();
  return true;
}

static uint8_t wid_save_cancel(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  wid_save_destroy();
  return true;
}

void Game::wid_save_select(void)
{
  TRACE_AND_INDENT();

  if (wid_save) {
    return;
  }

  int   menu_height = UI_WID_SAVE_SLOTS + 8;
  int   menu_width  = UI_WID_POPUP_WIDTH_WIDE;
  point tl          = make_point(TERM_WIDTH / 2 - (menu_width / 2), TERM_HEIGHT / 2 - (menu_height / 2));
  point br          = make_point(TERM_WIDTH / 2 + (menu_width / 2), TERM_HEIGHT / 2 + (menu_height / 2));
  wid_save          = new WidPopup("Game load", tl, br, nullptr, "", false, false);

  wid_set_on_key_up(wid_save->wid_popup_container, wid_save_key_up);
  wid_set_on_key_down(wid_save->wid_popup_container, wid_save_key_down);

  {
    TRACE_AND_INDENT();
    auto p = wid_save->wid_text_area->wid_text_area;
    auto w = wid_new_square_button(p, "back");

    point tl = make_point(menu_width / 2 - 4, menu_height - 4);
    point br = make_point(menu_width / 2 + 3, menu_height - 2);

    wid_set_style(w, UI_WID_STYLE_NORMAL);
    wid_set_on_mouse_up(w, wid_save_cancel);

    wid_set_pos(w, tl, br);
    wid_set_text(w, "BACK");
  }

  game_load_headers_only = true;

  wid_save->log(UI_LOGGING_EMPTY_LINE);
  wid_save->log("Choose a save slot.");

  int y_at = 3;
  for (auto slot = 0; slot < UI_WID_SAVE_SLOTS; slot++) {
    Game tmp;
    auto tmp_file = saved_dir + "saved-slot-" + std::to_string(slot);

    if (slot == UI_WID_SAVE_SLOTS - 1) {
      tmp_file = saved_dir + "saved-snapshot";
    }

    auto  p  = wid_save->wid_text_area->wid_text_area;
    auto  w  = wid_new_square_button(p, "save slot");
    point tl = make_point(0, y_at);
    point br = make_point(menu_width - 2, y_at);

    std::string s = std::to_string(slot) + " ";
    if (! load(tmp_file, tmp)) {
      if (slot == UI_WID_SAVE_SLOTS - 1) {
        s += "<no snapshot>";
      } else {
        s += "<empty>";
      }
      wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
    } else {
      if (slot == UI_WID_SAVE_SLOTS - 1) {
        s += "snapshot: " + tmp.save_meta;
      } else {
        s += tmp.save_meta;
      }
      wid_set_style(w, UI_WID_STYLE_HORIZ_LIGHT);
      wid_set_style(w, UI_WID_STYLE_GREEN);
    }

    if (slot == UI_WID_SAVE_SLOTS - 1) {
      //
      // Cannot save over
      //
    } else {
      wid_set_on_mouse_up(w, wid_save_mouse_up);
      wid_set_int_context(w, slot);
    }

    wid_set_pos(w, tl, br);
    wid_set_text(w, s);
    y_at++;
  }
  game_load_headers_only = false;
  wid_update(wid_save->wid_text_area->wid_text_area);

  game->change_state(Game::STATE_SAVE_MENU, "save select");
}
