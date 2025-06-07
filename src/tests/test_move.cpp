//
// Copyright goblinhack@gmail.com
//

#include "../my_test.hpp"

static bool test_move(Gamep g)
{
  TRACE_NO_INDENT();

  return true;
}

bool test_load_move(void)
{
  TRACE_NO_INDENT();

  Testp test = test_load("move");

  // begin sort marker1 {
  test_callback_set(test, test_move);
  // end sort marker1 }

  return true;
}
