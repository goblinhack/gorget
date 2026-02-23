
#ifndef MY_PTRCHECK_HPP
#define MY_PTRCHECK_HPP

#include "my_source_loc.hpp"

//
// __FUNCTION__ is not a preprocessor directive so we can't convert it into a
// string
//
#define PTRCHECK_AT SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM

void ptrcheck_fini();
auto myzalloc_(int size, const char *what, const char *file, const char *func, int line) -> void *;
auto mymalloc_(int size, const char *what, const char *file, const char *func, int line) -> void *;
auto myrealloc_(void *ptr, int size, const char *what, const char *file, const char *func, int line) -> void *;
void myfree_(void *ptr, const char *file, const char *func, int line);
auto mydupstr_(const char *in, const char *what, const char *file, const char *func, int line) -> char *;
auto strsub_(const char *in, const char *look_for, const char *replace_with, const char *what, const char *file, const char *func, int line)
    -> char *;

#define myzalloc(__size__, __what__) myzalloc_((__size__), (__what__), PTRCHECK_AT)

#define mymalloc(__size__, __what__) mymalloc_((__size__), (__what__), PTRCHECK_AT)

#define myrealloc(__ptr__, __size__, __what__) myrealloc_((__ptr__), (__size__), (__what__), PTRCHECK_AT)

#define myfree(__ptr__) myfree_((__ptr__), PTRCHECK_AT)

#define mydupstr(__ptr__, __what__) mydupstr_((__ptr__), (__what__), PTRCHECK_AT)

#define strsub(a, b, c, __what__) strsub_(a, b, c, (__what__), PTRCHECK_AT)

auto ptrcheck_alloc(int mtype, const void *ptr, const char *what, int size, const char *func, const char *file, int line) -> void *;
auto ptrcheck_VERIFY(int mtype, const void *ptr, const char *func, const char *file, int line) -> int;
auto ptrcheck_free(int mtype, void *ptr, const char *func, const char *file, int line) -> int;
void ptrcheck_leak_print(int mtype);
void ptrcheck_leak_print();

//
// MUST use DEBUG2 else "set debug on" gets confused as it never learned pointers.
//
#define NEWPTR(__mtype__, __ptr__, __what__)                                                                                               \
  {                                                                                                                                        \
    if (DEBUG2) {                                                                                                                          \
      TRACE_NO_INDENT();                                                                                                                   \
      ptrcheck_alloc(__mtype__, __ptr__, __what__, sizeof(*(__ptr__)), PTRCHECK_AT);                                                       \
    }                                                                                                                                      \
  }

#define OLDPTR(__mtype__, __ptr__)                                                                                                         \
  {                                                                                                                                        \
    if (DEBUG2) {                                                                                                                          \
      TRACE_NO_INDENT();                                                                                                                   \
      ptrcheck_free(__mtype__, __ptr__, PTRCHECK_AT);                                                                                      \
    }                                                                                                                                      \
  }

#define VERIFY(__mtype__, __ptr__)                                                                                                         \
  {                                                                                                                                        \
    if (DEBUG2) {                                                                                                                          \
      TRACE_NO_INDENT();                                                                                                                   \
      ptrcheck_VERIFY(__mtype__, __ptr__, SRC_FILE_NAME, SRC_FUNC_NAME, SRC_LINE_NUM);                                                     \
    }                                                                                                                                      \
  }

enum {
  MTYPE_SDL,
  MTYPE_LIGHT,
  MTYPE_MISC,
  MTYPE_TEX,
  MTYPE_TILE,
  MTYPE_TP,
  MTYPE_WID,
  MTYPE_LEVELS,
  MTYPE_GAME,
  MTYPE_MAX,
};

#endif // MY__PTRCHECK_HPP_
