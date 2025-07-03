//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_dice.hpp"
#include "my_dice_roll.hpp"
#include "my_enum.hpp"
#include "my_gl.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"
#include "my_tp_callbacks.hpp"
#include "my_tps.hpp"

#include <inttypes.h>
#include <map>
#include <vector>

ENUM_DEF_C(THING_FLAG_ENUM, ThingFlag)
ENUM_DEF_C(THING_ANIM_ENUM, ThingAnim)
ENUM_DEF_C(THING_DIR_ENUM, ThingDir)
ENUM_DEF_C(THING_DAMAGE_ENUM, ThingDamage)
ENUM_DEF_C(THING_RARITY_ENUM, ThingRarity)
ENUM_DEF_C(MONST_GROUP_ENUM, ThingMonstGroup)
ENUM_DEF_C(MAP_Z_DEPTH_ENUM, MapZDepth)
ENUM_DEF_C(MAP_Z_PRIO_ENUM, MapZPrio)

//
// Templates can be assigned dynamic IDs - however the levels are more reproducable it
// they have fixed numbers. This list helps to achieve that. It is optional for a template
// to be in this list
//
/* clang-format off */
std::initializer_list< std::string > tps = {
    // clang-format off
    "", // ID 0 means unused
    "wall1",
    "rock1",
    "player",
    /* begin shell marker1 */
    /* shell for i in $(find . -name "*.cpp" | xargs grep -h "tp_load(\"" | awk '{print $4}' | cut -d\" -f2) */
    /* shell do */
    /* shell echo "    \"$i\"", */
    /* shell done */
    "barrel",
    "explosion",
    "pillar",
    "brazier",
    "grass",
    "exit",
    "chasm",
    "floor",
    "secret_door",
    "foliage",
    "smoke",
    "door",
    "water",
    "bridge",
    "steam",
    "entrance",
    "lava",
    "fire",
    "key",
    "corridor",
    "dirt",
    "deep_water",
    "trap",
    "teleport",
    "cursor_path",
    "cursor_at",
    "goblin",
    "slime",
    "ghost",
    "level_curr",
    "level_visited",
    "level_across",
    "level_next",
    "level_not_visited",
    "level_final",
    "level_down",
    "chest",
    "potion",
    "ghost_mob",
    "goblin_mob",
    "player",
  /* end shell marker1 */
};
/* clang-format on */

class Tp
{
public:
  TpId id {};

  //
  // This allows us to draw floors, then objs and walls in order
  //
  uint8_t z_depth {};

  //
  // This is for objects at the same z depth
  //
  uint8_t z_prio {};

  //
  // See ThingFlag
  //
  uint8_t flag[ THING_FLAG_ENUM_MAX ] = {};

  //
  // Animation tiles
  //
  std::vector< class Tile * > tiles[ THING_ANIM_ENUM_MAX ];

  //
  // Which classes does this monst belong too
  //
  bool is_monst_group[ MONST_GROUP_ENUM_MAX ] {};

  //
  // Immunity to various damage types
  //
  bool is_immune[ THING_DAMAGE_ENUM_MAX ] {};

  //
  // Chance of this appearing on a level
  //
  int chance_d1000_appearing {};

  //
  // Speed compared to player
  //
  int speed {100};

  //
  // Weight in pounds
  //
  int weight {0};

  //
  // Starting health.
  //
  int health_initial {0};

  //
  // Temperature in celsius
  //
  int temperature_initial {0};

  //
  // When the thing catches fire
  //
  int temperature_burns_at {0};

  //
  // When the thing takes damage from heat
  //
  int temperature_damage_at {0};

  //
  // Internal name
  //
  std::string name;

  //
  // For mimics
  //
  std::string real_name;

  //
  // Short name for lists
  //
  std::string short_name;

  //
  // Longer name for attacks text
  //
  std::string long_name;

  //
  // Damage types, in dice
  //
  Dice damage[ THING_DAMAGE_ENUM_MAX ];

  //
  // For braziers and more
  //
  color light_color = {WHITE};

  //
  // Callbacks
  //
  tp_description_get_t description_get;

  Tp(void);
  ~Tp(void);
};

using Tpidmap = std::vector< class Tp * >;
Tpidmap tp_id_map;

// begin sort marker3 {
static Tpidmap tp_flag_map[ THING_FLAG_ENUM_MAX ];
static Tpidmap tp_monst_group[ MONST_GROUP_ENUM_MAX ];
// end sort marker3 }

static std::map< std::string, class Tp * > tp_name_map;

static uint8_t tp_init_done;

static void tp_fixup(void);

Tp::Tp(void) { newptr(MTYPE_TP, this, "Tp"); }

Tp::~Tp(void) { oldptr(MTYPE_TP, this); }

Tpp tp_find_mand(const char *name_in)
{
  TRACE_NO_INDENT();

  std::string name(name_in);
  auto        result = tp_name_map.find(name);

  if (unlikely(result != tp_name_map.end())) {
    return result->second;
  }

  DIE("tp_find_mand: thing template %s not found", name_in);
  return nullptr;
}

Tpp tp_find_opt(const char *name_in)
{
  TRACE_NO_INDENT();

  std::string name(name_in);
  auto        result = tp_name_map.find(name);

  if (unlikely(result != tp_name_map.end())) {
    return result->second;
  }

  return nullptr;
}

Tpp tp_find(TpId id)
{
  TRACE_NO_INDENT();

  if ((int) id - 1 >= (int) tp_id_map.size()) {
    DIE("tp_find: thing template %" PRIx16 " bad id, beyond size of tp_id_map", id);
    return nullptr;
  }

  auto result = tp_id_map[ id - 1 ];
  if (! result) {
    DIE("tp_find: thing template %" PRIx16 " not found", id);
    return nullptr;
  }

  return result;
}

TpId tp_id_get(Tpp tp)
{
  TRACE_NO_INDENT();

  return tp->id;
}

bool tp_init(void)
{
  TRACE_NO_INDENT();

  tp_init_done = true;

  templates_init();
  tp_fixup();

  return true;
}

void tp_fini(void)
{
  TRACE_NO_INDENT();

  if (! tp_init_done) {
    return;
  }
  tp_init_done = false;

  for (auto &tp : tp_name_map) {
    delete tp.second;
  }

  tp_id_map.clear();
  tp_name_map.clear();

  for (auto c = 0; c < MONST_GROUP_ENUM_MAX; c++) {
    tp_monst_group[ c ].clear();
  }

  for (auto f = 0; f < THING_FLAG_ENUM_MAX; f++) {
    tp_flag_map[ f ].clear();
  }
}

//
// Assign template IDs
//
static void tp_assign_id(const std::string &tp_name, int *id_out)
{
  TRACE_NO_INDENT();

  static std::map< std::string, int > tp_preferred_id;

  static const std::vector< std::string > tp_arr(tps);

  static int  id;
  static bool init;

  //
  // Assign static IDs
  //
  if (! init) {
    init = true;
    for (auto t : tp_arr) {
      tp_preferred_id[ t ] = id++;
    }
  }

  //
  // Previously known
  //
  if (tp_preferred_id.find(tp_name) == tp_preferred_id.end()) {
    tp_preferred_id[ tp_name ] = *id_out = ++id;
    ERR("tp_assign_id: thing template not found [%s] Please edit tp_ids.cpp and add it.", tp_name.c_str());
    return;
  }

  *id_out = tp_preferred_id[ tp_name ];
}

Tpp tp_load(const char *name_in)
{
  TRACE_NO_INDENT();

  std::string name(name_in);

  int id;
  tp_assign_id(name_in, &id);

  if (tp_find_opt(name_in)) {
    ERR("tp_load: thing template name [%s] already loaded", name_in);
  }

  auto tp  = new Tp();
  tp->name = name;

  auto result = tp_name_map.insert(std::make_pair(name, tp));
  if (! result.second) {
    ERR("tp_load: thing insert name [%s] failed", name_in);
  }

  tp_id_map.push_back(tp);
  tp->id = tp_id_map.size();

  //
  // Finalizing is done in tp_fixup
  //

  return tp;
}

static void tp_fixup(void)
{
  TRACE_NO_INDENT();

  for (auto &tp : tp_id_map) {
    //
    // Populate the flag map for quick lookup of things that share a flag
    //
    for (auto f = 0; f < THING_FLAG_ENUM_MAX; f++) {
      if (tp->flag[ f ]) {
        tp_flag_map[ f ].push_back(tp);
      }
    }
  }
}

Tilep tp_first_tile(Tpp tp, ThingAnim val)
{
  TRACE_NO_INDENT();

  if (! tp) {
    return nullptr;
  }

  auto tiles = &tp->tiles[ val ];

  if (! tiles || tiles->empty()) {
    ERR("tp %s class %d has no tiles", tp->name.c_str(), val);
    return nullptr;
  }

  //
  // Get the first anim tile.
  //
  return tp->tiles[ val ][ 0 ];
}

static Tpp tp_get_with_no_rarity_filter(Tpidmap &m)
{
  TRACE_NO_INDENT();

  int tries = 1000;
  while (tries-- > 0) {
    auto index = pcg_rand() % m.size();
    auto tp    = m[ index ];
    if (! tp) {
      break;
    }

    //
    // If this thing has a limited chance of appearing, roll the dice.
    //
    auto chance = tp->chance_d1000_appearing;
    if (chance) {
      auto roll = d1000();
      if (roll < chance) {
        return tp;
      }
    } else {
      return tp;
    }
  }

  //
  // Give in and return the first we find.
  //
  auto index = pcg_rand() % m.size();
  auto tp    = m[ index ];
  return tp;
}

Tpp tp_random_monst(int c)
{
  TRACE_NO_INDENT();

  if (c >= MONST_GROUP_ENUM_MAX) {
    ERR("tp_random_monst: monst bad rating %d", c);
    return nullptr;
  }

  if (unlikely(! tp_monst_group[ c ].size())) {
    ERR("tp_random_monst: no rating %d monsters found", c);
    return nullptr;
  }

  return tp_get_with_no_rarity_filter(tp_monst_group[ c ]);
}

Tpp tp_random(ThingFlag f)
{
  TRACE_NO_INDENT();

  if (unlikely(! tp_flag_map[ f ].size())) {
    ERR("tp_random: no tp found for ThingFlag %d/%s", f, ThingFlag_to_c_str(f));
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_flag_map[ f ]);
}

void tp_damage_set(Tpp tp, ThingDamage val, const char *str)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }

  if (val >= THING_DAMAGE_ENUM_MAX) {
    ERR("bad value in tp for %s, %d", __FUNCTION__, val);
    return;
  }

  tp->damage[ val ] = Dice(std::string(str));
}

//
// Roll for damage
//
int tp_damage(Tpp tp, ThingDamage val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }

  if (val >= THING_DAMAGE_ENUM_MAX) {
    ERR("bad value in tp for %s, %d", __FUNCTION__, val);
    return 0;
  }

  return tp->damage[ val ].roll();
}

Tilep tp_tiles_get(Tpp tp, ThingAnim val, int index)
{
  TRACE_NO_INDENT();

  if (index >= (int) tp->tiles[ val ].size()) {
    ERR("tp_tiles_get: tile overflow tp %s class %d index %d", tp->name.c_str(), val, index);
  }

  return tp->tiles[ val ][ index ];
}

void tp_tiles_push_back(Tpp tp, ThingAnim val, Tilep tile)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }

  if (val >= THING_ANIM_ENUM_MAX) {
    ERR("bad value in tp for %s, %d", __FUNCTION__, val);
    return;
  }

  tp->tiles[ val ].push_back(tile);
}

int tp_tiles_size(Tpp tp, ThingAnim val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return (int) tp->tiles[ val ].size();
}

const char *tp_name(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return "<noname>";
  }
  return tp->name.c_str();
}

void tp_short_name_set(Tpp tp, const char *name_in)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->short_name = std::string(name_in);
}

const char *tp_short_name(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return "<noshortname>";
  }
  if (tp->short_name.empty()) {
    return tp_name(tp);
  }
  return tp->short_name.c_str();
}

void tp_long_name_set(Tpp tp, const char *name_in)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->long_name = std::string(name_in);
}

const char *tp_long_name(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return "<nolongname>";
  }
  if (tp->long_name.empty()) {
    return tp_short_name(tp);
  }
  return tp->long_name.c_str();
}

void tp_real_name_set(Tpp tp, const char *name_in)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->real_name = std::string(name_in);
}

const char *tp_real_name(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return "<norealname>";
  }
  if (tp->real_name.empty()) {
    return tp_short_name(tp);
  }
  return tp->real_name.c_str();
}

void tp_light_color_set(Tpp tp, const char *name_in)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->light_color = color_find(name_in);
}

void tp_light_color_apply(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  glcolor(tp->light_color);
}

bool tp_flag(Tpp tp, ThingFlag f)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return false;
  }
  return tp->flag[ f ];
}

void tp_flag_set(Tpp tp, ThingFlag f, bool val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->flag[ f ] = val;
}

void tp_z_depth_set(Tpp tp, uint8_t val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->z_depth = val;
};
uint8_t tp_z_depth_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->z_depth;
};

void tp_z_prio_set(Tpp tp, uint8_t val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->z_prio = val;
};

uint8_t tp_z_prio_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->z_prio;
};

void tp_speed_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->speed = val;
};

int tp_speed_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->speed;
};

void tp_weight_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->weight = val;
};

int tp_weight_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->weight;
};

void tp_monst_group_add(Tpp tp, ThingMonstGroup val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }

  if ((int) val >= (int) MONST_GROUP_ENUM_MAX) {
    ERR("bad value in tp for %s, %d", __FUNCTION__, val);
    return;
  }

  if (tp->is_monst_group[ val ]) {
    return;
  }

  tp->is_monst_group[ val ] = true;

  //
  // Keep track of all things in each group so we can select random monsters from them
  //
  tp_monst_group[ val ].push_back(tp);

  //
  // Handy aliases
  //
  switch (val) {
    case MONST_GROUP_0 :
      //
      // Used for monsters that are only generated by mobs
      //
      tp_flag_set(tp, is_monst_group_0);
      break;
    case MONST_GROUP_1 : tp_flag_set(tp, is_monst_group_1); break;
    case MONST_GROUP_2 : tp_flag_set(tp, is_monst_group_2); break;
    default : ERR("bad value in tp for %s, %d", __FUNCTION__, val); return;
  }
}

void tp_is_immunity_add(Tpp tp, ThingDamage val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }

  if ((int) val >= (int) THING_DAMAGE_ENUM_MAX) {
    ERR("bad value in tp for %s, %d", __FUNCTION__, val);
    return;
  }

  if (tp->is_immune[ val ]) {
    return;
  }

  tp->is_immune[ val ] = true;
}

bool tp_is_immune_to(Tpp tp, ThingDamage val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return false;
  }

  if ((int) val >= (int) THING_DAMAGE_ENUM_MAX) {
    ERR("bad value in tp for %s, %d", __FUNCTION__, val);
    return false;
  }

  return tp->is_immune[ val ];
};

void tp_health_initial_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->health_initial = val;
};

int tp_health_initial_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->health_initial;
};

void tp_temperature_initial_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->temperature_initial = val;
  tp_flag_set(tp, is_able_to_change_temperature);
};

int tp_temperature_initial_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->temperature_initial;
};

void tp_temperature_burns_at_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->temperature_burns_at = val;
};

int tp_temperature_burns_at_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->temperature_burns_at;
};

void tp_temperature_damage_at_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->temperature_damage_at = val;
};

int tp_temperature_damage_at_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->temperature_damage_at;
};

//
// tp description callbacks
//
void tp_description_set(Tpp tp, tp_description_get_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->description_get = callback;
}

std::string tp_description_get(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp owner, spoint at)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return "<nodescription>";
  }
  if (! tp->description_get) {
    return "";
  }
  return tp->description_get(g, v, l, me, owner, at);
}
