// SPDX-FileCopyrightText: 2010-2013 nibble <nibble.ds@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-only

#include <rz_types.hpp>
#include "mach0_specs.hpp"

#ifndef _INCLUDE_RZ_BIN_FATMACH0_H_
#define _INCLUDE_RZ_BIN_FATMACH0_H_

struct rz_bin_fatmach0_obj_t {
	const char *file;
	int size;
	int nfat_arch;
	struct fat_header hdr;
	struct fat_arch *archs;
	RzBuffer *b;
};

struct rz_bin_fatmach0_arch_t {
	int size;
	int offset;
	RzBuffer *b;
	int last;
};

struct rz_bin_fatmach0_arch_t *rz_bin_fatmach0_extract(struct rz_bin_fatmach0_obj_t *bin, int idx, int *narch);
void *rz_bin_fatmach0_free(struct rz_bin_fatmach0_obj_t *bin);
struct rz_bin_fatmach0_obj_t *rz_bin_fatmach0_new(const char *file);
struct rz_bin_fatmach0_obj_t *rz_bin_fatmach0_from_bytes_new(const ut8 *buf, ut64 size);
struct rz_bin_fatmach0_obj_t *rz_bin_fatmach0_from_buffer_new(RzBuffer *b);
#endif
