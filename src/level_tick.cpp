//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_time.hpp"

void Level::tick(void)
{
  TRACE_NO_INDENT();

  //
  // How long each tick takes
  //
  static float dt;
  static float last_dt;
  static float tick_duration_ms = 100;
  auto         p                = player();
  int16_t      player_speed     = p ? p->speed : 100;

  last_dt = dt;
  if (data->tick_in_progress) {
    CON("TICK in progress");
    //
    // A tick is running
    //
    if (! data->tick_start) {
      //
      // First tick
      //
      data->tick_start = time_ms();
      dt               = 0.0;
    } else {
      //
      // Continue the tick
      //
      dt = ((float) (time_ms() - data->tick_start)) / (float) tick_duration_ms;
      if (dt >= 1.0) {
        //
        // Tick has surpassed its time
        //
        dt                       = 1.0;
        data->tick_end_requested = true;
      }
    }
  } else if (data->tick_start_requested) {
    CON("TICK requested");
    //
    // Player has moved
    //
    data->tick_start_requested = false;
    data->tick_start           = time_ms();
    dt                         = 0.0;
    data->tick++;
    data->tick_in_progress = true;
  } else {
    //
    // Idle state
    //
    CON("TICK idle");
  }

  if (data->tick_in_progress) {
    CON("TICK dt %f", dt);
    for (auto slot = 0; slot < MAP_SLOTS; slot++) {
      for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
          Tpp   tp;
          point p(x, y);
          auto  t = thing_get(p, slot, &tp);
          if (! t) {
            continue;
          }

          //                   Tick 1              Tick 2
          //            =================== ===================
          //            0.00 0.25 0.50 1.00 0.00 0.25 0.50 1.00
          // --------------------------------------------------------
          // speed 400  tick tick tick tick tick tick tick tick
          // speed 200  tick      tick      tick      tick
          // speed 100  tick           tick
          // speed 50   tick
          //
          t->thing_dt += (dt - last_dt) * ((float) t->speed / (float) player_speed);
          if (t->thing_dt >= 1.0) {
            t->thing_dt = 1.0;
          }

          CON("thing %p tick %f", t, t->thing_dt);
          thing_update_pixel_pos(t, t->thing_dt);

          if (t->thing_dt >= 1.0) {
            // thing tick
            t->thing_dt = 0.0;
          }
        }
      }
    }
  }

  if (data->tick_end_requested) {
    CON("TICK end");
    data->tick_in_progress   = false;
    data->tick_end_requested = false;
    dt                       = 0;
  }
}
