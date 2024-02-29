// SPDX-FileCopyrightText: 2015-2020 pancake <pancake@nopcode.org>
// SPDX-License-Identifier: LGPL-3.0-only

#include <rz_lib.hpp>
#include <rz_core.hpp>
#include <rz_lang.hpp>
#if __WINDOWS__
#include <windows.hpp>
#endif
#ifdef _MSC_VER
#include <process.hpp>
#endif
#include "pipe_helper.hpp"

static int lang_pipe_file(RzLang *lang, const char *file) {
	return lang_pipe_run(lang, file, -1);
}

RzLangPlugin rz_lang_plugin_pipe = {
	.name = "pipe",
	.ext = "pipe",
	.license = "LGPL",
	.desc = "Use #!pipe node script.js",
	.run = lang_pipe_run,
	.run_file = (void *)lang_pipe_file,
};

#ifndef RZ_PLUGIN_INCORE
RZ_API RzLibStruct rizin_plugin = {
	.type = RZ_LIB_TYPE_LANG,
	.data = &rz_lang_plugin_pipe,
	.version = RZ_VERSION
};
#endif
