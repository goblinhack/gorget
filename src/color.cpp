//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_gl.hpp"
#include "my_string.hpp"
#include "my_ui.hpp"

#include <map>

using colors = std::map< std::string, color >;

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

color gl_save_color(255, 255, 255, 255);
color gl_last_color(255, 255, 255, 255);

void glcolor_save(void)
{
  TRACE_NO_INDENT();
  gl_save_color = gl_last_color;
}

void glcolor_restore(void)
{
  TRACE_NO_INDENT();
  color s = gl_last_color = gl_save_color;

  glColor4ub(s.r, s.g, s.b, s.a);
}

color gl_color_current(void) { return gl_last_color; }

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

const char *string2colorname(const char **s)
{
  TRACE_NO_INDENT();
  static char        tmp[ MAXSHORTSTR ];
  static const char *eo_tmp = tmp + MAXSHORTSTR - 1;
  const char        *c      = *s;
  char              *t      = tmp;

  while (t < eo_tmp) {
    if ((*c == '\0') || (*c == '$')) {
      break;
    }

    *t++ = *c++;
  }

  if (c == eo_tmp) {
    return nullptr;
  }

  *t++ = '\0';
  *s += (t - tmp);

  if (! strcasecmp(tmp, "reset")) {
    return (UI_COLOR_STR);
  }

  auto result = color_map.find(std::string(tmp));

  if (result == color_map.end()) {
    if (color_init_done) { // avoids color warnings due to very early errors
      ERR("Unknown color [%s]", tmp);
    }
    return ("");
  }

  return tmp;
}

std::string string2colorname(std::string &s)
{
  TRACE_NO_INDENT();
  auto        iter = s.begin();
  std::string out;

  if (s == "") {
    return ("white");
  }

  while (iter != s.end()) {
    auto c = *iter;

    if ((c == '\0') || (c == '$')) {
      break;
    }

    out += c;
    iter++;
  }

  if (out == "reset") {
    return (UI_COLOR_STR);
  }

  auto result = color_map.find(out);

  if (result == color_map.end()) {
    if (color_init_done) { // avoids color warnings due to very early errors
      ERR("Unknown color [%s]", out.c_str());
    }
    return ("");
  }

  return out;
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

color color_to_mono(color a)
{
  TRACE_NO_INDENT();
  float avg = (a.r + a.g + a.b) / 3.0;

  a.r = (int) avg;
  a.g = (int) avg;
  a.b = (int) avg;

  return a;
}
