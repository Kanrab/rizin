// SPDX-FileCopyrightText: 2009-2017 pancake <pancake@nopcode.org>
// SPDX-License-Identifier: LGPL-3.0-only

#include <rz_bp.hpp>
#include <rz_lib.hpp>

static struct rz_bp_arch_t rz_bp_plugin_arm_bps[] = {
	{ 64, 4, 0, (const ut8 *)"\x00\x00\x20\xd4" }, // le - arm64 brk0
	{ 64, 4, 1, (const ut8 *)"\xd4\x20\x00\x00" }, // be - arm64
	//{ 64, 1, 0, (const ut8*)"\xfe\xde\xff\xe7" }, // le - arm64 // hacky fix

	{ 32, 4, 0, (const ut8 *)"\xf0\x01\xf0\xe7" }, // eabi-le - undefined instruction - for all kernels
	{ 32, 4, 1, (const ut8 *)"\xe7\xf0\x01\xf0" }, // eabi-be

//	{ 32, 1, 0, (const ut8*)"\xff\xff\xff\xff" }, // le - linux only? (undefined instruction)
//	{ 32, 1, 1, (const ut8*)"\xff\xff\xff\xff" }, // be - linux only? (undefined instruction)
//	{ 32, 4, 0, (const ut8*)"\x01\x00\x9f\xef" }, // le - linux only? (undefined instruction)
//	{ 32, 4, 1, (const ut8*)"\xef\x9f\x00\x01" }, // be
#if 0
	{ 4, 0, (const ut8*)"\xfe\xde\xff\xe7" }, // arm-le - from a gdb patch
	{ 4, 1, (const ut8*)"\xe7\xff\xde\xfe" }, // arm-be
        { 4, 0, (const ut8*)"\xf0\x01\xf0\xe7" }, // eabi-le - undefined instruction - for all kernels
	{ 4, 1, (const ut8*)"\xe7\xf0\x01\xf0" }, // eabi-be
#endif
	{ 16, 2, 0, (const ut8 *)"\x01\xbe" }, // thumb-le
	{ 16, 2, 1, (const ut8 *)"\xbe\x01" }, // thumb-be
	{ 16, 2, 0, (const ut8 *)"\xfe\xdf" }, // arm-thumb-le
	{ 16, 2, 1, (const ut8 *)"\xdf\xfe" }, // arm-thumb-be
	{ 16, 4, 0, (const ut8 *)"\xff\xff\xff\xff" }, // arm-thumb-le
	{ 16, 4, 1, (const ut8 *)"\xff\xff\xff\xff" }, // arm-thumb-be
	{ 0, 0, 0, NULL }
};

struct rz_bp_plugin_t rz_bp_plugin_arm = {
	.name = "arm",
	.arch = "arm",
	.nbps = 9,
	.bps = rz_bp_plugin_arm_bps,
};

#ifndef RZ_PLUGIN_INCORE
RZ_API RzLibStruct rizin_plugin = {
	.type = RZ_LIB_TYPE_BP,
	.data = &rz_bp_plugin_arm,
	.version = RZ_VERSION
};
#endif
