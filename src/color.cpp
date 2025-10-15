//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_gl.hpp"
#include "my_string.hpp"
#include "my_ui.hpp"

#include <unordered_map>

using colors = std::unordered_map< std::string, color >;

colors      color_map;
static bool color_init_done;

void color_set(std::string name, color *c, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  TRACE_NO_INDENT();
  c->r = r;
  c->g = g;
  c->b = b;
  c->a = a;

  auto result = color_map.insert(std::make_pair(name, *c));
  if (! result.second) {
    ERR("Color insert name [%s] failed", name.c_str());
  }
}

void color_init(void)
{
  TRACE_NO_INDENT();
  color_init1();
  color_init2();
  color_init3();
  color_init4();
  color_init_done = true;
}

void color_fini(void)
{
  TRACE_NO_INDENT();
  color_map.clear();
}

color string2color(const char **s)
{
  TRACE_NO_INDENT();
  static char        tmp[ MAXSHORTSTR ];
  static const char *eo_tmp = tmp + SIZEOF(tmp);
  const char        *c      = *s;
  char              *t      = tmp;

  while (t < eo_tmp) {
    if ((*c == '\0') || (*c == '$')) {
      break;
    }

    *t++ = *c++;
  }

  if (c == eo_tmp) {
    return WHITE;
  }

  *t++ = '\0';
  *s += (t - tmp);

  if (! strcasecmp(tmp, "reset")) {
    return (UI_COLOR);
  }

  auto result = color_map.find(std::string(tmp));

  if (result == color_map.end()) {
    if (color_init_done) { // avoids color warnings due to very early errors
      ERR("Unknown color [%s]", tmp);
    }
    return WHITE;
  }

  return (result->second);
}

color string2color(std::string &s, int *len)
{
  TRACE_NO_INDENT();
  auto        iter = s.begin();
  std::string out;

  while (iter != s.end()) {
    auto c = *iter;

    if ((c == '\0') || (c == '$')) {
      break;
    }

    out += c;
    iter++;
  }

  if (len) {
    *len = iter - s.begin();
  }

  if (out == "reset") {
    return (UI_COLOR);
  }

  auto result = color_map.find(out);

  if (result == color_map.end()) {
    if (color_init_done) { // avoids color warnings due to very early errors
      ERR("Unknown color [%s]", out.c_str());
    }
    return WHITE;
  }

  return (result->second);
}

color string2color(std::string &s)
{
  auto        iter = s.begin();
  std::string out;

  while (iter != s.end()) {
    auto c = *iter;

    if ((c == '\0') || (c == '$')) {
      break;
    }

    out += c;
    iter++;
  }

  if (out == "reset") {
    return (UI_COLOR);
  }

  auto result = color_map.find(out);

  if (result == color_map.end()) {
    if (color_init_done) { // avoids color warnings due to very early errors
      ERR("Unknown color [%s]", out.c_str());
    }
    return WHITE;
  }

  return (result->second);
}

color color_find(const char *s)
{
  TRACE_NO_INDENT();
  if (! s) {
    return WHITE;
  }

  if (! strcmp(s, "")) {
    return WHITE;
  }

  auto result = color_map.find(std::string(s));

  if (result == color_map.end()) {
    if (color_init_done) { // avoids color warnings due to very early errors
      ERR("Unknown color [%s]", s);
    }
    return WHITE;
  }

  return (result->second);
}

bool color_eq(const color &col1, const color &col2)
{
  return col1.r == col2.r && col1.g == col2.g && col1.b == col2.b && col1.a == col2.a;
}

bool color_neq(const color &col1, const color &col2)
{
  return col1.r != col2.r || col1.g != col2.g || col1.b != col2.b || col1.a != col2.a;
}
