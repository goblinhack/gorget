//
// Copyright goblinhack@gmail.com
//

#include "../my_test.hpp"

static bool test_move_ok(Gamep g)
{
  TRACE_NO_INDENT();

  return true;
}

bool test_load_move_ok(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("move_ok");

  // begin sort marker1 {
  test_callback_set(test, test_move_ok);
  // end sort marker1 }

  return true;
}
