// SPDX-FileCopyrightText: 2014 pancake <pancake@nopcode.org>
// SPDX-License-Identifier: LGPL-3.0-only

// included from p/debug_native.c
// split for better reading/cleaning up

static char *rz_debug_native_reg_profile(RzDebug *dbg) {
#if __WINDOWS__
/*_______
 |   |   |
 |___|___|
 |   |   |
 |___|___|
*/
#if defined(__arm64__)
	if (dbg->bits == RZ_SYS_BITS_64) {
#include "reg/windows-arm64.hpp"
	} else {
#include "reg/windows-arm64_32.hpp"
	}
#elif defined(__arm__)
#include "reg/windows-arm.hpp"
#elif defined(__x86_64__)
#include "reg/windows-x64.hpp"
#elif defined(__i386__)
#include "reg/windows-x86.hpp"
#endif
#elif (__OpenBSD__ || __NetBSD__)
/*                           __.--..__
       \-/-/-/    _ __  _.--'  _.--'
  _  \'       \   \\  ''      `------.__
  \\/      __)_)   \\      ____..---'
  //\       o  o    \\----'
     / <_/      3    \\
      \_,_,__,_/      \\
*/
#if __i386__
#include "reg/netbsd-x86.hpp"
#elif __x86_64__
#include "reg/netbsd-x64.hpp"
#else
#error "Unsupported BSD architecture"
#endif

#elif __KFBSD__ || __FreeBSD__
/*
    /(       ).
    \ \__   /|
    /  _ '-/ |
   (/\/ |    \
   / /  | \   )
   O O _/     |
  (__)  __   /
    \___/   /
      `----'
*/
#if __i386__ || __i386
#include "reg/kfbsd-x86.hpp"
#elif __x86_64__ || __amd64__
#include "reg/kfbsd-x64.hpp"
#elif __aarch64__
#include "reg/kfbsd-arm64.hpp"
#else
#error "Unsupported BSD architecture"
#endif

#else
#warning Unsupported Kernel
	return NULL;
#endif
}
