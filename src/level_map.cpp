//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_charmap.hpp"
#include "my_dice.hpp"
#include "my_game.hpp"
#include "my_game_defs.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

void level_map_set(Gamep g, Levelsp v, Levelp l, const char *in)
{
  TRACE_NO_INDENT();

  const auto row_len      = MAP_WIDTH;
  auto       expected_len = row_len * MAP_HEIGHT;

  if ((int) strlen(in) != expected_len) {
    DIE("bad map size, expected %d, got %d", (int) strlen(in), (int) expected_len);
  }

  auto tp_wall        = tp_random(is_wall);
  auto tp_rock        = tp_random(is_rock);
  auto tp_water       = tp_random(is_water);
  auto tp_lava        = tp_random(is_lava);
  auto tp_bridge      = tp_random(is_bridge);
  auto tp_chasm       = tp_random(is_chasm);
  auto tp_deep_water  = tp_random(is_deep_water);
  auto tp_brazier     = tp_random(is_brazier);
  auto tp_pillar      = tp_random(is_pillar);
  auto tp_barrel      = tp_random(is_barrel);
  auto tp_teleport    = tp_random(is_teleport);
  auto tp_treasure1   = tp_random(is_treasure1);
  auto tp_treasure2   = tp_random(is_treasure2);
  auto tp_key         = tp_random(is_key);
  auto tp_foliage     = tp_random(is_foliage);
  auto tp_corridor    = tp_random(is_corridor);
  auto tp_grass       = tp_random(is_grass);
  auto tp_door        = tp_find_mand("door");
  auto tp_secret_door = tp_find_mand("secret_door");
  auto tp_trap        = tp_find_mand("trap");
  auto tp_floor       = tp_find_mand("floor");
  auto tp_dirt        = tp_find_mand("dirt");
  auto tp_exit        = tp_find_mand("exit");
  auto tp_player      = tp_find_mand("player");
  auto tp_entrance    = tp_find_mand("entrance");

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      auto  offset = (row_len * y) + x;
      auto  c      = in[ offset ];
      Tpp   tp     = nullptr;
      point at(x, y);

      l->debug[ x ][ y ] = c;

      bool need_floor    = false;
      bool need_corridor = false;
      bool need_water    = false;
      bool need_dirt     = false;
      bool need_foliage  = false;

      switch (c) {
        case CHARMAP_FLOOR :
          need_floor = true;
          if (d100() < 5) {
            need_foliage = true;
          }
          break;
        case CHARMAP_DIRT :
          need_dirt = true;
          if (d100() < 50) {
            need_foliage = true;
          }
          break;
        case CHARMAP_CHASM : tp = tp_chasm; break;
        case CHARMAP_JOIN : need_corridor = true; break;
        case CHARMAP_CORRIDOR : tp = tp_corridor; break;
        case CHARMAP_BRIDGE : tp = tp_bridge; break;
        case CHARMAP_WALL :
          need_floor = true;
          tp         = tp_wall;
          break;
        case CHARMAP_TREASURE1 :
          need_floor = true;
          tp         = tp_treasure1;
          break;
        case CHARMAP_TREASURE2 :
          need_floor = true;
          tp         = tp_treasure2;
          break;
        case CHARMAP_TELEPORT :
          need_floor = true;
          tp         = tp_teleport;
          break;
        case CHARMAP_FOLIAGE :
          need_floor   = true;
          need_foliage = true;
          break;
        case CHARMAP_DEEP_WATER :
          need_dirt  = true;
          tp         = tp_deep_water;
          need_water = true;
          break;
        case CHARMAP_WATER :
          need_dirt  = true;
          need_water = true;
          if (d100() < 5) {
            need_foliage = true;
          }
          break;
        case CHARMAP_BARREL :
          need_floor = true;
          tp         = tp_barrel;
          break;
        case CHARMAP_PILLAR :
          need_floor = true;
          tp         = tp_pillar;
          break;
        case CHARMAP_TRAP :
          need_floor = true;
          tp         = tp_trap;
          break;
        case CHARMAP_LAVA :
          need_floor = true;
          tp         = tp_lava;
          break;
        case CHARMAP_BRAZIER :
          need_floor = true;
          tp         = tp_brazier;
          break;
        case CHARMAP_DOOR :
          need_floor = true;
          tp         = tp_door;
          break;
        case CHARMAP_SECRET_DOOR :
          need_floor = true;
          tp         = tp_secret_door;
          break;
        case CHARMAP_GRASS :
          need_floor = true;
          tp         = tp_grass;
          break;
        case CHARMAP_MONST1 :
          need_floor = true;
          tp         = tp_random(is_monst1);
          break;
        case CHARMAP_MONST2 :
          need_floor = true;
          tp         = tp_random(is_monst2);
          break;
        case CHARMAP_MOB1 :
          need_floor = true;
          tp         = tp_random(is_mob1);
          break;
        case CHARMAP_MOB2 :
          need_floor = true;
          tp         = tp_random(is_mob2);
          break;
        case CHARMAP_ENTRANCE :
          need_floor = true;
          if (l->level_num == 0) {
            tp = tp_player;
          } else {
            need_floor = true;
            tp         = tp_entrance;
          }
          l->entrance = at;
          break;
        case CHARMAP_EXIT :
          need_floor = true;
          tp         = tp_exit;
          l->exit    = at;
          break;
        case CHARMAP_KEY :
          need_floor = true;
          tp         = tp_key;
          break;
        case CHARMAP_EMPTY :
          need_dirt = true;
          tp        = tp_rock;
          break;
        default :
          if (! g_opt_do_level_gen) {
            //            DIE("unexpected map char '%c'", c);
          }
      }

      if (need_floor) {
        auto tp_add = tp_floor;
        auto t      = thing_init(g, v, l, tp_add, point(x, y));
        if (t) {
          thing_push(g, v, l, t);
        }
      }

      if (need_corridor) {
        auto tp_add = tp_corridor;
        auto t      = thing_init(g, v, l, tp_add, point(x, y));
        if (t) {
          thing_push(g, v, l, t);
        }
      }

      if (need_dirt) {
        auto tp_add = tp_dirt;
        auto t      = thing_init(g, v, l, tp_add, point(x, y));
        if (t) {
          thing_push(g, v, l, t);
        }
      }

      if (need_water) {
        auto t = thing_init(g, v, l, tp_water, point(x, y));
        if (t) {
          thing_push(g, v, l, t);
        }
      }

      if (need_foliage) {
        auto tp_add = tp_foliage;
        auto t      = thing_init(g, v, l, tp_add, point(x, y));
        if (t) {
          thing_push(g, v, l, t);
        }
      }

      if (tp) {
        auto t = thing_init(g, v, l, tp, point(x, y));
        if (t) {
          thing_push(g, v, l, t);
        }
      }

      if (0) {
        if (tp == tp_player) {
          auto t = thing_init(g, v, l, tp_teleport, point(x, y) + point(2, 0));
          if (t) {
            thing_push(g, v, l, t);
          }
        }
      }
    }
  }
}
