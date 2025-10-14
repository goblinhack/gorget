//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
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
  float  distance;
} RayPoint;

class Light
{
public:
  Light(void);
  ~Light(void);

  void ray_draw(const int16_t index, const spoint p0, const spoint p1);
  void ray_point_add(const int16_t index, const spoint p0, const spoint p1);
  void rays_generate(Gamep, Levelsp, Levelp);
  void calculate(Gamep, Levelsp, Levelp);
  void render(Gamep, Levelsp, Levelp);

  int   light_dist {};
  int   fbo {-1};
  color col {WHITE};

  Ray ray[ LIGHT_MAX_RAYS_MAX ];

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
  RayPoint r;
  r.p        = p1;
  r.distance = DISTANCE(p0.x, p0.y, p1.x, p1.y);
  points[ index ].push_back(r);
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

  memset(ray, 0, sizeof(ray));

  float dr = RAD_360 / ((float) LIGHT_MAX_RAYS_MAX);
  for (auto i = 0; i < LIGHT_MAX_RAYS_MAX; i++) {
    float cosr, sinr;
    sincosf(dr * i, &sinr, &cosr);
    ray_draw(i, spoint(0, 0), spoint((int) ((float) light_dist * cosr), (int) ((float) light_dist * sinr)));
  }
}

void Light::calculate(Gamep g, Levelsp v, Levelp l)
{
  TRACE_NO_INDENT();

  auto player = thing_player(g);
  if (! player) {
    return;
  }

  float vision_distance = thing_vision_distance(player);

  gl_cmds.clear();

  //
  // Slighly insane optimization
  //
  int last_x;
  int last_y;

#define AVOID_LOOKING_AT_THE_SAME_TILE()                                                                             \
  {                                                                                                                  \
    if (likely((x == last_x) && (y == last_y))) {                                                                    \
      rp++;                                                                                                          \
      continue;                                                                                                      \
    }                                                                                                                \
    last_x = x;                                                                                                      \
    last_y = y;                                                                                                      \
  }

#define AVOID_LOOKING_AT_THE_SAME_TILE2()                                                                            \
  {                                                                                                                  \
    if (likely((x == last_x) && (y == last_y))) {                                                                    \
      rp++;                                                                                                          \
      step2++;                                                                                                       \
      continue;                                                                                                      \
    }                                                                                                                \
    last_x = x;                                                                                                      \
    last_y = y;                                                                                                      \
  }

  int scale_x = INNER_TILE_WIDTH;
  int scale_y = INNER_TILE_HEIGHT;

  spoint light_pos = player->at;
  light_pos.x *= scale_x;
  light_pos.y *= scale_y;
  light_pos.x += INNER_TILE_WIDTH / 2;
  light_pos.y += INNER_TILE_HEIGHT / 2;

  //
  // Walk the light rays in a circle. Find the nearest walls and then let
  // the light leak a little.
  //
  for (int16_t i = 0; i < LIGHT_MAX_RAYS_MAX; i++) {
    auto          r             = &ray[ i ];
    int16_t       step          = 0;
    const int16_t end_of_points = static_cast< uint16_t >(points[ i ].size() - 1);
    auto          rp            = points[ i ].begin();
    last_x                      = -1;
    last_y                      = -1;

    for (;; step++) {
      if (unlikely(step >= end_of_points)) {
        break;
      }
      if (unlikely(rp->distance > vision_distance)) {
        break;
      }

      float p1x = light_pos.x + rp->p.x;
      float p1y = light_pos.y + rp->p.y;
      int   x   = (int) (p1x / (float) scale_x);
      int   y   = (int) (p1y / (float) scale_y);

      AVOID_LOOKING_AT_THE_SAME_TILE()
      rp++;

      if (level_is_obs_to_vision(g, v, l, spoint(x, y))) {
        //
        // We hit a wall. Keep walking until we exit the wall or we reach the light limit.
        //
        int16_t step2 = step;
        for (;;) {
          if (unlikely(step2 >= end_of_points)) {
            break;
          }

          if (rp->distance > step + scale_x) {
            break;
          }

          p1x = light_pos.x + rp->p.x;
          p1y = light_pos.y + rp->p.y;
          x   = (int) (p1x / (float) scale_x);
          y   = (int) (p1y / (float) scale_y);

          AVOID_LOOKING_AT_THE_SAME_TILE2()
          if (! level_is_obs_to_vision(g, v, l, spoint(x, y))) {
            break;
          }

          rp++;
          step2++;
        }
        step = step2;
        break;
      }
    }
    r->depth_furthest = step;
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
  glcolor(col);
  glClear(GL_COLOR_BUFFER_BIT);

  if (! gl_cmds.size()) {
    blit_init();

    int i;

    //
    // Walk the light rays in a circle.
    //
    push_point(light_pos.x, light_pos.y);

    for (i = 0; i < LIGHT_MAX_RAYS_MAX; i++) {
      auto    r   = &ray[ i ];
      spoint &p   = points[ i ][ r->depth_furthest ].p;
      int16_t p1x = light_pos.x + p.x;
      int16_t p1y = light_pos.y + p.y;
      push_point(p1x, p1y);
    }

    //
    // Complete the circle with the first point again.
    //
    i = 0;
    {
      auto    r   = &ray[ i ];
      spoint &p   = points[ i ][ r->depth_furthest ].p;
      int16_t p1x = light_pos.x + p.x;
      int16_t p1y = light_pos.y + p.y;
      push_point(p1x, p1y);
    }

    auto sz = bufp - gl_array_buf;
    gl_cmds.resize(sz);
    std::copy(gl_array_buf, bufp, gl_cmds.begin());
    blit_flush_triangle_fan();
  } else {
    auto *b = &(*gl_cmds.begin());
    auto *e = &(*gl_cmds.end());
    blit_flush_triangle_fan(b, e);
  }

  blit_fbo_unbind();
}

static Lightp light_new(int light_dist, color col, int fbo)
{
  TRACE_NO_INDENT();

  auto l = new Light();

  l->light_dist = light_dist;
  if (! light_dist) {
    DIE("No light power");
  }

  l->col = col;
  l->fbo = fbo;

  return l;
}

void player_light_render(Gamep g, Levelsp v, Levelp l, color col, int fbo)
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

    light = light_new(vision_distance, col, fbo);
    if (! light) {
      return;
    }
    light->rays_generate(g, v, l);
  }

  light->calculate(g, v, l);
  light->render(g, v, l);
}
