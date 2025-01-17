// SPDX-License-Identifier: LGPL-2.1-or-later
// SPDX-FileCopyrightText: 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald

// Taken from https://github.com/GNOME/glib/blob/main/glib/gconstructor.hpp and adapted to Rizin

#ifndef __RZ_CONSTRUCTOR_H__
#define __RZ_CONSTRUCTOR_H__

/*
  If RZ_HAS_CONSTRUCTORS is true then the compiler support *both* constructors and
  destructors, in a usable way, including e.g. on library unload. If not you're on
  your own.
  Some compilers need #pragma to handle this, which does not work with macros,
  so the way you need to use this is (for constructors):
  #ifdef RZ_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA
  #pragma RZ_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(my_constructor)
  #endif
  RZ_DEFINE_CONSTRUCTOR(my_constructor)
  static void my_constructor(void) {
   ...
  }
*/

#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)

#define RZ_HAS_CONSTRUCTORS 1

#define RZ_DEFINE_CONSTRUCTOR(_func) static void __attribute__((constructor)) _func(void);
#define RZ_DEFINE_DESTRUCTOR(_func)  static void __attribute__((destructor)) _func(void);

#elif defined(_MSC_VER) && (_MSC_VER >= 1500)
/* Visual studio 2008 and later has _Pragma */

#include <stdlib.h>

#define RZ_HAS_CONSTRUCTORS 1

/* We do some weird things to avoid the constructors being optimized
 * away on VS2015 if WholeProgramOptimization is enabled. First we
 * make a reference to the array from the wrapper to make sure its
 * references. Then we use a pragma to make sure the wrapper function
 * symbol is always included at the link stage. Also, the symbols
 * need to be extern (but not dllexport), even though they are not
 * really used from another object file.
 */

/* We need to account for differences between the mangling of symbols
 * for x86 and x64/ARM/ARM64 programs, as symbols on x86 are prefixed
 * with an underscore but symbols on x64/ARM/ARM64 are not.
 */
#ifdef _M_IX86
#define RZ_MSVC_SYMBOL_PREFIX "_"
#else
#define RZ_MSVC_SYMBOL_PREFIX ""
#endif

#define RZ_DEFINE_CONSTRUCTOR(_func) RZ_MSVC_CTOR(_func, RZ_MSVC_SYMBOL_PREFIX)
#define RZ_DEFINE_DESTRUCTOR(_func)  RZ_MSVC_DTOR(_func, RZ_MSVC_SYMBOL_PREFIX)

#define RZ_MSVC_CTOR(_func, _sym_prefix) \
	static void _func(void); \
	extern int (*_array##_func)(void); \
	int _func##_wrapper(void) { \
		_func(); \
		char *_func##_var = rz_str_dup(""); \
		free(_func##_var); \
		return 0; \
	} \
	__pragma(comment(linker, "/include:" _sym_prefix #_func "_wrapper")) \
		__pragma(section(".CRT$XCU", read)) __declspec(allocate(".CRT$XCU")) int (*_array##_func)(void) = _func##_wrapper;

#define RZ_MSVC_DTOR(_func, _sym_prefix) \
	static void _func(void); \
	extern int (*_array##_func)(void); \
	int _func##_constructor(void) { \
		atexit(_func); \
		char *_func##_var = rz_str_dup(""); \
		free(_func##_var); \
		return 0; \
	} \
	__pragma(comment(linker, "/include:" _sym_prefix #_func "_constructor")) \
		__pragma(section(".CRT$XCU", read)) __declspec(allocate(".CRT$XCU")) int (*_array##_func)(void) = _func##_constructor;

#elif defined(_MSC_VER)

#define RZ_HAS_CONSTRUCTORS                1

/* Pre Visual studio 2008 must use #pragma section */
#define RZ_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define RZ_DEFINE_DESTRUCTOR_NEEDS_PRAGMA  1

#define RZ_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
	section(".CRT$XCU", read)
#define RZ_DEFINE_CONSTRUCTOR(_func) \
	static void _func(void); \
	static int _func##_wrapper(void) { \
		_func(); \
		return 0; \
	} \
	__declspec(allocate(".CRT$XCU")) static int (*p)(void) = _func##_wrapper;

#define RZ_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
	section(".CRT$XCU", read)
#define RZ_DEFINE_DESTRUCTOR(_func) \
	static void _func(void); \
	static int _func##_constructor(void) { \
		atexit(_func); \
		return 0; \
	} \
	__declspec(allocate(".CRT$XCU")) static int (*_array##_func)(void) = _func##_constructor;

#elif defined(__SUNPRO_C)

/* This is not tested, but i believe it should work, based on:
 * http://opensource.apple.com/source/OpenSSL098/OpenSSL098-35/src/fips/fips_premain.c
 */

#define RZ_HAS_CONSTRUCTORS 1

#define RZ_DEFINE_CONSTRUCTOR_NEEDS_PRAGMA 1
#define RZ_DEFINE_DESTRUCTOR_NEEDS_PRAGMA  1

#define RZ_DEFINE_CONSTRUCTOR_PRAGMA_ARGS(_func) \
	init(_func)
#define RZ_DEFINE_CONSTRUCTOR(_func) \
	static void _func(void);

#define RZ_DEFINE_DESTRUCTOR_PRAGMA_ARGS(_func) \
	fini(_func)
#define RZ_DEFINE_DESTRUCTOR(_func) \
	static void _func(void);

#else

/* constructors not supported for this compiler */

#endif

#endif /* __RZ_CONSTRUCTOR_H__ */
