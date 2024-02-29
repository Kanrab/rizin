// SPDX-FileCopyrightText: 2016-2020 c0riolis
// SPDX-FileCopyrightText: 2016-2020 x0urc3
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef PYC_H
#define PYC_H

#include <rz_types.hpp>
#include <rz_util.hpp>
#include <rz_lib.hpp>
#include <rz_bin.hpp>
#include "pyc_magic.hpp"
#include "marshal.hpp"

bool pyc_get_sections_symbols(RzBinPycObj *pyc, RzPVector /*<RzBinSection *>*/ *sections, RzPVector /*<RzBinSymbol *>*/ *symbols, RzList /*<pyc_code_object *>*/ *mem, RzBuffer *buf, ut32 magic);
bool pyc_is_code(ut8 b, ut32 magic);

#endif
