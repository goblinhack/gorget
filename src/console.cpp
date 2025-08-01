//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_console.hpp"
#include "my_main.hpp"

static inline void term_puts_fg(unsigned char a)
{
  TRACE_NO_INDENT();

  static const char *data[] = {
      "[30m", "[31m", "[32m", "[33m", "[34m", "[35m", "[36m", "[37m", "\033[m",
  };

  if (a >= ARRAY_SIZE(data)) {
    ERR("Overflow");
  }

  fputs(data[ a ], stdout);
}

static void term_puts_fgbg(unsigned char fg, unsigned char bg)
{
  TRACE_NO_INDENT();

  static const char *data[] = {
      "[40;30m", "[40;31m", "[40;32m", "[40;33m", "[40;34m", "[40;35m", "[40;36m", "[40;37m",
      "[41;30m", "[41;31m", "[41;32m", "[41;33m", "[41;34m", "[41;35m", "[41;36m", "[41;37m",
      "[42;30m", "[42;31m", "[42;32m", "[42;33m", "[42;34m", "[42;35m", "[42;36m", "[42;37m",
      "[43;30m", "[43;31m", "[43;32m", "[43;33m", "[43;34m", "[43;35m", "[43;36m", "[43;37m",
      "[44;30m", "[44;31m", "[44;32m", "[44;33m", "[44;34m", "[44;35m", "[44;36m", "[44;37m",
      "[45;30m", "[45;31m", "[45;32m", "[45;33m", "[45;34m", "[45;35m", "[45;36m", "[45;37m",
      "[46;30m", "[46;31m", "[46;32m", "[46;33m", "[46;34m", "[46;35m", "[46;36m", "[46;37m",
      "[47;30m", "[47;31m", "[47;32m", "[47;33m", "[47;34m", "[47;35m", "[47;36m", "[47;37m",
  };

  if (bg == 0) {
    /*
     * Allow the default color to be 0, that of the terminal.
     */
    term_puts_fg(fg);
    return;
  }

  fputs((char *) data[ (bg & 7) * 8 + (fg & 7) ], stdout);
}

static term_color term_color_string_to_index(const char **s)
{
  TRACE_NO_INDENT();

  if (! strncmp(*s, "black$", SIZEOF("black$") - 1)) {
    *s += SIZEOF("black$") - 1;
    return (TERM_COLOR_BLACK);
  }
  if (! strncmp(*s, "red$", SIZEOF("red$") - 1)) {
    *s += SIZEOF("red$") - 1;
    return (TERM_COLOR_RED);
  }
  if (! strncmp(*s, "green$", SIZEOF("green$") - 1)) {
    *s += SIZEOF("green$") - 1;
    return (TERM_COLOR_GREEN);
  }
  if (! strncmp(*s, "yellow$", SIZEOF("yellow$") - 1)) {
    *s += SIZEOF("yellow$") - 1;
    return (TERM_COLOR_YELLOW);
  }
  if (! strncmp(*s, "orange$", SIZEOF("orange$") - 1)) {
    *s += SIZEOF("orange$") - 1;
    return (TERM_COLOR_YELLOW);
  }
  if (! strncmp(*s, "blue$", SIZEOF("blue$") - 1)) {
    *s += SIZEOF("blue$") - 1;
    return (TERM_COLOR_BLUE);
  }
  if (! strncmp(*s, "pink$", SIZEOF("pink$") - 1)) {
    *s += SIZEOF("pink$") - 1;
    return (TERM_COLOR_PINK);
  }
  if (! strncmp(*s, "cyan$", SIZEOF("cyan$") - 1)) {
    *s += SIZEOF("cyan$") - 1;
    return (TERM_COLOR_CYAN);
  }
  if (! strncmp(*s, "white$", SIZEOF("white$") - 1)) {
    *s += SIZEOF("white$") - 1;
    return (TERM_COLOR_WHITE);
  }
  if (! strncmp(*s, "reset$", SIZEOF("reset$") - 1)) {
    *s += SIZEOF("reset$") - 1;
    return (TERM_COLOR_RESET);
  }

  (void) string2color(s);

  return (TERM_COLOR_WHITE);
}

void term_log(const char *s)
{
  TRACE_NO_INDENT();
  char c;

  int fg = TERM_COLOR_WHITE;
  int bg = TERM_COLOR_BLACK;

  while ((c = *s++) != '\0') {

    if (c == '%') {
      if (! strncmp(s, "fg=", 3)) {
        s += 3;
        term_puts_fg(fg = term_color_string_to_index(&s));
        continue;
      }

      if (! strncmp(s, "bg=", 3)) {
        s += 3;
        bg = term_color_string_to_index(&s);
        term_puts_fgbg(fg, bg);
        continue;
      }
      continue;
    }

    putchar(c);
  }
}

int term_color_to_console_color(color c)
{
  if (c == BLACK)
    return TERM_COLOR_BLACK;
  if (c == BLUE)
    return TERM_COLOR_BLACK;
  if (c == BROWN)
    return TERM_COLOR_BLACK;
  if (c == COLOR_NONE)
    return TERM_COLOR_RESET;
  if (c == CYAN)
    return TERM_COLOR_CYAN;
  if (c == DARKBLUE)
    return TERM_COLOR_BLUE;
  if (c == DARKGRAY)
    return TERM_COLOR_BLACK;
  if (c == DARKGREEN)
    return TERM_COLOR_GREEN;
  if (c == DARKOLIVEGREEN2)
    return TERM_COLOR_GREEN;
  if (c == DARKOLIVEGREEN)
    return TERM_COLOR_GREEN;
  if (c == DARKRED)
    return TERM_COLOR_RED;
  if (c == DEEPWATER)
    return TERM_COLOR_BLUE;
  if (c == FORESTGREEN)
    return TERM_COLOR_GREEN;
  if (c == GOLD)
    return TERM_COLOR_YELLOW;
  if (c == GRAY10)
    return TERM_COLOR_BLUE;
  if (c == GRAY30)
    return TERM_COLOR_BLUE;
  if (c == GRAY40)
    return TERM_COLOR_BLUE;
  if (c == GRAY50)
    return TERM_COLOR_BLUE;
  if (c == GRAY5)
    return TERM_COLOR_BLUE;
  if (c == GRAY60)
    return TERM_COLOR_WHITE;
  if (c == GRAY70)
    return TERM_COLOR_WHITE;
  if (c == GRAY80)
    return TERM_COLOR_WHITE;
  if (c == GRAY90)
    return TERM_COLOR_WHITE;
  if (c == GRAY)
    return TERM_COLOR_WHITE;
  if (c == GREEN)
    return TERM_COLOR_GREEN;
  if (c == LIGHTBLUE)
    return TERM_COLOR_BLUE;
  if (c == LIGHTGREEN)
    return TERM_COLOR_GREEN;
  if (c == LIMEGREEN)
    return TERM_COLOR_GREEN;
  if (c == LIME)
    return TERM_COLOR_GREEN;
  if (c == MAGENTA)
    return TERM_COLOR_PINK;
  if (c == ORANGE)
    return TERM_COLOR_YELLOW;
  if (c == PEACHPUFF)
    return TERM_COLOR_RED;
  if (c == PINK)
    return TERM_COLOR_RED;
  if (c == PURPLE)
    return TERM_COLOR_PINK;
  if (c == RED)
    return TERM_COLOR_RED;
  if (c == SILVER)
    return TERM_COLOR_WHITE;
  if (c == STEELBLUE)
    return TERM_COLOR_WHITE;
  if (c == WATER)
    return TERM_COLOR_CYAN;
  if (c == WHITE)
    return TERM_COLOR_WHITE;
  if (c == YELLOW)
    return TERM_COLOR_YELLOW;
  if (c == PURPLE)
    return TERM_COLOR_BLUE;
  return TERM_COLOR_BLUE;
}
