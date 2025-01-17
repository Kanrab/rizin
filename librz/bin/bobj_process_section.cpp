// SPDX-FileCopyrightText: 2023 RizinOrg <info@rizin.re>
// SPDX-FileCopyrightText: 2023 deroad <wargio@libero.it>
// SPDX-License-Identifier: LGPL-3.0-only
#include <rz_bin.hpp>
#include "i/private.hpp"

static void process_handle_section(RzBinSection *section, RzBinObject *o, HtPP *filter_db) {
	// rebase physical address
	section->paddr += o->opts.loadaddr;

	if (!filter_db) {
		// we do not have to filter the names.
		return;
	}

	// check if section name was already found, then rename it.
	if (!ht_pp_find(filter_db, section->name, NULL)) {
		ht_pp_insert(filter_db, section->name, section);
		return;
	}

	char *name = rz_str_newf("%s_0x%" PFMT64x, section->name, section->paddr);
	free(section->name);
	section->name = name;
}

RZ_IPI void rz_bin_set_and_process_sections(RzBinFile *bf, RzBinObject *o) {
	RzBin *bin = bf->rbin;
	RzBinPlugin *plugin = o->plugin;

	rz_pvector_free(o->sections);
	if (!plugin->sections || !(o->sections = plugin->sections(bf))) {
		o->sections = rz_pvector_new((RzPVectorFree)rz_bin_section_free);
	}

	HtPP *filter_db = bin->filter ? ht_pp_new0() : NULL;

	void **it;
	RzBinSection *element;
	rz_pvector_foreach (o->sections, it) {
		element = *it;
		process_handle_section(element, o, filter_db);
	}

	ht_pp_free(filter_db);
}
