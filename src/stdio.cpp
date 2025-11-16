//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_globals.hpp"
#include "my_sprintf.hpp"

#include <errno.h>
#include <string.h>

//
// Remap stdout to a file of our choosing.
//
// This can be done for a thread also.
//
FILE *redirect_stdout(void)
{
#if 0
  //
  // Useful if github tests fail
  //
  g_log_stdout = stdout;
#endif

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
  } else {
    out = string_sprintf("%s%s%s%s%s", appdata, DIR_SEP, "gorget", DIR_SEP, "stdout.txt");
  }
  g_log_stdout_filename = out;
  g_log_stdout          = fopen(out.c_str(), "w+");

  //
  // If we failed to create, try a local file
  //
  if (! g_log_stdout) {
    if (g_thread_id != -1) {
      out = string_sprintf("%s.level.%d", "gorget.stdout.txt", g_thread_id);
    } else {
      out = "gorget.stdout.txt";
    }
    g_log_stdout_filename = out;
    g_log_stdout          = fopen(out.c_str(), "w+");

    //
    // Last resort
    //
    if (! g_log_stdout) {
      fprintf(stderr, "Failed to create stdout log file \"%s\" for thread %d, error: %s\n", out.c_str(), g_thread_id,
              strerror(errno));
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
#if 0
  //
  // Useful if github tests fail
  //
  g_log_stderr = stderr;
#endif

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
  } else {
    out = string_sprintf("%s%s%s%s%s", appdata, DIR_SEP, "gorget", DIR_SEP, "stderr.txt");
  }
  g_log_stderr_filename = out;
  g_log_stderr          = fopen(out.c_str(), "w+");

  //
  // If we failed to create, try a local file
  //
  if (! g_log_stderr) {
    if (g_thread_id != -1) {
      out = string_sprintf("%s.level.%d", "gorget.stderr.txt", g_thread_id);
    } else {
      out = "gorget.stderr.txt";
    }
    g_log_stderr_filename = out;
    g_log_stderr          = fopen(out.c_str(), "w+");

    //
    // Last resort
    //
    if (! g_log_stderr) {
      fprintf(stderr, "Failed to create stderr log file \"%s\" for thread %d, error: %s\n", out.c_str(), g_thread_id,
              strerror(errno));
      g_log_stderr = stderr;
    }
  }

  return g_log_stderr;
}

//
// Close the per thread file handle
//
void close_stdout(void)
{
  if (g_log_stdout && (g_log_stdout != stdout)) {
    fclose(g_log_stdout);
    g_log_stdout = nullptr;
  }
}

//
// Close the per thread file handle
//
void close_stderr(void)
{
  if (g_log_stderr && (g_log_stderr != stderr)) {
    fclose(g_log_stderr);
    g_log_stderr = nullptr;
  }
}
