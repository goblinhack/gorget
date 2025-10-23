//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_light.hpp"
#include "my_math.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl_event.hpp"
#include "my_tex.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"
#include "my_tp.hpp"

#include <array>

typedef struct {
  int16_t depth_furthest;
} Ray;

typedef struct {
  spoint p;
  double distance;
} RayPoint;

class Light
{
public:
  Light(void);
  ~Light(void);

  void ray_draw(const int16_t index, const spoint p0, const spoint p1);
  void ray_point_add(const int16_t index, const spoint p0, const spoint p1);
  void rays_generate(Gamep, Levelsp, Levelp);
  void calculate(Gamep, Levelsp, Levelp, level_fov_can_see_callback_t);
  void render(Gamep, Levelsp, Levelp);

  int light_dist {};
  int fbo {-1};

  Ray rays[ LIGHT_MAX_RAYS_MAX ];

  std::array< std::vector< RayPoint >, LIGHT_MAX_RAYS_MAX > points;

  std::vector< float > gl_cmds;
};

static Light *light;

Light::Light(void)
{
  TRACE_NO_INDENT();

  newptr(MTYPE_LIGHT, this, "Light");
}

Light::~Light(void)
{
  TRACE_NO_INDENT();

  oldptr(MTYPE_LIGHT, this);
}

void Light::ray_point_add(int16_t index, const spoint p0, const spoint p1)
{
  RayPoint ray;
  ray.p        = p1;
  ray.distance = DISTANCE(p0.x, p0.y, p1.x, p1.y);
  points[ index ].push_back(ray);
}

// http://www.edepot.com/linee.html
void Light::ray_draw(int16_t index, const spoint p0, const spoint p1)
{
  points[ index ].resize(0);

  const spoint start = p0;
  auto         x     = p0.x;
  auto         y     = p0.y;
  auto         x2    = p1.x;
  auto         y2    = p1.y;

  bool yLonger  = false;
  int  shortLen = y2 - y;
  int  longLen  = x2 - x;

  if (abs(shortLen) > abs(longLen)) {
    int swap = shortLen;
    shortLen = longLen;
    longLen  = swap;
    yLonger  = true;
  }
  int decInc;
  if (longLen == 0)
    decInc = 0;
  else
    decInc = (shortLen << 16) / longLen;

  if (yLonger) {
    if (longLen > 0) {
      longLen += y;
      for (int j = 0x8000 + (x << 16); y <= longLen; ++y) {
        ray_point_add(index, start, spoint(j >> 16, y));
        j += decInc;
      }
      return;
    }
    longLen += y;
    for (int j = 0x8000 + (x << 16); y >= longLen; --y) {
      ray_point_add(index, start, spoint(j >> 16, y));
      j -= decInc;
    }
    return;
  }

  if (longLen > 0) {
    longLen += x;
    for (int j = 0x8000 + (y << 16); x <= longLen; ++x) {
      ray_point_add(index, start, spoint(x, j >> 16));
      j += decInc;
    }
    return;
  }
  longLen += x;
  for (int j = 0x8000 + (y << 16); x >= longLen; --x) {
    ray_point_add(index, start, spoint(x, j >> 16));
    j -= decInc;
  }
}

//
// Generate the right ray lengths.
//
void Light::rays_generate(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  memset(rays, 0, sizeof(rays));

  double dr = (double) RAD_360 / ((double) LIGHT_MAX_RAYS_MAX);
  for (int i = 0; i < LIGHT_MAX_RAYS_MAX; i++) {
    double cosr, sinr;
    sincos(dr * (double) i, &sinr, &cosr);
    ray_draw(i, spoint(0, 0), spoint((int) ((double) light_dist * cosr), (int) ((double) light_dist * sinr)));
  }
}

static void light_tile(Gamep g, Levelsp v, Levelp l, Thingp t, ThingExtp ai, spoint pov, spoint tile, int max_radius,
                       level_fov_can_see_callback_t can_see)
{
  TRACE_NO_INDENT();

  //
  // Only apply color to the tile once
  //
  if (! ai->fov_can_see_tile.can_see[ tile.x ][ tile.y ]) {
    ai->fov_can_see_tile.can_see[ tile.x ][ tile.y ]        = true;
    l->player_fov_has_seen_tile.can_see[ tile.x ][ tile.y ] = true;
    can_see(g, v, l, t, pov, tile, max_radius);
  }

  //
  // This is the ray count hitting this tile
  //
  auto light_map_tile = &v->light_map.tile[ tile.x ][ tile.y ];
  if (light_map_tile->lit < 255) {
    light_map_tile->lit++;
  }
}

void Light::calculate(Gamep g, Levelsp v, Levelp l, level_fov_can_see_callback_t can_see)
{
  TRACE_NO_INDENT();

  auto player = thing_player(g);
  if (! player) {
    return;
  }

  auto ai = thing_ext_struct(g, player);
  if (! ai) {
    return;
  }

  memset(ai->fov_can_see_tile.can_see, 0, sizeof(ai->fov_can_see_tile.can_see));

  auto max_radius      = thing_vision_distance(player);
  auto pov             = player->at;
  auto vision_distance = max_radius * INNER_TILE_WIDTH;

  gl_cmds.clear();

  const int tile_w = INNER_TILE_WIDTH;
  const int tile_h = INNER_TILE_HEIGHT;

  //
  // Center the light on the player
  //
  spoint light_pos = player->pix_at;

  light_pos.x += INNER_TILE_WIDTH / 2;
  light_pos.y += INNER_TILE_HEIGHT / 2;

  //
  // Walk the light rays in a circle. Find the nearest walls and then let
  // the light leak a little.
  //
  for (auto i = 0; i < LIGHT_MAX_RAYS_MAX; i++) {
    const int16_t end_of_points = static_cast< uint16_t >(points[ i ].size() - 1);
    auto          ray           = &rays[ i ];
    auto          ray_pixel     = points[ i ].begin();
    int16_t       step          = 0;
    uint8_t       prev_tile_x   = -1;
    uint8_t       prev_tile_y   = -1;

    for (;; step++) {
      //
      // oob?
      //
      if (unlikely(step >= end_of_points)) {
        break;
      }

      //
      // Beyond vision limits?
      //
      if (unlikely(ray_pixel->distance > vision_distance)) {
        break;
      }

      int16_t p1x    = light_pos.x + ray_pixel->p.x;
      int16_t p1y    = light_pos.y + ray_pixel->p.y;
      uint8_t tile_x = p1x / tile_w;
      uint8_t tile_y = p1y / tile_h;
      ray_pixel++;

      //
      // Ignore the same tile. i.e. do not light it more than once.
      //
      if (likely((tile_x == prev_tile_x) && (tile_y == prev_tile_y))) {
        continue;
      }

      //
      // Oob can happen in custom levels with no edges
      //
      spoint tile(tile_x, tile_y);
      if (unlikely(is_oob(tile))) {
        break;
      }

      prev_tile_x = tile_x;
      prev_tile_y = tile_y;

      light_tile(g, v, l, player, ai, pov, tile, max_radius, can_see);

      //
      // This is for foliage so we don't obscure too much where we stand
      //
      if (step < INNER_TILE_WIDTH / 2) {
        continue;
      }

      //
      // Once we hit an obstacle to vision, how far do we allow the ray of light to penetrate
      //
      auto obs_to_vision_start_distance       = ray_pixel->distance;
      auto obs_to_vision_penetration_distance = (obs_to_vision_start_distance + INNER_TILE_WIDTH) - 1;

      //
      // Keep track of the type of object we hit
      //
      Thingp obs_to_vision;
      Tpp    tp_obs_to_vision;
      Thingp next_obs_to_vision;

      //
      // Did the light ray hit an obstacle?
      //
      obs_to_vision = level_is_obs_to_vision(g, v, l, tile);
      if (obs_to_vision) {
        //
        // What type of obstacle?
        //
        tp_obs_to_vision = thing_tp(obs_to_vision);

        //
        // We hit a wall. Keep walking until we exit the wall or we reach the light limit.
        //
        int16_t step2 = step;

        for (;;) {
          //
          // oob?
          //
          if (unlikely(step2 >= end_of_points)) {
            break;
          }

          //
          // Check if we've progressed far enough into the wall
          //
          if (unlikely(ray_pixel->distance > obs_to_vision_penetration_distance)) {
            break;
          }

          p1x    = light_pos.x + ray_pixel->p.x;
          p1y    = light_pos.y + ray_pixel->p.y;
          tile_x = p1x / tile_w;
          tile_y = p1y / tile_h;
          ray_pixel++;

          //
          // Ignore the same tile. i.e. do not light it more than once.
          //
          if (likely((tile_x == prev_tile_x) && (tile_y == prev_tile_y))) {
            step2++;
            continue;
          }

          //
          // Oob can happen in custom levels with no edges
          //
          tile.x = tile_x;
          tile.y = tile_y;
          if (unlikely(is_oob(tile))) {
            break;
          }

          prev_tile_x = tile_x;
          prev_tile_y = tile_y;

          //
          // If we've left the wall, we're done
          //
          next_obs_to_vision = level_is_obs_to_vision(g, v, l, tile);
          if (! next_obs_to_vision) {
            break;
          }

          //
          // If we've hit a different type of object, e.g. wall versus rock
          //
          if (thing_tp(next_obs_to_vision) != tp_obs_to_vision) {
            break;
          }

          light_tile(g, v, l, player, ai, pov, tile, max_radius, can_see);
          step2++;
        }

        //
        // This is how far the light travelled into the wall
        //
        step = step2;
        break;
      }
    }

    ray->depth_furthest = step;
  }
}

void Light::render(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  auto player = thing_player(g);
  if (! player) {
    return;
  }

  spoint light_pos = player->pix_at;

  light_pos.x += INNER_TILE_WIDTH / 2;
  light_pos.y += INNER_TILE_HEIGHT / 2;

  int w, h;
  fbo_get_size(g, FBO_MAP_LIGHT, w, h);
  gl_enter_2d_mode(g, w, h);

  glBlendFunc(GL_ONE, GL_ZERO);
  blit_fbo_bind(light->fbo);
  glClear(GL_COLOR_BUFFER_BIT);

  if (! gl_cmds.size()) {
    blit_init();

    int i;

    //
    // Walk the light rays in a circle.
    //
    push_point(light_pos.x, light_pos.y);

    for (i = 0; i < LIGHT_MAX_RAYS_MAX; i++) {
      auto    ray = &rays[ i ];
      spoint &p   = points[ i ][ ray->depth_furthest ].p;
      int16_t p1x = light_pos.x + p.x;
      int16_t p1y = light_pos.y + p.y;
      push_point(p1x, p1y);
    }

    //
    // Complete the circle with the first point again.
    //
    i = 0;
    {
      auto    ray = &rays[ i ];
      spoint &p   = points[ i ][ ray->depth_furthest ].p;
      int16_t p1x = light_pos.x + p.x;
      int16_t p1y = light_pos.y + p.y;
      push_point(p1x, p1y);
    }

    auto sz = bufp - gl_array_buf;
    gl_cmds.resize(sz);
    std::copy(gl_array_buf, bufp, gl_cmds.begin());
    blit_flush_triangle_fan();

    if (0) {
      glcolor(WHITE);
      blit_init();
      for (i = 0; i < LIGHT_MAX_RAYS_MAX; i++) {
        auto    ray = &rays[ i ];
        spoint &p   = points[ i ][ ray->depth_furthest ].p;
        int16_t p1x = light_pos.x + p.x;
        int16_t p1y = light_pos.y + p.y;
        gl_blitline(p1x, p1y, light_pos.x, light_pos.y);
      }

      i = 0;
      {
        auto    ray = &rays[ i ];
        spoint &p   = points[ i ][ ray->depth_furthest ].p;
        int16_t p1x = light_pos.x + p.x;
        int16_t p1y = light_pos.y + p.y;
        gl_blitline(p1x, p1y, light_pos.x, light_pos.y);
      }
      blit_flush();
    }

  } else {
    auto *b = &(*gl_cmds.begin());
    auto *e = &(*gl_cmds.end());
    blit_flush_triangle_fan(b, e);
  }

  blit_fbo_unbind();
}

static Lightp light_new(int light_dist, int fbo)
{
  TRACE_NO_INDENT();

  auto l = new Light();

  l->light_dist = light_dist;
  if (! light_dist) {
    DIE("No light power");
  }

  l->fbo = fbo;

  return l;
}

void level_light_calculate_for_player(Gamep g, Levelsp v, Levelp l, int fbo)
{
  if (! g || ! v || ! l) {
    return;
  }

  auto player = thing_player(g);
  if (! player) {
    return;
  }

  if (g_thread_id != -1) {
    return;
  }

  if (! light) {
    auto vision_distance = thing_vision_distance(player);

    light = light_new(vision_distance * INNER_TILE_WIDTH, fbo);
    if (! light) {
      return;
    }
    light->rays_generate(g, v, l);
  }

  light->calculate(g, v, l, level_light_calculate_can_see_callback);

  if (! g_opt_tests) {
    light->render(g, v, l);
  }
}

void player_light_fini(void)
{
  delete light;
  light = nullptr;
}
