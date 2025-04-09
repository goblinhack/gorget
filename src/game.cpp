//
// Copyright goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_game.hpp"
#include "my_hiscore.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_random.hpp"
#include "my_random_name.hpp"
#include "my_wid_topcon.hpp"
#include "my_wids.hpp"

#include <SDL_mixer.h>

static SDL_Keysym no_key;

using Config = class Config_
{
public:
  std::string version = "" MYVER "";

  //
  // Used to check for changes in the size of this struct.
  //
  int serialized_size = {};

  //
  // Keep flags int size so the header size will change on a new flag.
  // It does not always for new bools.
  //
  float aspect_ratio = {};

  int ui_term_height = {};
  int ui_term_width  = {};

  bool debug_mode             = {};
  bool fps_counter            = {};
  bool gfx_allow_highdpi      = {};
  bool gfx_borderless         = {};
  bool gfx_fullscreen         = {};
  bool gfx_fullscreen_desktop = {};
  bool gfx_vsync_enable       = {};

  bool mouse_wheel_lr_negated = {};
  bool mouse_wheel_ud_negated = {};

  int config_pix_height = {};
  int config_pix_width  = {};

  //
  // The visible map FBO
  //
  int map_fbo_height = {};
  int map_fbo_width  = {};

  //
  // The actual display resolution
  //
  int window_pix_height = {};
  int window_pix_width  = {};

  //
  // The number of tiles on screen.
  //
  int tiles_visible_across;
  int tiles_visible_down;

  int ascii_pix_height = {};
  int ascii_pix_width  = {};
  int music_volume     = {};
  int sdl_delay        = {};
  int sound_volume     = {};

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
  SDL_Keysym key_unused2    = {};
  SDL_Keysym key_unused3    = {};
  SDL_Keysym key_unused4    = {};
  SDL_Keysym key_unused5    = {};
  SDL_Keysym key_unused6    = {};
  SDL_Keysym key_unused7    = {};
  SDL_Keysym key_unused8    = {};
  SDL_Keysym key_unused9    = {};
  SDL_Keysym key_unused10   = {};
  SDL_Keysym key_unused11   = {};
  SDL_Keysym key_unused12   = {};
  SDL_Keysym key_unused13   = {};
  SDL_Keysym key_unused14   = {};
  SDL_Keysym key_unused15   = {};
  SDL_Keysym key_unused16   = {};
  SDL_Keysym key_unused17   = {};
  SDL_Keysym key_unused18   = {};
  SDL_Keysym key_unused19   = {};
  SDL_Keysym key_zoom       = {};

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
  // All levels
  //
  Levelsp levels {};

  //
  // Used to check for changes in the size of this struct.
  //
  int serialized_size {};

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
  // Human readable version of the above seed.
  //
  std::string seed_name {};

  //
  // All randomness jumps off of this.
  //
  uint32_t seed_num {};

  //
  // The source of the seed
  //
  SeedSource seed_source {SEED_SOURCE_RANDOM};

  //
  // Current fram-erate
  //
  int fps_value = {};

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
  GameState state {STATE_MAIN_MENU};

  //
  // Temporary. Dampens mouse clicks
  //
  int last_mouse_down {};

  //
  // These are the onscreen map pixel co-ords.
  //
  int visible_map_tl_x;
  int visible_map_tl_y;
  int visible_map_br_x;
  int visible_map_br_y;

  /////////////////////////////////////////////////////////////////////////
  // not worth saving
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  /////////////////////////////////////////////////////////////////////////

  Game(std::string appdata);
  Game(void) = default;

  void create_levels(void);
  void start_playing(void);
  void destroy_levels(void);
  void display(void);
  void fini(void);
  void init(void);
  void load_select(void);
  void save_select(void);
  void load_snapshot(void);
  void load(int slot);
  void save_config(void);
  void save_snapshot(void);
  void save(int slot);
  void seed_set(const char *seed = nullptr);
  void state_change(GameState state, const std::string &);
  void state_reset(const std::string &);
  bool load(std::string save_file, class Game &target);
  bool save(std::string save_file);

  std::string load_config(void);
};

class Game *game;

#include "game_load.hpp"
#include "game_save.hpp"

void Config::fini(void)
{
  LOG("Game fini");
  TRACE_AND_INDENT();
}

void Config::reset(void)
{
  LOG("Game reset");
  TRACE_AND_INDENT();

  config_pix_height      = {};
  config_pix_width       = {};
  debug_mode             = false;
  fps_counter            = false;
  map_fbo_height         = {};
  map_fbo_width          = {};
  gfx_allow_highdpi      = false;
  gfx_borderless         = true;
  gfx_fullscreen_desktop = true;
  gfx_fullscreen         = false;
  gfx_vsync_enable       = true;
  mouse_wheel_lr_negated = false;
  mouse_wheel_ud_negated = false;
  ui_term_height         = {TERM_HEIGHT_DEF};
  ui_term_width          = {TERM_WIDTH_DEF};
  version                = "" MYVER "";
  aspect_ratio           = {};
  window_pix_height      = {};
  window_pix_width       = {};
  tiles_visible_across   = MAP_TILES_ACROSS_DEF;
  tiles_visible_down     = MAP_TILES_DOWN_DEF;

  key_attack.sym     = SDLK_SPACE;
  key_help.sym       = SDLK_h;
  key_load.sym       = SDLK_F12;
  key_move_down.sym  = SDLK_s;
  key_move_left.sym  = SDLK_a;
  key_move_right.sym = SDLK_d;
  key_move_up.sym    = SDLK_w;
  key_quit.sym       = SDLK_q;
  key_save.sym       = SDLK_F1;
  key_screenshot.sym = SDLK_F10;
  key_zoom.sym       = SDLK_z;
  key_console.sym    = SDLK_BACKQUOTE;
  music_volume       = {MIX_MAX_VOLUME / 3};
  sdl_delay          = 10;
  sound_volume       = {MIX_MAX_VOLUME / 2};

  key_unused1.sym = SDLK_TAB;
}

void game_config_reset(Gamep g) { g->config.reset(); }

Game::Game(std::string vappdata)
{
  LOG("Game load %s", vappdata.c_str());
  TRACE_AND_INDENT();

  auto g = this;

  config.reset();

  g->appdata = vappdata;

  saved_dir = appdata + DIR_SEP + "gorget" + DIR_SEP;
  save_slot = 1;

  if (seed_name != "") {
    save_meta = "seed " + seed_name + ", ";
  }
  save_meta += string_timestamp();

  save_file = saved_dir + "saved-slot-" + std::to_string(save_slot);
}

void Game::init(void)
{
  LOG("Game init");
  TRACE_AND_INDENT();

  seed_set();
}
void game_init(Gamep g) { g->init(); }

void Game::fini(void)
{
  LOG("Game fini");
  TRACE_AND_INDENT();

  state_change(STATE_QUITTING, "quitting");
  destroy_levels();
}
void game_fini(Gamep g)
{
  TRACE_NO_INDENT();

  if (! g) {
    return;
  }

  g->fini();
  delete g;
  game = NULL;
}

void game_save_config(Gamep g)
{
  TRACE_NO_INDENT();

  if (! g) {
    ERR("No game pointer set");
    return;
  }

  g->save_config();
}

void Game::seed_set(const char *maybe_seed)
{
  TRACE_NO_INDENT();

  seed_source = SEED_SOURCE_RANDOM;

  if (maybe_seed) {
    LOG("Set seed from ui");
    seed_name   = std::string(maybe_seed);
    seed_source = SEED_SOURCE_USER;
  } else if (g_opt_seed_name != "") {
    LOG("Set seed from command line");
    seed_name   = g_opt_seed_name;
    seed_source = SEED_SOURCE_COMMAND_LINE;
  } else {
    LOG("Set random seed, none manually set");
    seed_name = random_name(SIZEOF("4294967295") - 1);
  }

  //
  // If a number, use that as the seed, else convert the string to hash number
  //
  char *p;
  seed_num = strtol(seed_name.c_str(), &p, 10);
  if (*p) {
    //
    // Conversion failed, not a number
    //
    seed_num = string_to_hash(seed_name);
  }

  LOG("Set seed, name '%s', seed %u", seed_name.c_str(), seed_num);
  pcg_srand(seed_num);
}

void game_seed_name_set(Gamep g, const char *maybe_seed)
{
  TRACE_NO_INDENT();

  if (! g) {
    ERR("No game pointer set");
    return;
  }

  g->seed_set(maybe_seed);
}

const char *game_seed_name_get(Gamep g)
{
  TRACE_NO_INDENT();

  if (! g) {
    ERR("No game pointer set");
    return "";
  }

  return g->seed_name.c_str();
}

SeedSource game_seed_source_get(Gamep g)
{
  TRACE_NO_INDENT();

  if (! g) {
    ERR("No game pointer set");
    return SEED_SOURCE_RANDOM;
  }

  return g->seed_source;
}

uint32_t game_seed_num_get(Gamep g)
{
  TRACE_NO_INDENT();

  if (! g) {
    ERR("No game pointer set");
    return 0;
  }

  return g->seed_num;
}

void Game::create_levels(void)
{
  LOG("Game create level");
  TRACE_AND_INDENT();

  auto g = this;
  seed_set();
  destroy_levels();

  level_gen_create_levels(g);

  auto v = game_levels_get(g);
  if (! v) {
    ERR("No levels created");
    return;
  }

  level_switch(g, v, 0);

  levels_stats_dump(g);
}
void game_create_levels(Gamep g) { g->create_levels(); }

void Game::start_playing(void)
{
  LOG("Game started playing");
  TRACE_AND_INDENT();

  auto g = this;

  wid_topcon_init(g);
  TOPCON("Welcome to bla bla bla..., %%fg=red$Gorget%%fg=reset$. TODO.");
  wid_topcon_flush(g);
}
void game_start_playing(Gamep g) { g->start_playing(); }

void Game::destroy_levels(void)
{
  LOG("Game destroy level");
  TRACE_AND_INDENT();

  auto g = this;
  auto v = game_levels_get(g);
  if (! v) {
    return;
  }

  levels_destroy(g, v);
}
void game_destroy_levels(Gamep g) { g->destroy_levels(); }

void Game::display(void)
{
  TRACE_NO_INDENT();
  auto g = this;
  auto v = game_levels_get(g);
  if (! v) {
    return;
  }

  if (game->state != STATE_PLAYING) {
    return;
  }

  auto l = game_level_get(g, v);
  if (l) {
    level_tick(g, v, l);
    level_anim(g, v, l);
    level_mouse_position_get(g, v, l);
    level_display(g, v, l);
    level_cursor_update(g, v, l);
  }
}
void game_display(Gamep g) { g->display(); }

std::string gama_state_to_string(int state)
{
  switch (state) {
    case STATE_MAIN_MENU : return "MAIN_MENU";
    case STATE_PLAYING : return "PLAYING";
    case STATE_LOAD_MENU : return "LOAD_MENU";
    case STATE_SAVE_MENU : return "SAVE_MENU";
    case STATE_QUIT_MENU : return "QUIT_MENU";
    case STATE_QUITTING : return "QUITTING";
    case STATE_KEYBOARD_MENU : return "KEYBOARD_MENU";
    default : ERR("Unhandled game state"); return "?";
  }
}

//
// Reset to the default state, either playing the game, or starting up.
//
void Game::state_reset(const std::string &why)
{
  LOG("State reset: %s", why.c_str());
  TRACE_AND_INDENT();

  auto g = this;
  auto v = game_levels_get(g);
  if (v) {
    auto l = game_level_get(g, v);
    if (l) {
      state_change(STATE_PLAYING, why);
    } else {
      state_change(STATE_MAIN_MENU, why);
    }
  } else {
    state_change(STATE_MAIN_MENU, why);
  }
}
void game_state_reset(Gamep g, const char *why) { g->state_reset(why); }

uint8_t game_state(Gamep g) { return g->state; }

void Game::state_change(GameState new_state, const std::string &why)
{
  TRACE_NO_INDENT();

  auto g = this;
  if (g->state == new_state) {
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
  LOG("Game state change: %s -> %s, reason: %s", gama_state_to_string(old_state).c_str(),
      gama_state_to_string(new_state).c_str(), why.c_str());
  TRACE_AND_INDENT();

  //
  // Cleanup actions for the new state
  //
  switch (new_state) {
    case STATE_MAIN_MENU :
    case STATE_QUITTING :
      wid_load_destroy(g);
      wid_main_menu_destroy(g);
      wid_quit_destroy(g);
      wid_save_destroy(g);
      wid_leftbar_fini(g);
      wid_rightbar_fini(g);
      wid_topcon_fini(g);
      break;
    case STATE_PLAYING :
      wid_load_destroy(g);
      wid_main_menu_destroy(g);
      wid_quit_destroy(g);
      wid_save_destroy(g);
      break;
    case STATE_KEYBOARD_MENU :
    case STATE_LOAD_MENU :
    case STATE_SAVE_MENU :
    case STATE_QUIT_MENU : break;
  }

  //
  // Enter the new state
  //
  switch (new_state) {
    case STATE_MAIN_MENU : wid_main_menu_select(g); break;
    case STATE_QUITTING : break;
    case STATE_PLAYING :
      switch (old_state) {
        case STATE_QUITTING : /* from loading */
        case STATE_MAIN_MENU :
          LOG("Create left and right bars");
          wid_leftbar_init(g);
          wid_rightbar_init(g);
          break;
        case STATE_KEYBOARD_MENU :
        case STATE_PLAYING :
        case STATE_LOAD_MENU :
        case STATE_SAVE_MENU :
        case STATE_QUIT_MENU : break;
      }
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
void game_state_change(Gamep g, GameState new_state, const char *why)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->state_change(new_state, std::string(why));
}

void game_load_config(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->load_config();
}

class HiScores *game_hiscores_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return nullptr;
  }
  return &g->config.hiscores;
}

void game_visible_map_pix_get(Gamep g, int *visible_map_tl_x, int *visible_map_tl_y, int *visible_map_br_x,
                              int *visible_map_br_y)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  *visible_map_tl_x = g->visible_map_tl_x;
  *visible_map_tl_y = g->visible_map_tl_y;
  *visible_map_br_x = g->visible_map_br_x;
  *visible_map_br_y = g->visible_map_br_y;
}

void game_visible_map_pix_set(Gamep g, int visible_map_tl_x, int visible_map_tl_y, int visible_map_br_x,
                              int visible_map_br_y)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->visible_map_tl_x = visible_map_tl_x;
  g->visible_map_tl_y = visible_map_tl_y;
  g->visible_map_br_x = visible_map_br_x;
  g->visible_map_br_y = visible_map_br_y;
}

int game_tiles_visible_across_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return MAP_TILES_ACROSS_DEF;
  }
  return g->config.tiles_visible_across;
}
void game_tiles_visible_across_set(Gamep g, int val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.tiles_visible_across = val;
}

int game_tiles_visible_down_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return MAP_TILES_DOWN_DEF;
  }
  return g->config.tiles_visible_down;
}
void game_tiles_visible_down_set(Gamep g, int val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.tiles_visible_down = val;
}

int game_last_mouse_down_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return 0;
  }
  return g->last_mouse_down;
}
void game_last_mouse_down_set(Gamep g, int val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->last_mouse_down = val;
}

float game_aspect_ratio_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return 1;
  }
  return g->config.aspect_ratio;
}
void game_aspect_ratio_set(Gamep g, float val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.aspect_ratio = val;
}

int game_ui_term_height_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return TERM_HEIGHT_DEF;
  }
  return g->config.ui_term_height;
}
void game_ui_term_height_set(Gamep g, int val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.ui_term_height = val;
}

int game_ui_term_width_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return TERM_WIDTH_DEF;
  }
  return g->config.ui_term_width;
}
void game_ui_term_width_set(Gamep g, int val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.ui_term_width = val;
}

bool game_debug_mode_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return false;
  }
  return g->config.debug_mode;
}
void game_debug_mode_set(Gamep g, bool val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.debug_mode = val;
}

bool game_fps_counter_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return false;
  }
  return g->config.fps_counter;
}
void game_fps_counter_set(Gamep g, bool val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.fps_counter = val;
}

int game_fps_value_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return 0;
  }
  return g->fps_value;
}
void game_fps_value_set(Gamep g, int val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->fps_value = val;
}

bool game_gfx_allow_highdpi_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return false;
  }
  return g->config.gfx_allow_highdpi;
}
void game_gfx_allow_highdpi_set(Gamep g, bool val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.gfx_allow_highdpi = val;
}

bool game_gfx_borderless_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return false;
  }
  return g->config.gfx_borderless;
}
void game_gfx_borderless_set(Gamep g, bool val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.gfx_borderless = val;
}

bool game_gfx_fullscreen_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return false;
  }
  return g->config.gfx_fullscreen;
}
void game_gfx_fullscreen_set(Gamep g, bool val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.gfx_fullscreen = val;
}

bool game_gfx_fullscreen_desktop_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return false;
  }
  return g->config.gfx_fullscreen_desktop;
}
void game_gfx_fullscreen_desktop_set(Gamep g, bool val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.gfx_fullscreen_desktop = val;
}

bool game_gfx_vsync_enable_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return false;
  }
  return g->config.gfx_vsync_enable;
}
void game_gfx_vsync_enable_set(Gamep g, bool val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.gfx_vsync_enable = val;
}

bool game_mouse_wheel_lr_negated_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return false;
  }
  return g->config.mouse_wheel_lr_negated;
}
void game_mouse_wheel_lr_negated_set(Gamep g, bool val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.mouse_wheel_lr_negated = val;
}

bool game_mouse_wheel_ud_negated_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return false;
  }
  return g->config.mouse_wheel_ud_negated;
}
void game_mouse_wheel_ud_negated_set(Gamep g, bool val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.mouse_wheel_ud_negated = val;
}

int game_config_pix_height_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return false;
  }
  return g->config.config_pix_height;
}
void game_config_pix_height_set(Gamep g, int val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.config_pix_height = val;
}

int game_config_pix_width_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return false;
  }
  return g->config.config_pix_width;
}
void game_config_pix_width_set(Gamep g, int val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.config_pix_width = val;
}

int game_map_fbo_height_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return 0;
  }
  return g->config.map_fbo_height;
}

int game_map_fbo_width_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return 0;
  }
  return g->config.map_fbo_width;
}

void game_map_fbo_height_set(Gamep g, int val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.map_fbo_height = val;
}

void game_map_fbo_width_set(Gamep g, int val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.map_fbo_width = val;
}

int game_window_pix_height_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return 0;
  }
  return g->config.window_pix_height;
}
void game_window_pix_height_set(Gamep g, int val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.window_pix_height = val;
}

int game_window_pix_width_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return 0;
  }
  return g->config.window_pix_width;
}
void game_window_pix_width_set(Gamep g, int val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.window_pix_width = val;
}

int game_ascii_pix_height_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return 0;
  }
  return g->config.ascii_pix_height;
}
void game_ascii_pix_height_set(Gamep g, int val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.ascii_pix_height = val;
}

int game_ascii_pix_width_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return 0;
  }
  return g->config.ascii_pix_width;
}
void game_ascii_pix_width_set(Gamep g, int val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.ascii_pix_width = val;
}

int game_music_volume_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return 0;
  }
  return g->config.music_volume;
}
void game_music_volume_set(Gamep g, int val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.music_volume = val;
}

int game_sdl_delay_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return 0;
  }
  return g->config.sdl_delay;
}
void game_sdl_delay_set(Gamep g, int val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.sdl_delay = val;
}

int game_sound_volume_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return 0;
  }
  return g->config.sound_volume;
}
void game_sound_volume_set(Gamep g, int val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.sound_volume = val;
}

Levelsp game_levels_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return nullptr;
  }
  return g->levels;
}
void game_levels_set(Gamep g, Levelsp val)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->levels = val;
}

Levelp game_level_get(Gamep g, Levelsp v)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return nullptr;
  }
  if (unlikely(! v)) {
    ERR("No levels pointer set");
    return nullptr;
  }
  auto n = v->level_num;
  return &v->level[ n ];
}
Levelp game_level_get(Gamep g, Levelsp v, int n)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return nullptr;
  }
  if (unlikely(! v)) {
    ERR("No levels pointer set");
    return nullptr;
  }
  return &v->level[ n ];
}
Levelp game_level_set(Gamep g, Levelsp v, int n)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return nullptr;
  }
  if (unlikely(! v)) {
    ERR("No levels pointer set");
    return nullptr;
  }
  v->level_num = n;
  return game_level_get(g, v);
}

SDL_Keysym game_key_attack_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_attack;
}
void game_key_attack_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (! g)
    return;
  g->config.key_attack = key;
}

SDL_Keysym game_key_console_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_console;
}
void game_key_console_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (! g)
    return;
  g->config.key_console = key;
}

SDL_Keysym game_key_help_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_help;
}
void game_key_help_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (! g)
    return;
  g->config.key_help = key;
}

SDL_Keysym game_key_load_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_load;
}
void game_key_load_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (! g)
    return;
  g->config.key_load = key;
}

SDL_Keysym game_key_move_down_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_move_down;
}
void game_key_move_down_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (! g)
    return;
  g->config.key_move_down = key;
}

SDL_Keysym game_key_move_left_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_move_left;
}
void game_key_move_left_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (! g)
    return;
  g->config.key_move_left = key;
}

SDL_Keysym game_key_move_right_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_move_right;
}
void game_key_move_right_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (! g)
    return;
  g->config.key_move_right = key;
}

SDL_Keysym game_key_move_up_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_move_up;
}
void game_key_move_up_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (! g)
    return;
  g->config.key_move_up = key;
}

SDL_Keysym game_key_quit_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_quit;
}
void game_key_quit_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (! g)
    return;
  g->config.key_quit = key;
}

SDL_Keysym game_key_save_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_save;
}
void game_key_save_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (! g)
    return;
  g->config.key_save = key;
}

SDL_Keysym game_key_screenshot_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_screenshot;
}
void game_key_screenshot_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (! g)
    return;
  g->config.key_screenshot = key;
}

SDL_Keysym game_key_unused1_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused1;
}
void game_key_unused1_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused1 = key;
}

SDL_Keysym game_key_unused2_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused2;
}
void game_key_unused2_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused2 = key;
}

SDL_Keysym game_key_unused3_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused3;
}
void game_key_unused3_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused3 = key;
}

SDL_Keysym game_key_unused4_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused4;
}
void game_key_unused4_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused4 = key;
}

SDL_Keysym game_key_unused5_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused5;
}
void game_key_unused5_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused5 = key;
}

SDL_Keysym game_key_unused6_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused6;
}
void game_key_unused6_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused6 = key;
}

SDL_Keysym game_key_unused7_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused7;
}
void game_key_unused7_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused7 = key;
}

SDL_Keysym game_key_unused8_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused8;
}
void game_key_unused8_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused8 = key;
}

SDL_Keysym game_key_unused9_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused9;
}
void game_key_unused9_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused9 = key;
}

SDL_Keysym game_key_unused10_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused10;
}
void game_key_unused10_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused10 = key;
}

SDL_Keysym game_key_unused11_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused11;
}
void game_key_unused11_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused11 = key;
}

SDL_Keysym game_key_unused12_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused12;
}
void game_key_unused12_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused12 = key;
}

SDL_Keysym game_key_unused13_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused13;
}
void game_key_unused13_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused13 = key;
}

SDL_Keysym game_key_unused14_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused14;
}
void game_key_unused14_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused14 = key;
}

SDL_Keysym game_key_unused15_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused15;
}
void game_key_unused15_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused15 = key;
}

SDL_Keysym game_key_unused16_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused16;
}
void game_key_unused16_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused16 = key;
}

SDL_Keysym game_key_unused17_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused17;
}
void game_key_unused17_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused17 = key;
}

SDL_Keysym game_key_unused18_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused18;
}
void game_key_unused18_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused18 = key;
}

SDL_Keysym game_key_unused19_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_unused19;
}
void game_key_unused19_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_unused19 = key;
}

SDL_Keysym game_key_zoom_get(Gamep g)
{
  TRACE_NO_INDENT();
  if (! g)
    return no_key;
  return g->config.key_zoom;
}
void game_key_zoom_set(Gamep g, SDL_Keysym key)
{
  TRACE_NO_INDENT();
  if (unlikely(! g)) {
    ERR("No game pointer set");
    return;
  }
  g->config.key_zoom = key;
}
