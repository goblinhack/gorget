//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_cave.hpp"
#include "my_charmap.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_math.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sdl_event.hpp"
#include "my_tex.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"
#include "my_time.hpp"
#include "my_tp.hpp"

#include <array>

typedef struct {
  int16_t depth_furthest;
} Ray;

typedef struct {
  spoint p;
  double distance;
} RayPixel;

class Raycast
{
public:
  Raycast(void);
  ~Raycast(void);

  void ray_pixel_line_draw(const int16_t index, const spoint p0, const spoint p1);
  void ray_pixel_add(const int16_t index, const spoint p0, const spoint p1);
  void ray_lengths_precalculate(Gamep, Levelsp, Levelp);
  void raycast_do(Gamep, Levelsp, Levelp);
  void raycast_render(Gamep, Levelsp, Levelp);

  //
  // This is how far the light rays reach
  //
  int ray_max_length_in_pixels {};

  //
  // What FBO to render to
  //
  int fbo {-1};

  //
  // The lenght of each ray when it is cast
  //
  Ray rays[ LIGHT_MAX_RAYS_MAX ];

  //
  // The precalculated ray lines
  //
  std::array< std::vector< RayPixel >, LIGHT_MAX_RAYS_MAX > ray_pixels;

  std::vector< float > ray_gl_cmds;
};

static Raycast *player_raycast;

static float light_fade[ MAP_WIDTH ];

void level_light_precalculate(Gamep g)
{
  static const char light_fade_map[]
      = "xxxx                                            " //
        "    xx                                          " //
        "      x                                         " //
        "       x                                        " //
        "        x                                       " //
        "        x                                       " //
        "         x                                      " //
        "         x                                      " //
        "          x                                     " //
        "          x                                     " //
        "          x                                     " //
        "          x                                     " //
        "          x                                     " //
        "          x                                     " //
        "           x                                    " //
        "           x                                    " //
        "           x                                    " //
        "           x                                    " //
        "           x                                    " //
        "            x                                   " //
        "            x                                   " //
        "            x                                   " //
        "            x                                   " //
        "            x                                   " //
        "             x                                  " //
        "             x                                  " //
        "             x                                  " //
        "              x                                 " //
        "              x                                 " //
        "              x                                 " //
        "               x                                " //
        "               x                                " //
        "                x                               " //
        "                 x                              " //
        "                  xx                            " //
        "                    xxx                         " //
        "                       xxxx                     " //
        "                           xxxxxx               " //
        "                                 xxxxxxx        " //
        "                                        xxxxxxxx" //
        "                                                " //
        "                                                " //
        "                                                " //
        "                                                " //
        "                                                " //
        "                                                " //
        "                                                " //
        "                                                " //
      ;

  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      auto c = light_fade_map[ (MAP_WIDTH * y) + x ];
      if (c == 'x') {
        if (light_fade[ x ] == 0) {
          light_fade[ x ] = 1.0f - ((float) y / MAP_HEIGHT);
        }
      }
    }
  }
}

//
// All light from all light sources, combined.
//
void level_light_fov_all_can_see_callback(Gamep g, Levelsp v, Levelp l, Thingp t, spoint pov, spoint p)
{
  color light_color      = tp_light_color(thing_tp(t));
  auto  light_strength   = thing_is_light_source(t);
  auto  light_fade_index = (int) ((distance(pov, p) / (float) light_strength) * (float) MAP_WIDTH);
  if (unlikely(light_fade_index >= MAP_WIDTH)) {
    light_fade_index = MAP_WIDTH - 1;
  }

  auto light_tile = &v->light_map.tile[ p.x ][ p.y ];
  auto fade       = light_fade[ light_fade_index ];

  light_tile->r += (int) (fade * light_color.r);
  light_tile->g += (int) (fade * light_color.g);
  light_tile->b += (int) (fade * light_color.b);

  if (DEBUG) {
    light_tile->r = 255;
    light_tile->g = 255;
    light_tile->b = 255;
  }
}

Raycast::Raycast(void)
{
  TRACE_NO_INDENT();

  newptr(MTYPE_LIGHT, this, "Raycast");
}

Raycast::~Raycast(void)
{
  TRACE_NO_INDENT();

  oldptr(MTYPE_LIGHT, this);
}

void Raycast::ray_pixel_add(int16_t index, const spoint p0, const spoint p1)
{
  RayPixel ray;
  ray.p        = p1;
  ray.distance = DISTANCE(p0.x, p0.y, p1.x, p1.y);
  ray_pixels[ index ].push_back(ray);
}

// http://www.edepot.com/linee.html
void Raycast::ray_pixel_line_draw(int16_t index, const spoint p0, const spoint p1)
{
  ray_pixels[ index ].resize(0);

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
        ray_pixel_add(index, start, spoint(j >> 16, y));
        j += decInc;
      }
      return;
    }
    longLen += y;
    for (int j = 0x8000 + (x << 16); y >= longLen; --y) {
      ray_pixel_add(index, start, spoint(j >> 16, y));
      j -= decInc;
    }
    return;
  }

  if (longLen > 0) {
    longLen += x;
    for (int j = 0x8000 + (y << 16); x <= longLen; ++x) {
      ray_pixel_add(index, start, spoint(x, j >> 16));
      j += decInc;
    }
    return;
  }
  longLen += x;
  for (int j = 0x8000 + (y << 16); x >= longLen; --x) {
    ray_pixel_add(index, start, spoint(x, j >> 16));
    j -= decInc;
  }
}

//
// Generate the right ray lengths.
//
void Raycast::ray_lengths_precalculate(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  double dr = (double) RAD_360 / ((double) LIGHT_MAX_RAYS_MAX);
  for (int i = 0; i < LIGHT_MAX_RAYS_MAX; i++) {
    double cosr, sinr;
    sincos(dr * (double) i, &sinr, &cosr);
    ray_pixel_line_draw(
        i, spoint(0, 0),
        spoint((int) ((double) ray_max_length_in_pixels * cosr), (int) ((double) ray_max_length_in_pixels * sinr)));
  }
}

static void light_tile(Gamep g, Levelsp v, Levelp l, Thingp t, ThingExtp ai, spoint pov, spoint tile)
{
  TRACE_NO_INDENT();

  //
  // Only apply color to the tile once
  //
  if (! ai->fov_can_see_tile.can_see[ tile.x ][ tile.y ]) {
    ai->fov_can_see_tile.can_see[ tile.x ][ tile.y ]        = true;
    l->player_fov_has_seen_tile.can_see[ tile.x ][ tile.y ] = true;
    level_light_fov_all_can_see_callback(g, v, l, t, pov, tile);
  }

  //
  // This is the ray count hitting this tile
  //
  auto light_map_tile = &v->light_map.tile[ tile.x ][ tile.y ];
  if (light_map_tile->lit < 255) {
    light_map_tile->lit++;
  }
}

void Raycast::raycast_do(Gamep g, Levelsp v, Levelp l)
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

  //
  // Reset the light ray lengths
  //
  memset(rays, 0, sizeof(rays));

  //
  // Reset what we can see
  //
  memset(ai->fov_can_see_tile.can_see, 0, sizeof(ai->fov_can_see_tile.can_see));

  //
  // The light source
  //
  auto pov = player->at;

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
    const int16_t end_of_points = static_cast< uint16_t >(ray_pixels[ i ].size() - 1);
    auto          ray           = &rays[ i ];
    auto          ray_pixel     = ray_pixels[ i ].begin();
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
      if (unlikely(ray_pixel->distance > ray_max_length_in_pixels)) {
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

      light_tile(g, v, l, player, ai, pov, tile);

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
      auto obs_to_vision_penetration_distance = (obs_to_vision_start_distance + INNER_TILE_WIDTH) - 2;

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
        int16_t step_inside_wall = step;

        for (;;) {
          //
          // oob?
          //
          if (unlikely(step_inside_wall >= end_of_points)) {
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
            step_inside_wall++;
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

          light_tile(g, v, l, player, ai, pov, tile);
          step_inside_wall++;
        }

        //
        // This is how far the light travelled into the wall
        //
        step = step_inside_wall;
        break;
      }
    }

    ray->depth_furthest = step;
  }

  //
  // Indicate that we need to generate new triangle gans
  //
  raycast_render(g, v, l);
}

//
// Re-generate triangle fans and render to the FBO
//
void Raycast::raycast_render(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  if (g_opt_tests) {
    return;
  }

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
  blit_fbo_bind(fbo);
  glClear(GL_COLOR_BUFFER_BIT);

  blit_init();

  int i;

  //
  // Walk the light rays in a circle.
  //
  push_point(light_pos.x, light_pos.y);

  for (i = 0; i < LIGHT_MAX_RAYS_MAX; i++) {
    auto    ray = &rays[ i ];
    spoint &p   = ray_pixels[ i ][ ray->depth_furthest ].p;
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
    spoint &p   = ray_pixels[ i ][ ray->depth_furthest ].p;
    int16_t p1x = light_pos.x + p.x;
    int16_t p1y = light_pos.y + p.y;
    push_point(p1x, p1y);
  }

  auto sz = bufp - gl_array_buf;
  ray_gl_cmds.resize(sz);
  std::copy(gl_array_buf, bufp, ray_gl_cmds.begin());
  blit_flush_triangle_fan();

  blit_fbo_unbind();
}

static Raycast *raycast_new(int ray_max_length_in_pixels, int fbo)
{
  TRACE_NO_INDENT();

  auto l = new Raycast();

  l->ray_max_length_in_pixels = ray_max_length_in_pixels;
  if (! ray_max_length_in_pixels) {
    DIE("No light power");
  }

  l->fbo = fbo;

  return l;
}

void level_light_raycast(Gamep g, Levelsp v, Levelp l, int fbo)
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

  if (! player_raycast) {
    //
    // This is how far the light rays reach
    //
    auto ray_max_length_in_pixels = thing_vision_distance(player) * INNER_TILE_WIDTH;

    player_raycast = raycast_new(ray_max_length_in_pixels, fbo);
    if (! player_raycast) {
      return;
    }
    player_raycast->ray_lengths_precalculate(g, v, l);
  }

  player_raycast->raycast_do(g, v, l);
}

void level_light_raycast_fini(void)
{
  delete player_raycast;
  player_raycast = nullptr;
}

//
// All light from all light sources, combined.
//
void level_light_fov_all(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  memset(&v->light_map, 0, sizeof(v->light_map));

  //
  // Now do the same for the player
  //
  level_light_raycast(g, v, l, FBO_MAP_LIGHT);

  //
  // Calculate all lit tiles for non player things
  //
  FOR_ALL_THINGS_ON_LEVEL(g, v, l, t)
  {
    int max_radius = thing_is_light_source(t);
    if (! max_radius) {
      continue;
    }

    if (thing_is_player(t)) {
      continue;
    }

    auto ext = thing_ext_struct(g, t);
    level_fov(g, v, l, t, &ext->fov_can_see_tile, &ext->fov_has_seen_tile, t->at, max_radius,
              level_light_fov_all_can_see_callback);
  }

  //
  // Calculate the total light color per tile
  //
  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      auto light_tile = &v->light_map.tile[ x ][ y ];

      if (light_tile->lit) {
        auto c_r = light_tile->r;
        if (c_r > 255) {
          c_r = 255;
        }
        auto c_g = light_tile->g;
        if (c_g > 255) {
          c_g = 255;
        }
        auto c_b = light_tile->b;
        if (c_b > 255) {
          c_b = 255;
        }

        light_tile->c.r = (uint8_t) c_r;
        light_tile->c.g = (uint8_t) c_g;
        light_tile->c.b = (uint8_t) c_b;
        light_tile->c.a = 255;
      }
    }
  }
}
