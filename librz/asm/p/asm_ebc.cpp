// SPDX-FileCopyrightText: 2012-2018 pancake <pancake@nopcode.org>
// SPDX-FileCopyrightText: 2012-2018 fedor sakharov <fedor.sakharov@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-only

#include <stdio.h>
#include <string.h>
#include <rz_types.hpp>
#include <rz_lib.hpp>
#include <rz_asm.hpp>
#include <ebc_disas.hpp>

static int disassemble(RzAsm *a, RzAsmOp *op, const ut8 *buf, int len) {
	ebc_command_t cmd = { { 0 }, { 0 } };
	int ret = ebc_decode_command(buf, len, &cmd);
	if (cmd.operands[0]) {
		rz_asm_op_setf_asm(op, "%s %s", cmd.instr, cmd.operands);
	} else {
		rz_asm_op_set_asm(op, cmd.instr);
	}
	return op->size = ret;
}

RzAsmPlugin rz_asm_plugin_ebc = {
	.name = "ebc",
	.license = "LGPL3",
	.desc = "EFI Bytecode",
	.author = "Fedor Sakharov",
	.arch = "ebc",
	.bits = 32 | 64,
	.endian = RZ_SYS_ENDIAN_LITTLE,
	.disassemble = &disassemble,
};

#ifndef RZ_PLUGIN_INCORE
RZ_API RzLibStruct rizin_plugin = {
	.type = RZ_LIB_TYPE_ASM,
	.data = &rz_asm_plugin_ebc,
	.version = RZ_VERSION
};
#endif
