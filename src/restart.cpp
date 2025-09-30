//
// Copyright goblinhack@gmail.com
//

#include <iostream>
#include <signal.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>

#include "my_test.hpp"
#include "my_wid_console.hpp"

//
// Restart the game, with an optional restart argument to indicate how to restart
//
void restart(Gamep g, std::string restart_arg)
{
  CON("Exiting, restart called");
  TRACE_NO_INDENT();

  char       *executable;
  const char *argv[ MAXSHORTSTR /* in pointers, should be enough */ ];
  int         argc = 0;
  int         i;

  memset(argv, 0, sizeof(argv));

  //
  // Original program name
  //
  executable     = (char *) g_program_name.c_str();
  argv[ argc++ ] = executable;

  //
  // Copy arguments and append any we need
  //
  for (i = 1; i < g_argc; i++) {
    if (strstr(g_argv[ i ], "-restart")) {
      continue;
    }
    argv[ argc++ ] = g_argv[ i ];
  }
  argv[ argc++ ] = restart_arg.c_str();

  //
  // Build the full command line
  //
  std::string argument_line;
  LOG("Command line arguments for restarting '%s'", executable);
  for (i = 1; i < argc; i++) {
    LOG("+ argument: \"%s\"", argv[ i ]);
    argument_line += ' ';
    argument_line += argv[ i ];
  }

  wid_console_flush(g);

  bool use_system;

#ifdef __linux__
  //
  // For some reason SDL audio fails if we use execve
  //
  use_system = true;
#elif _WIN32
  //
  // Windows has spaces in the path name and that ends up being incorrectly
  // split by execve on the 2nd boot. So, just avoid the issue.
  //
  executable = (char *) "gorget.exe";
  use_system = false;
#else
  use_system = false;
#endif

  cleanup();

  if (use_system) {
    char tmp_cmd[ PATH_MAX ];
    snprintf(tmp_cmd, SIZEOF(tmp_cmd), "%s &", argument_line.c_str());
    CON("system(%s)", tmp_cmd);
    int ret = system(tmp_cmd);
    exit(ret);
  }

  argv[ 0 ] = executable;
  CON("execve(%s%s)", executable, argument_line.c_str());
  execve(executable, (char *const *) argv, nullptr);

  DIE("Failed to restart");
}
