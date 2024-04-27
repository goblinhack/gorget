//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_game.hpp"
#include "my_hiscore.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_random_name.hpp"
#include "my_wids.hpp"

#include <SDL_mixer.h>

using Config = class Config_
{
public:
  std::string version = "" MYVER "";

  uint32_t serialized_size = {};
  //
  // Keep flags int size so the header size will change on a new flag.
  // It does not always for new bools.
  //
  float aspect_ratio = {};

  uint32_t ui_gfx_term_height = {};
  uint32_t ui_gfx_term_width  = {};

  bool debug_mode             = {};
  bool fps_counter            = {};
  bool gfx_allow_highdpi      = {};
  bool gfx_borderless         = {};
  bool gfx_fullscreen         = {};
  bool gfx_fullscreen_desktop = {};
  bool gfx_vsync_enable       = {};

  bool mouse_wheel_lr_negated = {};
  bool mouse_wheel_ud_negated = {};

  int16_t config_pix_height = {};
  int16_t config_pix_width  = {};
  //
  // The pixel perfect screen
  //
  int16_t game_pix_height = {};
  int16_t game_pix_width  = {};
  //
  // This is the size of the game map within the game FBO
  //
  int16_t map_pix_height = {};
  int16_t map_pix_width  = {};
  //
  // The user interface that can be higher res than the game
  //
  int16_t ui_pix_height = {};
  int16_t ui_pix_width  = {};
  //
  // The actual display res
  //
  int16_t window_pix_height = {};
  int16_t window_pix_width  = {};

  uint16_t ascii_gl_height = {};
  uint16_t ascii_gl_width  = {};
  uint32_t music_volume    = {};
  uint32_t sdl_delay       = {};
  uint32_t sound_volume    = {};

  SDL_Keysym key_attack     = {};
  SDL_Keysym key_console    = {};
  SDL_Keysym key_help       = {};
  SDL_Keysym key_load       = {};
  SDL_Keysym key_move_down  = {};
  SDL_Keysym key_move_left  = {};
  SDL_Keysym key_move_right = {};
  SDL_Keysym key_move_up    = {};
  SDL_Keysym key_quit       = {};
  SDL_Keysym key_save       = {};
  SDL_Keysym key_screenshot = {};
  SDL_Keysym key_unused1    = {};

  //
  // Ok, not really config...
  //
  HiScores hiscores;

  void fini(void);
  void reset(void);
};

class Game
{
public:
  //
  // Save file name, contains the date and other useful save slot info
  //
  std::string version = "" MYVER "";

  //
  // Current level
  //
  class Level *level {};

  //
  // Used to check for changes in the size of this struct.
  //
  uint32_t serialized_size {};

  //
  // If this was a saved game, which slot does it use.
  //
  uint8_t save_slot {};

  //
  // Title and seed name.
  //
  std::string save_meta;

  //
  // Saved file for this game.
  //
  std::string save_file;

  //
  // Appdata dir for saving logs.
  //
  std::string appdata;

  //
  // Save dir for saving games.
  //
  std::string saved_dir;

  //
  // User configuration.
  //
  Config config;

  //
  // All randomness jumps off of this.
  //
  uint32_t seed {};

  //
  // Human readable version of the above seed.
  //
  std::string seed_name {};

  //
  // Seed has been manually set, so stick with it
  //
  bool seed_manually_set {};

  //
  // Current fram-erate
  //
  uint32_t fps_value = {};

  /////////////////////////////////////////////////////////////////////////
  // not worth saving
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
  /////////////////////////////////////////////////////////////////////////

  //
  // Game is ending and levels are being destroyed.
  //
  bool is_being_destroyed {};

  //
  // Temporary. Global states
  //
  uint8_t state {STATE_MAIN_MENU};

  //
  // Temporary. Dampens mouse clicks
  //
  uint32_t last_mouse_down {};
  uint32_t last_pause {};

  /////////////////////////////////////////////////////////////////////////
  // not worth saving
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  /////////////////////////////////////////////////////////////////////////

  Game(std::string appdata);
  Game(void) = default;

  void create_level(void);
  void display(void);
  void fini(void);
  void init(void);
  void load_select(void);
  void save_select(void);
  void load_snapshot(void);
  void load(uint8_t slot);
  void load(void);
  void new_game(void);
  void save_config(void);
  void save_snapshot_check();
  void save_snapshot(void);
  void save(uint8_t slot);
  void save(void);
  void set_currently_saving_snapshot(void);
  void set_seed(void);
  void start(void);
  void state_change(uint8_t state, const std::string &);
  void state_reset(const std::string &);
  bool load(std::string save_file, class Game &target);
  bool save(std::string save_file);

  std::string load_config(void);
};

#include "game_load.hpp"
#include "game_save.hpp"

void Config::fini(void) { TRACE_AND_INDENT(); }

void Config::reset(void)
{
  TRACE_AND_INDENT();
  config_pix_height      = {};
  config_pix_width       = {};
  debug_mode             = false;
  fps_counter            = false;
  game_pix_height        = {};
  game_pix_width         = {};
  map_pix_height         = {};
  map_pix_width          = {};
  gfx_allow_highdpi      = false;
  gfx_borderless         = true;
  gfx_fullscreen_desktop = true;
  gfx_fullscreen         = false;
  gfx_vsync_enable       = true;
  mouse_wheel_lr_negated = false;
  mouse_wheel_ud_negated = false;
  ui_gfx_term_height     = {TERM_GFX_HEIGHT_DEF};
  ui_gfx_term_width      = {TERM_GFX_WIDTH_DEF};
  ui_pix_height          = {};
  ui_pix_width           = {};
  version                = "" MYVER "";
  aspect_ratio           = {};
  window_pix_height      = {};
  window_pix_width       = {};

  key_attack.sym     = SDLK_SPACE;
  key_help.sym       = SDLK_h;
  key_load.sym       = SDLK_F11;
  key_move_down.sym  = SDLK_s;
  key_move_left.sym  = SDLK_a;
  key_move_right.sym = SDLK_d;
  key_move_up.sym    = SDLK_w;
  key_quit.sym       = SDLK_q;
  key_quit.mod       = KMOD_SHIFT;
  key_save.sym       = SDLK_F12;
  key_screenshot.sym = SDLK_F10;
  key_console.sym    = SDLK_TAB;
  key_console.mod    = KMOD_SHIFT;
  music_volume       = {MIX_MAX_VOLUME / 3};
  sdl_delay          = 0;
  sound_volume       = {MIX_MAX_VOLUME / 2};

  // key_unused1.sym  = SDLK_TAB;
  // key_unused1.mod  = KMOD_NUM;
}

void game_config_reset(class Game *game) { game->config.reset(); }

Game::Game(std::string appdata)
{
  TRACE_AND_INDENT();

  config.reset();

  this->appdata = appdata;

  saved_dir = appdata + DIR_SEP + "gorget" + DIR_SEP;
  save_slot = 1;

  save_meta = "seed " + seed_name + ", ";
  save_meta += string_timestamp();

  save_file = saved_dir + "saved-slot-" + std::to_string(save_slot);
}

void Game::start(void) { TRACE_NO_INDENT(); }

void Game::init(void)
{
  LOG("Game init");
  TRACE_AND_INDENT();

  set_seed();
  start();
}

void game_init(class Game *game) { game->init(); }

void Game::fini(void)
{
  LOG("Game fini");
  TRACE_AND_INDENT();

  if (level) {
    auto l = level;
    level  = nullptr;
    delete l;
  }
}

void game_fini(class Game *game) { game->fini(); }

void game_save_config(class Game *game) { game->save_config(); }

void Game::set_seed(void)
{
  if (g_opt_seed_name != "") {
    seed_name = g_opt_seed_name;
  } else {
    seed_name = random_name(sizeof("4294967295") - 1);
  }

  seed = string_to_hash(seed_name);

  LOG("Set seed, name '%s', seed %u", seed_name.c_str(), seed);
  pcg_srand(seed);
}

void Game::create_level(void)
{
  LOG("Game create level");
  TRACE_AND_INDENT();

  set_seed();

  if (level) {
    TRACE_NO_INDENT();

    auto l = level;
    if (l) {
      LOG("Remove old level");
      delete l;
      level = nullptr;
    }
  }

  {
    TRACE_NO_INDENT();
    LOG("Level create");
    level = new Level();
  }
}

void game_create_level(class Game *game) { game->create_level(); }

void Game::display(void)
{
  if (level) {
    level->tick();
    level->anim();
    level->display();
  }
}

void game_display(class Game *game) { game->display(); }

std::string gama_state_to_string(int state)
{
  switch (state) {
    case STATE_MAIN_MENU : return "MAIN_MENU";
    case STATE_PLAYING : return "PLAYING";
    case STATE_LOAD_MENU : return "LOAD_MENU";
    case STATE_SAVE_MENU : return "SAVE_MENU";
    case STATE_QUIT_MENU : return "QUIT_MENU";
    case STATE_KEYBOARD_MENU : return "KEYBOARD_MENU";
    default : ERR("Unhandled game state"); return "?";
  }
}

//
// Reset to the default state, either playing the game, or starting up.
//
void Game::state_reset(const std::string &why)
{
  if (level) {
    state_change(STATE_PLAYING, why);
  } else {
    state_change(STATE_MAIN_MENU, why);
  }
}

void game_state_reset(class Game *game, const char *why) { game->state_reset(why); }

void Game::state_change(uint8_t new_state, const std::string &why)
{
  TRACE_NO_INDENT();

  if (game->state == new_state) {
    return;
  }

  auto old_state = state;

  //
  // Set here to stop recursion.
  //
  state = new_state;

  //
  // Why oh why change state
  //
  CON("INF: Game state change: %s -> %s, reason %s", gama_state_to_string(old_state).c_str(),
      gama_state_to_string(new_state).c_str(), why.c_str());
  TRACE_AND_INDENT();

  //
  // Actions for the new state
  //
  switch (new_state) {
    case STATE_MAIN_MENU :
      wid_load_destroy(game);
      wid_save_destroy(game);
      wid_quit_destroy(game);
      wid_rightbar_fini(game);
      break;
    case STATE_PLAYING :
      wid_main_menu_destroy(game);
      wid_load_destroy(game);
      wid_save_destroy(game);
      wid_quit_destroy(game);
      break;
    case STATE_KEYBOARD_MENU :
    case STATE_LOAD_MENU :
    case STATE_SAVE_MENU :
    case STATE_QUIT_MENU : break;
  }

  //
  // In case some cleanup above changed state
  //
  state = new_state;
}

void game_state_change(class Game *game, uint8_t new_state, const char *why)
{
  game->state_change(new_state, std::string(why));
}

void game_load_config(class Game *game) { game->load_config(); }

class HiScores *game_hiscores_get(class Game *game) { return &game->config.hiscores; }

uint32_t game_last_mouse_down_get(class Game *game) { return game->last_mouse_down; }
void     game_last_mouse_down_set(class Game *game, uint32_t val) { game->last_mouse_down = val; }

uint32_t game_last_pause_get(class Game *game) { return game->last_pause; }
void     game_last_pause_set(class Game *game, uint32_t val) { game->last_pause = val; }

uint32_t game_serialized_size_get(class Game *) { return game->serialized_size; }
void     game_serialized_size_set(class Game *, uint32_t val) { game->serialized_size = val; }

float game_aspect_ratio_get(class Game *) { return game->config.aspect_ratio; }
void  game_aspect_ratio_set(class Game *, float val) { game->config.aspect_ratio = val; }

uint32_t game_ui_gfx_term_height_get(class Game *) { return game->config.ui_gfx_term_height; }
void     game_ui_gfx_term_height_set(class Game *, uint32_t val) { game->config.ui_gfx_term_height = val; }

uint32_t game_ui_gfx_term_width_get(class Game *) { return game->config.ui_gfx_term_width; }
void     game_ui_gfx_term_width_set(class Game *, uint32_t val) { game->config.ui_gfx_term_width = val; }

bool game_debug_mode_get(class Game *) { return game->config.debug_mode; }
void game_debug_mode_set(class Game *, bool val) { game->config.debug_mode = val; }

bool game_fps_counter_get(class Game *) { return game->config.fps_counter; }
void game_fps_counter_set(class Game *, bool val) { game->config.fps_counter = val; }

uint32_t game_fps_value_get(class Game *) { return game->fps_value; }
void     game_fps_value_set(class Game *, uint32_t val) { game->fps_value = val; }

bool game_gfx_allow_highdpi_get(class Game *) { return game->config.gfx_allow_highdpi; }
void game_gfx_allow_highdpi_set(class Game *, bool val) { game->config.gfx_allow_highdpi = val; }

bool game_gfx_borderless_get(class Game *) { return game->config.gfx_borderless; }
void game_gfx_borderless_set(class Game *, bool val) { game->config.gfx_borderless = val; }

bool game_gfx_fullscreen_get(class Game *) { return game->config.gfx_fullscreen; }
void game_gfx_fullscreen_set(class Game *, bool val) { game->config.gfx_fullscreen = val; }

bool game_gfx_fullscreen_desktop_get(class Game *) { return game->config.gfx_fullscreen_desktop; }
void game_gfx_fullscreen_desktop_set(class Game *, bool val) { game->config.gfx_fullscreen_desktop = val; }

bool game_gfx_vsync_enable_get(class Game *) { return game->config.gfx_vsync_enable; }
void game_gfx_vsync_enable_set(class Game *, bool val) { game->config.gfx_vsync_enable = val; }

bool game_mouse_wheel_lr_negated_get(class Game *) { return game->config.mouse_wheel_lr_negated; }
void game_mouse_wheel_lr_negated_set(class Game *, bool val) { game->config.mouse_wheel_lr_negated = val; }

bool game_mouse_wheel_ud_negated_get(class Game *) { return game->config.mouse_wheel_ud_negated; }
void game_mouse_wheel_ud_negated_set(class Game *, bool val) { game->config.mouse_wheel_ud_negated = val; }

int16_t game_config_pix_height_get(class Game *) { return game->config.config_pix_height; }
void    game_config_pix_height_set(class Game *, int16_t val) { game->config.config_pix_height = val; }

int16_t game_config_pix_width_get(class Game *) { return game->config.config_pix_width; }
void    game_config_pix_width_set(class Game *, int16_t val) { game->config.config_pix_width = val; }

int16_t game_pix_height_get(class Game *) { return game->config.game_pix_height; }
void    game_pix_height_set(class Game *, int16_t val) { game->config.game_pix_height = val; }

int16_t game_pix_width_get(class Game *) { return game->config.game_pix_width; }
void    game_pix_width_set(class Game *, int16_t val) { game->config.game_pix_width = val; }

int16_t game_map_pix_height_get(class Game *) { return game->config.map_pix_height; }
void    game_map_pix_height_set(class Game *, int16_t val) { game->config.map_pix_height = val; }

int16_t game_map_pix_width_get(class Game *) { return game->config.map_pix_width; }
void    game_map_pix_width_set(class Game *, int16_t val) { game->config.map_pix_width = val; }

int16_t game_ui_pix_height_get(class Game *) { return game->config.ui_pix_height; }
void    game_ui_pix_height_set(class Game *, int16_t val) { game->config.ui_pix_height = val; }

int16_t game_ui_pix_width_get(class Game *) { return game->config.ui_pix_width; }
void    game_ui_pix_width_set(class Game *, int16_t val) { game->config.ui_pix_width = val; }

int16_t game_window_pix_height_get(class Game *) { return game->config.window_pix_height; }
void    game_window_pix_height_set(class Game *, int16_t val) { game->config.window_pix_height = val; }

int16_t game_window_pix_width_get(class Game *) { return game->config.window_pix_width; }
void    game_window_pix_width_set(class Game *, int16_t val) { game->config.window_pix_width = val; }

uint16_t game_ascii_gl_height_get(class Game *) { return game->config.ascii_gl_height; }
void     game_ascii_gl_height_set(class Game *, uint16_t val) { game->config.ascii_gl_height = val; }

uint16_t game_ascii_gl_width_get(class Game *) { return game->config.ascii_gl_width; }
void     game_ascii_gl_width_set(class Game *, uint16_t val) { game->config.ascii_gl_width = val; }

uint32_t game_music_volume_get(class Game *) { return game->config.music_volume; }
void     game_music_volume_set(class Game *, uint32_t val) { game->config.music_volume = val; }

uint32_t game_sdl_delay_get(class Game *) { return game->config.sdl_delay; }
void     game_sdl_delay_set(class Game *, uint32_t val) { game->config.sdl_delay = val; }

uint32_t game_sound_volume_get(class Game *) { return game->config.sound_volume; }
void     game_sound_volume_set(class Game *, uint32_t val) { game->config.sound_volume = val; }

class Level *game_level_get(class Game *game) { return game->level; }
void         game_level_set(class Game *game, class Level *val) { game->level = val; }

const char *game_seed_name_get(class Game *game) { return game->seed_name.c_str(); }
void        game_seed_name_set(class Game *game, const char *val) { game->seed_name = std::string(val); }

SDL_Keysym game_key_attack_get(class Game *game) { return game->config.key_attack; }
void       game_key_attack_set(class Game *game, SDL_Keysym key) { game->config.key_attack = key; }

SDL_Keysym game_key_console_get(class Game *game) { return game->config.key_console; }
void       game_key_console_set(class Game *game, SDL_Keysym key) { game->config.key_console = key; }

SDL_Keysym game_key_help_get(class Game *game) { return game->config.key_help; }
void       game_key_help_set(class Game *game, SDL_Keysym key) { game->config.key_help = key; }

SDL_Keysym game_key_load_get(class Game *game) { return game->config.key_load; }
void       game_key_load_set(class Game *game, SDL_Keysym key) { game->config.key_load = key; }

SDL_Keysym game_key_move_down_get(class Game *game) { return game->config.key_move_down; }
void       game_key_move_down_set(class Game *game, SDL_Keysym key) { game->config.key_move_down = key; }

SDL_Keysym game_key_move_left_get(class Game *game) { return game->config.key_move_left; }
void       game_key_move_left_set(class Game *game, SDL_Keysym key) { game->config.key_move_left = key; }

SDL_Keysym game_key_move_right_get(class Game *game) { return game->config.key_move_right; }
void       game_key_move_right_set(class Game *game, SDL_Keysym key) { game->config.key_move_right = key; }

SDL_Keysym game_key_move_up_get(class Game *game) { return game->config.key_move_up; }
void       game_key_move_up_set(class Game *game, SDL_Keysym key) { game->config.key_move_up = key; }

SDL_Keysym game_key_quit_get(class Game *game) { return game->config.key_quit; }
void       game_key_quit_set(class Game *game, SDL_Keysym key) { game->config.key_quit = key; }

SDL_Keysym game_key_save_get(class Game *game) { return game->config.key_save; }
void       game_key_save_set(class Game *game, SDL_Keysym key) { game->config.key_save = key; }

SDL_Keysym game_key_screenshot_get(class Game *game) { return game->config.key_screenshot; }
void       game_key_screenshot_set(class Game *game, SDL_Keysym key) { game->config.key_screenshot = key; }

SDL_Keysym game_key_unused1_get(class Game *game) { return game->config.key_unused1; }
void       game_key_unused1_set(class Game *game, SDL_Keysym key) { game->config.key_unused1 = key; }
