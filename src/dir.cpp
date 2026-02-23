//
// Copyright goblinhack@gmail.com
//

#include <cstring>
#include <sys/param.h>
#include <sys/stat.h>
#include <unistd.h>

#include "my_callstack.hpp"
#include "my_dir.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"

/*
 * Does the requested dir exist?
 */
auto dir_exists(const char *indir) -> bool
{
  TRACE_NO_INDENT();
  struct stat buf {};
  char       *dir = nullptr;
  uint8_t     rc  = 0;

  /*
   * msys is crap and unless you remove the / from the end of the name
   * will not think it is a dir.
   */
  dir = MYDUPSTR(indir, "dir");
  strchopc(dir, DIR_SEP_CHAR);

  rc = 0;
  if (stat(dir, &buf) >= 0) {
    rc = S_ISDIR(buf.st_mode);
  }

  MYFREE(dir);

  return static_cast< bool >(rc);
}

/*
 * Given a directory, find out what ./ is.
 */
auto dir_dot() -> char *
{
  TRACE_NO_INDENT();
  static char buf[ MAXPATHLEN ];

  dospath2unix(getcwd(buf, SIZEOF(buf)));

  return buf;
}

/*
 * Remove \ and change to /
 * Given a directory, find out what ../ is.
 */
auto dir_dotdot(char *s) -> char *
{
  TRACE_NO_INDENT();
  uint32_t size = 0;
  char    *end  = nullptr;

  size = (uint32_t) strlen(s);
  if (size <= 1) {
    return s;
  }

  /*
   * Skip trailing /
   */
  end = s + size - 2;
  while ((end >= s) && (*end != '/') && (*end != '\\')) {
    end--;
  }

  *(end + 1) = '\0';

  return dospath2unix(s);
}

/*
 * Remove \ and change to /
 */
auto dospath2unix(char *in) -> char *
{
  TRACE_NO_INDENT();
  char *s = in;

  while (*s != 0) {
    if (*s == '\\') {
      *s = '/';
    }

    s++;
  }

  return in;
}
