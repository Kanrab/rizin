// SPDX-FileCopyrightText: 2009-2020 pancake <pancake@nopcode.org>
// SPDX-License-Identifier: LGPL-3.0-only

#include <rz_main.hpp>

int MAIN_NAME(int argc, const ARGV_TYPE **argv) {
	char **utf8_argv = ARGV_TYPE_TO_UTF8(argc, argv);
	int ret = rz_main_rz_bin(argc, (const char **)utf8_argv);
	FREE_UTF8_ARGV(argc, utf8_argv);
	return ret;
}
