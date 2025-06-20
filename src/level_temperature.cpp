//
// Copyright goblinhack@gmail.com
//

#include "my_minimal.hpp"

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_tp.hpp"

#include <set>

void level_tick_temperature(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  int x, y;

  FOR_ALL_MAP_POINTS(g, v, l, x, y)
  {
    std::vector< Thingp > things;

    //
    // Collect all things at this point into a vector
    //
    point p(x, y);
    FOR_ALL_THINGS_AT(g, v, l, t, p)
    {
      if (thing_is_able_to_change_temperature(t)) {
        things.push_back(t);
      }
    }

    //
    // Make unique pairs
    //
    std::set< std::pair< Thingp, Thingp > > pairs;

    auto sz = (int) things.size();
    for (auto i = 0; i < sz; i++) {
      for (auto j = 0; j < sz; j++) {
        auto Ti = things[ i ];
        auto Tj = things[ j ];
        if (Ti == Tj) {
          continue;
        }

        if ((void *) Ti > (void *) Tj) {
          std::swap(Ti, Tj);
        }

        pairs.insert(std::make_pair(Ti, Tj));
      }
    }

    for (auto pair : pairs) {
      auto  a  = pair.first;
      auto  b  = pair.second;
      float Ta = thing_temperature(a);
      float Wa = thing_weight(a);
      float Tb = thing_temperature(b);
      float Wb = thing_weight(b);
      int   Na = std::round(Ta + ((Tb - Ta) / (Wa + Wb)) * Wb);
      int   Nb = std::round(Tb + ((Ta - Tb) / (Wa + Wb)) * Wa);

      THING_CON(a, "a temp %f -> %d", Ta, Na);
      THING_CON(b, "b temp %f -> %d", Tb, Nb);
      CON("-");

      thing_temperature_handle(g, v, l, b, a, Na);
      thing_temperature_handle(g, v, l, a, b, Nb);
    }
  }
}
