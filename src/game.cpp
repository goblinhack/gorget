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
#include "my_wid_topcon.hpp"
#include "my_wids.hpp"

#include <SDL_mixer.h>

using Config = class Config_
{
public:
  std::string version = "" MYVER "";

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
  // The pixel perfect screen
  //
  int game_pix_height = {};
  int game_pix_width  = {};
  //
  // This is the size of the game map within the game FBO
  //
  int map_pix_height = {};
  int map_pix_width  = {};
  //
  // The actual display res
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
  Levelp level {};

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
  uint8_t state {STATE_MAIN_MENU};

  //
  // Temporary. Dampens mouse clicks
  //
  int last_mouse_down {};
  int last_pause {};

  //
  // These are the onscreen map pixel co-ords.
  //
  int visible_map_tl_x;
  int visible_map_tl_y;
  int visible_map_br_x;
  int visible_map_br_y;
  int visible_map_mouse_x;
  int visible_map_mouse_y;

  /////////////////////////////////////////////////////////////////////////
  // not worth saving
  // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
  // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
  /////////////////////////////////////////////////////////////////////////

  Game(std::string appdata);
  Game(void) = default;

  void create_level(void);
  void entered_level(void);
  void destroy_level(void);
  void display(void);
  void fini(void);
  void init(void);
  void load_select(void);
  void save_select(void);
  void load_snapshot(void);
  void load(int slot);
  void load(void);
  void save_config(void);
  void save_snapshot_check();
  void save_snapshot(void);
  void save(int slot);
  void save(void);
  void set_currently_saving_snapshot(void);
  void set_seed(void);
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
  ui_term_height         = {TERM_HEIGHT_DEF};
  ui_term_width          = {TERM_WIDTH_DEF};
  version                = "" MYVER "";
  aspect_ratio           = {};
  window_pix_height      = {};
  window_pix_width       = {};
  tiles_visible_across   = {};
  tiles_visible_down     = {};

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
  sdl_delay          = 10;
  sound_volume       = {MIX_MAX_VOLUME / 2};

  // key_unused1.sym  = SDLK_TAB;
  // key_unused1.mod  = KMOD_NUM;
}

void game_config_reset(class Game *g) { g->config.reset(); }

Game::Game(std::string vappdata)
{
  TRACE_AND_INDENT();

  config.reset();

  this->appdata = vappdata;

  saved_dir = appdata + DIR_SEP + "gorget" + DIR_SEP;
  save_slot = 1;

  save_meta = "seed " + seed_name + ", ";
  save_meta += string_timestamp();

  save_file = saved_dir + "saved-slot-" + std::to_string(save_slot);
}

void Game::init(void)
{
  LOG("INF: Game init");
  TRACE_AND_INDENT();
  set_seed();
}
void game_init(class Game *g) { g->init(); }

void Game::fini(void)
{
  LOG("FIN: Game fini");
  TRACE_AND_INDENT();
  state_change(STATE_QUITTING, "quitting");
  destroy_level();
}
void game_fini(class Game *g)
{
  if (! g) {
    return;
  }

  g->fini();
  delete g;
  game = NULL;
}

void game_save_config(class Game *g) { g->save_config(); }

void Game::set_seed(void)
{
  if (g_opt_seed_name != "") {
    seed_name = g_opt_seed_name;
  } else {
    seed_name = random_name(SIZEOF("4294967295") - 1);
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
  destroy_level();

  LOG("Level create");
  level = level_new();
}
void game_create_level(class Game *g) { g->create_level(); }

void Game::entered_level(void)
{
  LOG("Game entered level");
  TRACE_AND_INDENT();

  TOPCON("Welcome to the dungeons of dread, home of the black dragon, %%fg=red$Gorget%%fg=reset$.");
  TOPCON("Complete all %%fg=yellow$16%%fg=reset$ levels and collect the Darkenstone to win.");

  CON("%%fg=red$          @@@@@@@@   @@@@@@   @@@@@@@    @@@@@@@@  @@@@@@@@  @@@@@@@%%fg=reset$");
  CON("%%fg=red$         @@@@@@@@@  @@@@@@@@  @@@@@@@@  @@@@@@@@@  @@@@@@@@  @@@@@@@%%fg=reset$");
  CON("%%fg=red$         !@@        @@!  @@@  @@!  @@@  !@@        @@!         @@!%%fg=reset$");
  CON("%%fg=red$         !@!        !@!  @!@  !@!  @!@  !@!        !@!         !@!%%fg=reset$");
  CON("%%fg=red$         !@! @!@!@  @!@  !@!  @!@!!@!   !@! @!@!@  @!!!:!      @!!%%fg=reset$");
  CON("%%fg=red$         !!! !!@!!  !@!  !!!  !!@!@!    !!! !!@!!  !!!!!:      !!!%%fg=reset$");
  CON("%%fg=red$         :!!   !!:  !!:  !!!  !!: :!!   :!!   !!:  !!:         !!:%%fg=reset$");
  CON("%%fg=red$         :!:   !::  :!:  !:!  :!:  !:!  :!:   !::  :!:         :!:%%fg=reset$");
  CON("%%fg=red$          ::: ::::  ::::: ::  ::   :::   ::: ::::   :: ::::     ::%%fg=reset$");
  CON("%%fg=red$          :: :: :    : :  :    :   : :   :: :: :   : :: ::      :%%fg=reset$");
  CON("%%fg=red$           :              :    .         :: :      :  :  :%%fg=reset$");
  CON("%%fg=red$           .              :               : .      .     .%%fg=reset$");
  CON("%%fg=red$                          :               .%%fg=reset$");
  CON("%%fg=red$                          .%%fg=reset$");
  CON("%%fg=green$Version: " MYVER "%%fg=reset$");
  CON("Press %%fg=yellow$<tab>%%fg=reset$ to complete commands.");
  CON("Press %%fg=yellow$?%%fg=reset$ to show command options.");
  wid_topcon_flush();
}
void game_entered_level(class Game *g) { g->entered_level(); }

void Game::destroy_level(void)
{
  LOG("Game destroy level");
  TRACE_AND_INDENT();

  if (level) {
    auto l = level;
    level_fini(l);
    level = nullptr;
  }
}
void game_destroy_level(class Game *g) { g->destroy_level(); }

void Game::display(void)
{
  if (level) {
    level_tick(level);
    level_anim(level);
    level_mouse_position_get(level);
    level_display(level);
    level_cursor_update(level);
  }
}
void game_display(class Game *g) { g->display(); }

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
  if (level) {
    state_change(STATE_PLAYING, why);
  } else {
    state_change(STATE_MAIN_MENU, why);
  }
}
void game_state_reset(class Game *g, const char *why) { g->state_reset(why); }

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
  LOG("INF: Game state change: %s -> %s, reason: %s", gama_state_to_string(old_state).c_str(),
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
      wid_leftbar_fini(game);
      wid_topcon_fini();
      break;
    case STATE_PLAYING :
      wid_main_menu_destroy(game);
      wid_load_destroy(game);
      wid_save_destroy(game);
      wid_quit_destroy(game);
      wid_rightbar_init(game);
      wid_leftbar_init(game);
      wid_topcon_init();
      break;
    case STATE_QUITTING :
      wid_main_menu_destroy(game);
      wid_load_destroy(game);
      wid_save_destroy(game);
      wid_quit_destroy(game);
      wid_rightbar_init(game);
      wid_leftbar_init(game);
      wid_topcon_init();
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
void game_state_change(class Game *g, uint8_t new_state, const char *why)
{
  g->state_change(new_state, std::string(why));
}

void game_load_config(class Game *g) { g->load_config(); }

class HiScores *game_hiscores_get(class Game *g) { return &g->config.hiscores; }

void game_visible_map_pix_get(class Game *g, int *visible_map_tl_x, int *visible_map_tl_y, int *visible_map_br_x,
                              int *visible_map_br_y)
{
  *visible_map_tl_x = g->visible_map_tl_x;
  *visible_map_tl_y = g->visible_map_tl_y;
  *visible_map_br_x = g->visible_map_br_x;
  *visible_map_br_y = g->visible_map_br_y;
}

void game_visible_map_pix_set(class Game *g, int visible_map_tl_x, int visible_map_tl_y, int visible_map_br_x,
                              int visible_map_br_y)
{
  g->visible_map_tl_x = visible_map_tl_x;
  g->visible_map_tl_y = visible_map_tl_y;
  g->visible_map_br_x = visible_map_br_x;
  g->visible_map_br_y = visible_map_br_y;
}

void game_visible_map_mouse_get(class Game *g, int *visible_map_mouse_x, int *visible_map_mouse_y)
{
  *visible_map_mouse_x = g->visible_map_mouse_x;
  *visible_map_mouse_y = g->visible_map_mouse_y;
}

void game_visible_map_mouse_set(class Game *g, int visible_map_mouse_x, int visible_map_mouse_y)
{
  g->visible_map_mouse_x = visible_map_mouse_x;
  g->visible_map_mouse_y = visible_map_mouse_y;
}

int  game_tiles_visible_across_get(class Game *g) { return g->config.tiles_visible_across; }
void game_tiles_visible_across_set(class Game *g, int val) { g->config.tiles_visible_across = val; }

int  game_tiles_visible_down_get(class Game *g) { return g->config.tiles_visible_down; }
void game_tiles_visible_down_set(class Game *g, int val) { g->config.tiles_visible_down = val; }

int  game_last_mouse_down_get(class Game *g) { return g->last_mouse_down; }
void game_last_mouse_down_set(class Game *g, int val) { g->last_mouse_down = val; }

int  game_last_pause_get(class Game *g) { return g->last_pause; }
void game_last_pause_set(class Game *g, int val) { g->last_pause = val; }

int  game_serialized_size_get(class Game *g) { return g->serialized_size; }
void game_serialized_size_set(class Game *g, int val) { g->serialized_size = val; }

float game_aspect_ratio_get(class Game *g) { return g->config.aspect_ratio; }
void  game_aspect_ratio_set(class Game *g, float val) { g->config.aspect_ratio = val; }

int  game_ui_term_height_get(class Game *g) { return g->config.ui_term_height; }
void game_ui_term_height_set(class Game *g, int val) { g->config.ui_term_height = val; }

int  game_ui_term_width_get(class Game *g) { return g->config.ui_term_width; }
void game_ui_term_width_set(class Game *g, int val) { g->config.ui_term_width = val; }

bool game_debug_mode_get(class Game *g) { return g->config.debug_mode; }
void game_debug_mode_set(class Game *g, bool val) { g->config.debug_mode = val; }

bool game_fps_counter_get(class Game *g) { return g->config.fps_counter; }
void game_fps_counter_set(class Game *g, bool val) { g->config.fps_counter = val; }

int  game_fps_value_get(class Game *g) { return g->fps_value; }
void game_fps_value_set(class Game *g, int val) { g->fps_value = val; }

bool game_gfx_allow_highdpi_get(class Game *g) { return g->config.gfx_allow_highdpi; }
void game_gfx_allow_highdpi_set(class Game *g, bool val) { g->config.gfx_allow_highdpi = val; }

bool game_gfx_borderless_get(class Game *g) { return g->config.gfx_borderless; }
void game_gfx_borderless_set(class Game *g, bool val) { g->config.gfx_borderless = val; }

bool game_gfx_fullscreen_get(class Game *g) { return g->config.gfx_fullscreen; }
void game_gfx_fullscreen_set(class Game *g, bool val) { g->config.gfx_fullscreen = val; }

bool game_gfx_fullscreen_desktop_get(class Game *g) { return g->config.gfx_fullscreen_desktop; }
void game_gfx_fullscreen_desktop_set(class Game *g, bool val) { g->config.gfx_fullscreen_desktop = val; }

bool game_gfx_vsync_enable_get(class Game *g) { return g->config.gfx_vsync_enable; }
void game_gfx_vsync_enable_set(class Game *g, bool val) { g->config.gfx_vsync_enable = val; }

bool game_mouse_wheel_lr_negated_get(class Game *g) { return g->config.mouse_wheel_lr_negated; }
void game_mouse_wheel_lr_negated_set(class Game *g, bool val) { g->config.mouse_wheel_lr_negated = val; }

bool game_mouse_wheel_ud_negated_get(class Game *g) { return g->config.mouse_wheel_ud_negated; }
void game_mouse_wheel_ud_negated_set(class Game *g, bool val) { g->config.mouse_wheel_ud_negated = val; }

int  game_config_pix_height_get(class Game *g) { return g->config.config_pix_height; }
void game_config_pix_height_set(class Game *g, int val) { g->config.config_pix_height = val; }

int  game_config_pix_width_get(class Game *g) { return g->config.config_pix_width; }
void game_config_pix_width_set(class Game *g, int val) { g->config.config_pix_width = val; }

int  game_pix_height_get(class Game *g) { return g->config.game_pix_height; }
void game_pix_height_set(class Game *g, int val) { g->config.game_pix_height = val; }

int  game_pix_width_get(class Game *g) { return g->config.game_pix_width; }
void game_pix_width_set(class Game *g, int val) { g->config.game_pix_width = val; }

int  game_map_pix_height_get(class Game *g) { return g->config.map_pix_height; }
void game_map_pix_height_set(class Game *g, int val) { g->config.map_pix_height = val; }

int  game_map_pix_width_get(class Game *g) { return g->config.map_pix_width; }
void game_map_pix_width_set(class Game *g, int val) { g->config.map_pix_width = val; }

int  game_window_pix_height_get(class Game *g) { return g->config.window_pix_height; }
void game_window_pix_height_set(class Game *g, int val) { g->config.window_pix_height = val; }

int  game_window_pix_width_get(class Game *g) { return g->config.window_pix_width; }
void game_window_pix_width_set(class Game *g, int val) { g->config.window_pix_width = val; }

int  game_ascii_pix_height_get(class Game *g) { return g->config.ascii_pix_height; }
void game_ascii_pix_height_set(class Game *g, int val) { g->config.ascii_pix_height = val; }

int  game_ascii_pix_width_get(class Game *g) { return g->config.ascii_pix_width; }
void game_ascii_pix_width_set(class Game *g, int val) { g->config.ascii_pix_width = val; }

int  game_music_volume_get(class Game *g) { return g->config.music_volume; }
void game_music_volume_set(class Game *g, int val) { g->config.music_volume = val; }

int  game_sdl_delay_get(class Game *g) { return g->config.sdl_delay; }
void game_sdl_delay_set(class Game *g, int val) { g->config.sdl_delay = val; }

int  game_sound_volume_get(class Game *g) { return g->config.sound_volume; }
void game_sound_volume_set(class Game *g, int val) { g->config.sound_volume = val; }

Levelp game_level_get(class Game *g) { return g->level; }
void   game_level_set(class Game *g, Levelp val) { g->level = val; }

const char *game_seed_name_get(class Game *g) { return g->seed_name.c_str(); }
void        game_seed_name_set(class Game *g, const char *val) { g->seed_name = std::string(val); }

SDL_Keysym game_key_attack_get(class Game *g) { return g->config.key_attack; }
void       game_key_attack_set(class Game *g, SDL_Keysym key) { g->config.key_attack = key; }

SDL_Keysym game_key_console_get(class Game *g) { return g->config.key_console; }
void       game_key_console_set(class Game *g, SDL_Keysym key) { g->config.key_console = key; }

SDL_Keysym game_key_help_get(class Game *g) { return g->config.key_help; }
void       game_key_help_set(class Game *g, SDL_Keysym key) { g->config.key_help = key; }

SDL_Keysym game_key_load_get(class Game *g) { return g->config.key_load; }
void       game_key_load_set(class Game *g, SDL_Keysym key) { g->config.key_load = key; }

SDL_Keysym game_key_move_down_get(class Game *g) { return g->config.key_move_down; }
void       game_key_move_down_set(class Game *g, SDL_Keysym key) { g->config.key_move_down = key; }

SDL_Keysym game_key_move_left_get(class Game *g) { return g->config.key_move_left; }
void       game_key_move_left_set(class Game *g, SDL_Keysym key) { g->config.key_move_left = key; }

SDL_Keysym game_key_move_right_get(class Game *g) { return g->config.key_move_right; }
void       game_key_move_right_set(class Game *g, SDL_Keysym key) { g->config.key_move_right = key; }

SDL_Keysym game_key_move_up_get(class Game *g) { return g->config.key_move_up; }
void       game_key_move_up_set(class Game *g, SDL_Keysym key) { g->config.key_move_up = key; }

SDL_Keysym game_key_quit_get(class Game *g) { return g->config.key_quit; }
void       game_key_quit_set(class Game *g, SDL_Keysym key) { g->config.key_quit = key; }

SDL_Keysym game_key_save_get(class Game *g) { return g->config.key_save; }
void       game_key_save_set(class Game *g, SDL_Keysym key) { g->config.key_save = key; }

SDL_Keysym game_key_screenshot_get(class Game *g) { return g->config.key_screenshot; }
void       game_key_screenshot_set(class Game *g, SDL_Keysym key) { g->config.key_screenshot = key; }

SDL_Keysym game_key_unused1_get(class Game *g) { return g->config.key_unused1; }
void       game_key_unused1_set(class Game *g, SDL_Keysym key) { g->config.key_unused1 = key; }
