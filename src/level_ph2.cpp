//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <array>

#include "my_array_bounds_check.hpp"
#include "my_charmap.hpp"
#include "my_level_ph1.hpp"
#include "my_level_ph2.hpp"
#include "my_level_ph2_room.hpp"
#include "my_main.hpp"
#include "my_point.hpp"
#include "my_template.hpp"

static LevelPh2Roomp get_fitted_room_type(const Level1Node *node, const LevelPh2Roomp room_left,
                                          const LevelPh2Roomp room_right, const LevelPh2Roomp room_up,
                                          const LevelPh2Roomp room_down)
{
  TRACE_NO_INDENT();

  auto required_room_type = ROOM_TYPE_NORMAL;

  if (node->is_entrance) {
    required_room_type = ROOM_TYPE_ENTRANCE;
  }
  if (node->is_exit) {
    required_room_type = ROOM_TYPE_EXIT;
  }
  if (node->is_key) {
    required_room_type = ROOM_TYPE_KEY;
  }
  if (node->is_lock) {
    required_room_type = ROOM_TYPE_LOCK;
  }
  if (node->is_secret) {
    required_room_type = ROOM_TYPE_SECRET;
  }

  int  max_elems = LevelPh2Room::all_rooms_of_type[ required_room_type ].size();
  auto tries     = max_elems * 4;

  while (tries-- > 0) {
    auto r = one_of(LevelPh2Room::all_rooms_of_type[ required_room_type ]);
    if (! r) {
      return nullptr;
    }

    int wanted = (((node->has_door_left || node->has_secret_exit_left) ? 1 : 0) << 3)
               | (((node->has_door_right || node->has_secret_exit_right) ? 1 : 0) << 2)
               | (((node->has_door_up || node->has_secret_exit_up) ? 1 : 0) << 1)
               | ((node->has_door_down || node->has_secret_exit_down) ? 1 : 0);

    int candidate = ((r->exits_left) ? 1 : 0) << 3 | ((r->exits_right) ? 1 : 0) << 2 | ((r->exits_up) ? 1 : 0) << 1
                  | ((r->exits_down) ? 1 : 0);

    if (wanted != candidate) {
      continue;
    }

    if (room_left && room_left->exits_right) {
      if (! (room_left->exits_right & r->exits_left)) {
        continue;
      }
    }

    if (room_right && room_right->exits_left) {
      if (! (room_right->exits_left & r->exits_right)) {
        continue;
      }
    }

    if (room_up && room_up->exits_down) {
      if (! (room_up->exits_down & r->exits_up)) {
        continue;
      }
    }

    if (room_down && room_down->exits_up) {
      if (! (room_down->exits_up & r->exits_down)) {
        continue;
      }
    }

    return r;
  }
  return nullptr;
}

void LevelPh2::dump(void)
{
  TRACE_NO_INDENT();

  const auto w = ((LEVEL_PH2_ROOM_WIDTH + 1) * LEVEL_PH1_WIDTH) + 1;
  const auto h = ((LEVEL_PH2_ROOM_HEIGHT + 1) * LEVEL_PH1_HEIGHT) + 1;

  std::array< std::array< char, h >, w > out {};

  for (auto room_across = 0; room_across < LEVEL_PH1_WIDTH; room_across++) {
    for (auto room_down = 0; room_down < LEVEL_PH1_HEIGHT; room_down++) {
      LevelPh2Roomp r = get(rooms, room_across, room_down);
      if (r) {
        for (auto ry = 0; ry < LEVEL_PH2_ROOM_HEIGHT; ry++) {
          for (auto rx = 0; rx < LEVEL_PH2_ROOM_WIDTH; rx++) {
            auto c = get(r->data, rx, ry);
            auto x = (room_across * (LEVEL_PH2_ROOM_WIDTH + 1)) + rx;
            auto y = (room_down * (LEVEL_PH2_ROOM_HEIGHT + 1)) + ry;
            set(out, x + 1, y + 1, c);
          }
        }
      }
    }
  }

  for (auto y = 0; y < h; y++) {
    std::string s;
    for (auto x = 0; x < w; x++) {
      auto c = get(out, x, y);
      if (c) {
        s += c;
      } else {
        s += ' ';
      }
    }
    LOG("Phase2: [%s]", s.c_str());
  }
  LOG("Phase2: -");
}

bool LevelPh2::solve(const LevelPh1 &ph1, point at)
{
  TRACE_NO_INDENT();

  auto x    = at.x;
  auto y    = at.y;
  auto r    = get(rooms, x, y);
  auto node = ph1.get_node_ptr_const(x, y);

  if (node->on_critical_path) {
    if (node->dir_up && ! node->dir_down && node->dir_left && node->dir_right && ! node->is_exit) {
      return false;
    }
  }

  if (! r) {
    //
    // Place a room that fits
    //
    LevelPh2Roomp left_room;
    LevelPh2Roomp right_room;
    LevelPh2Roomp up_room;
    LevelPh2Roomp down_room;

    if (x > 0) {
      left_room = get(rooms, x - 1, y);
    } else {
      left_room = nullptr;
    }
    if (x < LEVEL_PH1_WIDTH - 1) {
      right_room = get(rooms, x + 1, y);
    } else {
      right_room = nullptr;
    }
    if (y > 0) {
      up_room = get(rooms, x, y - 1);
    } else {
      up_room = nullptr;
    }
    if (y < LEVEL_PH1_HEIGHT - 1) {
      down_room = get(rooms, x, y + 1);
    } else {
      down_room = nullptr;
    }

    //
    // Place the room
    //
    r = get_fitted_room_type(node, left_room, right_room, up_room, down_room);
    if (! r) {
      return false;
    }
    set(rooms, x, y, r);
  }

  if (x > 0) {
    if (! get(rooms, x - 1, y)) {
      if (! solve(ph1, point(x - 1, y))) {
        return false;
      }
    }
  }

  if (x < LEVEL_PH1_WIDTH - 1) {
    if (! get(rooms, x + 1, y)) {
      if (! solve(ph1, point(x + 1, y))) {
        return false;
      }
    }
  }

  if (y > 0) {
    if (! get(rooms, x, y - 1)) {
      if (! solve(ph1, point(x, y - 1))) {
        return false;
      }
    }
  }

  if (y < LEVEL_PH1_HEIGHT - 1) {
    if (! get(rooms, x, y + 1)) {
      if (! solve(ph1, point(x, y + 1))) {
        return false;
      }
    }
  }

  return true;
}

LevelPh2::LevelPh2(const LevelPh1 &ph1)
{
  TRACE_NO_INDENT();

  point entrance_at;

  //
  // Find the starting point, the entrance
  //
  for (auto y = 0; y < ph1.grid_height; y++) {
    for (auto x = 0; x < ph1.grid_width; x++) {
      auto node = ph1.get_node_ptr_const(x, y);
      if (node->is_entrance) {
        entrance_at = point(x, y);
        goto got_entrance;
      }
    }
  }

  //
  // No entrance
  //
  return;

got_entrance:
  //
  // Create all the rooms
  //
  if (solve(ph1, entrance_at)) {
    ok = true;
    return;
  }
}

LevelPh2 level_ph2(const LevelPh1 &ph1)
{
  TRACE_NO_INDENT();

  LevelPh2 ph2(ph1);
  return ph2;
}
