//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"

#define __MAIN__

thread_local struct callframe callframes[ MAXCALLFRAME ];
thread_local unsigned char    g_callframes_depth;
thread_local unsigned char    g_callframes_indent;
