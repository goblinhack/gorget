//
// from https://gist.github.com/tom-seddon/5171093
//
#ifdef _WIN32
// clang-format off
#include <stdio.h>   
#include <windows.h> 
#include <shlwapi.h> 
#include <winbase.h> 
#include <dbghelp.h>
// clang-format on

static int g_symInitialised;
static int g_symInitWorked;

char **backtrace_symbols(void *const *array, size_t size)
{
  size_t i, symbols_size;
  char **symbols;

  if (! g_symInitialised) {
    g_symInitWorked  = SymInitialize(GetCurrentProcess(), 0, TRUE);
    g_symInitialised = 1;
  }

  symbols_size = size * sizeof(char *);
  symbols      = (char **) malloc(symbols_size);
  if (! symbols)
    return NULL;

  for (i = 0; i < size; ++i)
    symbols[ i ] = NULL;

  for (i = 0; i < size; ++i) {
    // don't much care if the expansion is any longer than this...
    char line[ 1000 ], **new_symbols;

    if (! g_symInitWorked) {
    hex_only:;
      _snprintf(line, sizeof line, "0x%p", array[ i ]);
    } else {
      IMAGEHLP_LINE64 ihl;
      DWORD           dwDisp;

      ihl.SizeOfStruct = sizeof ihl;

      if (! SymGetLineFromAddr64(GetCurrentProcess(), (DWORD64) array[ i ], &dwDisp, &ihl))
        goto hex_only;

      _snprintf(line, sizeof line, "%s(%lu)", ihl.FileName, ihl.LineNumber);
    }

    line[ sizeof line - 1 ] = 0;
    size_t line_len         = strlen(line);

    new_symbols = (char **) realloc(symbols, symbols_size + line_len + 1); //+1 for '\x0'
    if (! new_symbols)
      break;

    memcpy((char *) new_symbols + symbols_size, line, line_len + 1);
    new_symbols[ i ] = (char *) symbols_size;

    symbols = new_symbols;
    symbols_size += line_len + 1;
  }

  for (i = 0; i < size; ++i) {
    symbols[ i ] = (char *) symbols + (uintptr_t) symbols[ i ];
  }

  return symbols;
}
#endif
