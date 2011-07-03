#ifndef __MASTER_H__
#define __MASTER_H__
/* Should we enable valgrind instrumentation? */
#if defined(USE_VALGRIND) || defined(DEBUG) 
# define VALGRIND 1
#endif /* USE_VALGRIND || DEBUG */

/* 
 * These should be independent of system headers. Used in case we want platform/compiler
 * specific includes
 */
#include "platform/compiler.h"
#include "platform/os.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <locale.h>
#include <errno.h>

#if defined(PLATFORM_DARWIN) || defined(PLATFORM_UNIX)
#include <unistd.h>
#include <sys/mman.h>
#endif

// Concurrency kit stuff
// #include <ck_pr.h>

#include "util/macros.h"
#include "util/trace.h"
#include "util/alloc.h"
#include "util/popcount.h"
#include "util/utlist.h"
#ifdef VALGRIND
#include "vg/memcheck.h"
#else /* VALGRIND */
# define VALGRIND_MAKE_MEM_UNDEFINED(x,y) 0
# define VALGRIND_MAKE_MEM_DEFINED(x,y) 0
# define VALGRIND_DO_QUICK_LEAK_CHECK
#endif /* VALGRIND */

#endif /* __MASTER_H__ */
