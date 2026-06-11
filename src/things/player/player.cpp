//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game_popups.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_music.hpp"
#include "my_sound.hpp"
#include "my_thing.hpp"
#include "my_thing_callbacks.hpp"
#include "my_thing_inlines.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"
#include "my_ui.hpp"

static auto tp_player_description_get(Gamep g, Levelsp v, Levelp l, Thingp me) -> std::string
{
  TRACE();

  if (thing_is_dead(me)) {
    return "dead you";
  }
  return "You";
}

static auto tp_player_detail_get(Gamep g, Levelsp v, Levelp l, Thingp me) -> std::string
{
  TRACE();

  return UI_INFO1_FMT_STR "You: a luckless wizard hoping to reclaim forgotten skills.";
}

static void tp_player_on_moved(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE();

  //
  // If we fell into another chasm, don't make an oof sound
  //
  if (level_is_chasm(g, v, l, thing_at(me)) != nullptr) {
    return;
  }

  if (level_is_water(g, v, l, thing_at(me)) != nullptr) {
    thing_sound_play(g, v, l, me, "splash");
  } else {
    thing_sound_play(g, v, l, me, "footstep");
  }

  auto at                   = thing_at(me);
  v->cursor[ at.x ][ at.y ] = CURSOR_NONE;
}

static bool tp_player_on_damage(Gamep g, Levelsp v, Levelp l, Thingp me, ThingEvent &e)
{
  TRACE();

  //
  // If hit, clear the cursor path and stop moving.
  //
  player_state_change(g, v, l, PLAYER_STATE_NORMAL);

  (void) thing_spawn(g, v, l, tp_first(is_effect_blood), me);

  thing_sound_play(g, v, l, me, "player_hit");

  return true; // allow the damage to be applied
}

static void tp_player_on_jump_end(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE();

  if (thing_is_falling(me) != 0) {
    return;
  }

  if (level_is_water(g, v, l, thing_at(me)) != nullptr) {
    //
    // We already have a splash noise
    //
    auto at = thing_at(me);
    game_popup_text_add(g, at.x, at.y, std::string("Splash!"));
  } else {
    thing_sound_play(g, v, l, me, "player_oof");

    auto at = thing_at(me);
    game_popup_text_add(g, at.x, at.y, std::string("Oof!"));
  }
}

static void tp_player_on_fall_begin(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE();

  auto at = thing_at(me);
  game_popup_text_add(g, at.x, at.y, std::string("Aargh!"));
}

static void tp_player_on_fall_end(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE();

  //
  // If we fell into another chasm, don't make an oof sound
  //
  if (level_is_chasm(g, v, l, thing_at(me)) != nullptr) {
    return;
  }

  if (level_is_water(g, v, l, thing_at(me)) != nullptr) {
    thing_sound_play(g, v, l, me, "splash");
  } else {
    thing_sound_play(g, v, l, me, "player_oof");
  }
}

static void tp_player_level_leave(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE();

  thing_vision_reset(g, v, l, me);

  sound_fade_out(g);
}

static void tp_player_level_enter(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE();

  //
  // Ambience loops
  //
  auto loops = 100;
  auto scale = 1;

  //
  // Needed to make sure the light resets as it looks for pixel changes.
  //
  thing_prev_pix_at_set(g, v, l, me, spoint(-1, -1));

  switch (l->level_num + 1) {
    case 1 :
      (void) sound_play(g, "dungeon_ambience", scale, loops);
      (void) music_play(g, "dungeon.1");
      break;
    case 2 :
      (void) sound_play(g, "dungeon_ambience", scale, loops);
      (void) music_play(g, "dungeon.2");
      break;
    case 3 :
      (void) sound_play(g, "dungeon_ambience", scale, loops);
      (void) music_play(g, "dungeon.3");
      break;
    case 4 :
      (void) sound_play(g, "dungeon_ambience", scale, loops);
      (void) music_play(g, "dungeon.4");
      break;
    case 5 :
      (void) sound_play(g, "dungeon_ambience", scale, loops);
      (void) music_play(g, "dungeon.boss");
      break;
    case 6 :
      (void) sound_play(g, "bogland_ambience", scale, loops);
      (void) music_play(g, "bogland.1");
      break;
    case 7 :
      (void) sound_play(g, "bogland_ambience", scale, loops);
      (void) music_play(g, "bogland.2");
      break;
    case 8 :
      (void) sound_play(g, "bogland_ambience", scale, loops);
      (void) music_play(g, "bogland.3");
      break;
    case 9 :
      (void) sound_play(g, "bogland_ambience", scale, loops);
      (void) music_play(g, "bogland.4");
      break;
    case 10 :
      (void) sound_play(g, "bogland_ambience", scale, loops);
      (void) music_play(g, "bogland.boss");
      break;
    case 11 :
      (void) sound_play(g, "nethervoid_ambience", scale, loops);
      (void) music_play(g, "nethervoid.1");
      break;
    case 12 :
      (void) sound_play(g, "nethervoid_ambience", scale, loops);
      (void) music_play(g, "nethervoid.2");
      break;
    case 13 :
      (void) sound_play(g, "nethervoid_ambience", scale, loops);
      (void) music_play(g, "nethervoid.3");
      break;
    case 14 :
      (void) sound_play(g, "nethervoid_ambience", scale, loops);
      (void) music_play(g, "nethervoid.4");
      break;
    case 15 :
      (void) sound_play(g, "nethervoid_ambience", scale, loops);
      (void) music_play(g, "nethervoid.boss");
      break;
    case 16 :
      (void) sound_play(g, "graveyard_ambience", scale, loops);
      (void) music_play(g, "graveyard.1");
      break;
    case 17 :
      (void) sound_play(g, "graveyard_ambience", scale, loops);
      (void) music_play(g, "graveyard.2");
      break;
    case 18 :
      (void) sound_play(g, "graveyard_ambience", scale, loops);
      (void) music_play(g, "graveyard.3");
      break;
    case 19 :
      (void) sound_play(g, "graveyard_ambience", scale, loops);
      (void) music_play(g, "graveyard.4");
      break;
    case 20 :
      (void) sound_play(g, "graveyard_ambience", scale, loops);
      (void) music_play(g, "graveyard.boss");
      break;
    case 21 :
      (void) sound_play(g, "underhell_ambience", scale, loops);
      (void) music_play(g, "underhell.1");
      break;
    case 22 :
      (void) sound_play(g, "underhell_ambience", scale, loops);
      (void) music_play(g, "underhell.2");
      break;
    case 23 :
      (void) sound_play(g, "underhell_ambience", scale, loops);
      (void) music_play(g, "underhell.3");
      break;
    case 24 :
      (void) sound_play(g, "underhell_ambience", scale, loops);
      (void) music_play(g, "underhell.4");
      break;
    case 25 :
      (void) sound_play(g, "underhell_ambience", scale, loops);
      (void) music_play(g, "underhell.boss");
      break;
  }
}

static void tp_player_level_populated(Gamep g, Levelsp v, Levelp l, Thingp me) { TRACE(); }

static void tp_player_tick_begin(Gamep g, Levelsp v, Levelp l, Thingp me) { TRACE(); }

static void tp_player_on_teleported(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE();

  auto at = thing_at(me);
  game_popup_text_add(g, at.x, at.y, std::string("Urgh"));
}

static void tp_player_tick_idle(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE();

  //
  // If asked to follow the mouse path, start walking
  //
  (void) player_move_to_next(g, v, l, me);
}

static void tp_player_tick_end(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE();

  //
  // If asked to follow the mouse path, start walking
  //
  (void) player_move_to_next(g, v, l, me);
}

static void tp_player_on_spawned(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE();

  if (g_opt_tests) {
    return;
  }

  static std::initializer_list< std::string > carry = {
      "staff_fire",     //
      "staff_fire",     //
      "staff_light",    //
      "wand_fire",      //
      "wand_light",     //
      "potion_incin",   //
      "potion_incin",   //
      "potion_incin",   //
      "potion_incin",   //
      "potion_incin",   //
      "potion_healing", //
      "potion_healing", //
  };

  for (auto tp : carry) {
    auto weapon_tp = tp_find_mand(tp);
    if (weapon_tp) {
      auto weapon = thing_spawn(g, v, l, weapon_tp, thing_at(me));
      if (weapon) {
        ThingEvent e {
            .reason     = "spawned",           //
            .event_type = THING_EVENT_SPAWNED, //
            .source     = me,                  //
        };
        if (! thing_carry(g, v, l, me, weapon, e)) {
          thing_err(me, "failed to carry");
        }
      }
    }
  }

  if (compiler_unused) {
    if (! thing_buff_add(g, v, l, me, tp_find_mand("buff_resistant_fire"))) {
      thing_err(me, "failed to add buff");
    }
    if (! thing_buff_add(g, v, l, me, tp_find_mand("buff_resistant_fire"))) {
      thing_err(me, "failed to add buff");
    }
    if (! thing_buff_add(g, v, l, me, tp_find_mand("buff_resistant_fire"))) {
      thing_err(me, "failed to add buff");
    }
    if (! thing_buff_add(g, v, l, me, tp_find_mand("buff_immune_fire"))) {
      thing_err(me, "failed to add buff");
    }
    if (! thing_buff_add(g, v, l, me, tp_find_mand("buff_immune_fire"))) {
      thing_err(me, "failed to add buff");
    }
  }
}

[[nodiscard]] auto tp_load_player() -> bool
{
  auto *tp   = tp_load("player"); // keep as string for scripts
  auto  name = tp_name(tp);

  // begin sort marker1 {
  thing_description_set(tp, tp_player_description_get);
  thing_detail_set(tp, tp_player_detail_get);
  thing_on_damage_set(tp, tp_player_on_damage);
  thing_on_fall_begin_set(tp, tp_player_on_fall_begin);
  thing_on_fall_end_set(tp, tp_player_on_fall_end);
  thing_on_jump_end_set(tp, tp_player_on_jump_end);
  thing_on_level_enter_set(tp, tp_player_level_enter);
  thing_on_level_leave_set(tp, tp_player_level_leave);
  thing_on_level_populated_set(tp, tp_player_level_populated);
  thing_on_moved_set(tp, tp_player_on_moved);
  thing_on_spawned_set(tp, tp_player_on_spawned);
  thing_on_teleported_set(tp, tp_player_on_teleported);
  thing_on_tick_begin_set(tp, tp_player_tick_begin);
  thing_on_tick_end_set(tp, tp_player_tick_end);
  thing_on_tick_idle_set(tp, tp_player_tick_idle);
  tp_chance_set(tp, THING_CHANCE_CONTINUE_TO_BURN, "1d6"); // fumble => intensify / keep burning / crit => stop burning
  tp_chance_set(tp, THING_CHANCE_START_BURNING, "1d100");  // fumble => flames spread to you
  tp_damage_set(tp, THING_EVENT_MELEE_DAMAGE, "1d4");
  tp_distance_jump_set(tp, 3);
  tp_distance_throw_set(tp, 6);
  tp_distance_vision_set(tp, MAP_WIDTH / 2); // tiles
  tp_flag_set(tp, is_able_to_be_buffed);
  tp_flag_set(tp, is_able_to_collect_items);
  tp_flag_set(tp, is_able_to_collect_keys);
  tp_flag_set(tp, is_able_to_crush_grass);
  tp_flag_set(tp, is_able_to_fall_repeatedly);
  tp_flag_set(tp, is_able_to_fall_sound);
  tp_flag_set(tp, is_able_to_fall);
  tp_flag_set(tp, is_able_to_fire_weapons);
  tp_flag_set(tp, is_able_to_lunge);
  tp_flag_set(tp, is_able_to_move_diagonally);
  tp_flag_set(tp, is_able_to_open_things);
  tp_flag_set(tp, is_able_to_shove);
  tp_flag_set(tp, is_able_to_throw_items_items);
  tp_flag_set(tp, is_able_to_throw_items);
  tp_flag_set(tp, is_able_to_wield_items);
  tp_flag_set(tp, is_animated_can_hflip);
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_attackable_by_monst);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_blit_hit_outline_w_invis_inside);
  tp_flag_set(tp, is_blit_shown_in_chasms);
  tp_flag_set(tp, is_blit_shown_in_overlay);
  tp_flag_set(tp, is_blit_when_obscured_outline);
  tp_flag_set(tp, is_burnable); // is capable of being burned by fire
  tp_flag_set(tp, is_collision_circle_large);
  tp_flag_set(tp, is_combustible);
  tp_flag_set(tp, is_corpse_on_death);
  tp_flag_set(tp, is_critical_to_level);
  tp_flag_set(tp, is_damage_capped);
  tp_flag_set(tp, is_described_cursor);
  tp_flag_set(tp, is_dmap);
  tp_flag_set(tp, is_flesh);
  tp_flag_set(tp, is_health_visible);
  tp_flag_set(tp, is_light_source, MAP_WIDTH / 2);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_obs_to_beam);
  tp_flag_set(tp, is_obs_to_jumping_onto);
  tp_flag_set(tp, is_obs_to_movement);
  tp_flag_set(tp, is_physics_explosion);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_player);
  tp_flag_set(tp, is_stamina_visible);
  tp_flag_set(tp, is_submergible); // is seen submerged when in water
  tp_flag_set(tp, is_tickable);
  tp_health_set(tp, "100");
  tp_light_color_set(tp, "white");
  tp_missile_count_max_set(tp, THING_MISSILE_MAX);
  tp_priority_set(tp, THING_PRIORITY_PLAYER);
  tp_speed_set(tp, 100);
  tp_stamina_set(tp, "100");
  tp_temperature_burns_at_set(tp, 50);  // celsius
  tp_temperature_damage_at_set(tp, 35); // celsius
  tp_temperature_initial_set(tp, 20);   // celsius
  tp_weight_set(tp, WEIGHT_HUMAN);      // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_PLAYER);
  // end sort marker1 }

  auto delay = 1000;

  for (auto frame = 0; frame < 2; frame++) {
    auto *tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_size_set(tile, OUTLINE_TILE_WIDTH, OUTLINE_TILE_HEIGHT);
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);
  }

  for (auto frame = 0; frame < 1; frame++) {
    auto *tile = tile_find_mand(name + std::string(".dead.") + std::to_string(frame));
    tile_size_set(tile, OUTLINE_TILE_WIDTH, OUTLINE_TILE_HEIGHT);
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_DEAD, tile);
  }

  return true;
}
