// SPDX-FileCopyrightText: 2020 FXTi <zjxiang1998@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-only

#include "opcode.hpp"

pyc_opcodes *opcode_25(void) {
	pyc_opcodes *ret = opcode_24();
	if (!ret) {
		return NULL;
	}

	ret->version_sig = (void *(*)())opcode_25;

	// Bytecodes added in 2.5 from 2.4
	def_op(.op_obj = ret->opcodes, .op_name = "WITH_CLEANUP", .op_code = 81);

	rz_list_purge(ret->opcode_arg_fmt);
	add_arg_fmt(ret, "EXTENDED_ARG", format_extended_arg);

	return ret;
}
