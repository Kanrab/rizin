// SPDX-FileCopyrightText: 2016 Davis
// SPDX-FileCopyrightText: 2016 Alex Kornitzer <alex.kornitzer@countercept.com>
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef MDMP_PE_H
#define MDMP_PE_H

#include <rz_types.hpp>
#include <rz_util.hpp>
#include <rz_lib.hpp>
#include <rz_bin.hpp>

#include "pe/pe.hpp"

#include "mdmp_specs.hpp"

struct PE_(rz_bin_mdmp_pe_bin) {
	ut64 vaddr;
	ut64 paddr;
	struct PE_(rz_bin_pe_obj_t) * bin;
};

RzPVector /*<RzBinAddr *>*/ *PE_(rz_bin_mdmp_pe_get_entrypoint)(struct PE_(rz_bin_mdmp_pe_bin) * pe_bin);
RzPVector /*<RzBinImport *>*/ *PE_(rz_bin_mdmp_pe_get_imports)(struct PE_(rz_bin_mdmp_pe_bin) * pe_bin);
RzPVector /*<RzBinSection *>*/ *PE_(rz_bin_mdmp_pe_get_sections)(struct PE_(rz_bin_mdmp_pe_bin) * pe_bin);
RzList /*<RzBinSymbol *>*/ *PE_(rz_bin_mdmp_pe_get_symbols)(RzBin *rbin, struct PE_(rz_bin_mdmp_pe_bin) * pe_bin);

#endif /* MDMP_PE_H */
