//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_level.hpp"

//
// Create all fragments
//
void fragments_init(Gamep g)
{
  TRACE_NO_INDENT();

  if (fragment_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                   /* frag   */ (const char *) "     ",
                   /* frag   */ (const char *) "     ",
                   /* frag   */ (const char *) "     ",
                   /* frag   */ (const char *) "     ",
                   /* frag   */ (const char *) "     ", nullptr)) {
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "     ",
                     /* alt  */ (const char *) " ~   ",
                     /* alt  */ (const char *) "  ~~ ",
                     /* alt  */ (const char *) " ~ ~ ",
                     /* alt  */ (const char *) "     ", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "     ",
                     /* alt  */ (const char *) " ~~  ",
                     /* alt  */ (const char *) "  ~~ ",
                     /* alt  */ (const char *) " ~ ~ ",
                     /* alt  */ (const char *) "     ", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "  ~~~",
                     /* alt  */ (const char *) " ~~  ",
                     /* alt  */ (const char *) "  ~~ ",
                     /* alt  */ (const char *) " ~~~ ",
                     /* alt  */ (const char *) "~~   ", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "~~~  ",
                     /* alt  */ (const char *) " ~~~ ",
                     /* alt  */ (const char *) " ~~~~",
                     /* alt  */ (const char *) " ~~~~",
                     /* alt  */ (const char *) "~~ ~~", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "~    ",
                     /* alt  */ (const char *) " ~~~ ",
                     /* alt  */ (const char *) "  ~~~",
                     /* alt  */ (const char *) "  ~~~",
                     /* alt  */ (const char *) "   ~~", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xT~~x",
                     /* alt  */ (const char *) "x~~~x",
                     /* alt  */ (const char *) "xm~$x",
                     /* alt  */ (const char *) "xxxxx", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xT~~x",
                     /* alt  */ (const char *) "x~~~x",
                     /* alt  */ (const char *) "x~~$x",
                     /* alt  */ (const char *) "xxxxx", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xTCCx",
                     /* alt  */ (const char *) "xCCCx",
                     /* alt  */ (const char *) "xCC$x",
                     /* alt  */ (const char *) "xxxxx", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xTLLx",
                     /* alt  */ (const char *) "xLLLx",
                     /* alt  */ (const char *) "xLL$x",
                     /* alt  */ (const char *) "xxxxx", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xT..x",
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "x..$x",
                     /* alt  */ (const char *) "xxxxx", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "x.$mx",
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "xxTxx",
                     /* alt  */ (const char *) " xxx ", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xm$mx",
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "xxTxx",
                     /* alt  */ (const char *) " xxx ", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "....m",
                     /* alt  */ (const char *) ".CCC.",
                     /* alt  */ (const char *) ".C$C.",
                     /* alt  */ (const char *) ".CCC.",
                     /* alt  */ (const char *) "T....", nullptr);
  }

  if (fragment_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                   /* frag   */ (const char *) "xxxxx",
                   /* frag   */ (const char *) "x....",
                   /* frag   */ (const char *) "x....",
                   /* frag   */ (const char *) "x....",
                   /* frag   */ (const char *) "x....", nullptr)) {
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xbb..",
                     /* alt  */ (const char *) "xb...",
                     /* alt  */ (const char *) "x....",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xbbx.",
                     /* alt  */ (const char *) "xb.x.",
                     /* alt  */ (const char *) "xxDx.",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xm~~~",
                     /* alt  */ (const char *) "x~~~.",
                     /* alt  */ (const char *) "x~~..",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "x....",
                     /* alt  */ (const char *) "x..x.",
                     /* alt  */ (const char *) "x.xx.",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "x..C.",
                     /* alt  */ (const char *) "x.bx.",
                     /* alt  */ (const char *) "x.xx.",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xCC..",
                     /* alt  */ (const char *) "xC...",
                     /* alt  */ (const char *) "x..x.",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "x..x.",
                     /* alt  */ (const char *) "x....",
                     /* alt  */ (const char *) "xx.x.",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "x$mx.",
                     /* alt  */ (const char *) "x..C.",
                     /* alt  */ (const char *) "xxCx.",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "x....",
                     /* alt  */ (const char *) "x..x.",
                     /* alt  */ (const char *) "x..x.",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "x$.C.",
                     /* alt  */ (const char *) "x..C.",
                     /* alt  */ (const char *) "xCCC.",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xTCC.",
                     /* alt  */ (const char *) "xCCC.",
                     /* alt  */ (const char *) "xCCC.",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "x$.C.",
                     /* alt  */ (const char *) "x.C..",
                     /* alt  */ (const char *) "xC...",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "x$.x.",
                     /* alt  */ (const char *) "x..x.",
                     /* alt  */ (const char *) "xxsx.",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "x$mx.",
                     /* alt  */ (const char *) "x..x.",
                     /* alt  */ (const char *) "xxsx.",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_V_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xm$x.",
                     /* alt  */ (const char *) "x$mx.",
                     /* alt  */ (const char *) "xxsx.",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_VV_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "x$$x.",
                     /* alt  */ (const char *) "x$$x.",
                     /* alt  */ (const char *) "xxsx.",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_VV_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xb$x.",
                     /* alt  */ (const char *) "x..x.",
                     /* alt  */ (const char *) "xxsx.",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_VV_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "x$Cx.",
                     /* alt  */ (const char *) "xCCx.",
                     /* alt  */ (const char *) "xxsx.",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_VV_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xTCx.",
                     /* alt  */ (const char *) "xCCx.",
                     /* alt  */ (const char *) "xxsx.",
                     /* alt  */ (const char *) "x....", nullptr);
    fragment_alt_add(g, CHANCE_VV_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xT.x.",
                     /* alt  */ (const char *) "x..x.",
                     /* alt  */ (const char *) "xxsx.",
                     /* alt  */ (const char *) "x....", nullptr);
  }

  if (fragment_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                   /* frag   */ (const char *) "xxxxx",
                   /* frag   */ (const char *) "x...x",
                   /* frag   */ (const char *) "x...x",
                   /* frag   */ (const char *) "x...x",
                   /* frag   */ (const char *) "x...x", nullptr)) {
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xB$Bx",
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "xxsxx",
                     /* alt  */ (const char *) "x...x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xB$Bx",
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "xCCCx",
                     /* alt  */ (const char *) "x...x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xx.xx",
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "x...x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "x|T|x",
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "x...x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "xCTCx",
                     /* alt  */ (const char *) "xCCCx",
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "x...x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "x.$.x",
                     /* alt  */ (const char *) "xCCCx",
                     /* alt  */ (const char *) "xCCCx",
                     /* alt  */ (const char *) "x...x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxxx",
                     /* alt  */ (const char *) "x.$mx",
                     /* alt  */ (const char *) "xCCCx",
                     /* alt  */ (const char *) "xCCCx",
                     /* alt  */ (const char *) "x...x", nullptr);
  }

  if (fragment_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                   /* frag   */ (const char *) "xxxx",
                   /* frag   */ (const char *) "x..x",
                   /* frag   */ (const char *) "x..x",
                   /* frag   */ (const char *) "x..x",
                   /* frag   */ (const char *) "x..x", nullptr)) {
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxx",
                     /* alt  */ (const char *) "xB$x",
                     /* alt  */ (const char *) "x..x",
                     /* alt  */ (const char *) "xxsx",
                     /* alt  */ (const char *) "x..x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxx",
                     /* alt  */ (const char *) "xB$x",
                     /* alt  */ (const char *) "x..x",
                     /* alt  */ (const char *) "xCCx",
                     /* alt  */ (const char *) "x..x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxx",
                     /* alt  */ (const char *) "xx.x",
                     /* alt  */ (const char *) "x..x",
                     /* alt  */ (const char *) "x..x",
                     /* alt  */ (const char *) "x..x", nullptr);
  }

  if (fragment_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                   /* frag   */ (const char *) "xxxx",
                   /* frag   */ (const char *) "x..x",
                   /* frag   */ (const char *) "x..x",
                   /* frag   */ (const char *) "x..x", nullptr)) {
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x$Cx",
                     /* alt  */ (const char *) "xCCx",
                     /* alt  */ (const char *) "xCCx",
                     /* alt  */ (const char *) "x..x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxx",
                     /* alt  */ (const char *) "x$sx",
                     /* alt  */ (const char *) "xxxx",
                     /* alt  */ (const char *) "x..x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "....",
                     /* alt  */ (const char *) "....",
                     /* alt  */ (const char *) "....",
                     /* alt  */ (const char *) "....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".$..",
                     /* alt  */ (const char *) "B..B",
                     /* alt  */ (const char *) "CCCC",
                     /* alt  */ (const char *) "....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxx",
                     /* alt  */ (const char *) "x..x",
                     /* alt  */ (const char *) "x.xx",
                     /* alt  */ (const char *) "x..x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxxx",
                     /* alt  */ (const char *) "x.$x",
                     /* alt  */ (const char *) "x..x",
                     /* alt  */ (const char *) "x..x", nullptr);
  }

  if (fragment_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                   /* frag   */ (const char *) "xxx",
                   /* frag   */ (const char *) "x.x",
                   /* frag   */ (const char *) "x.x",
                   /* frag   */ (const char *) "x.x", nullptr)) {
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) "...", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) "x.x",
                     /* alt  */ (const char *) "x.x",
                     /* alt  */ (const char *) "x.x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) "x.x",
                     /* alt  */ (const char *) "x.x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x$x",
                     /* alt  */ (const char *) "xCx",
                     /* alt  */ (const char *) "xCx",
                     /* alt  */ (const char *) "x.x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxx",
                     /* alt  */ (const char *) "x$x",
                     /* alt  */ (const char *) "xCx",
                     /* alt  */ (const char *) "x.x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) "...", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "t$t",
                     /* alt  */ (const char *) "B.B",
                     /* alt  */ (const char *) "CCC",
                     /* alt  */ (const char *) "...", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "C$C",
                     /* alt  */ (const char *) "B.B",
                     /* alt  */ (const char *) "CCC",
                     /* alt  */ (const char *) "...", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxx",
                     /* alt  */ (const char *) "xmx",
                     /* alt  */ (const char *) "x.x",
                     /* alt  */ (const char *) "x.x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxx",
                     /* alt  */ (const char *) "x$x",
                     /* alt  */ (const char *) "x.x",
                     /* alt  */ (const char *) "x.x", nullptr);
  }

  if (fragment_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                   /* frag   */ (const char *) "xxx",
                   /* frag   */ (const char *) ".x.",
                   /* frag   */ (const char *) ".x.",
                   /* frag   */ (const char *) ".x.", nullptr)) {
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxx",
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) ".x.",
                     /* alt  */ (const char *) "...", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxx",
                     /* alt  */ (const char *) ".s.",
                     /* alt  */ (const char *) ".x.",
                     /* alt  */ (const char *) ".x.", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "xxx",
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) ".m.",
                     /* alt  */ (const char *) "...", nullptr);
  }

  if (fragment_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                   /* frag   */ (const char *) "     ",
                   /* frag   */ (const char *) " ....",
                   /* frag   */ (const char *) " ....",
                   /* frag   */ (const char *) " ....",
                   /* frag   */ (const char *) " ....", nullptr)) {
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "$.   ",
                     /* alt  */ (const char *) "..|..",
                     /* alt  */ (const char *) " |...",
                     /* alt  */ (const char *) " ....",
                     /* alt  */ (const char *) " ....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "m.   ",
                     /* alt  */ (const char *) "..C..",
                     /* alt  */ (const char *) " CC..",
                     /* alt  */ (const char *) " ....",
                     /* alt  */ (const char *) " ....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "m.   ",
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) " ....",
                     /* alt  */ (const char *) " ....",
                     /* alt  */ (const char *) " ....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "m..  ",
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) " ....",
                     /* alt  */ (const char *) " ....",
                     /* alt  */ (const char *) " ....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".... ",
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) " ....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "     ",
                     /* alt  */ (const char *) " ....",
                     /* alt  */ (const char *) " .x..",
                     /* alt  */ (const char *) " ....",
                     /* alt  */ (const char *) " ....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "$``  ",
                     /* alt  */ (const char *) "```..",
                     /* alt  */ (const char *) " ``..",
                     /* alt  */ (const char *) " `...",
                     /* alt  */ (const char *) " ...m", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "m``  ",
                     /* alt  */ (const char *) "```..",
                     /* alt  */ (const char *) " ``..",
                     /* alt  */ (const char *) " `...",
                     /* alt  */ (const char *) " ....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "C``  ",
                     /* alt  */ (const char *) "```..",
                     /* alt  */ (const char *) " ``..",
                     /* alt  */ (const char *) " `...",
                     /* alt  */ (const char *) " ....", nullptr);
  }

  if (fragment_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                   /* frag   */ (const char *) ".....",
                   /* frag   */ (const char *) ".....",
                   /* frag   */ (const char *) ".....",
                   /* frag   */ (const char *) ".....",
                   /* frag   */ (const char *) ".....", nullptr)) {
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".x...",
                     /* alt  */ (const char *) "..m..",
                     /* alt  */ (const char *) "...x.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".xsx.",
                     /* alt  */ (const char *) ".xTx.",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".   .",
                     /* alt  */ (const char *) ".   .",
                     /* alt  */ (const char *) ".   .",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".   .",
                     /* alt  */ (const char *) ". Ts.",
                     /* alt  */ (const char *) ".   .",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".   .",
                     /* alt  */ (const char *) ". $s.",
                     /* alt  */ (const char *) ".   .",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".   .",
                     /* alt  */ (const char *) ". mD.",
                     /* alt  */ (const char *) ".   .",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".x...",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) "...x.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".x...",
                     /* alt  */ (const char *) ".xx..",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".x...",
                     /* alt  */ (const char *) "..x..",
                     /* alt  */ (const char *) "...x.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) "..x..",
                     /* alt  */ (const char *) "..x..",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) ".x.x.",
                     /* alt  */ (const char *) ".x.x.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".CCC.",
                     /* alt  */ (const char *) ".C$C.",
                     /* alt  */ (const char *) ".CCC.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".x.x.",
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".x.x.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".x.x.",
                     /* alt  */ (const char *) "..|..",
                     /* alt  */ (const char *) ".x.x.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".xCx.",
                     /* alt  */ (const char *) ".C|C.",
                     /* alt  */ (const char *) ".xCx.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "..~..",
                     /* alt  */ (const char *) ".x~x.",
                     /* alt  */ (const char *) "~~|~~",
                     /* alt  */ (const char *) ".x~x.",
                     /* alt  */ (const char *) "..~..", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) ".xmx.",
                     /* alt  */ (const char *) ".xsx.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) "..xx.",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) ".xx..",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) "..x..",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) "..x..",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".LLL.",
                     /* alt  */ (const char *) ".L|L.",
                     /* alt  */ (const char *) ".LLL.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) "..mx.",
                     /* alt  */ (const char *) "...x.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) "...x.",
                     /* alt  */ (const char *) "..gx.",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".|.|.",
                     /* alt  */ (const char *) "..m..",
                     /* alt  */ (const char *) ".|.|.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".CCm.",
                     /* alt  */ (const char *) ".CCC.",
                     /* alt  */ (const char *) "..CC.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".LLm.",
                     /* alt  */ (const char *) ".LLL.",
                     /* alt  */ (const char *) "..LL.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".~~m.",
                     /* alt  */ (const char *) ".~~~.",
                     /* alt  */ (const char *) "..~~.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) "..m..",
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) "..M..",
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".x.x.",
                     /* alt  */ (const char *) "..g..",
                     /* alt  */ (const char *) ".x.x.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_V_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) ".gxg.",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_VV_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".xxx.",
                     /* alt  */ (const char *) ".gxg.",
                     /* alt  */ (const char *) ".xgx.",
                     /* alt  */ (const char *) ".....", nullptr);
    fragment_alt_add(g, CHANCE_VVV_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) ".....",
                     /* alt  */ (const char *) ".xgx.",
                     /* alt  */ (const char *) ".gxg.",
                     /* alt  */ (const char *) ".xgx.",
                     /* alt  */ (const char *) ".....", nullptr);
  }

  if (fragment_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                   /* frag   */ (const char *) "x...x",
                   /* frag   */ (const char *) "x...x",
                   /* frag   */ (const char *) "x...x",
                   /* frag   */ (const char *) "x...x",
                   /* frag   */ (const char *) "x...x", nullptr)) {
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "B...B",
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "B...B",
                     /* alt  */ (const char *) "x...x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "|...|",
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "|...|",
                     /* alt  */ (const char *) "x...x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "xx.xx",
                     /* alt  */ (const char *) "xxCxx",
                     /* alt  */ (const char *) "xx.xx",
                     /* alt  */ (const char *) "x...x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "xxCxx",
                     /* alt  */ (const char *) "xx.xx",
                     /* alt  */ (const char *) "xxCxx",
                     /* alt  */ (const char *) "x...x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "xC=Cx",
                     /* alt  */ (const char *) "xC=Cx",
                     /* alt  */ (const char *) "xC=Cx",
                     /* alt  */ (const char *) "x...x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "xx.xx",
                     /* alt  */ (const char *) "xxtxx",
                     /* alt  */ (const char *) "xx.xx",
                     /* alt  */ (const char *) "x...x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "xx.xx",
                     /* alt  */ (const char *) "xx.xx",
                     /* alt  */ (const char *) "xx.xx",
                     /* alt  */ (const char *) "x...x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "xx.xx",
                     /* alt  */ (const char *) "xxmxx",
                     /* alt  */ (const char *) "xx.xx",
                     /* alt  */ (const char *) "x...x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "x.xxx",
                     /* alt  */ (const char *) "x.s$x",
                     /* alt  */ (const char *) "x.xxx",
                     /* alt  */ (const char *) "x...x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "xxx.x",
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "x.xxx",
                     /* alt  */ (const char *) "x...x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x...x",
                     /* alt  */ (const char *) "xxx.x",
                     /* alt  */ (const char *) "x.C.x",
                     /* alt  */ (const char *) "x.xxx",
                     /* alt  */ (const char *) "x...x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x.~.x",
                     /* alt  */ (const char *) "x~~~x",
                     /* alt  */ (const char *) "x~~~x",
                     /* alt  */ (const char *) "x~~~x",
                     /* alt  */ (const char *) "x.~.x", nullptr);
  }

  if (fragment_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                   /* frag   */ (const char *) "x..x",
                   /* frag   */ (const char *) "x..x",
                   /* frag   */ (const char *) "x..x",
                   /* frag   */ (const char *) "x..x",
                   /* frag   */ (const char *) "x..x", nullptr)) {
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x..x",
                     /* alt  */ (const char *) "B..B",
                     /* alt  */ (const char *) "x..x",
                     /* alt  */ (const char *) "B..B",
                     /* alt  */ (const char *) "x..x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x..x",
                     /* alt  */ (const char *) "|..|",
                     /* alt  */ (const char *) "x..x",
                     /* alt  */ (const char *) "|..|",
                     /* alt  */ (const char *) "x..x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x..x",
                     /* alt  */ (const char *) "x.Cx",
                     /* alt  */ (const char *) "xCCx",
                     /* alt  */ (const char *) "xC.x",
                     /* alt  */ (const char *) "x..x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x..x",
                     /* alt  */ (const char *) "xx.x",
                     /* alt  */ (const char *) "x..x",
                     /* alt  */ (const char *) "x.xx",
                     /* alt  */ (const char *) "x..x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "x~~x",
                     /* alt  */ (const char *) "xx~x",
                     /* alt  */ (const char *) "x~~x",
                     /* alt  */ (const char *) "x~xx",
                     /* alt  */ (const char *) "x~~x", nullptr);
  }

  if (fragment_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                   /* frag   */ (const char *) "?xx?",
                   /* frag   */ (const char *) ".^^.",
                   /* frag   */ (const char *) "?xx?", nullptr)) {
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) " xx ",
                     /* alt  */ (const char *) "....",
                     /* alt  */ (const char *) " xx ", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) " xx ",
                     /* alt  */ (const char *) ".D..",
                     /* alt  */ (const char *) " xx ", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) " xx ",
                     /* alt  */ (const char *) ".##.",
                     /* alt  */ (const char *) " xx ", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) " xx ",
                     /* alt  */ (const char *) ".DC.",
                     /* alt  */ (const char *) " xx ", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) " x| ",
                     /* alt  */ (const char *) ".D..",
                     /* alt  */ (const char *) " x| ", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) " xB ",
                     /* alt  */ (const char *) ".D..",
                     /* alt  */ (const char *) " xB ", nullptr);
  }

  if (fragment_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                   /* frag   */ (const char *) "...",
                   /* frag   */ (const char *) "...",
                   /* frag   */ (const char *) "...", nullptr)) {
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) ".x.",
                     /* alt  */ (const char *) "...", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) ".|.",
                     /* alt  */ (const char *) "...", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) ".m.",
                     /* alt  */ (const char *) "...", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) ".g.",
                     /* alt  */ (const char *) "...", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) ".M.",
                     /* alt  */ (const char *) "...", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) ".G.",
                     /* alt  */ (const char *) "...", nullptr);
  }

  if (fragment_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                   /* frag   */ (const char *) "~=~",
                   /* frag   */ (const char *) "~=~",
                   /* frag   */ (const char *) "~=~",
                   /* frag   */ (const char *) "~=~",
                   /* frag   */ (const char *) "~=~",
                   /* frag   */ (const char *) "~=~",
                   /* frag   */ (const char *) "~=~", nullptr)) {
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "B.B",
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) "B.B",
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "~=~", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "~m~",
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "~=~", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "~.~",
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "~=~", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "~~~",
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "~=~",
                     /* alt  */ (const char *) "~=~", nullptr);
  }

  if (fragment_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                   /* frag   */ (const char *) "C=C",
                   /* frag   */ (const char *) "C=C",
                   /* frag   */ (const char *) "C=C",
                   /* frag   */ (const char *) "C=C",
                   /* frag   */ (const char *) "C=C",
                   /* frag   */ (const char *) "C=C",
                   /* frag   */ (const char *) "C=C", nullptr)) {
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "C=C",
                     /* alt  */ (const char *) "C=C",
                     /* alt  */ (const char *) "B.B",
                     /* alt  */ (const char *) "...",
                     /* alt  */ (const char *) "B.B",
                     /* alt  */ (const char *) "C=C",
                     /* alt  */ (const char *) "C=C", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "C=C",
                     /* alt  */ (const char *) "C=C",
                     /* alt  */ (const char *) "C=C",
                     /* alt  */ (const char *) "CmC",
                     /* alt  */ (const char *) "C=C",
                     /* alt  */ (const char *) "C=C",
                     /* alt  */ (const char *) "C=C", nullptr);
    fragment_alt_add(g, CHANCE_UNLIKELY, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "C=C",
                     /* alt  */ (const char *) "C=C",
                     /* alt  */ (const char *) "C.C",
                     /* alt  */ (const char *) "CCC",
                     /* alt  */ (const char *) "C.C",
                     /* alt  */ (const char *) "C=C",
                     /* alt  */ (const char *) "C=C", nullptr);
  }

  if (fragment_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                   /* frag   */ (const char *) "xxxxxxx",
                   /* frag   */ (const char *) "x.....x",
                   /* frag   */ (const char *) "x.....x",
                   /* frag   */ (const char *) "x.....x",
                   /* frag   */ (const char *) "x.....x",
                   /* frag   */ (const char *) "x.....x", nullptr)) {
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "B..g..B",
                     /* alt  */ (const char *) ".......",
                     /* alt  */ (const char *) ".B...B$",
                     /* alt  */ (const char *) "xxCCCxx",
                     /* alt  */ (const char *) "xB...Bx",
                     /* alt  */ (const char *) "x.....x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "B..G..B",
                     /* alt  */ (const char *) ".......",
                     /* alt  */ (const char *) ".B...B$",
                     /* alt  */ (const char *) "xxCCCxx",
                     /* alt  */ (const char *) "xxCCCxx",
                     /* alt  */ (const char *) "x.....x", nullptr);
    fragment_alt_add(g, CHANCE_NORMAL, __FUNCTION__, __LINE__,
                     /* alt  */ (const char *) "B..gxx.",
                     /* alt  */ (const char *) "....s..",
                     /* alt  */ (const char *) "B...x.$",
                     /* alt  */ (const char *) "xxxDxxx",
                     /* alt  */ (const char *) "x.B.B.x",
                     /* alt  */ (const char *) "x.....x", nullptr);
  }
}
