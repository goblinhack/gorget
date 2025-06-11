//
// Copyright goblinhack@gmail.com
//

#include "../my_test.hpp"

static bool test_move_obstacle(Gamep g)
{
  TRACE_NO_INDENT();

  return true;
}

bool test_load_move_obstacle(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("move_obstacle");

  // begin sort marker1 {
  test_callback_set(test, test_move_obstacle);
  // end sort marker1 }

  return true;
}
