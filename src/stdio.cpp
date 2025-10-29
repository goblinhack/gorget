//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_sprintf.hpp"

//
// Remap stdout to a file of our choosing.
//
// This can be done for a thread also.
//
FILE *redirect_stdout(void)
{
  if (likely(g_log_stdout != nullptr)) {
    return g_log_stdout;
  }

  TRACE_NO_INDENT();

  const char *appdata;
  appdata = getenv("APPDATA");
  if (! appdata || ! appdata[ 0 ]) {
    appdata = "appdata";
  }

  std::string out;
  if (g_thread_id != -1) {
    out = string_sprintf("%s%s%s%s%s.level.%d", appdata, DIR_SEP, "gorget", DIR_SEP, "stdout.txt", g_thread_id);
    g_log_stdout = fopen(out.c_str(), "w");
  } else {
    out                   = string_sprintf("%s%s%s%s%s", appdata, DIR_SEP, "gorget", DIR_SEP, "stdout.txt");
    g_log_stdout_filename = out;
    g_log_stdout          = fopen(out.c_str(), "w+");
  }

  //
  // If we failed to create, try a local file
  //
  if (! g_log_stdout) {
    if (g_thread_id != -1) {
      out          = string_sprintf("%s.level.%d", "gorget.stdout.txt", g_thread_id);
      g_log_stdout = fopen(out.c_str(), "w");
    } else {
      out                   = "gorget.stdout.txt";
      g_log_stdout_filename = out;
      g_log_stdout          = fopen(out.c_str(), "w+");
    }

    //
    // Last resort
    //
    if (! g_log_stdout) {
      g_log_stdout = stdout;
    }
  }

  return g_log_stdout;
}

//
// Remap stderr to a file of our choosing.
//
// This can be done for a thread also.
//
FILE *redirect_stderr(void)
{
  if (likely(g_log_stderr != nullptr)) {
    return g_log_stderr;
  }

  TRACE_NO_INDENT();

  const char *appdata;
  appdata = getenv("APPDATA");
  if (! appdata || ! appdata[ 0 ]) {
    appdata = "appdata";
  }

  std::string out;
  if (g_thread_id != -1) {
    out = string_sprintf("%s%s%s%s%s.level.%d", appdata, DIR_SEP, "gorget", DIR_SEP, "stderr.txt", g_thread_id);
    g_log_stderr = fopen(out.c_str(), "w");
  } else {
    out                   = string_sprintf("%s%s%s%s%s", appdata, DIR_SEP, "gorget", DIR_SEP, "stderr.txt");
    g_log_stderr_filename = out;
    g_log_stderr          = fopen(out.c_str(), "w+");
  }

  //
  // If we failed to create, try a local file
  //
  if (! g_log_stderr) {
    if (g_thread_id != -1) {
      out          = string_sprintf("%s.level.%d", "gorget.stderr.txt", g_thread_id);
      g_log_stderr = fopen(out.c_str(), "w");
    } else {
      out                   = "gorget.stderr.txt";
      g_log_stderr_filename = out;
      g_log_stderr          = fopen(out.c_str(), "w+");
    }

    //
    // Last resort
    //
    if (! g_log_stderr) {
      g_log_stderr = stderr;
    }
  }

  return g_log_stderr;
}
