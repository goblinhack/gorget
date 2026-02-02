//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_dice_rolls.hpp"
#include "my_gl.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_tp_class.hpp"
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
    "floor1", // Update FLOOR_VARIANTS
    "floor2", // Update FLOOR_VARIANTS
    "floor3", // Update FLOOR_VARIANTS
    "floor4", // Update FLOOR_VARIANTS
    "floor5", // Update FLOOR_VARIANTS
    "floor6", // Update FLOOR_VARIANTS
    "floor7", // Update FLOOR_VARIANTS
    "floor8", // Update FLOOR_VARIANTS
    "floor9", // Update FLOOR_VARIANTS
    "floor10", // Update FLOOR_VARIANTS
    "door_secret1", // Update WALL_VARIANTS
    "door_secret2", // Update WALL_VARIANTS
    "door_secret3", // Update WALL_VARIANTS
    "door_secret4", // Update WALL_VARIANTS
    "door_secret5", // Update WALL_VARIANTS
    "door_secret6", // Update WALL_VARIANTS
    "door_secret7", // Update WALL_VARIANTS
    "door_secret8", // Update WALL_VARIANTS
    "door_secret9", // Update WALL_VARIANTS
    "door_secret10", // Update WALL_VARIANTS
    "door_secret11", // Update WALL_VARIANTS
    "door_secret12", // Update WALL_VARIANTS
    "wall1", // Update WALL_VARIANTS
    "wall2", // Update WALL_VARIANTS
    "wall3", // Update WALL_VARIANTS
    "wall4", // Update WALL_VARIANTS
    "wall5", // Update WALL_VARIANTS
    "wall6", // Update WALL_VARIANTS
    "wall7", // Update WALL_VARIANTS
    "wall8", // Update WALL_VARIANTS
    "wall9", // Update WALL_VARIANTS
    "wall10", // Update WALL_VARIANTS
    "wall11", // Update WALL_VARIANTS
    "wall12", // Update WALL_VARIANTS
    "rock1",
    "border",
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
    "door_locked",
    "door_unlocked",
    "entrance",
    "exit",
    "explosion",
    "fire",
    "fireball",
    "foliage",
    "ghost_mob",
    "ghost",
    "grass",
    "key",
    "kobalos_mob",
    "kobalos",
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
    "slime",
    "smoke",
    "steam",
    "teleport",
    "trap",
    "water",
  /* end shell marker1 */
};
/* clang-format on */

using TpVec = std::vector< class Tp * >;
TpVec tp_vec;

// begin sort marker3 {
static TpVec tp_flag_vec[ THING_FLAG_ENUM_MAX ];
static TpVec tp_monst_vec[ MONST_GROUP_ENUM_MAX ];
// end sort marker3 }

static std::map< std::string, class Tp * > tp_name_map;

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

  CROAK("tp_find_mand: thing template %s not found", val.c_str());
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
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT(); // expensive

  if ((int) id - 1 >= (int) tp_vec.size()) {
    CROAK("tp_find: thing template %" PRIX16 " bad id, beyond size of tp_vec", id);
    return nullptr;
  }
#endif

  auto result = tp_vec[ id - 1 ];
#ifdef _DEBUG_BUILD_
  if (! result) {
    CROAK("tp_find: thing template %" PRIX16 " not found", id);
    return nullptr;
  }
#endif

  return result;
}

TpId tp_id_get(Tpp tp)
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT(); // expensive
#endif

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

  tp_vec.clear();
  tp_name_map.clear();

  for (auto c = 0; c < MONST_GROUP_ENUM_MAX; c++) {
    tp_monst_vec[ c ].clear();
  }

  for (auto f = 0; f < THING_FLAG_ENUM_MAX; f++) {
    tp_flag_vec[ f ].clear();
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

  tp_vec.push_back(tp);
  tp->id = tp_vec.size();

  //
  // Finalizing is done in tp_fixup
  //

  return tp;
}

static void tp_fixup(void)
{
  TRACE_NO_INDENT();

  for (auto &tp : tp_vec) {
    //
    // Populate the flag map for quick lookup of things that share a flag
    //
    for (auto f = 0; f < THING_FLAG_ENUM_MAX; f++) {
      if (tp->flag[ f ]) {
        tp_flag_vec[ f ].push_back(tp);
      }

      bool heat_exchange_set {};
      if (tp_is_stone(tp) || tp_is_lava(tp)) {
        tp_temperature_thermal_conductivity_set(tp, THERMAL_CONDUCTIVITY_STONE);
        tp_temperature_heat_capacity_set(tp, HEAT_CAPACITY_STONE);
        heat_exchange_set = true;
      }
      if (tp_is_wall(tp)) {
        tp_temperature_thermal_conductivity_set(tp, THERMAL_CONDUCTIVITY_WALL);
        tp_temperature_heat_capacity_set(tp, HEAT_CAPACITY_WALL);
        heat_exchange_set = true;
      }
      if (tp_is_glass(tp)) {
        tp_temperature_thermal_conductivity_set(tp, THERMAL_CONDUCTIVITY_GLASS);
        tp_temperature_heat_capacity_set(tp, HEAT_CAPACITY_GLASS);
        heat_exchange_set = true;
      }
      if (tp_is_gold(tp)) {
        tp_temperature_thermal_conductivity_set(tp, THERMAL_CONDUCTIVITY_GOLD);
        tp_temperature_heat_capacity_set(tp, HEAT_CAPACITY_GOLD);
        heat_exchange_set = true;
      }
      if (tp_is_gold(tp)) {
        tp_temperature_thermal_conductivity_set(tp, THERMAL_CONDUCTIVITY_GOLD);
        tp_temperature_heat_capacity_set(tp, HEAT_CAPACITY_GOLD);
        heat_exchange_set = true;
      }
      if (tp_is_metal(tp)) {
        tp_temperature_thermal_conductivity_set(tp, THERMAL_CONDUCTIVITY_STEEL);
        tp_temperature_heat_capacity_set(tp, HEAT_CAPACITY_STEEL);
        heat_exchange_set = true;
      }
      if (tp_is_water(tp) || tp_is_deep_water(tp)) {
        tp_temperature_thermal_conductivity_set(tp, THERMAL_CONDUCTIVITY_WATER);
        tp_temperature_heat_capacity_set(tp, HEAT_CAPACITY_WATER);
        heat_exchange_set = true;
      }
      if (tp_is_gaseous(tp)) {
        tp_temperature_thermal_conductivity_set(tp, THERMAL_CONDUCTIVITY_GAS);
        tp_temperature_heat_capacity_set(tp, HEAT_CAPACITY_GAS);
        heat_exchange_set = true;
      }
      if (tp_is_wood(tp) || tp_is_plant(tp)) {
        tp_temperature_thermal_conductivity_set(tp, THERMAL_CONDUCTIVITY_HIGH);
        tp_temperature_heat_capacity_set(tp, HEAT_CAPACITY_WOOD);
        heat_exchange_set = true;
      }
      if (tp_is_flesh(tp)) {
        tp_temperature_thermal_conductivity_set(tp, THERMAL_CONDUCTIVITY_HIGH);
        tp_temperature_heat_capacity_set(tp, HEAT_CAPACITY_FLESH);
        heat_exchange_set = true;
      }
      if (tp_is_slime(tp)) {
        tp_temperature_thermal_conductivity_set(tp, THERMAL_CONDUCTIVITY_GEL);
        tp_temperature_heat_capacity_set(tp, HEAT_CAPACITY_GEL);
        heat_exchange_set = true;
      }
      if (tp_is_physics_temperature(tp)) {
        if (! heat_exchange_set) {
          TP_ERR(tp, "tp has heat physics set but no conductivity set");
        }
      }

      if (tp_is_collision_circle_small(tp) || // newline
          tp_is_collision_circle_large(tp) || // newline
          tp_is_collision_square(tp)) {
        tp_flag_set(tp, is_collision_detection_enabled);
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
    TP_ERR(tp, "class %d has no tiles", val);
    return nullptr;
  }

  //
  // Get the first anim tile.
  //
  return tp->tiles[ val ][ 0 ];
}

static Tpp tp_get_with_no_rarity_filter(TpVec &m)
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

  if (unlikely(! tp_monst_vec[ c ].size())) {
    ERR("tp_random_monst: no rating %d monsters found", c);
    return nullptr;
  }

  return tp_get_with_no_rarity_filter(tp_monst_vec[ c ]);
}

Tpp tp_random(ThingFlag f)
{
  TRACE_NO_INDENT();

  if (unlikely(! tp_flag_vec[ f ].size())) {
    ERR("tp_random: no tp found for ThingFlag %d/%s", f, ThingFlag_to_c_str(f));
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_flag_vec[ f ]);
}

Tpp tp_variant(ThingFlag f, int variant)
{
  TRACE_NO_INDENT();

  for (auto i = 0; i < (int) tp_flag_vec[ f ].size(); i++) {
    auto tp = tp_flag_vec[ f ][ i ];
    if (tp_variant_get(tp) == variant) {
      return tp;
    }
  }

  ERR("tp_variant: failed to find %d/%s variant %d", f, ThingFlag_to_c_str(f), variant);
  return nullptr;
}

Tpp tp_first(ThingFlag f)
{
  TRACE_NO_INDENT();

  if (unlikely(! tp_flag_vec[ f ].size())) {
    ERR("tp_first: no tp found for ThingFlag %d/%s", f, ThingFlag_to_c_str(f));
    return nullptr;
  }
  return tp_flag_vec[ f ][ 0 ];
}

void tp_damage_set(Tpp tp, ThingEventType ev, const std::string &val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }

  if (ev >= THING_EVENT_ENUM_MAX) {
    TP_ERR(tp, "bad value in tp for %s, %d", __FUNCTION__, ev);
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
    ERR("No thing template pointer set");
    return 0;
  }

  if (val >= THING_EVENT_ENUM_MAX) {
    TP_ERR(tp, "bad value in tp for %s, %d", __FUNCTION__, val);
    return 0;
  }

  return tp->damage[ val ].roll();
}

void tp_chance_set(Tpp tp, ThingChanceType ev, const std::string &val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }

  if (ev >= THING_CHANCE_ENUM_MAX) {
    TP_ERR(tp, "bad value in tp for %s, %d", __FUNCTION__, ev);
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
    ERR("No thing template pointer set");
    return 0;
  }

  if (val >= THING_CHANCE_ENUM_MAX) {
    TP_ERR(tp, "bad value in tp for %s, %d", __FUNCTION__, val);
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
    ERR("No thing template pointer set");
    return false;
  }

  if (val >= THING_CHANCE_ENUM_MAX) {
    TP_ERR(tp, "bad value in tp for %s, %d", __FUNCTION__, val);
    return false;
  }

  auto roll = tp->chance[ val ].roll();
  if (! roll) {
    return false;
  }

  return roll == tp->chance[ val ].max_roll();
}

//
// Roll for chance of success
//
bool tp_chance_fail(Tpp tp, ThingChanceType val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return false;
  }

  if (val >= THING_CHANCE_ENUM_MAX) {
    TP_ERR(tp, "bad value in tp for %s, %d", __FUNCTION__, val);
    return false;
  }

  return tp->chance[ val ].roll() == 1;
}

Tilep tp_tiles_get(Tpp tp, ThingAnim val, int index)
{
  TRACE_NO_INDENT();

  if (! tp) {
    ERR("No thing template pointer set");
    return nullptr;
  }

  if (index >= (int) tp->tiles[ val ].size()) {
    TP_ERR(tp, "tp_tiles_get: tile overflow tp %s class %s/%d index %d", tp->name.c_str(),
           ThingAnim_to_string(val).c_str(), val, index);
  }

  return tp->tiles[ val ][ index ];
}

void tp_tiles_push_back(Tpp tp, ThingAnim val, Tilep tile)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }

  if (val >= THING_ANIM_ENUM_MAX) {
    TP_ERR(tp, "bad value in tp for %s, %d", __FUNCTION__, val);
    return;
  }

  tp->tiles[ val ].push_back(tile);
}

int tp_tiles_size(Tpp tp, ThingAnim val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return (int) tp->tiles[ val ].size();
}

std::string tp_name(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return "<noname>";
  }
  return tp->name.c_str();
}

void tp_short_name_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->short_name = std::string(val);
}

std::string tp_short_name(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
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
    ERR("No thing template pointer set");
    return;
  }
  tp->long_name = std::string(val);
}

std::string tp_long_name(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
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
    ERR("No thing template pointer set");
    return;
  }
  tp->apostrophize_name = std::string(val);
}

std::string tp_apostrophize_name(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
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
    ERR("No thing template pointer set");
    return;
  }
  tp->pluralize_name = std::string(val);
}

std::string tp_pluralize_name(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
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
    ERR("No thing template pointer set");
    return;
  }
  tp->real_name = std::string(val);
}

std::string tp_real_name(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
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
    ERR("No thing template pointer set");
    return;
  }
  tp->light_color = color_find(val.c_str());
}

void tp_light_color_apply(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  glcolor(tp->light_color);
}

color tp_light_color(Tpp tp)
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return WHITE;
  }
#endif
  return tp->light_color;
}

int tp_flag(Tpp tp, ThingFlag f)
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT(); // expensive
#endif

  if (! tp) {
    ERR("No thing template pointer set");
    return false;
  }
  return tp->flag[ f ];
}

void tp_flag_set(Tpp tp, ThingFlag f, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->flag[ f ] = val;
}

void tp_z_depth_set(Tpp tp, MapZDepth val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->z_depth = val;
}
uint8_t tp_z_depth_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->z_depth;
}

void tp_speed_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->speed = val;
}

int tp_speed_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->speed;
}

void tp_weight_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->weight = val;
}

int tp_weight_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->weight;
}

void tp_monst_group_add(Tpp tp, ThingMonstGroup val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }

  if ((int) val >= (int) MONST_GROUP_ENUM_MAX) {
    TP_ERR(tp, "bad value in tp for %s, %d", __FUNCTION__, val);
    return;
  }

  if (tp->is_monst_group[ val ]) {
    return;
  }

  tp->is_monst_group[ val ] = true;

  //
  // Keep track of all things in each group so we can select random monsters from them
  //
  tp_monst_vec[ val ].push_back(tp);

  //
  // Handy aliases
  //
  switch (val) {
    case MONST_GROUP_MOB :
      //
      // Used for monsters that are only generated by mobs
      //
      tp_flag_set(tp, is_monst_group_mob);
      break;
    case MONST_GROUP_EASY : tp_flag_set(tp, is_monst_group_easy); break;
    case MONST_GROUP_HARD : tp_flag_set(tp, is_monst_group_hard); break;
    default :               TP_ERR(tp, "bad value in tp for %s, %d", __FUNCTION__, val); return;
  }
}

void tp_is_immunity_add(Tpp tp, ThingEventType val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }

  if ((int) val >= (int) THING_EVENT_ENUM_MAX) {
    TP_ERR(tp, "bad value in tp for %s, %d", __FUNCTION__, val);
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
    ERR("No thing template pointer set");
    return false;
  }

  if ((int) val >= (int) THING_EVENT_ENUM_MAX) {
    TP_ERR(tp, "bad value in tp for %s, %d", __FUNCTION__, val);
    return false;
  }

  return tp->is_immune[ val ];
}

void tp_health_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->health_initial = Dice(std::string(val));
}

int tp_health_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->health_initial.roll();
}

int tp_health_max_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->health_initial.max_roll();
}

void tp_temperature_initial_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->temperature_initial = val;
}

int tp_temperature_initial_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->temperature_initial;
}

void tp_temperature_burns_at_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->temperature_burns_at = val;
}

int tp_temperature_burns_at_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->temperature_burns_at;
}

void tp_temperature_melts_at_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->temperature_melts_at = val;
}

int tp_temperature_melts_at_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->temperature_melts_at;
}

void tp_temperature_damage_at_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->temperature_damage_at = val;
}

int tp_temperature_damage_at_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->temperature_damage_at;
}

void tp_value1_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value1 = val;
}

int tp_value1_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value1;
}

void tp_value2_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value2 = val;
}

int tp_value2_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value2;
}

void tp_value3_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value3 = val;
}

int tp_value3_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value3;
}

void tp_value4_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value4 = val;
}

int tp_value4_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value4;
}

void tp_value5_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value5 = val;
}

int tp_value5_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value5;
}

void tp_value6_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value6 = val;
}

int tp_value6_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value6;
}

void tp_value7_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value7 = val;
}

int tp_value7_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value7;
}

void tp_value8_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value8 = val;
}

int tp_value8_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value8;
}

void tp_value9_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value9 = val;
}

int tp_value9_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value9;
}

void tp_value10_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value10 = val;
}

int tp_value10_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value10;
}

void tp_value11_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value11 = val;
}

int tp_value11_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value11;
}

void tp_value12_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value12 = val;
}

int tp_value12_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value12;
}

void tp_value13_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value13 = val;
}

int tp_value13_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value13;
}

void tp_value14_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value14 = val;
}

int tp_value14_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value14;
}

void tp_value15_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value15 = val;
}

int tp_value15_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value15;
}

void tp_value16_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value16 = val;
}

int tp_value16_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value16;
}

void tp_value17_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value17 = val;
}

int tp_value17_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value17;
}

void tp_value18_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value18 = val;
}

int tp_value18_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value18;
}

void tp_value19_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value19 = val;
}

int tp_value19_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value19;
}

void tp_value20_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value20 = val;
}

int tp_value20_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value20;
}

void tp_value21_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value21 = val;
}

int tp_value21_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value21;
}

void tp_value22_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->value22 = val;
}

int tp_value22_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->value22;
}

void tp_can_see_distance_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->can_see_distance = val;
}

int tp_can_see_distance_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->can_see_distance;
}

void tp_temperature_thermal_conductivity_set(Tpp tp, float val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->temperature_thermal_conductivity = val;
}

float tp_temperature_thermal_conductivity_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->temperature_thermal_conductivity;
}

void tp_temperature_heat_capacity_set(Tpp tp, float val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->temperature_heat_capacity = val;
}

float tp_temperature_heat_capacity_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->temperature_heat_capacity;
}

void tp_variant_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->variant = val;
}

int tp_variant_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->variant;
}

void tp_priority_set(Tpp tp, ThingPriorityType val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->priority = val;
}

ThingPriorityType tp_priority_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return THING_PRIORITY_LOW;
  }
  return tp->priority;
}

void tp_vision_distance_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->vision_distance = val;
}

int tp_vision_distance_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->vision_distance;
}
void tp_jump_distance_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->jump_distance = val;
}

int tp_jump_distance_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->jump_distance;
}

void tp_lifespan_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return;
  }
  tp->lifespan = Dice(std::string(val));
}

int tp_lifespan_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->lifespan.roll();
}

int tp_lifespan_max_get(Tpp tp)
{
  TRACE_NO_INDENT();
  if (! tp) {
    ERR("No thing template pointer set");
    return 0;
  }
  return tp->lifespan.max_roll();
}

float tp_collision_radius(Tpp t)
{
  TRACE_NO_INDENT();

  return tp_is_collision_circle_small(t) ? 0.25 : 0.5;
}
