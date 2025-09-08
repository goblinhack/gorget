//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_dice.hpp"
#include "my_dice_roll.hpp"
#include "my_gl.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_tp_callbacks.hpp"
#include "my_tps.hpp"

#include <map>
#include <vector>

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
    /* shell for i in $(find . -name "*.cpp" | xargs grep -h "tp_load(\"" | sort | awk '{print $4}' | cut -d\" -f2) */
    /* shell do */
    /* shell echo "    \"$i\"", */
    /* shell done */
    "barrel",
    "brazier",
    "bridge",
    "chasm",
    "chest",
    "corridor",
    "cursor_at",
    "cursor_path",
    "deep_water",
    "dirt",
    "door",
    "entrance",
    "exit",
    "explosion",
    "fire",
    "floor",
    "foliage",
    "ghost_mob",
    "ghost",
    "goblin_mob",
    "goblin",
    "grass",
    "key",
    "lava",
    "level_across",
    "level_curr",
    "level_down",
    "level_final",
    "level_next",
    "level_not_visited",
    "level_visited",
    "pillar",
    "player",
    "potion",
    "secret_door",
    "slime",
    "smoke",
    "steam",
    "teleport",
    "trap",
    "water",
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
  uint8_t z_layer {};

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
  bool is_immune[ THING_EVENT_ENUM_MAX ] {};

  //
  // Chance of this appearing on a level
  //
  int chance_d1000_appearing {};

  //
  // Speed compared to player
  //
  int speed {100};

  //
  // Weight in grams
  //
  int weight {0};

  //
  // Starting health.
  //
  Dice health_initial;

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

  int value1 {0};
  int value2 {0};
  int value3 {0};
  int value4 {0};
  int value5 {0};
  int value6 {0};
  int value7 {0};
  int value8 {0};
  int value9 {0};
  int value10 {0};
  int value11 {0};
  int value12 {0};
  int value13 {0};
  int value14 {0};
  int value15 {0};
  int value16 {0};
  int value17 {0};
  int value18 {0};
  int value19 {0};
  int value20 {0};
  int value21 {0};
  int value22 {0};
  int value23 {0};
  int value24 {0};
  int value25 {0};
  int value26 {0};
  int value27 {0};
  int value28 {0};
  int jump_distance {0};

  //
  // Lifespan in ticks. -1 is forever.
  //
  Dice lifespan;

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
  // monster's
  //
  std::string apostrophize_name;

  //
  // monsters
  //
  std::string pluralize_name;

  //
  // Damage types, in dice
  //
  Dice damage[ THING_EVENT_ENUM_MAX ];

  //
  // Chance types, in dice
  //
  Dice chance[ THING_EVENT_ENUM_MAX ];

  //
  // For braziers and more
  //
  color light_color = {WHITE};

  //
  // Callbacks
  //
  tp_description_get_t description_get = {};
  tp_on_spawn_t        on_spawn        = {};
  tp_on_open_t         on_open         = {};
  tp_on_closed_t       on_closed       = {};
  tp_on_tick_idle_t    tick_idle       = {};
  tp_on_tick_begin_t   tick_begin      = {};
  tp_on_tick_end_t     tick_end        = {};
  tp_on_death_t        on_death        = {};
  tp_on_moved_t        on_moved        = {};
  tp_on_teleported_t   on_teleported   = {};
  tp_on_shoved_t       on_shoved       = {};
  tp_on_jump_end_t     on_jump_end     = {};
  tp_on_jump_begin_t   on_jump_begin   = {};
  tp_on_fall_begin_t   on_fall_begin   = {};
  tp_on_fall_end_t     on_fall_end     = {};

  Tp(void);
  ~Tp(void);
};

using Tpidmap = std::vector< class Tp * >;
Tpidmap tp_id_map;

// begin sort marker3 {
static Tpidmap tp_flag_map[ THING_FLAG_ENUM_MAX ];
static Tpidmap tp_monst_group[ MONST_GROUP_ENUM_MAX ];
// end sort marker3 }

static std::unordered_map< std::string, class Tp * > tp_name_map;

static uint8_t tp_init_done;

static void tp_fixup(void);

Tp::Tp(void) { newptr(MTYPE_TP, this, "Tp"); }

Tp::~Tp(void) { oldptr(MTYPE_TP, this); }

Tpp tp_find_mand(const std::string &val)
{
  TRACE_NO_INDENT();

  std::string name(val);
  auto        result = tp_name_map.find(name);

  if (unlikely(result != tp_name_map.end())) {
    return result->second;
  }

  DIE("tp_find_mand: thing template %s not found", val.c_str());
  return nullptr;
}

Tpp tp_find_opt(const std::string &val)
{
  TRACE_NO_INDENT();

  std::string name(val);
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

  static std::unordered_map< std::string, int > tp_preferred_id;

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
    ERR("tp_assign_id: thing template not found [%s] Please edit tp.cpp and add it.", tp_name.c_str());
    return;
  }

  *id_out = tp_preferred_id[ tp_name ];
}

Tpp tp_load(const std::string &val)
{
  TRACE_NO_INDENT();

  std::string name(val);

  int id;
  tp_assign_id(val, &id);

  if (tp_find_opt(val)) {
    ERR("tp_load: thing template name [%s] already loaded", val.c_str());
  }

  auto tp  = new Tp();
  tp->name = name;

  auto result = tp_name_map.insert(std::make_pair(name, tp));
  if (! result.second) {
    ERR("tp_load: thing insert name [%s] failed", val.c_str());
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

void tp_damage_set(Tpp tp, ThingEventType ev, const std::string &val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }

  if (ev >= THING_EVENT_ENUM_MAX) {
    ERR("bad value in tp for %s, %d", __FUNCTION__, ev);
    return;
  }

  tp->damage[ ev ] = Dice(std::string(val));
}

//
// Roll for damage
//
int tp_damage(Tpp tp, ThingEventType val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }

  if (val >= THING_EVENT_ENUM_MAX) {
    ERR("bad value in tp for %s, %d", __FUNCTION__, val);
    return 0;
  }

  return tp->damage[ val ].roll();
}

void tp_chance_set(Tpp tp, ThingChanceType ev, const std::string &val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }

  if (ev >= THING_CHANCE_ENUM_MAX) {
    ERR("bad value in tp for %s, %d", __FUNCTION__, ev);
    return;
  }

  tp->chance[ ev ] = Dice(std::string(val));
}

//
// Roll for chance
//
int tp_chance(Tpp tp, ThingChanceType val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }

  if (val >= THING_CHANCE_ENUM_MAX) {
    ERR("bad value in tp for %s, %d", __FUNCTION__, val);
    return 0;
  }

  return tp->chance[ val ].roll();
}

//
// Roll for chance of success
//
bool tp_chance_success(Tpp tp, ThingChanceType val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return false;
  }

  if (val >= THING_CHANCE_ENUM_MAX) {
    ERR("bad value in tp for %s, %d", __FUNCTION__, val);
    return false;
  }

  return tp->chance[ val ].roll() == tp->chance[ val ].max_roll();
}

//
// Roll for chance of success
//
bool tp_chance_fail(Tpp tp, ThingChanceType val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return false;
  }

  if (val >= THING_CHANCE_ENUM_MAX) {
    ERR("bad value in tp for %s, %d", __FUNCTION__, val);
    return false;
  }

  return tp->chance[ val ].roll() == 1;
}

Tilep tp_tiles_get(Tpp tp, ThingAnim val, int index)
{
  TRACE_NO_INDENT();

  if (index >= (int) tp->tiles[ val ].size()) {
    ERR("tp_tiles_get: tile overflow tp %s class %s/%d index %d", tp->name.c_str(), ThingAnim_to_string(val).c_str(),
        val, index);
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

std::string tp_name(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return "<noname>";
  }
  return tp->name.c_str();
}

void tp_short_name_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->short_name = std::string(val);
}

std::string tp_short_name(Tpp tp)
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

void tp_long_name_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->long_name = std::string(val);
}

std::string tp_long_name(Tpp tp)
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

void tp_apostrophize_name_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->apostrophize_name = std::string(val);
}

std::string tp_apostrophize_name(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return "<noapostrophizename>";
  }
  if (tp->apostrophize_name.empty()) {
    return tp_long_name(tp);
  }
  return tp->apostrophize_name.c_str();
}

void tp_pluralize_name_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->pluralize_name = std::string(val);
}

std::string tp_pluralize_name(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return "<nopluralizename>";
  }
  if (tp->pluralize_name.empty()) {
    return tp_long_name(tp);
  }
  return tp->pluralize_name.c_str();
}

void tp_real_name_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->real_name = std::string(val);
}

std::string tp_real_name(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return "<norealname>";
  }
  if (tp->real_name.empty()) {
    return tp_long_name(tp);
  }
  return tp->real_name.c_str();
}

void tp_light_color_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->light_color = color_find(val.c_str());
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

void tp_z_depth_set(Tpp tp, MapZDepth val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->z_depth = val;
}
uint8_t tp_z_depth_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->z_depth;
}

void tp_speed_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->speed = val;
}

int tp_speed_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->speed;
}

void tp_weight_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->weight = val;
}

int tp_weight_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->weight;
}

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
    default :            ERR("bad value in tp for %s, %d", __FUNCTION__, val); return;
  }
}

void tp_is_immunity_add(Tpp tp, ThingEventType val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }

  if ((int) val >= (int) THING_EVENT_ENUM_MAX) {
    ERR("bad value in tp for %s, %d", __FUNCTION__, val);
    return;
  }

  if (tp->is_immune[ val ]) {
    return;
  }

  tp->is_immune[ val ] = true;
}

bool tp_is_immune_to(Tpp tp, ThingEventType val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return false;
  }

  if ((int) val >= (int) THING_EVENT_ENUM_MAX) {
    ERR("bad value in tp for %s, %d", __FUNCTION__, val);
    return false;
  }

  return tp->is_immune[ val ];
}

void tp_health_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->health_initial = Dice(std::string(val));
}

int tp_health_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->health_initial.roll();
}

int tp_health_max_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->health_initial.max_roll();
}

void tp_temperature_initial_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->temperature_initial = val;
}

int tp_temperature_initial_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->temperature_initial;
}

void tp_temperature_burns_at_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->temperature_burns_at = val;
}

int tp_temperature_burns_at_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->temperature_burns_at;
}

void tp_temperature_damage_at_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->temperature_damage_at = val;
}

int tp_temperature_damage_at_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->temperature_damage_at;
}

void tp_description_set(Tpp tp, tp_description_get_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->description_get = callback;
}

std::string tp_description_get(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return "<no description>";
  }
  if (! tp->description_get) {
    return "";
  }
  return tp->description_get(g, v, l, me);
}

void tp_on_tick_idle_set(Tpp tp, tp_on_tick_idle_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->tick_idle = callback;
}

void tp_on_tick_idle(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  if (! tp->tick_idle) {
    return;
  }
  return tp->tick_idle(g, v, l, me);
}

void tp_on_tick_begin_set(Tpp tp, tp_on_tick_begin_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->tick_begin = callback;
}

void tp_on_tick_begin(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  if (! tp->tick_begin) {
    return;
  }
  return tp->tick_begin(g, v, l, me);
}

void tp_on_tick_end_set(Tpp tp, tp_on_tick_end_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->tick_end = callback;
}

void tp_on_tick_end(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  if (! tp->tick_end) {
    return;
  }
  return tp->tick_end(g, v, l, me);
}

void tp_on_spawn_set(Tpp tp, tp_on_spawn_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->on_spawn = callback;
}

void tp_on_spawn(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  if (! tp->on_spawn) {
    return;
  }
  return tp->on_spawn(g, v, l, me);
}

void tp_on_open_set(Tpp tp, tp_on_open_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->on_open = callback;
}

void tp_on_open(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  if (! tp->on_open) {
    return;
  }
  return tp->on_open(g, v, l, me);
}

void tp_on_closed_set(Tpp tp, tp_on_closed_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->on_closed = callback;
}

void tp_on_closed(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  if (! tp->on_closed) {
    return;
  }
  return tp->on_closed(g, v, l, me);
}

void tp_on_death_set(Tpp tp, tp_on_death_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->on_death = callback;
}

void tp_on_death(Gamep g, Levelsp v, Levelp l, Thingp me, ThingEvent &e)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  if (! tp->on_death) {
    return;
  }
  return tp->on_death(g, v, l, me, e);
}

void tp_on_moved_set(Tpp tp, tp_on_moved_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->on_moved = callback;
}

void tp_on_moved(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  if (! tp->on_moved) {
    return;
  }
  return tp->on_moved(g, v, l, me);
}

void tp_on_teleported_set(Tpp tp, tp_on_teleported_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->on_teleported = callback;
}

void tp_on_teleported(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  if (! tp->on_teleported) {
    return;
  }
  return tp->on_teleported(g, v, l, me);
}

void tp_on_jump_begin_set(Tpp tp, tp_on_jump_begin_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->on_jump_begin = callback;
}

void tp_on_jump_begin(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  if (! tp->on_jump_begin) {
    return;
  }
  return tp->on_jump_begin(g, v, l, me);
}

void tp_on_jump_end_set(Tpp tp, tp_on_jump_end_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->on_jump_end = callback;
}

void tp_on_jump_end(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  if (! tp->on_jump_end) {
    return;
  }
  return tp->on_jump_end(g, v, l, me);
}

void tp_on_shoved_set(Tpp tp, tp_on_shoved_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->on_shoved = callback;
}

void tp_on_shoved(Gamep g, Levelsp v, Levelp l, Thingp me, Thingp shover)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  if (! tp->on_shoved) {
    return;
  }
  return tp->on_shoved(g, v, l, me, shover);
}

void tp_on_fall_begin_set(Tpp tp, tp_on_fall_begin_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->on_fall_begin = callback;
}

void tp_on_fall_begin(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  if (! tp->on_fall_begin) {
    return;
  }
  return tp->on_fall_begin(g, v, l, me);
}

void tp_on_fall_end_set(Tpp tp, tp_on_fall_end_t callback)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->on_fall_end = callback;
}

void tp_on_fall_end(Gamep g, Levelsp v, Levelp l, Thingp me)
{
  TRACE_NO_INDENT();
  auto tp = thing_tp(me);
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  if (! tp->on_fall_end) {
    return;
  }
  return tp->on_fall_end(g, v, l, me);
}

void tp_value1_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value1 = val;
}

int tp_value1_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value1;
}

void tp_value2_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value2 = val;
}

int tp_value2_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value2;
}
void tp_value3_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value3 = val;
}

int tp_value3_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value3;
}
void tp_value4_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value4 = val;
}

int tp_value4_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value4;
}
void tp_value5_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value5 = val;
}

int tp_value5_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value5;
}
void tp_value6_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value6 = val;
}

int tp_value6_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value6;
}
void tp_value7_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value7 = val;
}

int tp_value7_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value7;
}
void tp_value8_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value8 = val;
}

int tp_value8_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value8;
}
void tp_value9_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value9 = val;
}

int tp_value9_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value9;
}
void tp_value10_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value10 = val;
}

int tp_value10_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value10;
}
void tp_value11_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value11 = val;
}

int tp_value11_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value11;
}
void tp_value12_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value12 = val;
}

int tp_value12_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value12;
}
void tp_value13_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value13 = val;
}

int tp_value13_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value13;
}
void tp_value14_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value14 = val;
}

int tp_value14_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value14;
}
void tp_value15_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value15 = val;
}

int tp_value15_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value15;
}
void tp_value16_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value16 = val;
}

int tp_value16_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value16;
}
void tp_value17_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value17 = val;
}

int tp_value17_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value17;
}
void tp_value18_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value18 = val;
}

int tp_value18_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value18;
}
void tp_value19_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value19 = val;
}

int tp_value19_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value19;
}
void tp_value20_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value20 = val;
}

int tp_value20_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value20;
}
void tp_value21_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value21 = val;
}

int tp_value21_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value21;
}
void tp_value22_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value22 = val;
}

int tp_value22_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value22;
}
void tp_value23_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value23 = val;
}

int tp_value23_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value23;
}
void tp_value24_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value24 = val;
}

int tp_value24_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value24;
}
void tp_value25_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value25 = val;
}

int tp_value25_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value25;
}
void tp_value26_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value26 = val;
}

int tp_value26_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value26;
}
void tp_value27_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value27 = val;
}

int tp_value27_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value27;
}
void tp_value28_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->value28 = val;
}

int tp_value28_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->value28;
}
void tp_jump_distance_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->jump_distance = val;
}

int tp_jump_distance_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->jump_distance;
}

void tp_lifespan_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return;
  }
  tp->lifespan = Dice(std::string(val));
}

int tp_lifespan_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->lifespan.roll();
}

int tp_lifespan_max_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("no tp for %s", __FUNCTION__);
    return 0;
  }
  return tp->lifespan.max_roll();
}
