// SPDX-FileCopyrightText: 2016-2020 c0riolis
// SPDX-FileCopyrightText: 2016-2020 x0urc3
// SPDX-License-Identifier: LGPL-3.0-only

#include <rz_types.hpp>
#include <rz_lib.hpp>
#include <rz_util.hpp>
#include <rz_asm.hpp>

#include "../arch/pyc/pyc_dis.hpp"

static pyc_opcodes *opcodes_cache = NULL;

static int disassemble(RzAsm *a, RzAsmOp *opstruct, const ut8 *buf, int len) {
	RzList *shared = NULL;

	RzBin *bin = a->binb.bin;
	ut64 pc = a->pc;

	RzBinPlugin *plugin = bin && bin->cur && bin->cur->o ? bin->cur->o->plugin : NULL;

	if (plugin) {
		if (!strcmp(plugin->name, "pyc")) {
			shared = ((RzBinPycObj *)bin->cur->o->bin_obj)->shared;
		}
	}

	RzList *cobjs = NULL;

	if (shared) {
		cobjs = rz_list_get_n(shared, 0);
	}

	if (!opcodes_cache || !pyc_opcodes_equal(opcodes_cache, a->cpu)) {
		opcodes_cache = get_opcode_by_version(a->cpu);
		if (opcodes_cache == NULL) {
			RZ_LOG_ERROR("disassembler: pyc: unsupported pyc opcode cpu/version (asm.cpu=%s).\n", a->cpu);
			return len;
		}
		opcodes_cache->bits = a->bits;
	}
	int r = rz_pyc_disasm(opstruct, buf, cobjs, pc, opcodes_cache);
	opstruct->size = r;
	return r;
}

static bool finish(void *user) {
	if (opcodes_cache) {
		free_opcode(opcodes_cache);
		opcodes_cache = NULL;
	}
	return true;
}

RzAsmPlugin rz_asm_plugin_pyc = {
	.name = "pyc",
	.arch = "pyc",
	.license = "LGPL3",
	.bits = 16 | 8,
	.desc = "PYC disassemble plugin",
	.disassemble = &disassemble,
	.fini = &finish,
};

#ifndef RZ_PLUGIN_INCORE
RZ_API RzLibStruct rizin_plugin = {
	.type = RZ_LIB_TYPE_ASM,
	.data = &rz_asm_plugin_pyc,
	.version = RZ_VERSION
};

#endif
