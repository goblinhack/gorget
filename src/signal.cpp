//
// Copyright goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_string.hpp"
#include "my_wid_console.hpp"

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

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
  std::string pid_str(std::to_string(getpid()));

  const size_t max_path = PATH_MAX + 1;
  char         prog_name[ max_path ];

#if defined __APPLE__
  auto pid_num = getpid();
  auto ret     = proc_pidpath(pid_num, prog_name, SIZEOF(prog_name));
  if (ret <= 0) {
    fprintf(stderr, "PID %d: proc_pidpath ();\n", pid_num);
    fprintf(stderr, "    %s\n", strerror(errno));
  } else {
    printf("proc %d: %s\n", pid_num, prog_name);
  }
#elif defined(__WIN64__) || defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(_WIN32)               \
    || defined(WIN32) || defined(__WINDOWS_386__) || defined(__CYGWIN__)
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
    if (system("which gdb")) {
      // ignore
    }
    ERR("Debugger failed to exec");
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

static void error_handler_do(std::string &tech_support)
{
  TRACE_NO_INDENT();

  extern Gamep game;
  auto         g = game;

  tech_support += "\n";

  auto seed_name = game_seed_name_get(g);
  if (*seed_name) {
    tech_support += "Seed name: " + std::string(seed_name) + "\n";
  }

  tech_support += "Could you please email goblinhack@gmail.com and attach the following files and trace info?\n";
  tech_support += g_log_stdout_filename;
  tech_support += "\n";
  tech_support += g_log_stderr_filename;
  tech_support += "\n";
  tech_support += "\n";
  tech_support += backtrace_string();
  tech_support += "\n";
  tech_support += callstack_string();
  tech_support += "\n";
  tech_support += "The goblin responsible for this shall be punished!!!\n";

  wid_console_raise(g);

  sdl_msg_box("%s", tech_support.c_str());
}

static const char *signal_str(int sig)
{
  switch (sig) {
#ifdef SIGHUP
    case SIGHUP : return "SIGHUP";
#endif
#ifdef SIGINT
    case SIGINT : return "SIGINT";
#endif
#ifdef SIGQUIT
    case SIGQUIT : return "SIGQUIT";
#endif
#ifdef SIGILL
    case SIGILL : return "SIGILL";
#endif
#ifdef SIGTRAP
    case SIGTRAP : return "SIGTRAP";
#endif
#ifdef SIGABRT
    case SIGABRT : return "SIGABRT";
#endif
#ifdef SIGEMT
    case SIGEMT : return "SIGEMT";
#endif
#ifdef SIGFPE
    case SIGFPE : return "SIGFPE";
#endif
#ifdef SIGKILL
    case SIGKILL : return "SIGKILL";
#endif
#ifdef SIGBUS
    case SIGBUS : return "SIGBUS";
#endif
#ifdef SIGSEGV
    case SIGSEGV : return "SIGSEGV";
#endif
#ifdef SIGSYS
    case SIGSYS : return "SIGSYS";
#endif
#ifdef SIGPIPE
    case SIGPIPE : return "SIGPIPE";
#endif
#ifdef SIGALRM
    case SIGALRM : return "SIGALRM";
#endif
#ifdef SIGTERM
    case SIGTERM : return "SIGTERM";
#endif
#ifdef SIGURG
    case SIGURG : return "SIGURG";
#endif
#ifdef SIGSTOP
    case SIGSTOP : return "SIGSTOP";
#endif
#ifdef SIGTSTP
    case SIGTSTP : return "SIGTSTP";
#endif
#ifdef SIGCONT
    case SIGCONT : return "SIGCONT";
#endif
#ifdef SIGCHLD
    case SIGCHLD : return "SIGCHLD";
#endif
#ifdef SIGTTIN
    case SIGTTIN : return "SIGTTIN";
#endif
#ifdef SIGTTOU
    case SIGTTOU : return "SIGTTOU";
#endif
#ifdef SIGIO
    case SIGIO : return "SIGIO";
#endif
#ifdef SIGXCPU
    case SIGXCPU : return "SIGXCPU";
#endif
#ifdef SIGXFSZ
    case SIGXFSZ : return "SIGXFSZ";
#endif
#ifdef SIGVTALRM
    case SIGVTALRM : return "SIGVTALRM";
#endif
#ifdef SIGPROF
    case SIGPROF : return "SIGPROF";
#endif
#ifdef SIGWINCH
    case SIGWINCH : return "SIGWINCH";
#endif
#ifdef SIGINFO
    case SIGINFO : return "SIGINFO";
#endif
#ifdef SIGUSR1
    case SIGUSR1 : return "SIGUSR1";
#endif
#ifdef SIGUSR2
    case SIGUSR2 : return "SIGUSR2";
#endif
  }

  return "Unknown signal";
}

void crash_handler(int sig)
{
  static bool crashed;

  if (crashed) {
    fprintf(stderr, "\n\nNested crash. Signal %d(%s). Disabling signal handlers...\n", sig, signal_str(sig));
    return;
  }

  crashed = true;

  fprintf(stderr, "\n\nCrashed. Signal %d(%s). Disabling signal handlers...\n", sig, signal_str(sig));
  callstack_dump_stderr();
  backtrace_dump_stderr();

#ifdef SIGSEGV
  signal(SIGSEGV, nullptr);
#endif
#ifdef SIGBUS
  signal(SIGBUS, nullptr);
#endif
#ifdef SIGABRT
  signal(SIGABRT, nullptr);
#endif
#ifdef SIGFPE
  signal(SIGFPE, nullptr);
#endif
#ifdef SIGILL
  signal(SIGILL, nullptr);
#endif
#ifdef SIGPIPE
  signal(SIGPIPE, nullptr);
#endif
#ifdef SIGINT
  signal(SIGINT, nullptr);
#endif

#if defined __linux__
  debug_crash_handler(sig);
#endif

  fprintf(stderr, "\n\nCleaning up after crash...\n");
  fprintf(stderr, "--------------------------\n");

  DIE("Crashed");
}

void error_handler(const std::string &error_msg)
{
  if (g_thread_id != -1) {
    return;
  }

  TRACE_NO_INDENT();

  std::string tech_support = "Sorry, an error has occurred: ";
  tech_support += error_msg;

  error_handler_do(tech_support);
}

void ctrlc_handler(int sig)
{
  fprintf(stderr, "\n\nInterrupted. Signal %d(%s). Disabling signal handlers...\n", sig, signal_str(sig));
  callstack_dump_stderr();
  backtrace_dump_stderr();

#ifdef SIGSEGV
  signal(SIGSEGV, nullptr);
#endif
#ifdef SIGBUS
  signal(SIGBUS, nullptr);
#endif
#ifdef SIGABRT
  signal(SIGABRT, nullptr);
#endif
#ifdef SIGFPE
  signal(SIGFPE, nullptr);
#endif
#ifdef SIGILL
  signal(SIGILL, nullptr);
#endif
#ifdef SIGPIPE
  signal(SIGPIPE, nullptr);
#endif
#ifdef SIGINT
  signal(SIGINT, nullptr);
#endif

  fprintf(stderr, "\n\nInterrupted. Cleaning up...\n");
  fprintf(stderr, "---------------------------\n");

  DIE_CLEAN("Interrupted");
}
