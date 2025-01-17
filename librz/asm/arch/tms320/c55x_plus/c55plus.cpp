// SPDX-FileCopyrightText: 2013 th0rpe <josediazfer@yahoo.es>
// SPDX-License-Identifier: LGPL-3.0-only

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <rz_types.hpp>
#include <rz_lib.hpp>
#include <rz_asm.hpp>

#define USE_DECODE
#include "decode.hpp"

#include "../tms320_dasm.hpp"

extern ut8 *ins_buff;
extern ut32 ins_buff_len;
extern char *c55plus_decode(ut32 ins_pos, ut32 *next_ins_pos);

int c55x_plus_disassemble(tms320_dasm_t *dasm, const ut8 *buf, int len) {
	unsigned int next_ins_pos;
	char *ins_decoded;
	size_t i, ins_decoded_len;

	ins_buff = (ut8 *)buf;
	ins_buff_len = (ut32)len;

	next_ins_pos = 0;

	// decode instruction
	ins_decoded = c55plus_decode(0, &next_ins_pos);
	dasm->length = next_ins_pos;
	if (!ins_decoded) {
		return 0;
	}

	// opcode length
	dasm->length = next_ins_pos;
	ins_decoded_len = strlen(ins_decoded);
	for (i = 0; i < ins_decoded_len; i++) {
		{
			ins_decoded[i] = tolower((unsigned char)ins_decoded[i]);
		}
	}
	snprintf(dasm->syntax, sizeof(dasm->syntax), "%s", ins_decoded);
	free(ins_decoded);

	return next_ins_pos;
}
