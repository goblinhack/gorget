//
// Copyright goblinhack@gmail.com
//
//
#include "my_backtrace.hpp"
#include "my_main.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"

#include <errno.h>
#include <iostream>
#include <string.h>

#ifdef _WIN32
// clang-format off
#include <stdio.h>   
#include <windows.h> 
#include <shlwapi.h> 
#include <winbase.h> 
#include <dbghelp.h>
// clang-format on
extern char **backtrace_symbols(void *const *array, size_t size);
#else
#include <execinfo.h>
#endif
#include <cxxabi.h>
#ifdef HAVE_LIBUNWIND
#include <execinfo.h>
#include <libunwind.h>
#endif
#include <memory>

#include <mutex>

static std::recursive_mutex backtrace_mutex;

void Backtrace::init(void)
{
  // clang-format off
#ifdef HAVE_LIBUNWIND
#  ifdef _WIN32
  size = 0; // Just did not seem to work on mingw
#  else
#    ifdef LIBUNWIND_HAS_UNW_BACKTRACE
  size = unw_backtrace(&bt[ 0 ], bt.size());
#    else
  size = backtrace(&bt[ 0 ], bt.size());
#    endif
#  endif
#else
#  ifdef _WIN32
  size = 0;
#  else
  size = backtrace(&bt[ 0 ], bt.size());
#  endif
#endif
  // clang-format on
}

//
// Inspired from https://github.com/nico/demumble/issues
//
static bool starts_with(const char *s, const char *prefix) { return strncmp(s, prefix, strlen(prefix)) == 0; }

static bool is_mangle_char_posix(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

static bool is_mangle_char_win(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || strchr("?_@$", c);
}

static bool is_plausible_itanium_prefix(char *s)
{
  // Itanium symbols start with 1-4 underscores followed by Z.
  // strnstr() is BSD, so use a small local buffer and strstr().
  const int N = 5; // == strlen("____Z")
  char      prefix[ N + 1 ];
  my_strlcpy(prefix, s, N);
  prefix[ N ] = '\0';
  return strstr(prefix, "_Z");
}

//
// See
// https://stackoverflow.com/questions/4939636/function-to-mangle-demangle-functions
//
// See also c++filt e.g.:
//
// c++filt -n _ZNK3MapI10StringName3RefI8GDScriptE10ComparatorIS0_E16DefaultAllocatorE3hasERKS0_
// Map<StringName, Ref<GDScript>, Comparator<StringName>, DefaultAllocator>::has(StringName const&) const
//
static auto cppDemangle(const char *abiName)
{
  //
  // This function allocates and returns storage in ret
  //
  int   status;
  char *ret = abi::__cxa_demangle(abiName, nullptr /* output buffer */, nullptr /* length */, &status);

  auto deallocator = ([](char *mem) {
    if (mem)
      free((void *) mem);
  });

  if (status) {
    // 0: The demangling operation succeeded.
    // -1: A memory allocation failure occurred.
    // -2: mangled_name is not a valid name under the C++ ABI mangling rules.
    // -3: One of the arguments is invalid.
    std::unique_ptr< char, decltype(deallocator) > retval(nullptr, deallocator);
    return retval;
  }

  //
  // Create a unique pointer to take ownership of the returned string so it
  // is freed when that pointers goes out of scope
  //
  std::unique_ptr< char, decltype(deallocator) > retval(ret, deallocator);
  return retval;
}

std::string Backtrace::to_string(void)
{
  backtrace_mutex.lock();
  auto        addrlist = &bt[ 0 ];
  std::string sout     = "stack trace\n===========\n";

  if (size == 0) {
    sout += "  <empty, possibly corrupt>\n";
    backtrace_mutex.unlock();
    return sout;
  }

  // resolve addresses into strings containing "filename(function+address)",
  // this array must be free()-ed
  char      **symbollist = backtrace_symbols(addrlist, size);
  const char *prefix     = " >";

  // address of this function.
  for (int i = size - 1; i >= 0; i--) {

    char *p    = symbollist[ i ];
    char *cur  = p;
    char *end  = p + strlen(cur);
    bool  done = false;

    while (cur < end) {
      size_t special = strcspn(cur, "_?");
      cur += special;

      if (cur >= end) {
        break;
      }

      size_t n_sym = 0;
      if (*cur == '?') {
        while (cur + n_sym != end && is_mangle_char_win(cur[ n_sym ])) {
          ++n_sym;
        }
      } else if (is_plausible_itanium_prefix(cur)) {
        while (cur + n_sym != end && is_mangle_char_posix(cur[ n_sym ])) {
          ++n_sym;
        }
      } else {
        ++cur;
        continue;
      }

      char tmp     = cur[ n_sym ];
      cur[ n_sym ] = '\0';

      if (starts_with(cur, "__Z")) {
        cur++;
      }

      auto demangled = cppDemangle(cur);
      if (demangled) {
        sout += string_sprintf("%s %s\n", prefix, demangled.get());
        done = true;
        break;
      }

      cur[ n_sym ] = tmp;
      cur += n_sym;
    }

    if (! done) {
      sout += string_sprintf("%s%s\n", prefix, p);
    }
  }

  sout += string_sprintf("end-of-stack\n");

  free(symbollist);

  backtrace_mutex.unlock();
  return sout;
}

void Backtrace::log(void)
{
  backtrace_mutex.lock();
  auto addrlist = &bt[ 0 ];

  LOG("stack trace");
  LOG("===========");

  if (size == 0) {
    LOG("  <empty, possibly corrupt>");
    backtrace_mutex.unlock();
    return;
  }

  // resolve addresses into strings containing "filename(function+address)",
  // this array must be free()-ed
  char      **symbollist = backtrace_symbols(addrlist, size);
  const char *prefix     = " >";

  // address of this function.
  for (int i = 1; i < size; i++) {

    char *p    = symbollist[ i ];
    char *cur  = p;
    char *end  = p + strlen(cur);
    bool  done = false;

    while (cur < end) {
      size_t special = strcspn(cur, "_?");
      cur += special;

      if (cur >= end) {
        break;
      }

      size_t n_sym = 0;
      if (*cur == '?') {
        while (cur + n_sym != end && is_mangle_char_win(cur[ n_sym ])) {
          ++n_sym;
        }
      } else if (is_plausible_itanium_prefix(cur)) {
        while (cur + n_sym != end && is_mangle_char_posix(cur[ n_sym ])) {
          ++n_sym;
        }
      } else {
        ++cur;
        continue;
      }

      char tmp     = cur[ n_sym ];
      cur[ n_sym ] = '\0';

      if (starts_with(cur, "__Z")) {
        cur++;
      }

      auto demangled = cppDemangle(cur);
      if (demangled) {
        LOG("%s%u %s", prefix, i, demangled.get());
        done = true;
        break;
      }

      cur[ n_sym ] = tmp;
      cur += n_sym;
    }

    if (! done) {
      LOG("%s%s", prefix, p);
    }
  }

  LOG("end-of-stack");

  free(symbollist);
  backtrace_mutex.unlock();
}

#ifdef _WIN32

static void PrintLastError(const char *msg)
{
  DWORD errCode = GetLastError();
  char *err;
  if (! FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, errCode,
                      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
                      (LPTSTR) &err, 0, NULL))
    return;

  static char buffer[ 1024 * 32 ];
  snprintf(buffer, sizeof(buffer), "ERROR: %s: %s\n", msg, err);
  OutputDebugString(buffer);
  LocalFree(err);
}

std::string backtrace_string(void)
{
  backtrace_mutex.lock();
  std::string out = "stack trace\n===========\n";

  HANDLE        thread            = GetCurrentThread();
  HANDLE        handle            = GetCurrentProcess();
  constexpr int frames_to_capture = 16;

  if (! SymInitialize(handle, nullptr, true)) {
    DWORD error = GetLastError();
    auto  ret   = string_sprintf("SymInitialize: failed, errno = %d: %s\n", (int) error, strerror((int) error));
    backtrace_mutex.unlock();
    return ret.c_str();
  }

  SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES);

  bool do_stackwalk = false;
  if (do_stackwalk) {
    CONTEXT context;
    memset(&context, 0, sizeof(CONTEXT));
    context.ContextFlags = CONTEXT_FULL;
    RtlCaptureContext(&context);

    DWORD        imageType;
    STACKFRAME64 stackframe;
    memset(&stackframe, 0, sizeof(stackframe));

#ifdef _M_IX86
    // normally, call ImageNtHeader() and use machine info from PE header
    imageType                   = IMAGE_FILE_MACHINE_I386;
    stackframe.AddrPC.Offset    = context.Eip;
    stackframe.AddrPC.Mode      = AddrModeFlat;
    stackframe.AddrFrame.Offset = context.Ebp;
    stackframe.AddrFrame.Mode   = AddrModeFlat;
    stackframe.AddrStack.Offset = context.Esp;
    stackframe.AddrStack.Mode   = AddrModeFlat;
#elif _M_X64
    imageType                   = IMAGE_FILE_MACHINE_AMD64;
    stackframe.AddrPC.Offset    = context.Rip;
    stackframe.AddrPC.Mode      = AddrModeFlat;
    stackframe.AddrFrame.Offset = context.Rsp;
    stackframe.AddrFrame.Mode   = AddrModeFlat;
    stackframe.AddrStack.Offset = context.Rsp;
    stackframe.AddrStack.Mode   = AddrModeFlat;
#elif _M_IA64
    imageType                    = IMAGE_FILE_MACHINE_IA64;
    stackframe.AddrPC.Offset     = context.StIIP;
    stackframe.AddrPC.Mode       = AddrModeFlat;
    stackframe.AddrFrame.Offset  = context.IntSp;
    stackframe.AddrFrame.Mode    = AddrModeFlat;
    stackframe.AddrBStore.Offset = context.RsBSP;
    stackframe.AddrBStore.Mode   = AddrModeFlat;
    stackframe.AddrStack.Offset  = context.IntSp;
    stackframe.AddrStack.Mode    = AddrModeFlat;
#elif _M_ARM64
    imageType                   = IMAGE_FILE_MACHINE_ARM64;
    stackframe.AddrPC.Offset    = context.Pc;
    stackframe.AddrPC.Mode      = AddrModeFlat;
    stackframe.AddrFrame.Offset = context.Fp;
    stackframe.AddrFrame.Mode   = AddrModeFlat;
    stackframe.AddrStack.Offset = context.Sp;
    stackframe.AddrStack.Mode   = AddrModeFlat;
#else
#error "Platform not supported!"
#endif

    for (int i = 0; i < frames_to_capture; i++) {
      BOOL result = StackWalk64(imageType, handle, thread, &stackframe, &context, NULL, SymFunctionTableAccess64,
                                SymGetModuleBase64, NULL);
      if (! result) {
        out += string_sprintf("StackWalk[end]\n");
        break;
      }

      char         buffer[ sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR) ];
      PSYMBOL_INFO symbol  = (PSYMBOL_INFO) buffer;
      symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
      symbol->MaxNameLen   = MAX_SYM_NAME;

      DWORD64 displacement = 0;
      if (SymFromAddr(handle, stackframe.AddrPC.Offset, &displacement, symbol)) {
        out += string_sprintf("StackWalk[%d]: sym:%s\n", i, symbol->Name);
      }
    }
  }

#define MAX_SYMBOL_LEN 1024

  char         symbol_mem[ SIZEOF(SYMBOL_INFO) + MAX_SYMBOL_LEN * SIZEOF(TCHAR) ];
  SYMBOL_INFO *symbol  = (SYMBOL_INFO *) symbol_mem;
  symbol->MaxNameLen   = MAX_SYMBOL_LEN;
  symbol->SizeOfStruct = SIZEOF(SYMBOL_INFO);

  IMAGEHLP_LINE64 line = {};
  line.SizeOfStruct    = sizeof(IMAGEHLP_LINE64);

  std::array< void *, frames_to_capture > frames;
  int                                     frames_to_skip = 0;
  int frame_count = CaptureStackBackTrace(frames_to_skip, frames_to_capture, frames.data(), NULL);

  for (int i = 0; i < frame_count; i++) {
    DWORD64 addr = (DWORD64) frames[ i ];

    const char *file          = "<no-file>";
    const char *function_name = "<no-function>";
    int         line_number   = -1;
    DWORD       displacement  = 0;

    if (SymGetLineFromAddr64(handle, addr, &displacement, &line)) {
      file        = line.FileName;
      line_number = (int) line.LineNumber;
    }

    if (SymFromAddr(handle, addr, nullptr, symbol)) {
      function_name = symbol->Name;
    }

    out += string_sprintf("CaptureStackBackTrace[%d]: %s() %s:%d\n", i - frames_to_skip, function_name, file,
                          line_number);
  }

  PrintLastError(out.c_str());
  // __debugbreak();

  SymCleanup(handle);
  CloseHandle(thread);

  backtrace_mutex.unlock();
  return out;
}
#else
std::string backtrace_string(void)
{
  backtrace_mutex.lock();
  auto bt = new Backtrace();
  bt->init();
  auto ret = bt->to_string();
  delete bt;
  backtrace_mutex.unlock();
  return ret;
}
#endif

void backtrace_dump_stderr(void)
{
  backtrace_mutex.lock();
  auto bt = backtrace_string();

  fprintf(stderr, "%s", bt.c_str());
  backtrace_mutex.unlock();
}

void backtrace_dump(void)
{
  backtrace_mutex.lock();
  auto bt = backtrace_string();

  fprintf(MY_STDERR, "%s", bt.c_str());
  backtrace_mutex.unlock();
}
