//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game_popups.hpp"
#include "my_level.hpp"
#include "my_sound.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tp_callbacks.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"

static std::string tp_player_description_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (thing_is_dead(t)) {
    return "dead you";
  }
  return "You";
}

static std::string tp_player_detail_get(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  return "You: a luckless wizard hoping to reclaim forgotten skills.";
}

static void tp_player_on_moved(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (level_is_water(g, v, l, t->at)) {
    sound_play(g, "splash");
  } else {
    sound_play(g, "footstep");
  }

  v->cursor[ t->at.x ][ t->at.y ] = CURSOR_NONE;
}

static void tp_player_on_jump_end(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (level_is_water(g, v, l, t->at)) {
    sound_play(g, "splash");
  }

  if (thing_is_falling(t)) {
    return;
  }

  game_popup_text_add(g, t->at.x, t->at.y, std::string("Oof!"));
}

static void tp_player_on_fall_begin(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  sound_play(g, "fall");

  //
  // Falling can be good
  //
  if (thing_is_burning(t)) {
    thing_is_burning_unset(g, v, l, t);
    TOPCON(UI_GOOD_FMT_STR "You extinguish the flames as you fall!" UI_RESET_FMT);
  }

  game_popup_text_add(g, t->at.x, t->at.y, std::string("Aargh!"));
}

static void tp_player_on_fall_end(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  if (level_is_water(g, v, l, t->at)) {
    sound_play(g, "splash");
  } else {
    sound_play(g, "oof");
  }
}

static void tp_player_vision_update(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  auto ai = thing_ext_struct(g, t);
  if (ai) {
    level_fov(g, v, l, t, &ai->fov_can_see_tile, &l->player_fov_has_seen_tile, t->at, thing_vision_distance(t));
  }
}

static void tp_player_level_leave(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  thing_vision_reset(g, v, l, t);
}

static void tp_player_level_enter(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  tp_player_vision_update(g, v, l, t);
}

static void tp_player_level_populated(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  tp_player_vision_update(g, v, l, t);
}

static void tp_player_tick_begin(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();
  tp_player_vision_update(g, v, l, t);
}

static void tp_player_on_teleported(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  sound_play(g, "teleport");

  game_popup_text_add(g, t->at.x, t->at.y, std::string("Urgh"));

  tp_player_vision_update(g, v, l, t);
}

static void tp_player_tick_idle(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // If asked to follow the mouse path, start walking
  //
  player_move_to_next(g, v, l, t);
}

static void tp_player_tick_end(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  //
  // If asked to follow the mouse path, start walking
  //
  player_move_to_next(g, v, l, t);

  if (thing_is_burning(t)) {
    sound_play(g, "ouch");
  }
}

bool tp_load_player(void)
{
  auto tp   = tp_load("player"); // keep as string for scripts
  auto name = tp_name(tp);

  // begin sort marker1 {
  tp_chance_set(tp, THING_CHANCE_CONTINUE_TO_BURN, "1d6"); // roll max to stop burning
  tp_description_set(tp, tp_player_description_get);
  tp_detail_set(tp, tp_player_detail_get);
  tp_flag_set(tp, is_able_to_collect_items);
  tp_flag_set(tp, is_able_to_collect_keys);
  tp_flag_set(tp, is_able_to_crush_grass);
  tp_flag_set(tp, is_able_to_fall);
  tp_flag_set(tp, is_able_to_jump);
  tp_flag_set(tp, is_able_to_open);
  tp_flag_set(tp, is_able_to_shove);
  tp_flag_set(tp, is_animated_can_hflip);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_burnable); // is capable of being burned by fire
  tp_flag_set(tp, is_corpse_on_death);
  tp_flag_set(tp, is_damage_capped);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_health_bar_shown);
  tp_flag_set(tp, is_light_source, 10);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_physics_explosion);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_player);
  tp_flag_set(tp, is_submergible); // is seen submerged when in water
  tp_flag_set(tp, is_tickable);
  tp_health_set(tp, "100");
  tp_is_immunity_add(tp, THING_EVENT_WATER_DAMAGE);
  tp_jump_distance_set(tp, 3);
  tp_on_fall_begin_set(tp, tp_player_on_fall_begin);
  tp_on_fall_end_set(tp, tp_player_on_fall_end);
  tp_on_jump_end_set(tp, tp_player_on_jump_end);
  tp_on_level_enter_set(tp, tp_player_level_enter);
  tp_on_level_leave_set(tp, tp_player_level_leave);
  tp_on_level_populated_set(tp, tp_player_level_populated);
  tp_on_moved_set(tp, tp_player_on_moved);
  tp_on_teleported_set(tp, tp_player_on_teleported);
  tp_on_tick_begin_set(tp, tp_player_tick_begin);
  tp_on_tick_end_set(tp, tp_player_tick_end);
  tp_on_tick_idle_set(tp, tp_player_tick_idle);
  tp_speed_set(tp, 100);
  tp_temperature_burns_at_set(tp, 100);      // celsius
  tp_temperature_damage_at_set(tp, 35);      // celsius
  tp_temperature_initial_set(tp, 20);        // celsius
  tp_vision_distance_set(tp, MAP_WIDTH / 2); // tiles
  tp_weight_set(tp, WEIGHT_HUMAN);           // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_PLAYER);
  // end sort marker1 }

  auto delay = 1000;

  for (auto frame = 0; frame < 2; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  for (auto frame = 0; frame < 1; frame++) {
    auto tile = tile_find_mand(name + std::string(".dead.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_DEAD, tile);
  }

  return true;
}
