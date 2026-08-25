//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"
#include "my_tp.hpp"
#include "my_types.hpp"

[[nodiscard]] auto level_to_biome(Gamep g, Levelsp v, Levelp l) -> BiomeType
{
  TRACE();

  if (l->biome != 0U) {
    return l->biome;
  }

  switch (l->level_num) {
    case 0 :               return BIOME_DUNGEON;
    case 1 :               return BIOME_DUNGEON;
    case 2 :               return BIOME_DUNGEON;
    case 3 :               return BIOME_DUNGEON;
    case 4 :               return BIOME_DUNGEON;
    case 5 :               return BIOME_DUNGEON;
    case 6 :               return BIOME_DUNGEON;
    case 7 :               return BIOME_DUNGEON;
    case 8 :               return BIOME_DUNGEON;
    case 9 :               return BIOME_DUNGEON;
    case 10 :              return BIOME_DUNGEON;
    case 11 :              return BIOME_DUNGEON;
    case 12 :              return BIOME_DUNGEON;
    case 13 :              return BIOME_DUNGEON;
    case 14 :              return BIOME_DUNGEON;
    case 15 :              return BIOME_DUNGEON;
    case 16 :              return BIOME_DUNGEON;
    case 17 :              return BIOME_DUNGEON;
    case 18 :              return BIOME_DUNGEON;
    case 19 :              return BIOME_DUNGEON;
    case 20 :              return BIOME_BOGLAND;
    case 21 :              return BIOME_BOGLAND;
    case 22 :              return BIOME_BOGLAND;
    case 23 :              return BIOME_BOGLAND;
    case 24 :              return BIOME_BOGLAND;
    case 25 :              return BIOME_BOGLAND;
    case 26 :              return BIOME_BOGLAND;
    case 27 :              return BIOME_BOGLAND;
    case 28 :              return BIOME_BOGLAND;
    case 29 :              return BIOME_BOGLAND;
    case 30 :              return BIOME_BOGLAND;
    case 31 :              return BIOME_BOGLAND;
    case 32 :              return BIOME_BOGLAND;
    case 33 :              return BIOME_BOGLAND;
    case 34 :              return BIOME_BOGLAND;
    case 35 :              return BIOME_BOGLAND;
    case 36 :              return BIOME_BOGLAND;
    case 37 :              return BIOME_BOGLAND;
    case 38 :              return BIOME_BOGLAND;
    case 39 :              return BIOME_BOGLAND;
    case 40 :              return BIOME_NETHERVOID;
    case 41 :              return BIOME_NETHERVOID;
    case 42 :              return BIOME_NETHERVOID;
    case 43 :              return BIOME_NETHERVOID;
    case 44 :              return BIOME_NETHERVOID;
    case 45 :              return BIOME_NETHERVOID;
    case 46 :              return BIOME_NETHERVOID;
    case 47 :              return BIOME_NETHERVOID;
    case 48 :              return BIOME_NETHERVOID;
    case 49 :              return BIOME_NETHERVOID;
    case 50 :              return BIOME_NETHERVOID;
    case 51 :              return BIOME_NETHERVOID;
    case 52 :              return BIOME_NETHERVOID;
    case 53 :              return BIOME_NETHERVOID;
    case 54 :              return BIOME_NETHERVOID;
    case 55 :              return BIOME_NETHERVOID;
    case 56 :              return BIOME_NETHERVOID;
    case 57 :              return BIOME_NETHERVOID;
    case 58 :              return BIOME_NETHERVOID;
    case 59 :              return BIOME_NETHERVOID;
    case 60 :              return BIOME_GRAVEYARD;
    case 61 :              return BIOME_GRAVEYARD;
    case 62 :              return BIOME_GRAVEYARD;
    case 63 :              return BIOME_GRAVEYARD;
    case 64 :              return BIOME_GRAVEYARD;
    case 65 :              return BIOME_GRAVEYARD;
    case 66 :              return BIOME_GRAVEYARD;
    case 67 :              return BIOME_GRAVEYARD;
    case 68 :              return BIOME_GRAVEYARD;
    case 69 :              return BIOME_GRAVEYARD;
    case 70 :              return BIOME_GRAVEYARD;
    case 71 :              return BIOME_GRAVEYARD;
    case 72 :              return BIOME_GRAVEYARD;
    case 73 :              return BIOME_GRAVEYARD;
    case 74 :              return BIOME_GRAVEYARD;
    case 75 :              return BIOME_GRAVEYARD;
    case 76 :              return BIOME_GRAVEYARD;
    case 77 :              return BIOME_GRAVEYARD;
    case 78 :              return BIOME_GRAVEYARD;
    case 79 :              return BIOME_GRAVEYARD;
    case 80 :              return BIOME_UNDERHELL;
    case 81 :              return BIOME_UNDERHELL;
    case 82 :              return BIOME_UNDERHELL;
    case 83 :              return BIOME_UNDERHELL;
    case 84 :              return BIOME_UNDERHELL;
    case 85 :              return BIOME_UNDERHELL;
    case 86 :              return BIOME_UNDERHELL;
    case 87 :              return BIOME_UNDERHELL;
    case 88 :              return BIOME_UNDERHELL;
    case 89 :              return BIOME_UNDERHELL;
    case 90 :              return BIOME_UNDERHELL;
    case 91 :              return BIOME_UNDERHELL;
    case 92 :              return BIOME_UNDERHELL;
    case 93 :              return BIOME_UNDERHELL;
    case 94 :              return BIOME_UNDERHELL;
    case 95 :              return BIOME_UNDERHELL;
    case 96 :              return BIOME_UNDERHELL;
    case 97 :              return BIOME_UNDERHELL;
    case 98 :              return BIOME_UNDERHELL;
    case 99 :              return BIOME_UNDERHELL;
    case LEVEL_SELECT_ID : return BIOME_DUNGEON;
    default :              ERR("unexpected level number with no biome assigned: %d", l->level_num); return BIOME_DUNGEON;
  }
}
