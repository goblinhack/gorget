//
// Copyright goblinhack@gmail.com
//

#include "my_charmap.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_test.hpp"
#include "my_thing_inlines.hpp"
#include "my_ui.hpp"
#include "my_wids.hpp"

#include <format>

auto level_request_to_cleanup_things(Gamep g, Levelsp v, Levelp l) -> bool
{
  TRACE_AND_INDENT();
  return l->request_to_cleanup_things;
}

void level_request_to_cleanup_things_set(Gamep g, Levelsp v, Levelp l)
{
  TRACE_AND_INDENT();
  l->request_to_cleanup_things = true;
}

void level_request_to_cleanup_things_unset(Gamep g, Levelsp v, Levelp l)
{
  TRACE_AND_INDENT();
  l->request_to_cleanup_things = false;
}

auto level_is_player_level(Gamep g, Levelsp v, Levelp l) -> bool
{
  TRACE_AND_INDENT();
  return l->_is_player_level;
}

void level_is_player_level_set(Gamep g, Levelsp v, Levelp l)
{
  TRACE_AND_INDENT();
  l->_is_player_level = true;
}

void level_is_player_level_unset(Gamep g, Levelsp v, Levelp l)
{
  TRACE_AND_INDENT();
  l->_is_player_level = false;
}

auto tp_is_able_to_collect_items(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_able_to_collect_items);
}

auto tp_is_able_to_collect_keys(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_able_to_collect_keys);
}

auto tp_is_able_to_crush_grass(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_able_to_crush_grass);
}

auto tp_is_able_to_fall_repeatedly(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_able_to_fall_repeatedly);
}

auto tp_is_able_to_fall(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_able_to_fall);
}

auto tp_is_able_to_jump(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_able_to_jump);
}

auto tp_is_able_to_move_diagonally(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_able_to_move_diagonally);
}

auto tp_is_able_to_move_through_walls(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_able_to_move_through_walls);
}

auto tp_is_able_to_open(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_able_to_open);
}

auto tp_is_able_to_shove(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_able_to_shove);
}

auto tp_is_able_to_walk_through_walls(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_able_to_walk_through_walls);
}

auto tp_is_animated_can_hflip(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_animated_can_hflip);
}

auto tp_is_animated_no_dir(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_animated_no_dir);
}

auto tp_is_animated_sync_first(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_animated_sync_first);
}

auto tp_is_animated(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_animated);
}

auto tp_is_barrel(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_barrel);
}

auto tp_is_blit_centered(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_blit_centered);
}

auto tp_is_blit_flush_per_line(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_blit_flush_per_line);
}

auto tp_is_blit_if_has_seen(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_blit_if_has_seen);
}

auto tp_is_blit_obscures(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_blit_obscures);
}

auto tp_is_blit_on_ground(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_blit_on_ground);
}

auto tp_is_blit_outlined(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_blit_outlined);
}

auto tp_is_blit_per_pixel_lighting(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_blit_per_pixel_lighting);
}

auto tp_is_blit_shown_in_chasms(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_blit_shown_in_chasms);
}

auto tp_is_blit_shown_in_overlay(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_blit_shown_in_overlay);
}

auto tp_is_blit_square_outlined(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_blit_square_outlined);
}

auto tp_is_blit_when_obscured(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_blit_when_obscured);
}

auto tp_is_border(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_border);
}

auto tp_is_brazier(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_brazier);
}

auto tp_is_bridge(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_bridge);
}

auto tp_is_broken_on_death(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_broken_on_death);
}

auto tp_is_burnable(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_burnable);
}

auto tp_is_chasm(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_chasm);
}

auto tp_is_collectable(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_collectable);
}

auto tp_is_collision_circle_large(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_collision_circle_large);
}

auto tp_is_collision_circle_small(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_collision_circle_small);
}

auto tp_is_collision_detection_enabled(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_collision_detection_enabled);
}

auto tp_is_collision_square(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_collision_square);
}

auto tp_is_combustible(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_combustible);
}

auto tp_is_corpse_on_death(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_corpse_on_death);
}

auto tp_is_corridor(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_corridor);
}

auto tp_is_crushable(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_crushable);
}

auto tp_is_cursor_path_hazard(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_cursor_path_hazard);
}

auto tp_is_cursor_path_none(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_cursor_path_none);
}

auto tp_is_cursor_path_warning(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_cursor_path_warning);
}

auto tp_is_cursor_path(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_cursor_path);
}

auto tp_is_cursor(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_cursor);
}

auto tp_is_damage_capped(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_damage_capped);
}

auto tp_is_dead_on_collision(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_dead_on_collision);
}

auto tp_is_dead_on_shoving(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_dead_on_shoving);
}

auto tp_is_deep_water(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_deep_water);
}

auto tp_is_described_cursor(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_described_cursor);
}

auto tp_is_dirt(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_dirt);
}

auto tp_is_dmap(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_dmap);
}

auto tp_is_door_locked(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_door_locked);
}

auto tp_is_door_secret(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_door_secret);
}

auto tp_is_door_unlocked(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_door_unlocked);
}

auto tp_is_dungeon_entrance(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_dungeon_entrance);
}

auto tp_is_entrance(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_entrance);
}

auto tp_is_ethereal(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_ethereal);
}

auto tp_is_exit(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_exit);
}

auto tp_is_explosion(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_explosion);
}

auto tp_is_extinguished_on_death(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_extinguished_on_death);
}

auto tp_is_fire(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_fire);
}

auto tp_is_fireball(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_fireball);
}

auto tp_is_flesh(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_flesh);
}

auto tp_is_floating(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_floating);
}

auto tp_is_floor(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_floor);
}

auto tp_is_flying(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_flying);
}

auto tp_is_foliage(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_foliage);
}

auto tp_is_gaseous(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_gaseous);
}

auto tp_is_ghost(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_ghost);
}

auto tp_is_glass(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_glass);
}

auto tp_is_gold(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_gold);
}

auto tp_is_grass(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_grass);
}

auto tp_is_health_bar_shown(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_health_bar_shown);
}

auto tp_is_indestructible(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_indestructible);
}

auto tp_is_insectoid(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_insectoid);
}

auto tp_is_inventory_item(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_inventory_item);
}

auto tp_is_item_droppable(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_item_droppable);
}

auto tp_is_item_equipable(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_item_equipable);
}

auto tp_is_item_mergeable(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_item_mergeable);
}

auto tp_is_item(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_item);
}

auto tp_is_key(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_key);
}

auto tp_is_kobalos(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_kobalos);
}

auto tp_is_lava(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_lava);
}

auto tp_is_level_across_icon(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_level_across_icon);
}

auto tp_is_level_curr(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_level_curr);
}

auto tp_is_level_down_icon(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_level_down_icon);
}

auto tp_is_level_final_icon(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_level_final_icon);
}

auto tp_is_level_next_icon(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_level_next_icon);
}

auto tp_is_level_not_visited_icon(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_level_not_visited_icon);
}

auto tp_is_level_visited_icon(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_level_visited_icon);
}

auto tp_is_levitating(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_levitating);
}

auto tp_is_light_source(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_light_source);
}

auto tp_is_loggable(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_loggable);
}

auto tp_is_mantisman(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_mantisman);
}

auto tp_is_meltable(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_meltable);
}

auto tp_is_metal(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_metal);
}

auto tp_is_minion(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_minion);
}

auto tp_is_mob_kill_minions_on_death(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_mob_kill_minions_on_death);
}

auto tp_is_mob(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_mob);
}

auto tp_is_mob1(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_mob1);
}

auto tp_is_mob2(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_mob2);
}

auto tp_is_monst_group_easy(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_monst_group_easy);
}

auto tp_is_monst_group_hard(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_monst_group_hard);
}

auto tp_is_monst_group_mob(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_monst_group_mob);
}

auto tp_is_monst(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_monst);
}

auto tp_is_needs_move_confirm(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_needs_move_confirm);
}

auto tp_is_obs_to_cursor_path(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_obs_to_cursor_path);
}

auto tp_is_obs_to_explosion(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_obs_to_explosion);
}

auto tp_is_obs_to_falling_onto(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_obs_to_falling_onto);
}

auto tp_is_obs_to_fire(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_obs_to_fire);
}

auto tp_is_obs_to_jump_over(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_obs_to_jump_over);
}

auto tp_is_obs_to_jumping_onto(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_obs_to_jumping_onto);
}

auto tp_is_obs_to_jumping_out_of(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_obs_to_jumping_out_of);
}

auto tp_is_obs_to_movement(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_obs_to_movement);
}

auto tp_is_obs_to_spawning(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_obs_to_spawning);
}

auto tp_is_obs_to_teleporting_onto(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_obs_to_teleporting_onto);
}

auto tp_is_obs_to_vision(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_obs_to_vision);
}

auto tp_is_obs_when_dead(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_obs_when_dead);
}

auto tp_is_openable(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_openable);
}

auto tp_is_physics_explosion(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_physics_explosion);
}

auto tp_is_physics_temperature(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_physics_temperature);
}

auto tp_is_physics_water(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_physics_water);
}

auto tp_is_pillar(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_pillar);
}

auto tp_is_plant(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_plant);
}

auto tp_is_player(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_player);
}

auto tp_is_projectile(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_projectile);
}

auto tp_is_removable_on_err(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_removable_on_err);
}

auto tp_is_removable_when_dead_on_err(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_removable_when_dead_on_err);
}

auto tp_is_rock(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_rock);
}

auto tp_is_shovable(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_shovable);
}

auto tp_is_slime(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_slime);
}

auto tp_is_smoke(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_smoke);
}

auto tp_is_steam(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_steam);
}

auto tp_is_stone(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_stone);
}

auto tp_is_submergible(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_submergible);
}

auto tp_is_teleport_blocked(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_teleport_blocked);
}

auto tp_is_teleport(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_teleport);
}

auto tp_is_tick_end_delay(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_tick_end_delay);
}

auto tp_is_tickable(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_tickable);
}

auto tp_is_tiled(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_tiled);
}

auto tp_is_trap(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_trap);
}

auto tp_is_treasure(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_treasure);
}

auto tp_is_undead(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_undead);
}

auto tp_is_unused1(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused1);
}

auto tp_is_unused10(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused10);
}

auto tp_is_unused11(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused11);
}

auto tp_is_unused12(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused12);
}

auto tp_is_unused13(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused13);
}

auto tp_is_unused14(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused14);
}

auto tp_is_unused15(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused15);
}

auto tp_is_unused16(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused16);
}

auto tp_is_unused17(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused17);
}

auto tp_is_unused18(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused18);
}

auto tp_is_unused19(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused19);
}

auto tp_is_unused2(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused2);
}

auto tp_is_unused20(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused20);
}

auto tp_is_unused21(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused21);
}

auto tp_is_unused22(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused22);
}

auto tp_is_unused23(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused23);
}

auto tp_is_unused24(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused24);
}

auto tp_is_unused25(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused25);
}

auto tp_is_unused26(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused26);
}

auto tp_is_unused27(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused27);
}

auto tp_is_unused28(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused28);
}

auto tp_is_unused29(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused29);
}

auto tp_is_unused3(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused3);
}

auto tp_is_unused30(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused30);
}

auto tp_is_unused31(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused31);
}

auto tp_is_unused32(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused32);
}

auto tp_is_unused33(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused33);
}

auto tp_is_unused34(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused34);
}

auto tp_is_unused35(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused35);
}

auto tp_is_unused36(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused36);
}

auto tp_is_unused37(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused37);
}

auto tp_is_unused38(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused38);
}

auto tp_is_unused39(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused39);
}

auto tp_is_unused4(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused4);
}

auto tp_is_unused40(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused40);
}

auto tp_is_unused41(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused41);
}

auto tp_is_unused42(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused42);
}

auto tp_is_unused43(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused43);
}

auto tp_is_unused44(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused44);
}

auto tp_is_unused45(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused45);
}

auto tp_is_unused46(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused46);
}

auto tp_is_unused47(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused47);
}

auto tp_is_unused48(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused48);
}

auto tp_is_unused49(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused49);
}

auto tp_is_unused5(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused5);
}

auto tp_is_unused50(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused50);
}

auto tp_is_unused51(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused51);
}

auto tp_is_unused52(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused52);
}

auto tp_is_unused53(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused53);
}

auto tp_is_unused54(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused54);
}

auto tp_is_unused55(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused55);
}

auto tp_is_unused56(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused56);
}

auto tp_is_unused57(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused57);
}

auto tp_is_unused58(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused58);
}

auto tp_is_unused59(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused59);
}

auto tp_is_unused6(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused6);
}

auto tp_is_unused60(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused60);
}

auto tp_is_unused61(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused61);
}

auto tp_is_unused62(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused62);
}

auto tp_is_unused63(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused63);
}

auto tp_is_unused64(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused64);
}

auto tp_is_unused65(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused65);
}

auto tp_is_unused66(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused66);
}

auto tp_is_unused67(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused67);
}

auto tp_is_unused68(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused68);
}

auto tp_is_unused7(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused7);
}

auto tp_is_unused8(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused8);
}

auto tp_is_unused9(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_unused9);
}

auto tp_is_wait_on_dead_anim(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_wait_on_dead_anim);
}

auto tp_is_wall(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_wall);
}

auto tp_is_water(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_water);
}

auto tp_is_wood(Tpp tp) -> bool
{
  TRACE_AND_INDENT();
  return tp_flag(tp, is_wood);
}

auto level_is_able_to_collect_items(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_able_to_collect_items, p);
}

auto level_is_able_to_collect_keys(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_able_to_collect_keys, p);
}

auto level_is_able_to_crush_grass(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_able_to_crush_grass, p);
}

auto level_is_able_to_fall_repeatedly(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_able_to_fall_repeatedly, p);
}

auto level_is_able_to_fall(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_able_to_fall, p);
}

auto level_is_able_to_jump(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_able_to_jump, p);
}

auto level_is_able_to_move_diagonally(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_able_to_move_diagonally, p);
}

auto level_is_able_to_move_through_walls(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_able_to_move_through_walls, p);
}

auto level_is_able_to_open(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_able_to_open, p);
}

auto level_is_able_to_shove(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_able_to_shove, p);
}

auto level_is_able_to_walk_through_walls(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_able_to_walk_through_walls, p);
}

auto level_is_animated_can_hflip(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_animated_can_hflip, p);
}

auto level_is_animated_no_dir(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_animated_no_dir, p);
}

auto level_is_animated_sync_first(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_animated_sync_first, p);
}

auto level_is_animated(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_animated, p);
}

auto level_is_barrel(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_barrel, p);
}

auto level_is_blit_centered(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_blit_centered, p);
}

auto level_is_blit_flush_per_line(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_blit_flush_per_line, p);
}

auto level_is_blit_if_has_seen(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_blit_if_has_seen, p);
}

auto level_is_blit_obscures(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_blit_obscures, p);
}

auto level_is_blit_on_ground(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_blit_on_ground, p);
}

auto level_is_blit_outlined(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_blit_outlined, p);
}

auto level_is_blit_per_pixel_lighting(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_blit_per_pixel_lighting, p);
}

auto level_is_blit_shown_in_chasms(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_blit_shown_in_chasms, p);
}

auto level_is_blit_shown_in_overlay(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_blit_shown_in_overlay, p);
}

auto level_is_blit_square_outlined(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_blit_square_outlined, p);
}

auto level_is_blit_when_obscured(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_blit_when_obscured, p);
}

auto level_is_border(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_border, p);
}

auto level_is_brazier(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_brazier, p);
}

auto level_is_bridge(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_bridge, p);
}

auto level_is_broken_on_death(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_broken_on_death, p);
}

auto level_is_burnable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_burnable, p);
}

auto level_is_chasm(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_chasm, p);
}

auto level_is_collectable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_collectable, p);
}

auto level_is_collision_circle_large(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_collision_circle_large, p);
}

auto level_is_collision_circle_small(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_collision_circle_small, p);
}

auto level_is_collision_detection_enabled(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_collision_detection_enabled, p);
}

auto level_is_collision_square(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_collision_square, p);
}

auto level_is_combustible(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_combustible, p);
}

auto level_is_corpse_on_death(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_corpse_on_death, p);
}

auto level_is_corridor(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_corridor, p);
}

auto level_is_crushable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_crushable, p);
}

auto level_is_cursor_path_hazard(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_cursor_path_hazard, p);
}

auto level_is_cursor_path_none(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_cursor_path_none, p);
}

auto level_is_cursor_path_warning(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_cursor_path_warning, p);
}

auto level_is_cursor_path(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_cursor_path, p);
}

auto level_is_cursor(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_cursor, p);
}

auto level_is_damage_capped(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_damage_capped, p);
}

auto level_is_dead_on_collision(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_dead_on_collision, p);
}

auto level_is_dead_on_shoving(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_dead_on_shoving, p);
}

auto level_is_deep_water(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_deep_water, p);
}

auto level_is_described_cursor(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_described_cursor, p);
}

auto level_is_dirt(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_dirt, p);
}

auto level_is_dmap(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_dmap, p);
}

auto level_is_door_locked(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_door_locked, p);
}

auto level_is_door_secret(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_door_secret, p);
}

auto level_is_door_unlocked(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_door_unlocked, p);
}

auto level_is_dungeon_entrance(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_dungeon_entrance, p);
}

auto level_is_entrance(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_entrance, p);
}

auto level_is_ethereal(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_ethereal, p);
}

auto level_is_exit(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_exit, p);
}

auto level_is_explosion(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_explosion, p);
}

auto level_is_extinguished_on_death(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_extinguished_on_death, p);
}

auto level_is_fire(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_fire, p);
}

auto level_is_fireball(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_fireball, p);
}

auto level_is_flesh(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_flesh, p);
}

auto level_is_floating(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_floating, p);
}

auto level_is_floor(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_floor, p);
}

auto level_is_flying(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_flying, p);
}

auto level_is_foliage(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_foliage, p);
}

auto level_is_gaseous(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_gaseous, p);
}

auto level_is_ghost(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_ghost, p);
}

auto level_is_glass(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_glass, p);
}

auto level_is_gold(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_gold, p);
}

auto level_is_grass(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_grass, p);
}

auto level_is_health_bar_shown(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_health_bar_shown, p);
}

auto level_is_indestructible(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_indestructible, p);
}

auto level_is_insectoid(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_insectoid, p);
}

auto level_is_inventory_item(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_inventory_item, p);
}

auto level_is_item_droppable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_item_droppable, p);
}

auto level_is_item_equipable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_item_equipable, p);
}

auto level_is_item_mergeable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_item_mergeable, p);
}

auto level_is_item(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_item, p);
}

auto level_is_key(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_key, p);
}

auto level_is_kobalos(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_kobalos, p);
}

auto level_is_lava(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_lava, p);
}

auto level_is_level_across_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_level_across_icon, p);
}

auto level_is_level_curr(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_level_curr, p);
}

auto level_is_level_down_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_level_down_icon, p);
}

auto level_is_level_final_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_level_final_icon, p);
}

auto level_is_level_next_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_level_next_icon, p);
}

auto level_is_level_not_visited_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_level_not_visited_icon, p);
}

auto level_is_level_visited_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_level_visited_icon, p);
}

auto level_is_levitating(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_levitating, p);
}

auto level_is_light_source(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_light_source, p);
}

auto level_is_loggable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_loggable, p);
}

auto level_is_mantisman(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_mantisman, p);
}

auto level_is_meltable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_meltable, p);
}

auto level_is_metal(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_metal, p);
}

auto level_is_minion(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_minion, p);
}

auto level_is_mob_kill_minions_on_death(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_mob_kill_minions_on_death, p);
}

auto level_is_mob(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_mob, p);
}

auto level_is_mob1(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_mob1, p);
}

auto level_is_mob2(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_mob2, p);
}

auto level_is_monst_group_easy(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_monst_group_easy, p);
}

auto level_is_monst_group_hard(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_monst_group_hard, p);
}

auto level_is_monst_group_mob(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_monst_group_mob, p);
}

auto level_is_monst(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_monst, p);
}

auto level_is_needs_move_confirm(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_needs_move_confirm, p);
}

auto level_is_obs_to_cursor_path(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_obs_to_cursor_path, p);
}

auto level_is_obs_to_explosion(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_obs_to_explosion, p);
}

auto level_is_obs_to_falling_onto(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_obs_to_falling_onto, p);
}

auto level_is_obs_to_fire(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_obs_to_fire, p);
}

auto level_is_obs_to_jump_over(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_obs_to_jump_over, p);
}

auto level_is_obs_to_jumping_onto(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_obs_to_jumping_onto, p);
}

auto level_is_obs_to_jumping_out_of(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_obs_to_jumping_out_of, p);
}

auto level_is_obs_to_movement(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_obs_to_movement, p);
}

auto level_is_obs_to_spawning(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_obs_to_spawning, p);
}

auto level_is_obs_to_teleporting_onto(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_obs_to_teleporting_onto, p);
}

auto level_is_obs_to_vision(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_obs_to_vision, p);
}

auto level_is_obs_when_dead(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_obs_when_dead, p);
}

auto level_is_openable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_openable, p);
}

auto level_is_physics_explosion(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_physics_explosion, p);
}

auto level_is_physics_temperature(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_physics_temperature, p);
}

auto level_is_physics_water(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_physics_water, p);
}

auto level_is_pillar(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_pillar, p);
}

auto level_is_plant(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_plant, p);
}

auto level_is_player(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_player, p);
}

auto level_is_projectile(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_projectile, p);
}

auto level_is_removable_on_err(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_removable_on_err, p);
}

auto level_is_removable_when_dead_on_err(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_removable_when_dead_on_err, p);
}

auto level_is_rock(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_rock, p);
}

auto level_is_shovable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_shovable, p);
}

auto level_is_slime(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_slime, p);
}

auto level_is_smoke(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_smoke, p);
}

auto level_is_steam(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_steam, p);
}

auto level_is_stone(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_stone, p);
}

auto level_is_submergible(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_submergible, p);
}

auto level_is_teleport_blocked(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_teleport_blocked, p);
}

auto level_is_teleport(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_teleport, p);
}

auto level_is_tick_end_delay(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_tick_end_delay, p);
}

auto level_is_tickable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_tickable, p);
}

auto level_is_tiled(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_tiled, p);
}

auto level_is_trap(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_trap, p);
}

auto level_is_treasure(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_treasure, p);
}

auto level_is_undead(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_undead, p);
}

auto level_is_unused1(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused1, p);
}

auto level_is_unused10(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused10, p);
}

auto level_is_unused11(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused11, p);
}

auto level_is_unused12(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused12, p);
}

auto level_is_unused13(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused13, p);
}

auto level_is_unused14(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused14, p);
}

auto level_is_unused15(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused15, p);
}

auto level_is_unused16(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused16, p);
}

auto level_is_unused17(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused17, p);
}

auto level_is_unused18(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused18, p);
}

auto level_is_unused19(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused19, p);
}

auto level_is_unused2(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused2, p);
}

auto level_is_unused20(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused20, p);
}

auto level_is_unused21(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused21, p);
}

auto level_is_unused22(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused22, p);
}

auto level_is_unused23(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused23, p);
}

auto level_is_unused24(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused24, p);
}

auto level_is_unused25(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused25, p);
}

auto level_is_unused26(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused26, p);
}

auto level_is_unused27(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused27, p);
}

auto level_is_unused28(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused28, p);
}

auto level_is_unused29(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused29, p);
}

auto level_is_unused3(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused3, p);
}

auto level_is_unused30(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused30, p);
}

auto level_is_unused31(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused31, p);
}

auto level_is_unused32(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused32, p);
}

auto level_is_unused33(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused33, p);
}

auto level_is_unused34(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused34, p);
}

auto level_is_unused35(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused35, p);
}

auto level_is_unused36(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused36, p);
}

auto level_is_unused37(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused37, p);
}

auto level_is_unused38(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused38, p);
}

auto level_is_unused39(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused39, p);
}

auto level_is_unused4(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused4, p);
}

auto level_is_unused40(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused40, p);
}

auto level_is_unused41(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused41, p);
}

auto level_is_unused42(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused42, p);
}

auto level_is_unused43(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused43, p);
}

auto level_is_unused44(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused44, p);
}

auto level_is_unused45(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused45, p);
}

auto level_is_unused46(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused46, p);
}

auto level_is_unused47(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused47, p);
}

auto level_is_unused48(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused48, p);
}

auto level_is_unused49(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused49, p);
}

auto level_is_unused5(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused5, p);
}

auto level_is_unused50(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused50, p);
}

auto level_is_unused51(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused51, p);
}

auto level_is_unused52(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused52, p);
}

auto level_is_unused53(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused53, p);
}

auto level_is_unused54(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused54, p);
}

auto level_is_unused55(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused55, p);
}

auto level_is_unused56(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused56, p);
}

auto level_is_unused57(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused57, p);
}

auto level_is_unused58(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused58, p);
}

auto level_is_unused59(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused59, p);
}

auto level_is_unused6(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused6, p);
}

auto level_is_unused60(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused60, p);
}

auto level_is_unused61(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused61, p);
}

auto level_is_unused62(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused62, p);
}

auto level_is_unused63(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused63, p);
}

auto level_is_unused64(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused64, p);
}

auto level_is_unused65(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused65, p);
}

auto level_is_unused66(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused66, p);
}

auto level_is_unused67(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused67, p);
}

auto level_is_unused68(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused68, p);
}

auto level_is_unused7(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused7, p);
}

auto level_is_unused8(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused8, p);
}

auto level_is_unused9(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_unused9, p);
}

auto level_is_wait_on_dead_anim(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_wait_on_dead_anim, p);
}

auto level_is_wall(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_wall, p);
}

auto level_is_water(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_water, p);
}

auto level_is_wood(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_flag(g, v, l, is_wood, p);
}

auto level_alive_is_able_to_collect_items(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_able_to_collect_items, p);
}

auto level_alive_is_able_to_collect_keys(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_able_to_collect_keys, p);
}

auto level_alive_is_able_to_crush_grass(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_able_to_crush_grass, p);
}

auto level_alive_is_able_to_fall_repeatedly(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_able_to_fall_repeatedly, p);
}

auto level_alive_is_able_to_fall(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_able_to_fall, p);
}

auto level_alive_is_able_to_jump(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_able_to_jump, p);
}

auto level_alive_is_able_to_move_diagonally(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_able_to_move_diagonally, p);
}

auto level_alive_is_able_to_move_through_walls(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_able_to_move_through_walls, p);
}

auto level_alive_is_able_to_open(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_able_to_open, p);
}

auto level_alive_is_able_to_shove(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_able_to_shove, p);
}

auto level_alive_is_able_to_walk_through_walls(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_able_to_walk_through_walls, p);
}

auto level_alive_is_animated_can_hflip(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_animated_can_hflip, p);
}

auto level_alive_is_animated_no_dir(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_animated_no_dir, p);
}

auto level_alive_is_animated_sync_first(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_animated_sync_first, p);
}

auto level_alive_is_animated(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_animated, p);
}

auto level_alive_is_barrel(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_barrel, p);
}

auto level_alive_is_blit_centered(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_blit_centered, p);
}

auto level_alive_is_blit_flush_per_line(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_blit_flush_per_line, p);
}

auto level_alive_is_blit_if_has_seen(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_blit_if_has_seen, p);
}

auto level_alive_is_blit_obscures(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_blit_obscures, p);
}

auto level_alive_is_blit_on_ground(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_blit_on_ground, p);
}

auto level_alive_is_blit_outlined(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_blit_outlined, p);
}

auto level_alive_is_blit_per_pixel_lighting(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_blit_per_pixel_lighting, p);
}

auto level_alive_is_blit_shown_in_chasms(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_blit_shown_in_chasms, p);
}

auto level_alive_is_blit_shown_in_overlay(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_blit_shown_in_overlay, p);
}

auto level_alive_is_blit_square_outlined(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_blit_square_outlined, p);
}

auto level_alive_is_blit_when_obscured(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_blit_when_obscured, p);
}

auto level_alive_is_border(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_border, p);
}

auto level_alive_is_brazier(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_brazier, p);
}

auto level_alive_is_bridge(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_bridge, p);
}

auto level_alive_is_broken_on_death(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_broken_on_death, p);
}

auto level_alive_is_burnable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_burnable, p);
}

auto level_alive_is_chasm(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_chasm, p);
}

auto level_alive_is_collectable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_collectable, p);
}

auto level_alive_is_collision_circle_large(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_collision_circle_large, p);
}

auto level_alive_is_collision_circle_small(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_collision_circle_small, p);
}

auto level_alive_is_collision_detection_enabled(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_collision_detection_enabled, p);
}

auto level_alive_is_collision_square(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_collision_square, p);
}

auto level_alive_is_combustible(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_combustible, p);
}

auto level_alive_is_corpse_on_death(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_corpse_on_death, p);
}

auto level_alive_is_corridor(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_corridor, p);
}

auto level_alive_is_crushable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_crushable, p);
}

auto level_alive_is_cursor_path_hazard(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_cursor_path_hazard, p);
}

auto level_alive_is_cursor_path_none(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_cursor_path_none, p);
}

auto level_alive_is_cursor_path_warning(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_cursor_path_warning, p);
}

auto level_alive_is_cursor_path(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_cursor_path, p);
}

auto level_alive_is_cursor(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_cursor, p);
}

auto level_alive_is_damage_capped(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_damage_capped, p);
}

auto level_alive_is_dead_on_collision(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_dead_on_collision, p);
}

auto level_alive_is_dead_on_shoving(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_dead_on_shoving, p);
}

auto level_alive_is_deep_water(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_deep_water, p);
}

auto level_alive_is_described_cursor(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_described_cursor, p);
}

auto level_alive_is_dirt(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_dirt, p);
}

auto level_alive_is_dmap(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_dmap, p);
}

auto level_alive_is_door_locked(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_door_locked, p);
}

auto level_alive_is_door_secret(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_door_secret, p);
}

auto level_alive_is_door_unlocked(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_door_unlocked, p);
}

auto level_alive_is_dungeon_entrance(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_dungeon_entrance, p);
}

auto level_alive_is_entrance(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_entrance, p);
}

auto level_alive_is_ethereal(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_ethereal, p);
}

auto level_alive_is_exit(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_exit, p);
}

auto level_alive_is_explosion(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_explosion, p);
}

auto level_alive_is_extinguished_on_death(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_extinguished_on_death, p);
}

auto level_alive_is_fire(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_fire, p);
}

auto level_alive_is_fireball(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_fireball, p);
}

auto level_alive_is_flesh(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_flesh, p);
}

auto level_alive_is_floating(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_floating, p);
}

auto level_alive_is_floor(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_floor, p);
}

auto level_alive_is_flying(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_flying, p);
}

auto level_alive_is_foliage(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_foliage, p);
}

auto level_alive_is_gaseous(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_gaseous, p);
}

auto level_alive_is_ghost(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_ghost, p);
}

auto level_alive_is_glass(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_glass, p);
}

auto level_alive_is_gold(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_gold, p);
}

auto level_alive_is_grass(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_grass, p);
}

auto level_alive_is_health_bar_shown(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_health_bar_shown, p);
}

auto level_alive_is_indestructible(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_indestructible, p);
}

auto level_alive_is_insectoid(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_insectoid, p);
}

auto level_alive_is_inventory_item(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_inventory_item, p);
}

auto level_alive_is_item_droppable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_item_droppable, p);
}

auto level_alive_is_item_equipable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_item_equipable, p);
}

auto level_alive_is_item_mergeable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_item_mergeable, p);
}

auto level_alive_is_item(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_item, p);
}

auto level_alive_is_key(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_key, p);
}

auto level_alive_is_kobalos(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_kobalos, p);
}

auto level_alive_is_lava(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_lava, p);
}

auto level_alive_is_level_across_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_level_across_icon, p);
}

auto level_alive_is_level_curr(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_level_curr, p);
}

auto level_alive_is_level_down_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_level_down_icon, p);
}

auto level_alive_is_level_final_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_level_final_icon, p);
}

auto level_alive_is_level_next_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_level_next_icon, p);
}

auto level_alive_is_level_not_visited_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_level_not_visited_icon, p);
}

auto level_alive_is_level_visited_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_level_visited_icon, p);
}

auto level_alive_is_levitating(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_levitating, p);
}

auto level_alive_is_light_source(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_light_source, p);
}

auto level_alive_is_loggable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_loggable, p);
}

auto level_alive_is_mantisman(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_mantisman, p);
}

auto level_alive_is_meltable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_meltable, p);
}

auto level_alive_is_metal(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_metal, p);
}

auto level_alive_is_minion(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_minion, p);
}

auto level_alive_is_mob_kill_minions_on_death(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_mob_kill_minions_on_death, p);
}

auto level_alive_is_mob(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_mob, p);
}

auto level_alive_is_mob1(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_mob1, p);
}

auto level_alive_is_mob2(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_mob2, p);
}

auto level_alive_is_monst_group_easy(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_monst_group_easy, p);
}

auto level_alive_is_monst_group_hard(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_monst_group_hard, p);
}

auto level_alive_is_monst_group_mob(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_monst_group_mob, p);
}

auto level_alive_is_monst(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_monst, p);
}

auto level_alive_is_needs_move_confirm(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_needs_move_confirm, p);
}

auto level_alive_is_obs_to_cursor_path(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_obs_to_cursor_path, p);
}

auto level_alive_is_obs_to_explosion(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_obs_to_explosion, p);
}

auto level_alive_is_obs_to_falling_onto(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_obs_to_falling_onto, p);
}

auto level_alive_is_obs_to_fire(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_obs_to_fire, p);
}

auto level_alive_is_obs_to_jump_over(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_obs_to_jump_over, p);
}

auto level_alive_is_obs_to_jumping_onto(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_obs_to_jumping_onto, p);
}

auto level_alive_is_obs_to_jumping_out_of(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_obs_to_jumping_out_of, p);
}

auto level_alive_is_obs_to_movement(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_obs_to_movement, p);
}

auto level_alive_is_obs_to_spawning(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_obs_to_spawning, p);
}

auto level_alive_is_obs_to_teleporting_onto(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_obs_to_teleporting_onto, p);
}

auto level_alive_is_obs_to_vision(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_obs_to_vision, p);
}

auto level_alive_is_obs_when_dead(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_obs_when_dead, p);
}

auto level_alive_is_openable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_openable, p);
}

auto level_alive_is_physics_explosion(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_physics_explosion, p);
}

auto level_alive_is_physics_temperature(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_physics_temperature, p);
}

auto level_alive_is_physics_water(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_physics_water, p);
}

auto level_alive_is_pillar(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_pillar, p);
}

auto level_alive_is_plant(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_plant, p);
}

auto level_alive_is_player(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_player, p);
}

auto level_alive_is_projectile(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_projectile, p);
}

auto level_alive_is_removable_on_err(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_removable_on_err, p);
}

auto level_alive_is_removable_when_dead_on_err(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_removable_when_dead_on_err, p);
}

auto level_alive_is_rock(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_rock, p);
}

auto level_alive_is_shovable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_shovable, p);
}

auto level_alive_is_slime(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_slime, p);
}

auto level_alive_is_smoke(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_smoke, p);
}

auto level_alive_is_steam(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_steam, p);
}

auto level_alive_is_stone(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_stone, p);
}

auto level_alive_is_submergible(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_submergible, p);
}

auto level_alive_is_teleport_blocked(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_teleport_blocked, p);
}

auto level_alive_is_teleport(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_teleport, p);
}

auto level_alive_is_tick_end_delay(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_tick_end_delay, p);
}

auto level_alive_is_tickable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_tickable, p);
}

auto level_alive_is_tiled(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_tiled, p);
}

auto level_alive_is_trap(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_trap, p);
}

auto level_alive_is_treasure(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_treasure, p);
}

auto level_alive_is_undead(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_undead, p);
}

auto level_alive_is_unused1(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused1, p);
}

auto level_alive_is_unused10(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused10, p);
}

auto level_alive_is_unused11(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused11, p);
}

auto level_alive_is_unused12(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused12, p);
}

auto level_alive_is_unused13(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused13, p);
}

auto level_alive_is_unused14(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused14, p);
}

auto level_alive_is_unused15(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused15, p);
}

auto level_alive_is_unused16(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused16, p);
}

auto level_alive_is_unused17(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused17, p);
}

auto level_alive_is_unused18(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused18, p);
}

auto level_alive_is_unused19(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused19, p);
}

auto level_alive_is_unused2(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused2, p);
}

auto level_alive_is_unused20(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused20, p);
}

auto level_alive_is_unused21(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused21, p);
}

auto level_alive_is_unused22(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused22, p);
}

auto level_alive_is_unused23(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused23, p);
}

auto level_alive_is_unused24(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused24, p);
}

auto level_alive_is_unused25(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused25, p);
}

auto level_alive_is_unused26(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused26, p);
}

auto level_alive_is_unused27(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused27, p);
}

auto level_alive_is_unused28(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused28, p);
}

auto level_alive_is_unused29(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused29, p);
}

auto level_alive_is_unused3(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused3, p);
}

auto level_alive_is_unused30(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused30, p);
}

auto level_alive_is_unused31(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused31, p);
}

auto level_alive_is_unused32(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused32, p);
}

auto level_alive_is_unused33(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused33, p);
}

auto level_alive_is_unused34(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused34, p);
}

auto level_alive_is_unused35(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused35, p);
}

auto level_alive_is_unused36(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused36, p);
}

auto level_alive_is_unused37(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused37, p);
}

auto level_alive_is_unused38(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused38, p);
}

auto level_alive_is_unused39(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused39, p);
}

auto level_alive_is_unused4(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused4, p);
}

auto level_alive_is_unused40(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused40, p);
}

auto level_alive_is_unused41(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused41, p);
}

auto level_alive_is_unused42(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused42, p);
}

auto level_alive_is_unused43(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused43, p);
}

auto level_alive_is_unused44(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused44, p);
}

auto level_alive_is_unused45(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused45, p);
}

auto level_alive_is_unused46(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused46, p);
}

auto level_alive_is_unused47(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused47, p);
}

auto level_alive_is_unused48(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused48, p);
}

auto level_alive_is_unused49(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused49, p);
}

auto level_alive_is_unused5(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused5, p);
}

auto level_alive_is_unused50(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused50, p);
}

auto level_alive_is_unused51(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused51, p);
}

auto level_alive_is_unused52(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused52, p);
}

auto level_alive_is_unused53(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused53, p);
}

auto level_alive_is_unused54(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused54, p);
}

auto level_alive_is_unused55(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused55, p);
}

auto level_alive_is_unused56(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused56, p);
}

auto level_alive_is_unused57(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused57, p);
}

auto level_alive_is_unused58(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused58, p);
}

auto level_alive_is_unused59(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused59, p);
}

auto level_alive_is_unused6(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused6, p);
}

auto level_alive_is_unused60(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused60, p);
}

auto level_alive_is_unused61(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused61, p);
}

auto level_alive_is_unused62(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused62, p);
}

auto level_alive_is_unused63(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused63, p);
}

auto level_alive_is_unused64(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused64, p);
}

auto level_alive_is_unused65(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused65, p);
}

auto level_alive_is_unused66(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused66, p);
}

auto level_alive_is_unused67(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused67, p);
}

auto level_alive_is_unused68(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused68, p);
}

auto level_alive_is_unused7(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused7, p);
}

auto level_alive_is_unused8(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused8, p);
}

auto level_alive_is_unused9(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_unused9, p);
}

auto level_alive_is_wait_on_dead_anim(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_wait_on_dead_anim, p);
}

auto level_alive_is_wall(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_wall, p);
}

auto level_alive_is_water(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_water, p);
}

auto level_alive_is_wood(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_alive(g, v, l, is_wood, p);
}

auto level_count_is_able_to_collect_items(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_able_to_collect_items, p);
}

auto level_count_is_able_to_collect_keys(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_able_to_collect_keys, p);
}

auto level_count_is_able_to_crush_grass(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_able_to_crush_grass, p);
}

auto level_count_is_able_to_fall_repeatedly(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_able_to_fall_repeatedly, p);
}

auto level_count_is_able_to_fall(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_able_to_fall, p);
}

auto level_count_is_able_to_jump(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_able_to_jump, p);
}

auto level_count_is_able_to_move_diagonally(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_able_to_move_diagonally, p);
}

auto level_count_is_able_to_move_through_walls(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_able_to_move_through_walls, p);
}

auto level_count_is_able_to_open(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_able_to_open, p);
}

auto level_count_is_able_to_shove(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_able_to_shove, p);
}

auto level_count_is_able_to_walk_through_walls(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_able_to_walk_through_walls, p);
}

auto level_count_is_animated_can_hflip(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_animated_can_hflip, p);
}

auto level_count_is_animated_no_dir(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_animated_no_dir, p);
}

auto level_count_is_animated_sync_first(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_animated_sync_first, p);
}

auto level_count_is_animated(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_animated, p);
}

auto level_count_is_barrel(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_barrel, p);
}

auto level_count_is_blit_centered(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_blit_centered, p);
}

auto level_count_is_blit_flush_per_line(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_blit_flush_per_line, p);
}

auto level_count_is_blit_if_has_seen(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_blit_if_has_seen, p);
}

auto level_count_is_blit_obscures(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_blit_obscures, p);
}

auto level_count_is_blit_on_ground(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_blit_on_ground, p);
}

auto level_count_is_blit_outlined(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_blit_outlined, p);
}

auto level_count_is_blit_per_pixel_lighting(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_blit_per_pixel_lighting, p);
}

auto level_count_is_blit_shown_in_chasms(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_blit_shown_in_chasms, p);
}

auto level_count_is_blit_shown_in_overlay(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_blit_shown_in_overlay, p);
}

auto level_count_is_blit_square_outlined(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_blit_square_outlined, p);
}

auto level_count_is_blit_when_obscured(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_blit_when_obscured, p);
}

auto level_count_is_border(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_border, p);
}

auto level_count_is_brazier(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_brazier, p);
}

auto level_count_is_bridge(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_bridge, p);
}

auto level_count_is_broken_on_death(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_broken_on_death, p);
}

auto level_count_is_burnable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_burnable, p);
}

auto level_count_is_chasm(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_chasm, p);
}

auto level_count_is_collectable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_collectable, p);
}

auto level_count_is_collision_circle_large(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_collision_circle_large, p);
}

auto level_count_is_collision_circle_small(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_collision_circle_small, p);
}

auto level_count_is_collision_detection_enabled(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_collision_detection_enabled, p);
}

auto level_count_is_collision_square(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_collision_square, p);
}

auto level_count_is_combustible(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_combustible, p);
}

auto level_count_is_corpse_on_death(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_corpse_on_death, p);
}

auto level_count_is_corridor(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_corridor, p);
}

auto level_count_is_crushable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_crushable, p);
}

auto level_count_is_cursor_path_hazard(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_cursor_path_hazard, p);
}

auto level_count_is_cursor_path_none(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_cursor_path_none, p);
}

auto level_count_is_cursor_path_warning(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_cursor_path_warning, p);
}

auto level_count_is_cursor_path(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_cursor_path, p);
}

auto level_count_is_cursor(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_cursor, p);
}

auto level_count_is_damage_capped(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_damage_capped, p);
}

auto level_count_is_dead_on_collision(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_dead_on_collision, p);
}

auto level_count_is_dead_on_shoving(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_dead_on_shoving, p);
}

auto level_count_is_deep_water(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_deep_water, p);
}

auto level_count_is_described_cursor(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_described_cursor, p);
}

auto level_count_is_dirt(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_dirt, p);
}

auto level_count_is_dmap(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_dmap, p);
}

auto level_count_is_door_locked(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_door_locked, p);
}

auto level_count_is_door_secret(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_door_secret, p);
}

auto level_count_is_door_unlocked(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_door_unlocked, p);
}

auto level_count_is_dungeon_entrance(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_dungeon_entrance, p);
}

auto level_count_is_entrance(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_entrance, p);
}

auto level_count_is_ethereal(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_ethereal, p);
}

auto level_count_is_exit(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_exit, p);
}

auto level_count_is_explosion(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_explosion, p);
}

auto level_count_is_extinguished_on_death(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_extinguished_on_death, p);
}

auto level_count_is_fire(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_fire, p);
}

auto level_count_is_fireball(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_fireball, p);
}

auto level_count_is_flesh(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_flesh, p);
}

auto level_count_is_floating(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_floating, p);
}

auto level_count_is_floor(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_floor, p);
}

auto level_count_is_flying(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_flying, p);
}

auto level_count_is_foliage(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_foliage, p);
}

auto level_count_is_gaseous(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_gaseous, p);
}

auto level_count_is_ghost(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_ghost, p);
}

auto level_count_is_glass(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_glass, p);
}

auto level_count_is_gold(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_gold, p);
}

auto level_count_is_grass(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_grass, p);
}

auto level_count_is_health_bar_shown(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_health_bar_shown, p);
}

auto level_count_is_indestructible(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_indestructible, p);
}

auto level_count_is_insectoid(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_insectoid, p);
}

auto level_count_is_inventory_item(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_inventory_item, p);
}

auto level_count_is_item_droppable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_item_droppable, p);
}

auto level_count_is_item_equipable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_item_equipable, p);
}

auto level_count_is_item_mergeable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_item_mergeable, p);
}

auto level_count_is_item(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_item, p);
}

auto level_count_is_key(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_key, p);
}

auto level_count_is_kobalos(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_kobalos, p);
}

auto level_count_is_lava(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_lava, p);
}

auto level_count_is_level_across_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_level_across_icon, p);
}

auto level_count_is_level_curr(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_level_curr, p);
}

auto level_count_is_level_down_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_level_down_icon, p);
}

auto level_count_is_level_final_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_level_final_icon, p);
}

auto level_count_is_level_next_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_level_next_icon, p);
}

auto level_count_is_level_not_visited_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_level_not_visited_icon, p);
}

auto level_count_is_level_visited_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_level_visited_icon, p);
}

auto level_count_is_levitating(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_levitating, p);
}

auto level_count_is_light_source(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_light_source, p);
}

auto level_count_is_loggable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_loggable, p);
}

auto level_count_is_mantisman(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_mantisman, p);
}

auto level_count_is_meltable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_meltable, p);
}

auto level_count_is_metal(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_metal, p);
}

auto level_count_is_minion(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_minion, p);
}

auto level_count_is_mob_kill_minions_on_death(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_mob_kill_minions_on_death, p);
}

auto level_count_is_mob(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_mob, p);
}

auto level_count_is_mob1(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_mob1, p);
}

auto level_count_is_mob2(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_mob2, p);
}

auto level_count_is_monst_group_easy(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_monst_group_easy, p);
}

auto level_count_is_monst_group_hard(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_monst_group_hard, p);
}

auto level_count_is_monst_group_mob(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_monst_group_mob, p);
}

auto level_count_is_monst(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_monst, p);
}

auto level_count_is_needs_move_confirm(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_needs_move_confirm, p);
}

auto level_count_is_obs_to_cursor_path(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_obs_to_cursor_path, p);
}

auto level_count_is_obs_to_explosion(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_obs_to_explosion, p);
}

auto level_count_is_obs_to_falling_onto(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_obs_to_falling_onto, p);
}

auto level_count_is_obs_to_fire(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_obs_to_fire, p);
}

auto level_count_is_obs_to_jump_over(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_obs_to_jump_over, p);
}

auto level_count_is_obs_to_jumping_onto(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_obs_to_jumping_onto, p);
}

auto level_count_is_obs_to_jumping_out_of(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_obs_to_jumping_out_of, p);
}

auto level_count_is_obs_to_movement(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_obs_to_movement, p);
}

auto level_count_is_obs_to_spawning(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_obs_to_spawning, p);
}

auto level_count_is_obs_to_teleporting_onto(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_obs_to_teleporting_onto, p);
}

auto level_count_is_obs_to_vision(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_obs_to_vision, p);
}

auto level_count_is_obs_when_dead(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_obs_when_dead, p);
}

auto level_count_is_openable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_openable, p);
}

auto level_count_is_physics_explosion(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_physics_explosion, p);
}

auto level_count_is_physics_temperature(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_physics_temperature, p);
}

auto level_count_is_physics_water(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_physics_water, p);
}

auto level_count_is_pillar(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_pillar, p);
}

auto level_count_is_plant(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_plant, p);
}

auto level_count_is_player(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_player, p);
}

auto level_count_is_projectile(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_projectile, p);
}

auto level_count_is_removable_on_err(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_removable_on_err, p);
}

auto level_count_is_removable_when_dead_on_err(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_removable_when_dead_on_err, p);
}

auto level_count_is_rock(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_rock, p);
}

auto level_count_is_shovable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_shovable, p);
}

auto level_count_is_slime(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_slime, p);
}

auto level_count_is_smoke(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_smoke, p);
}

auto level_count_is_steam(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_steam, p);
}

auto level_count_is_stone(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_stone, p);
}

auto level_count_is_submergible(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_submergible, p);
}

auto level_count_is_teleport_blocked(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_teleport_blocked, p);
}

auto level_count_is_teleport(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_teleport, p);
}

auto level_count_is_tick_end_delay(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_tick_end_delay, p);
}

auto level_count_is_tickable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_tickable, p);
}

auto level_count_is_tiled(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_tiled, p);
}

auto level_count_is_trap(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_trap, p);
}

auto level_count_is_treasure(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_treasure, p);
}

auto level_count_is_undead(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_undead, p);
}

auto level_count_is_unused1(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused1, p);
}

auto level_count_is_unused10(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused10, p);
}

auto level_count_is_unused11(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused11, p);
}

auto level_count_is_unused12(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused12, p);
}

auto level_count_is_unused13(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused13, p);
}

auto level_count_is_unused14(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused14, p);
}

auto level_count_is_unused15(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused15, p);
}

auto level_count_is_unused16(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused16, p);
}

auto level_count_is_unused17(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused17, p);
}

auto level_count_is_unused18(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused18, p);
}

auto level_count_is_unused19(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused19, p);
}

auto level_count_is_unused2(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused2, p);
}

auto level_count_is_unused20(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused20, p);
}

auto level_count_is_unused21(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused21, p);
}

auto level_count_is_unused22(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused22, p);
}

auto level_count_is_unused23(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused23, p);
}

auto level_count_is_unused24(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused24, p);
}

auto level_count_is_unused25(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused25, p);
}

auto level_count_is_unused26(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused26, p);
}

auto level_count_is_unused27(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused27, p);
}

auto level_count_is_unused28(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused28, p);
}

auto level_count_is_unused29(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused29, p);
}

auto level_count_is_unused3(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused3, p);
}

auto level_count_is_unused30(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused30, p);
}

auto level_count_is_unused31(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused31, p);
}

auto level_count_is_unused32(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused32, p);
}

auto level_count_is_unused33(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused33, p);
}

auto level_count_is_unused34(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused34, p);
}

auto level_count_is_unused35(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused35, p);
}

auto level_count_is_unused36(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused36, p);
}

auto level_count_is_unused37(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused37, p);
}

auto level_count_is_unused38(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused38, p);
}

auto level_count_is_unused39(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused39, p);
}

auto level_count_is_unused4(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused4, p);
}

auto level_count_is_unused40(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused40, p);
}

auto level_count_is_unused41(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused41, p);
}

auto level_count_is_unused42(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused42, p);
}

auto level_count_is_unused43(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused43, p);
}

auto level_count_is_unused44(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused44, p);
}

auto level_count_is_unused45(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused45, p);
}

auto level_count_is_unused46(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused46, p);
}

auto level_count_is_unused47(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused47, p);
}

auto level_count_is_unused48(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused48, p);
}

auto level_count_is_unused49(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused49, p);
}

auto level_count_is_unused5(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused5, p);
}

auto level_count_is_unused50(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused50, p);
}

auto level_count_is_unused51(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused51, p);
}

auto level_count_is_unused52(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused52, p);
}

auto level_count_is_unused53(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused53, p);
}

auto level_count_is_unused54(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused54, p);
}

auto level_count_is_unused55(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused55, p);
}

auto level_count_is_unused56(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused56, p);
}

auto level_count_is_unused57(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused57, p);
}

auto level_count_is_unused58(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused58, p);
}

auto level_count_is_unused59(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused59, p);
}

auto level_count_is_unused6(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused6, p);
}

auto level_count_is_unused60(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused60, p);
}

auto level_count_is_unused61(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused61, p);
}

auto level_count_is_unused62(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused62, p);
}

auto level_count_is_unused63(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused63, p);
}

auto level_count_is_unused64(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused64, p);
}

auto level_count_is_unused65(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused65, p);
}

auto level_count_is_unused66(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused66, p);
}

auto level_count_is_unused67(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused67, p);
}

auto level_count_is_unused68(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused68, p);
}

auto level_count_is_unused7(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused7, p);
}

auto level_count_is_unused8(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused8, p);
}

auto level_count_is_unused9(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_unused9, p);
}

auto level_count_is_wait_on_dead_anim(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_wait_on_dead_anim, p);
}

auto level_count_is_wall(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_wall, p);
}

auto level_count_is_water(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_water, p);
}

auto level_count_is_wood(Gamep g, Levelsp v, Levelp l, const spoint &p) -> uint32_t
{
  TRACE_AND_INDENT();
  return level_count(g, v, l, is_wood, p);
}

auto level_open_is_able_to_collect_items(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_able_to_collect_items, p);
}

auto level_open_is_able_to_collect_keys(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_able_to_collect_keys, p);
}

auto level_open_is_able_to_crush_grass(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_able_to_crush_grass, p);
}

auto level_open_is_able_to_fall_repeatedly(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_able_to_fall_repeatedly, p);
}

auto level_open_is_able_to_fall(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_able_to_fall, p);
}

auto level_open_is_able_to_jump(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_able_to_jump, p);
}

auto level_open_is_able_to_move_diagonally(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_able_to_move_diagonally, p);
}

auto level_open_is_able_to_move_through_walls(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_able_to_move_through_walls, p);
}

auto level_open_is_able_to_open(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_able_to_open, p);
}

auto level_open_is_able_to_shove(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_able_to_shove, p);
}

auto level_open_is_able_to_walk_through_walls(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_able_to_walk_through_walls, p);
}

auto level_open_is_animated_can_hflip(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_animated_can_hflip, p);
}

auto level_open_is_animated_no_dir(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_animated_no_dir, p);
}

auto level_open_is_animated_sync_first(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_animated_sync_first, p);
}

auto level_open_is_animated(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_animated, p);
}

auto level_open_is_barrel(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_barrel, p);
}

auto level_open_is_blit_centered(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_blit_centered, p);
}

auto level_open_is_blit_flush_per_line(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_blit_flush_per_line, p);
}

auto level_open_is_blit_if_has_seen(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_blit_if_has_seen, p);
}

auto level_open_is_blit_obscures(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_blit_obscures, p);
}

auto level_open_is_blit_on_ground(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_blit_on_ground, p);
}

auto level_open_is_blit_outlined(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_blit_outlined, p);
}

auto level_open_is_blit_per_pixel_lighting(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_blit_per_pixel_lighting, p);
}

auto level_open_is_blit_shown_in_chasms(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_blit_shown_in_chasms, p);
}

auto level_open_is_blit_shown_in_overlay(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_blit_shown_in_overlay, p);
}

auto level_open_is_blit_square_outlined(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_blit_square_outlined, p);
}

auto level_open_is_blit_when_obscured(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_blit_when_obscured, p);
}

auto level_open_is_border(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_border, p);
}

auto level_open_is_brazier(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_brazier, p);
}

auto level_open_is_bridge(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_bridge, p);
}

auto level_open_is_broken_on_death(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_broken_on_death, p);
}

auto level_open_is_burnable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_burnable, p);
}

auto level_open_is_chasm(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_chasm, p);
}

auto level_open_is_collectable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_collectable, p);
}

auto level_open_is_collision_circle_large(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_collision_circle_large, p);
}

auto level_open_is_collision_circle_small(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_collision_circle_small, p);
}

auto level_open_is_collision_detection_enabled(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_collision_detection_enabled, p);
}

auto level_open_is_collision_square(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_collision_square, p);
}

auto level_open_is_combustible(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_combustible, p);
}

auto level_open_is_corpse_on_death(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_corpse_on_death, p);
}

auto level_open_is_corridor(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_corridor, p);
}

auto level_open_is_crushable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_crushable, p);
}

auto level_open_is_cursor_path_hazard(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_cursor_path_hazard, p);
}

auto level_open_is_cursor_path_none(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_cursor_path_none, p);
}

auto level_open_is_cursor_path_warning(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_cursor_path_warning, p);
}

auto level_open_is_cursor_path(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_cursor_path, p);
}

auto level_open_is_cursor(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_cursor, p);
}

auto level_open_is_damage_capped(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_damage_capped, p);
}

auto level_open_is_dead_on_collision(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_dead_on_collision, p);
}

auto level_open_is_dead_on_shoving(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_dead_on_shoving, p);
}

auto level_open_is_deep_water(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_deep_water, p);
}

auto level_open_is_described_cursor(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_described_cursor, p);
}

auto level_open_is_dirt(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_dirt, p);
}

auto level_open_is_dmap(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_dmap, p);
}

auto level_open_is_door_locked(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_door_locked, p);
}

auto level_open_is_door_secret(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_door_secret, p);
}

auto level_open_is_door_unlocked(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_door_unlocked, p);
}

auto level_open_is_dungeon_entrance(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_dungeon_entrance, p);
}

auto level_open_is_entrance(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_entrance, p);
}

auto level_open_is_ethereal(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_ethereal, p);
}

auto level_open_is_exit(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_exit, p);
}

auto level_open_is_explosion(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_explosion, p);
}

auto level_open_is_extinguished_on_death(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_extinguished_on_death, p);
}

auto level_open_is_fire(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_fire, p);
}

auto level_open_is_fireball(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_fireball, p);
}

auto level_open_is_flesh(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_flesh, p);
}

auto level_open_is_floating(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_floating, p);
}

auto level_open_is_floor(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_floor, p);
}

auto level_open_is_flying(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_flying, p);
}

auto level_open_is_foliage(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_foliage, p);
}

auto level_open_is_gaseous(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_gaseous, p);
}

auto level_open_is_ghost(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_ghost, p);
}

auto level_open_is_glass(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_glass, p);
}

auto level_open_is_gold(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_gold, p);
}

auto level_open_is_grass(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_grass, p);
}

auto level_open_is_health_bar_shown(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_health_bar_shown, p);
}

auto level_open_is_indestructible(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_indestructible, p);
}

auto level_open_is_insectoid(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_insectoid, p);
}

auto level_open_is_inventory_item(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_inventory_item, p);
}

auto level_open_is_item_droppable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_item_droppable, p);
}

auto level_open_is_item_equipable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_item_equipable, p);
}

auto level_open_is_item_mergeable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_item_mergeable, p);
}

auto level_open_is_item(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_item, p);
}

auto level_open_is_key(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_key, p);
}

auto level_open_is_kobalos(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_kobalos, p);
}

auto level_open_is_lava(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_lava, p);
}

auto level_open_is_level_across_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_level_across_icon, p);
}

auto level_open_is_level_curr(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_level_curr, p);
}

auto level_open_is_level_down_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_level_down_icon, p);
}

auto level_open_is_level_final_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_level_final_icon, p);
}

auto level_open_is_level_next_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_level_next_icon, p);
}

auto level_open_is_level_not_visited_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_level_not_visited_icon, p);
}

auto level_open_is_level_visited_icon(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_level_visited_icon, p);
}

auto level_open_is_levitating(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_levitating, p);
}

auto level_open_is_light_source(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_light_source, p);
}

auto level_open_is_loggable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_loggable, p);
}

auto level_open_is_mantisman(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_mantisman, p);
}

auto level_open_is_meltable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_meltable, p);
}

auto level_open_is_metal(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_metal, p);
}

auto level_open_is_minion(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_minion, p);
}

auto level_open_is_mob_kill_minions_on_death(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_mob_kill_minions_on_death, p);
}

auto level_open_is_mob(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_mob, p);
}

auto level_open_is_mob1(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_mob1, p);
}

auto level_open_is_mob2(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_mob2, p);
}

auto level_open_is_monst_group_easy(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_monst_group_easy, p);
}

auto level_open_is_monst_group_hard(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_monst_group_hard, p);
}

auto level_open_is_monst_group_mob(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_monst_group_mob, p);
}

auto level_open_is_monst(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_monst, p);
}

auto level_open_is_needs_move_confirm(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_needs_move_confirm, p);
}

auto level_open_is_obs_to_cursor_path(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_obs_to_cursor_path, p);
}

auto level_open_is_obs_to_explosion(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_obs_to_explosion, p);
}

auto level_open_is_obs_to_falling_onto(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_obs_to_falling_onto, p);
}

auto level_open_is_obs_to_fire(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_obs_to_fire, p);
}

auto level_open_is_obs_to_jump_over(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_obs_to_jump_over, p);
}

auto level_open_is_obs_to_jumping_onto(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_obs_to_jumping_onto, p);
}

auto level_open_is_obs_to_jumping_out_of(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_obs_to_jumping_out_of, p);
}

auto level_open_is_obs_to_movement(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_obs_to_movement, p);
}

auto level_open_is_obs_to_spawning(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_obs_to_spawning, p);
}

auto level_open_is_obs_to_teleporting_onto(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_obs_to_teleporting_onto, p);
}

auto level_open_is_obs_to_vision(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_obs_to_vision, p);
}

auto level_open_is_obs_when_dead(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_obs_when_dead, p);
}

auto level_open_is_openable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_openable, p);
}

auto level_open_is_physics_explosion(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_physics_explosion, p);
}

auto level_open_is_physics_temperature(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_physics_temperature, p);
}

auto level_open_is_physics_water(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_physics_water, p);
}

auto level_open_is_pillar(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_pillar, p);
}

auto level_open_is_plant(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_plant, p);
}

auto level_open_is_player(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_player, p);
}

auto level_open_is_projectile(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_projectile, p);
}

auto level_open_is_removable_on_err(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_removable_on_err, p);
}

auto level_open_is_removable_when_dead_on_err(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_removable_when_dead_on_err, p);
}

auto level_open_is_rock(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_rock, p);
}

auto level_open_is_shovable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_shovable, p);
}

auto level_open_is_slime(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_slime, p);
}

auto level_open_is_smoke(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_smoke, p);
}

auto level_open_is_steam(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_steam, p);
}

auto level_open_is_stone(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_stone, p);
}

auto level_open_is_submergible(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_submergible, p);
}

auto level_open_is_teleport_blocked(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_teleport_blocked, p);
}

auto level_open_is_teleport(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_teleport, p);
}

auto level_open_is_tick_end_delay(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_tick_end_delay, p);
}

auto level_open_is_tickable(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_tickable, p);
}

auto level_open_is_tiled(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_tiled, p);
}

auto level_open_is_trap(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_trap, p);
}

auto level_open_is_treasure(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_treasure, p);
}

auto level_open_is_undead(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_undead, p);
}

auto level_open_is_unused1(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused1, p);
}

auto level_open_is_unused10(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused10, p);
}

auto level_open_is_unused11(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused11, p);
}

auto level_open_is_unused12(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused12, p);
}

auto level_open_is_unused13(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused13, p);
}

auto level_open_is_unused14(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused14, p);
}

auto level_open_is_unused15(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused15, p);
}

auto level_open_is_unused16(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused16, p);
}

auto level_open_is_unused17(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused17, p);
}

auto level_open_is_unused18(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused18, p);
}

auto level_open_is_unused19(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused19, p);
}

auto level_open_is_unused2(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused2, p);
}

auto level_open_is_unused20(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused20, p);
}

auto level_open_is_unused21(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused21, p);
}

auto level_open_is_unused22(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused22, p);
}

auto level_open_is_unused23(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused23, p);
}

auto level_open_is_unused24(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused24, p);
}

auto level_open_is_unused25(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused25, p);
}

auto level_open_is_unused26(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused26, p);
}

auto level_open_is_unused27(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused27, p);
}

auto level_open_is_unused28(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused28, p);
}

auto level_open_is_unused29(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused29, p);
}

auto level_open_is_unused3(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused3, p);
}

auto level_open_is_unused30(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused30, p);
}

auto level_open_is_unused31(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused31, p);
}

auto level_open_is_unused32(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused32, p);
}

auto level_open_is_unused33(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused33, p);
}

auto level_open_is_unused34(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused34, p);
}

auto level_open_is_unused35(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused35, p);
}

auto level_open_is_unused36(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused36, p);
}

auto level_open_is_unused37(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused37, p);
}

auto level_open_is_unused38(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused38, p);
}

auto level_open_is_unused39(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused39, p);
}

auto level_open_is_unused4(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused4, p);
}

auto level_open_is_unused40(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused40, p);
}

auto level_open_is_unused41(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused41, p);
}

auto level_open_is_unused42(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused42, p);
}

auto level_open_is_unused43(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused43, p);
}

auto level_open_is_unused44(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused44, p);
}

auto level_open_is_unused45(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused45, p);
}

auto level_open_is_unused46(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused46, p);
}

auto level_open_is_unused47(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused47, p);
}

auto level_open_is_unused48(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused48, p);
}

auto level_open_is_unused49(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused49, p);
}

auto level_open_is_unused5(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused5, p);
}

auto level_open_is_unused50(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused50, p);
}

auto level_open_is_unused51(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused51, p);
}

auto level_open_is_unused52(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused52, p);
}

auto level_open_is_unused53(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused53, p);
}

auto level_open_is_unused54(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused54, p);
}

auto level_open_is_unused55(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused55, p);
}

auto level_open_is_unused56(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused56, p);
}

auto level_open_is_unused57(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused57, p);
}

auto level_open_is_unused58(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused58, p);
}

auto level_open_is_unused59(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused59, p);
}

auto level_open_is_unused6(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused6, p);
}

auto level_open_is_unused60(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused60, p);
}

auto level_open_is_unused61(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused61, p);
}

auto level_open_is_unused62(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused62, p);
}

auto level_open_is_unused63(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused63, p);
}

auto level_open_is_unused64(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused64, p);
}

auto level_open_is_unused65(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused65, p);
}

auto level_open_is_unused66(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused66, p);
}

auto level_open_is_unused67(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused67, p);
}

auto level_open_is_unused68(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused68, p);
}

auto level_open_is_unused7(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused7, p);
}

auto level_open_is_unused8(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused8, p);
}

auto level_open_is_unused9(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_unused9, p);
}

auto level_open_is_wait_on_dead_anim(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_wait_on_dead_anim, p);
}

auto level_open_is_wall(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_wall, p);
}

auto level_open_is_water(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_water, p);
}

auto level_open_is_wood(Gamep g, Levelsp v, Levelp l, const spoint &p) -> Thingp
{
  TRACE_AND_INDENT();
  return level_open(g, v, l, is_wood, p);
}
