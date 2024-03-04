// SPDX-FileCopyrightText: 2014 condret <condr3t@protonmail.com>
// SPDX-License-Identifier: LGPL-3.0-only

#include <rz_types.hpp>

typedef enum {
	SPC700_ARG_NONE,
	SPC700_ARG_IMM8,
	SPC700_ARG_ABS8,
	SPC700_ARG_ABS8_REL8,
	SPC700_ARG_ABS8_ABS8,
	SPC700_ARG_ABS16,
	SPC700_ARG_ABS13_BIT3,
	SPC700_ARG_REL8,
	SPC700_ARG_IMM8_ABS8,
	SPC700_ARG_UPPER8
} Spc700ArgType;

typedef struct spc700_op_t {
	char *name;
	Spc700ArgType arg;
} Spc700Op;

static const Spc700Op spc700_op_table[] = {
	{ "nop", SPC700_ARG_NONE },
	{ "tcall 0", SPC700_ARG_NONE },
	{ "set1 0x%02x.0", SPC700_ARG_ABS8 },
	{ "bbs 0x%02x.0, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "or a, 0x%02x", SPC700_ARG_ABS8 },
	{ "or a, 0x%04x", SPC700_ARG_ABS16 },
	{ "or a, (x)", SPC700_ARG_NONE },
	{ "or a, [0x%02x+x]", SPC700_ARG_ABS8 },
	{ "or a, #0x%02x", SPC700_ARG_IMM8 },
	{ "or 0x%02x, 0x%02x", SPC700_ARG_ABS8_ABS8 },
	{ "or1 c, 0x%04x.%u", SPC700_ARG_ABS13_BIT3 },
	{ "asl 0x%02x", SPC700_ARG_ABS8 },
	{ "asl 0x%04x", SPC700_ARG_ABS16 },
	{ "push psw", SPC700_ARG_NONE },
	{ "tset1 0x%04x", SPC700_ARG_ABS16 },
	{ "brk", SPC700_ARG_NONE },
	{ "bpl 0x%04x", SPC700_ARG_REL8 },
	{ "tcall 1", SPC700_ARG_NONE },
	{ "clr1 0x%02x.0", SPC700_ARG_ABS8 },
	{ "bbc 0x%02x.0, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "or a, 0x%02x+x", SPC700_ARG_ABS8 },
	{ "or a, 0x%04x+x", SPC700_ARG_ABS16 },
	{ "or a, 0x%04x+y", SPC700_ARG_ABS16 },
	{ "or a, [0x%02x]+y", SPC700_ARG_ABS8 },
	{ "or 0x%02x, #0x%02x", SPC700_ARG_IMM8_ABS8 },
	{ "or (x), (y)", SPC700_ARG_NONE },
	{ "decw 0x%02x", SPC700_ARG_ABS8 },
	{ "asl 0x%02x+x", SPC700_ARG_ABS8 },
	{ "asl a", SPC700_ARG_NONE },
	{ "dec x", SPC700_ARG_NONE },
	{ "cmp x, 0x%04x", SPC700_ARG_ABS16 },
	{ "jmp [0x%04x+x]", SPC700_ARG_ABS16 },
	{ "clrp", SPC700_ARG_NONE },
	{ "tcall 2", SPC700_ARG_NONE },
	{ "set1 0x%02x.1", SPC700_ARG_ABS8 },
	{ "bbs 0x%02x.1, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "and a, 0x%02x", SPC700_ARG_ABS8 },
	{ "and a, 0x%04x", SPC700_ARG_ABS16 },
	{ "and a, (x)", SPC700_ARG_NONE },
	{ "and a, [0x%02x+x]", SPC700_ARG_ABS8 },
	{ "and a, #0x%02x", SPC700_ARG_IMM8 },
	{ "and 0x%02x, 0x%02x", SPC700_ARG_ABS8_ABS8 },
	{ "or1 c, ~0x%04x.%u", SPC700_ARG_ABS13_BIT3 },
	{ "rol 0x%02x", SPC700_ARG_ABS8 },
	{ "rol 0x%04x", SPC700_ARG_ABS16 },
	{ "push a", SPC700_ARG_NONE },
	{ "cbne 0x%02x, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "bra 0x%04x", SPC700_ARG_REL8 },
	{ "bmi 0x%04x", SPC700_ARG_REL8 },
	{ "tcall 3", SPC700_ARG_NONE },
	{ "clr1 0x%02x.1", SPC700_ARG_ABS8 },
	{ "bbc 0x%02x.1, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "and a, 0x%02x+x", SPC700_ARG_ABS8 },
	{ "and a, 0x%04x+x", SPC700_ARG_ABS16 },
	{ "and a, 0x%04x+y", SPC700_ARG_ABS16 },
	{ "and a, [0x%02x]+y", SPC700_ARG_ABS8 },
	{ "and 0x%02x, #0x%02x", SPC700_ARG_IMM8_ABS8 },
	{ "and (x), (y)", SPC700_ARG_NONE },
	{ "incw 0x%02x", SPC700_ARG_ABS8 },
	{ "rol 0x%02x+x", SPC700_ARG_ABS8 },
	{ "rol a", SPC700_ARG_NONE },
	{ "inc x", SPC700_ARG_NONE },
	{ "cmp x, 0x%02x", SPC700_ARG_ABS8 },
	{ "call 0x%04x", SPC700_ARG_ABS16 },
	{ "setp", SPC700_ARG_NONE },
	{ "tcall 4", SPC700_ARG_NONE },
	{ "set1 0x%02x.2", SPC700_ARG_ABS8 },
	{ "bbs 0x%02x.2, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "eor a, 0x%02x", SPC700_ARG_ABS8 },
	{ "eor a, 0x%04x", SPC700_ARG_ABS16 },
	{ "eor a, (x)", SPC700_ARG_NONE },
	{ "eor a, [0x%02x+x]", SPC700_ARG_ABS8 },
	{ "eor a, #0x%02x", SPC700_ARG_IMM8 },
	{ "eor 0x%02x, 0x%02x", SPC700_ARG_ABS8_ABS8 },
	{ "and1 c, 0x%04x.%u", SPC700_ARG_ABS13_BIT3 },
	{ "lsr 0x%02x", SPC700_ARG_ABS8 },
	{ "lsr 0x%04x", SPC700_ARG_ABS16 },
	{ "push x", SPC700_ARG_NONE },
	{ "tclr1 0x%04x", SPC700_ARG_ABS16 },
	{ "pcall 0x%02x", SPC700_ARG_UPPER8 },
	{ "bvc 0x%04x", SPC700_ARG_REL8 },
	{ "tcall 5", SPC700_ARG_NONE },
	{ "clr1 0x%02x.2", SPC700_ARG_ABS8 },
	{ "bbc 0x%02x.2, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "eor a, 0x%02x+x", SPC700_ARG_ABS8 },
	{ "eor a, 0x%04x+x", SPC700_ARG_ABS16 },
	{ "eor a, 0x%04x+y", SPC700_ARG_ABS16 },
	{ "eor a, [0x%02x]+y", SPC700_ARG_ABS8 },
	{ "eor 0x%02x, #0x%02x", SPC700_ARG_IMM8_ABS8 },
	{ "eor (x), (y)", SPC700_ARG_NONE },
	{ "cmpw ya, 0x%02x", SPC700_ARG_ABS8 },
	{ "lsr 0x%02x+x", SPC700_ARG_ABS8 },
	{ "lsr a", SPC700_ARG_NONE },
	{ "mov x, a", SPC700_ARG_NONE },
	{ "cmp y, 0x%04x", SPC700_ARG_ABS16 },
	{ "jmp 0x%04x", SPC700_ARG_ABS16 },
	{ "clrc", SPC700_ARG_NONE },
	{ "tcall 6", SPC700_ARG_NONE },
	{ "set1 0x%02x.3", SPC700_ARG_ABS8 },
	{ "bbs 0x%02x.3, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "cmp a, 0x%02x", SPC700_ARG_ABS8 },
	{ "cmp a, 0x%04x", SPC700_ARG_ABS16 },
	{ "cmp a, (x)", SPC700_ARG_NONE },
	{ "cmp a, [0x%02x+x]", SPC700_ARG_ABS8 },
	{ "cmp a, #0x%02x", SPC700_ARG_IMM8 },
	{ "cmp 0x%02x, 0x%02x", SPC700_ARG_ABS8_ABS8 },
	{ "and1 c, ~0x%04x.%u", SPC700_ARG_ABS13_BIT3 },
	{ "ror 0x%02x", SPC700_ARG_ABS8 },
	{ "ror 0x%04x", SPC700_ARG_ABS16 },
	{ "push y", SPC700_ARG_NONE },
	{ "dbnz 0x%02x, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "ret", SPC700_ARG_NONE },
	{ "bvs 0x%04x", SPC700_ARG_REL8 },
	{ "tcall 7", SPC700_ARG_NONE },
	{ "clr1 0x%02x.3", SPC700_ARG_ABS8 },
	{ "bbc 0x%02x.3, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "cmp a, 0x%02x+x", SPC700_ARG_ABS8 },
	{ "cmp a, 0x%04x+x", SPC700_ARG_ABS16 },
	{ "cmp a, 0x%04x+y", SPC700_ARG_ABS16 },
	{ "cmp a, [0x%02x]+y", SPC700_ARG_ABS8 },
	{ "cmp 0x%02x, #0x%02x", SPC700_ARG_IMM8_ABS8 },
	{ "cmp (x), (y)", SPC700_ARG_NONE },
	{ "addw ya, 0x%02x", SPC700_ARG_ABS8 },
	{ "ror 0x%02x+x", SPC700_ARG_ABS8 },
	{ "ror a", SPC700_ARG_NONE },
	{ "mov a, x", SPC700_ARG_NONE },
	{ "cmp y, 0x%02x", SPC700_ARG_ABS8 },
	{ "ret1", SPC700_ARG_NONE },
	{ "setc", SPC700_ARG_NONE },
	{ "tcall 8", SPC700_ARG_NONE },
	{ "set1 0x%02x.4", SPC700_ARG_ABS8 },
	{ "bbs 0x%02x.4, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "adc a, 0x%02x", SPC700_ARG_ABS8 },
	{ "adc a, 0x%04x", SPC700_ARG_ABS16 },
	{ "adc a, (x)", SPC700_ARG_NONE },
	{ "adc a, [0x%02x+x]", SPC700_ARG_ABS8 },
	{ "adc a, #0x%02x", SPC700_ARG_IMM8 },
	{ "adc 0x%02x, 0x%02x", SPC700_ARG_ABS8_ABS8 },
	{ "eor1 c, 0x%04x.%u", SPC700_ARG_ABS13_BIT3 },
	{ "dec 0x%02x", SPC700_ARG_ABS8 },
	{ "dec 0x%04x", SPC700_ARG_ABS16 },
	{ "mov y, #0x%02x", SPC700_ARG_IMM8 },
	{ "pop psw", SPC700_ARG_NONE },
	{ "mov 0x%02x, #0x%02x", SPC700_ARG_IMM8_ABS8 },
	{ "bcc 0x%04x", SPC700_ARG_REL8 },
	{ "tcall 9", SPC700_ARG_NONE },
	{ "clr1 0x%02x.4", SPC700_ARG_ABS8 },
	{ "bbc 0x%02x.4, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "adc a, 0x%02x+x", SPC700_ARG_ABS8 },
	{ "adc a, 0x%04x+x", SPC700_ARG_ABS16 },
	{ "adc a, 0x%04x+y", SPC700_ARG_ABS16 },
	{ "adc a, [0x%02x]+y", SPC700_ARG_ABS8 },
	{ "adc 0x%02x, #0x%02x", SPC700_ARG_IMM8_ABS8 },
	{ "adc (x), (y)", SPC700_ARG_NONE },
	{ "subw ya, 0x%02x", SPC700_ARG_ABS8 },
	{ "dec 0x%02x+x", SPC700_ARG_ABS8 },
	{ "dec a", SPC700_ARG_NONE },
	{ "mov x, sp", SPC700_ARG_NONE },
	{ "div ya, x", SPC700_ARG_NONE },
	{ "xcn a", SPC700_ARG_NONE },
	{ "ei", SPC700_ARG_NONE },
	{ "tcall 10", SPC700_ARG_NONE },
	{ "set1 0x%02x.5", SPC700_ARG_ABS8 },
	{ "bbs 0x%02x.5, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "sbc a, 0x%02x", SPC700_ARG_ABS8 },
	{ "sbc a, 0x%04x", SPC700_ARG_ABS16 },
	{ "sbc a, (x)", SPC700_ARG_NONE },
	{ "sbc a, [0x%02x+x]", SPC700_ARG_ABS8 },
	{ "sbc a, #0x%02x", SPC700_ARG_IMM8 },
	{ "sbc 0x%02x, 0x%02x", SPC700_ARG_ABS8_ABS8 },
	{ "mov1 c, 0x%04x.%u", SPC700_ARG_ABS13_BIT3 },
	{ "inc 0x%02x", SPC700_ARG_ABS8 },
	{ "inc 0x%04x", SPC700_ARG_ABS16 },
	{ "cmp y, #0x%02x", SPC700_ARG_IMM8 },
	{ "pop a", SPC700_ARG_NONE },
	{ "mov (x)+, a", SPC700_ARG_NONE },
	{ "bcs 0x%04x", SPC700_ARG_REL8 },
	{ "tcall 11", SPC700_ARG_NONE },
	{ "clr1 0x%02x.5", SPC700_ARG_ABS8 },
	{ "bbc 0x%02x.5, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "sbc a, 0x%02x+x", SPC700_ARG_ABS8 },
	{ "sbc a, 0x%04x+x", SPC700_ARG_ABS16 },
	{ "sbc a, 0x%04x+y", SPC700_ARG_ABS16 },
	{ "sbc a, [0x%02x]+y", SPC700_ARG_ABS8 },
	{ "sbc 0x%02x, #0x%02x", SPC700_ARG_IMM8_ABS8 },
	{ "sbc (x), (y)", SPC700_ARG_NONE },
	{ "movw ya, 0x%02x", SPC700_ARG_ABS8 },
	{ "inc 0x%02x+x", SPC700_ARG_ABS8 },
	{ "inc a", SPC700_ARG_NONE },
	{ "mov sp, x", SPC700_ARG_NONE },
	{ "das a", SPC700_ARG_NONE },
	{ "mov a, (x)+", SPC700_ARG_NONE },
	{ "di", SPC700_ARG_NONE },
	{ "tcall 12", SPC700_ARG_NONE },
	{ "set1 0x%02x.6", SPC700_ARG_ABS8 },
	{ "bbs 0x%02x.6, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "mov 0x%02x, a", SPC700_ARG_ABS8 },
	{ "mov 0x%04x, a", SPC700_ARG_ABS16 },
	{ "mov (x), a", SPC700_ARG_NONE },
	{ "mov [0x%02x+x], a", SPC700_ARG_ABS8 },
	{ "cmp x, #0x%02x", SPC700_ARG_IMM8 },
	{ "mov 0x%04x, x", SPC700_ARG_ABS16 },
	{ "mov1 0x%04x.%u, c", SPC700_ARG_ABS13_BIT3 },
	{ "mov 0x%02x, y", SPC700_ARG_ABS8 },
	{ "mov 0x%04x, y", SPC700_ARG_ABS16 },
	{ "mov x, #0x%02x", SPC700_ARG_IMM8 },
	{ "pop x", SPC700_ARG_NONE },
	{ "mul ya", SPC700_ARG_NONE },
	{ "bne 0x%04x", SPC700_ARG_REL8 },
	{ "tcall 13", SPC700_ARG_NONE },
	{ "clr1 0x%02x.6", SPC700_ARG_ABS8 },
	{ "bbc 0x%02x.6, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "mov 0x%02x+x, a", SPC700_ARG_ABS8 },
	{ "mov 0x%04x+x, a", SPC700_ARG_ABS16 },
	{ "mov 0x%04x+y, a", SPC700_ARG_ABS16 },
	{ "mov [0x%02x]+y, a", SPC700_ARG_ABS8 },
	{ "mov 0x%02x, x", SPC700_ARG_ABS8 },
	{ "mov 0x%02x+y, x", SPC700_ARG_ABS8 },
	{ "movw 0x%02x, ya", SPC700_ARG_ABS8 },
	{ "mov 0x%02x+x, y", SPC700_ARG_ABS8 },
	{ "dec y", SPC700_ARG_NONE },
	{ "mov a, y", SPC700_ARG_NONE },
	{ "cbne 0x%02x+x, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "daa a", SPC700_ARG_NONE },
	{ "clrv", SPC700_ARG_NONE },
	{ "tcall 14", SPC700_ARG_NONE },
	{ "set1 0x%02x.7", SPC700_ARG_ABS8 },
	{ "bbs 0x%02x.7, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "mov a, 0x%02x", SPC700_ARG_ABS8 },
	{ "mov a, 0x%04x", SPC700_ARG_ABS16 },
	{ "mov a, (x)", SPC700_ARG_NONE },
	{ "mov a, [0x%02x+x]", SPC700_ARG_ABS8 },
	{ "mov a, #0x%02x", SPC700_ARG_IMM8 },
	{ "mov x, 0x%04x", SPC700_ARG_ABS16 },
	{ "not1 0x%04x.%u", SPC700_ARG_ABS13_BIT3 },
	{ "mov y, 0x%02x", SPC700_ARG_ABS8 },
	{ "mov y, 0x%04x", SPC700_ARG_ABS16 },
	{ "notc", SPC700_ARG_NONE },
	{ "pop y", SPC700_ARG_NONE },
	{ "sleep", SPC700_ARG_NONE },
	{ "beq 0x%04x", SPC700_ARG_REL8 },
	{ "tcall 15", SPC700_ARG_NONE },
	{ "clr1 0x%02x.7", SPC700_ARG_ABS8 },
	{ "bbc 0x%02x.7, 0x%04x", SPC700_ARG_ABS8_REL8 },
	{ "mov a, 0x%02x+x", SPC700_ARG_ABS8 },
	{ "mov a, 0x%04x+x", SPC700_ARG_ABS16 },
	{ "mov a, 0x%04x+y", SPC700_ARG_ABS16 },
	{ "mov a, [0x%02x]+y", SPC700_ARG_ABS8 },
	{ "mov x, 0x%02x", SPC700_ARG_ABS8 },
	{ "mov x, 0x%02x+y", SPC700_ARG_ABS8 },
	{ "mov 0x%02x, 0x%02x", SPC700_ARG_ABS8_ABS8 },
	{ "mov y, 0x%02x+x", SPC700_ARG_ABS8 },
	{ "inc y", SPC700_ARG_NONE },
	{ "mov y, a", SPC700_ARG_NONE },
	{ "dbnz y, 0x%04x", SPC700_ARG_REL8 },
	{ "stop", SPC700_ARG_NONE }
};