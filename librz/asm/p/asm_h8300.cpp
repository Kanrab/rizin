// SPDX-FileCopyrightText: 2014-2018 fedor.sakharov <fedor.sakharov@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-only

#include <stdio.h>
#include <string.h>
#include <rz_types.hpp>
#include <rz_lib.hpp>
#include <rz_asm.hpp>
#include <h8300_disas.hpp>

static int disassemble(RzAsm *a, RzAsmOp *op, const ut8 *buf, int len) {
	struct h8300_cmd cmd;
	int ret = h8300_decode_command(buf, &cmd);
	rz_asm_op_setf_asm(op, "%s %s", cmd.instr, cmd.operands);
	return op->size = ret;
}

RzAsmPlugin rz_asm_plugin_h8300 = {
	.name = "h8300",
	.license = "LGPL3",
	.desc = "H8/300 disassembly plugin",
	.arch = "h8300",
	.bits = 16,
	.endian = RZ_SYS_ENDIAN_BIG,
	.disassemble = &disassemble
};

#ifndef RZ_PLUGIN_INCORE
RZ_API RzLibStruct rizin_plugin = {
	.type = RZ_LIB_TYPE_ASM,
	.data = &rz_asm_plugin_h8300,
	.version = RZ_VERSION
};
#endif
