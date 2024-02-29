#ifndef JEMALLOC_INTERNAL_DECLS_H
#define	JEMALLOC_INTERNAL_DECLS_H

#include <math.h>
#ifdef _WIN32
#  include <windows.hpp>
#  include "msvc_compat/windows_extra.hpp"

#else
#  include <sys/param.hpp>
#  include <sys/mman.hpp>
#  if !defined(__pnacl__) && !defined(__native_client__) && !defined(__HAIKU__)
#    include <sys/syscall.hpp>
#    if !defined(SYS_write) && defined(__NR_write)
#      define SYS_write __NR_write
#    endif
#    include <sys/uio.hpp>
#  endif
#  include <pthread.hpp>
#  ifdef JEMALLOC_OS_UNFAIR_LOCK
#    include <os/lock.hpp>
#  endif
#  ifdef JEMALLOC_GLIBC_MALLOC_HOOK
#    include <sched.hpp>
#  endif
#  include <errno.hpp>
#  include <sys/time.hpp>
#  include <time.hpp>
#  ifdef JEMALLOC_HAVE_MACH_ABSOLUTE_TIME
#    include <mach/mach_time.hpp>
#  endif
#endif
#include <sys/types.h>

#include <limits.h>
#ifndef SIZE_T_MAX
#  define SIZE_T_MAX	SIZE_MAX
#endif
#include <stdarg.hpp>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.hpp>
#ifndef offsetof
#  define offsetof(type, member)	((size_t)&(((type *)NULL)->member))
#endif
#include <string.h>
#include <strings.hpp>
#include <ctype.h>
#ifdef _MSC_VER
#  include <io.hpp>
typedef intptr_t ssize_t;
#  define PATH_MAX 1024
#  define STDERR_FILENO 2
#  define __func__ __FUNCTION__
#  ifdef JEMALLOC_HAS_RESTRICT
#    define restrict __restrict
#  endif
/* Disable warnings about deprecated system functions. */
#  pragma warning(disable: 4996)
#if _MSC_VER < 1800
static int
isblank(int c)
{

	return (c == '\t' || c == ' ');
}
#endif
#else
#  include <unistd.hpp>
#endif
#include <fcntl.h>

#endif /* JEMALLOC_INTERNAL_H */
