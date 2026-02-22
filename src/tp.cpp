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
#include <utility>
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
    "glorp",
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
    "mantisman",
    "pillar",
    "player",
    "potion",
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

static bool tp_init_done;

static void tp_fixup();

Tp::Tp() { newptr(MTYPE_TP, this, "Tp"); }

Tp::~Tp() { oldptr(MTYPE_TP, this); }

auto tp_find_mand(const std::string &val) -> Tpp
{
  TRACE_NO_INDENT();

  const std::string &name(val);
  auto               result = tp_name_map.find(name);

  if (unlikely(result != tp_name_map.end())) {
    return result->second;
  }

  CROAK("tp_find_mand: thing template %s not found", val.c_str());
  return nullptr;
}

auto tp_find_opt(const std::string &val) -> Tpp
{
  TRACE_NO_INDENT();

  const std::string &name(val);
  auto               result = tp_name_map.find(name);

  if (unlikely(result != tp_name_map.end())) {
    return result->second;
  }

  return nullptr;
}

auto tp_find(TpId id) -> Tpp
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT(); // expensive

  if ((int) id - 1 >= (int) tp_vec.size()) {
    CROAK("tp_find: thing template %" PRIX16 " bad id, beyond size of tp_vec", id);
    return nullptr;
  }
#endif

  auto *result = tp_vec[ id - 1 ];
#ifdef _DEBUG_BUILD_
  if (! result) {
    CROAK("tp_find: thing template %" PRIX16 " not found", id);
    return nullptr;
  }
#endif

  return result;
}

auto tp_id_get(Tpp tp) -> TpId
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT(); // expensive
#endif

  return tp->id;
}

auto tp_init() -> bool
{
  TRACE_NO_INDENT();

  tp_init_done = true;

  templates_init();
  tp_fixup();

  return true;
}

void tp_fini()
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

  for (auto &c : tp_monst_vec) {
    c.clear();
  }

  for (auto &f : tp_flag_vec) {
    f.clear();
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
    for (const auto &t : tp_arr) {
      tp_preferred_id[ t ] = id++;
    }
  }

  //
  // Previously known
  //
  if (! tp_preferred_id.contains(tp_name)) {
    tp_preferred_id[ tp_name ] = *id_out = ++id;
    ERR("tp_assign_id: thing template not found [%s] Please edit tp.cpp and add it.", tp_name.c_str());
    return;
  }

  *id_out = tp_preferred_id[ tp_name ];
}

auto tp_load(const std::string &val) -> Tpp
{
  TRACE_NO_INDENT();

  std::string const& name(val);

  int id;
  tp_assign_id(val, &id);

  if (tp_find_opt(val) != nullptr) {
    ERR("tp_load: thing template name [%s] already loaded", val.c_str());
  }

  auto *tp = new Tp();
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

static void tp_fixup()
{
  TRACE_NO_INDENT();

  for (auto &tp : tp_vec) {
    //
    // Populate the flag map for quick lookup of things that share a flag
    //
    for (auto f = 0; f < THING_FLAG_ENUM_MAX; f++) {
      if (tp->flag[ f ] != 0) {
        tp_flag_vec[ f ].push_back(tp);
      }

      tp_temperature_init(tp);
      tp_collision_init(tp);
    }
  }
}

auto tp_first_tile(Tpp tp, ThingAnim val) -> Tilep
{
  TRACE_NO_INDENT();

  if (tp == nullptr) {
    return nullptr;
  }

  auto *tiles = &tp->tiles[ val ];

  if ((tiles == nullptr) || tiles->empty()) {
    TP_ERR(tp, "class %d has no tiles", val);
    return nullptr;
  }

  //
  // Get the first anim tile.
  //
  return tp->tiles[ val ][ 0 ];
}

static auto tp_get_with_no_rarity_filter(TpVec &m) -> Tpp
{
  TRACE_NO_INDENT();

  int tries = 1000;
  while (tries-- > 0) {
    auto  index = pcg_rand() % m.size();
    auto *tp    = m[ index ];
    if (tp == nullptr) {
      break;
    }

    //
    // If this thing has a limited chance of appearing, roll the dice.
    //
    auto chance = tp->chance_d1000_appearing;
    if (chance != 0) {
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
  auto  index = pcg_rand() % m.size();
  auto *tp    = m[ index ];
  return tp;
}

auto tp_random_monst(int c) -> Tpp
{
  TRACE_NO_INDENT();

  if (c >= MONST_GROUP_ENUM_MAX) {
    ERR("tp_random_monst: monst bad rating %d", c);
    return nullptr;
  }

  if (unlikely(tp_monst_vec[ c ].empty())) {
    ERR("tp_random_monst: no rating %d monsters found", c);
    return nullptr;
  }

  return tp_get_with_no_rarity_filter(tp_monst_vec[ c ]);
}

auto tp_random(ThingFlag f) -> Tpp
{
  TRACE_NO_INDENT();

  if (unlikely(tp_flag_vec[ f ].empty())) {
    ERR("tp_random: no tp found for ThingFlag %d/%s", f, ThingFlag_to_c_str(f));
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_flag_vec[ f ]);
}

auto tp_variant(ThingFlag f, int variant) -> Tpp
{
  TRACE_NO_INDENT();

  for (auto *tp : tp_flag_vec[ f ]) {
    if (tp_variant_get(tp) == variant) {
      return tp;
    }
  }

  ERR("tp_variant: failed to find %d/%s variant %d", f, ThingFlag_to_c_str(f), variant);
  return nullptr;
}

auto tp_first(ThingFlag f) -> Tpp
{
  TRACE_NO_INDENT();

  if (unlikely(tp_flag_vec[ f ].empty())) {
    ERR("tp_first: no tp found for ThingFlag %d/%s", f, ThingFlag_to_c_str(f));
    return nullptr;
  }
  return tp_flag_vec[ f ][ 0 ];
}

void tp_damage_set(Tpp tp, ThingEventType ev, const std::string &val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
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
auto tp_damage(Tpp tp, ThingEventType val) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
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
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
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
auto tp_chance(Tpp tp, ThingChanceType val) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
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
auto tp_chance_success(Tpp tp, ThingChanceType val) -> bool
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return false;
  }

  if (val >= THING_CHANCE_ENUM_MAX) {
    TP_ERR(tp, "bad value in tp for %s, %d", __FUNCTION__, val);
    return false;
  }

  auto roll = tp->chance[ val ].roll();
  if (roll == 0) {
    return false;
  }

  return roll == tp->chance[ val ].max_roll();
}

//
// Roll for chance of success
//
auto tp_chance_fail(Tpp tp, ThingChanceType val) -> bool
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return false;
  }

  if (val >= THING_CHANCE_ENUM_MAX) {
    TP_ERR(tp, "bad value in tp for %s, %d", __FUNCTION__, val);
    return false;
  }

  return tp->chance[ val ].roll() == 1;
}

auto tp_tiles_get(Tpp tp, ThingAnim val, int index) -> Tilep
{
  TRACE_NO_INDENT();

  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return nullptr;
  }

  if (std::cmp_greater_equal(index, tp->tiles[ val ].size())) {
    TP_ERR(tp, "tp_tiles_get: tile overflow tp %s class %s/%d index %d", tp->name.c_str(),
           ThingAnim_to_string(val).c_str(), val, index);
  }

  return tp->tiles[ val ][ index ];
}

void tp_tiles_push_back(Tpp tp, ThingAnim val, Tilep tile)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }

  if (val >= THING_ANIM_ENUM_MAX) {
    TP_ERR(tp, "bad value in tp for %s, %d", __FUNCTION__, val);
    return;
  }

  tp->tiles[ val ].push_back(tile);
}

auto tp_tiles_size(Tpp tp, ThingAnim val) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return (int) tp->tiles[ val ].size();
}

auto tp_name(Tpp tp) -> std::string
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return "<noname>";
  }
  return tp->name;
}

void tp_short_name_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->short_name = std::string(val);
}

auto tp_short_name(Tpp tp) -> std::string
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return "<noshortname>";
  }
  if (tp->short_name.empty()) {
    return tp_name(tp);
  }
  return tp->short_name;
}

void tp_long_name_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->long_name = std::string(val);
}

auto tp_long_name(Tpp tp) -> std::string
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return "<nolongname>";
  }
  if (tp->long_name.empty()) {
    return tp_short_name(tp);
  }
  return tp->long_name;
}

void tp_apostrophize_name_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->apostrophize_name = std::string(val);
}

auto tp_apostrophize_name(Tpp tp) -> std::string
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return "<noapostrophizename>";
  }
  if (tp->apostrophize_name.empty()) {
    return tp_long_name(tp);
  }
  return tp->apostrophize_name;
}

void tp_pluralize_name_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->pluralize_name = std::string(val);
}

auto tp_pluralize_name(Tpp tp) -> std::string
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return "<nopluralizename>";
  }
  if (tp->pluralize_name.empty()) {
    return tp_long_name(tp);
  }
  return tp->pluralize_name;
}

void tp_real_name_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->real_name = std::string(val);
}

auto tp_real_name(Tpp tp) -> std::string
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return "<norealname>";
  }
  if (tp->real_name.empty()) {
    return tp_long_name(tp);
  }
  return tp->real_name;
}

void tp_light_color_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->light_color = color_find(val.c_str());
}

void tp_light_color_apply(Tpp tp)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  glcolor(tp->light_color);
}

auto tp_light_color(Tpp tp) -> color
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT();
  if (! tp) {
    TP_ERR(tp, "No thing template pointer set");
    return WHITE;
  }
#endif
  return tp->light_color;
}

auto tp_flag(Tpp tp, ThingFlag f) -> int
{
#ifdef _DEBUG_BUILD_
  TRACE_NO_INDENT(); // expensive
#endif

  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->flag[ f ];
}

void tp_flag_set(Tpp tp, ThingFlag f, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->flag[ f ] = val;
}

void tp_z_depth_set(Tpp tp, MapZDepth val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->z_depth = val;
}
auto tp_z_depth_get(Tpp tp) -> uint8_t
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->z_depth;
}

void tp_speed_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->speed = val;
}

auto tp_speed_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->speed;
}

void tp_weight_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->weight = val;
}

auto tp_weight_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->weight;
}

void tp_monst_group_add(Tpp tp, ThingMonstGroup val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
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
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
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

auto tp_is_immune_to(Tpp tp, ThingEventType val) -> bool
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
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
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->health_initial = Dice(std::string(val));
}

auto tp_health_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->health_initial.roll();
}

auto tp_health_max_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->health_initial.max_roll();
}

void tp_temperature_initial_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->temperature_initial = val;
}

auto tp_temperature_initial_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->temperature_initial;
}

void tp_temperature_burns_at_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->temperature_burns_at = val;
}

auto tp_temperature_burns_at_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->temperature_burns_at;
}

void tp_temperature_melts_at_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->temperature_melts_at = val;
}

auto tp_temperature_melts_at_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->temperature_melts_at;
}

void tp_temperature_damage_at_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->temperature_damage_at = val;
}

auto tp_temperature_damage_at_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->temperature_damage_at;
}

void tp_value1_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value1 = val;
}

auto tp_value1_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value1;
}

void tp_value2_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value2 = val;
}

auto tp_value2_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value2;
}

void tp_value3_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value3 = val;
}

auto tp_value3_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value3;
}

void tp_value4_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value4 = val;
}

auto tp_value4_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value4;
}

void tp_value5_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value5 = val;
}

auto tp_value5_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value5;
}

void tp_value6_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value6 = val;
}

auto tp_value6_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value6;
}

void tp_value7_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value7 = val;
}

auto tp_value7_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value7;
}

void tp_value8_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value8 = val;
}

auto tp_value8_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value8;
}

void tp_value9_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value9 = val;
}

auto tp_value9_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value9;
}

void tp_value10_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value10 = val;
}

auto tp_value10_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value10;
}

void tp_value11_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value11 = val;
}

auto tp_value11_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value11;
}

void tp_value12_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value12 = val;
}

auto tp_value12_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value12;
}

void tp_value13_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value13 = val;
}

auto tp_value13_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value13;
}

void tp_value14_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value14 = val;
}

auto tp_value14_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value14;
}

void tp_value15_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value15 = val;
}

auto tp_value15_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value15;
}

void tp_value16_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value16 = val;
}

auto tp_value16_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value16;
}

void tp_value17_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value17 = val;
}

auto tp_value17_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value17;
}

void tp_value18_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value18 = val;
}

auto tp_value18_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value18;
}

void tp_value19_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value19 = val;
}

auto tp_value19_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value19;
}

void tp_value20_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->value20 = val;
}

auto tp_value20_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->value20;
}

void tp_minion_max_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  if (val > THING_MINION_MAX) {
    TP_ERR(tp, "minion max too high: %d", val);
    return;
  }

  tp->minion_max = val;
}

auto tp_minion_max_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->minion_max;
}

void tp_distance_minion_from_mob_max_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->distance_minion_from_mob_max = val;
}

auto tp_distance_minion_from_mob_max_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->distance_minion_from_mob_max;
}

void tp_distance_vision_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->distance_vision = val;
}

auto tp_distance_vision_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->distance_vision;
}

void tp_temperature_thermal_conductivity_set(Tpp tp, float val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->temperature_thermal_conductivity = val;
}

auto tp_temperature_thermal_conductivity_get(Tpp tp) -> float
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->temperature_thermal_conductivity;
}

void tp_temperature_heat_capacity_set(Tpp tp, float val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->temperature_heat_capacity = val;
}

auto tp_temperature_heat_capacity_get(Tpp tp) -> float
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->temperature_heat_capacity;
}

void tp_variant_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->variant = val;
}

auto tp_variant_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->variant;
}

void tp_priority_set(Tpp tp, ThingPriorityType val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->priority = val;
}

auto tp_priority_get(Tpp tp) -> ThingPriorityType
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return THING_PRIORITY_LOW;
  }
  return tp->priority;
}

void tp_distance_jump_set(Tpp tp, int val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->distance_jump = val;
}

auto tp_distance_jump_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->distance_jump;
}

void tp_lifespan_set(Tpp tp, const std::string &val)
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return;
  }
  tp->lifespan = Dice(std::string(val));
}

auto tp_lifespan_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->lifespan.roll();
}

auto tp_lifespan_max_get(Tpp tp) -> int
{
  TRACE_NO_INDENT();
  if (tp == nullptr) {
    TP_ERR(tp, "No thing template pointer set");
    return 0;
  }
  return tp->lifespan.max_roll();
}

auto tp_collision_radius(Tpp t) -> float
{
  TRACE_NO_INDENT();

  return tp_is_collision_circle_small(t) ? 0.25 : 0.5;
}
