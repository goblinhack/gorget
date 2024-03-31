//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_time.hpp"

void Level::tick(void)
{
  TRACE_NO_INDENT();

  data->last_time_step = data->time_step;
  if (data->tick_in_progress) {
    //
    // A tick is running
    //
    tick_time_step();
  } else if (data->_tick_begin_requested) {
    //
    // Start the tick
    //
    tick_begin();
  } else {
    //
    // Idle state
    //
  }

  //
  // Move things
  //
  if (data->tick_in_progress) {
    CON("TICK time_step %f", data->time_step);
    tick_body(data->time_step - data->last_time_step);
  }

  //
  // End of tick?
  //
  if (data->_tick_end_requested) {
    CON("TICK end");
    tick_end_requested();
  }
}

void Level::tick_time_step(void)
{
  //
  // How long each tick takes
  //
  static float tick_duration_ms = 1000;

  CON("TICK in progress");

  if (! data->tick_begin_ms) {
    //
    // First tick
    //
    data->tick_begin_ms = time_ms();
    data->time_step     = 0.0;
  } else {
    //
    // Continue the tick
    //
    data->time_step = ((float) (time_ms() - data->tick_begin_ms)) / (float) tick_duration_ms;
    if (data->time_step >= 1.0) {
      //
      // Tick has surpassed its time
      //
      data->time_step           = 1.0;
      data->_tick_end_requested = true;
    }
  }
}

void Level::tick_body(float dt)
{
  TRACE_NO_INDENT();

  auto    p            = thing_player();
  int16_t player_speed = p ? p->speed : 100;

  FOR_ALL_THINGS(t)
  {
    CON("TICK dt %f", dt);
    //                   Tick 1              Tick 2
    //            =================== ===================
    //            0.00 0.25 0.50 1.00 0.00 0.25 0.50 1.00
    // --------------------------------------------------------
    // speed 400  tick tick tick tick tick tick tick tick
    // speed 200  tick      tick      tick      tick
    // speed 100  tick           tick
    // speed 50   tick
    //
    t->thing_dt += dt * ((float) t->speed / (float) player_speed);
    if (t->thing_dt >= 1.0) {
      t->thing_dt = 1.0;
    }

    thing_update_pixel_pos(t, t->thing_dt);

    if (t->thing_dt >= 1.0) {
      // thing tick
      t->thing_dt = 0.0;
    }
  }
}

void Level::tick_begin(void)
{
  CON("TICK begin");

  data->tick++;
  data->_tick_begin_requested = false;
  data->tick_begin_ms         = time_ms();
  data->time_step             = 0.0;
  data->tick_in_progress      = true;
}

void Level::tick_begin_requested(const std::string &why)
{
  TRACE_NO_INDENT();

  data->_tick_begin_requested = true;

  data->request_player_move_up    = false;
  data->request_player_move_down  = false;
  data->request_player_move_left  = false;
  data->request_player_move_right = false;
}

void Level::tick_end_requested(void)
{
  TRACE_NO_INDENT();

  data->tick_in_progress    = false;
  data->_tick_end_requested = false;
  data->time_step           = 0;
}

bool Level::tick_is_in_progress(void)
{
  TRACE_NO_INDENT();

  return data->tick_in_progress;
}
