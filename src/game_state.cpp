//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_game.hpp"
#include "my_wid_popups.hpp"
#include "my_wid_rightbar.hpp"

std::string gama_state_to_string(int state)
{
  switch (state) {
    case Game::STATE_MAIN_MENU : return "MAIN_MENU";
    case Game::STATE_PLAYING : return "PLAYING";
    case Game::STATE_LOAD_MENU : return "LOAD_MENU";
    case Game::STATE_SAVE_MENU : return "SAVE_MENU";
    case Game::STATE_QUIT_MENU : return "QUIT_MENU";
    case Game::STATE_KEYBOARD_MENU : return "KEYBOARD_MENU";
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
      wid_load_destroy();
      wid_save_destroy();
      wid_quit_destroy();
      wid_rightbar_fini();
      break;
    case STATE_PLAYING :
      wid_main_menu_destroy();
      wid_load_destroy();
      wid_save_destroy();
      wid_quit_destroy();
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
