// SPDX-FileCopyrightText: 2013-2021 th0rpe <josediazfer@yahoo.es>
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef C55PLUS_H
#define C55PLUS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rz_types.hpp>
#include <rz_lib.hpp>

#include "../tms320_dasm.hpp"

extern int c55x_plus_disassemble(tms320_dasm_t *dasm, const ut8 *buf, int len);

#endif
