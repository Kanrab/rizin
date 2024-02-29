// SPDX-FileCopyrightText: 2016-2020 c0riolis
// SPDX-FileCopyrightText: 2016-2020 x0urc3
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef PYC_DIS_H
#define PYC_DIS_H

#include <rz_types.hpp>
#include <rz_lib.hpp>
#include <rz_util.hpp>
#include <rz_asm.hpp>

#include "opcode.hpp"

#include "../../../bin/format/pyc/marshal.hpp"

int rz_pyc_disasm(RzAsmOp *op, const ut8 *buf, RzList /*<py_code_objects *>*/ *cobjs, ut64 pc, pyc_opcodes *opcodes);

#endif
