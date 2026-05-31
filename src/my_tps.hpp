//
// Copyright goblinhack@gmail.com
//

#ifndef MY_TPS_HPP
#define MY_TPS_HPP

[[nodiscard]] auto templates_init() ->  bool;

// clang-format off
/* begin shell marker1 */
/* shell for i in $(find things -name "*.cpp" | xargs grep -h "^auto tp_load" | sort | awk '{print $2}' | cut -d'(' -f1 ) */
/* shell do */
/* shell echo "auto $i() -> bool;" */
/* shell done */
[[nodiscard]] auto tp_load_argusul() ->  bool;
[[nodiscard]] auto tp_load_barrel() ->  bool;
[[nodiscard]] auto tp_load_blitzhound() ->  bool;
[[nodiscard]] auto tp_load_border() ->  bool;
[[nodiscard]] auto tp_load_brazier() ->  bool;
[[nodiscard]] auto tp_load_bridge() ->  bool;
[[nodiscard]] auto tp_load_chasm() ->  bool;
[[nodiscard]] auto tp_load_chest() ->  bool;
[[nodiscard]] auto tp_load_corridor() ->  bool;
[[nodiscard]] auto tp_load_cursor_at() ->  bool;
[[nodiscard]] auto tp_load_cursor_path() ->  bool;
[[nodiscard]] auto tp_load_deep_water() ->  bool;
[[nodiscard]] auto tp_load_dirt() ->  bool;
[[nodiscard]] auto tp_load_door_locked() ->  bool;
[[nodiscard]] auto tp_load_door_secret() ->  bool;
[[nodiscard]] auto tp_load_door_unlocked() ->  bool;
[[nodiscard]] auto tp_load_effect_attack() ->  bool;
[[nodiscard]] auto tp_load_effect_blood() ->  bool;
[[nodiscard]] auto tp_load_entrance() ->  bool;
[[nodiscard]] auto tp_load_exit() ->  bool;
[[nodiscard]] auto tp_load_explosion() ->  bool;
[[nodiscard]] auto tp_load_fire() ->  bool;
[[nodiscard]] auto tp_load_fireball() ->  bool;
[[nodiscard]] auto tp_load_floor() ->  bool;
[[nodiscard]] auto tp_load_foliage() ->  bool;
[[nodiscard]] auto tp_load_ghost_mob() ->  bool;
[[nodiscard]] auto tp_load_ghost() ->  bool;
[[nodiscard]] auto tp_load_glorp() ->  bool;
[[nodiscard]] auto tp_load_grass() ->  bool;
[[nodiscard]] auto tp_load_key() ->  bool;
[[nodiscard]] auto tp_load_kobalos_mob() ->  bool;
[[nodiscard]] auto tp_load_kobalos() ->  bool;
[[nodiscard]] auto tp_load_laser_fire() ->  bool;
[[nodiscard]] auto tp_load_laser_light() ->  bool;
[[nodiscard]] auto tp_load_lava() ->  bool;
[[nodiscard]] auto tp_load_level_closed() ->  bool;
[[nodiscard]] auto tp_load_level_curr() ->  bool;
[[nodiscard]] auto tp_load_level_final() ->  bool;
[[nodiscard]] auto tp_load_level_locked() ->  bool;
[[nodiscard]] auto tp_load_level_next() ->  bool;
[[nodiscard]] auto tp_load_level_open() ->  bool;
[[nodiscard]] auto tp_load_level_select_bg() ->  bool;
[[nodiscard]] auto tp_load_mantisman() ->  bool;
[[nodiscard]] auto tp_load_pillar() ->  bool;
[[nodiscard]] auto tp_load_player() ->  bool;
[[nodiscard]] auto tp_load_potion() ->  bool;
[[nodiscard]] auto tp_load_reeds() ->  bool;
[[nodiscard]] auto tp_load_rock() ->  bool;
[[nodiscard]] auto tp_load_smoke() ->  bool;
[[nodiscard]] auto tp_load_staff_fire() ->  bool;
[[nodiscard]] auto tp_load_steam() ->  bool;
[[nodiscard]] auto tp_load_teleport() ->  bool;
[[nodiscard]] auto tp_load_trap() ->  bool;
[[nodiscard]] auto tp_load_vault() ->  bool;
[[nodiscard]] auto tp_load_wall() ->  bool;
[[nodiscard]] auto tp_load_wand_fire() ->  bool;
[[nodiscard]] auto tp_load_wand_light() ->  bool;
[[nodiscard]] auto tp_load_water() ->  bool;
  /* end shell marker1 */

#endif
