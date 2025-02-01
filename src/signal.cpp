//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_string.hpp"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

void callstack_dump(void)
{
  TRACE_AND_INDENT();

  fprintf(MY_STDERR, "code trace\n");
  fprintf(MY_STDERR, "==========\n");
  for (auto depth = 0; depth < g_callframes_depth; depth++) {
    auto iter = &callframes[ depth ];
    fprintf(MY_STDERR, "(trace) %d %s, line %u\n", depth, iter->func, iter->line);
    fflush(MY_STDERR);
  }

  CON("code trace");
  CON("==========");
  for (auto depth = 0; depth < g_callframes_depth; depth++) {
    auto iter = &callframes[ depth ];
    CON("(con-trace) %d %s, line %u", depth, iter->func, iter->line);
  }
}

std::string callstack_string(void)
{
  char tmp[ MAXLONGSTR ];

  *tmp = '\0';

  for (auto depth = 0; depth < g_callframes_depth; depth++) {
    auto iter = &callframes[ depth ];
    snprintf(tmp + strlen(tmp), SIZEOF(tmp) - strlen(tmp), "(strace) %d %s, line %u\n", depth, iter->func,
             iter->line);
  }

  return std::string(tmp);
}

#include <assert.h>
#ifndef _WIN32
#include <sys/wait.h>
#endif
#include <unistd.h>

#if defined(__linux__)
#include <sys/prctl.h>
#endif

#ifndef PATH_MAX
#define PATH_MAX 512
#endif

#if defined __linux__
//
// I can only really get this working with linux
//
static void debug_crash_handler(int sig)
{
  fprintf(stderr, "debug_crash_handler: Error: Signal %d:\n", sig);

  std::string pid_str(std::to_string(getpid()));

  const size_t max_path = PATH_MAX + 1;
  char         prog_name[ max_path ];

#if defined __APPLE__
  auto pid_num = getpid();
  auto ret     = proc_pidpath(pid_num, prog_name, sizeof(prog_name));
  if (ret <= 0) {
    fprintf(stderr, "PID %d: proc_pidpath ();\n", pid_num);
    fprintf(stderr, "    %s\n", strerror(errno));
  } else {
    printf("proc %d: %s\n", pid_num, prog_name);
  }
#elif defined WIN32
  HMODULE module = GetModuleHandleA(nullptr);
  GetModuleFileNameA(module, prog_name, max_path);
#elif defined __linux__
  int ret = readlink("/proc/self/exe", prog_name, max_path - 1);
  if (ret == -1) {
    ERR("debug_crash_handler: Read process name failed");
    return;
  }

  if ((size_t) ret >= max_path) {
    ERR("debug_crash_handler: Symlink too long");
    return;
  }
#endif

#if defined __linux__
  //
  // Permissions for GDB
  //
  prctl(PR_SET_PTRACER, PR_SET_PTRACER_ANY, 0, 0, 0);

  auto child = fork();
  if (! child) {
    //
    // Start GDB
    //
#ifdef __APPLE__
    execl("/usr/bin/lldb", "lldb", "-p", pid_str.c_str(), nullptr);
#else
    execl("/usr/bin/gdb", "gdb", "--batch", "-n", "-ex", "thread apply all bt", prog_name, pid_str.c_str(), nullptr);
#endif
    assert(false && "Debugger failed to exec");
  } else {
    //
    // Wait for the child to stop
    //
    waitpid(child, nullptr, 0);
  }
#endif
}
#endif

void common_error_handler(std::string &tech_support)
{
  TRACE_AND_INDENT();

  extern Gamep game;
  auto         g = game;

  tech_support += "\n";

  auto seed_name = game_seed_name_get(g);
  if (g && seed_name && *seed_name) {
    tech_support += "Seed name: " + std::string(seed_name) + "\n";
  }
  tech_support += "Could you please email goblinhack@gmail.com and attach the following files and trace info?\n";
  tech_support += g_log_stdout_filename;
  tech_support += "\n";
  tech_support += g_log_stderr_filename;
  tech_support += "\n";
  tech_support += "\n";
  tech_support += "Backtrace:";
  tech_support += backtrace_string();
  tech_support += "\n";
  tech_support += "Trace:";
  tech_support += callstack_string();
  tech_support += "\n";
  tech_support += "The goblin responsible for this shall be punished!!!\n";

  SDL_MSG_BOX("%s", tech_support.c_str());
}

void segv_handler(int sig)
{
  TRACE_AND_INDENT();
  std::string tech_support = "Sorry, a crash has occurred!";
  common_error_handler(tech_support);

#if defined __linux__
  debug_crash_handler(sig);
#endif

  DIE("Crashed");
}

void error_handler(const std::string &error_msg)
{
  TRACE_AND_INDENT();

  std::string tech_support = "Sorry, an error has occurred: ";
  tech_support += error_msg;
  common_error_handler(tech_support);
}

void ctrlc_handler(int sig)
{
  TRACE_AND_INDENT();

  fprintf(MY_STDERR, "Interrupted!!!");
  backtrace_dump();
  DIE_CLEAN("Interrupted");
}
