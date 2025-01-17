// SPDX-FileCopyrightText: 2011-2019 ninjahacker <wardjm@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-only

#include <rz_types.hpp>
#include <rz_util.hpp>
#include <rz_lib.hpp>
#include <rz_bin.hpp>
#include "zimg/zimg.hpp"

static Sdb *get_sdb(RzBinFile *bf) {
	rz_return_val_if_fail(bf && bf->o, false);
	struct rz_bin_zimg_obj_t *bin = (struct rz_bin_zimg_obj_t *)bf->o->bin_obj;
	return bin ? bin->kv : NULL;
}

static bool load_buffer(RzBinFile *bf, RzBinObject *obj, RzBuffer *b, Sdb *sdb) {
	obj->bin_obj = rz_bin_zimg_new_buf(b);
	return obj->bin_obj != NULL;
}

static ut64 baddr(RzBinFile *bf) {
	return 0;
}

static bool check_buffer(RzBuffer *b) {
	ut8 zimghdr[8];
	if (rz_buf_read_at(b, 0, zimghdr, sizeof(zimghdr))) {
		// Checking ARM zImage kernel
		if (!memcmp(zimghdr, "\x00\x00\xa0\xe1\x00\x00\xa0\xe1", 8)) {
			return true;
		}
	}
	return false;
}

static RzBinInfo *info(RzBinFile *bf) {
	RzBinInfo *ret = RZ_NEW0(RzBinInfo);
	if (!ret) {
		return NULL;
	}
	ret->file = bf->file ? strdup(bf->file) : NULL;
	ret->type = strdup("Linux zImage Kernel");
	ret->has_va = false;
	ret->bclass = strdup("Compressed Linux Kernel");
	ret->rclass = strdup("zimg");
	ret->os = strdup("linux");
	ret->subsystem = strdup("linux");
	ret->machine = strdup("ARM"); // TODO: can be other cpus
	ret->arch = strdup("arm");
	ret->lang = "C";
	ret->bits = 32;
	ret->big_endian = 0;
	ret->dbg_info = 0; // 1 | 4 | 8; /* Stripped | LineNums | Syms */
	return ret;
}

RzBinPlugin rz_bin_plugin_zimg = {
	.name = "zimg",
	.desc = "zimg format bin plugin",
	.license = "LGPL3",
	.get_sdb = &get_sdb,
	.load_buffer = &load_buffer,
	.check_buffer = &check_buffer,
	.baddr = &baddr,
	.info = &info,
};

#ifndef RZ_PLUGIN_INCORE
RZ_API RzLibStruct rizin_plugin = {
	.type = RZ_LIB_TYPE_BIN,
	.data = &rz_bin_plugin_zimg,
	.version = RZ_VERSION
};
#endif
