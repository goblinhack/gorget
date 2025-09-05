//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_sound.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tp_callbacks.hpp"
#include "my_tps.hpp"
#include "my_types.hpp"

static void tp_explosion_spawn(Gamep g, Levelsp v, Levelp l, Thingp t)
{
  TRACE_NO_INDENT();

  sound_play(g, "explosion");
}

bool tp_load_explosion(void)
{
  TRACE_NO_INDENT();

  auto tp   = tp_load("explosion"); // keep as string for scripts
  auto name = tp_name(tp);

  // begin sort marker1 {
  tp_damage_set(tp, THING_EVENT_EXPLOSION_DAMAGE, "20+1d20");
  tp_flag_set(tp, is_animated);
  tp_flag_set(tp, is_blit_centered);
  tp_flag_set(tp, is_described_cursor);
  tp_on_spawn_set(tp, tp_explosion_spawn);
  tp_flag_set(tp, is_explosion);
  tp_flag_set(tp, is_gaseous);
  tp_flag_set(tp, is_light_source, 5);
  tp_flag_set(tp, is_loggable);
  tp_flag_set(tp, is_physics_temperature);
  tp_flag_set(tp, is_teleport_blocked);
  tp_flag_set(tp, is_tick_delay_on_spawn);
  tp_flag_set(tp, is_wait_on_dead_anim);
  tp_light_color_set(tp, "white");
  tp_temperature_initial_set(tp, 1000); // celsius
  tp_weight_set(tp, WEIGHT_NONE);       // grams
  tp_z_depth_set(tp, MAP_Z_DEPTH_OBJ);
  // end sort marker1 }

  auto delay = 50;

  for (auto frame = 0; frame < 6; frame++) {
    auto tile = tile_find_mand(name + std::string(".idle.") + std::to_string(frame));
    tile_delay_ms_set(tile, delay);
    tp_tiles_push_back(tp, THING_ANIM_IDLE, tile);

    if (frame == 5) {
      tile_is_cleanup_on_end_of_anim_set(tile);
    }
  }

  return true;
}
