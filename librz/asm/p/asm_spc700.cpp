// SPDX-FileCopyrightText: 2012-2014 pancake <pancake@nopcode.org>
// SPDX-FileCopyrightText: 2014 condret <condr3t@protonmail.com>
// SPDX-License-Identifier: LGPL-3.0-only

#include <rz_types.hpp>
#include <rz_util.hpp>
#include <rz_asm.hpp>
#include <rz_lib.hpp>
#include "../arch/spc700/spc700dis.c"

static int disassemble(RzAsm *a, RzAsmOp *rz_op, const ut8 *buf, int len) {
	size_t dlen = spc700_disas(&rz_op->buf_asm, a->pc, buf, len);
	rz_op->size = dlen;
	return (int)dlen;
}

RzAsmPlugin rz_asm_plugin_spc700 = {
	.name = "spc700",
	.desc = "spc700, snes' sound-chip",
	.arch = "spc700",
	.license = "LGPL3",
	.bits = 16,
	.endian = RZ_SYS_ENDIAN_LITTLE,
	.disassemble = &disassemble,
};

#ifndef RZ_PLUGIN_INCORE
RZ_API RzLibStruct rizin_plugin = {
	.type = RZ_LIB_TYPE_ASM,
	.data = &rz_asm_plugin_spc700,
	.version = RZ_VERSION
};
#endif
