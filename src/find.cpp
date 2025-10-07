//
// Copyright goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_dir.hpp"
#include "my_file.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"

#include <libgen.h>
#include <string.h>
#include <unistd.h>

//
// Find the binary we are running.
//
static void find_executable(void)
{
  TRACE_NO_INDENT();

  char       *parent_dir         = nullptr;
  char       *curr_dir           = nullptr;
  std::string exec_name          = "";
  char       *exec_expanded_name = nullptr;
  char       *path               = nullptr;
  char       *tmp;

  exec_name = mybasename(g_argv[ 0 ], __FUNCTION__);
  LOG("Will use EXEC_NAME as '%s'", exec_name.c_str());

  //
  // Get the current directory, ending in a single /
  //
  curr_dir = dynprintf("%s" DIR_SEP, dir_dot());
  tmp      = strsub(curr_dir, DIR_SEP DIR_SEP, DIR_SEP, "curr_dir");
  myfree(curr_dir);
  curr_dir = tmp;

  //
  // Get the parent directory, ending in a single /
  //
  parent_dir = dynprintf("%s" DIR_SEP, dir_dotdot(dir_dot()));
  tmp        = strsub(parent_dir, DIR_SEP DIR_SEP, DIR_SEP, "parent_dir");
  myfree(parent_dir);
  parent_dir = tmp;

  //
  // Get rid of ../ from the program name and replace with the path.
  //
  exec_expanded_name = mydupstr(g_argv[ 0 ], __FUNCTION__);
  if (*exec_expanded_name == '.') {
    tmp = strsub(exec_expanded_name, ".." DIR_SEP, parent_dir, "exec_expanded_name");
    myfree(exec_expanded_name);
    exec_expanded_name = tmp;
  }

  //
  // Get rid of ./ from the program name.
  //
  if (*exec_expanded_name == '.') {
    tmp = strsub(exec_expanded_name, "." DIR_SEP, "", "exec_expanded_name2");
    myfree(exec_expanded_name);
    exec_expanded_name = tmp;
  }

  //
  // Get rid of any // from the path
  //
  tmp = strsub(exec_expanded_name, DIR_SEP DIR_SEP, DIR_SEP, "exec_expanded_name3");
  myfree(exec_expanded_name);
  exec_expanded_name = tmp;

  //
  // Look in the simplest case first.
  //
  g_exec_full_path_and_name = dynprintf("%s%s", curr_dir, exec_name.c_str());
  if (file_exists(g_exec_full_path_and_name)) {
    g_exec_dir = mydupstr(curr_dir, "exec dir 1");
    goto cleanup;
  }

  myfree(g_exec_full_path_and_name);
  g_exec_full_path_and_name = nullptr;

  //
  // Try the parent dir.
  //
  g_exec_full_path_and_name = dynprintf("%s%s", parent_dir, exec_name.c_str());
  if (file_exists(g_exec_full_path_and_name)) {
    g_exec_dir = mydupstr(parent_dir, "exec dir 2");
    goto cleanup;
  }

  myfree(g_exec_full_path_and_name);
  g_exec_full_path_and_name = nullptr;

  //
  // Try the PATH.
  //
  path = getenv("PATH");
  if (path) {
    char *dir = nullptr;

    path = mydupstr(path, "path");

    for (dir = strtok(path, PATHSEP); dir; dir = strtok(nullptr, PATHSEP)) {
      g_exec_full_path_and_name = dynprintf("%s" DIR_SEP "%s", dir, exec_name.c_str());
      if (file_exists(g_exec_full_path_and_name)) {
        g_exec_dir = dynprintf("%s" DIR_SEP, dir);
        goto cleanup;
      }

      myfree(g_exec_full_path_and_name);
      g_exec_full_path_and_name = nullptr;
    }

    myfree(path);
    path = nullptr;
  }

  g_exec_full_path_and_name = mydupstr(exec_expanded_name, "full path");
  g_exec_dir                = mydupstr(dirname(exec_expanded_name), "exec dir");

cleanup:
  auto new_g_exec_dir = strsub(g_exec_dir, "/", DIR_SEP, "g_exec_dir");
  myfree(g_exec_dir);
  g_exec_dir = new_g_exec_dir;

  DBG2("g_exec_dir set to %s", g_exec_dir);
  DBG2("Parent dir  : \"%s\"", parent_dir);
  DBG2("Curr dir    : \"%s\"", curr_dir);
  DBG2("Full name   : \"%s\"", exec_expanded_name);

  if (path) {
    myfree(path);
  }

  if (exec_expanded_name) {
    myfree(exec_expanded_name);
  }

  if (parent_dir) {
    myfree(parent_dir);
  }

  if (curr_dir) {
    myfree(curr_dir);
  }
}

//
// Find all installed file locations.
//
static void find_exec_dir(void)
{
  TRACE_NO_INDENT();

  find_executable();

  //
  // Make sure the exec dir ends in a /
  //
  auto tmp  = dynprintf("%s" DIR_SEP, g_exec_dir);
  auto tmp2 = strsub(tmp, "//", DIR_SEP, "g_exec_dir");
  auto tmp3 = strsub(tmp2, "\\\\", DIR_SEP, "g_exec_dir");
  auto tmp4 = strsub(tmp3, "/", DIR_SEP, "g_exec_dir");
  auto tmp5 = strsub(tmp4, "\\", DIR_SEP, "g_exec_dir");
  myfree(tmp);
  myfree(tmp2);
  myfree(tmp3);
  myfree(tmp4);
  if (g_exec_dir) {
    myfree(g_exec_dir);
  }
  g_exec_dir = tmp5;

  LOG("Will use g_exec_dir as '%s'", g_exec_dir);
}

//
// Hunt down the data/ dir.
//
static void find_data_dir(void)
{
  TRACE_NO_INDENT();
  g_data_path = dynprintf("%sdata" DIR_SEP, g_exec_dir);
  if (dir_exists(g_data_path)) {
    return;
  }
  myfree(g_data_path);

  g_data_path = dynprintf(".." DIR_SEP "data");
  if (dir_exists(g_data_path)) {
    return;
  }
  myfree(g_data_path);

  g_data_path = mydupstr(g_exec_dir, __FUNCTION__);
}

//
// Hunt down the fonts/ dir.
//
static void find_ttf_dir(void)
{
  TRACE_NO_INDENT();
  g_ttf_path = dynprintf("%sdata" DIR_SEP "ttf" DIR_SEP, g_exec_dir);
  if (dir_exists(g_ttf_path)) {
    return;
  }
  myfree(g_ttf_path);

  g_ttf_path = dynprintf(".." DIR_SEP "data" DIR_SEP "ttf" DIR_SEP);
  if (dir_exists(g_ttf_path)) {
    return;
  }
  myfree(g_ttf_path);

  g_ttf_path = mydupstr(g_exec_dir, __FUNCTION__);
}

//
// Hunt down the gfx/ dir.
//
static void find_gfx_dir(void)
{
  TRACE_NO_INDENT();
  g_gfx_path = dynprintf("%sdata" DIR_SEP "gfx" DIR_SEP, g_exec_dir);
  if (dir_exists(g_gfx_path)) {
    return;
  }
  myfree(g_gfx_path);

  g_gfx_path = dynprintf(".." DIR_SEP "gfx" DIR_SEP);
  if (dir_exists(g_gfx_path)) {
    return;
  }
  myfree(g_gfx_path);

  g_gfx_path = mydupstr(g_exec_dir, __FUNCTION__);
}

//
// Find all installed file locations.
//
void find_file_locations(void)
{
  TRACE_NO_INDENT();

  find_exec_dir();
  find_data_dir();
  find_ttf_dir();
  find_gfx_dir();

  LOG("Gfx path    : \"%s\"", g_gfx_path);
  LOG("Font path   : \"%s\"", g_ttf_path);
}
